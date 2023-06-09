/*!
    \file    main.c
    \brief   USART transmit and receive interrupt

    \version 2015-07-15, V1.0.0, firmware for GD32F20x
    \version 2017-06-05, V2.0.0, firmware for GD32F20x
    \version 2018-10-31, V2.1.0, firmware for GD32F20x
    \version 2020-09-30, V2.2.0, firmware for GD32F20x
    \version 2021-07-30, V2.3.0, firmware for GD32F20x
    \version 2022-06-30, V2.4.0, firmware for GD32F20x
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f20x.h"
#include "gd32f20x_eval.h"

#define USART0_RDATA_ADDRESS      ((uint32_t)&USART_DATA(USART0))

uint8_t rxbuffer[256];
uint8_t rx_count = 0;
__IO uint8_t tx_count = 0;
__IO uint8_t receive_flag = 0;

void dma_config(void);
void usart_config(void);
void nvic_config(void);

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    gd_eval_led_init(LED2);
    gd_eval_led_on(LED2);
    nvic_config();

    /* initialize DMA */
    dma_config();

    /* initialize USART */
    usart_config();

    /*wait IDLEF set and clear it*/
    while(RESET == usart_flag_get(USART0, USART_FLAG_IDLEF));
    usart_flag_clear(USART0, USART_FLAG_IDLEF);
    usart_interrupt_enable(USART0, USART_INT_IDLE);

    /* wait the data is received and send to the hyperterminal */
    while(1) {
        if(1 == receive_flag) {
            for(tx_count = 0; tx_count < rx_count; tx_count++) {
                while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
                usart_data_transmit(USART0, rxbuffer[tx_count]);
            }
            receive_flag = 0;
        }
    }
}

/*!
    \brief      configure USART DMA
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void)
{
    dma_parameter_struct dma_init_struct;

    rcu_periph_clock_enable(RCU_DMA0);

    /* deinitialize DMA channel4 (USART0 rx) */
    dma_deinit(DMA0, DMA_CH4);
    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr = (uint32_t)rxbuffer;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 256;
    dma_init_struct.periph_addr = USART0_RDATA_ADDRESS;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;
    dma_init(DMA0, DMA_CH4, &dma_init_struct);
    /* configure DMA mode */
    dma_circulation_disable(DMA0, DMA_CH4);
    /* enable DMA channel4 */
    dma_channel_enable(DMA0, DMA_CH4);
}

/*!
    \brief      configure USART
    \param[in]  none
    \param[out] none
    \retval     none
*/
void usart_config(void)
{
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USART0 TX */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USART0 RX */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_dma_enable(USART0, USART_DMA_RECEIVE);
    usart_dma_enable(USART0, USART_DMA_TRANSMIT);
    usart_enable(USART0);
}

/*!
    \brief      configure NVIC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void nvic_config(void)
{
    nvic_irq_enable(USART0_IRQn, 0, 0);
}
