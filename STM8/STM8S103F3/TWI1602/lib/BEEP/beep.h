/**
  ******************************************************************************
  * @file    stm8s_beep.h
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   This file contains all functions prototype and macros for the BEEP peripheral.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
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
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_BEEP_H
#define __STM8S_BEEP_H


/* Exported types ------------------------------------------------------------*/
/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< Unsigned integer types  */
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

/*!< STM8 Standard Peripheral Library old types (maintained for legacy purpose) */

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define BEEP_BaseAddress 0x50F3
#define     __IO    volatile         /*!< defines 'read / write' permissions  */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/
/**
  * @brief  Beeper (BEEP) peripheral registers.
  */

typedef struct BEEP_struct
{
  __IO uint8_t CSR; /*!< BEEP Control status register */
}
BEEP_TypeDef;

/** @addtogroup BEEP_Registers_Reset_Value
  * @{
  */
#define BEEP_CSR_RESET_VALUE ((uint8_t)0x1F)
/**
  * @}
  */

/** @addtogroup BEEP_Registers_Bits_Definition
  * @{
  */
#define BEEP_CSR_BEEPSEL ((uint8_t)0xC0) /*!< Beeper frequency selection mask */
#define BEEP_CSR_BEEPEN  ((uint8_t)0x20) /*!< Beeper enable mask */
#define BEEP_CSR_BEEPDIV ((uint8_t)0x1F) /*!< Beeper Divider prescalar mask */
/**
  * @}
  */

/*----------------------------------------------------------------------------*/

#define BEEP_CSR_RESET_VALUE ((uint8_t)0x1F)
#define BEEP ((BEEP_TypeDef *) BEEP_BaseAddress)
/** @addtogroup BEEP_Exported_Types
  * @{
  */

/**
  * @brief  BEEP Frequency selection
  */
typedef enum {
  BEEP_FREQUENCY_1KHZ = (uint8_t)0x00,  /*!< Beep signal output frequency equals to 1 KHz */
  BEEP_FREQUENCY_2KHZ = (uint8_t)0x40,  /*!< Beep signal output frequency equals to 2 KHz */
  BEEP_FREQUENCY_4KHZ = (uint8_t)0x80   /*!< Beep signal output frequency equals to 4 KHz */
} BEEP_Frequency_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @addtogroup BEEP_Exported_Constants
  * @{
  */

#define BEEP_CALIBRATION_DEFAULT ((uint8_t)0x0B) /*!< Default value when calibration is not done */

#define LSI_FREQUENCY_MIN ((uint32_t)110000) /*!< LSI minimum value in Hertz */
#define LSI_FREQUENCY_MAX ((uint32_t)150000) /*!< LSI maximum value in Hertz */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup BEEP_Private_Macros
  * @{
  */

/**
  * @brief  Macro used by the assert function to check the different functions parameters.
  */

/**
  * @brief  Macro used by the assert function to check the BEEP frequencies.
  */
#define IS_BEEP_FREQUENCY_OK(FREQ) \
  (((FREQ) == BEEP_FREQUENCY_1KHZ) || \
   ((FREQ) == BEEP_FREQUENCY_2KHZ) || \
   ((FREQ) == BEEP_FREQUENCY_4KHZ))

/**
  * @brief   Macro used by the assert function to check the LSI frequency (in Hz).
  */
#define IS_LSI_FREQUENCY_OK(FREQ) \
  (((FREQ) >= LSI_FREQUENCY_MIN) && \
   ((FREQ) <= LSI_FREQUENCY_MAX))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/** @addtogroup BEEP_Exported_Functions
  * @{
  */

void BEEP_DeInit(void);
void BEEP_Init(BEEP_Frequency_TypeDef BEEP_Frequency);
void BEEP_Cmd(FunctionalState NewState);
void BEEP_LSICalibrationConfig(uint32_t LSIFreqHz);


/**
  * @}
  */

#endif /* __STM8S_BEEP_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
