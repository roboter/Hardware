/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.1
 *
 * @date        2021-07-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "Board.h"
#include "stdio.h"
#include "string.h"
#include "apm32f0xx_i2c.h"
#include "apm32f0xx_misc.h"
#include "apm32f0xx_eint.h"
#include "apm32f0xx_rcm.h"

/** printf function configs to USART2*/
#define DEBUG_USART  USART2

/*Waiting TIMEOUT*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
static volatile uint32_t I2CTimeout = I2CT_LONG_TIMEOUT;

/*Debug Information output*/
#define I2C_DEBUG_ON        1
#define I2C_ERROR(fmt,arg...)      printf("<<-Slave-I2C_ERROR->> "fmt"\r\n",##arg)

/** I2C Init */
void I2CInit(void);
/** I2C write uint8_t data */
uint32_t I2C_Write(I2C_T *i2c,uint8_t *dat);
/** Delay */
void Delay(uint32_t count);


/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
int main(void)
{

    APM_MINI_LEDInit(LED3);
    APM_MINI_PBInit(BUTTON_KEY1,BUTTON_MODE_EINT);
    APM_MINI_COMInit(COM2);
    I2CInit();

    for(;;)
    {
        /** Press the BUTTON_KEY1, master will send data to
        slave along with information that showed in serial port*/

        APM_MINI_LEDToggle(LED3);

        Delay(100000);
    }
}

/*!
 * @brief       Redirect C Library function printf to serial port.
 *              After Redirection, you can use printf function.
 *
 * @param       ch:  The characters that need to be send.
 *
 * @param       *f:  pointer to a FILE that can recording all information
 *              needed to control a stream
 *
 * @retval      The characters that need to be send.
 *
 * @note
 */
int fputc(int ch, FILE *f)
{
        /** send a byte of data to the serial port */
        USART_TxData(DEBUG_USART,(uint8_t)ch);

        /** wait for the data to be send  */
        while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

        return (ch);
}

/*!
 * @brief       Delay
 *
 * @param       count:  delay count
 *
.
 * @retval      None
 *
 * @note
 */
void Delay(uint32_t count)
{
    volatile uint32_t delay = count;

    while(delay--);
}

/*!
 * @brief        Used to locate the wrong location of the
 *              I2C_Write()
 *
 * @param        errorCode
 *
 * @retval      Error code location information
 *
 * @note
 */
uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
   if(I2C_DEBUG_ON)
   {
         I2C_ERROR("I2C Wait TIMEOUT! errorCode = %d\r\n",errorCode);
   }

  return 0;
}

/*!
 * @brief       I2C Init
 *
 * @param       None
 *
 * @retval      None
 *
 * @note
 */
 void I2CInit(void)
 {
    GPIO_Config_T gpioConfigStruct;
    I2C_Config_T i2cConfigStruct;
     /** Enable I2C related Clock */
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_I2C1);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

     /** Free I2C_SCL and I2C_SDA */
    gpioConfigStruct.mode = GPIO_MODE_OUT;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    gpioConfigStruct.outtype = GPIO_OUT_TYPE_PP;
    gpioConfigStruct.pupd = GPIO_PUPD_NO;
    gpioConfigStruct.pin = GPIO_PIN_8;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    gpioConfigStruct.pin = GPIO_PIN_9;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    GPIO_SetBit(GPIOB,GPIO_PIN_8);
    GPIO_SetBit(GPIOB,GPIO_PIN_9);

    /** Connect I2C to SCL */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_8, GPIO_AF_PIN1);
    /** Connect I2C to SDA */
    GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_9, GPIO_AF_PIN1);
    /** Config  I2C1 GPIO */
    gpioConfigStruct.mode = GPIO_MODE_AF;
    gpioConfigStruct.speed = GPIO_SPEED_50MHz;
    gpioConfigStruct.outtype = GPIO_OUT_TYPE_OD;
    gpioConfigStruct.pupd = GPIO_PUPD_NO;
    gpioConfigStruct.pin = GPIO_PIN_8;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    gpioConfigStruct.pin = GPIO_PIN_9;
    GPIO_Config(GPIOB, &gpioConfigStruct);

    /**  Config I2C1 */
    I2C_Reset(I2C1);
    RCM_ConfigI2CCLK(RCM_I2C1CLK_SYSCLK);
    i2cConfigStruct.ack = I2C_ACK_ENABLE;
    i2cConfigStruct.ackaddress = I2C_ACK_ADDRESS_7BIT;
    i2cConfigStruct.address1 = 0XB0;
    i2cConfigStruct.analogfilter = I2C_ANALOG_FILTER_ENABLE;
    i2cConfigStruct.digitalfilter = I2C_DIGITAL_FILTER_0;
    i2cConfigStruct.mode = I2C_MODE_I2C;
    i2cConfigStruct.timing = 0x1042F013;
    I2C_Config(I2C1,&i2cConfigStruct);

    /** Enable the I2C1 Interrupt */
    I2C_EnableInterrupt(I2C1,I2C_INT_RXIE|I2C_INT_ADDRIE|I2C_INT_STOPIE);

    /** NVIC configuration */
    NVIC_EnableIRQRequest(I2C1_IRQn,1);

    /** Enable I2Cx */
     I2C_Enable(I2C1);
 }


/*!
 * @brief    I2C Write
 *
 * @param    I2C: Specifies the I2C to be configured.
 *           This parameter can be one of following parameters:
 *           @arg I2C1
 *           @arg I2C2
 *
 * @param    *dat: Pointer to data
 *
 * @retval   0 or ERROR Information
 *
 * @note
 */
uint32_t I2C_Write(I2C_T *i2c,uint8_t *dat)
{

    I2CTimeout = I2CT_LONG_TIMEOUT;

    /** Wait until I2C is idle */
    while(I2C_ReadStatusFlag(i2c,I2C_FLAG_BUSY) == SET)
    {
       I2CInit();
       if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
    }
     /** Disable I2C interrupt  */
    I2C_DisableInterrupt(i2c,I2C_INT_RXIE|I2C_INT_ADDRIE|I2C_INT_STOPIE);
    I2C_DisableReload(I2C1);
    /** I2C Send Configuration*/
    I2C_HandlingTransfer(i2c,0xA0,strlen((char *)dat),I2C_RELOAD_MODE_AUTOEND,I2C_GENERATE_START_WRITE);
    /** I2C Send Data */

    while(*dat)
    {
        I2C_TxData(i2c,*dat++);

        I2CTimeout = I2CT_LONG_TIMEOUT;

        while(I2C_ReadStatusFlag(i2c,I2C_FLAG_TXBE) == RESET)
        {
            if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
        }
    }
     /** I2C Generate Stop signal */
    I2C_EnableGenerateStop(i2c);

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while(I2C_ReadStatusFlag(i2c,I2C_FLAG_STOP) == RESET)
    {
        if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);

    }
     /** I2C Clear Stop Flag */
    I2C_ClearIntFlag(i2c,I2C_INT_FLAG_STOP);
    I2C_EnableReload(I2C1);
     /** I2C Config Number of Bytes to send or to write */
    I2C_ConfigNumberOfBytes(i2c, 1);
     /** I2C Enable Interrupt */
    I2C_EnableInterrupt(i2c,I2C_INT_RXIE|I2C_INT_ADDRIE|I2C_INT_STOPIE);

    return 0;
}

/*!
 * @brief       I2C interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into I2C1_IRQHandler() in apm32f0xx_int.c
 */
void  I2C_Isr(void)
{
    uint8_t dat;

    if(I2C_ReadIntFlag(I2C1,I2C_INT_FLAG_ADDR) == SET)
    {
        /** I2C_ConfigNumberOfBytes is necessary*/
        I2C_ConfigNumberOfBytes(I2C1, 1);

        I2C_ClearIntFlag(I2C1,I2C_INT_FLAG_ADDR);
    }

    if(I2C_ReadIntFlag(I2C1,I2C_INT_FLAG_RXBNE) == SET)
    {
        /** I2C_ConfigNumberOfBytes is necessary*/
        I2C_ConfigNumberOfBytes(I2C1, 1);
        dat = (uint8_t)I2C_RxData(I2C1);
        printf("%c",dat);
    }

    if(I2C_ReadIntFlag(I2C1,I2C_INT_FLAG_STOP) == SET)
    {
        I2C_ClearIntFlag(I2C1,I2C_INT_FLAG_STOP);
    }

}

/*!
 * @brief       BUTTON_KEY interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This function need to put into EINT0_1_IRQHandler()
 *              in apm32f0xx_int.c
 */
 void APM_MINI_PB_I2C_Isr()
{
    if(EINT_ReadStatusFlag(EINT_LINE1)==SET)
    {
        I2C_Write(I2C1,"Hello slave \r\n");

        EINT_ClearStatusFlag(EINT_LINE1);
    }
}




