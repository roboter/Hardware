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

CFG = default

################################################################################
#                                [cfg: default]                                #
################################################################################
ifeq ($(CFG),default)
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
  TOOLPREFIX = arm-none-eabi-
  FLASHTOOL = openocd
  
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
  ELF_FILE = application.elf
  SOURCE_DIR = ../
  LINKERSCRIPT = ../config/linkerscript.ld
  OPENOCD_CHIPFILE = ../config/openocd_chip.cfg
  OPENOCD_PROBEFILE = ../config/openocd_probe.cfg
  
  # 4. BINARIES
  # ===========
  # Define the binaries that must be built.
  BINARIES = \
    $(ELF_FILE) \
    $(ELF_FILE:.elf=.bin) \
    $(ELF_FILE:.elf=.hex) \
  # Define the rules to build these binaries from the .elf file.
  %.bin: %.elf
	$(info )
	$(info )
	$(info Preparing: $@)
	$(OBJCOPY) -O binary $< $@
  
  %.hex: %.elf
	$(info )
	$(info )
	$(info Preparing: $@)
	$(OBJCOPY) -O ihex $< $@
  
  # 5. COMPILATION FLAGS
  # ====================
  # CPU specific flags for C++, C and assembly compilation and linking.
  TARGET_COMMONFLAGS = -mfpu=fpv4-sp-d16 \
                       -mfloat-abi=hard \
                       -mcpu=cortex-m4 \
                       -mthumb \
                       -DARM_MATH_CM4 \
  
  # CPU specific C compilation flags
  TARGET_CFLAGS = -D__packed="__attribute__((__packed__))" \
                  -D__weak="__attribute__((weak))" \
                  -DUSE_HAL_DRIVER \
                  -DSTM32F303x8 \
  
  # CPU specific C++ compilation flags
  TARGET_CXXFLAGS = -D__packed="__attribute__((__packed__))" \
                    -D__weak="__attribute__((weak))" \
                    -DUSE_HAL_DRIVER \
                    -DSTM32F303x8 \
  
  # CPU specific assembler flags
  TARGET_SFLAGS = -D__packed="__attribute__((__packed__))" \
                  -D__weak="__attribute__((weak))" \
  
  # CPU specific linker flags
  TARGET_LDFLAGS = --specs=nano.specs \
                   --specs=nosys.specs \
                   -T $(LINKERSCRIPT) \
                   -L $(dir $(LINKERSCRIPT)) \
  
  # Libraries from the toolchain
  TOOLCHAIN_LDLIBS = -lm \
  
  # NOTE:
  # The -DARM_MATH_XX flag can be:
  #     ARM_MATH_CM7
  #     ARM_MATH_CM4
  #     ARM_MATH_CM3
  #     ARM_MATH_CM0PLUS
  #     ARM_MATH_CM0
  #     ARM_MATH_ARMV8MBL
  #     ARM_MATH_ARMV8MML
  
  # 6. FLASH RULES
  # ==============
  # The 'flash' target flashes the binary to the target microcontroller. To
  # achieve this, it invokes the OpenOCD tool:
  .PHONY: flash
  flash: $(BINARIES) print_flash
	"$(FLASHTOOL)" -f $(OPENOCD_PROBEFILE)\
                 -f $(OPENOCD_CHIPFILE)\
                 -c "program {$(ELF_FILE)} verify reset; shutdown;"
  
  # Let's figure out what the flags mean:
  #
  #   -f: Specify a config file for OpenOCD to use. We pass this flag
  #       twice: once for the config file that defines the probe and
  #       once to define the chip (microcontroller).
  #
  #   -c: Run the specified commands. The ones we pass are:
  #         1) program {file} verify reset;
  #            Upload the firmware to the flash memory and verify
  #            if it was successful.
  #         2) shutdown;
  #            Quit OpenOCD.
endif

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