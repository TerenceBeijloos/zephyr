add_subdirectory(${SOC_SERIES})

add_subdirectory(hal_da1469x)
zephyr_include_directories(hal_da1469x)

zephyr_compile_options("SHELL: $<TARGET_PROPERTY:compiler,imacros> ${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/bsp/config/custom_config_qspi.h")
zephyr_compile_options("SHELL: $<TARGET_PROPERTY:compiler,imacros> ${ZEPHYR_BASE}/soc/${ARCH}/${SOC_FAMILY}/${SOC_SERIES}/DA1469x_compiler_imacros.h")

