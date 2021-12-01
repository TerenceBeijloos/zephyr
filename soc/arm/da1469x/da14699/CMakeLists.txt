# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SOC_SERIES_DA1469X)
  zephyr_library()
  zephyr_library_sources(soc.c)
  zephyr_library_sources(vector_table_da1469x.S)
  zephyr_library_sources(deepsleep.S)
  zephyr_library_sources(exception_handlers.S)
  zephyr_library_sources(startup_da1469x.S)
  # zephyr_library_sources(da1469x_m33_sleep.S)
  # zephyr_library_sources(gcc_startup_da1469x.S)
endif()


add_subdirectory(bsp)
add_subdirectory(middleware)

# zephyr_sources(soc.c)
