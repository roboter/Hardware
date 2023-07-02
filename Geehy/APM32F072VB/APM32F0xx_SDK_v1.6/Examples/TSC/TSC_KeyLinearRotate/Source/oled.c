/*!
 * @file        oled.c
 *
 * @brief       This file contains the Delay Driver main functions.
 *
 * @version     V1.0.0
 *
 * @date        2022-02-21
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
#include "oled.h"
#include "delay.h"
#include "oledfont.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup OLED_Driver OLED Driver
  @{
*/

/** @addtogroup OLED_Fuctions Fuctions
  @{
*/

uint8_t OLED_GRAM[144][8];

/*!
 * @brief       I2C start signal
 *
 * @param       None
 *
 * @retval      None
 */
void I2C_Start(void)
{
    OLED_SDA_Set();
    OLED_SCL_Set();
    OLED_SDA_Clr();
    OLED_SCL_Clr();
}

/*!
 * @brief       I2C stop signal
 *
 * @param       None
 *
 * @retval      None
 */
void I2C_Stop(void)
{
    OLED_SCL_Set();
    OLED_SDA_Clr();
    OLED_SDA_Set();
}

/*!
 * @brief       I2C wait ACk
 *
 * @param       None
 *
 * @retval      None
 */
void I2C_WaitAck(void)
{
    OLED_SCL_Set();
    OLED_SCL_Clr();
}

/*!
 * @brief       Send one byte
 *
 * @param       data: one byte
 *
 * @retval      None
 */
void Send_Byte(uint8_t data)
{
    uint8_t i;

    for (i=0; i<8; i++)
    {
        OLED_SCL_Clr();
        /** Write data from the highest bits */
        if (data & 0x80)
        {
            OLED_SDA_Set();
        }
        else
        {
            OLED_SDA_Clr();
        }

        OLED_SCL_Set();
        OLED_SCL_Clr();
        data <<= 1;
    }
}

/*!
 * @brief       Write one byte
 *
 * @param       data: one byte
 *
 * @param       mode: write mode
 *              @arg 0: CMD
 *              @arg 1: DATA
 *
 * @retval      None
 */
void OLED_Write_Byte(uint8_t data, uint8_t mode)
{
    I2C_Start();
    Send_Byte(0x78);
    I2C_WaitAck();

    if (mode)
    {
        Send_Byte(0x40);
    }
    else
    {
        Send_Byte(0x00);
    }

    I2C_WaitAck();
    Send_Byte(data);
    I2C_WaitAck();
    I2C_Stop();
}

/*!
 * @brief       Turn Color
 *
 * @param       i: Select color mode
 *              @arg 0: Normal
 *              @arg 1: Turn
 *
 * @retval      None
 */
void OLED_TurnColor(uint8_t i)
{
    if (i==0)
    {
        OLED_Write_Byte(0xA6, OLED_CMD);
    }
    if (i==1)
    {
        OLED_Write_Byte(0xA7, OLED_CMD);
    }
}

/*!
 * @brief       Turn Display
 *
 * @param       i: Select display mode
 *              @arg 0: Normal
 *              @arg 1: Turn 180бу
 *
 * @retval      None
 */
void OLED_TurnDisplay(uint8_t i)
{
    if (i==0)
    {
        OLED_Write_Byte(0xC8, OLED_CMD);
        OLED_Write_Byte(0xA1, OLED_CMD);
    }
    if (i==1)
    {
        OLED_Write_Byte(0xC0, OLED_CMD);
        OLED_Write_Byte(0xA0, OLED_CMD);
    }
}

/*!
 * @brief       Open the OLED display
 *
 * @param       None
 *
 * @retval      None
 */
void OLED_DisPlay_On(void)
{
    /** Enable charge pupm */
    OLED_Write_Byte(0x8D, OLED_CMD);
    /** Open charge pupm */
    OLED_Write_Byte(0x14, OLED_CMD);
    /** Open OLED */
    OLED_Write_Byte(0xAF, OLED_CMD);
}

/*!
 * @brief       Off the OLED display
 *
 * @param       None
 *
 * @retval      None
 */
void OLED_DisPlay_Off(void)
{
    /** Enable charge pupm */
    OLED_Write_Byte(0x8D, OLED_CMD);
    /** Off charge pupm */
    OLED_Write_Byte(0x10, OLED_CMD);
    /** Off OLED */
    OLED_Write_Byte(0xAF, OLED_CMD);
}

/*!
 * @brief       Refresh the OLED
 *
 * @param       None
 *
 * @retval      None
 */
void OLED_Refresh(void)
{
    uint8_t i, n;

    for (i=0; i<8; i++)
    {
        /** Set the start address for line */
        OLED_Write_Byte(0xb0+i, OLED_CMD);
        /** Set the start address for low column */
        OLED_Write_Byte(0x00, OLED_CMD);
        /** Set the start address for high column */
        OLED_Write_Byte(0x10, OLED_CMD);

        for (n=0; n<128; n++)
        {
            OLED_Write_Byte(OLED_GRAM[n][i], OLED_DATA);
        }
    }
}

/*!
 * @brief       Clear the OLED
 *
 * @param       None
 *
 * @retval      None
 */
void OLED_Clear(void)
{
    uint8_t i, n;

    for (i=0; i<8; i++)
    {
        for (n=0; n<128; n++)
        {
            OLED_GRAM[n][i]=0;
        }
    }

    OLED_Refresh();
}

/*!
 * @brief       Clear char on the OLED
 *
 * @param       None
 *
 * @retval      None
 */
void OLED_ClearChar(uint8_t x, uint8_t y)
{
    uint8_t i, n;
    for(i=0; i<2; i++)
    {
        for(n=x; n<y; n++)
        {
            OLED_GRAM[n][i]=0;
        }

    }

    OLED_Refresh();
}

/*!
 * @brief       Draw point on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @retval      None
 */
void OLED_DrawPoint(uint8_t x, uint8_t y)
{
    uint8_t i, m, n;
    i=y/8;
    m=y%8;
    n=1<<m;
    OLED_GRAM[x][i]|=n;
}

/*!
 * @brief       Clear point on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @retval      None
 */
void OLED_ClearPoint(uint8_t x, uint8_t y)
{
    uint8_t i, m, n;
    i=y/8;
    m=y%8;
    n=1<<m;
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
    OLED_GRAM[x][i]|=n;
    OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}

/*!
 * @brief       Draw line on the OLED
 *
 * @param       x1,x2: 0~127  y1,y2:0~63
 *
 * @retval      None
 */
void OLED_DrawLine(int x1, int y1, int x2, int y2)
{
    int i, k, k1, k2;

    if ((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))
    {
        return;
    }
    /** Vertical line */
    if (x1==x2)
    {
        for (i=0; i<(y2-y1); i++)
        {
            OLED_DrawPoint(x1, y1+i);
        }
    }
    /** Horizontal line */
    else if (y1==y2)
    {
        for (i=0; i<(x2-x1); i++)
        {
            OLED_DrawPoint(x1+i, y1);
        }
    }
    /** Oblique line */
    else
    {
        k1=y2-y1;
        k2=x2-x1;
        k=k1*10/k2;

        for (i=0; i<(x2-x1); i++)
        {
            OLED_DrawPoint(x1+i, y1+i*k/10);
        }
    }
}

/*!
 * @brief       Draw line on the OLED
 *
 * @param       x,y: center   r: radius
 *
 * @retval      None
 */
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r)
{
    int a, b, num;
    a = 0;
    b = r;

    while (2 * b * b >= r * r)
    {
        OLED_DrawPoint(x + a, y - b);
        OLED_DrawPoint(x - a, y - b);
        OLED_DrawPoint(x - a, y + b);
        OLED_DrawPoint(x + a, y + b);

        OLED_DrawPoint(x + b, y + a);
        OLED_DrawPoint(x + b, y - a);
        OLED_DrawPoint(x - b, y - a);
        OLED_DrawPoint(x - b, y + a);

        a++;
        num = (a * a + b * b) - r*r;

        if (num > 0)
        {
            b--;
            a--;
        }
    }
}

/*!
 * @brief       Show char on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @param       size: cna be 12/16/24
 *
 * @retval      None
 */
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
    uint8_t i, m, temp, size1, chr1;
    uint8_t y0=y;
    size1 = (size/8 + ((size%8) ? 1:0))*(size/2);
    chr1 = chr-' ';

    for (i=0; i<size1; i++)
    {
        if (size==12)
        {
            /** ASCII 1206 type */
            temp=asc2_1206[chr1][i];
        }
        else if (size==16)
        {
            /** ASCII 1608 type */
            temp=asc2_1608[chr1][i];
        }
        else if (size==24)
        {
            /** ASCII 2412 type */
            temp=asc2_2412[chr1][i];
        }
        else
        {
            return;
        }

        for (m=0; m<8; m++)
        {
            if (temp&0x80)
            {
                OLED_DrawPoint(x, y);
            }
            else
            {
                OLED_ClearPoint(x, y);
            }

            temp<<=1;
            y++;

            if ((y-y0)==size)
            {
                y=y0;
                x++;
                break;
            }
        }
    }
}

/*!
 * @brief       Show String on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @param       *chr: string start address
 *
 * @param       size: cna be 12/16/24
 *
 * @retval      None
 */
void OLED_ShowString(uint8_t x, uint8_t y, char* chr, uint8_t size)
{
    while ((*chr>=' ')&&(*chr<='~'))
    {
        OLED_ShowChar(x, y, *chr, size);
        x+=size/2;

        if (x>128-size)
        {
            x=0;
            y+=2;
        }

        chr++;
    }
}

/*!
 * @brief       m^n
 *
 * @param       None
 *
 * @retval      None
 */
uint32_t OLED_Pow(uint8_t m, uint8_t n)
{
    uint32_t result=1;

    while (n--)
    {
        result*=m;
    }

    return result;
}

/*!
 * @brief       Show number on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @retval      None
 */
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;

    for (t=0; t<len; t++)
    {
        temp=(num/OLED_Pow(10, len-t-1))%10;

        if (temp==0)
        {
            OLED_ShowChar(x+(size/2)*t, y, '0', size);
        }
        else
        {
            OLED_ShowChar(x+(size/2)*t, y, temp+'0', size);
        }
    }
}

/*!
 * @brief       Show chinese on the OLED
 *
 * @param       x: 0~127  y: 0~63
 *
 * @param       num: the chinese number
 *
 * @param       size: cna be 16/24/32/64
 *
 * @retval      None
 */
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size)
{
    uint8_t i, m, n=0, temp, chr1;
    uint8_t x0=x, y0=y;
    uint8_t size2 = size/8;

    while (size2--)
    {
        chr1 = num*size/8+n;
        n++;

        for (i=0; i<size; i++)
        {
            if (size==16)
            {
                /** 16*16 */
                temp=Hzk1[chr1][i];
            }
            else if (size==24)
            {
                /** 24*24 */
                temp=Hzk2[chr1][i];
            }
            else if (size==32)
            {
                /** 32*32 */
                temp=Hzk3[chr1][i];
            }
            else if (size==64)
            {
                /** 64*64 */
                temp=Hzk4[chr1][i];
            }
            else
            {
                return;
            }

            for (m=0; m<8; m++)
            {
                if (temp & 0x01)
                {
                    OLED_DrawPoint(x, y);
                }
                else
                {
                    OLED_ClearPoint(x, y);
                }

                temp>>=1;
                y++;
            }

            x++;

            if ((x-x0)==size)
            {
                x=x0;
                y0=y0+8;
            }

            y=y0;
        }
    }
}

/*!
 * @brief       Scroll Display
 *
 * @param       num: number chinese
 *
 * @retval      None
 */
void OLED_ScrollDisplay(uint8_t num, uint8_t space)
{
    uint8_t i, n, t=0, m=0, r;

    while (1)
    {
        if (m==0)
        {
            OLED_ShowChinese(128, 24, t, 16);
            t++;
        }

        if (t==num)
        {
            for (r=0; r<16*space; r++)
            {
                for (i=0; i<144; i++)
                {
                    for (n=0; n<8; n++)
                    {
                        OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
                    }
                }

                OLED_Refresh();
            }

            t=0;
        }

        m++;

        if (m==16)
        {
            m=0;
        }

        for (i=0; i<144; i++)
        {
            for (n=0; n<8; n++)
            {
                OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
            }
        }

        OLED_Refresh();
    }
}

/*!
 * @brief       Write start position
 *
 * @param       x: 0~127  y: 0~63
 *
 * @retval      None
 */
void OLED_Write_BP(uint8_t x, uint8_t y)
{
    OLED_Write_Byte(0xb0+y, OLED_CMD);
    OLED_Write_Byte(((x&0xf0)>>4)|0x10, OLED_CMD);
    OLED_Write_Byte((x&0x0f), OLED_CMD);
}

/*!
 * @brief       Write picturer position
 *
 * @param       x0y0: start position
 *
 * @param       x1y1: end position
 *
 * @retval      None
 */
void OLED_ShowPicture(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t* p)
{
    uint8_t x, y;

    for (y=y0; y<y1; y++)
    {
        OLED_Write_BP(x0, y);

        for (x=x0; x<x1; x++)
        {
            OLED_Write_Byte(*p, OLED_DATA);
        }
    }
}

/*!
 * @brief       Config OLED
 *
 * @param       num: number chinese
 *
 * @retval      None
 */
void OLED_Config(void)
{
    GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);

    gpioConfig.pin = GPIO_PIN_6|GPIO_PIN_7;
    gpioConfig.speed = GPIO_SPEED_10MHz;
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    GPIO_Config(GPIOB, &gpioConfig);

    GPIO_SetBit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
    Delay_ms(200);

    OLED_Write_Byte(0xAE, OLED_CMD); //!< turn off oled panel
    OLED_Write_Byte(0x00, OLED_CMD); //!< set low column address
    OLED_Write_Byte(0x10, OLED_CMD); //!< set high column address
    OLED_Write_Byte(0x40, OLED_CMD); //!< set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_Write_Byte(0x81, OLED_CMD); //!< set contrast control register
    OLED_Write_Byte(0xff, OLED_CMD); //!< set SEG Output Current Brightness
    OLED_Write_Byte(0xA1, OLED_CMD); //!< set SEG/Column Mapping    0xa0 left/right turn, 0xa1 Normal
    OLED_Write_Byte(0xC8, OLED_CMD); //!< set COM/Row Scan Direction   0xc0 up/down turn, 0xc8 Normal
    OLED_Write_Byte(0xA6, OLED_CMD); //!< set normal display
    OLED_Write_Byte(0xA8, OLED_CMD); //!< set multiplex ratio(1 to 64)
    OLED_Write_Byte(0x3f, OLED_CMD); //!< 1/64 duty
    OLED_Write_Byte(0xD3, OLED_CMD); //!< set display offset   Shift Mapping RAM Counter (0x00~0x3F)
    OLED_Write_Byte(0x00, OLED_CMD); //!< not offset
    OLED_Write_Byte(0xd5, OLED_CMD); //!< set display clock divide ratio/oscillator frequency
    OLED_Write_Byte(0x80, OLED_CMD); //!< set divide ratio, Set Clock as 100 Frames/Sec
    OLED_Write_Byte(0xD9, OLED_CMD); //!< set pre-charge period
    OLED_Write_Byte(0xF1, OLED_CMD); //!< set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_Write_Byte(0xDA, OLED_CMD); //!< set com pins hardware configuration
    OLED_Write_Byte(0x12, OLED_CMD);
    OLED_Write_Byte(0xDB, OLED_CMD); //!< set vcomh
    OLED_Write_Byte(0x40, OLED_CMD); //!< set VCOM Deselect Level
    OLED_Write_Byte(0x20, OLED_CMD); //!< set Page Addressing Mode (0x00/0x01/0x02)
    OLED_Write_Byte(0x02, OLED_CMD);
    OLED_Write_Byte(0x8D, OLED_CMD); //!< set Charge Pump enable/disable
    OLED_Write_Byte(0x14, OLED_CMD); //!< set(0x10) disable
    OLED_Write_Byte(0xA4, OLED_CMD); //!< disable Entire Display On (0xa4/0xa5)
    OLED_Write_Byte(0xA6, OLED_CMD); //!< disable Inverse Display On (0xa6/0xa7)
    OLED_Clear();
    OLED_Write_Byte(0xAF, OLED_CMD); //!< display ON
}

/**@} end of group OLED_Fuctions*/
/**@} end of group OLED_Driver*/
/**@} end of group Peripherals_Library*/

