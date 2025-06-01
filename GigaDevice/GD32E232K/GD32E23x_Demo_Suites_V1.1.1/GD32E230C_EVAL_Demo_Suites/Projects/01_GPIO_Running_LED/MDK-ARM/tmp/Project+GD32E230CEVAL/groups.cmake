# groups.cmake

# group Application
add_library(Group_Application OBJECT
  "${SOLUTION_ROOT}/../main.c"
  "${SOLUTION_ROOT}/../systick.c"
  "${SOLUTION_ROOT}/../gd32e23x_it.c"
)
target_include_directories(Group_Application PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Application PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Application_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Application_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Application PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Application PUBLIC
  Group_Application_ABSTRACTIONS
)

# group CMSIS
add_library(Group_CMSIS OBJECT
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Source/system_gd32e23x.c"
)
target_include_directories(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_CMSIS_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_CMSIS_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_CMSIS PUBLIC
  Group_CMSIS_ABSTRACTIONS
)

# group GD32E23x_Peripherals
add_library(Group_GD32E23x_Peripherals OBJECT
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_adc.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_cmp.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_crc.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_dbg.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_dma.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_exti.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_fmc.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_fwdgt.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_gpio.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_i2c.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_misc.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_pmu.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_rcu.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_rtc.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_spi.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_syscfg.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_timer.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_usart.c"
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c"
)
target_include_directories(Group_GD32E23x_Peripherals PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_GD32E23x_Peripherals PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_GD32E23x_Peripherals_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_GD32E23x_Peripherals_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_GD32E23x_Peripherals PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_GD32E23x_Peripherals PUBLIC
  Group_GD32E23x_Peripherals_ABSTRACTIONS
)

# group GD32E230_EVAL
add_library(Group_GD32E230_EVAL OBJECT
  "${SOLUTION_ROOT}/../../../Utilities/gd32e230c_eval.c"
)
target_include_directories(Group_GD32E230_EVAL PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_GD32E230_EVAL PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_GD32E230_EVAL_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_GD32E230_EVAL_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_GD32E230_EVAL PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_GD32E230_EVAL PUBLIC
  Group_GD32E230_EVAL_ABSTRACTIONS
)

# group Startup
add_library(Group_Startup OBJECT
  "${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Source/ARM/startup_gd32e23x.s"
)
target_include_directories(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
add_library(Group_Startup_ABSTRACTIONS INTERFACE)
target_link_libraries(Group_Startup_ABSTRACTIONS INTERFACE
  ${CONTEXT}_ABSTRACTIONS
)
target_compile_options(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Startup PUBLIC
  Group_Startup_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  GD32E23x
  _RTE_
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Source/ARM/startup_gd32e23x.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set_source_files_properties("${SOLUTION_ROOT}/../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Source/ARM/startup_gd32e23x.s" PROPERTIES
  COMPILE_OPTIONS "-masm=auto"
)
