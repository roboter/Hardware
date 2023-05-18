/**
  ******************************************************************************
  * @file    Project/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    16_January-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * FOR MORE INFORMATION PLEASE READ CAREFULLY THE LICENSE AGREEMENT FILE
  * LOCATED IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"
#include "HD44780.h"
#include "delay.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Global variables*/
volatile bool event = TRUE;
volatile bool timeON = FALSE;
volatile bool Key_status = FALSE;
volatile u16 ten_ms = 0;
volatile u16 sec = 0 ;
volatile u16 min = 0;

/* Define 6 custom characters to display bar graph*/
char STCustom[48] =
  {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Blank
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, // 1column  |
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, // 2columns ||
    0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, // 3columns |||
    0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, // 4columns ||||
    0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, // 5columns |||||
  };

void main(void)
{
  u16 i, count;
  u8 char_pos, roll;
  /* Custom characters can be 8 max. user defined characters from 0 to 7*/
  /* disp[] string is here to generate the display of custom characters on LCD*/
  /* of the bar graph using 8 characters pattern*/
  /* Example: printing "\0\0\0\0\0\0\0\0\n" will display 8 times character 0*/
  /* which is the blank character*/
  /* Example: printing "\5\5\5\5\5\5\5\5\n" will display 8 times character 5*/
  /* which is the 5 columns character*/
  char disp[] = "\0\0\0\0\0\0\0\0\n";
  char message[5][7] = {"STM8S", "Value", "Line", "8-Bit", "Micro"};

  /* Init CLK divider*/
  CLK->CKDIVR = 0x00; //to be programmed with value for Fmaster = Fcpu = Fhsi

  /* Init GPIOs*/
  /* This function sets GPIOs pins according to LCD pins assignment in main.h*/
  GPIO_Configuration();

  /* TIM4 configuration:
    - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
    clock used is 16 MHz / 128 = 125 000 Hz
   - With 125 000 Hz we can generate time base:
       max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
       min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
   - In this example we need to generate a time base equal to 1 ms
    so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
  /* Enable interrupts */
  enableInterrupts();
  /* Set power supply on LCD via LCD Power Pin */
  LCD_PWRON();
  /* Min. delay to wait before initialization after LCD power ON */
  /* Value is ms units*/
  Delay(100);
  /* Initialization of LCD */
  LCD_INIT();
  /* LCD Clear Display */
  LCD_CLEAR_DISPLAY();
  /* Set @CGRAM address start */
  LCD_CMD(CGRAM_address_start);
  /* Loading 6 characters @CGRAM address from STCustom tab */
  LCD_LOAD_CGRAM(STCustom, 6);

  /* Init local variables*/
  roll = 0;
  count = 0;
  /* Init global variables*/
  ten_ms = 0;
  sec = 0;
  min = 0;

  /* Welcome application message while user key not pressed*/
  while (!Key_status)
  {
    LCD_CLEAR_DISPLAY();
    /* Set cursor to the chosen position*/
    LCD_LOCATE(1, 1);
    /* Print string on LCD (must be ended with \n)*/
    LCD_printstring("*STM8SValueLine*\n");
    LCD_LOCATE(2, 2);
    LCD_printstring("* Discovery *\n");
    Delay(700);
    /* Set display OFF*/
    LCD_DISP_OFF();
    Delay(300);
    LCD_CLEAR_DISPLAY();
    LCD_LOCATE(1, 4);
    LCD_printstring("* Press *\n");
    LCD_LOCATE(2, 5);
    LCD_printstring("* Key *\n");
    /* Set display ON again*/
    LCD_DISP_ON();
    Delay(500);
  }
  LCD_CLEAR_DISPLAY();
  /* Reset key status*/
  Key_status = FALSE;
  /* Enable time counter display*/
  timeON = TRUE;

  /* Purpose of this brief LCD demo is to simultaneously display 4 different items*/
  /* on the 2-line LCD combining some of the LCD library resources*/
  /* A 8-character pattern bar graph which is progressively incremented*/
  /* The square value of a count variable between 0 up to 128*/
  /* A time counter displaying minutes, seconds, tenth and hundredth of seconds*/
  /* A rolling ASCII message changing every second*/
  while (1)
  {
    /* Start with first character of bar graph*/
    char_pos = 0;
    /* Display 8-character pattern bar graph, (count)^2 value, time counter, rolling message*/
    while (char_pos < 8)
    {
      /* If event true (1 sec elapsed) then display rolling messages*/
      if (event == TRUE)
      {
        event = FALSE;
        LCD_LOCATE(2, 11);
        /* Message is displayed at the bottom right*/
        /* Uses special mask*/
        LCD_printf("%5s", message[roll]);
        /* Message changes every time (5 times) then return to first word*/
        /* Table index "roll" is set accordingly*/
        roll = (roll + 1) % 5;
      }
      /* Display each 6 (0 to 5) custom characters at same LCD position*/
      for (i = 0;i < 6;i++)
      {
        /* Display bar graph at the top left*/
        LCD_LOCATE(1, 1);
        LCD_printstring(disp);
        /* Change custom character to be displayed 0->1->2->3->4->5*/
        disp[char_pos] = (disp[char_pos] + 1);
        /* Display count value*/
        LCD_LOCATE(1, 11);
        /* Display (count^2) value at the top right*/
        /* Uses special mask*/
        LCD_printf("%5d", count*count);
        count++;
        /* Reset count variable if upper than 128*/
        if (count > 128)
          count = 0;
        Key_status = FALSE;
        /* Display time counter Min:Sec:Ten ms at the bottom left*/
        LCD_LOCATE(2, 1);
        /* Uses special mask*/
        LCD_printf("%02d:%02d:%02d", min, sec, ten_ms);
      }
      /* if custom character 5 reached (all columns filled) maintain it display */
      disp[char_pos] = 5;
      /* and move to next position of bar graph*/
      char_pos++;
    }
    /* Reset bar graph display to blank*/
    for (i = 0;i < 8;i++)
      disp[i] = 0;
    /* Blink display and wait for a while*/
    LCD_DISP_OFF();
    Delay(300);
    LCD_DISP_ON();
    Delay(1000);
  }
}



/**
  ******************************************************************************
  * @brief Configures clocks
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void CLK_Configuration(void)
{
  /* Fmaster = 16MHz */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

/**
  ******************************************************************************
  * @brief Configures GPIOs
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void GPIO_Configuration(void)
{
  /* GPIOD reset */
  GPIO_DeInit(GPIOD);
  /* GPIO reset */
  GPIO_DeInit(LCDPort);
  /* GPIO reset */
  GPIO_DeInit(LCDPwrPort);
  /* GPIO reset */
  GPIO_DeInit(LCDControlPort);
  /* Configure PD0 (LED1) as output push-pull low (led switched on) */
  GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort D0 output push-pull low LCD Bus*/
  GPIO_Init(LCDPort, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort D1  output push-pull low LCD Bus*/
  GPIO_Init(LCDPort, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort D2  output push-pull low LCD Bus*/
  GPIO_Init(LCDPort, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort D3  output push-pull low LCD Bus*/
  GPIO_Init(LCDPort, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort E output push-pull low LCD Enable Pin*/
  GPIO_Init(LCDControlPort, LCD_Enable, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPort RS output push-pull low LCD RS Pin*/
  GPIO_Init(LCDControlPort, LCD_RS, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure LCDPwrOnPort VDD output push-pull low LCD Power Supply*/
  GPIO_Init(LCDPwrPort, LCDPwrPin, GPIO_MODE_OUT_PP_LOW_FAST);
  /* Configure PC4 (push button) as input floating */
  GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_MODE_IN_PU_IT);
}

/**
  ******************************************************************************
  * @brief Toggle PD0 (Led LD1)
  * @par Parameters:
  * None
  * @retval void None
  * @par Required preconditions:
  * None
  ******************************************************************************
  */
void Toggle(void)
{
  GPIO_WriteReverse(GPIOD, GPIO_PIN_0);
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
  {}
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
