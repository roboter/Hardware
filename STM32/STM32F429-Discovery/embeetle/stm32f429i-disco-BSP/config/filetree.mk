################################################################################
#                              MAKEFILE INCLUDES                               #
################################################################################
# COPYRIGHT (c) 2020 Embeetle                                                  #
# This software component is licensed by Embeetle under the MIT license. Con-  #
# sult the license text at the bottom of this file.                            #
#                                                                              #
#------------------------------------------------------------------------------#
#                                   SUMMARY                                    #
#------------------------------------------------------------------------------#
# This file should be included in the makefile. It lists all source files (c,  #
# c++, asm..) that take part in the compilation.                               #
#                                                                              #
# Take a look at the Embeetle filetree. All files with a green checkmark are   #
# the ones ending up here in this file. Embeetle attempts to list automatical- #
# ly the right set of files, starting from 'main.c'. However, you can manually #
# overrule the beetle's decisions by clicking the file's checkmark (turning it #
# red). Save the project (Ctrl+S) and observe the result in this file.         #
#                                                                              #
# We suggest to include this file in your makefile like so:                    #
#                                                                              #
#     MAKEFILE := $(lastword $(MAKEFILE_LIST))                                 #
#     MAKEFILE_DIR := $(dir $(MAKEFILE))                                       #
#     include $(MAKEFILE_DIR)filetree.mk                                       #
#                                                                              #
#------------------------------------------------------------------------------#
#                                    EDITS                                     #
#------------------------------------------------------------------------------#
# This file was automatically generated. Do not edit! It is overwritten regu-  #
# larly by Embeetle. Although Embeetle IDE practices the "treat config as      #
# code" principle, this file is an exception.                                  #
#                                                                              #
# If you want to force a certain source file to be in- or excluded from the    #
# build, just click the corresponding checkbox in the Embeetle Filetree and    #
# save the project. This file should adapt itself accordingly.                 #
#                                                                              #
#------------------------------------------------------------------------------#
#                               MORE INFORMATION                               #
#------------------------------------------------------------------------------#
# Consult the following pages on our website for more info about this file:    #
# https://embeetle.com/#embeetle-ide/manual/beetle-anatomy/file-tree           #
# https://embeetle.com/#embeetle-ide/manual/build/source-file-selection        #
#                                                                              #
# Read this comic if you want to have a good laugh:                            #
# https://embeetle.com/#comics/src_files_selection                             #
#                                                                              #
################################################################################

# VERSION:
EMBEETLE_MAKEFILE_INTERFACE_VERSION = 7

# INCLUDED CFILES:
C_OFILES = \
project/source/Drivers/BSP/Components/ili9341/ili9341.c.o \
project/source/Drivers/BSP/Components/l3gd20/l3gd20.c.o \
project/source/Drivers/BSP/Components/stmpe811/stmpe811.c.o \
project/source/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.c.o \
project/source/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_gyroscope.c.o \
project/source/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.c.o \
project/source/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_sdram.c.o \
project/source/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_ts.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma2d.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_ltdc.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_msp_template.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sdram.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c.o \
project/source/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fmc.c.o \
project/source/Utilities/Fonts/font12.c.o \
project/source/Utilities/Fonts/font16.c.o \
project/source/Utilities/Fonts/font20.c.o \
project/source/Utilities/Fonts/font24.c.o \
project/source/Utilities/Log/lcd_log.c.o \
project/source/user_code/lcd.c.o \
project/source/user_code/log.c.o \
project/source/user_code/main.c.o \
project/source/user_code/mems.c.o \
project/source/user_code/stm32f4xx_it.c.o \
project/source/user_code/system_stm32f4xx.c.o \
project/source/user_code/touchscreen.c.o \
project/source/user_code/ts_calibration.c.o

# INCLUDED CXXFILES:
CXX_OFILES =

# INCLUDED SFILES:
S_OFILES = \
project/source/startup_stm32f429xx.s.o

# LIST ALL OFILES:
OFILES = $(C_OFILES) $(CXX_OFILES) $(S_OFILES)

# INCLUDED HDIRS:
HDIR_FLAGS = \
-I$(SOURCE_DIR)source/Drivers/BSP/Components/ili9341 \
-I$(SOURCE_DIR)source/Drivers/BSP/Components/l3gd20 \
-I$(SOURCE_DIR)source/Drivers/BSP/Components/stmpe811 \
-I$(SOURCE_DIR)source/Drivers/BSP/STM32F429I-Discovery \
-I$(SOURCE_DIR)source/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
-I$(SOURCE_DIR)source/Drivers/CMSIS/Include \
-I$(SOURCE_DIR)source/Drivers/STM32F4xx_HAL_Driver/Inc \
-I$(SOURCE_DIR)source/Inc \
-I$(SOURCE_DIR)source/Utilities/Fonts \
-I$(SOURCE_DIR)source/Utilities/Log

# INCLUDED ARCHIVES
PROJECT_LDLIBS =

# MIT LICENSE
# ===========
# COPYRIGHT (c) 2020 Embeetle
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
