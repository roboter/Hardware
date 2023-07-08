################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/FreeRTOS/Portable/STM32F4xx/subdir.mk
-include Utilities/FreeRTOS/Memory/subdir.mk
-include Utilities/FreeRTOS/Core/subdir.mk
-include Utilities/FAT_FS/subdir.mk
-include Libraries/STemWin522/OS/subdir.mk
-include Libraries/STemWin522/Config/subdir.mk
-include Libraries/STM32_USB/Host/Core/subdir.mk
-include Libraries/STM32_USB/Host/Class/MSC/subdir.mk
-include Libraries/STM32_USB/Driver/subdir.mk
-include Libraries/STM32_USB/Device/Core/subdir.mk
-include Libraries/STM32_USB/Device/Class/HID/subdir.mk
-include Libraries/STM32F4xx_StdPeriph_Driver/subdir.mk
-include Libraries/STM32429I-DISCO/subdir.mk
-include Appli/Utils/subdir.mk
-include Appli/User/subdir.mk
-include Appli/Test/subdir.mk
-include Appli/Demo/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := STM32F429I-Discovery_Demo
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F429I-Discovery_Demo.elf \

MAP_FILES += \
STM32F429I-Discovery_Demo.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F429I-Discovery_Demo.list \


# All Target
all: main-build

# Main-build Target
main-build: STM32F429I-Discovery_Demo.elf secondary-outputs

# Tool invocations
STM32F429I-Discovery_Demo.elf STM32F429I-Discovery_Demo.map: $(OBJS) $(USER_OBJS) ../STM32F429ZI_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "STM32F429I-Discovery_Demo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../STM32F429ZI_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F429I-Discovery_Demo.map" -Wl,--gc-sections -static -L"../../../../../Libraries/STemWinLibrary522_4x9i/Lib" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F429I-Discovery_Demo.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F429I-Discovery_Demo.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) STM32F429I-Discovery_Demo.elf STM32F429I-Discovery_Demo.list STM32F429I-Discovery_Demo.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
