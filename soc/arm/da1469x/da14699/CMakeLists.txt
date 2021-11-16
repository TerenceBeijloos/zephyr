# SPDX-License-Identifier: Apache-2.0

add_subdirectory(hw)
zephyr_include_directories(hw)

add_subdirectory(bsp)
zephyr_include_directories(bsp)

zephyr_sources(soc.c)
zephyr_sources(init_da1469x.c)
