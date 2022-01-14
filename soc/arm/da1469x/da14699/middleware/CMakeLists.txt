# SPDX-License-Identifier: Apache-2.0

add_subdirectory(config)
zephyr_include_directories(config)

add_subdirectory(adapters/include)
add_subdirectory(adapters/src)
zephyr_include_directories(adapters/src)
zephyr_include_directories(adapters/include)

add_subdirectory(osal)
zephyr_include_directories(osal)