# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SOC_SERIES_DA1469X)
  zephyr_library()
  zephyr_library_sources(soc.c)
endif()


add_subdirectory(bsp)
add_subdirectory(middleware)
