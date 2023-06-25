
/*************************此部分为AT2402的驱动程序使用I2C总线连接*************************************/

#include  <delay.h>

#include  <i2c.h>
#include  <z24C02.h>
#include <stm32f1xx.h>

 typedef uint32_t u32;
 typedef uint16_t u16;
 typedef uint8_t u8;

 // The default hardware address of 24c is 0xa0, which is 1010, then A2 A1 A0, the last bit is the read and write bit, 1 read, 0 write
 // 24c02 256x8 bit
 // 24c04 512x8 bit
 // The sub-address is only 8 bits, that is, the maximum is 256 bytes, then 24c04 will occupy 2 256 bytes
 // Here, the 24c04 hardware adopts the paging method, that is, there are A0, A1 and A2 in 24c02. When it is 24c04, A0 is used as the paging bit
 // When A0 is 0, it means the first page, write the first page 256 bytes
 // When A0 is 1, it means that the second page writes 256 bytes to the second page

 // 初始化IIC接口
 void AT24CXX_Init(void)
 {
    IIC_Init();
 }

 // 在AT24CXX指定地址读出一个数据
 // Addr:开始读数的地址
 // 返回值  :读到的数据
 u8 AT24C_Rcvone(u8 Addr)
 {
    u8 temp = 0;
    Start_I2c();    // 启动总线
    SendByte(0xa0); // 发送写命令
    I2c_wait_ack(); // 等待应答
    SendByte(Addr); // 发送地址
    I2c_wait_ack(); // 等待应答

    Start_I2c();    // 重新启动总线
    SendByte(0xa1); // 设置为读操作
    I2c_wait_ack(); // 等待应答;

    temp = RcvByte(0); // 读字节	非应答

    Stop_I2c(); // 结束总线
    return temp;
 }

 // 在AT24CXX指定地址写入一个数据	 此函数只限于 c02-c16
 // Addr:写入数据的目的地址
 // Data:要写入的数据
 void AT24C_Sendone(u8 Addr, u8 Data)
 {
    Start_I2c(); // 启动总线

    SendByte(0xa0); // 发送写命令
    I2c_wait_ack(); // 等待应答
    SendByte(Addr); // 发送地址
    I2c_wait_ack(); // 等待应答
    SendByte(Data); // 发送字节数据
    I2c_wait_ack(); // 等待应答
    Stop_I2c();     // 结束总线
    delay_ms(10);   // 如果是连续发送字节的时候这个延时很重要 否则将回传错
 }

 // 在AT24CXX里面的指定地址开始写入长度为Len的数据
 // 该函数用于写入16bit或者32bit的数据.
 // Addr  :开始写入的地址
 // Data  :数据数组首地址
 // Len   :要写入数据的长度2,4
 void AT24C_SendLenByte(u8 Addr, u8 *Data, u8 Len)
 {
    while (Len--)
    {
       AT24C_Sendone(Addr, *Data);
       Addr++;
       Data++;
    }
 }

 // 在AT24CXX里面的指定地址开始读出长度为Len的数据
 // 该函数用于读出16bit或者32bit的数据.
 // Addr   :开始读出的地址
 // 返回值     :数据
 // Len        :要读出数据的长度2,4
 void AT24C_RcvLenByte(u8 Addr, u8 *temp, u8 Len)
 {

    while (Len)
    {
       *temp++ = AT24C_Rcvone(Addr++);
       Len--;
    }
 }

 ////24c04 读写函数
 ////作用  按3.3 字母数据+1  按1.2保存当前显示的数据  按5.0 显示24c里保存的数据
 // void c02()
 //{
 //   struct TFT_Pointer Tp_pix;	   //定义触摸变量结构体
 //
 //   u8 Count1=65,Count2=65,   //字母初始值为大写字母A
 //      pd; 				    //存入 读取变量
 //
 //   GUI_Clear(White);	       //清屏
 //   tian(1);                 //上下框填充
 //
 //	GUI_sprintf_hzstr16x(0,0,"24C02芯片单字节存读测试",White,1);    //显示说明
 //	GUI_sprintf_hzstr16x(0,84 ,"读取值:   <<读取时LED灭",Blue,White);
 //	GUI_sprintf_hzstr16x(0,100,"保存值:   <<保存时LED亮",Blue,White);
 //
 //	GUI_box(0,180,239,183,Blue1);
 //	GUI_sprintf_hzstr16x(0,184,"按键说明：",Red,White);
 //	GUI_sprintf_hzstr16x(0,200,"保存:P33",Black,White);
 //	GUI_sprintf_hzstr16x(0,217,"读取:P14",Black,White);
 //     GUI_sprintf_hzstr16x(0,234,"加一:任意触摸",Black,White);
 //
 //  while(1)
 //   {
 //     Tp_pix=TFT_Cm();	                 // 扫描触摸屏
 //
 //     if(Tp_pix.flag==1)                   //是否有触摸事件 发送
 //     {
 //
 //       if(Tp_pix.y>=0&&Tp_pix.y<=299) 	 //只要在0-299区域触摸屏任意位置有按下 立即反应
 //	  {
 //		Count1++; 				         //预存储值增加
 //		delay1ms(100);	  				 //降低变化速度
 //	  }
 //
 //  	  if(Tp_pix.x>200&&Tp_pix.x<239&&Tp_pix.y>295&&Tp_pix.y<320){Return(); led=1; break;}	 //返回主菜单
 //   	}
 //
 //	  //=========================读取
 //     if(P14==0)	        //屏下主按键   读取E2 0地址位 的一个字节 到pd中
 //	 {
 //		led=1;	 		//指示灯 灭 提示 读取成功
 //         pd=AT24C_Rcvone(0);    //选择要读取的地址  然后将读取的数据存入变量pd中 1读出1个字节到存入的指定变量
 //		Count1=pd ;		//将读取值存入临时变量中
 //		Count2=pd ;
 //	 }
 //
 //	  //========================IIC 保存
 //	if(key33==0)    //板子侧按键 小龟
 //      {
 //		led=0;			//指示灯 灭 提示 保存成功
 //		pd=Count1;		//将预存储Count1中的值给变量pd
 //		AT24C_Sendone(0,pd);	//将pd的值存入  0地址位置 存入量为1字节
 //      }
 //	//更新显示
 //     GUI_sprintf_char(60,84,Count1,0xf800,0xffff,0); //显示读取出来的值
 //     GUI_sprintf_char(60,100,Count2,0xf800,0xffff,0);//显示保存进去的值
 //
 //   }
 // }
 //
 //
