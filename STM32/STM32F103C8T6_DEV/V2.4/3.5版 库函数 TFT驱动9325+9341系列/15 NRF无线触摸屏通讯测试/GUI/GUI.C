


#include  "stm32f10x.h"
#include  "delay.h"
#include  "tft.h"
#include  "zifu8x16.h"
#include  "gui.h"




//清屏
//color是背景颜色。
//说明：使用背景颜色清除TFT模块屏幕的全部显示内容。
void GUI_Clear(u16 color)
{
	u16 i;
	u8 j;
	Address_set(0,0,239,319,0,0);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 Lcd_Write_Data(color);
	    }

	  }
}



//画点
//(x，y)是点的坐标
//color 是点的颜色。
//说明：用指定的颜色在指定的坐标位置上画出一个点。
void GUI_Point(u8 x, u16 y, u16 color)
{  
	Address_set(x,y,x,y,x,y);
	Lcd_Write_Data(color);
}

   

////画直线（可以画任意方向直线，包括横线、竖线、斜线）。
////(x1,y1)起点, (x2,y2)终点, color颜色。
////说明：用指定的颜色在指定的两点间画出一条直线。
//void GUI_line(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)  
//{  
//    u16 t;  
//    int xerr=0,yerr=0,delta_x,delta_y,distance;  
//    int incx,incy;  
//    u16 row,col;  
//    delta_x = x2-x1;//计算坐标增量  
//    delta_y = y2-y1;  
//    col=x1;  
//    row=y1;  
//    if(delta_x>0) incx=1;//设置单步方向  
//    else   
//    {  
//        if(delta_x==0) incx=0;//垂直线  
//        else {incx=-1;delta_x=-delta_x;}  
//    }  
//    if(delta_y>0)incy=1;  
//    else  
//    {  
//        if(delta_y==0) incy=0;//水平线  
//        else {incy=-1;delta_y=-delta_y;}  
//    }  
//    if(delta_x>delta_y) distance=delta_x;//选取基本增量坐标轴  
//    else distance=delta_y;  
//
//    for(t=0;t<=distance+1;t++)  
//	{                                     //画线输出  
//	    GUI_Point(col, row, color);
//        xerr+=delta_x;  
//        yerr+=delta_y;  
//      	if(xerr>distance)  
//        {  
//            xerr-=distance;  
//            col+=incx;  
//        }  
//        if(yerr>distance)  
//        {  
//            yerr-=distance;  
//            row+=incy;  
//        }  
//    }  
//}




//画8点(Bresenham算法)		  
//(rx,ry,a,b):参数
//color:颜色
void gui_circle8(u16 rx,u16 ry,int a,int b,u16 color)
{
	GUI_Point(rx+a,ry-b,color);              
	GUI_Point(rx+b,ry-a,color);                       
	GUI_Point(rx+b,ry+a,color);                           
	GUI_Point(rx+a,ry+b,color);             
	GUI_Point(rx-a,ry+b,color);                  
	GUI_Point(rx-b,ry+a,color);               
	GUI_Point(rx-b,ry-a,color);                      
	GUI_Point(rx-a,ry-b,color);                  
}
//在指定位置画一个指定大小的圆
//(rx,ry):圆心
//r    :半径
//color:颜色
//mode :0,不填充;1,填充
void GUI_arc(u16 rx,u16 ry,u16 r,u16 color,u8 mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//判断下个点位置的标志
	while(a<=b)
	{
		if(mode)
		for(c=a;c<=b;c++)
		gui_circle8(rx,ry,a,c,color);//画实心圆
 		else gui_circle8(rx,ry,a,b,color);			//画空心圆
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}

//画实心矩形
//(sx,sy)左上角顶点坐标, 
//(ex,ey)右下角顶点坐标, color颜色
//返回: 无
//说明：在指定位置上画出实心矩形。
void GUI_box(u8 sx,u16 sy,u8 ex,u16 ey,u16 color)
{ 
	u16 temp,temp1,m,n;   
	Address_set(sx,sy,ex,ey,sx,sy); 
    n=ex-sx+1;
	m=ey-sy+1;

	for(temp=0;temp<m;temp++)
	{	 	
		for(temp1=0;temp1<n;temp1++)
	 	{	
			Lcd_Write_Data(color);
		}
	}
}


////画颜色递变巨型  可以是横条 竖条等
////(sx,sy)左上角顶点坐标, 
////(ex,ey)右下角顶点坐标, color颜色
//// mode 模式  mode=1  纵向颜色变化 mode=2 横向颜色变化
//void GUI_boxchange(u8 sx,u16 sy,u8 ex,u16 ey,u16 color,u8 mode)
//{ 
//	u16 temp,temp1,m,n,color2;   
//	Address_set(sx,sy,ex,ey); 
//    n=ex-sx+1;
//	m=ey-sy+1;
//	if(mode==2)color2=color;
//	for(temp=0;temp<m;temp++)
//	{	 	
//		for(temp1=0;temp1<n;temp1++)
//	 	{	
//			Lcd_Write_Data(color);
//			if(mode==2)color+=15;
//		}
//		if(mode==1)color+=15;
//		if(mode==2)color=color2;
//	}
//}



//填充矩形
//x0,y0:矩形的左上角坐标
//width,height:矩形的尺寸
//color:颜色
void GUI_fill_box(u16 x0,u16 y0,u16 width,u16 height,u16 color)
{	  							   
	if(width==0||height==0)return;//非法.	 
	GUI_box(x0,y0,x0+width-1,y0+height-1,color);	   	   
}











//显示英文或数字字符
//函数支持 字符的纵向和横向显示 （要配合扫描方式）
//         支持忽略背景颜色显示 （横向没有开此功能）
//x  y  要显示字符的初始坐标
//value 显示字符数据
//dcolor 显示的字符颜色  bgcolor显示字符的背景颜色
//                       bgcolor 只给1 说明背景颜色使用 当前屏幕颜色（只适用于纵向显示）
//mode   0 字符纵向显示  1 字符横向显示
void GUI_sprintf_char(u8 x,u16 y,u8 value,u16 dcolor,u16 bgcolor,u8 mode)	
{  
	u8 i,j;
	u8 *temp=(u8 *)zifu816;    //temp是*temp的地址  这里temp就是zifu的首地址 
    u8 ma;  
	                    
	temp+=(value-32)*16;   //确定要显示的值
				           //用ascii表  前32个ascii没有存入zifu库里 所以要减32
	                       //每个字符用16个字节显示 所以在乘以16  就是对应的显示位的首地址

    if(bgcolor!=1)		   //用自己设定的背景色
	 {											   //注意 不管设置哪一显示方向 前提是扫描要对应
	  if(mode==0)Address_set(x,y,x+7,y+15,x,y);    //设置区域		   
	  if(mode==1)Address_set(x,y,x+15,y+7,x+15,y); //设置区域   
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //先横扫
			{ 		     
			 	if((*temp&(1<<(7-i)))!=0)		   //将1 左移 然后对应位进行相与 				
				  Lcd_Write_Data(dcolor);		   //显示字符颜色
				 
				else				
				  Lcd_Write_Data(bgcolor);		   //显示背景颜色		
			}
			temp++;								   //下一字节
		 }
	  }
	else				  //用屏幕上自有的颜色做背景色 （只支持纵向显示）
	 {	
	    ma=x;			  //赋值x的初始值给ma 
		for(j=0;j<16;j++)
		{
			for(i=0;i<8;i++)		    //先横扫
			{ 
			    Address_set(x,y,x,y,x,y);
			 	if((*temp&(1<<(7-i)))!=0)	//将1 左移 然后对应位进行相与 
				{
				   Lcd_Write_Data(dcolor);	//显示字符颜色
				   x++;
				   if((x-ma)==8){x=ma;y++;}	//判断是否到一行
				} 
				else
				{
				   x++;						//没有要显示的数据 x自加跳过
				   if((x-ma)==8){x=ma;y++;}	//判断是否到一行
				} 
			}
			temp++;							//下一字节
		}		 			  
	 } 

}



//显示汉字及字符  纵向显示
//x1 y1 显示的初始位置
//*str 要显示的数据
//dcolor 显示汉字 字符的颜色
//bgcolor 显示汉字 字符的背景颜色  当bgcolor=1是 那么背景颜色为屏幕自有颜色
void GUI_sprintf_hzstr16x(u8 x1,u16 y1,u8 *str,u16 dcolor,u16 bgcolor)	  
{  
	 u8 l=0;
	while(*str)
	{	
	  if(*str<0x80)		  //小于128   ascii 都在数组内
	  {	  
		GUI_sprintf_char(x1+l*8,y1,*str,dcolor,bgcolor,0);
		l+=1;
		str++;
		}
//	  else
//	  {	  
//	   PutGB1616(x1+l*8,y1,(u8*)str,dcolor, bgcolor,0);
//			str+=2;l+=2;
//	  }
	}	
}





//显示最大5位的数据  如果非5位状态 其他位不显示 只显示有效值
//支持功能 如果背景颜色 为1 那么不显示背景颜色 背景颜色为写入前默认值
// x y 显示数值坐标  
//dat 数值
//dcolor  显示数值颜色  bgcolor背景颜色
void number(u8 x,u16 y,u32 dat,u16 dcolor,u16 bgcolor)				//坐标 要显示的数据	   跟踪程序数据用
{
 u8 take[5];
 u8 i,m;

 take[0]=dat/10000%10;
 take[1]=dat/1000%10;
 take[2]=dat/100%10;
 take[3]=dat/10%10;
 take[4]=dat%10;

							  //显示位数
 if(dat/10000)m=5;			  //万位
 else if(dat/1000)m=4;		  //千位
 else if(dat/100)m=3;		  //百位
 else if(dat/10)m=2;		  //十位
 else if(dat/1)m=1;			  //个位
 else if(dat==0)m=1;		  //如果读出来的值就是0 直接用一位表示

 for(i=0;i<m;i++)			  //显示
  GUI_sprintf_char(x+i*8,y,take[5-m+i]+'0',dcolor,bgcolor,0);			  //+'0'表示转换为ACCII码

}




//只显示10位数据
void number10(u8 x,u16 y,u16 dat,u16 dcolor,u16 bgcolor)	//坐标 要显示的数据	 
{

   GUI_sprintf_char(x,y,dat/10%10+'0',dcolor,bgcolor,0);
   GUI_sprintf_char(x+8,y,dat%10+'0',dcolor,bgcolor,0); 
}




















