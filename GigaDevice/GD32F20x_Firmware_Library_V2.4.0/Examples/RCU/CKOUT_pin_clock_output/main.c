/*!
    \file    main.c
    \brief   clock output via CKOUT pin example

    \version 2021-07-30, V1.0.0, firmware for GD32F20x
    \version 2022-06-30, V1.1.0, firmware for GD32F20x
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
#include "systick.h"
#include <stdio.h>
#include "gd32f20x_eval.h"

/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    /* initialize the Systick */
    systick_config();
    /* peripheral clock enable */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    /* configure clock output 0 pin(PA8) */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_8);
    /* configure clock output 1 pin(PC9) */
    gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_9);

    /* configure CKOUT0 to output system clock */
    rcu_ckout0_config(RCU_CKOUT0SRC_CKSYS, RCU_CKOUT0_DIV4);
    delay_1ms(1000);

    /* enable IRC8M clock */
    rcu_osci_on(RCU_IRC8M);
    if(ERROR == rcu_osci_stab_wait(RCU_IRC8M)) {
        while(1) {
        }
    }
    /* configure CKOUT0 to output IRC8M clock */
    rcu_ckout0_config(RCU_CKOUT0SRC_IRC8M, RCU_CKOUT0_DIV1);
    delay_1ms(1000);

    /* enable HXTAL clock */
    rcu_osci_on(RCU_HXTAL);
    if(ERROR == rcu_osci_stab_wait(RCU_HXTAL)) {
        while(1) {
        }
    }
    /* configure CKOUT0 to output HXTAL clock */
    rcu_ckout0_config(RCU_CKOUT0SRC_HXTAL, RCU_CKOUT0_DIV1);
    delay_1ms(1000);

    /* configure CKOUT1 to output CK_PLL1 clock */
    rcu_ckout1_config(RCU_CKOUT1SRC_CKPLL1, RCU_CKOUT1_DIV2);
    delay_1ms(1000);

    /* configure PLL2 multiplication factor */
    rcu_pll2_config(RCU_PLL2_MUL8);
    /* enable PLL2 */
    rcu_osci_on(RCU_PLL2_CK);
    /* wait till PLL2 is ready */
    if(ERROR == rcu_osci_stab_wait(RCU_PLL2_CK)) {
        while(1);
    }

    /* configure CKOUT1 to output CK_PLL2 clock */
    rcu_ckout1_config(RCU_CKOUT1SRC_CKPLL2, RCU_CKOUT1_DIV4);
    delay_1ms(1000);

    while(1) {
    }
}
