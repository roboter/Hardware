################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/cpu_utils.c \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/file_utils.c \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/str_utils.c \
C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/time_utils.c 

OBJS += \
./Appli/Utils/cpu_utils.o \
./Appli/Utils/file_utils.o \
./Appli/Utils/str_utils.o \
./Appli/Utils/time_utils.o 

C_DEPS += \
./Appli/Utils/cpu_utils.d \
./Appli/Utils/file_utils.d \
./Appli/Utils/str_utils.d \
./Appli/Utils/time_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Appli/Utils/cpu_utils.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/cpu_utils.c Appli/Utils/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Appli/Utils/file_utils.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/file_utils.c Appli/Utils/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Appli/Utils/str_utils.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/str_utils.c Appli/Utils/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Appli/Utils/time_utils.o: C:/Users/roboter/Documents/GitHub/HardwareModules/STM32/STM32F429-Discovery/STM32F429I-Discovery_FW_V1.0.3/Projects/Demonstration/Core/Lib/time_utils.c Appli/Utils/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu99 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F429_439xx -DUSE_STM32F429I_DISCO -DUSE_STM32F429I_DISCO_REVC -DUSE_USB_OTG_HS -DUSE_EMBEDDED_PHY -c -I../../../Config -I../../../Core/Devices/STM32F4xx -I../../../Core/User -I../../../Core/Demo -I../../../Core/Lib -I../../../Core/Test_Program -I../../../../../Libraries/STM32_USB_HOST_Library/Core/inc -I../../../../../Libraries/STM32_USB_HOST_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Core/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/MSC/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/HID/inc -I../../../../../Libraries/STM32_USB_Device_Library/Class/Audio/inc -I../../../../../Libraries/STM32_USB_OTG_Driver/inc -I../../../../../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../../../../../Libraries/CMSIS/Include -I../../../../../Libraries/CMSIS/Device/ST/STM32F4xx/Include -I../../../../../Utilities -I../../../../../Utilities/Common -I../../../../../Utilities/STM32F429i-Discovery -I../../../../../Utilities/Third_Party/fat_fs/inc -I../../../../../Utilities/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../../../Utilities/Third_Party/FreeRTOS/Source/include -I../../../../../Libraries/STemWinLibrary522_4x9i/inc -I../../../../../Libraries/STemWinLibrary522_4x9i/Config -Ofast -ffunction-sections -fdata-sections -Wall -Wno-pointer-sign -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Appli-2f-Utils

clean-Appli-2f-Utils:
	-$(RM) ./Appli/Utils/cpu_utils.d ./Appli/Utils/cpu_utils.o ./Appli/Utils/cpu_utils.su ./Appli/Utils/file_utils.d ./Appli/Utils/file_utils.o ./Appli/Utils/file_utils.su ./Appli/Utils/str_utils.d ./Appli/Utils/str_utils.o ./Appli/Utils/str_utils.su ./Appli/Utils/time_utils.d ./Appli/Utils/time_utils.o ./Appli/Utils/time_utils.su

.PHONY: clean-Appli-2f-Utils
