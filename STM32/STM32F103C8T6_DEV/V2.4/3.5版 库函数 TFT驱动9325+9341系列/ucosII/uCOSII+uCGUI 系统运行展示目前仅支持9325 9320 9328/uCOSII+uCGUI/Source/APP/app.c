

/* 

  http://zq281598585.taobao.com/  
  启光电子	  ELH    enlighten  sunny
  STM32F103RBT6 开发板 库函数部分	  


  STM32 ucosII+ucgui  效果显示程序

  采用的TFT为9325TFT
  	   用到的GPIO  PB为数据口	  CS PC.8    RS PC.9    WR PC.10     RD PA.15	  RES 采用系统复位

  此程序为网络参考程序改编  如有不明白地方 请参考资料中的关于UCOS的参考资料

*/






/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-EVAL Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : Brian Nagel
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/* ----------------- APPLICATION GLOBALS ------------------ */
static OS_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
static OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
static OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];

//static  OS_EVENT       *AppUserIFMbox;

int ExTick;

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void AppTaskCreate(void);
static void AppTaskStart(void *p_arg);

static void AppTaskUserIF(void *p_arg);
static void AppTaskKbd(void *p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

void MainTask(void);

int  main (void)
{
    INT8U  err;
	  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   

  //  BSP_IntDisAll();                   /* Disable all interrupts until we are ready to accept them */

    OSInit();                          /* Initialize "uC/OS-II, The Real-Time Kernel"              */

   /* Create the start task */
OSTaskCreateExt(AppTaskStart,(void *)0,(OS_STK *)&AppTaskStartStk[APP_TASK_START_STK_SIZE-1],APP_TASK_START_PRIO,APP_TASK_START_PRIO,(OS_STK *)&AppTaskStartStk[0],APP_TASK_START_STK_SIZE,(void *)0,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 13)
    OSTaskNameSet(APP_TASK_START_PRIO, "Start Task", &err);
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
  (void)p_arg;

   BSP_Init();                                                 /* Initialize BSP functions                                 */
   #if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                                   */
   #endif

//   AppUserIFMbox = OSMboxCreate((void *)0);                  /* Create MBOX for communication between Kbd and UserIF     */
   AppTaskCreate();                                            /* Create application tasks                                 */
    
   while(DEF_TRUE)
	 {  
	  /* Task body, always written as an infinite loop. */
	   OSTaskSuspend(OS_PRIO_SELF);
	 //OSTimeDlyHMSM(0,0,0,200); 
	// GPIO_SetBits(GPIOC,GPIO_Pin_6);
	 //OSTimeDlyHMSM(0,0,0,200);
	// GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	  /* ExTick=TPReadY();
	   GUI_DispDecAt(ExTick,20,40,4);
	  */
	  
     }
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppTaskCreate(void)
{
  INT8U  err;

  OSTaskCreateExt(AppTaskUserIF,(void *)0,(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],APP_TASK_USER_IF_PRIO,APP_TASK_USER_IF_PRIO,(OS_STK *)&AppTaskUserIFStk[0],
                    APP_TASK_USER_IF_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);


#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_USER_IF_PRIO, "User I/F", &err);
#endif


  OSTaskCreateExt(AppTaskKbd,(void *)0,(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],APP_TASK_KBD_PRIO,APP_TASK_KBD_PRIO,(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 8)
  OSTaskNameSet(APP_TASK_KBD_PRIO, "Keyboard", &err);
#endif
}


/*
*********************************************************************************************************
*                                         USER INTERFACE TASK
*
* Description : This task updates the LCD screen based on messages passed to it by AppTaskKbd().
*
* Arguments   : p_arg   is the argument passed to 'AppStartUserIF()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

static  void  AppTaskUserIF (void *p_arg)
{
 
 (void)p_arg;
  // GUI_Init();
  while(DEF_TRUE) 
    {
	  MainTask(); 
//	  GUIDEMO_Touch();
    }
}


/*
*********************************************************************************************************
*                                    KEYBOARD RESPONSE TASK
*
* Description : This task monitors the state of the push buttons and passes messages to AppTaskUserIF()
*
* Arguments   : p_arg   is the argument passed to 'AppStartKbd()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

static  void  AppTaskKbd (void *p_arg)		//指示灯闪烁
{
   u8 tick=0;
  (void)p_arg;
   while(DEF_TRUE) 
     {
	 	tick++;
        OSTimeDlyHMSM(0,0,0,100); 
//	   GUI_TOUCH_Exec(); 
		if(tick&0x10)
		{
		    GPIO_SetBits(GPIOA,GPIO_Pin_1);

		}
		else
		{
		 	GPIO_ResetBits(GPIOA,GPIO_Pin_1);

		}
	   ;
	   /*	 
	 OSTimeDlyHMSM(0,0,0,500);
	  */
     }
}
