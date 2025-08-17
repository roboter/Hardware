#include "stm32h7xx_hal.h"
#include "key.h"

/***
	************************************************************************************************
	*
>>>>> 文件说明：
	*
	*  初始化按键引脚，配置为上拉输入
	*
	************************************************************************************************
***/

#include "key.h"  


/*************************************************************************************************
*	函 数 名:	KEY_Init
*	入口参数:	无
*	返 回 值:无
*	函数功能:	初始化按键引脚
*	说    明:配置为上拉输入			
*************************************************************************************************/

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_KEY_CLK_ENABLE;						// 开启时钟

	GPIO_InitStruct.Pin 	= KEY_PIN;				// 按键引脚
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;	// 输入模式	
	GPIO_InitStruct.Pull = GPIO_PULLUP;			// 上拉
	
	HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);	

}

/*************************************************************************************************
*	函 数 名:	KEY_Scan
*	入口参数:	无
*	返 回 值:KEY_ON - 按键按下，KEY_OFF - 按键放开 
*	函数功能:	按键扫描
*	说    明:周期性调用该函数，根据返回值判断状态			
*************************************************************************************************/
	
uint8_t	KEY_Scan(void)
{
	if( HAL_GPIO_ReadPin ( KEY_PORT,KEY_PIN) == 0 )	//检测按键是否被按下
	{	
		HAL_Delay(10);	//延时消抖
		if( HAL_GPIO_ReadPin ( KEY_PORT,KEY_PIN) == 0)	//再次检测是否为低电平
		{
			while(  HAL_GPIO_ReadPin ( KEY_PORT,KEY_PIN) == 0);	//等待按键放开
			return KEY_ON;	//返回按键按下标志
		}
	}
	return KEY_OFF;	
}

// 按键扫描函数
// 返回值：按键按下的次数
uint8_t KEY_Scan1(void) {
    static uint8_t keyPressCount = 0; // 记录按键按下的次数
    static uint8_t keyPreviousState = KEY_OFF; // 保存按键的先前状态

    if (HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_RESET) {
        HAL_Delay(10);	//延时消抖
        if (HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_RESET && keyPreviousState == KEY_OFF) {
            while (HAL_GPIO_ReadPin(KEY_PORT, KEY_PIN) == GPIO_PIN_RESET); // 等待按键释放
            keyPressCount++; // 按键按下次数加一
            keyPreviousState = KEY_ON; // 更新先前状态
        }
    } else {
        keyPreviousState = KEY_OFF; // 当按钮未被按下时更新先前状态
    }

    return keyPressCount; // 返回按键按下次数
}








