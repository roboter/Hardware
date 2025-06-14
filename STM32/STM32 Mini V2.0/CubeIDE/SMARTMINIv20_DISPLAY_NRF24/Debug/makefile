################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := SMARTMINIv20_DISPLAY_NRF24
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SMARTMINIv20_DISPLAY_NRF24.elf \

MAP_FILES += \
SMARTMINIv20_DISPLAY_NRF24.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SMARTMINIv20_DISPLAY_NRF24.list \


# All Target
all: main-build

# Main-build Target
main-build: SMARTMINIv20_DISPLAY_NRF24.elf secondary-outputs

# Tool invocations
SMARTMINIv20_DISPLAY_NRF24.elf SMARTMINIv20_DISPLAY_NRF24.map: $(OBJS) $(USER_OBJS) C:\Users\robby\STM32CubeIDE\workspace_1.18.0_new\SMARTMINIv20_DISPLAY_NRF24\STM32F103RCTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SMARTMINIv20_DISPLAY_NRF24.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\robby\STM32CubeIDE\workspace_1.18.0_new\SMARTMINIv20_DISPLAY_NRF24\STM32F103RCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SMARTMINIv20_DISPLAY_NRF24.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SMARTMINIv20_DISPLAY_NRF24.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SMARTMINIv20_DISPLAY_NRF24.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SMARTMINIv20_DISPLAY_NRF24.elf SMARTMINIv20_DISPLAY_NRF24.list SMARTMINIv20_DISPLAY_NRF24.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
