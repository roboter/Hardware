# Makefile for STM32H750 LED Project

# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Target
TARGET = STM32H750_LED
MCU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT_ABI = -mfloat-abi=hard
THUMB = -mthumb

# Compiler flags
CFLAGS = $(MCU) $(FPU) $(FLOAT_ABI) $(THUMB) -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx
CFLAGS += -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage
CFLAGS += -MMD -MP --specs=nano.specs

# Include paths
INCLUDES = -I./Core/Inc \
           -I./Drivers/STM32H7xx_HAL_Driver/Inc \
           -I./Drivers/STM32H7xx_HAL_Driver/Inc/Legacy \
           -I./Drivers/CMSIS/Device/ST/STM32H7xx/Include \
           -I./Drivers/CMSIS/Include

# Source files
C_SOURCES = $(wildcard Core/Src/*.c) \
            $(wildcard Drivers/STM32H7xx_HAL_Driver/Src/*.c)

# Object files
OBJECTS = $(C_SOURCES:.c=.o)

# Linker script
LDSCRIPT = STM32H750VBTX_FLASH.ld

# Linker flags
LDFLAGS = $(MCU) $(FPU) $(FLOAT_ABI) $(THUMB) -T$(LDSCRIPT) --specs=nano.specs
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections

# Default target
all: $(TARGET).elf

# Compile C files
%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link
$(TARGET).elf: $(OBJECTS)
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o $@ $(OBJECTS)
	@$(SIZE) $@

# Clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(TARGET).elf $(TARGET).map

.PHONY: all clean 