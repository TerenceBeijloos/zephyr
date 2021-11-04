# SPDX-License-Identifier: Apache-2.0

add_subdirectory_ifdef(CONFIG_CPU_CORTEX_M common/cortex_m)

message("soc family:")
message(${SOC_FAMILY})

message("soc name:")
message(${SOC_NAME})

if(SOC_FAMILY)
  add_subdirectory(${SOC_FAMILY})
else()
  add_subdirectory(${SOC_NAME})
endif()

