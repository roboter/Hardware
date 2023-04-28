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
project/source/components/ble/ble_advertising/ble_advertising.c.o \
project/source/components/ble/ble_db_discovery/ble_db_discovery.c.o \
project/source/components/ble/ble_dtm/ble_dtm.c.o \
project/source/components/ble/ble_dtm/ble_dtm_hw_nrf51.c.o \
project/source/components/ble/ble_dtm/ble_dtm_hw_nrf52.c.o \
project/source/components/ble/ble_link_ctx_manager/ble_link_ctx_manager.c.o \
project/source/components/ble/ble_racp/ble_racp.c.o \
project/source/components/ble/ble_radio_notification/ble_radio_notification.c.o \
project/source/components/ble/ble_services/ble_ancs_c/ancs_app_attr_get.c.o \
project/source/components/ble/ble_services/ble_ancs_c/ancs_attr_parser.c.o \
project/source/components/ble/ble_services/ble_ancs_c/nrf_ble_ancs_c.c.o \
project/source/components/ble/ble_services/ble_ans_c/ble_ans_c.c.o \
project/source/components/ble/ble_services/ble_bas/ble_bas.c.o \
project/source/components/ble/ble_services/ble_bas_c/ble_bas_c.c.o \
project/source/components/ble/ble_services/ble_bps/ble_bps.c.o \
project/source/components/ble/ble_services/ble_cscs/ble_cscs.c.o \
project/source/components/ble/ble_services/ble_cscs/ble_sc_ctrlpt.c.o \
project/source/components/ble/ble_services/ble_cts_c/ble_cts_c.c.o \
project/source/components/ble/ble_services/ble_dfu/ble_dfu.c.o \
project/source/components/ble/ble_services/ble_dfu/ble_dfu_bonded.c.o \
project/source/components/ble/ble_services/ble_dfu/ble_dfu_unbonded.c.o \
project/source/components/ble/ble_services/ble_dis/ble_dis.c.o \
project/source/components/ble/ble_services/ble_dis_c/ble_dis_c.c.o \
project/source/components/ble/ble_services/ble_escs/nrf_ble_escs.c.o \
project/source/components/ble/ble_services/ble_gls/ble_gls.c.o \
project/source/components/ble/ble_services/ble_gls/ble_gls_db.c.o \
project/source/components/ble/ble_services/ble_hids/ble_hids.c.o \
project/source/components/ble/ble_services/ble_hrs/ble_hrs.c.o \
project/source/components/ble/ble_services/ble_hrs_c/ble_hrs_c.c.o \
project/source/components/ble/ble_services/ble_hts/ble_hts.c.o \
project/source/components/ble/ble_services/ble_ias/ble_ias.c.o \
project/source/components/ble/ble_services/ble_ias_c/ble_ias_c.c.o \
project/source/components/ble/ble_services/ble_ipsp/ble_ipsp.c.o \
project/source/components/ble/ble_services/ble_lbs/ble_lbs.c.o \
project/source/components/ble/ble_services/ble_lbs_c/ble_lbs_c.c.o \
project/source/components/ble/ble_services/ble_lls/ble_lls.c.o \
project/source/components/ble/ble_services/ble_nus/ble_nus.c.o \
project/source/components/ble/ble_services/ble_nus_c/ble_nus_c.c.o \
project/source/components/ble/ble_services/ble_rscs/ble_rscs.c.o \
project/source/components/ble/ble_services/ble_rscs_c/ble_rscs_c.c.o \
project/source/components/ble/ble_services/ble_tps/ble_tps.c.o \
project/source/components/ble/ble_services/eddystone/es_adv.c.o \
project/source/components/ble/ble_services/eddystone/es_adv_frame.c.o \
project/source/components/ble/ble_services/eddystone/es_adv_timing.c.o \
project/source/components/ble/ble_services/eddystone/es_adv_timing_resolver.c.o \
project/source/components/ble/ble_services/eddystone/es_battery_voltage_saadc.c.o \
project/source/components/ble/ble_services/eddystone/es_flash.c.o \
project/source/components/ble/ble_services/eddystone/es_gatts.c.o \
project/source/components/ble/ble_services/eddystone/es_gatts_read.c.o \
project/source/components/ble/ble_services/eddystone/es_gatts_write.c.o \
project/source/components/ble/ble_services/eddystone/es_security.c.o \
project/source/components/ble/ble_services/eddystone/es_slot.c.o \
project/source/components/ble/ble_services/eddystone/es_slot_reg.c.o \
project/source/components/ble/ble_services/eddystone/es_stopwatch.c.o \
project/source/components/ble/ble_services/eddystone/es_tlm.c.o \
project/source/components/ble/ble_services/eddystone/nrf_ble_es.c.o \
project/source/components/ble/ble_services/experimental_ble_lns/ble_ln_cp.c.o \
project/source/components/ble/ble_services/experimental_ble_lns/ble_ln_db.c.o \
project/source/components/ble/ble_services/experimental_ble_lns/ble_lns.c.o \
project/source/components/ble/ble_services/experimental_ble_ots/ble_ots.c.o \
project/source/components/ble/ble_services/experimental_ble_ots/ble_ots_l2cap.c.o \
project/source/components/ble/ble_services/experimental_ble_ots/ble_ots_oacp.c.o \
project/source/components/ble/ble_services/experimental_ble_ots/ble_ots_object.c.o \
project/source/components/ble/ble_services/experimental_gatts_c/nrf_ble_gatts_c.c.o \
project/source/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_db.c.o \
project/source/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_meas.c.o \
project/source/external/mbedtls/programs/wince_main.c.o \
project/source/modules/nrfx/mdk/system_nrf52833.c.o \
project/source/projects/ble_peripheral/ble_app_tester/main.c.o

# INCLUDED CXXFILES:
CXX_OFILES =

# INCLUDED SFILES:
S_OFILES = \
project/source/modules/nrfx/mdk/gcc_startup_nrf52833.S.o

# LIST ALL OFILES:
OFILES = $(C_OFILES) $(CXX_OFILES) $(S_OFILES)

# INCLUDED HDIRS:
HDIR_FLAGS =

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
