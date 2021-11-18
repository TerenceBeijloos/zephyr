# SPDX-License-Identifier: Apache-2.0


    add_subdirectory(bsp)
add_subdirectory(middleware)

zephyr_sources(soc.c)

message("######################################\n\n${TOOLCHAIN_C_FLAGS}######################################\n\n")
# list(APPEND TOOLCHAIN_C_FLAGS
# -imacros${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/DA1469x_helper_defines.h
# )



# message("ZEPHYR BASE#####################################################" ${AUTOCONF_H})