/**
  @page NETMF_Binary_Image
  
  @verbatim
  ******************** (C) COPYRIGHT 2013 STMicroelectronics *******************
  * @file    NETMF_Binary_Image/readme.txt 
  * @author  MCD
  * @version V1.0.0
  * @date    24-Sep-2013
  * @brief   Description of the NETMF_Binary_Image folder contents.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
   @endverbatim

@par Description 

Binary images of the user program
=================================
This folder contains the following binary images that should be loaded the STM32F429 Discovery:  
    - Tinybooter.hex : NETMF bootloader
    - ER_FLASH.hex   : CLR and HAL drivers
    - ER_CONFIG.hex  : NETMF configuration region
    
@par How to use it ? 

In order to load the NETMF binary image into STM32F429 Discovery, you should do the following:
 - Open ST-LINK Utility.
 - Load hex file: File->Open file... (Ctrl+O)
 - Program the hex file: Target->Program & Verify (Ctrl+P)
   
 * <h3><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h3>
 */
