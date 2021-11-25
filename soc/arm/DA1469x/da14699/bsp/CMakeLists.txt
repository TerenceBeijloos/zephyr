# SPDX-License-Identifier: Apache-2.0
add_subdirectory(peripherals/src)
add_subdirectory(peripherals/include)
zephyr_include_directories(peripherals/include)

add_subdirectory(include)
zephyr_include_directories(include)

add_subdirectory(config)
zephyr_include_directories(config)

add_subdirectory(memory/include)
add_subdirectory(memory/src)
zephyr_include_directories(memory/include)

add_subdirectory(system/sys_man)
add_subdirectory(system/sys_man/include)
zephyr_include_directories(system/sys_man/include)

add_subdirectory(startup/DA1469x)

add_subdirectory(snc/include)
zephyr_include_directories(snc/include)