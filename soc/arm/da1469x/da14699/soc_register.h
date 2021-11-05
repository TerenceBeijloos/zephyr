#ifndef _RENESAS_da1469X_REGS_H_
#define _RENESAS_da1469X_REGS_H_

// TODO:  license

#include <sys/util.h>
#include <zephyr/types.h>

struct DA1469x_GPIO{                                /*!< (@ 0x50020A00) GPIO Structure                                             */
  __IOM uint32_t  P0_DATA_REG;                  /*!< (@ 0x00000000) P0 Data input / output Register                            */
  __IOM uint32_t  P1_DATA_REG;                  /*!< (@ 0x00000004) P1 Data input / output Register                            */
  __IOM uint32_t  P0_SET_DATA_REG;              /*!< (@ 0x00000008) P0 Set port pins Register                                  */
  __IOM uint32_t  P1_SET_DATA_REG;              /*!< (@ 0x0000000C) P1 Set port pins Register                                  */
  __IOM uint32_t  P0_RESET_DATA_REG;            /*!< (@ 0x00000010) P0 Reset port pins Register                                */
  __IOM uint32_t  P1_RESET_DATA_REG;            /*!< (@ 0x00000014) P1 Reset port pins Register                                */
  __IOM uint32_t  P0_00_MODE_REG;               /*!< (@ 0x00000018) P0_00 Mode Register                                        */
  __IOM uint32_t  P0_01_MODE_REG;               /*!< (@ 0x0000001C) P0_01 Mode Register                                        */
  __IOM uint32_t  P0_02_MODE_REG;               /*!< (@ 0x00000020) P0_02 Mode Register                                        */
  __IOM uint32_t  P0_03_MODE_REG;               /*!< (@ 0x00000024) P0_03 Mode Register                                        */
  __IOM uint32_t  P0_04_MODE_REG;               /*!< (@ 0x00000028) P0_04 Mode Register                                        */
  __IOM uint32_t  P0_05_MODE_REG;               /*!< (@ 0x0000002C) P0_05 Mode Register                                        */
  __IOM uint32_t  P0_06_MODE_REG;               /*!< (@ 0x00000030) P0_06 Mode Register                                        */
  __IOM uint32_t  P0_07_MODE_REG;               /*!< (@ 0x00000034) P0_07 Mode Register                                        */
  __IOM uint32_t  P0_08_MODE_REG;               /*!< (@ 0x00000038) P0_08 Mode Register                                        */
  __IOM uint32_t  P0_09_MODE_REG;               /*!< (@ 0x0000003C) P0_09 Mode Register                                        */
  __IOM uint32_t  P0_10_MODE_REG;               /*!< (@ 0x00000040) P0_10 Mode Register                                        */
  __IOM uint32_t  P0_11_MODE_REG;               /*!< (@ 0x00000044) P0_11 Mode Register                                        */
  __IOM uint32_t  P0_12_MODE_REG;               /*!< (@ 0x00000048) P0_12 Mode Register                                        */
  __IOM uint32_t  P0_13_MODE_REG;               /*!< (@ 0x0000004C) P0_13 Mode Register                                        */
  __IOM uint32_t  P0_14_MODE_REG;               /*!< (@ 0x00000050) P0_14 Mode Register                                        */
  __IOM uint32_t  P0_15_MODE_REG;               /*!< (@ 0x00000054) P0_15 Mode Register                                        */
  __IOM uint32_t  P0_16_MODE_REG;               /*!< (@ 0x00000058) P0_16 Mode Register                                        */
  __IOM uint32_t  P0_17_MODE_REG;               /*!< (@ 0x0000005C) P0_17 Mode Register                                        */
  __IOM uint32_t  P0_18_MODE_REG;               /*!< (@ 0x00000060) P0_18 Mode Register                                        */
  __IOM uint32_t  P0_19_MODE_REG;               /*!< (@ 0x00000064) P0_19 Mode Register                                        */
  __IOM uint32_t  P0_20_MODE_REG;               /*!< (@ 0x00000068) P0_20 Mode Register                                        */
  __IOM uint32_t  P0_21_MODE_REG;               /*!< (@ 0x0000006C) P0_21 Mode Register                                        */
  __IOM uint32_t  P0_22_MODE_REG;               /*!< (@ 0x00000070) P0_22 Mode Register                                        */
  __IOM uint32_t  P0_23_MODE_REG;               /*!< (@ 0x00000074) P0_23 Mode Register                                        */
  __IOM uint32_t  P0_24_MODE_REG;               /*!< (@ 0x00000078) P0_24 Mode Register                                        */
  __IOM uint32_t  P0_25_MODE_REG;               /*!< (@ 0x0000007C) P0_25 Mode Register                                        */
  __IOM uint32_t  P0_26_MODE_REG;               /*!< (@ 0x00000080) P0_26 Mode Register                                        */
  __IOM uint32_t  P0_27_MODE_REG;               /*!< (@ 0x00000084) P0_27 Mode Register                                        */
  __IOM uint32_t  P0_28_MODE_REG;               /*!< (@ 0x00000088) P0_28 Mode Register                                        */
  __IOM uint32_t  P0_29_MODE_REG;               /*!< (@ 0x0000008C) P0_29 Mode Register                                        */
  __IOM uint32_t  P0_30_MODE_REG;               /*!< (@ 0x00000090) P0_30 Mode Register                                        */
  __IOM uint32_t  P0_31_MODE_REG;               /*!< (@ 0x00000094) P0_31 Mode Register                                        */
  __IOM uint32_t  P1_00_MODE_REG;               /*!< (@ 0x00000098) P1_00 Mode Register                                        */
  __IOM uint32_t  P1_01_MODE_REG;               /*!< (@ 0x0000009C) P1_01 Mode Register                                        */
  __IOM uint32_t  P1_02_MODE_REG;               /*!< (@ 0x000000A0) P1_02 Mode Register                                        */
  __IOM uint32_t  P1_03_MODE_REG;               /*!< (@ 0x000000A4) P1_03 Mode Register                                        */
  __IOM uint32_t  P1_04_MODE_REG;               /*!< (@ 0x000000A8) P1_04 Mode Register                                        */
  __IOM uint32_t  P1_05_MODE_REG;               /*!< (@ 0x000000AC) P1_05 Mode Register                                        */
  __IOM uint32_t  P1_06_MODE_REG;               /*!< (@ 0x000000B0) P1_06 Mode Register                                        */
  __IOM uint32_t  P1_07_MODE_REG;               /*!< (@ 0x000000B4) P1_07 Mode Register                                        */
  __IOM uint32_t  P1_08_MODE_REG;               /*!< (@ 0x000000B8) P1_08 Mode Register                                        */
  __IOM uint32_t  P1_09_MODE_REG;               /*!< (@ 0x000000BC) P1_09 Mode Register                                        */
  __IOM uint32_t  P1_10_MODE_REG;               /*!< (@ 0x000000C0) P1_10 Mode Register                                        */
  __IOM uint32_t  P1_11_MODE_REG;               /*!< (@ 0x000000C4) P1_11 Mode Register                                        */
  __IOM uint32_t  P1_12_MODE_REG;               /*!< (@ 0x000000C8) P1_12 Mode Register                                        */
  __IOM uint32_t  P1_13_MODE_REG;               /*!< (@ 0x000000CC) P1_13 Mode Register                                        */
  __IOM uint32_t  P1_14_MODE_REG;               /*!< (@ 0x000000D0) P1_14 Mode Register                                        */
  __IOM uint32_t  P1_15_MODE_REG;               /*!< (@ 0x000000D4) P1_15 Mode Register                                        */
  __IOM uint32_t  P1_16_MODE_REG;               /*!< (@ 0x000000D8) P1_16 Mode Register                                        */
  __IOM uint32_t  P1_17_MODE_REG;               /*!< (@ 0x000000DC) P1_17 Mode Register                                        */
  __IOM uint32_t  P1_18_MODE_REG;               /*!< (@ 0x000000E0) P1_18 Mode Register                                        */
  __IOM uint32_t  P1_19_MODE_REG;               /*!< (@ 0x000000E4) P1_19 Mode Register                                        */
  __IOM uint32_t  P1_20_MODE_REG;               /*!< (@ 0x000000E8) P1_20 Mode Register                                        */
  __IOM uint32_t  P1_21_MODE_REG;               /*!< (@ 0x000000EC) P1_21 Mode Register                                        */
  __IOM uint32_t  P1_22_MODE_REG;               /*!< (@ 0x000000F0) P1_22 Mode Register                                        */
  __IOM uint32_t  P0_PADPWR_CTRL_REG;           /*!< (@ 0x000000F4) P0 Output Power Control Register                           */
  __IOM uint32_t  P1_PADPWR_CTRL_REG;           /*!< (@ 0x000000F8) P1 Output Power Control Register                           */
  __IOM uint32_t  GPIO_CLK_SEL_REG;             /*!< (@ 0x000000FC) Select which clock to map on ports P0/P1                   */
  __IOM uint32_t  PAD_WEAK_CTRL_REG;            /*!< (@ 0x00000100) Weak Pads Control Register                                 */
};

#endif /* _RENESAS_da1469X_REGS_H_ */