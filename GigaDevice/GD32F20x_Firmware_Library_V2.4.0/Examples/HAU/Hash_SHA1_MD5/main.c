/*!
    \file    main.c
    \brief   Hash SHA1 MD5 example

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

#include "gd32f20x_eval.h"
#include "gd32f20x.h"
#include "stdio.h"
#include "string.h"

const uint8_t message_input[] = {
    0x54U, 0x68U, 0x65U, 0x20U, 0x68U, 0x61U, 0x73U, 0x68U,
    0x20U, 0x70U, 0x72U, 0x6fU, 0x63U, 0x65U, 0x73U, 0x73U,
    0x6fU, 0x72U, 0x20U, 0x69U, 0x73U, 0x20U, 0x61U, 0x20U,
    0x66U, 0x75U, 0x6cU, 0x6cU, 0x79U, 0x20U, 0x63U, 0x6fU,
    0x6dU, 0x70U, 0x6cU, 0x69U, 0x61U, 0x6eU, 0x74U, 0x20U,
    0x69U, 0x6dU, 0x70U, 0x6cU, 0x65U, 0x6dU, 0x65U, 0x6eU,
    0x74U, 0x61U, 0x74U, 0x69U, 0x6fU, 0x6eU, 0x20U, 0x6fU,
    0x66U, 0x20U, 0x74U, 0x68U, 0x65U, 0x20U, 0x73U, 0x65U,
    0x63U, 0x75U, 0x72U, 0x65U, 0x20U, 0x68U, 0x61U, 0x73U,
    0x68U, 0x20U, 0x61U, 0x6cU, 0x67U, 0x6fU, 0x72U, 0x69U,
    0x74U, 0x68U, 0x6dU, 0x20U, 0x28U, 0x53U, 0x48U, 0x41U,
    0x2dU, 0x31U, 0x29U, 0x2cU, 0x20U, 0x74U, 0x68U, 0x65U,
    0x20U, 0x4dU, 0x44U, 0x35U, 0x20U, 0x28U, 0x6dU, 0x65U,
    0x73U, 0x73U, 0x61U, 0x67U, 0x65U, 0x2dU, 0x64U, 0x69U,
    0x67U, 0x65U, 0x73U, 0x74U, 0x20U, 0x61U, 0x6cU, 0x67U,
    0x6fU, 0x72U, 0x69U, 0x74U, 0x68U, 0x6dU, 0x20U, 0x35U,
    0x29U, 0x20U, 0x68U, 0x61U, 0x73U, 0x68U, 0x20U, 0x61U,
    0x6cU, 0x67U, 0x6fU, 0x72U, 0x69U, 0x74U, 0x68U, 0x6dU,
    0x20U, 0x61U, 0x6eU, 0x64U, 0x20U, 0x74U, 0x68U, 0x65U,
    0x20U, 0x48U, 0x4dU, 0x41U, 0x43U, 0x20U, 0x28U, 0x6bU,
    0x65U, 0x79U, 0x65U, 0x64U, 0x2dU, 0x68U, 0x61U, 0x73U,
    0x68U, 0x20U, 0x6dU, 0x65U, 0x73U, 0x73U, 0x61U, 0x67U,
    0x65U, 0x20U, 0x61U, 0x75U, 0x74U, 0x68U, 0x65U, 0x6eU,
    0x74U, 0x69U, 0x63U, 0x61U, 0x74U, 0x69U, 0x6fU, 0x6eU,
    0x20U, 0x63U, 0x6fU, 0x64U, 0x65U, 0x29U, 0x20U, 0x61U,
    0x6cU, 0x67U, 0x6fU, 0x72U, 0x69U, 0x74U, 0x68U, 0x6dU,
    0x20U, 0x73U, 0x75U, 0x69U, 0x74U, 0x61U, 0x62U, 0x6cU,
    0x65U, 0x20U, 0x66U, 0x6fU, 0x72U, 0x20U, 0x61U, 0x20U,
    0x76U, 0x61U, 0x72U, 0x69U, 0x65U, 0x74U, 0x79U, 0x20U,
    0x6fU, 0x66U, 0x20U, 0x61U, 0x70U, 0x70U, 0x6cU, 0x69U,
    0x63U, 0x61U, 0x74U, 0x69U, 0x6fU, 0x6eU, 0x73U, 0x2eU,
};
static uint8_t md5_output[16];
static uint8_t sha1_output[20];

/* printf data in bytes */
static void data_display(uint32_t datalength, uint8_t *data);

uint32_t i = 0U, len = 0U;

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    gd_eval_com_init(EVAL_COM1);
    /* enable HAU clock */
    rcu_periph_clock_enable(RCU_HAU);

    len = sizeof(message_input);
    printf("\r\nmessage to be hashed:\r\n\r\n");
    for(i = 0U; i < len ; i++) {
        printf("%c", message_input[i]);
    }

    /* SHA-1 digest computation */
    hau_hash_sha_1((uint8_t *)message_input, len, sha1_output);
    printf(" \r\n\r\nSHA1 message digest (160 bits):\r\n\r\n");
    data_display(20U, sha1_output);

    /* MD5 digest computation */
    hau_hash_md5((uint8_t *)message_input, len, md5_output);
    printf(" \r\n\r\nMD5 message digest (128 bits):\r\n\r\n");
    data_display(16U, md5_output);

    while(1) {
    }
}

/*!
    \brief      printf data in bytes
    \param[in]  datalength: length of the data to display
    \param[in]  data: pointer to the data to display
    \param[out] none
    \retval     none
*/
static void data_display(uint32_t datalength, uint8_t *data)
{
    uint32_t i = 0U, count = 0U;

    for(i = 0U; i < datalength; i++) {
        printf("0x%02X ", data[i]);
        count++;

        if(4U == count) {
            count = 0U;
            printf("\r\n");
        }
    }
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(EVAL_COM1, (uint8_t)ch);
    while(RESET == usart_flag_get(EVAL_COM1, USART_FLAG_TBE));

    return ch;
}