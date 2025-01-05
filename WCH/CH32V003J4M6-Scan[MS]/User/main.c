/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/25
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                    PD6 -- Tx
 *
 *
 *Info : WCH-LinkE  mode:RV version 2.15
 */

#include "debug.h"
#include <ch32v00x_i2c.h>
#include <ch32v00x_gpio.h>
#include <ch32v00x_rcc.h>
#include <stdio.h>

/* Global define */
#define LED_PIN GPIO_Pin_1
#define LED_PORT GPIOC

#define BUTTONPORT GPIOC
#define UP      GPIO_Pin_7
#define RIGHT GPIO_Pin_6
#define LEFT    GPIO_Pin_5
#define DOWN    GPIO_Pin_4
#define ENTER GPIO_Pin_3

#define TIMEOUT 100  // Define a timeout value
/*********************************************************************
 * @fn      GPIO_Toggle_INIT
 *
 * @brief   Initializes GPIOA.0
 *
 * @return  none
 */
void GPIO_Buttons_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    // Enable the clock for the GPIO port
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Configure the pins as input floating
    GPIO_InitStructure.GPIO_Pin = ENTER | UP | DOWN | RIGHT | LEFT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(BUTTONPORT, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void IIC_Init() {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    I2C_InitTypeDef I2C_InitTSturcture = { 0 };

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // PC2 - SCL
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // PC1 - SDA
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD; // Alternative function + Open Drain
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure);

    I2C_InitTSturcture.I2C_ClockSpeed = 400000;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
//    I2C_InitTSturcture.I2C_OwnAddress1 = 0x00;//address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture);

    I2C_Cmd( I2C1, ENABLE);

    I2C_AcknowledgeConfig( I2C1, ENABLE);
}

void I2C_SendByte(uint8_t address, uint8_t data) {
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);

    I2C_GenerateSTART(I2C1, ENABLE);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) == RESET);

    I2C_SendData(I2C1, data);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTOP(I2C1, ENABLE);
}

void I2C_Scan() {
    printf("Scanning I2C bus...\r\n");
    for (uint16_t address = 0; address < 128; address++) {
        // Wait until the I2C bus is ready
        while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET);

        // Generate start condition
        I2C_GenerateSTART(I2C1, ENABLE);

        // Wait for the start condition to be generated
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

        // Send the address with the write bit
        I2C_Send7bitAddress(I2C1, address << 1, I2C_Direction_Transmitter);
        // Wait for the address to be acknowledged with a timeout
        uint32_t timeout_counter = 0;
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
            if (timeout_counter++ > TIMEOUT) {
                //            printf("Timeout at address 0x%02X\n", address);
                break;
            }
        }

        // If the address was acknowledged, print it
        if (timeout_counter <= TIMEOUT) {
            printf("0x%02X ", address  /*<< 1*/);
        } else {
            printf(". ");
        }

        // Generate stop condition
        I2C_GenerateSTOP(I2C1, ENABLE);
    }
    printf("\r\n");
}

int main(void) {
    // Initialize system and GPIO
    SystemInit();
    Delay_Init();
    USART_Printf_Init(115200);
    GPIO_Buttons_INIT();
    // Setup internal peripherals

    IIC_Init();
    //I2C_init_Display();
    int previous = 0;

    while (1)
    {
        // Toggle PC1
        // Read the button values
        int up = GPIO_ReadInputDataBit(BUTTONPORT, UP);
        int right = GPIO_ReadInputDataBit(BUTTONPORT, RIGHT);
        int left = GPIO_ReadInputDataBit(BUTTONPORT, LEFT);
        int down = GPIO_ReadInputDataBit(BUTTONPORT, DOWN);
        int enter = GPIO_ReadInputDataBit(BUTTONPORT, ENTER);

        // Check which button is pressed
        if (up && previous != UP) {

            printf("UP\n");
            printf("SystemClk:%d\r\n",SystemCoreClock);
            previous = UP;
        } else if (right && previous != RIGHT) {

            printf("RIGHT\n");
            previous = RIGHT;
        } else if (left && previous != LEFT) {

            printf("LEFT\n");
            previous = LEFT;
        } else if (down && previous != DOWN) {

            printf("DOWN\n");
            previous = DOWN;
        } else if (enter && previous != ENTER) {

            printf("ENTER button pressed\n");
            previous = ENTER;
            I2C_Scan();
        }

    }
}
