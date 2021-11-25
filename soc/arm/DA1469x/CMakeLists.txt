add_subdirectory(${SOC_SERIES})
zephyr_compile_options("SHELL: $<TARGET_PROPERTY:compiler,imacros> ${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/bsp/config/custom_config_qspi.h")
zephyr_compile_options("SHELL: $<TARGET_PROPERTY:compiler,imacros> ${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/DA1469x_helper_defines.h")
# zephyr_compile_options("SHELL: $<TARGET_PROPERTY:compiler,imacros> ${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/bsp/include/sdk_defs.h")

# list(APPEND TOOLCHAIN_C_FLAGS
#     -imacros${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/bsp/system/loaders/uartboot/config/custom_config.h
#     )
# zephyr_include_directories(${SOC_SERIES})
