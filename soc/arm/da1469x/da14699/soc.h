#ifndef _SOC__H_
#define _SOC__H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "DA1469xAB.h"

// #if defined(CONFIG_dg_configUSE_HW_SYS) && !defined(dg_configUSE_HW_SYS)
// #define dg_configUSE_HW_SYS CONFIG_dg_configUSE_HW_SYS
// #endif

// /*
//  * CMSIS IRQn_Type enum is broken relative to ARM GNU compiler.
//  *
//  * So redefine the IRQn_Type enum to a unsigned int to avoid
//  * the ARM compiler from sign extending IRQn_Type values higher than 0x80
//  * into negative IRQ values, which causes hard-to-debug Hard Faults.
//  */
// typedef uint32_t IRQn_Type;

// /* Need to keep the remaining from cmsis.h, as Zephyr expects these. */
// typedef enum {
// 	Reset_IRQn                    = -15,
// 	NonMaskableInt_IRQn           = -14,
// 	HardFault_IRQn                = -13,
// 	MemoryManagement_IRQn         = -12,
// 	BusFault_IRQn                 = -11,
// 	UsageFault_IRQn               = -10,
// 	SVCall_IRQn                   =  -5,
// 	DebugMonitor_IRQn             =  -4,
// 	PendSV_IRQn                   =  -2,
// 	SysTick_IRQn                  =  -1,
// } CMSIS_IRQn_Type;

// #if __NVIC_PRIO_BITS != NUM_IRQ_PRIO_BITS
// #define __NVIC_PRIO_BITS        NUM_IRQ_PRIO_BITS
// #endif

#ifdef __cplusplus
}
#endif

#endif /* _SOC__H_ */