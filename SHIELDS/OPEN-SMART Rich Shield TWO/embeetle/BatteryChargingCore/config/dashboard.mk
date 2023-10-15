################################################################################
#                                 DASHBOARD.MK                                 #
################################################################################
# COPYRIGHT (c) 2020 Embeetle                                                  #
# This software component is licensed by Embeetle under the MIT license. Con-  #
# sult the license text at the bottom of this file.                            #
#                                                                              #
#------------------------------------------------------------------------------#
#                                   SUMMARY                                    #
#------------------------------------------------------------------------------#
# This file is intended to be included in the makefile. It contains all        #
# variables that depend on dashboard settings in Embeetle.                     #
#                                                                              #
# We suggest to include this file in your makefile like so:                    #
#                                                                              #
#     MAKEFILE := $(lastword $(MAKEFILE_LIST))                                 #
#     MAKEFILE_DIR := $(dir $(MAKEFILE))                                       #
#     include $(MAKEFILE_DIR)dashboard.mk                                      #
#                                                                              #
#------------------------------------------------------------------------------#
#                                    EDITS                                     #
#------------------------------------------------------------------------------#
# This file was automatically generated, but feel free to edit. When you chan- #
# ge something in the dashboard, Embeetle will ask your permission to modify   #
# this file accordingly. You'll be shown a proposal for a 3-way-merge in a     #
# diffing window. In other words, your manual edits won't be lost.             #
#                                                                              #
#------------------------------------------------------------------------------#
#                               MORE INFORMATION                               #
#------------------------------------------------------------------------------#
# Consult the Embeetle website for more info about this file:                  #
# https://embeetle.com/#embeetle-ide/manual/beetle-anatomy/dashboard           #
#                                                                              #
################################################################################

# 1. VERSION
# ==========
# Define the makefile interface version this 'dashboard.mk' file must be com-
# patible with.
EMBEETLE_MAKEFILE_INTERFACE_VERSION = 7

# 2. TOOLS
# ========
# When invoking the makefile, Embeetle passes absolute paths to the toolchain
# (ARM, RISCV, ...) and the flash tool (OpenOCD, esptool, ...) on the command-
# line.
# Example:
#
#   > "TOOLPREFIX=C:/my_tools/gnu_arm_toolchain_9.2.1/bin/arm-none-eabi-"
#   > "FLASHTOOL=C:/my_tools/openocd_0.10.0_dev01138_32b/bin/openocd.exe"
#
# If you ever invoke the makefile without these commandline-arguments,
# you need a fallback mechanism. Therefore, we provide a default value
# for these variables here. Read more about the reasons in ADDENDUM 2.
TOOLPREFIX = avr-
FLASHTOOL = avrdude

# 3. PROJECT LAYOUT
# =================
# The PROJECT LAYOUT section in the dashboard points to all important config
# file locations (eg. linkerscript, openocd config files, ...). If you change
# any of those locations in the dashboard, Embeetle changes the variables be-
# low accordingly.
#
# NOTES:
#     - These paths are all relative to the build directory.
#     - Locations of 'dashboard.mk' and 'filetree.mk' are not
#       defined here. That's because they're always located in
#       the same folder with the makefile.
SOURCE_DIR = ../
BIN_FILE = application.bin
ELF_FILE = application.elf
LINKERSCRIPT = ../config/linkerscript.ld

# 4. BINARIES
# ===========
# Define the binaries that must be built.
BINARIES = \
  $(ELF_FILE) \
  $(ELF_FILE:.elf=.bin) \
  $(ELF_FILE:.elf=.hex) \
  $(ELF_FILE:.elf=.eep)

# Define the rules to build these binaries from the .elf file.
%.bin: %.elf
	$(info )
	$(info )
	$(info Preparing: $@)
	$(OBJCOPY) -O binary $< $@

%.hex: %.elf %.eep
	$(info )
	$(info )
	$(info Preparing: $@)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.eep: %.elf
	$(info )
	$(info )
	$(info Preparing: $@)
	$(OBJCOPY) -O ihex \
             -j .eeprom \
             --set-section-flags=.eeprom=alloc,load \
             --no-change-warnings \
             --change-section-lma .eeprom=0 \
             $< $@

# 5. COMPILATION FLAGS
# ====================
# CPU specific flags for C++, C and assembly compilation and linking.
TARGET_COMMONFLAGS = -mmcu=atmega328p \
                     -flto \
                     -DF_CPU=16000000L \
                     -DARDUINO=10813 \
                     -DARDUINO_ARCH_AVR \
                     -DARDUINO_AVR_UNO \

# CPU specific C compilation flags
TARGET_CFLAGS = -std=gnu11 \
                -fno-fat-lto-objects \

# CPU specific C++ compilation flags
TARGET_CXXFLAGS = -std=gnu++11 \
                  -fpermissive \
                  -fno-exceptions \
                  -fno-threadsafe-statics \
                  -Wno-error=narrowing \

# CPU specific assembler flags
TARGET_SFLAGS = -x assembler-with-cpp \

# CPU specific linker flags
TARGET_LDFLAGS = -fuse-linker-plugin \
                 -T $(LINKERSCRIPT) \
                 -L $(dir $(LINKERSCRIPT)) \

# Libraries from the toolchain
TOOLCHAIN_LDLIBS = -lm \

# 6. FLASH RULES
# ==============
# The 'flash' target flashes the .hex file to the target microcontroller. To
# achieve this it invokes the 'avrdude' program, pointed to by the FLASHTOOL
# variable (defined at the top of this file), and provides the right parame-
# ters to launch avrdude properly.
#
# NOTE: To function properly, avrdude needs the 'avrdude.conf' file, which is in-
#       side the avrdude installation folder. Before avrdude v6.99.0, avrdude was
#       unable to locate this file by itself. You then had to provide the absolute
#       path to the file with the '-C' argument, or copy the file to some location
#       location in your $USER directory. Make sure your avrdude version is higher
#       than v6.99.0 such that it just works.

# Back to the flash-procedure. The flash-rule defined below launches avrdude
# and instructs it to flash the firmware through a Serial Port. It will only
# work if your microcontroller has a bootloader! Arduino boards are shipped with
# such a bootloader pre-installed. If your chip has no bootloader yet, or it is
# corrupted, you need to flash it again. Select a probe in the dashboard (eg. AVR
# ISP mkII or Atmel ICE) to do that.
.PHONY: flash
flash: $(BINARIES) print_flash
	"$(FLASHTOOL)" -v \
               -patmega328p \
               -carduino \
               -P$(FLASH_PORT) \
               -b115200 \
               -D \
               -Uflash:w:$(ELF_FILE:.elf=.hex):i

# Let's examine these flags one-by-one:
#
#   -v                  Enable verbose output.
#
#   -p <partno>         Specify what type of part (MCU) that is connected to
#                       the programmer.
#
#   -c <programmer-id>  Specify the programmer to be used.
#
#   -P <port>           Identify the device to which the programmer is attach-
#                       ed. We use this parameter to define the Flash Port
#                       (Serial Port), which should be passed on the commandline
#                       when invoking gnu make.
#
#   -b <baudrate>       Override the RS-232 connection baud rate specified in
#                       the respective programmer's entry of the configuration
#                       file.
#
#   -D                  Disable auto erase for flash.
#
#   -e                  Erase chip before programming.
#
#
#   -U <memtype>:<op>:<filename>:<format>   Perform a memory operation.
#
#                       <memtype>  specifies the memory type to operate on,
#                                  such as 'flash', 'eeprom', 'fuse', 'lock',
#                                  ...
#
#                       <op>       specifies what operation to perform, such
#                                  as 'r' for read, 'w' for write and 'v' for
#                                  verify.
#
#                       <filename> indicates the name of the file to read or
#                                  write.
#
#                       <format>   contains the format of the file to read or
#                                  write, such as 'i' for Intel Hex, 's' for
#                                  Motorola S-record, 'r' for raw binary, 'e'
#                                  for elf and 'a' for autodetect.


# ADDENDUM 1. MIT LICENSE
# =======================
# Copyright (c) 2020 Embeetle
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is furn-
# ished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# ADDENDUM 2. WHY THE FALLBACK MECHANISM FOR TOOLS?
# =================================================
# You might wonder: why bother with a default value? Embeetle could simply
# insert the actual paths (as selected in the dashboard) here, like:
#
# TOOLPREFIX = C:/my_tools/gnu_arm_toolchain_9.2.1/bin/arm-none-eabi-
# FLASHTOOL  = C:/my_tools/openocd_0.10.0_dev01138_32b/bin/openocd.exe
#
# However, that would make this dashboard.mk file location dependent: the
# location of the tool would be hardcoded. That's a problem if you access
# this project from two computers where the same tool is stored in different
# locations.