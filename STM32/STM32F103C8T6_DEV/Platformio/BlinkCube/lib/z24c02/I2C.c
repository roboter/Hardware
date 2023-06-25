
/*************************此部分为I2C总线的驱动程序*************************************/

#include <i2c.h>
#define LED1_Pin GPIO_PIN_1
#define LED1_GPIO_Port GPIOA

#define SCL_Pin GPIO_PIN_4
#define SCL_GPIO_Port GPIOB

#define SDA_Pin GPIO_PIN_6
#define SDA_GPIO_Port GPIOB

 void IIC_Init(void)
 {
   /*Configure GPIO pins : SCL_Pin SDA_Pin */
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   GPIO_InitStruct.Pin = SCL_Pin | SDA_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

// void IIC_Init(void)
// {
//    GPIO_InitTypeDef GPIO_InitStructure;
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//    GPIO_SetBits(GPIOC, GPIO_Pin_11 | GPIO_Pin_12); // PC11,PC12 输出高
// }

// 起动总线函数
// Start_I2c();
// 功能:     启动I2C总线,即发送I2C起始条件.
void Start_I2c(void)
{
   SDA_OUT(); // sda线输出
   SDA = 1;   // 发送起始条件的数据信号
   SCL = 1;
   delay_us(4);
   SDA = 0; // 发送起始信号
   delay_us(4);
   SCL = 0; // 钳住I2C总线，准备发送或接收数据
}

// 结束总线函数
// Stop_I2c();
// 功能:     结束I2C总线,即发送I2C结束条件.
void Stop_I2c(void)
{
   SDA_OUT(); // sda线输出
   SCL = 0;
   SDA = 0; // 发送结束条件的数据信号
   delay_us(4);
   SCL = 1; // 结束条件建立时间大于4μs
   SDA = 1; // 发送I2C总线结束信号
   delay_us(4);
}

// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
u8 I2c_wait_ack(void)
{
   u8 Time = 0;
   SDA_IN(); // 配置SDA为输入
   SDA = 1;  // 准备接收应答位
   delay_us(1);
   SCL = 1;
   delay_us(1);
   while (READ_SDA)
   {
     Time++;
     if (Time > 250)
     {
       Stop_I2c();
       return 1; // 无应答返回1
     }
   }
   SCL = 0; // 时钟输出0

   return 0; // 有应答返回0
}

// 字节数据发送函数
// SendByte(u8 c);
// 功能:     将数据c发送出去,可以是地址,也可以是数据
void SendByte(u8 c)
{
   u8 BitCnt;

   SDA_OUT(); // sda线输出
   SCL = 0;   // 拉低时钟开始数据传输
            // 条件 一定要开启总线 保持SCL处于0状态 才能进行写入
   for (BitCnt = 0; BitCnt < 8; BitCnt++) // 要传送的数据长度为8位
   {
     if ((c << BitCnt) & 0x80)
       SDA = 1; // 判断发送位  发送是由高位开始发送
     else
       SDA = 0;
     delay_us(2);
     SCL = 1; // 置时钟线为高，通知被控器开始接收数据位
     delay_us(2);
     SCL = 0;
     delay_us(2);
   }
}

// 产生ACK应答
void I2C_Ack(void)
{
   SCL = 0;
   SDA_OUT(); // sda线输出
   SDA = 0;
   delay_us(2);
   SCL = 1;
   delay_us(2);
   SCL = 0;
}
// 不产生ACK应答
void I2C_NAck(void)
{
   SCL = 0;
   SDA_OUT(); // sda线输出
   SDA = 1;
   delay_us(2);
   SCL = 1;
   delay_us(2);
   SCL = 0;
}

// 字节数据接收函数
// RcvByte();
// 功能:  用来接收从器件传来的数据,并判断总线错误(发应答信号)
// ack  1 发送应答  0 不发送应答
u8 RcvByte(u8 ack)
{
   u8 retc = 0,
      i;
   SDA_IN(); // SDA设置为输入
   for (i = 0; i < 8; i++)
   {
     SCL = 0; // 置时钟线为低，准备接收数据位
     delay_us(2);
     SCL = 1; // 置时钟线为高使数据线上数据有效
     delay_us(1);
     retc <<= 1;
     if (READ_SDA)
       retc++; // 读数据位,接收的数据位放入retc中
     delay_us(1);
   }

   if (!ack)
     I2C_NAck(); // 发送nACK
   else
     I2C_Ack(); // 发送ACK

   return retc;
}
