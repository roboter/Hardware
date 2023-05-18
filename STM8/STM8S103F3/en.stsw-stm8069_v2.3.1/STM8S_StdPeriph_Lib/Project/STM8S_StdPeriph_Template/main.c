/**
******************************************************************************
* @file    Project/main.c 
* @author  MCD Application Team
* @version V2.3.0
* @date    16-June-2017
* @brief   Main program body
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


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint32_t LSIMeasurment(void);
void Delay (uint16_t nCount);
static void CLK_Config(void);
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  uint8_t i = 0;
  /* Clock configuration -----------------------------------------*/
  CLK_Config();
  /* BEEP calibration */
  BEEP_LSICalibrationConfig(LSIMeasurment());
  /* Enable general interrupts for Key button reading */
  enableInterrupts();
  
  BEEP_Cmd(DISABLE);
  Delay(100);
  BEEP_Init(BEEP_FREQUENCY_1KHZ);
  
  BEEP_Cmd(ENABLE);
  Delay(65535);
  /* Infinite loop */
  while (1)
  {
    i++;
    /* Change BEEP frequency */
    switch (i)
    {
    case 1:
      BEEP_Cmd(DISABLE);     
      BEEP_Init(BEEP_FREQUENCY_1KHZ);
      BEEP_Cmd(ENABLE);
      Delay(20000);
      break;
      
    case 2:
      BEEP_Cmd(DISABLE);      
      BEEP_Init(BEEP_FREQUENCY_2KHZ);
      BEEP_Cmd(ENABLE);
      Delay(20000);
      break;
      
    case 3:
      BEEP_Cmd(DISABLE);  
      BEEP_Init(BEEP_FREQUENCY_4KHZ);
      BEEP_Cmd(ENABLE);
      Delay(20000);
      break;
      
    case 4:
      BEEP_Cmd(DISABLE);
      Delay(200000);
      break;
    case 5:
      i=0;
      break;
    default:
      
      break;
    }
    
    
  }
  
}
/**
* @brief  Configure system clock to run at 16Mhz
* @param  None
* @retval None
*/
static void CLK_Config(void)
{
  /* Initialization of the clock */
  /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}
/**
* @brief  Delay.
* @param  nCount
* @retval None
*/
void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

/**
* @brief  Measure the LSI frequency using timer IC1 and update the calibration registers.
* @note   It is recommended to use a timer clock frequency of at least 10MHz in order 
*         to obtain a better in the LSI frequency measurement.
* @param  None
* @retval None
*/
uint32_t LSIMeasurment(void)
{
  
  uint32_t lsi_freq_hz = 0x0;
  uint32_t fmaster = 0x0;
  uint16_t ICValue1 = 0x0;
  uint16_t ICValue2 = 0x0;
  
  /* Get master frequency */
  fmaster = CLK_GetClockFreq();
  
  /* Enable the LSI measurement: LSI clock connected to timer Input Capture 1 */
  AWU->CSR |= AWU_CSR_MSR;
  
#if defined (STM8S903) || defined (STM8S103) || defined (STM8S003) || defined (STM8S001)
  /* Measure the LSI frequency with TIMER Input Capture 1 */
  
  /* Capture only every 8 events!!! */
  /* Enable capture of TI1 */
  TIM1_ICInit(TIM1_CHANNEL_1, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV8, 0);
  
  /* Enable TIM1 */
  TIM1_Cmd(ENABLE);
  
  /* wait a capture on cc1 */
  while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue1 = TIM1_GetCapture1();
  TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  /* wait a capture on cc1 */
  while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue2 = TIM1_GetCapture1();
  TIM1_ClearFlag(TIM1_FLAG_CC1);
  
  /* Disable IC1 input capture */
  TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1E);
  /* Disable timer2 */
  TIM1_Cmd(DISABLE);
  
#else  
  /* Measure the LSI frequency with TIMER Input Capture 1 */
  
  /* Capture only every 8 events!!! */
  /* Enable capture of TI1 */
  TIM3_ICInit(TIM3_CHANNEL_1, TIM3_ICPOLARITY_RISING, TIM3_ICSELECTION_DIRECTTI, TIM3_ICPSC_DIV8, 0);
  
  /* Enable TIM3 */
  TIM3_Cmd(ENABLE);
  
  /* wait a capture on cc1 */
  while ((TIM3->SR1 & TIM3_FLAG_CC1) != TIM3_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue1 = TIM3_GetCapture1();
  TIM3_ClearFlag(TIM3_FLAG_CC1);
  
  /* wait a capture on cc1 */
  while ((TIM3->SR1 & TIM3_FLAG_CC1) != TIM3_FLAG_CC1);
  /* Get CCR1 value*/
  ICValue2 = TIM3_GetCapture1();
  TIM3_ClearFlag(TIM3_FLAG_CC1);
  
  /* Disable IC1 input capture */
  TIM3->CCER1 &= (uint8_t)(~TIM3_CCER1_CC1E);
  /* Disable timer3 */
  TIM3_Cmd(DISABLE);
#endif /* (STM8S903) || (STM8S103) || (STM8S003) || (STM8S001) */
  
  /* Compute LSI clock frequency */
  lsi_freq_hz = (8 * fmaster) / (ICValue2 - ICValue1);
  
  /* Disable the LSI measurement: LSI clock disconnected from timer Input Capture 1 */
  AWU->CSR &= (uint8_t)(~AWU_CSR_MSR);
  
  return (lsi_freq_hz);
}

#ifdef USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
