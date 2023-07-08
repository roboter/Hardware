################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Libraries/STemWinLibrary522_4x9i/Config/GUIConf.c \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Libraries/STemWinLibrary522_4x9i/Config/GUIDRV_stm32f429i_discovery.c 

OBJS += \
./Libraries/STemWin522/Config/GUIConf.o \
./Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.o 

C_DEPS += \
./Libraries/STemWin522/Config/GUIConf.d \
./Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/STemWin522/Config/GUIConf.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Libraries/STemWinLibrary522_4x9i/Config/GUIConf.c Libraries/STemWin522/Config/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Libraries/STemWinLibrary522_4x9i/Config/GUIDRV_stm32f429i_discovery.c Libraries/STemWin522/Config/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Libraries-2f-STemWin522-2f-Config

clean-Libraries-2f-STemWin522-2f-Config:
	-$(RM) ./Libraries/STemWin522/Config/GUIConf.d ./Libraries/STemWin522/Config/GUIConf.o ./Libraries/STemWin522/Config/GUIConf.su ./Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.d ./Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.o ./Libraries/STemWin522/Config/GUIDRV_stm32f429i_discovery.su

.PHONY: clean-Libraries-2f-STemWin522-2f-Config

