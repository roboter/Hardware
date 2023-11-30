################################################################################
#                              MAKEFILE INCLUDES                               #
################################################################################
# COPYRIGHT (c) 2023 Embeetle                                                  #
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
project/source/HAL_Driver/Src/stm32f7xx_hal.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_cortex.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_dma.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_gpio.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_i2c.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_ltdc.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_pwr_ex.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_rcc.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_rcc_ex.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_sdram.c.o \
project/source/HAL_Driver/Src/stm32f7xx_hal_uart.c.o \
project/source/HAL_Driver/Src/stm32f7xx_ll_fmc.c.o \
project/source/Utilities/Components/ft5336/ft5336.c.o \
project/source/Utilities/STM32746G-Discovery/stm32746g_discovery.c.o \
project/source/Utilities/STM32746G-Discovery/stm32746g_discovery_sdram.c.o \
project/source/Utilities/STM32746G-Discovery/stm32746g_discovery_ts.c.o \
project/source/hal_stm_lvgl/tft/tft.c.o \
project/source/hal_stm_lvgl/touchpad/touchpad.c.o \
project/source/lvgl/demos/music/lv_demo_music_main.c.o \
project/source/lvgl/demos/widgets/assets/img_clothes.c.o \
project/source/lvgl/demos/widgets/assets/img_demo_widgets_avatar.c.o \
project/source/lvgl/demos/widgets/assets/img_lvgl_logo.c.o \
project/source/lvgl/demos/widgets/lv_demo_widgets.c.o \
project/source/lvgl/src/core/lv_disp.c.o \
project/source/lvgl/src/core/lv_event.c.o \
project/source/lvgl/src/core/lv_group.c.o \
project/source/lvgl/src/core/lv_indev.c.o \
project/source/lvgl/src/core/lv_indev_scroll.c.o \
project/source/lvgl/src/core/lv_obj.c.o \
project/source/lvgl/src/core/lv_obj_class.c.o \
project/source/lvgl/src/core/lv_obj_draw.c.o \
project/source/lvgl/src/core/lv_obj_pos.c.o \
project/source/lvgl/src/core/lv_obj_scroll.c.o \
project/source/lvgl/src/core/lv_obj_style.c.o \
project/source/lvgl/src/core/lv_obj_style_gen.c.o \
project/source/lvgl/src/core/lv_obj_tree.c.o \
project/source/lvgl/src/core/lv_refr.c.o \
project/source/lvgl/src/core/lv_theme.c.o \
project/source/lvgl/src/draw/lv_draw.c.o \
project/source/lvgl/src/draw/lv_draw_arc.c.o \
project/source/lvgl/src/draw/lv_draw_img.c.o \
project/source/lvgl/src/draw/lv_draw_label.c.o \
project/source/lvgl/src/draw/lv_draw_line.c.o \
project/source/lvgl/src/draw/lv_draw_mask.c.o \
project/source/lvgl/src/draw/lv_draw_rect.c.o \
project/source/lvgl/src/draw/lv_img_buf.c.o \
project/source/lvgl/src/draw/lv_img_cache.c.o \
project/source/lvgl/src/draw/lv_img_decoder.c.o \
project/source/lvgl/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_arc.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_blend.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_gradient.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_img.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_letter.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_line.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_polygon.c.o \
project/source/lvgl/src/draw/sw/lv_draw_sw_rect.c.o \
project/source/lvgl/src/extra/layouts/flex/lv_flex.c.o \
project/source/lvgl/src/extra/layouts/grid/lv_grid.c.o \
project/source/lvgl/src/extra/lv_extra.c.o \
project/source/lvgl/src/extra/themes/default/lv_theme_default.c.o \
project/source/lvgl/src/extra/widgets/calendar/lv_calendar.c.o \
project/source/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c.o \
project/source/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c.o \
project/source/lvgl/src/extra/widgets/chart/lv_chart.c.o \
project/source/lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c.o \
project/source/lvgl/src/extra/widgets/keyboard/lv_keyboard.c.o \
project/source/lvgl/src/extra/widgets/led/lv_led.c.o \
project/source/lvgl/src/extra/widgets/list/lv_list.c.o \
project/source/lvgl/src/extra/widgets/menu/lv_menu.c.o \
project/source/lvgl/src/extra/widgets/meter/lv_meter.c.o \
project/source/lvgl/src/extra/widgets/msgbox/lv_msgbox.c.o \
project/source/lvgl/src/extra/widgets/spinbox/lv_spinbox.c.o \
project/source/lvgl/src/extra/widgets/spinner/lv_spinner.c.o \
project/source/lvgl/src/extra/widgets/tabview/lv_tabview.c.o \
project/source/lvgl/src/extra/widgets/tileview/lv_tileview.c.o \
project/source/lvgl/src/extra/widgets/win/lv_win.c.o \
project/source/lvgl/src/font/lv_font.c.o \
project/source/lvgl/src/font/lv_font_fmt_txt.c.o \
project/source/lvgl/src/font/lv_font_montserrat_12.c.o \
project/source/lvgl/src/font/lv_font_montserrat_14.c.o \
project/source/lvgl/src/font/lv_font_montserrat_16.c.o \
project/source/lvgl/src/hal/lv_hal_disp.c.o \
project/source/lvgl/src/hal/lv_hal_indev.c.o \
project/source/lvgl/src/hal/lv_hal_tick.c.o \
project/source/lvgl/src/misc/lv_anim.c.o \
project/source/lvgl/src/misc/lv_area.c.o \
project/source/lvgl/src/misc/lv_async.c.o \
project/source/lvgl/src/misc/lv_color.c.o \
project/source/lvgl/src/misc/lv_fs.c.o \
project/source/lvgl/src/misc/lv_gc.c.o \
project/source/lvgl/src/misc/lv_ll.c.o \
project/source/lvgl/src/misc/lv_math.c.o \
project/source/lvgl/src/misc/lv_mem.c.o \
project/source/lvgl/src/misc/lv_printf.c.o \
project/source/lvgl/src/misc/lv_style.c.o \
project/source/lvgl/src/misc/lv_style_gen.c.o \
project/source/lvgl/src/misc/lv_timer.c.o \
project/source/lvgl/src/misc/lv_tlsf.c.o \
project/source/lvgl/src/misc/lv_txt.c.o \
project/source/lvgl/src/misc/lv_utils.c.o \
project/source/lvgl/src/widgets/lv_arc.c.o \
project/source/lvgl/src/widgets/lv_bar.c.o \
project/source/lvgl/src/widgets/lv_btn.c.o \
project/source/lvgl/src/widgets/lv_btnmatrix.c.o \
project/source/lvgl/src/widgets/lv_checkbox.c.o \
project/source/lvgl/src/widgets/lv_dropdown.c.o \
project/source/lvgl/src/widgets/lv_img.c.o \
project/source/lvgl/src/widgets/lv_label.c.o \
project/source/lvgl/src/widgets/lv_line.c.o \
project/source/lvgl/src/widgets/lv_roller.c.o \
project/source/lvgl/src/widgets/lv_slider.c.o \
project/source/lvgl/src/widgets/lv_switch.c.o \
project/source/lvgl/src/widgets/lv_table.c.o \
project/source/lvgl/src/widgets/lv_textarea.c.o \
project/source/startup/sysmem.c.o \
project/source/user_code/main.c.o \
project/source/user_code/stm32f7xx_it.c.o \
project/source/user_code/syscalls.c.o \
project/source/user_code/system_stm32f7xx.c.o

# INCLUDED CXXFILES:
CXX_OFILES =

# INCLUDED SFILES:
S_OFILES = \
project/source/startup/startup_stm32f746xx.s.o

# LIST ALL OFILES:
OFILES = $(C_OFILES) $(CXX_OFILES) $(S_OFILES)

# INCLUDED HDIRS:
HDIR_FLAGS = \
-I$(SOURCE_DIR)source \
-I$(SOURCE_DIR)source/CMSIS/core \
-I$(SOURCE_DIR)source/CMSIS/device \
-I$(SOURCE_DIR)source/HAL_Driver/Inc \
-I$(SOURCE_DIR)source/Utilities/Components \
-I$(SOURCE_DIR)source/Utilities/Components/ft5336 \
-I$(SOURCE_DIR)source/Utilities/STM32746G-Discovery \
-I$(SOURCE_DIR)source/lvgl \
-I$(SOURCE_DIR)source/lvgl/demos \
-I$(SOURCE_DIR)source/lvgl/src \
-I$(SOURCE_DIR)source/lvgl/src/core \
-I$(SOURCE_DIR)source/lvgl/src/draw \
-I$(SOURCE_DIR)source/lvgl/src/draw/sdl \
-I$(SOURCE_DIR)source/lvgl/src/draw/stm32_dma2d \
-I$(SOURCE_DIR)source/lvgl/src/draw/sw \
-I$(SOURCE_DIR)source/lvgl/src/extra/layouts \
-I$(SOURCE_DIR)source/lvgl/src/extra/layouts/flex \
-I$(SOURCE_DIR)source/lvgl/src/extra/themes/default \
-I$(SOURCE_DIR)source/lvgl/src/font \
-I$(SOURCE_DIR)source/lvgl/src/hal \
-I$(SOURCE_DIR)source/lvgl/src/misc \
-I$(SOURCE_DIR)source/lvgl/src/widgets

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