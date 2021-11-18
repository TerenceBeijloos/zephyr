#include "custom_config_ram.h"
#include "sdk_defs.h"
#include <core_cm33.h>
#include "hw_bod.h"
#include "hw_cache.h"
#include "hw_pd.h"
#include "hw_qspi.h"
#include "hw_otpc.h"
#include "hw_clk.h"
#include "hw_memctrl.h"
#include "sys_tcs_da1469x.h"
#include "interrupts.h"

// extern uint32_t __copy_table_start__;
// extern uint32_t __copy_table_end__;
// extern uint32_t __zero_table_start__;
// extern uint32_t __zero_table_end__;
extern uint8_t end;
// extern uint8_t __HeapLimit;

/*
 * Global variables
 */
__RETAINED_RW static uint8_t *heapend = &end;
__RETAINED_RW uint32_t SystemLPClock = dg_configXTAL32K_FREQ;   /*!< System Low Power Clock Frequency (LP Clock) */


void set_interrupt_priorities(const int8_t prios[])
{
        uint32_t old_primask, iser, iser2;
        int i = 0;
        uint32_t prio = 0;

        // Assign all bit for preemption to be preempt priority bits.
        // (required by FreeRTOS)
        NVIC_SetPriorityGrouping(0);

        /*
         * We shouldn't change the priority of an enabled interrupt.
         *  1. Globally disable interrupts, saving the global interrupts disable state.
         *  2. Explicitly disable all interrupts, saving the individual interrupt enable state.
         *  3. Set interrupt priorities.
         *  4. Restore individual interrupt enables.
         *  5. Restore global interrupt enable state.
         */
        old_primask = __get_PRIMASK();
        __disable_irq();
        iser  = NVIC->ISER[0];
        iser2 = NVIC->ISER[1];
        NVIC->ICER[0] = iser;
        NVIC->ICER[1] = iser2;

        for (i = 0; prios[i] != PRIORITY_TABLE_END; ++i) {
                switch (prios[i]) {
                case PRIORITY_0:
                case PRIORITY_1:
                case PRIORITY_2:
                case PRIORITY_3:
                case PRIORITY_4:
                case PRIORITY_5:
                case PRIORITY_6:
                case PRIORITY_7:
                case PRIORITY_8:
                case PRIORITY_9:
                case PRIORITY_10:
                case PRIORITY_11:
                case PRIORITY_12:
                case PRIORITY_13:
                case PRIORITY_14:
                case PRIORITY_15:
                        prio = prios[i] - PRIORITY_0;
                        break;
                default:
                        NVIC_SetPriority(prios[i], prio);
                        break;
                }
        }

        NVIC->ISER[0] = iser;
        NVIC->ISER[1] = iser2;
        __set_PRIMASK(old_primask);

        // enable Usage-, Bus-, and MMU Fault
        SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
                   |  SCB_SHCSR_BUSFAULTENA_Msk
                   |  SCB_SHCSR_MEMFAULTENA_Msk;
}


void da1469x_SystemInit(void)
{
        REG_SETF(CRG_TOP, POWER_CTRL_REG, LDO_RADIO_ENABLE, 1); // Switch on the RF LDO

        /*
         * Initialize busy status register
         */
        hw_sys_sw_bsr_init();

        /*
         * Apply default priorities to interrupts.
         */
        set_interrupt_priorities(__dialog_interrupt_priorities);

        SystemLPClock = dg_configXTAL32K_FREQ;

#if ((dg_configCODE_LOCATION == NON_VOLATILE_IS_FLASH) && (dg_configEXEC_MODE == MODE_IS_CACHED))
        /* Disable cache before reinitialize QSPI */
        uint32_t cache_len = hw_cache_get_len();
        hw_cache_disable();
#endif

        /* Disable QSPI init after power up */
        hw_qspi_disable_init(HW_QSPIC);
        /* The bootloader may have left the Flash in wrong mode */
        qspi_automode_init();

#if ((dg_configCODE_LOCATION == NON_VOLATILE_IS_FLASH) && (dg_configEXEC_MODE == MODE_IS_CACHED))
        hw_cache_enable(cache_len);
#endif

        /* Already up in SystemInitPre()
         * PD_TIM is kept active here in order to program XTAL and PLL registers*/
        ASSERT_WARNING(hw_pd_check_tim_status());

        /* enable OTP to read TCS values */
        hw_otpc_init();
        hw_otpc_set_speed(HW_OTPC_CLK_FREQ_32MHz);
        hw_otpc_enter_mode(HW_OTPC_MODE_READ);
        /* get TCS values */
        sys_tcs_get_trim_values_from_cs();
        /*
         * Apply trimmed values for xtal32m in case no entry exists in OTP
         */
        hw_sys_apply_default_values();
        /* Close OPT */
        hw_otpc_close();
        // configure_cache(); TODO

// #if defined(CONFIG_RETARGET) || defined(CONFIG_RTT)
//         /* This is needed to initialize stdout, so that it can be used by putchar (that doesn't initialize stdout,
//          * contrary to printf). Putchar is needed by the Unity test framework
//          * This also has the side effect of changing stdout to unbuffered (which seems more reasonable)
//          */
//         setvbuf(stdout, NULL, _IONBF, 0);
// #endif

        /*
         * Keep PD_PER enabled.
         */
        hw_sys_pd_periph_enable();

        /* Default settings to be used if no CS setting is available*/
        CHARGER->CHARGER_TEST_CTRL_REG = DEFAULT_CHARGER_TEST_CTRL_REG;

        /*
         * Apply tcs settings.
         * They need to be re-applied when the blocks they contain are enabled.
         * PD_MEM is by default enabled.
         * PD_AON settings are applied by the booter
         */
        sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_MEM);
        sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_PER);
        /* In non baremetal apps PD_COMM will be opened by the  power manager */
#ifdef OS_BAREMETAL
        hw_sys_pd_com_enable();
        sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_COMM);
#endif
        sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_SYS);
        sys_tcs_apply_reg_pairs(SYS_TCS_GROUP_PD_TMR);

        /*
         * Apply custom trim settings which don't require the respective block to be enabled
         */
        sys_tcs_apply_custom_values(SYS_TCS_GROUP_GP_ADC_SINGLE_MODE, sys_tcs_custom_values_system_cb, NULL);
        sys_tcs_apply_custom_values(SYS_TCS_GROUP_GP_ADC_DIFF_MODE, sys_tcs_custom_values_system_cb, NULL);

        /*
         * Apply preferred settings on top of tcs settings.
         */
        hw_sys_set_preferred_values(HW_PD_AON);
        hw_sys_set_preferred_values(HW_PD_SYS);
        hw_sys_set_preferred_values(HW_PD_TMR);

#if dg_configUSE_CLOCK_MGR
        cm_clk_init_low_level_internal();
#else
        hw_clk_xtalm_configure();
        if (dg_configXTAL32M_SETTLE_TIME_IN_USEC != 0) {
                hw_clk_set_xtalm_settling_time(XTAL32M_USEC_TO_256K_CYCLES(dg_configXTAL32M_SETTLE_TIME_IN_USEC)/8, false);
        }
#endif

        configure_pdc();

#if dg_configUSE_CLOCK_MGR
        // Always enable the XTAL32M
        cm_enable_xtalm();
        while (!cm_poll_xtalm_ready());                 // Wait for XTAL32M to settle
        hw_clk_set_sysclk(SYS_CLK_IS_XTAL32M);          // Set XTAL32M as sys_clk

#if ((dg_configLP_CLK_SOURCE == LP_CLK_IS_ANALOG) && (dg_configUSE_LP_CLK == LP_CLK_RCX))
        /*
         * Note: If the LP clock is the RCX then we have to wait for the XTAL32M to settle
         *       since we need to estimate the frequency of the RCX before continuing
         *       (calibration procedure).
         */
        cm_rcx_calibrate();
        hw_clk_set_lpclk(LP_CLK_IS_RCX);        // Set RCX as the LP clock
#endif
#if dg_configUSE_HW_RTC
        configure_rtc();
#endif
#else
        /* perform clock initialization here, as there is no clock manager to do it later for us */
        nortos_clk_setup();
#endif

        /* Calculate pll_min_current value
         * Apply value to PLL_SYS_CTRL3_REG
         */
        hw_sys_pll_calculate_min_current();
        hw_sys_pll_set_min_current();

        /*
         * BOD protection
         */
#if (dg_configUSE_BOD == 1)
        /* BOD has already been enabled at this point but it must be reconfigured */
        hw_bod_configure();
#else
        hw_bod_deactivate();
#endif




#if dg_configFPGA_AD9361_RADIO
#if defined(CONFIG_USE_BLE)
        /*  We need the SPI port if external radio is used - enable it if needed. */
        if (!hw_pd_check_com_status()) {
                hw_sys_pd_com_enable();
        }

        ASSERT_ERROR(REG_GETF(CRG_TOP, PMU_CTRL_REG, COM_SLEEP) == 0);

        /* Initialize FPGA radio */
        ad9361_radio_init();

        /* Now COM power domain could be disabled - radio has been initialized. */
        hw_sys_pd_com_disable();
        hw_pd_wait_power_down_com();
#endif /* defined(CONFIG_USE_BLE) */
#endif /* dg_configFPGA_AD9361_RADIO */
}
