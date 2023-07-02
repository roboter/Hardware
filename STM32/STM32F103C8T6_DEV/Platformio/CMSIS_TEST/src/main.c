

/* http://zq281598585.taobao.com/
�������	  ELH    enlighten  sunny
STM32������ �⺯������	  */

/*

OLED��ʾЧ��ʵ��

���ñ�����OLED  OLED��ֱ�Ӳ嵽TFT�ӿڵ�ǰ7����λ�ü���
oled IOʹ��˵��			 ע��OLED����һ��Ҫ3.3V
D0 SCLK  PC8
D1 SDIN  PC9
RES      PC10
DC       PA15
CS       PB8

*/

#include "delay.h"
#include "led.h"
#include "oled.h"

int main(void)
{

    delay_init(); // ��ʱ������ʼ��
    LED_Init();   // ��ʼ����LED���ӵ�Ӳ���ӿ�

    OLED_Init(); // ��ʼ��OLED

    OLED_Clear();

    OLED_ShowCHinese(0, 0, 0); // ������ӿƼ�
    OLED_ShowCHinese(18, 0, 1);
    OLED_ShowCHinese(36, 0, 2);
    OLED_ShowCHinese(54, 0, 3);
    OLED_ShowCHinese(72, 0, 4);
    OLED_ShowCHinese(90, 0, 5);

    OLED_ShowString(0, 2, "1.3' OLED TEST");
    //	OLED_ShowString(8,2,"ZHONGJINGYUAN");
    OLED_ShowString(20, 4, "2015/10/13");
    OLED_ShowString(0, 6, "ASCII:");
    OLED_ShowString(63, 6, "CODE:");

    while (1)
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1); // ��PC13��0
        delay_ms(800);
        GPIO_SetBits(GPIOA, GPIO_Pin_1); // ��PC13��1
        delay_ms(800);
    }
}
