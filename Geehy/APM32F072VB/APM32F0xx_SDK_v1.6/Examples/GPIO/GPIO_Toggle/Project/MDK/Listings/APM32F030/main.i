# 1 "../../Source/main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 365 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../Source/main.c" 2
# 26 "../../Source/main.c"
# 1 "../../../../../Board\\Board.h" 1
# 34 "../../../../../Board\\Board.h"
# 1 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h" 1
# 33 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h"
# 1 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h" 1
# 117 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h"
typedef enum
{

    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,
    SVC_IRQn = -5,
    PendSV_IRQn = -2,
    SysTick_IRQn = -1,



    WWDT_IRQn = 0,
    RTC_IRQn = 2,
    FLASH_IRQn = 3,
    RCM_IRQn = 4,
    EINT0_1_IRQn = 5,
    EINT2_3_IRQn = 6,
    EINT4_15_IRQn = 7,
    DMA1_CH1_IRQn = 9,
    DMA1_CH2_3_IRQn = 10,
    DMA1_CH4_5_IRQn = 11,
    ADC1_IRQn = 12,
    TMR1_BRK_UP_TRG_COM_IRQn = 13,
    TMR1_CC_IRQn = 14,
    TMR3_IRQn = 16,
    TMR6_IRQn = 17,
    TMR7_IRQn = 18,
    TMR14_IRQn = 19,
    TMR15_IRQn = 20,
    TMR16_IRQn = 21,
    TMR17_IRQn = 22,
    I2C1_IRQn = 23,
    I2C2_IRQn = 24,
    SPI1_IRQn = 25,
    SPI2_IRQn = 26,
    USART1_IRQn = 27,
    USART2_IRQn = 28,
    USART3_6_IRQn = 29
# 317 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h"
} IRQn_Type;


# 1 "../../../../../Library/CMSIS/Include\\core_cm0plus.h" 1
# 126 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 127 "../../../../../Library/CMSIS/Include\\core_cm0plus.h" 2
# 1 "../../../../../Library/CMSIS/Include\\core_cmInstr.h" 1
# 325 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline void __NOP(void)
{
  __asm volatile ("nop");
}







__attribute__( ( always_inline ) ) static inline void __WFI(void)
{
  __asm volatile ("wfi");
}







__attribute__( ( always_inline ) ) static inline void __WFE(void)
{
  __asm volatile ("wfe");
}






__attribute__( ( always_inline ) ) static inline void __SEV(void)
{
  __asm volatile ("sev");
}
# 369 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline void __ISB(void)
{
  __asm volatile ("isb");
}







__attribute__( ( always_inline ) ) static inline void __DSB(void)
{
  __asm volatile ("dsb");
}







__attribute__( ( always_inline ) ) static inline void __DMB(void)
{
  __asm volatile ("dmb");
}
# 404 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __REV(uint32_t value)
{



  uint32_t result;

  __asm volatile ("rev %0, %1" : "=l" (result) : "l" (value) );
  return(result);

}
# 424 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __asm volatile ("rev16 %0, %1" : "=l" (result) : "l" (value) );
  return(result);
}
# 440 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline int32_t __REVSH(int32_t value)
{



  uint32_t result;

  __asm volatile ("revsh %0, %1" : "=l" (result) : "l" (value) );
  return(result);

}
# 461 "../../../../../Library/CMSIS/Include\\core_cmInstr.h"
__attribute__( ( always_inline ) ) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  return (op1 >> op2) | (op1 << (32 - op2));
}
# 128 "../../../../../Library/CMSIS/Include\\core_cm0plus.h" 2
# 1 "../../../../../Library/CMSIS/Include\\core_cmFunc.h" 1
# 329 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}







__attribute__( ( always_inline ) ) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 352 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 367 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
}
# 379 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}
# 394 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}
# 409 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}
# 424 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_PSP(void)
{
  register uint32_t result;

  __asm volatile ("MRS %0, psp\n" : "=r" (result) );
  return(result);
}
# 439 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0\n" : : "r" (topOfProcStack) : "sp");
}
# 451 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_MSP(void)
{
  register uint32_t result;

  __asm volatile ("MRS %0, msp\n" : "=r" (result) );
  return(result);
}
# 466 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0\n" : : "r" (topOfMainStack) : "sp");
}
# 478 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 493 "../../../../../Library/CMSIS/Include\\core_cmFunc.h"
__attribute__( ( always_inline ) ) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 129 "../../../../../Library/CMSIS/Include\\core_cm0plus.h" 2
# 206 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
typedef union
{
  struct
  {

    uint32_t _reserved0:27;





    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;




typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;




typedef union
{
  struct
  {
    uint32_t ISR:9;

    uint32_t _reserved0:15;





    uint32_t T:1;
    uint32_t IT:2;
    uint32_t Q:1;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;




typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t FPCA:1;
    uint32_t _reserved0:29;
  } b;
  uint32_t w;
} CONTROL_Type;
# 291 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
typedef struct
{
  volatile uint32_t ISER[1];
       uint32_t RESERVED0[31];
  volatile uint32_t ICER[1];
       uint32_t RSERVED1[31];
  volatile uint32_t ISPR[1];
       uint32_t RESERVED2[31];
  volatile uint32_t ICPR[1];
       uint32_t RESERVED3[31];
       uint32_t RESERVED4[64];
  volatile uint32_t IP[8];
} NVIC_Type;
# 316 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;

  volatile uint32_t VTOR;



  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
       uint32_t RESERVED1;
  volatile uint32_t SHP[2];
  volatile uint32_t SHCSR;
} SCB_Type;
# 431 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 626 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 638 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 654 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}
# 666 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 678 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[0] = (1 << ((uint32_t)(IRQn) & 0x1F));
}
# 693 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] = (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
  else {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] = (((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[( ((uint32_t)(IRQn) >> 2) )] & ~(0xFF << ( (((uint32_t)(IRQn) ) & 0x03) * 8 ))) |
        (((priority << (8 - 2)) & 0xFF) << ( (((uint32_t)(IRQn) ) & 0x03) * 8 )); }
}
# 715 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[( ((((uint32_t)(IRQn) & 0x0F)-8) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) & 0xFF) >> (8 - 2))); }
  else {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[ ( ((uint32_t)(IRQn) >> 2) )] >> ( (((uint32_t)(IRQn) ) & 0x03) * 8 ) ) & 0xFF) >> (8 - 2))); }
}






static inline void NVIC_SystemReset(void)
{
  __DSB();

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = ((0x5FA << 16) |
                 (1UL << 2));
  __DSB();
  while(1);
}
# 767 "../../../../../Library/CMSIS/Include\\core_cm0plus.h"
static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1) > (0xFFFFFFUL << 0)) return (1);

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = ticks - 1;
  NVIC_SetPriority (SysTick_IRQn, (1<<2) - 1);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2) |
                   (1UL << 1) |
                   (1UL << 0);
  return (0);
}
# 321 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h" 2
# 1 "../../../../../Library/Device/Geehy/APM32F0xx/Include/system_apm32f0xx.h" 1
# 36 "../../../../../Library/Device/Geehy/APM32F0xx/Include/system_apm32f0xx.h"
extern uint32_t SystemCoreClock;

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
# 322 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h" 2


typedef enum {FALSE, TRUE} BOOL;

enum {BIT_RESET, BIT_SET};

enum {RESET = 0, SET = !RESET};

enum {DISABLE = 0, ENABLE = !DISABLE};

enum {ERROR = 0, SUCCESS = !ERROR};
# 360 "../../../../../Library/Device/Geehy/APM32F0xx/Include\\apm32f0xx.h"
typedef struct
{

    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t ADCRDYFLG : 1;
            volatile uint32_t EOSMPFLG : 1;
            volatile uint32_t EOCFLG : 1;
            volatile uint32_t EOSEQFLG : 1;
            volatile uint32_t OVREFLG : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t AWDFLG : 1;
            volatile const uint32_t RESERVED2 : 24;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t INT;

        struct
        {
            volatile uint32_t ADCRDYIEN : 1;
            volatile uint32_t EOSMPIEN : 1;
            volatile uint32_t EOCIEN : 1;
            volatile uint32_t EOSEQIEN : 1;
            volatile uint32_t OVRIEN : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t AWDIEN : 1;
            volatile const uint32_t RESERVED2 : 24;
        } INT_B;
    } ;


    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t ADCEN : 1;
            volatile uint32_t ADCD : 1;
            volatile uint32_t STARTCEN : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t STOPCEN : 1;
            volatile const uint32_t RESERVED2 : 26;
            volatile uint32_t CAL : 1;
        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t DMAEN : 1;
            volatile uint32_t DMACFG : 1;
            volatile uint32_t SCANSEQDIR : 1;
            volatile uint32_t DATARESCFG : 2;
            volatile uint32_t DALIGCFG : 1;
            volatile uint32_t EXTTRGSEL : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t EXTPOLSEL : 2;
            volatile uint32_t OVRMAG : 1;
            volatile uint32_t CMODESEL : 1;
            volatile uint32_t WAITCEN : 1;
            volatile uint32_t AOEN : 1;
            volatile uint32_t DISCEN : 1;
            volatile const uint32_t RESERVED2 : 5;
            volatile uint32_t AWDCHEN : 1;
            volatile uint32_t AWDEN : 1;
            volatile const uint32_t RESERVED3 : 2;
            volatile uint32_t AWDCHSEL : 5;
            volatile const uint32_t RESERVED4 : 1;
        } CFG1_B;
    } ;


    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile const uint32_t RESERVED1 : 30;
            volatile uint32_t CLKCFG : 2;
        } CFG2_B;
    } ;


    union
    {
        volatile uint32_t SMPTIM;

        struct
        {
            volatile uint32_t SMPCYCSEL : 3;
            volatile const uint32_t RESERVED1 : 29;
        } SMPTIM_B;
    } ;
    volatile const uint32_t RESERVED[2];


    union
    {
        volatile uint32_t AWDT;

        struct
        {
            volatile uint32_t AWDLT : 12;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t AWDHT : 12;
            volatile const uint32_t RESERVED2 : 4;
        } AWDT_B;
    } ;
    volatile const uint32_t RESERVED1;


    union
    {
        volatile uint32_t CHSEL;

        struct
        {
            volatile uint32_t CH0SEL : 1;
            volatile uint32_t CH1SEL : 1;
            volatile uint32_t CH2SEL : 1;
            volatile uint32_t CH3SEL : 1;
            volatile uint32_t CH4SEL : 1;
            volatile uint32_t CH5SEL : 1;
            volatile uint32_t CH6SEL : 1;
            volatile uint32_t CH7SEL : 1;
            volatile uint32_t CH8SEL : 1;
            volatile uint32_t CH9SEL : 1;
            volatile uint32_t CH10SEL : 1;
            volatile uint32_t CH11SEL : 1;
            volatile uint32_t CH12SEL : 1;
            volatile uint32_t CH13SEL : 1;
            volatile uint32_t CH14SEL : 1;
            volatile uint32_t CH15SEL : 1;
            volatile uint32_t CH16SEL : 1;
            volatile uint32_t CH17SEL : 1;
            volatile uint32_t CH18SEL : 1;
            volatile const uint32_t RESERVED1 : 13;
        } CHSEL_B;
    } ;
    volatile const uint32_t RESERVED2[5];


    union
    {
        volatile const uint32_t DATA;

        struct
        {
            volatile const uint32_t DATA : 16;
            volatile const uint32_t RESERVED1 : 16;
        } DATA_B;
    } ;
    volatile const uint32_t RESERVED3[177];


    union
    {
        volatile uint32_t CCFG;

        struct
        {
            volatile const uint32_t RESERVED1 : 22;
            volatile uint32_t VREFEN : 1;
            volatile uint32_t TSEN : 1;
            volatile uint32_t VBATEN : 1;
            volatile const uint32_t RESERVED2 : 7;
        } CCFG_B;
    } ;
} ADC_T;




typedef struct
{

    union
    {
        volatile uint32_t TXMID;

        struct
        {
            volatile uint32_t TXMREQ : 1;
            volatile uint32_t TXRFREQ : 1;
            volatile uint32_t IDTYPESEL : 1;
            volatile uint32_t EXTID : 18;
            volatile uint32_t STDID : 11;
        } TXMID_B;
    } ;


    union
    {
        volatile uint32_t TXDLEN;

        struct
        {
            volatile uint32_t DLCODE : 4;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t TXGT : 1;
            volatile const uint32_t RESERVED2 : 7;
            volatile uint32_t MTS : 16;
        } TXDLEN_B;
    } ;


    union
    {
        volatile uint32_t TXMDL;

        struct
        {
            volatile uint32_t DATABYTE0 : 8;
            volatile uint32_t DATABYTE1 : 8;
            volatile uint32_t DATABYTE2 : 8;
            volatile uint32_t DATABYTE3 : 8;
        } TXMDL_B;
    } ;


    union
    {
        volatile uint32_t TXMDH;

        struct
        {
            volatile uint32_t DATABYTE4 : 8;
            volatile uint32_t DATABYTE5 : 8;
            volatile uint32_t DATABYTE6 : 8;
            volatile uint32_t DATABYTE7 : 8;
        } TXMDH_B;
    } ;

} CAN_TxMailBox_T;




typedef struct
{

    union
    {
        volatile const uint32_t RXMID;

        struct
        {
            volatile const uint32_t RESERVED1 : 1;
            volatile const uint32_t RFTXREQ : 1;
            volatile const uint32_t IDTYPESEL : 1;
            volatile const uint32_t EXTID : 18;
            volatile const uint32_t STDID : 11;
        } RXMID_B;
    } ;


    union
    {
        volatile const uint32_t RXDLEN;

        struct
        {
            volatile const uint32_t DLCODE : 4;
            volatile const uint32_t RESERVED1 : 4;
            volatile const uint32_t FMIDX : 8;
            volatile const uint32_t MTS : 16;
        } RXDLEN_B;
    } ;


    union
    {
        volatile const uint32_t RXMDL;

        struct
        {
            volatile const uint32_t DATABYTE0 : 8;
            volatile const uint32_t DATABYTE1 : 8;
            volatile const uint32_t DATABYTE2 : 8;
            volatile const uint32_t DATABYTE3 : 8;
        } RXMDL_B;
    } ;


    union
    {
        volatile const uint32_t RXMDH;

        struct
        {
            volatile const uint32_t DATABYTE4 : 8;
            volatile const uint32_t DATABYTE5 : 8;
            volatile const uint32_t DATABYTE6 : 8;
            volatile const uint32_t DATABYTE7 : 8;
        } RXMDH_B;
    } ;

} CAN_RxFIFO_T;




typedef struct
{

    union
    {
        volatile uint32_t R1;

        struct
        {
            volatile uint32_t FBIT0 : 1;
            volatile uint32_t FBIT1 : 1;
            volatile uint32_t FBIT2 : 1;
            volatile uint32_t FBIT3 : 1;
            volatile uint32_t FBIT4 : 1;
            volatile uint32_t FBIT5 : 1;
            volatile uint32_t FBIT6 : 1;
            volatile uint32_t FBIT7 : 1;
            volatile uint32_t FBIT8 : 1;
            volatile uint32_t FBIT9 : 1;
            volatile uint32_t FBIT10 : 1;
            volatile uint32_t FBIT11 : 1;
            volatile uint32_t FBIT12 : 1;
            volatile uint32_t FBIT13 : 1;
            volatile uint32_t FBIT14 : 1;
            volatile uint32_t FBIT15 : 1;
            volatile uint32_t FBIT16 : 1;
            volatile uint32_t FBIT17 : 1;
            volatile uint32_t FBIT18 : 1;
            volatile uint32_t FBIT19 : 1;
            volatile uint32_t FBIT20 : 1;
            volatile uint32_t FBIT21 : 1;
            volatile uint32_t FBIT22 : 1;
            volatile uint32_t FBIT23 : 1;
            volatile uint32_t FBIT24 : 1;
            volatile uint32_t FBIT25 : 1;
            volatile uint32_t FBIT26 : 1;
            volatile uint32_t FBIT27 : 1;
            volatile uint32_t FBIT28 : 1;
            volatile uint32_t FBIT29 : 1;
            volatile uint32_t FBIT30 : 1;
            volatile uint32_t FBIT31 : 1;
        } R1_B;
    };


    union
    {
        volatile uint32_t R2;

        struct
        {
            volatile uint32_t FBIT0 : 1;
            volatile uint32_t FBIT1 : 1;
            volatile uint32_t FBIT2 : 1;
            volatile uint32_t FBIT3 : 1;
            volatile uint32_t FBIT4 : 1;
            volatile uint32_t FBIT5 : 1;
            volatile uint32_t FBIT6 : 1;
            volatile uint32_t FBIT7 : 1;
            volatile uint32_t FBIT8 : 1;
            volatile uint32_t FBIT9 : 1;
            volatile uint32_t FBIT10 : 1;
            volatile uint32_t FBIT11 : 1;
            volatile uint32_t FBIT12 : 1;
            volatile uint32_t FBIT13 : 1;
            volatile uint32_t FBIT14 : 1;
            volatile uint32_t FBIT15 : 1;
            volatile uint32_t FBIT16 : 1;
            volatile uint32_t FBIT17 : 1;
            volatile uint32_t FBIT18 : 1;
            volatile uint32_t FBIT19 : 1;
            volatile uint32_t FBIT20 : 1;
            volatile uint32_t FBIT21 : 1;
            volatile uint32_t FBIT22 : 1;
            volatile uint32_t FBIT23 : 1;
            volatile uint32_t FBIT24 : 1;
            volatile uint32_t FBIT25 : 1;
            volatile uint32_t FBIT26 : 1;
            volatile uint32_t FBIT27 : 1;
            volatile uint32_t FBIT28 : 1;
            volatile uint32_t FBIT29 : 1;
            volatile uint32_t FBIT30 : 1;
            volatile uint32_t FBIT31 : 1;
        } R2_B;
    };
} CAN_FilterRegister_T;





typedef struct
{

    union
    {
        volatile uint32_t MCTRL;

        struct
        {
            volatile uint32_t INITREQ : 1;
            volatile uint32_t SLEEPREQ : 1;
            volatile uint32_t TXFPCFG : 1;
            volatile uint32_t RXFLOCK : 1;
            volatile uint32_t ARTXMD : 1;
            volatile uint32_t AWUPCFG : 1;
            volatile uint32_t ALBOFFM : 1;
            volatile uint32_t TTCM : 1;
            volatile const uint32_t RESERVED1 : 7;
            volatile uint32_t SWRST : 1;
            volatile uint32_t DBGFRZE : 1;
            volatile const uint32_t RESERVED2 : 15;
        } MCTRL_B;
    } ;


    union
    {
        volatile uint32_t MSTS;

        struct
        {
            volatile const uint32_t INITFLG : 1;
            volatile const uint32_t SLEEPFLG : 1;
            volatile uint32_t ERRIFLG : 1;
            volatile uint32_t WUPIFLG : 1;
            volatile uint32_t SLEEPIFLG : 1;
            volatile const uint32_t RESERVED1 : 3;
            volatile const uint32_t TXMFLG : 1;
            volatile const uint32_t RXMFLG : 1;
            volatile const uint32_t LSAMVALUE : 1;
            volatile const uint32_t RXSIGL : 1;
            volatile const uint32_t RESERVED2 : 20;
        } MSTS_B;
    } ;


    union
    {
        volatile uint32_t TXSTS;

        struct
        {
            volatile uint32_t REQCFLG0 : 1;
            volatile uint32_t TXSUSFLG0 : 1;
            volatile uint32_t ARBLSTFLG0 : 1;
            volatile uint32_t TXERRFLG0 : 1;
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t ABREQFLG0 : 1;
            volatile uint32_t REQCFLG1 : 1;
            volatile uint32_t TXSUSFLG1 : 1;
            volatile uint32_t ARBLSTFLG1 : 1;
            volatile uint32_t TXERRFLG1 : 1;
            volatile const uint32_t RESERVED2 : 3;
            volatile uint32_t ABREQFLG1 : 1;
            volatile uint32_t REQCFLG2 : 1;
            volatile uint32_t TXSUSFLG2 : 1;
            volatile uint32_t ARBLSTFLG2 : 1;
            volatile uint32_t TXERRFLG2 : 1;
            volatile const uint32_t RESERVED3 : 3;
            volatile uint32_t ABREQFLG2 : 1;
            volatile const uint32_t EMNUM : 2;
            volatile const uint32_t TXMEFLG0 : 1;
            volatile const uint32_t TXMEFLG1 : 1;
            volatile const uint32_t TXMEFLG2 : 1;
            volatile const uint32_t LOWESTP0 : 1;
            volatile const uint32_t LOWESTP1 : 1;
            volatile const uint32_t LOWESTP2 : 1;
        } TXSTS_B;
    } ;


    union
    {
        volatile uint32_t RXF0;

        struct
        {
            volatile const uint32_t FMNUM0 : 2;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t FFULLFLG0 : 1;
            volatile uint32_t FOVRFLG0 : 1;
            volatile uint32_t RFOM0 : 1;
            volatile const uint32_t RESERVED2 : 26;
        } RXF0_B;
    } ;


    union
    {
        volatile uint32_t RXF1;

        struct
        {
            volatile const uint32_t FMNUM1 : 2;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t FFULLFLG1 : 1;
            volatile uint32_t FOVRFLG1 : 1;
            volatile uint32_t RFOM1 : 1;
            volatile const uint32_t RESERVED2 : 26;
        } RXF1_B;
    } ;


    union
    {
        volatile uint32_t INTEN;

        struct
        {
            volatile uint32_t TXMEIE : 1;
            volatile uint32_t FMIEN0 : 1;
            volatile uint32_t FFULLIEN0 : 1;
            volatile uint32_t FOVRIEN0 : 1;
            volatile uint32_t FMPIEN1 : 1;
            volatile uint32_t FFULLIEN1 : 1;
            volatile uint32_t FOVRIEN1 : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t ERRWIEN : 1;
            volatile uint32_t ERRPIEN : 1;
            volatile uint32_t BOFFIEN : 1;
            volatile uint32_t LECIEN : 1;
            volatile const uint32_t RESERVED2 : 3;
            volatile uint32_t ERRIEN : 1;
            volatile uint32_t WUPIEN : 1;
            volatile uint32_t SLEEPIEN : 1;
            volatile const uint32_t RESERVED3 : 14;
        } INTEN_B;
    } ;


    union
    {
        volatile uint32_t ERRSTS;

        struct
        {
            volatile const uint32_t ERRWFLG : 1;
            volatile const uint32_t ERRPFLG : 1;
            volatile const uint32_t BOFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t LERRC : 3;
            volatile const uint32_t RESERVED2 : 9;
            volatile const uint32_t TXERRCNT : 8;
            volatile const uint32_t RXERRCNT : 8;
        } ERRSTS_B;
    } ;


    union
    {
        volatile uint32_t BITTIM;

        struct
        {
            volatile uint32_t BRPSC : 10;
            volatile const uint32_t RESERVED1 : 6;
            volatile uint32_t TIMSEG1 : 4;
            volatile uint32_t TIMSEG2 : 3;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t RSYNJW : 2;
            volatile const uint32_t RESERVED3 : 4;
            volatile uint32_t LBKMEN : 1;
            volatile uint32_t SILMEN : 1;
        } BITTIM_B;
    } ;
    volatile const uint32_t RESERVED1[88];

    CAN_TxMailBox_T sTxMailBox[3];

    CAN_RxFIFO_T sRxFIFO[2];

    volatile const uint32_t RESERVED2[12];


    union
    {
        volatile uint32_t FCTRL;

        struct
        {
            volatile uint32_t FIM : 1;
            volatile const uint32_t RESERVED1 : 31;
        } FCTRL_B;
    } ;


    union
    {
        volatile uint32_t FMCFG;

        struct
        {
            volatile uint32_t FMCFG0 : 1;
            volatile uint32_t FMCFG1 : 1;
            volatile uint32_t FMCFG2 : 1;
            volatile uint32_t FMCFG3 : 1;
            volatile uint32_t FMCFG4 : 1;
            volatile uint32_t FMCFG5 : 1;
            volatile uint32_t FMCFG6 : 1;
            volatile uint32_t FMCFG7 : 1;
            volatile uint32_t FMCFG8 : 1;
            volatile uint32_t FMCFG9 : 1;
            volatile uint32_t FMCFG10 : 1;
            volatile uint32_t FMCFG11 : 1;
            volatile uint32_t FMCFG12 : 1;
            volatile uint32_t FMCFG13 : 1;
            volatile const uint32_t RESERVED1 : 18;
        } FMCFG_B;
    } ;
    volatile const uint32_t RESERVED3;


    union
    {
        volatile uint32_t FSCFG;

        struct
        {
            volatile uint32_t FSCFG0 : 1;
            volatile uint32_t FSCFG1 : 1;
            volatile uint32_t FSCFG2 : 1;
            volatile uint32_t FSCFG3 : 1;
            volatile uint32_t FSCFG4 : 1;
            volatile uint32_t FSCFG5 : 1;
            volatile uint32_t FSCFG6 : 1;
            volatile uint32_t FSCFG7 : 1;
            volatile uint32_t FSCFG8 : 1;
            volatile uint32_t FSCFG9 : 1;
            volatile uint32_t FSCFG10 : 1;
            volatile uint32_t FSCFG11 : 1;
            volatile uint32_t FSCFG12 : 1;
            volatile uint32_t FSCFG13 : 1;
            volatile const uint32_t RESERVED1 : 18;
        } FSCFG_B;
    } ;
    volatile const uint32_t RESERVED4;


    union
    {
        volatile uint32_t FFASS;

        struct
        {
            volatile uint32_t FFASS0 : 1;
            volatile uint32_t FFASS1 : 1;
            volatile uint32_t FFASS2 : 1;
            volatile uint32_t FFASS3 : 1;
            volatile uint32_t FFASS4 : 1;
            volatile uint32_t FFASS5 : 1;
            volatile uint32_t FFASS6 : 1;
            volatile uint32_t FFASS7 : 1;
            volatile uint32_t FFASS8 : 1;
            volatile uint32_t FFASS9 : 1;
            volatile uint32_t FFASS10 : 1;
            volatile uint32_t FFASS11 : 1;
            volatile uint32_t FFASS12 : 1;
            volatile uint32_t FFASS13 : 1;
            volatile const uint32_t RESERVED1 : 18;
        } FFASS_B;
    } ;
    volatile const uint32_t RESERVED5;


    union
    {
        volatile uint32_t FACT;

        struct
        {
            volatile uint32_t FACT0 : 1;
            volatile uint32_t FACT1 : 1;
            volatile uint32_t FACT2 : 1;
            volatile uint32_t FACT3 : 1;
            volatile uint32_t FACT4 : 1;
            volatile uint32_t FACT5 : 1;
            volatile uint32_t FACT6 : 1;
            volatile uint32_t FACT7 : 1;
            volatile uint32_t FACT8 : 1;
            volatile uint32_t FACT9 : 1;
            volatile uint32_t FACT10 : 1;
            volatile uint32_t FACT11 : 1;
            volatile uint32_t FACT12 : 1;
            volatile uint32_t FACT13 : 1;
            volatile const uint32_t RESERVED1 : 18;
        } FACT_B;
    } ;
    volatile const uint32_t RESERVED6[8];


    CAN_FilterRegister_T sFilterRegister[14];
} CAN_T;





typedef struct
{

    union
        {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t CECEN : 1;
            volatile uint32_t TXSM : 1;
            volatile uint32_t TXEM : 1;
            volatile const uint32_t RESERVED1 : 29;
        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t CFG;

        struct
        {
            volatile uint32_t SFTCFG : 3;
            volatile uint32_t RXTCFG : 1;
            volatile uint32_t RXSBRERR : 1;
            volatile uint32_t GEBRERR : 1;
            volatile uint32_t GELBPERR : 1;
            volatile uint32_t AEBGIB : 1;
            volatile uint32_t SFTOB : 1;
            volatile const uint32_t RESERVED1 : 7;
            volatile uint32_t OACFG : 15;
            volatile uint32_t LMODSEL : 1;
        } CFG_B;
    } ;


    union
    {
        volatile uint32_t TXDATA;

        struct
        {
            volatile uint32_t TXDATA : 8;
            volatile const uint32_t RESERVED1 : 24;
        } TXDATA_B;
    } ;


    union {
        volatile const uint32_t RXDATA;

        struct
        {
            volatile const uint32_t RXDATA : 8;
            volatile const uint32_t RESERVED1 : 24;
        } RXDATA_B;
    } ;


    union {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t RXBREFLG : 1;
            volatile uint32_t RXEFLG : 1;
            volatile uint32_t RXOVRFLG : 1;
            volatile uint32_t RXBRERRFLG : 1;
            volatile uint32_t RXSBPEFLG : 1;
            volatile uint32_t RXLBPEFLG : 1;
            volatile uint32_t RXMACKFLG : 1;
            volatile uint32_t ARBLOSFLG : 1;
            volatile uint32_t TXBREFLG : 1;
            volatile uint32_t TXEFLG : 1;
            volatile uint32_t TXBUFLG : 1;
            volatile uint32_t TXERRFLG : 1;
            volatile uint32_t TXMACKFLG : 1;
            volatile const uint32_t RESERVED1 : 19;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t INTEN;

        struct
        {
            volatile uint32_t RXBREIEN : 1;
            volatile uint32_t RXEIEN : 1;
            volatile uint32_t RXOVRIEN : 1;
            volatile uint32_t RXBRERRIEN : 1;
            volatile uint32_t RXSBPEIEN : 1;
            volatile uint32_t RXLBPEIEN : 1;
            volatile uint32_t RXMACKIEN : 1;
            volatile uint32_t ARBLOSIEN : 1;
            volatile uint32_t TXBREIEN : 1;
            volatile uint32_t TXIEN : 1;
            volatile uint32_t TXBUIEN : 1;
            volatile uint32_t TXERRIEN : 1;
            volatile uint32_t TXMACKIEN : 1;
            volatile const uint32_t RESERVED1 : 19;
        } INTEN_B;
    } ;
} CEC_T;





typedef struct
{

    union
    {
        volatile uint32_t DATA;

        struct
        {
            volatile uint32_t DATA : 32;
        } DATA_B;
    } ;


    union
    {
        volatile uint32_t INDATA;

        struct
        {
            volatile uint32_t INDATA : 8;
            volatile const uint32_t RESERVED1 : 24;
        } INDATA_B;
    } ;


    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t RST : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t POLSIZE : 2;
            volatile uint32_t REVI : 2;
            volatile uint32_t REVO : 1;
            volatile const uint32_t RESERVED2 : 24;
        } CTRL_B;
    } ;
    volatile const uint32_t RESERVED;


    union
    {
        volatile uint32_t INITVAL;

        struct
        {
            volatile uint32_t VALUE : 32;
        } INITVAL_B;
    } ;


    union
    {
        volatile uint32_t POL;

        struct
        {
            volatile uint32_t PPOL : 32;
        } POL_B;
    } ;
} CRC_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t SNINTEN : 1;
            volatile uint32_t SWINTEN : 1;
            volatile uint32_t EINTEN : 1;
            volatile uint32_t ESINTEN : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t CNTEN : 1;
            volatile uint32_t AUTOTRMEN : 1;
            volatile uint32_t SWSGNR : 1;
            volatile uint32_t HSI48TRM : 6;
            volatile const uint32_t RESERVED2 : 18;
        } CTRL_B;
    } ;

    union
    {
        volatile uint32_t CFG;

        struct
        {
            volatile uint32_t RLDVAL : 16;
            volatile uint32_t FELMT : 8;
            volatile uint32_t SYNCPSC : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t SYNCSRCSEL : 2;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t SYNCPOLSEL : 1;
        } CFG_B;
    } ;

    union
    {
        volatile const uint32_t INTSTS;

        struct
        {
            volatile const uint32_t SNFLG : 1;
            volatile const uint32_t SWFLG : 1;
            volatile const uint32_t EFLG : 1;
            volatile const uint32_t ESFLG : 1;
            volatile const uint32_t RESERVED1 : 4;
            volatile const uint32_t ERRORFLG : 1;
            volatile const uint32_t SYNCMISS : 1;
            volatile const uint32_t TRMFLG : 1;
            volatile const uint32_t RESERVED2 : 4;
            volatile const uint32_t CNTDRCT : 1;
            volatile const uint32_t FECPT : 16;
        } INTSTS_B;
    } ;

    union
    {
        volatile uint32_t INTCLR;

        struct
        {
            volatile uint32_t SNCLR : 1;
            volatile uint32_t SWCLR : 1;
            volatile uint32_t ECLR : 1;
            volatile uint32_t ESCLR : 1;
            volatile const uint32_t RESERVED1 : 28;
        } INTCLR_B;
    } ;
} CRS_T;





typedef struct
{

    union
    {
        volatile uint32_t CSTS;

        struct
        {
            volatile uint32_t EN1 : 1;
            volatile uint32_t SW1 : 1;
            volatile uint32_t MOD1 : 2;
            volatile uint32_t INVINSEL1 : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t OUTSEL1 : 3;
            volatile uint32_t OPINV1 : 1;
            volatile uint32_t HYSCFG1 : 2;
            volatile const uint32_t OUTSTS1 : 1;
            volatile uint32_t LOCK1 : 1;
            volatile uint32_t EN2 : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t MOD2 : 2;
            volatile uint32_t INVINSEL2 : 3;
            volatile uint32_t WMODEN : 1;
            volatile uint32_t OUTSEL2 : 3;
            volatile uint32_t OPINV2 : 1;
            volatile uint32_t HYSCFG2 : 2;
            volatile const uint32_t OUTSTS2 : 1;
            volatile uint32_t LOCK2 : 1;
        } CSTS_B;
    } ;
} COMP_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t ENCH1 : 1;
            volatile uint32_t BUFFDCH1 : 1;
            volatile uint32_t TRGENCH1 : 1;
            volatile uint32_t TRGSELCH1 : 3;
            volatile uint32_t WAVENCH1 : 2;
            volatile uint32_t MAMPSELCH1 : 4;
            volatile uint32_t DMAENCH1 : 1;
            volatile uint32_t DMAUDRIEN1 : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t ENCH2 : 1;
            volatile uint32_t BUFFDCH2 : 1;
            volatile uint32_t TRGENCH2 : 1;
            volatile uint32_t TRGSELCH2 : 3;
            volatile uint32_t WAVENCH2 : 2;
            volatile uint32_t MAMPSELCH2 : 4;
            volatile uint32_t DMAENCH2 : 1;
            volatile uint32_t DMAUDRIEN2 : 1;
            volatile const uint32_t RESERVED2 : 2;
        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t SWTRG;

        struct
        {
            volatile uint32_t SWTRG1 : 1;
            volatile uint32_t SWTRG2 : 1;
            volatile const uint32_t RESERVED1 : 30;
        } SWTRG_B;
    } ;


    union
    {
        volatile uint32_t DH12R1;

        struct
        {
            volatile uint32_t DATA : 12;
            volatile const uint32_t RESERVED1 : 20;
        } DH12R1_B;
    } ;


    union
    {
        volatile uint32_t DH12L1;

        struct
        {
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t DATA : 12;
            volatile const uint32_t RESERVED2 : 16;
        } DH12L1_B;
    } ;


    union
    {
        volatile uint32_t DH8R1;

        struct
        {
            volatile uint32_t DATA : 8;
            volatile const uint32_t RESERVED2 : 24;
        } DH8R1_B;
    } ;


    union
    {
        volatile uint32_t DH12R2;

        struct
        {
            volatile uint32_t DATA : 12;
            volatile const uint32_t RESERVED1 : 20;
        } DH12R2_B;
    } ;


    union
    {
        volatile uint32_t DH12L2;

        struct
        {
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t DATA : 12;
            volatile const uint32_t RESERVED2 : 16;
        } DH12L2_B;
    } ;


    union
    {
        volatile uint32_t DH8R2;

        struct
        {
            volatile uint32_t DATA : 8;
            volatile const uint32_t RESERVED1 : 24;
        } DH8R2_B;
    } ;


    union
    {
        volatile uint32_t DH12RDUAL;

        struct
        {
            volatile uint32_t DATACH1 : 12;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t DATACH2 : 12;
            volatile const uint32_t RESERVED2 : 4;
        } DH12RDUAL_B;
    } ;


    union
    {
        volatile uint32_t DH12LDUAL;

        struct
        {
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t DATACH1 : 12;
            volatile const uint32_t RESERVED2 : 4;
            volatile uint32_t DATACH2 : 12;
        } DH12LDUAL_B;
    } ;


    union
    {
        volatile uint32_t DH8RDUAL;

        struct
        {
            volatile uint32_t DATACH1 : 8;
            volatile uint32_t DATACH2 : 8;
            volatile const uint32_t RESERVED1 : 16;
        } DH8RDUAL_B;
    } ;


    union
    {
        volatile const uint32_t DATAOCH1;

        struct
        {
            volatile const uint32_t DATA : 12;
            volatile const uint32_t RESERVED1 : 20;
        } DATAOCH1_B;
    } ;


    union
    {
        volatile const uint32_t DATAOCH2;

        struct
        {
            volatile const uint32_t DATA : 12;
            volatile const uint32_t RESERVED1 : 20;
    } DATAOCH2_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const uint32_t RESERVED1 : 13;
            volatile uint32_t DMAUDRFLG1 : 1;
            volatile const uint32_t RESERVED2 : 15;
            volatile uint32_t DMAUDRFLG2 : 1;
            volatile const uint32_t RESERVED3 : 2;
        } STS_B;
    } ;
} DAC_T;





typedef struct
{


    union
    {
        volatile const uint32_t IDCODE;

        struct
        {
            volatile const uint32_t EQR : 12;
            volatile const uint32_t RESERVED1 : 4;
            volatile const uint32_t WVR : 16;
        } IDCODE_B;
    } ;


    union
    {
        volatile uint32_t CFG;

        struct
        {
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t STOP_CLK_STS : 1;
            volatile uint32_t STANDBY_CLK_STS : 1;
            volatile const uint32_t RESERVED2 : 29;
        } CFG_B;
    } ;


    union
    {
        volatile uint32_t APB1F;

        struct
        {
            volatile uint32_t TMR2_STS : 1;
            volatile uint32_t TMR3_STS : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t TMR6_STS : 1;
            volatile uint32_t TMR7_STS : 1;
            volatile const uint32_t RESERVED2 : 2;
            volatile uint32_t TMR14_STS : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t RTC_STS : 1;
            volatile uint32_t WWDT_STS : 1;
            volatile uint32_t IWDT_STS : 1;
            volatile const uint32_t RESERVED4 : 8;
            volatile uint32_t I2C1_SMBUS_TIMEOUT_STS : 1;
            volatile const uint32_t RESERVED5 : 3;
            volatile uint32_t CAN_STS : 1;
            volatile const uint32_t RESERVED6 : 6;
        } APB1F_B;
    } ;


    union
    {
        volatile uint32_t APB2F;

        struct
        {
            volatile const uint32_t RESERVED1 : 11;
            volatile uint32_t TMR1_STS : 1;
            volatile const uint32_t RESERVED2 : 4;
            volatile uint32_t TMR15_STS : 1;
            volatile uint32_t TMR16_STS : 1;
            volatile uint32_t TMR17_STS : 1;
            volatile const uint32_t RESERVED3 : 13;
        } APB2F_B;
    } ;
} DBG_T;





typedef struct
{


    union
    {
        volatile const uint32_t INTSTS;

        struct
        {
            volatile const uint32_t GINTFLG1 : 1;
            volatile const uint32_t TCFLG1 : 1;
            volatile const uint32_t HTFLG1 : 1;
            volatile const uint32_t TERRFLG1 : 1;
            volatile const uint32_t GINTFLG2 : 1;
            volatile const uint32_t TCFLG2 : 1;
            volatile const uint32_t HTFLG2 : 1;
            volatile const uint32_t TERRFLG2 : 1;
            volatile const uint32_t GINTFLG3 : 1;
            volatile const uint32_t TCFLG3 : 1;
            volatile const uint32_t HTFLG3 : 1;
            volatile const uint32_t TERRFLG3 : 1;
            volatile const uint32_t GINTFLG4 : 1;
            volatile const uint32_t TCFLG4 : 1;
            volatile const uint32_t HTFLG4 : 1;
            volatile const uint32_t TERRFLG4 : 1;
            volatile const uint32_t GINTFLG5 : 1;
            volatile const uint32_t TCFLG5 : 1;
            volatile const uint32_t HTFLG5 : 1;
            volatile const uint32_t TERRFLG5 : 1;
            volatile const uint32_t GINTFLG6 : 1;
            volatile const uint32_t TCFLG6 : 1;
            volatile const uint32_t HTFLG6 : 1;
            volatile const uint32_t TERRFLG6 : 1;
            volatile const uint32_t GINTFLG7 : 1;
            volatile const uint32_t TCFLG7 : 1;
            volatile const uint32_t HTFLG7 : 1;
            volatile const uint32_t TERRFLG7 : 1;
            volatile const uint32_t RESERVED1 : 4;
        } ISTS_B;
    } ;


    union
    {
        volatile uint32_t INTFCLR;

        struct
        {
            volatile uint32_t GINTCLR1 : 1;
            volatile uint32_t TCCLR1 : 1;
            volatile uint32_t HTCLR1 : 1;
            volatile uint32_t TERRCLR1 : 1;
            volatile uint32_t GINTCLR2 : 1;
            volatile uint32_t TCCLR2 : 1;
            volatile uint32_t HTCLR2 : 1;
            volatile uint32_t TERRCLR2 : 1;
            volatile uint32_t GINTCLR3 : 1;
            volatile uint32_t TCCLR3 : 1;
            volatile uint32_t HTCLR3 : 1;
            volatile uint32_t TERRCLR3 : 1;
            volatile uint32_t GINTCLR4 : 1;
            volatile uint32_t TCCLR4 : 1;
            volatile uint32_t HTCLR4 : 1;
            volatile uint32_t TERRCLR4 : 1;
            volatile uint32_t GINTCLR5 : 1;
            volatile uint32_t TCCLR5 : 1;
            volatile uint32_t HTCLR5 : 1;
            volatile uint32_t TERRCLR5 : 1;
            volatile uint32_t GINTCLR6 : 1;
            volatile uint32_t TCCLR6 : 1;
            volatile uint32_t HTCLR6 : 1;
            volatile uint32_t TERRCLR6 : 1;
            volatile uint32_t GINTCLR7 : 1;
            volatile uint32_t TCCLR7 : 1;
            volatile uint32_t HTCLR7 : 1;
            volatile uint32_t TERRCLR7 : 1;
            volatile const uint32_t RESERVED1 : 4;
        } INTFCLR_B;
    } ;


    union
    {
        volatile uint32_t CHCFG1;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG1_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA1;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA1_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR1;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR1_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR1;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR1_B;
    } ;
    volatile const uint32_t RESERVED1;


    union
    {
        volatile uint32_t CHCFG2;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG2_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA2;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA2_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR2;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR2_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR2;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR2_B;
    } ;
    volatile const uint32_t RESERVED2;


    union
    {
        volatile uint32_t CHCFG3;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG3_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA3;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA3_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR3;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR3_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR3;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR3_B;
    } ;
    volatile const uint32_t RESERVED3;


    union
    {
        volatile uint32_t CHCFG4;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG4_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA4;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA4_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR4;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR4_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR4;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR4_B;
    } ;
    volatile const uint32_t RESERVED4;


    union
    {
        volatile uint32_t CHCFG5;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG5_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA5;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA5_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR5;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR5_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR5;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR5_B;
    } ;
    volatile const uint32_t RESERVED5;


    union
    {
        volatile uint32_t CHCFG6;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG6_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA6;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA6_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR6;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR6_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR6;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR6_B;
    } ;
    volatile const uint32_t RESERVED6;


    union
    {
        volatile uint32_t CHCFG7;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG7_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA7;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA7_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR7;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR7_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR7;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR7_B;
    } ;
    volatile const uint32_t RESERVED7[6];


    union
    {
        volatile uint32_t CHSEL;

        struct
        {
            volatile uint32_t CHSEL1 : 4;
            volatile uint32_t CHSEL2 : 4;
            volatile uint32_t CHSEL3 : 4;
            volatile uint32_t CHSEL4 : 4;
            volatile uint32_t CHSEL5 : 4;
            volatile uint32_t CHSEL6 : 4;
            volatile uint32_t CHSEL7 : 4;
            volatile const uint32_t RESERVED1 : 4;
        } CHSEL_B;
    } ;
} DMA_T;





typedef struct
{


    union
    {
        volatile uint32_t CHCFG;

        struct
        {
            volatile uint32_t CHEN : 1;
            volatile uint32_t TCINTEN : 1;
            volatile uint32_t HTINTEN : 1;
            volatile uint32_t TERRINTEN : 1;
            volatile uint32_t DIRCFG : 1;
            volatile uint32_t CIRMODE : 1;
            volatile uint32_t PERIMODE : 1;
            volatile uint32_t MIMODE : 1;
            volatile uint32_t PERSIZE : 2;
            volatile uint32_t MSIZE : 2;
            volatile uint32_t CHPL : 2;
            volatile uint32_t M2MMODE : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CHCFG_B;
    } ;


    union
    {
        volatile uint32_t CHNDATA;

        struct
        {
            volatile uint32_t NDATAT : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CHNDATA_B;
    } ;


    union
    {
        volatile uint32_t CHPADDR;

        struct
        {
            volatile uint32_t PERADDR : 32;
        } CHPADDR_B;
    } ;


    union
    {
        volatile uint32_t CHMADDR;

        struct
        {
            volatile uint32_t MEMADD : 32;
        } CHMADDR_B;
    } ;
} DMA_CHANNEL_T;





typedef struct
{

    union
    {
        volatile uint32_t IMASK;

        struct
        {
            volatile uint32_t IMASK0 : 1;
            volatile uint32_t IMASK1 : 1;
            volatile uint32_t IMASK2 : 1;
            volatile uint32_t IMASK3 : 1;
            volatile uint32_t IMASK4 : 1;
            volatile uint32_t IMASK5 : 1;
            volatile uint32_t IMASK6 : 1;
            volatile uint32_t IMASK7 : 1;
            volatile uint32_t IMASK8 : 1;
            volatile uint32_t IMASK9 : 1;
            volatile uint32_t IMASK10 : 1;
            volatile uint32_t IMASK11 : 1;
            volatile uint32_t IMASK12 : 1;
            volatile uint32_t IMASK13 : 1;
            volatile uint32_t IMASK14 : 1;
            volatile uint32_t IMASK15 : 1;
            volatile uint32_t IMASK16 : 1;
            volatile uint32_t IMASK17 : 1;
            volatile uint32_t IMASK18 : 1;
            volatile uint32_t IMASK19 : 1;
            volatile uint32_t IMASK20 : 1;
            volatile uint32_t IMASK21 : 1;
            volatile uint32_t IMASK22 : 1;
            volatile uint32_t IMASK23 : 1;
            volatile uint32_t IMASK24 : 1;
            volatile uint32_t IMASK25 : 1;
            volatile uint32_t IMASK26 : 1;
            volatile uint32_t IMASK27 : 1;
            volatile uint32_t IMASK28 : 1;
            volatile uint32_t IMASK29 : 1;
            volatile uint32_t IMASK30 : 1;
            volatile uint32_t IMASK31 : 1;
        } IMASK_B;
    } ;


    union
    {

        volatile uint32_t EMASK;

        struct
        {
            volatile uint32_t EMASK0 : 1;
            volatile uint32_t EMASK1 : 1;
            volatile uint32_t EMASK2 : 1;
            volatile uint32_t EMASK3 : 1;
            volatile uint32_t EMASK4 : 1;
            volatile uint32_t EMASK5 : 1;
            volatile uint32_t EMASK6 : 1;
            volatile uint32_t EMASK7 : 1;
            volatile uint32_t EMASK8 : 1;
            volatile uint32_t EMASK9 : 1;
            volatile uint32_t EMASK10 : 1;
            volatile uint32_t EMASK11 : 1;
            volatile uint32_t EMASK12 : 1;
            volatile uint32_t EMASK13 : 1;
            volatile uint32_t EMASK14 : 1;
            volatile uint32_t EMASK15 : 1;
            volatile uint32_t EMASK16 : 1;
            volatile uint32_t EMASK17 : 1;
            volatile uint32_t EMASK18 : 1;
            volatile uint32_t EMASK19 : 1;
            volatile uint32_t EMASK20 : 1;
            volatile uint32_t EMASK21 : 1;
            volatile uint32_t EMASK22 : 1;
            volatile uint32_t EMASK23 : 1;
            volatile uint32_t EMASK24 : 1;
            volatile uint32_t EMASK25 : 1;
            volatile uint32_t EMASK26 : 1;
            volatile uint32_t EMASK27 : 1;
            volatile uint32_t EMASK28 : 1;
            volatile uint32_t EMASK29 : 1;
            volatile uint32_t EMASK30 : 1;
            volatile uint32_t EMASK31 : 1;
        } EMASK_B;
    } ;

    union
    {
        volatile uint32_t RTEN;

        struct
        {
            volatile uint32_t RTEN0 : 1;
            volatile uint32_t RTEN1 : 1;
            volatile uint32_t RTEN2 : 1;
            volatile uint32_t RTEN3 : 1;
            volatile uint32_t RTEN4 : 1;
            volatile uint32_t RTEN5 : 1;
            volatile uint32_t RTEN6 : 1;
            volatile uint32_t RTEN7 : 1;
            volatile uint32_t RTEN8 : 1;
            volatile uint32_t RTEN9 : 1;
            volatile uint32_t RTEN10 : 1;
            volatile uint32_t RTEN11 : 1;
            volatile uint32_t RTEN12 : 1;
            volatile uint32_t RTEN13 : 1;
            volatile uint32_t RTEN14 : 1;
            volatile uint32_t RTEN15 : 1;
            volatile uint32_t RTEN16 : 1;
            volatile uint32_t RTEN17 : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t RTEN19 : 1;
            volatile uint32_t RTEN20 : 1;
            volatile uint32_t RTEN21 : 1;
            volatile uint32_t RTEN22 : 1;
            volatile const uint32_t RESERVED2 : 8;
            volatile uint32_t RTEN31 : 1;
        } RTEN_B;
    } ;


    union
    {
        volatile uint32_t FTEN;

        struct
        {
            volatile uint32_t FTEN0 : 1;
            volatile uint32_t FTEN1 : 1;
            volatile uint32_t FTEN2 : 1;
            volatile uint32_t FTEN3 : 1;
            volatile uint32_t FTEN4 : 1;
            volatile uint32_t FTEN5 : 1;
            volatile uint32_t FTEN6 : 1;
            volatile uint32_t FTEN7 : 1;
            volatile uint32_t FTEN8 : 1;
            volatile uint32_t FTEN9 : 1;
            volatile uint32_t FTEN10 : 1;
            volatile uint32_t FTEN11 : 1;
            volatile uint32_t FTEN12 : 1;
            volatile uint32_t FTEN13 : 1;
            volatile uint32_t FTEN14 : 1;
            volatile uint32_t FTEN15 : 1;
            volatile uint32_t FTEN16 : 1;
            volatile uint32_t FTEN17 : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t FTEN19 : 1;
            volatile uint32_t FTEN20 : 1;
            volatile uint32_t FTEN21 : 1;
            volatile uint32_t FTEN22 : 1;
            volatile const uint32_t RESERVED2 : 8;
            volatile uint32_t FTEN31 : 1;
        } FTEN_B;
    } ;


    union
    {
        volatile uint32_t SWINTE;

        struct
        {
            volatile uint32_t SWINTE0 : 1;
            volatile uint32_t SWINTE1 : 1;
            volatile uint32_t SWINTE2 : 1;
            volatile uint32_t SWINTE3 : 1;
            volatile uint32_t SWINTE4 : 1;
            volatile uint32_t SWINTE5 : 1;
            volatile uint32_t SWINTE6 : 1;
            volatile uint32_t SWINTE7 : 1;
            volatile uint32_t SWINTE8 : 1;
            volatile uint32_t SWINTE9 : 1;
            volatile uint32_t SWINTE10 : 1;
            volatile uint32_t SWINTE11 : 1;
            volatile uint32_t SWINTE12 : 1;
            volatile uint32_t SWINTE13 : 1;
            volatile uint32_t SWINTE14 : 1;
            volatile uint32_t SWINTE15 : 1;
            volatile uint32_t SWINTE16 : 1;
            volatile uint32_t SWINTE17 : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t SWINTE19 : 1;
            volatile uint32_t SWINTE20 : 1;
            volatile uint32_t SWINTE21 : 1;
            volatile uint32_t SWINTE22 : 1;
            volatile const uint32_t RESERVED2 : 8;
            volatile uint32_t SWINTE31 : 1;
        } SWINTE_B;
    } ;


    union
    {
        volatile uint32_t IPEND;

        struct
        {
            volatile uint32_t IPEND0 : 1;
            volatile uint32_t IPEND1 : 1;
            volatile uint32_t IPEND2 : 1;
            volatile uint32_t IPEND3 : 1;
            volatile uint32_t IPEND4 : 1;
            volatile uint32_t IPEND5 : 1;
            volatile uint32_t IPEND6 : 1;
            volatile uint32_t IPEND7 : 1;
            volatile uint32_t IPEND8 : 1;
            volatile uint32_t IPEND9 : 1;
            volatile uint32_t IPEND10 : 1;
            volatile uint32_t IPEND11 : 1;
            volatile uint32_t IPEND12 : 1;
            volatile uint32_t IPEND13 : 1;
            volatile uint32_t IPEND14 : 1;
            volatile uint32_t IPEND15 : 1;
            volatile uint32_t IPEND16 : 1;
            volatile uint32_t IPEND17 : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t IPEND19 : 1;
            volatile uint32_t IPEND20 : 1;
            volatile uint32_t IPEND21 : 1;
            volatile uint32_t IPEND22 : 1;
            volatile const uint32_t RESERVED2 : 8;
            volatile uint32_t IPEND31 : 1;
        } IPEND_B;
    } ;
} EINT_T;





typedef struct
{


    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t WS : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t PBEN : 1;
            volatile const uint32_t PBSF : 1;
            volatile const uint32_t RESERVED3 : 26;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t KEY;

        struct
        {
            volatile uint32_t KEY : 32;
        } KEY_B;
    } ;


    union
    {
        volatile uint32_t OBKEY;

        struct
        {
            volatile uint32_t OBKEY : 32;
        } OBKEY_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const uint32_t BUSYF : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t PEF : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t WPEF : 1;
            volatile uint32_t OCF : 1;
            volatile const uint32_t RESERVED3 : 26;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t PG : 1;
            volatile uint32_t PAGEERA : 1;
            volatile uint32_t MASSERA : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t OBP : 1;
            volatile uint32_t OBE : 1;
            volatile uint32_t STA : 1;
            volatile uint32_t LOCK : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t OBWEN : 1;
            volatile uint32_t ERRIE : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t OCIE : 1;
            volatile uint32_t OBLOAD : 1;
            volatile const uint32_t RESERVED4 : 18;
        } CTRL2_B;
    } ;


    union
    {
        volatile uint32_t ADDR;

        struct
        {
            volatile uint32_t ADDR : 32;
        } ADDR_B;
    } ;
    volatile const uint32_t RESERVED;


    union
    {
        volatile const uint32_t OBCS;

        struct
        {
            volatile const uint32_t OBE : 1;
            volatile const uint32_t READPROT : 2;
            volatile const uint32_t RESERVED1 : 5;
            volatile const uint32_t WDTSEL : 1;
            volatile const uint32_t RSTSTOP : 1;
            volatile const uint32_t RSTSTDB : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile const uint32_t nBOOT1 : 1;
            volatile const uint32_t VDDAMONI : 1;
            volatile const uint32_t SRAMPARITY : 1;
            volatile const uint32_t nBOOT0 : 1;
            volatile const uint32_t DATA0 : 8;
            volatile const uint32_t DATA1 : 8;
        } OBCS_B;
    } ;


    union
    {
        volatile const uint32_t WRTPROT;

        struct
        {
            volatile const uint32_t WRTPROT : 32;
        } WRTPROT_B;
    } ;
} FMC_T;





typedef struct
{

    union
    {
        volatile uint32_t MODE;

        struct
        {
            volatile uint32_t MODE0 : 2;
            volatile uint32_t MODE1 : 2;
            volatile uint32_t MODE2 : 2;
            volatile uint32_t MODE3 : 2;
            volatile uint32_t MODE4 : 2;
            volatile uint32_t MODE5 : 2;
            volatile uint32_t MODE6 : 2;
            volatile uint32_t MODE7 : 2;
            volatile uint32_t MODE8 : 2;
            volatile uint32_t MODE9 : 2;
            volatile uint32_t MODE10 : 2;
            volatile uint32_t MODE11 : 2;
            volatile uint32_t MODE12 : 2;
            volatile uint32_t MODE13 : 2;
            volatile uint32_t MODE14 : 2;
            volatile uint32_t MODE15 : 2;
        } MODE_B;
    } ;


    union
    {
        volatile uint32_t OMODE;

        struct
        {
            volatile uint32_t OMODE0 : 1;
            volatile uint32_t OMODE1 : 1;
            volatile uint32_t OMODE2 : 1;
            volatile uint32_t OMODE3 : 1;
            volatile uint32_t OMODE4 : 1;
            volatile uint32_t OMODE5 : 1;
            volatile uint32_t OMODE6 : 1;
            volatile uint32_t OMODE7 : 1;
            volatile uint32_t OMODE8 : 1;
            volatile uint32_t OMODE9 : 1;
            volatile uint32_t OMODE10 : 1;
            volatile uint32_t OMODE11 : 1;
            volatile uint32_t OMODE12 : 1;
            volatile uint32_t OMODE13 : 1;
            volatile uint32_t OMODE14 : 1;
            volatile uint32_t OMODE15 : 1;
            volatile uint32_t RESERVED1 : 16;
        } OMODE_B;
    } ;


    union
    {
        volatile uint32_t OSSEL;

        struct
        {
            volatile uint32_t OSSEL0 : 2;
            volatile uint32_t OSSEL1 : 2;
            volatile uint32_t OSSEL2 : 2;
            volatile uint32_t OSSEL3 : 2;
            volatile uint32_t OSSEL4 : 2;
            volatile uint32_t OSSEL5 : 2;
            volatile uint32_t OSSEL6 : 2;
            volatile uint32_t OSSEL7 : 2;
            volatile uint32_t OSSEL8 : 2;
            volatile uint32_t OSSEL9 : 2;
            volatile uint32_t OSSEL10 : 2;
            volatile uint32_t OSSEL11 : 2;
            volatile uint32_t OSSEL12 : 2;
            volatile uint32_t OSSEL13 : 2;
            volatile uint32_t OSSEL14 : 2;
            volatile uint32_t OSSEL15 : 2;
        } OSSEL_B;
    } ;


    union
    {
        volatile uint32_t PUPD;

        struct
        {
            volatile uint32_t PUPD0 : 2;
            volatile uint32_t PUPD1 : 2;
            volatile uint32_t PUPD2 : 2;
            volatile uint32_t PUPD3 : 2;
            volatile uint32_t PUPD4 : 2;
            volatile uint32_t PUPD5 : 2;
            volatile uint32_t PUPD6 : 2;
            volatile uint32_t PUPD7 : 2;
            volatile uint32_t PUPD8 : 2;
            volatile uint32_t PUPD9 : 2;
            volatile uint32_t PUPD10 : 2;
            volatile uint32_t PUPD11 : 2;
            volatile uint32_t PUPD12 : 2;
            volatile uint32_t PUPD13 : 2;
            volatile uint32_t PUPD14 : 2;
            volatile uint32_t PUPD15 : 2;
        } PUPD_B;
    } ;


    union
    {
        volatile const uint32_t IDATA;

        struct
        {
            volatile const uint32_t IDATA0 : 1;
            volatile const uint32_t IDATA1 : 1;
            volatile const uint32_t IDATA2 : 1;
            volatile const uint32_t IDATA3 : 1;
            volatile const uint32_t IDATA4 : 1;
            volatile const uint32_t IDATA5 : 1;
            volatile const uint32_t IDATA6 : 1;
            volatile const uint32_t IDATA7 : 1;
            volatile const uint32_t IDATA8 : 1;
            volatile const uint32_t IDATA9 : 1;
            volatile const uint32_t IDATA10 : 1;
            volatile const uint32_t IDATA11 : 1;
            volatile const uint32_t IDATA12 : 1;
            volatile const uint32_t IDATA13 : 1;
            volatile const uint32_t IDATA14 : 1;
            volatile const uint32_t IDATA15 : 1;
            volatile const uint32_t RESERVED1 : 16;
        } IDATA_B;
    } ;


    union
    {
        volatile uint32_t ODATA;

        struct
        {
            volatile uint32_t ODATA0 : 1;
            volatile uint32_t ODATA1 : 1;
            volatile uint32_t ODATA2 : 1;
            volatile uint32_t ODATA3 : 1;
            volatile uint32_t ODATA4 : 1;
            volatile uint32_t ODATA5 : 1;
            volatile uint32_t ODATA6 : 1;
            volatile uint32_t ODATA7 : 1;
            volatile uint32_t ODATA8 : 1;
            volatile uint32_t ODATA9 : 1;
            volatile uint32_t ODATA10 : 1;
            volatile uint32_t ODATA11 : 1;
            volatile uint32_t ODATA12 : 1;
            volatile uint32_t ODATA13 : 1;
            volatile uint32_t ODATA14 : 1;
            volatile uint32_t ODATA15 : 1;
            volatile uint32_t RESERVED1 : 16;
        } ODATA_B;
    } ;


    union
    {
        volatile uint32_t BSC;

        struct
        {
            volatile uint32_t BS0 : 1;
            volatile uint32_t BS1 : 1;
            volatile uint32_t BS2 : 1;
            volatile uint32_t BS3 : 1;
            volatile uint32_t BS4 : 1;
            volatile uint32_t BS5 : 1;
            volatile uint32_t BS6 : 1;
            volatile uint32_t BS7 : 1;
            volatile uint32_t BS8 : 1;
            volatile uint32_t BS9 : 1;
            volatile uint32_t BS10 : 1;
            volatile uint32_t BS11 : 1;
            volatile uint32_t BS12 : 1;
            volatile uint32_t BS13 : 1;
            volatile uint32_t BS14 : 1;
            volatile uint32_t BS15 : 1;
            volatile uint32_t BC0 : 1;
            volatile uint32_t BC1 : 1;
            volatile uint32_t BC2 : 1;
            volatile uint32_t BC3 : 1;
            volatile uint32_t BC4 : 1;
            volatile uint32_t BC5 : 1;
            volatile uint32_t BC6 : 1;
            volatile uint32_t BC7 : 1;
            volatile uint32_t BC8 : 1;
            volatile uint32_t BC9 : 1;
            volatile uint32_t BC10 : 1;
            volatile uint32_t BC11 : 1;
            volatile uint32_t BC12 : 1;
            volatile uint32_t BC13 : 1;
            volatile uint32_t BC14 : 1;
            volatile uint32_t BC15 : 1;
        } BSC_B;
    } ;


    union
    {
        volatile uint32_t LOCK;

        struct
        {
            volatile uint32_t LOCK0 : 1;
            volatile uint32_t LOCK1 : 1;
            volatile uint32_t LOCK2 : 1;
            volatile uint32_t LOCK3 : 1;
            volatile uint32_t LOCK4 : 1;
            volatile uint32_t LOCK5 : 1;
            volatile uint32_t LOCK6 : 1;
            volatile uint32_t LOCK7 : 1;
            volatile uint32_t LOCK8 : 1;
            volatile uint32_t LOCK9 : 1;
            volatile uint32_t LOCK10 : 1;
            volatile uint32_t LOCK11 : 1;
            volatile uint32_t LOCK12 : 1;
            volatile uint32_t LOCK13 : 1;
            volatile uint32_t LOCK14 : 1;
            volatile uint32_t LOCK15 : 1;
            volatile uint32_t LOCKKEY : 1;
            volatile uint32_t RESERVED1 : 15;
        } LOCK_B;
    } ;


    union
    {
        volatile uint32_t ALFL;

        struct
        {
            volatile uint32_t AF0 : 4;
            volatile uint32_t AF1 : 4;
            volatile uint32_t AF2 : 4;
            volatile uint32_t AF3 : 4;
            volatile uint32_t AF4 : 4;
            volatile uint32_t AF5 : 4;
            volatile uint32_t AF6 : 4;
            volatile uint32_t AF7 : 4;
        } ALFL_B;
    } ;


    union
    {
        volatile uint32_t ALFH;

        struct
        {
            volatile uint32_t AF0 : 4;
            volatile uint32_t AF1 : 4;
            volatile uint32_t AF2 : 4;
            volatile uint32_t AF3 : 4;
            volatile uint32_t AF4 : 4;
            volatile uint32_t AF5 : 4;
            volatile uint32_t AF6 : 4;
            volatile uint32_t AF7 : 4;
        } ALFH_B;
    } ;


    union
    {
        volatile uint32_t BR;

        struct
        {
            volatile uint32_t BR0 : 1;
            volatile uint32_t BR1 : 1;
            volatile uint32_t BR2 : 1;
            volatile uint32_t BR3 : 1;
            volatile uint32_t BR4 : 1;
            volatile uint32_t BR5 : 1;
            volatile uint32_t BR6 : 1;
            volatile uint32_t BR7 : 1;
            volatile uint32_t BR8 : 1;
            volatile uint32_t BR9 : 1;
            volatile uint32_t BR10 : 1;
            volatile uint32_t BR11 : 1;
            volatile uint32_t BR12 : 1;
            volatile uint32_t BR13 : 1;
            volatile uint32_t BR14 : 1;
            volatile uint32_t BR15 : 1;
            volatile uint32_t RESERVED1 : 16;
        } BR_B;
    } ;
} GPIO_T;






typedef struct
{

    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t I2CEN : 1;
            volatile uint32_t TXIEN : 1;
            volatile uint32_t RXIEN : 1;
            volatile uint32_t SADDRMIEN : 1;
            volatile uint32_t NACKRXIEN : 1;
            volatile uint32_t STOPIEN : 1;
            volatile uint32_t TXCIEN : 1;
            volatile uint32_t ERRIEN : 1;
            volatile uint32_t DNFCFG : 4;
            volatile uint32_t ANFD : 1;
            volatile uint32_t SWRST : 1;
            volatile uint32_t DMATXEN : 1;
            volatile uint32_t DMARXEN : 1;
            volatile uint32_t SBCEN : 1;
            volatile uint32_t CLKSTRETCHD : 1;
            volatile uint32_t WUPEN : 1;
            volatile uint32_t RBEN : 1;
            volatile uint32_t HADDREN : 1;
            volatile uint32_t DEADDREN : 1;
            volatile uint32_t ALTEN : 1;
            volatile uint32_t PECEN : 1;
            volatile const uint32_t RESERVED2 : 8;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t SADDR0 : 1;
            volatile uint32_t SADDR1 : 7;
            volatile uint32_t SADDR8 : 2;
            volatile uint32_t TXDIR : 1;
            volatile uint32_t SADDRLEN : 1;
            volatile uint32_t ADDR10 : 1;
            volatile uint32_t START : 1;
            volatile uint32_t STOP : 1;
            volatile uint32_t NACKEN : 1;
            volatile uint32_t NUMBYT : 8;
            volatile uint32_t RELOADEN : 1;
            volatile uint32_t ENDCFG : 1;
            volatile uint32_t PEC : 1;
            volatile uint32_t RESERVED1 : 5;
        } CTRL2_B;
    } ;


    union
    {
        volatile uint32_t ADDR1;

        struct
        {
            volatile uint32_t ADDR0 : 1;
            volatile uint32_t ADDR1 : 7;
            volatile uint32_t ADDR8 : 2;
            volatile uint32_t ADDR1LEN : 1;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t ADDR1EN : 1;
            volatile const uint32_t RESERVED2 : 16;
        } ADDR1_B;
    } ;


    union
    {
        volatile uint32_t ADDR2;

        struct
        {
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t ADDR2 : 7;
            volatile uint32_t ADDR2MSK : 3;
            volatile const uint32_t RESERVED2 : 4;
            volatile uint32_t ADDR2EN : 1;
            volatile const uint32_t RESERVED3 : 16;
        } ADDR2_B;
    } ;


    union
    {
        volatile uint32_t TIMING;

        struct
        {
            volatile uint32_t SCLL : 8;
            volatile uint32_t SCLH : 8;
            volatile uint32_t DATAHT : 4;
            volatile uint32_t DATAT : 4;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t TIMINGPSC : 4;
        } TIMING_B;
    } ;


    union
    {
        volatile uint32_t TIMEOUT;

        struct
        {
            volatile uint32_t TIMEOUTA : 12;
            volatile uint32_t IDLECLKTO : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t CLKTOEN : 1;
            volatile uint32_t TIMEOUTB : 12;
            volatile const uint32_t RESERVED2 : 3;
            volatile uint32_t EXCLKTOEN : 1;
        } TIMEOUT_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t TXBEFLG : 1;
            volatile uint32_t TXINTFLG : 1;
            volatile const uint32_t RXBNEFLG : 1;
            volatile const uint32_t ADDRMFLG : 1;
            volatile const uint32_t NACKFLG : 1;
            volatile const uint32_t STOPFLG : 1;
            volatile const uint32_t TXCFLG : 1;
            volatile const uint32_t TXCRFLG : 1;
            volatile const uint32_t BERRFLG : 1;
            volatile const uint32_t ALFLG : 1;
            volatile const uint32_t OVRURFLG : 1;
            volatile const uint32_t PECEFLG : 1;
            volatile const uint32_t TTEFLG : 1;
            volatile const uint32_t SMBALTFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile const uint32_t BUSBSYFLG : 1;
            volatile const uint32_t TXDIRFLG : 1;
            volatile const uint32_t ADDRCMFLG : 7;
            volatile const uint32_t RESERVED2 : 8;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t INTFCLR;

        struct
        {
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t ADDRMCLR : 1;
            volatile uint32_t NACKCLR : 1;
            volatile uint32_t STOPCLR : 1;
            volatile const uint32_t RESERVED2 : 2;
            volatile uint32_t BERRCLR : 1;
            volatile uint32_t ALCLR : 1;
            volatile uint32_t OVRURCLR : 1;
            volatile uint32_t PECECLR : 1;
            volatile uint32_t TTECLR : 1;
            volatile uint32_t SMBALTCLR : 1;
            volatile const uint32_t RESERVED3 : 18;
        } INTFCLR_B;
    } ;


    union
    {
        volatile const uint32_t PEC;

        struct
        {
            volatile const uint32_t PEC : 8;
            volatile const uint32_t RESERVED1 : 24;
        } PEC_B;
    } ;


    union
    {
        volatile const uint32_t RXDATA;

        struct
        {
            volatile const uint32_t RXDATA : 8;
            volatile const uint32_t RESERVED1 : 24;
        } RXDATA_B;
    } ;


    union
    {
        volatile uint32_t TXDATA;

        struct
        {
            volatile uint32_t TXDATA : 8;
            volatile uint32_t RESERVED1 : 24;
        } TXDATA_B;
    } ;
} I2C_T;





typedef struct
{


    union
    {
        volatile uint32_t KEY;

        struct
        {
            volatile uint32_t KEY : 16;
            volatile const uint32_t RESERVED1 : 16;
        } KEY_B;
    } ;


    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t PSC : 3;
            volatile const uint32_t RESERVED1 : 29;
        } PSC_B;
    } ;


    union
    {
        volatile uint32_t CNTRLD;

        struct
        {
            volatile uint32_t CNTRLD : 12;
            volatile const uint32_t RESERVED1 : 20;
        } CNTRLD_B;
    } ;


    union
    {
        volatile const uint32_t STS;

        struct
        {
            volatile const uint32_t PSCUFLG : 1;
            volatile const uint32_t CNTUFLG : 1;
            volatile const uint32_t WINUFLG : 1;
            volatile const uint32_t RESERVED1 : 29;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t WIN;

        struct
        {
            volatile uint32_t WIN : 12;
            volatile const uint32_t RESERVED1 : 20;
        } WIN_B;
    } ;
} IWDT_T;





typedef struct
{


    union
    {
        volatile uint16_t READPROT;

        struct
        {
            volatile uint16_t READPROT : 8;
            volatile uint16_t nREADPROT : 8;
        } READPORT_B;
    } ;


    union
    {
        volatile uint16_t USER;

        struct
        {
            volatile uint16_t WDTSEL : 1;
            volatile uint16_t RSTSTOP : 1;
            volatile uint16_t RSTSTDBY : 1;
            volatile const uint16_t RESERVED1 : 1;
            volatile uint16_t BOT1 : 1;
            volatile uint16_t VDDAMON : 1;
            volatile uint16_t RPC : 1;
            volatile const uint16_t RESERVED2 : 1;
            volatile uint16_t nUSER : 8;
        } USER_B;
    } ;


    union
    {
        volatile uint16_t DATA0;

        struct
        {
            volatile uint16_t DATA0 : 8;
            volatile uint16_t nDATA0 : 8;
        } DATA0_B;
    } ;


    union
    {
        volatile uint16_t DATA1;

        struct
        {
            volatile uint16_t DATA1 : 8;
            volatile uint16_t nDATA1 : 8;
        } DATA1_B;
    } ;


    union
    {
        volatile uint16_t WRTPROT0;

        struct
        {
            volatile uint16_t WRTPROT0 : 8;
            volatile uint16_t nWRTPROT0 : 8;
        } WRTPROT0_B;
    } ;


    union
    {
        volatile uint16_t WRTPROT1;

        struct
        {
            volatile uint16_t WRTPROT1 : 8;
            volatile uint16_t nWRTPROT1 : 8;
        } WRTPROT1_B;
    } ;
} OB_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t LPDSCFG : 1;
            volatile uint32_t PDDSCFG : 1;
            volatile uint32_t WUFLGCLR : 1;
            volatile uint32_t SBFLGCLR : 1;
            volatile uint32_t PVDEN : 1;
            volatile uint32_t PLSEL : 3;
            volatile uint32_t BPWEN : 1;
            volatile const uint32_t RESERVED1 : 23;

        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t CSTS;

        struct
        {
            volatile const uint32_t WUEFLG : 1;
            volatile const uint32_t SBFLG : 1;
            volatile const uint32_t PVDOFLG : 1;
            volatile const uint32_t RESERVED1 : 5;
            volatile uint32_t WKUPCFG1 : 1;
            volatile uint32_t WKUPCFG2 : 1;
            volatile uint32_t WKUPCFG3 : 1;
            volatile uint32_t WKUPCFG4 : 1;
            volatile uint32_t WKUPCFG5 : 1;
            volatile uint32_t WKUPCFG6 : 1;
            volatile uint32_t WKUPCFG7 : 1;
            volatile uint32_t WKUPCFG8 : 1;
            volatile const uint32_t RESERVED2 : 16;
        } CSTS_B;
    } ;
} PMU_T;





typedef struct
{

    union
    {

        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t HSIEN : 1;
            volatile const uint32_t HSIRDYFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t HSITRM : 5;
            volatile const uint32_t HSICAL : 8;
            volatile uint32_t HSEEN : 1;
            volatile const uint32_t HSERDYFLG : 1;
            volatile uint32_t HSEBCFG : 1;
            volatile uint32_t CSSEN : 1;
            volatile const uint32_t RESERVED2 : 4;
            volatile uint32_t PLLEN : 1;
            volatile const uint32_t PLLRDYFLG : 1;
            volatile const uint32_t RESERVED3 : 6;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t SCLKSEL : 2;
            volatile const uint32_t SCLKSWSTS : 2;
            volatile uint32_t AHBPSC : 4;
            volatile uint32_t APB1PSC : 3;
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t ADCPSC : 1;
            volatile uint32_t PLLSRCSEL : 2;
            volatile uint32_t PLLHSEPSC : 1;
            volatile uint32_t PLLMULCFG : 4;
            volatile const uint32_t RESERVED3 : 2;
            volatile uint32_t MCOSEL : 4;
            volatile uint32_t MCOPSC : 3;
            volatile uint32_t MCOPLLPSC : 1;
        } CFG1_B;
    } ;


    union
    {
        volatile uint32_t INT;

        struct
        {
            volatile const uint32_t LSIRDYFLG : 1;
            volatile const uint32_t LSERDYFLG : 1;
            volatile const uint32_t HSIRDYFLG : 1;
            volatile const uint32_t HSERDYFLG : 1;
            volatile const uint32_t PLLRDYFLG : 1;
            volatile const uint32_t HSI14RDYFLG : 1;
            volatile const uint32_t HSI48RDYFLG : 1;
            volatile const uint32_t CSSFLG : 1;
            volatile uint32_t LSIRDYEN : 1;
            volatile uint32_t LSERDYEN : 1;
            volatile uint32_t HSIRDYEN : 1;
            volatile uint32_t HSERDYEN : 1;
            volatile uint32_t PLLRDYEN : 1;
            volatile uint32_t HSI14RDYEN : 1;
            volatile uint32_t HSI48RDYEN : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t LSIRDYCLR : 1;
            volatile uint32_t LSERDYCLR : 1;
            volatile uint32_t HSIRDYCLR : 1;
            volatile uint32_t HSERDYCLR : 1;
            volatile uint32_t PLLRDYCLR : 1;
            volatile uint32_t HSI14RDYCLR : 1;
            volatile uint32_t HSI48RDYCLR : 1;
            volatile uint32_t CSSCLR : 1;
            volatile const uint32_t RESERVED2 : 8;
        } INT_B;
    } ;


    union
    {
        volatile uint32_t APBRST2;

        struct
        {
            volatile uint32_t SYSCFG : 1;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t USART5 : 1;
            volatile uint32_t USART6 : 1;
            volatile uint32_t USART7 : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t ADC : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t TMR1 : 1;
            volatile uint32_t SPI1 : 1;
            volatile const uint32_t RESERVED4 : 1;
            volatile uint32_t USART1 : 1;
            volatile const uint32_t RESERVED5 : 1;
            volatile uint32_t TMR15 : 1;
            volatile uint32_t TMR16 : 1;
            volatile uint32_t TMR17 : 1;
            volatile const uint32_t RESERVED6 : 3;
            volatile uint32_t DBG : 1;
            volatile const uint32_t RESERVED7 : 9;
        } APBRST2_B;
    } ;


    union
    {
        volatile uint32_t APBRST1;

        struct
        {
            volatile uint32_t TMR2 : 1;
            volatile uint32_t TMR3 : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t TMR6 : 1;
            volatile uint32_t TMR7 : 1;
            volatile const uint32_t RESERVED2 : 2;
            volatile uint32_t TMR14 : 1;
            volatile const uint32_t RESERVED3 : 2;
            volatile uint32_t WWDT : 1;
            volatile const uint32_t RESERVED4 : 2;
            volatile uint32_t SPI2 : 1;
            volatile const uint32_t RESERVED5 : 2;
            volatile uint32_t USART2 : 1;
            volatile uint32_t USART3 : 1;
            volatile uint32_t USART4 : 1;
            volatile uint32_t USART5RST : 1;
            volatile uint32_t I2C1 : 1;
            volatile uint32_t I2C2 : 1;
            volatile uint32_t USBD : 1;
            volatile const uint32_t RESERVED6 : 1;
            volatile uint32_t CAN : 1;
            volatile const uint32_t RESERVED7 : 1;
            volatile uint32_t CRS : 1;
            volatile uint32_t PMU : 1;
            volatile uint32_t DAC : 1;
            volatile uint32_t CEC : 1;
            volatile const uint32_t RESERVED8 : 1;
        } APBRST1_B;
    } ;


    union
    {
        volatile uint32_t AHBCLKEN;

        struct
        {
            volatile uint32_t DMA1 : 1;
            volatile uint32_t DMA2 : 1;
            volatile uint32_t SRAM : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t FMC : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t CRC : 1;
            volatile const uint32_t RESERVED3 : 10;
            volatile uint32_t PA : 1;
            volatile uint32_t PB : 1;
            volatile uint32_t PC : 1;
            volatile uint32_t PD : 1;
            volatile uint32_t PE : 1;
            volatile uint32_t PF : 1;
            volatile const uint32_t RESERVED4 : 1;
            volatile uint32_t TSC : 1;
            volatile const uint32_t RESERVED5 : 7;
        } AHBCLKEN_B;
    } ;

    union
    {
        volatile uint32_t APBCLKEN2;

        struct
        {
            volatile uint32_t SCFGCOMP : 1;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t USART6 : 1;
            volatile uint32_t USART7 : 1;
            volatile uint32_t USART8 : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t ADC : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t TMR1 : 1;
            volatile uint32_t SPI1 : 1;
            volatile const uint32_t RESERVED4 : 1;
            volatile uint32_t USART1 : 1;
            volatile const uint32_t RESERVED5 : 1;
            volatile uint32_t TMR15 : 1;
            volatile uint32_t TMR16 : 1;
            volatile uint32_t TMR17 : 1;
            volatile const uint32_t RESERVED6 : 3;
            volatile uint32_t DBG : 1;
            volatile const uint32_t RESERVED7 : 9;
        } APBCLKEN2_B;
    } ;


    union
    {
        volatile uint32_t APBCLKEN1;

        struct
        {
            volatile uint32_t TMR2 : 1;
            volatile uint32_t TMR3 : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t TMR6 : 1;
            volatile uint32_t TMR7 : 1;
            volatile const uint32_t RESERVED2 : 2;
            volatile uint32_t TMR14 : 1;
            volatile const uint32_t RESERVED3 : 2;
            volatile uint32_t WWDT : 1;
            volatile const uint32_t RESERVED4 : 2;
            volatile uint32_t SPI2 : 1;
            volatile const uint32_t RESERVED5 : 2;
            volatile uint32_t USART2 : 1;
            volatile uint32_t USART3 : 1;
            volatile uint32_t USART4 : 1;
            volatile uint32_t USART5 : 1;
            volatile uint32_t I2C1 : 1;
            volatile uint32_t I2C2 : 1;
            volatile uint32_t USBD : 1;
            volatile const uint32_t RESERVED6 : 1;
            volatile uint32_t CAN : 1;
            volatile const uint32_t RESERVED7 : 1;
            volatile uint32_t CRS : 1;
            volatile uint32_t PMU : 1;
            volatile uint32_t DAC : 1;
            volatile uint32_t CEC : 1;
            volatile const uint32_t RESERVED8 : 1;
        } APBCLKEN1_B;
    } ;


    union
    {
        volatile uint32_t BDCTRL;

        struct
        {
            volatile uint32_t LSEEN : 1;
            volatile const uint32_t LSERDYFLG : 1;
            volatile uint32_t LSEBCFG : 1;
            volatile uint32_t LSEDRVCFG : 2;
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t RTCSRCSEL : 2;
            volatile const uint32_t RESERVED2 : 5;
            volatile uint32_t RTCCLKEN : 1;
            volatile uint32_t BDRST : 1;
            volatile const uint32_t RESERVED3 : 15;
        } BDCTRL_B;
    } ;


    union
    {
        volatile uint32_t CSTS;

        struct
        {
            volatile uint32_t LSIEN : 1;
            volatile const uint32_t LSIRDYFLG : 1;
            volatile const uint32_t RESERVED1 : 21;
            volatile const uint32_t PWRRSTFLG : 1;
            volatile uint32_t RSTFLGCLR : 1;
            volatile const uint32_t OBRSTFLG : 1;
            volatile const uint32_t PINRSTFLG : 1;
            volatile const uint32_t PODRSTFLG : 1;
            volatile const uint32_t SWRSTFLG : 1;
            volatile const uint32_t IWDTRSTFLG : 1;
            volatile const uint32_t WWDTRSTFLG : 1;
            volatile const uint32_t LPWRRSTFLG : 1;
        } CSTS_B;
    } ;


    union
    {
        volatile uint32_t AHBRST;

        struct
        {
            volatile const uint32_t RESERVED1 : 17;
            volatile uint32_t PARST : 1;
            volatile uint32_t PBRST : 1;
            volatile uint32_t PCRST : 1;
            volatile uint32_t PDRST : 1;
            volatile uint32_t PERST : 1;
            volatile uint32_t PFRST : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t TSCRST : 1;
            volatile const uint32_t RESERVED3 : 7;
        } AHBRST_B;
    } ;


    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile uint32_t PLLDIVCFG : 4;
            volatile const uint32_t RESERVED1 : 28;
        } CFG2_B;
    } ;


    union
    {
        volatile uint32_t CFG3;

        struct
        {
            volatile uint32_t USART1SEL : 2;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t I2C1SEL : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t CECSEL : 1;
            volatile uint32_t USBDSEL : 1;
            volatile uint32_t ADCSEL : 1;
            volatile const uint32_t RESERVED3 : 7;
            volatile uint32_t USART2SEL : 2;
            volatile uint32_t USART3SEL : 2;
            volatile const uint32_t RESERVED4 : 12;
        } CFG3_B;
    } ;

    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t HSI14EN : 1;
            volatile const uint32_t HSI14RDFLG : 1;
            volatile uint32_t HSI14TO : 1;
            volatile uint32_t HSI14TRM : 5;
            volatile const uint32_t HSI14CAL : 8;
            volatile uint32_t HSI48EN : 1;
            volatile const uint32_t HSI48RDFLG : 1;
            volatile const uint32_t RESERVED1 : 6;
            volatile const uint32_t HSI48CAL : 8;
        } CTRL2_B;
    } ;
} RCM_T;





typedef struct
{


    union
    {
        volatile uint32_t TIME;

        struct
        {
            volatile uint32_t SECU : 4;
            volatile uint32_t SECT : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t MINU : 4;
            volatile uint32_t MINT : 3;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t HRU : 4;
            volatile uint32_t HRT : 2;
            volatile uint32_t TIMEFCFG : 1;
            volatile const uint32_t RESERVED3 : 9;
        } TIME_B;
    } ;


    union
    {
        volatile uint32_t DATE;

        struct
        {
            volatile uint32_t DAYU : 4;
            volatile uint32_t DAYT : 2;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t MONU : 4;
            volatile uint32_t MONT : 1;
            volatile uint32_t WEEKSEL : 3;
            volatile uint32_t YRU : 4;
            volatile uint32_t YRT : 4;
            volatile const uint32_t RESERVED2 : 8;
        } DATE_B;
    } ;


    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t WUCLKSEL : 3;
            volatile uint32_t TSETECFG : 1;
            volatile uint32_t RCLKDEN : 1;
            volatile uint32_t RCMCFG : 1;
            volatile uint32_t TIMEFCFG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t ALREN : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t WUTEN : 1;
            volatile uint32_t TSEN : 1;
            volatile uint32_t ALRIEN : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t WUTIEN : 1;
            volatile uint32_t TSIEN : 1;
            volatile uint32_t STCCFG : 1;
            volatile uint32_t WTCCFG : 1;
            volatile uint32_t BAKP : 1;
            volatile uint32_t CALOSEL : 1;
            volatile uint32_t POLCFG : 1;
            volatile uint32_t OUTSEL : 2;
            volatile uint32_t CALOEN : 1;
            volatile const uint32_t RESERVED4 : 8;
        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const uint32_t ALRWFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t WUTWFLG : 1;
            volatile uint32_t SOPFLG : 1;
            volatile const uint32_t INITSFLG : 1;
            volatile uint32_t RSFLG : 1;
            volatile const uint32_t RINITFLG : 1;
            volatile uint32_t INITEN : 1;
            volatile uint32_t ALRAFLG : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t WUTFLG : 1;
            volatile uint32_t TSFLG : 1;
            volatile uint32_t TSOVRFLG : 1;
            volatile uint32_t TP1FLG : 1;
            volatile uint32_t TP2FLG : 1;
            volatile const uint32_t TP3FLG : 1;
            volatile const uint32_t RCALPFLG : 1;
            volatile const uint32_t RESERVED3 : 15;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t SPSC : 15;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t APSC : 7;
            volatile const uint32_t RESERVED2 : 9;
        } PSC_B;
    } ;


    union
    {
        volatile uint32_t AUTORLD;

        struct
        {
            volatile uint32_t WUAUTORE : 15;
            volatile const uint32_t RESERVED1 : 17;
        } AUTORLD_B;
    } ;
    volatile const uint32_t RESERVED;


    union
    {
        volatile uint32_t ALRMA;

        struct
        {
            volatile uint32_t SECU : 4;
            volatile uint32_t SECT : 3;
            volatile uint32_t SECMEN : 1;
            volatile uint32_t MINU : 4;
            volatile uint32_t MINT : 3;
            volatile uint32_t MINMEN : 1;
            volatile uint32_t HRU : 4;
            volatile uint32_t HRT : 2;
            volatile uint32_t TIMEFCFG : 1;
            volatile uint32_t HRMEN : 1;
            volatile uint32_t DAYU : 4;
            volatile uint32_t DAYT : 2;
            volatile uint32_t WEEKSEL : 1;
            volatile uint32_t DATEMEN : 1;
        } ALRMA_B;
    } ;

    volatile const uint32_t RESERVED1;


    union
    {
        volatile uint32_t WRPROT;

        struct
        {
            volatile uint32_t KEY : 8;
            volatile const uint32_t RESERVED1 : 24;
        } WRPROT_B;
    } ;


    union
    {
        volatile const uint32_t SUBSEC;

        struct
        {
            volatile const uint32_t SUBSEC : 16;
            volatile const uint32_t RESERVED1 : 16;
        } SUBSEC_B;
    } ;


    union
    {
        volatile uint32_t SHIFT;

        struct
        {
            volatile uint32_t SFSEC : 15;
            volatile const uint32_t RESERVED1 : 16;
            volatile uint32_t ADD1SECEN : 1;
        } SHIFT_B;
    } ;


    union
    {
        volatile const uint32_t TSTIME;

        struct
        {
            volatile const uint32_t SECU : 4;
            volatile const uint32_t SECT : 3;
            volatile const uint32_t RESERVED1 : 1;
            volatile const uint32_t MINU : 4;
            volatile const uint32_t MINT : 3;
            volatile const uint32_t RESERVED2 : 1;
            volatile const uint32_t HRU : 4;
            volatile const uint32_t HRT : 2;
            volatile const uint32_t TIMEFCFG : 1;
            volatile const uint32_t RESERVED3 : 9;
        } TSTIME_B;
    } ;


    union
    {
        volatile const uint32_t TSDATE;

        struct
        {
            volatile const uint32_t DAYU : 4;
            volatile const uint32_t DAYT : 2;
            volatile const uint32_t RESERVED1 : 2;
            volatile const uint32_t MONU : 4;
            volatile const uint32_t MONT : 1;
            volatile const uint32_t WEEKSEL : 3;
            volatile const uint32_t RESERVED2 : 16;
        } TSDATE_B;
    } ;


    union
    {
        volatile const uint32_t TSSUBSEC;

        struct
        {
            volatile const uint32_t SUBSEC : 16;
            volatile const uint32_t RESERVED1 : 16;
        } TSSUBSEC_B;
    } ;


    union
    {
        volatile uint32_t CAL;

        struct
        {
            volatile uint32_t RECALF : 9;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t CAL16CFG : 1;
            volatile uint32_t CAL8CFG : 1;
            volatile uint32_t ICALFEN : 1;
            volatile const uint32_t RESERVED2 : 16;
        } CAL_B;
    } ;


    union
    {
        volatile uint32_t TACFG;

        struct
        {
            volatile uint32_t TP1EN : 1;
            volatile uint32_t TP1ALCFG : 1;
            volatile uint32_t TPIEN : 1;
            volatile uint32_t TP2EN : 1;
            volatile uint32_t TP2ALCFG : 1;
            volatile uint32_t TP3EN : 1;
            volatile uint32_t TP3ALCFG : 1;
            volatile uint32_t TPTSEN : 1;
            volatile uint32_t TPSFSEL : 3;
            volatile uint32_t TPFCSEL : 2;
            volatile uint32_t TPPRDUSEL : 2;
            volatile uint32_t TPPUDIS : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t PC13VAL : 1;
            volatile uint32_t PC13EN : 1;
            volatile uint32_t PC14VAL : 1;
            volatile uint32_t PC14EN : 1;
            volatile uint32_t PC15VAL : 1;
            volatile uint32_t PC15EN : 1;
            volatile const uint32_t RESERVED2 : 8;
        } TACFG_B;
    } ;


    union
    {
        volatile uint32_t ALRMASS;

        struct
        {
            volatile uint32_t SUBSEC : 15;
            volatile const uint32_t RESERVED1 : 9;
            volatile uint32_t MASKSEL : 4;
            volatile const uint32_t RESERVED2 : 4;
        } ALRMASS_B;
    } ;

    volatile const uint32_t RESERVED2[2];

    union
    {
        volatile uint32_t BAKP0;

        struct
        {
            volatile uint32_t BAKP : 32;
        } BAKP0_B;
    } ;

    union
    {
        volatile uint32_t BAKP1;

        struct
        {
            volatile uint32_t BAKP : 32;
        } BAKP1_B;
    } ;
    union
    {
        volatile uint32_t BAKP2;

        struct
        {
            volatile uint32_t BAKP : 32;
        } BAKP2_B;
    } ;
    union
    {
        volatile uint32_t BAKP3;

        struct
        {
            volatile uint32_t BAKP : 32;
        } BAKP3_B;
    } ;
    union
    {
        volatile uint32_t BAKP4;

        struct
        {
            volatile uint32_t BAKP : 32;
        } BAKP4_B;
    } ;
} RTC_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t CPHA : 1;
            volatile uint32_t CPOL : 1;
            volatile uint32_t MSMCFG : 1;
            volatile uint32_t BRSEL : 3;
            volatile uint32_t SPIEN : 1;
            volatile uint32_t LSBSEL : 1;
            volatile uint32_t ISSEL : 1;
            volatile uint32_t SSEN : 1;
            volatile uint32_t RXOMEN : 1;
            volatile uint32_t CRCLSEL : 1;
            volatile uint32_t CRCNXT : 1;
            volatile uint32_t CRCEN : 1;
            volatile uint32_t BMOEN : 1;
            volatile uint32_t BMEN : 1;
            volatile const uint32_t RESERVED1 : 16;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t RXDEN : 1;
            volatile uint32_t TXDEN : 1;
            volatile uint32_t SSOEN : 1;
            volatile uint32_t NSSPEN : 1;
            volatile uint32_t FRFCFG : 1;
            volatile uint32_t ERRIEN : 1;
            volatile uint32_t RXBNEIEN : 1;
            volatile uint32_t TXBEIEN : 1;
            volatile uint32_t DSCFG : 4;
            volatile uint32_t FRTCFG : 1;
            volatile uint32_t LDRX : 1;
            volatile uint32_t LDTX : 1;
            volatile const uint32_t RESERVED1 : 17;
        } CTRL2_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile const uint32_t RXBNEFLG : 1;
            volatile const uint32_t TXBEFLG : 1;
            volatile const uint32_t SCHDIR : 1;
            volatile const uint32_t UDRFLG : 1;
            volatile uint32_t CRCEFLG : 1;
            volatile const uint32_t MEFLG : 1;
            volatile const uint32_t OVRFLG : 1;
            volatile const uint32_t BSYFLG : 1;
            volatile const uint32_t FRECFG : 1;
            volatile const uint32_t FRLSEL : 2;
            volatile const uint32_t FTLSEL : 2;
            volatile const uint32_t RESERVED1 : 19;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t DATA;

        struct
        {
            volatile uint32_t DATA : 16;
            volatile const uint32_t RESERVED1 : 16;
        } DATA_B;
    } ;


    union
    {
        volatile uint32_t CRCPOLY;

        struct
        {
            volatile uint32_t CRCPOLY : 16;
            volatile const uint32_t RESERVED1 : 16;
        } CRCPOLY_B;
    } ;


    union
    {

        volatile const uint32_t RXCRC;

        struct
        {
            volatile const uint32_t RXCRC : 16;
            volatile const uint32_t RESERVED1 : 16;
        } RXCRC_B;
    } ;


    union
    {

        volatile const uint32_t TXCRC;

        struct
        {
            volatile const uint32_t TXCRC : 16;
            volatile const uint32_t RESERVED1 : 16;
        } TXCRC_B;
    } ;


    union
    {
        volatile uint32_t I2SCFG;

        struct
        {
            volatile uint32_t CHLEN : 1;
            volatile uint32_t DATALEN : 2;
            volatile uint32_t CPOL : 1;
            volatile uint32_t I2SSSEL : 2;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t PFSSEL : 1;
            volatile uint32_t I2SMOD : 2;
            volatile uint32_t I2SEN : 1;
            volatile uint32_t MODESEL : 1;
            volatile const uint32_t RESERVED2 : 20;
        } I2SCFG_B;
    } ;


    union
    {
        volatile uint32_t I2SPSC;

        struct
        {
            volatile uint32_t I2SPSC : 8;
            volatile uint32_t ODDPSC : 1;
            volatile uint32_t MCOEN : 1;
            volatile const uint32_t RESERVED1 : 22;
        } I2SPSC_B;
    } ;
} SPI_T;





typedef struct
{

    union
    {
        volatile uint32_t CFG1;

        struct
        {
            volatile uint32_t MMSEL : 2;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t IRSEL : 2;
            volatile uint32_t ADCDMARMP : 1;
            volatile uint32_t USART1TXRMP : 1;
            volatile uint32_t USART1RXRMP : 1;
            volatile uint32_t TMR16DMARMP : 1;
            volatile uint32_t TMR17DMARMP : 1;
            volatile uint32_t TMR16DMARMP2 : 1;
            volatile uint32_t TMR17DMARMP2 : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t I2CPB6FMP : 1;
            volatile uint32_t I2CPB7FMP : 1;
            volatile uint32_t I2CPB8FMP : 1;
            volatile uint32_t I2CPB9FMP : 1;
            volatile uint32_t I2C1FMP : 1;
            volatile uint32_t I2C2FMP : 1;
            volatile uint32_t I2CPA9FMP : 1;
            volatile uint32_t I2CPA10FMP : 1;
            volatile uint32_t SPI2DMARMP : 1;
            volatile uint32_t USART2DMARMP : 1;
            volatile uint32_t USART3DMARMP : 1;
            volatile uint32_t I2C1DMARMP : 1;
            volatile uint32_t TMR1DMARMP : 1;
            volatile uint32_t TMR2DMARMP : 1;
            volatile uint32_t TMR3DMARMP : 1;
            volatile const uint32_t RESERVED3 : 1;
        } CFG1_B;
    } ;
    volatile const uint32_t RESERVED;


    union
    {

        volatile uint32_t EINTCFG1;

        struct
        {
            volatile uint32_t EINT0 : 4;
            volatile uint32_t EINT1 : 4;
            volatile uint32_t EINT2 : 4;
            volatile uint32_t EINT3 : 4;
            volatile const uint32_t RESERVED1 : 16;
        } EINTCFG1_B;
    } ;


    union
    {
        volatile uint32_t EINTCFG2;

        struct
        {
            volatile uint32_t EINT4 : 4;
            volatile uint32_t EINT5 : 4;
            volatile uint32_t EINT6 : 4;
            volatile uint32_t EINT7 : 4;
            volatile const uint32_t RESERVED1 : 16;
        } EINTCFG2_B;
    } ;


    union
    {
        volatile uint32_t EINTCFG3;

        struct
        {
            volatile uint32_t EINT8 : 4;
            volatile uint32_t EINT9 : 4;
            volatile uint32_t EINT10 : 4;
            volatile uint32_t EINT11 : 4;
            volatile const uint32_t RESERVED1 : 16;
        } EINTCFG3_B;
    } ;


    union
    {
        volatile uint32_t EINTCFG4;

        struct
        {
            volatile uint32_t EINT12 : 4;
            volatile uint32_t EINT13 : 4;
            volatile uint32_t EINT14 : 4;
            volatile uint32_t EINT15 : 4;
            volatile const uint32_t RESERVED1 : 16;
        } EINTCFG4_B;
    } ;


    union
    {
        volatile uint32_t CFG2;

        struct
        {
            volatile uint32_t LOCK : 1;
            volatile uint32_t SRAMLOCK : 1;
            volatile uint32_t PVDLOCK : 1;
            volatile const uint32_t RESERVED1 : 5;
            volatile uint32_t SRAMEFLG : 1;
            volatile const uint32_t RESERVED2 : 23;
        } CFG2_B;
    } ;
} SYSCFG_T;





typedef struct
{

    union
    {
        volatile const uint32_t IOGCNT;

        struct
        {
            volatile const uint32_t CNTVAL : 14;
            volatile const uint32_t RESERVED1 : 18;
        } IOGCNT_B;
    };
} TSC_IOGroupRegister_T;

typedef struct
{

    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t TSCEN : 1;
            volatile uint32_t STARTAFLG : 1;
            volatile uint32_t AMCFG : 1;
            volatile uint32_t SYNPPOL : 1;
            volatile uint32_t IODEFCFG : 1;
            volatile uint32_t MCNTVSEL : 3;
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t PGCDFSEL : 3;
            volatile uint32_t SSCDFSEL : 1;
            volatile uint32_t SSEN : 1;
            volatile uint32_t SSERRVSEL : 7;
            volatile uint32_t CTPLSEL : 4;
            volatile uint32_t CTPHSEL : 4;
        } CTRL_B;
    } ;


    union
    {
        volatile uint32_t INTEN;

        struct
        {
            volatile uint32_t EOAIEN : 1;
            volatile uint32_t MCEIEN : 1;
            volatile const uint32_t RESERVED1 : 30;
        } INTEN_B;
    } ;


    union
    {
        volatile uint32_t INTFCLR;

        struct
        {
            volatile uint32_t EOAICLR : 1;
            volatile uint32_t MCEICLR : 1;
            volatile const uint32_t RESERVED1 : 30;
        } INTFCLR_B;
    } ;


    union
    {
        volatile uint32_t INTSTS;

        struct
        {
            volatile uint32_t EOAFLG : 1;
            volatile uint32_t MCEFLG : 1;
            volatile const uint32_t RESERVED1 : 30;
        } INTSTS_B;
    } ;


    union
    {
        volatile uint32_t IOHCTRL;

        struct
        {
            volatile uint32_t G1P1 : 1;
            volatile uint32_t G1P2 : 1;
            volatile uint32_t G1P3 : 1;
            volatile uint32_t G1P4 : 1;
            volatile uint32_t G2P1 : 1;
            volatile uint32_t G2P2 : 1;
            volatile uint32_t G2P3 : 1;
            volatile uint32_t G2P4 : 1;
            volatile uint32_t G3P1 : 1;
            volatile uint32_t G3P2 : 1;
            volatile uint32_t G3P3 : 1;
            volatile uint32_t G3P4 : 1;
            volatile uint32_t G4P1 : 1;
            volatile uint32_t G4P2 : 1;
            volatile uint32_t G4P3 : 1;
            volatile uint32_t G4P4 : 1;
            volatile uint32_t G5P1 : 1;
            volatile uint32_t G5P2 : 1;
            volatile uint32_t G5P3 : 1;
            volatile uint32_t G5P4 : 1;
            volatile uint32_t G6P1 : 1;
            volatile uint32_t G6P2 : 1;
            volatile uint32_t G6P3 : 1;
            volatile uint32_t G6P4 : 1;
            volatile const uint32_t RESERVED1 : 8;
        } IOHCTRL_B;
    } ;
    volatile const uint32_t RESERVED;


    union
    {
        volatile uint32_t IOASWCTRL;

        struct
        {
            volatile uint32_t G1P1 : 1;
            volatile uint32_t G1P2 : 1;
            volatile uint32_t G1P3 : 1;
            volatile uint32_t G1P4 : 1;
            volatile uint32_t G2P1 : 1;
            volatile uint32_t G2P2 : 1;
            volatile uint32_t G2P3 : 1;
            volatile uint32_t G2P4 : 1;
            volatile uint32_t G3P1 : 1;
            volatile uint32_t G3P2 : 1;
            volatile uint32_t G3P3 : 1;
            volatile uint32_t G3P4 : 1;
            volatile uint32_t G4P1 : 1;
            volatile uint32_t G4P2 : 1;
            volatile uint32_t G4P3 : 1;
            volatile uint32_t G4P4 : 1;
            volatile uint32_t G5P1 : 1;
            volatile uint32_t G5P2 : 1;
            volatile uint32_t G5P3 : 1;
            volatile uint32_t G5P4 : 1;
            volatile uint32_t G6P1 : 1;
            volatile uint32_t G6P2 : 1;
            volatile uint32_t G6P3 : 1;
            volatile uint32_t G6P4 : 1;
            volatile const uint32_t RESERVED1 : 8;
        } IOASWCTRL_B;
    } ;
    volatile const uint32_t RESERVED1;


    union
    {
        volatile uint32_t IOSMPCTRL;

        struct
        {
            volatile uint32_t G1P1 : 1;
            volatile uint32_t G1P2 : 1;
            volatile uint32_t G1P3 : 1;
            volatile uint32_t G1P4 : 1;
            volatile uint32_t G2P1 : 1;
            volatile uint32_t G2P2 : 1;
            volatile uint32_t G2P3 : 1;
            volatile uint32_t G2P4 : 1;
            volatile uint32_t G3P1 : 1;
            volatile uint32_t G3P2 : 1;
            volatile uint32_t G3P3 : 1;
            volatile uint32_t G3P4 : 1;
            volatile uint32_t G4P1 : 1;
            volatile uint32_t G4P2 : 1;
            volatile uint32_t G4P3 : 1;
            volatile uint32_t G4P4 : 1;
            volatile uint32_t G5P1 : 1;
            volatile uint32_t G5P2 : 1;
            volatile uint32_t G5P3 : 1;
            volatile uint32_t G5P4 : 1;
            volatile uint32_t G6P1 : 1;
            volatile uint32_t G6P2 : 1;
            volatile uint32_t G6P3 : 1;
            volatile uint32_t G6P4 : 1;
            volatile const uint32_t RESERVED1 : 8;
        } IOSMPCTRL_B;
    } ;
    volatile const uint32_t RESERVED2;


    union
    {
        volatile uint32_t IOCHCTRL;

        struct
        {
            volatile uint32_t G1P1 : 1;
            volatile uint32_t G1P2 : 1;
            volatile uint32_t G1P3 : 1;
            volatile uint32_t G1P4 : 1;
            volatile uint32_t G2P1 : 1;
            volatile uint32_t G2P2 : 1;
            volatile uint32_t G2P3 : 1;
            volatile uint32_t G2P4 : 1;
            volatile uint32_t G3P1 : 1;
            volatile uint32_t G3P2 : 1;
            volatile uint32_t G3P3 : 1;
            volatile uint32_t G3P4 : 1;
            volatile uint32_t G4P1 : 1;
            volatile uint32_t G4P2 : 1;
            volatile uint32_t G4P3 : 1;
            volatile uint32_t G4P4 : 1;
            volatile uint32_t G5P1 : 1;
            volatile uint32_t G5P2 : 1;
            volatile uint32_t G5P3 : 1;
            volatile uint32_t G5P4 : 1;
            volatile uint32_t G6P1 : 1;
            volatile uint32_t G6P2 : 1;
            volatile uint32_t G6P3 : 1;
            volatile uint32_t G6P4 : 1;
            volatile const uint32_t RESERVED1 : 8;
        } IOCHCTRL_B;
    } ;
    volatile const uint32_t RESERVED3;


    union
    {
        volatile uint32_t IOGCSTS;

        struct
        {
            volatile uint32_t G1EN : 1;
            volatile uint32_t G2EN : 1;
            volatile uint32_t G3EN : 1;
            volatile uint32_t G4EN : 1;
            volatile uint32_t G5EN : 1;
            volatile uint32_t G6EN : 1;
            volatile uint32_t G7EN : 1;
            volatile uint32_t G8EN : 1;
            volatile const uint32_t RESERVED1 : 8;
            volatile const uint32_t G1STS : 1;
            volatile const uint32_t G2STS : 1;
            volatile const uint32_t G3STS : 1;
            volatile const uint32_t G4STS : 1;
            volatile const uint32_t G5STS : 1;
            volatile const uint32_t G6STS : 1;
            volatile const uint32_t G7STS : 1;
            volatile const uint32_t G8STS : 1;
            volatile const uint32_t RESERVED2 : 8;
        } IOGCSTS_B;
    } ;

    TSC_IOGroupRegister_T IOGxCNT[8];
} TSC_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t CNTEN : 1;
            volatile uint32_t UD : 1;
            volatile uint32_t URSSEL : 1;
            volatile uint32_t SPMEN : 1;
            volatile uint32_t CNTDIR : 1;
            volatile uint32_t CAMSEL : 2;
            volatile uint32_t ARPEN : 1;
            volatile uint32_t CLKDIV : 2;
            volatile const uint32_t RESERVED1 : 22;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile uint32_t CCPEN : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t CCUSEL : 1;
            volatile uint32_t CCDSEL : 1;
            volatile uint32_t MMSEL : 3;
            volatile uint32_t TI1SEL : 1;
            volatile uint32_t OC1OIS : 1;
            volatile uint32_t OC1NOIS : 1;
            volatile uint32_t OC2OIS : 1;
            volatile uint32_t OC2NOIS : 1;
            volatile uint32_t OC3OIS : 1;
            volatile uint32_t OC3NOIS : 1;
            volatile uint32_t OC4OIS : 1;
            volatile const uint32_t RESERVED2 : 17;
        } CTRL2_B;
    } ;


    union
    {
        volatile uint32_t SMCTRL;

        struct
        {
            volatile uint32_t SMFSEL : 3;
            volatile uint32_t OCCSEL : 1;
            volatile uint32_t TRGSEL : 3;
            volatile uint32_t MSMEN : 1;
            volatile uint32_t ETFCFG : 4;
            volatile uint32_t ETPCFG : 2;
            volatile uint32_t ECEN : 1;
            volatile uint32_t ETPOL : 1;
            volatile const uint32_t RESERVED1 : 16;
        } SMCTRL_B;
    } ;


    union
    {
        volatile uint32_t DIEN;

        struct
        {
            volatile uint32_t UIEN : 1;
            volatile uint32_t CC1IEN : 1;
            volatile uint32_t CC2IEN : 1;
            volatile uint32_t CC3IEN : 1;
            volatile uint32_t CC4IEN : 1;
            volatile uint32_t COMIEN : 1;
            volatile uint32_t TRGIEN : 1;
            volatile uint32_t BRKIEN : 1;
            volatile uint32_t UDIEN : 1;
            volatile uint32_t CC1DEN : 1;
            volatile uint32_t CC2DEN : 1;
            volatile uint32_t CC3DEN : 1;
            volatile uint32_t CC4DEN : 1;
            volatile uint32_t COMDEN : 1;
            volatile uint32_t TRGDEN : 1;
            volatile const uint32_t RESERVED1 : 17;
        } DIEN_B;
    } ;


    union
    {
        volatile uint32_t STS;

        struct
        {
            volatile uint32_t UIFLG : 1;
            volatile uint32_t CC1IFLG : 1;
            volatile uint32_t CC2IFLG : 1;
            volatile uint32_t CC3IFLG : 1;
            volatile uint32_t CC4IFLG : 1;
            volatile uint32_t COMIFLG : 1;
            volatile uint32_t TRGIFLG : 1;
            volatile uint32_t BRKIFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t CC1RCFLG : 1;
            volatile uint32_t CC2RCFLG : 1;
            volatile uint32_t CC3RCFLG : 1;
            volatile uint32_t CC4RCFLG : 1;
            volatile const uint32_t RESERVED2 : 19;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t CEG;

        struct
        {
            volatile uint32_t UEG : 1;
            volatile uint32_t CC1EG : 1;
            volatile uint32_t CC2EG : 1;
            volatile uint32_t CC3EG : 1;
            volatile uint32_t CC4EG : 1;
            volatile uint32_t COMG : 1;
            volatile uint32_t TEG : 1;
            volatile uint32_t BEG : 1;
            volatile const uint32_t RESERVED1 : 24;
        } SCEG_B;
    } ;

    union
    {

        union
        {
            volatile uint32_t CCM1_OUTPUT;

            struct
            {
                volatile uint32_t CC1SEL : 2;
                volatile uint32_t OC1FEN : 1;
                volatile uint32_t OC1PEN : 1;
                volatile uint32_t OC1MOD : 3;
                volatile uint32_t OC1CEN : 1;
                volatile uint32_t CC2SEL : 2;
                volatile uint32_t OC2FEN : 1;
                volatile uint32_t OC2PEN : 1;
                volatile uint32_t OC2MOD : 3;
                volatile uint32_t OC2CEN : 1;
                volatile const uint32_t RESERVED1 : 16;
            } CCM1_OUTPUT_B;
        } ;


        union
        {
            volatile uint32_t CCM1_INPUT;

            struct
            {
                volatile uint32_t CC1SEL : 2;
                volatile uint32_t IC1PSC : 2;
                volatile uint32_t IC1F : 4;
                volatile uint32_t CC2SEL : 2;
                volatile uint32_t IC2PSC : 2;
                volatile uint32_t IC2F : 4;
                volatile const uint32_t RESERVED1 : 16;
            } CCM1_INPUT_B;
        } ;
    };

    union
    {

        union
        {
            volatile uint32_t CCM2_OUTPUT;

            struct
            {
                volatile uint32_t CC3SEL : 2;
                volatile uint32_t OC3FEN : 1;
                volatile uint32_t OC3PEN : 1;
                volatile uint32_t OC3MOD : 3;
                volatile uint32_t OC3CEN : 1;
                volatile uint32_t CC4SEL : 2;
                volatile uint32_t OC4FEN : 1;
                volatile uint32_t OC4PEN : 1;
                volatile uint32_t OC4MOD : 3;
                volatile uint32_t OC4CEN : 1;
                volatile const uint32_t RESERVED1 : 16;
            } CCM2_OUTPUT_B;
        } ;


        union
        {
            volatile uint32_t CCM2_INPUT;

            struct
            {
                volatile uint32_t CC3SEL : 2;
                volatile uint32_t IC3PSC : 2;
                volatile uint32_t IC3F : 4;
                volatile uint32_t CC4SEL : 2;
                volatile uint32_t IC4PSC : 2;
                volatile uint32_t IC4F : 4;
                volatile const uint32_t RESERVED1 : 16;
            } CCM2_INPUT_B;
        } ;
    };


    union
    {
        volatile uint32_t CCEN;

        struct
        {
            volatile uint32_t CC1EN : 1;
            volatile uint32_t CC1POL : 1;
            volatile uint32_t CC1NEN : 1;
            volatile uint32_t CC1NPOL : 1;
            volatile uint32_t CC2EN : 1;
            volatile uint32_t CC2POL : 1;
            volatile uint32_t CC2NEN : 1;
            volatile uint32_t CC2NPOL : 1;
            volatile uint32_t CC3EN : 1;
            volatile uint32_t CC3POL : 1;
            volatile uint32_t CC3NEN : 1;
            volatile uint32_t CC3NPOL : 1;
            volatile uint32_t CC4EN : 1;
            volatile uint32_t CC4POL : 1;
            volatile const uint32_t RESERVED1 : 18;
        } CCEN_B;
    } ;


    union
    {
        volatile uint32_t CNT;

        struct
        {
            volatile uint32_t CNT : 32;
        } CNT_B;
    } ;


    union
    {
        volatile uint32_t PSC;

        struct
        {
            volatile uint32_t PSC : 16;
            volatile const uint32_t RESERVED1 : 16;
        } PSC_B;
    } ;


    union
    {
        volatile uint32_t AUTORLD;

        struct
        {
            volatile uint32_t AUTORLD : 32;
        } AUTORLD_B;
    } ;


    union
    {
        volatile uint32_t REPCNT;

        struct
        {
            volatile uint32_t REPCNT : 8;
            volatile const uint32_t RESERVED1 : 24;
        } REPCNT_B;
    } ;


    union
    {
        volatile uint32_t CC1;

        struct
        {
            volatile uint32_t CC1 : 32;
        } CC1_B;
    } ;


    union
    {
        volatile uint32_t CC2;

        struct
        {
            volatile uint32_t CC2 : 32;
        } CC2_B;
    } ;


    union
    {
        volatile uint32_t CC3;

        struct
        {
            volatile uint32_t CC3 : 32;
        } CC3_B;
    } ;


    union
    {
        volatile uint32_t CC4;

        struct
        {
            volatile uint32_t CC4 : 32;
        } CC4_B;
    } ;


    union
    {
        volatile uint32_t BDT;

        struct
        {
            volatile uint32_t DTS : 8;
            volatile uint32_t LOCKCFG : 2;
            volatile uint32_t IMOS : 1;
            volatile uint32_t RMOS : 1;
            volatile uint32_t BRKEN : 1;
            volatile uint32_t BRKPOL : 1;
            volatile uint32_t AOEN : 1;
            volatile uint32_t MOEN : 1;
            volatile const uint32_t RESERVED1 : 16;
        } BDT_B;
    } ;


    union
    {
        volatile uint32_t DCTRL;

        struct
        {
            volatile uint32_t DBADDR : 5;
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t DBLEN : 5;
            volatile const uint32_t RESERVED2 : 19;
        } DCTRL_B;
    } ;


    union
    {
        volatile uint32_t DMADDR;

        struct
        {
            volatile uint32_t DMADDR : 16;
            volatile const uint32_t RESERVED1 : 16;
        } DMADDR_B;
    } ;


    union
    {
        volatile uint32_t OPT;

        struct
        {
            volatile uint32_t RMPSEL : 2;
            volatile const uint32_t RESERVED1 : 30;
        } OPT_B;
    } ;
} TMR_T;





typedef struct
{

    union
    {
        volatile uint32_t CTRL1;

        struct
        {
            volatile uint32_t UEN : 1;
            volatile uint32_t USWMEN : 1;
            volatile uint32_t RXEN : 1;
            volatile uint32_t TXEN : 1;
            volatile uint32_t IDLEIEN : 1;
            volatile uint32_t RXBNEIEN : 1;
            volatile uint32_t TXCIEN : 1;
            volatile uint32_t TXBEIEN : 1;
            volatile uint32_t PEIEN : 1;
            volatile uint32_t PCFG : 1;
            volatile uint32_t PCEN : 1;
            volatile uint32_t WUPMCFG : 1;
            volatile uint32_t DBLCFG0 : 1;
            volatile uint32_t RXMUTEEN : 1;
            volatile uint32_t CMIEN : 1;
            volatile uint32_t OSMCFG : 1;
            volatile uint32_t DDLTEN : 5;
            volatile uint32_t DLTEN : 5;
            volatile uint32_t RXTOIEN : 1;
            volatile uint32_t EOBIEN : 1;
            volatile uint32_t DBLCFG1 : 1;
            volatile const uint32_t RESERVED2 : 3;
        } CTRL1_B;
    } ;


    union
    {
        volatile uint32_t CTRL2;

        struct
        {
            volatile const uint32_t RESERVED1 : 4;
            volatile uint32_t ADDRLEN : 1;
            volatile uint32_t LBDLCFG : 1;
            volatile uint32_t LBDIEN : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t LBCPOEN : 1;
            volatile uint32_t CPHA : 1;
            volatile uint32_t CPOL : 1;
            volatile uint32_t CLKEN : 1;
            volatile uint32_t STOPCFG : 2;
            volatile uint32_t LINMEN : 1;
            volatile uint32_t SWAPEN : 1;
            volatile uint32_t RXINVEN : 1;
            volatile uint32_t TXINVEN : 1;
            volatile uint32_t BINVEN : 1;
            volatile uint32_t MSBFEN : 1;
            volatile uint32_t ABRDEN : 1;
            volatile uint32_t ABRDCFG : 2;
            volatile uint32_t RXTODEN : 1;
            volatile uint32_t ADDRL : 4;
            volatile uint32_t ADDRH : 4;
        } CTRL2_B;
    } ;


    union
    {
        volatile uint32_t CTRL3;

        struct
        {
            volatile uint32_t ERRIEN : 1;
            volatile uint32_t IREN : 1;
            volatile uint32_t IRLPEN : 1;
            volatile uint32_t HDEN : 1;
            volatile uint32_t SCNACKEN : 1;
            volatile uint32_t SCEN : 1;
            volatile uint32_t DMARXEN : 1;
            volatile uint32_t DMATXEN : 1;
            volatile uint32_t RTSEN : 1;
            volatile uint32_t CTSEN : 1;
            volatile uint32_t CTSIEN : 1;
            volatile uint32_t SAMCFG : 1;
            volatile uint32_t OVRDEDIS : 1;
            volatile uint32_t DDISRXEEN : 1;
            volatile uint32_t DEN : 1;
            volatile uint32_t DPCFG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t SCARCCFG : 3;
            volatile uint32_t WSIFLGSEL : 2;
            volatile uint32_t WSMIEN : 1;
            volatile const uint32_t RESERVED2 : 9;
        } CTRL3_B;
    } ;


    union
    {
        volatile uint32_t BR;

        struct
        {
            volatile uint32_t FBR : 4;
            volatile uint32_t MBR : 12;
            volatile const uint32_t RESERVED1 : 16;
        } BR_B;
    } ;


    union
    {
        volatile uint32_t GTPSC;

        struct
        {
            volatile uint32_t PSC : 8;
            volatile uint32_t GRDT : 8;
            volatile const uint32_t RESERVED1 : 16;
        } GTPSC_B;
    } ;


    union
    {
        volatile uint32_t RXTO;

        struct
        {
            volatile uint32_t RXTO : 24;
            volatile uint32_t BLEN : 8;
        } RXTO_B;
    } ;


    union
    {
        volatile uint32_t REQUEST;

        struct
        {
            volatile uint32_t ABRDQ : 1;
            volatile uint32_t TXBFQ : 1;
            volatile uint32_t MUTEQ : 1;
            volatile uint32_t RXDFQ : 1;
            volatile uint32_t TXDFQ : 1;
            volatile const uint32_t RESERVED1 : 27;
        } REQUEST_B;
    } ;


    union
    {
        volatile const uint32_t STS;

        struct
        {
            volatile const uint32_t PEFLG : 1;
            volatile const uint32_t FEFLG : 1;
            volatile const uint32_t NEFLG : 1;
            volatile const uint32_t OVREFLG : 1;
            volatile const uint32_t IDLEFLG : 1;
            volatile const uint32_t RXBNEFLG : 1;
            volatile const uint32_t TXCFLG : 1;
            volatile const uint32_t TXBEFLG : 1;
            volatile const uint32_t LBDFLG : 1;
            volatile const uint32_t CTSFLG : 1;
            volatile const uint32_t CTSCFG : 1;
            volatile const uint32_t RXTOFLG : 1;
            volatile const uint32_t EOBFLG : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile const uint32_t ABRDEFLG : 1;
            volatile const uint32_t ABRDFLG : 1;
            volatile const uint32_t BSYFLG : 1;
            volatile const uint32_t CMFLG : 1;
            volatile const uint32_t TXBFFLG : 1;
            volatile const uint32_t RXWFMUTE : 1;
            volatile const uint32_t WSMFLG : 1;
            volatile const uint32_t TXENACKFLG : 1;
            volatile const uint32_t RXENACKFLG : 1;
            volatile const uint32_t RESERVED2 : 9;
        } STS_B;
    } ;


    union
    {
        volatile uint32_t INTFCLR;

        struct
        {
            volatile uint32_t PECLR : 1;
            volatile uint32_t FECLR : 1;
            volatile uint32_t NECLR : 1;
            volatile uint32_t OVRECLR : 1;
            volatile uint32_t IDLECLR : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t TXCCLR : 1;
            volatile const uint32_t RESERVED2 : 1;
            volatile uint32_t LBDCLR : 1;
            volatile uint32_t CTSCLR : 1;
            volatile const uint32_t RESERVED3 : 1;
            volatile uint32_t RXTOCLR : 1;
            volatile uint32_t EOBCLR : 1;
            volatile const uint32_t RESERVED4 : 4;
            volatile uint32_t CMCLR : 1;
            volatile const uint32_t RESERVED5 : 2;
            volatile uint32_t WSMCLR : 1;
            volatile const uint32_t RESERVED6 : 11;
        } INTFCLR_B;
    } ;


    union
    {
        volatile const uint32_t RXDATA;

        struct
        {
            volatile const uint32_t RXDATA : 9;
            volatile const uint32_t RESERVED1 : 23;
        } RXDATA_B;
    } ;


    union
    {
        volatile uint32_t TXDATA;

        struct
        {
            volatile uint32_t TXDATA : 9;
            volatile const uint32_t RESERVED1 : 23;
        } TXDATA_B;
    } ;
} USART_T;





typedef struct
{
    union
    {

        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t CNT : 7;
            volatile uint32_t WWDTEN : 1;
            volatile const uint32_t RESERVED1 : 24;
        } CTRL_B;
    } ;

    union
    {

        volatile uint32_t CFG;

        struct
        {
            volatile uint32_t WIN : 7;
            volatile uint32_t TBPSC : 2;
            volatile uint32_t EWIEN : 1;
            volatile const uint32_t RESERVED1 : 22;
        } CFG_B;
    } ;

    union
    {

        volatile uint32_t STS;

        struct
        {
            volatile uint32_t EWIFLG : 1;
            volatile const uint32_t RESERVED1 : 31;
        } STS_B;
    } ;
} WWDT_T;





typedef union
{
    volatile uint32_t EP;

    struct
    {
        volatile uint32_t ADDR : 4;
        volatile uint32_t TXSTS : 2;
        volatile uint32_t TXDTOG : 1;
        volatile uint32_t CTFT : 1;
        volatile uint32_t KIND : 1;
        volatile uint32_t TYPE : 2;
        volatile uint32_t SETUP : 1;
        volatile uint32_t RXSTS : 2;
        volatile uint32_t RXDTOG : 1;
        volatile uint32_t CTFR : 1;
        volatile const uint32_t RESERVED : 16;
    }EP_B;
}USB_EP_REG_T;

typedef struct
{

    USB_EP_REG_T EP[8];

    volatile uint32_t RESERVED1[8];




    union
    {
        volatile uint32_t CTRL;

        struct
        {
            volatile uint32_t FORRST : 1;
            volatile uint32_t PWRDOWN : 1;
            volatile uint32_t LPWREN : 1;
            volatile uint32_t FORSUS : 1;
            volatile uint32_t WKUPREQ : 1;
            volatile uint32_t L1WKUPREQ : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t L1STSREQIM : 1;
            volatile uint32_t ESOFIEN : 1;
            volatile uint32_t SOFIEN : 1;
            volatile uint32_t RSTIEN : 1;
            volatile uint32_t SUSIEN : 1;
            volatile uint32_t WKUPIEN : 1;
            volatile uint32_t ERRIEN : 1;
            volatile uint32_t PMAOUIEN : 1;
            volatile uint32_t CTRIEN : 1;
            volatile const uint32_t RESERVED2 : 16;
        }CTRL_B;
    };




    union
    {
        volatile uint32_t INTSTS;

        struct
        {
            volatile uint32_t EPID : 4;
            volatile uint32_t DOT : 1;
            volatile const uint32_t RESERVED1 : 2;
            volatile uint32_t L1STSREQ : 1;
            volatile uint32_t ESOFFLG : 1;
            volatile uint32_t SOFFLG : 1;
            volatile uint32_t RSTREQ : 1;
            volatile uint32_t SUSREQ : 1;
            volatile uint32_t WUPREQ : 1;
            volatile uint32_t ERRFLG : 1;
            volatile uint32_t PMOFLG : 1;
            volatile uint32_t CTFLG : 1;
            volatile const uint32_t RESERVED2 : 16;
        }INTSTS_B;
    };




    union
    {
        volatile uint32_t FRANUM;

        struct
        {
            volatile uint32_t FRANUM : 11;
            volatile uint32_t LSOFNUM : 2;
            volatile uint32_t LOCK : 1;
            volatile uint32_t RXDMSTS : 1;
            volatile uint32_t RXDPSTS : 1;
            volatile const uint32_t RESERVED : 16;
        }FRANUM_B;
    };




    union
    {
        volatile uint32_t ADDR;

        struct
        {
            volatile uint32_t ADDR : 7;
            volatile uint32_t USBDEN : 1;
            volatile const uint32_t RESERVED : 24;
        }ADDR_B;
    };




    union
    {
        volatile uint32_t BUFFTB;

        struct
        {
            volatile const uint32_t RESERVED1 : 3;
            volatile uint32_t BUFFTB : 13;
            volatile const uint32_t RESERVED2 : 16;
        }BUFFTB_B;
    };




    union
    {
        volatile uint32_t LPMCTRLSTS;

        struct
        {
            volatile uint32_t LPMEN : 1;
            volatile uint32_t LPMACKEN : 1;
            volatile const uint32_t RESERVED1 : 1;
            volatile uint32_t REMWAKE : 1;
            volatile uint32_t BESL : 4;
            volatile const uint32_t RESERVED2 : 24;
        }LPMCTRLSTS_B;
    };




    union
    {
        volatile uint32_t BCD;

        struct
        {
            volatile uint32_t BCDEN : 1;
            volatile uint32_t DCDEN : 1;
            volatile uint32_t PDEN : 1;
            volatile uint32_t SDEN : 1;
            volatile uint32_t DCDFLG : 1;
            volatile uint32_t PDFLG : 1;
            volatile uint32_t SDFLG : 1;
            volatile uint32_t DMPUDFLG : 1;
            volatile const uint32_t RESERVED1 : 7;
            volatile uint32_t DPPUCTRL : 1;
            volatile const uint32_t RESERVED2 : 16;
        }BCD_B;
    };
}USBD_T;
# 34 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h" 2
# 1 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_gpio.h" 1
# 50 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_gpio.h"
typedef enum
{
    GPIO_MODE_IN = 0x00,
    GPIO_MODE_OUT = 0x01,
    GPIO_MODE_AF = 0x02,
    GPIO_MODE_AN = 0X03,
} GPIO_MODE_T;




typedef enum
{
    GPIO_OUT_TYPE_PP = 0x00,
    GPIO_OUT_TYPE_OD = 0x01,
} GPIO_OUT_TYPE_T;




typedef enum
{
    GPIO_SPEED_2MHz = 0x00,
    GPIO_SPEED_10MHz = 0x01,
    GPIO_SPEED_50MHz = 0x03,
} GPIO_SPEED_T;




typedef enum
{
    GPIO_PUPD_NO = 0x00,
    GPIO_PUPD_PU = 0x01,
    GPIO_PUPD_PD = 0x02,
} GPIO_PUPD_T;




typedef enum
{
    Bit_RESET,
    Bit_SET
} GPIO_BSRET_T;




typedef enum
{
    GPIO_PIN_0 = ((uint16_t)0x00000001),
    GPIO_PIN_1 = ((uint16_t)0x00000002),
    GPIO_PIN_2 = ((uint16_t)0x00000004),
    GPIO_PIN_3 = ((uint16_t)0x00000008),
    GPIO_PIN_4 = ((uint16_t)0x00000010),
    GPIO_PIN_5 = ((uint16_t)0x00000020),
    GPIO_PIN_6 = ((uint16_t)0x00000040),
    GPIO_PIN_7 = ((uint16_t)0x00000080),
    GPIO_PIN_8 = ((uint16_t)0x00000100),
    GPIO_PIN_9 = ((uint16_t)0x00000200),
    GPIO_PIN_10 = ((uint16_t)0x00000400),
    GPIO_PIN_11 = ((uint16_t)0x00000800),
    GPIO_PIN_12 = ((uint16_t)0x00001000),
    GPIO_PIN_13 = ((uint16_t)0x00002000),
    GPIO_PIN_14 = ((uint16_t)0x00004000),
    GPIO_PIN_15 = ((uint16_t)0x00008000),
    GPIO_PIN_ALL = ((uint32_t)0XFFFF),
} GPIO_PIN_T;




typedef enum
{
    GPIO_PIN_SOURCE_0 = ((uint8_t)0x00),
    GPIO_PIN_SOURCE_1 = ((uint8_t)0x01),
    GPIO_PIN_SOURCE_2 = ((uint8_t)0x02),
    GPIO_PIN_SOURCE_3 = ((uint8_t)0x03),
    GPIO_PIN_SOURCE_4 = ((uint8_t)0x04),
    GPIO_PIN_SOURCE_5 = ((uint8_t)0x05),
    GPIO_PIN_SOURCE_6 = ((uint8_t)0x06),
    GPIO_PIN_SOURCE_7 = ((uint8_t)0x07),
    GPIO_PIN_SOURCE_8 = ((uint8_t)0x08),
    GPIO_PIN_SOURCE_9 = ((uint8_t)0x09),
    GPIO_PIN_SOURCE_10 = ((uint8_t)0x0A),
    GPIO_PIN_SOURCE_11 = ((uint8_t)0x0B),
    GPIO_PIN_SOURCE_12 = ((uint8_t)0x0C),
    GPIO_PIN_SOURCE_13 = ((uint8_t)0x0D),
    GPIO_PIN_SOURCE_14 = ((uint8_t)0x0E),
    GPIO_PIN_SOURCE_15 = ((uint8_t)0x0F),
} GPIO_PIN_SOURCE_T;




typedef enum
{
    GPIO_AF_PIN0 = ((uint8_t)0x00),
    GPIO_AF_PIN1 = ((uint8_t)0x01),
    GPIO_AF_PIN2 = ((uint8_t)0x02),
    GPIO_AF_PIN3 = ((uint8_t)0x03),
    GPIO_AF_PIN4 = ((uint8_t)0x04),
    GPIO_AF_PIN5 = ((uint8_t)0x05),
    GPIO_AF_PIN6 = ((uint8_t)0x06),
    GPIO_AF_PIN7 = ((uint8_t)0x07),
} GPIO_AF_T;
# 167 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_gpio.h"
typedef struct
{
    uint16_t pin;
    GPIO_MODE_T mode;
    GPIO_OUT_TYPE_T outtype;
    GPIO_SPEED_T speed;
    GPIO_PUPD_T pupd;
} GPIO_Config_T;
# 183 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_gpio.h"
void GPIO_Reset(GPIO_T* port);
void GPIO_Config(GPIO_T* port, GPIO_Config_T* gpioConfig);
void GPIO_ConfigStructInit(GPIO_Config_T* gpioConfig);


void GPIO_ConfigPinLock(GPIO_T* port, uint16_t pin);


uint16_t GPIO_ReadOutputPort(GPIO_T* port);
uint16_t GPIO_ReadInputPort(GPIO_T* port);
uint8_t GPIO_ReadInputBit(GPIO_T* port, uint16_t pin);
uint8_t GPIO_ReadOutputBit(GPIO_T* port, uint16_t pin);


void GPIO_SetBit(GPIO_T* port, uint16_t pin);
void GPIO_ClearBit(GPIO_T* port, uint16_t pin);
void GPIO_WriteBitValue(GPIO_T* port, uint16_t pin, GPIO_BSRET_T bitVal);
void GPIO_WriteOutputPort(GPIO_T* port, uint16_t portValue);


void GPIO_ConfigPinAF(GPIO_T* port, GPIO_PIN_SOURCE_T pinSource, GPIO_AF_T afPin);
# 35 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h" 2
# 1 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_usart.h" 1
# 50 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_usart.h"
typedef enum
{
    USART_WORD_LEN_8B = 0,
    USART_WORD_LEN_9B = 0x00001000,
    USART_WORD_LEN_7B = 0x00001000 | 0x10000000
} USART_WORD_LEN_T;




typedef enum
{
    USART_STOP_BIT_1 = 0,
    USART_STOP_BIT_2 = 0x00002000,
    USART_STOP_BIT_1_5 = 0x00001000 | 0x00002000
} USART_STOP_BITS_T;




typedef enum
{
    USART_PARITY_NONE = 0,
    USART_PARITY_EVEN = 0x00000400,
    USART_PARITY_ODD = 0x00000400 | 0x00000200
} USART_PARITY_T;




typedef enum
{
    USART_MODE_RX = 0x00000004,
    USART_MODE_TX = 0x00000008,
    USART_MODE_TX_RX = 0x00000004 | 0x00000008
} USART_MODE_T;




typedef enum
{
    USART_FLOW_CTRL_NONE = 0,
    USART_FLOW_CTRL_RTS = 0x00000100,
    USART_FLOW_CTRL_CTS = 0x00000200,
    USART_FLOW_CTRL_RTS_CTS = 0x00000100 | 0x00000200
} USART_HARDWARE_FLOW_CTRL_T;




typedef enum
{
    USART_CLKEN_DISABLE = ((uint8_t)0),
    USART_CLKEN_ENABLE = ((uint8_t)1)
} USART_CLKEN_T;




typedef enum
{
    USART_CLKPOL_LOW = ((uint8_t)0),
    USART_CLKPOL_HIGH = ((uint8_t)1)
} USART_CLKPOL_T;




typedef enum
{
    USART_CLKPHA_1EDGE = ((uint8_t)0),
    USART_CLKPHA_2EDGE = ((uint8_t)1)
} USART_CLKPHA_T;




typedef enum
{
    USART_LBCP_DISABLE = ((uint8_t)0),
    USART_LBCP_ENABLE = ((uint8_t)1)
} USART_LBCP_T;




typedef enum
{
    USART_DMA_REQUEST_RX = 0x00000040,
    USART_DMA_REQUEST_TX = 0x00000080
} USART_DMA_REQUEST_T;




typedef enum
{
    USART_DMA_RXERR_ENABLE = ((uint8_t)0),
    USART_DMA_RXERR_DISABLE = ((uint8_t)1)
} USART_DMA_RXERR_T;




typedef enum
{
    USART_WAKEUP_IDLE_LINE = ((uint8_t)0),
    USART_WAKEUP_ADDRESS_MARK = ((uint8_t)1)
} USART_WAKEUP_T;




typedef enum
{
    USART_BREAK_LENGTH_10B = ((uint8_t)0),
    USART_BREAK_LENGTH_11B = ((uint8_t)1)
} USART_BREAK_LENGTH_T;




typedef enum
{
    USART_ADDRESS_MODE_4B = ((uint8_t)0),
    USART_ADDRESS_MODE_7B = ((uint8_t)1)
} USART_ADDRESS_MODE_T;




typedef enum
{
    USART_WAKEUP_SOURCE_ADDRESS = ((uint8_t)0),
    USART_WAKEUP_SOURCE_START = ((uint8_t)2),
    USART_WAKEUP_SOURCE_RXNE = ((uint8_t)3)
} USART_WAKEUP_SOURCE_T;




typedef enum
{
    USART_DE_POL_HIGH = ((uint8_t)0),
    USART_DE_POL_LOW = ((uint8_t)1)
} USART_DE_POL_T;




typedef enum
{
    USART_INVERSION_RX = 0x00010000,
    USART_INVERSION_TX = 0x00020000,
    USART_INVERSION_TX_RX = 0x00010000|0x00020000
} USART_INVERSION_T;




typedef enum
{
    USART_IRDA_MODE_NORMAL = ((uint8_t)0),
    USART_IRDA_MODE_LOWPOWER = ((uint8_t)1)
} USART_IRDA_MODE_T;




typedef enum
{
    USART_AUTO_BAUD_RATE_STARTBIT = ((uint8_t)0x00),
    USART_AUTO_BAUD_RATE_FALLINGEDGE = ((uint8_t)0x01)
} USART_AUTO_BAUD_RATE_T;




typedef enum
{
    USART_OVER_DETECTION_ENABLE = ((uint8_t)0),
    USART_OVER_DETECTION_DISABLE = ((uint8_t)1)
} USART_OVER_DETECTION_T;




typedef enum
{
    USART_REQUEST_ABRQ = ((uint8_t)0x01),
    USART_REQUEST_SBQ = ((uint8_t)0x02),
    USART_REQUEST_MMQ = ((uint8_t)0x04),
    USART_REQUEST_RDFQ = ((uint8_t)0x08),
    USART_REQUEST_TDFQ = ((uint8_t)0x10)
} USART_REQUEST_T;




typedef enum
{
    USART_FLAG_RXENACKF = ((uint32_t)0x00400000),
    USART_FLAG_TXENACKF = ((uint32_t)0x00200000),
    USART_FLAG_WAKEUP = ((uint32_t)0x00100000),
    USART_FLAG_RWF = ((uint32_t)0x00080000),
    USART_FLAG_SBF = ((uint32_t)0x00040000),
    USART_FLAG_CMF = ((uint32_t)0X00020000),
    USART_FLAG_BUSY = ((uint32_t)0X00010000),
    USART_FLAG_ABRTF = ((uint32_t)0X00008000),
    USART_FLAG_ABRTE = ((uint32_t)0X00004000),
    USART_FLAG_EOBF = ((uint32_t)0X00001000),
    USART_FLAG_RXTOF = ((uint32_t)0X00000800),
    USART_FLAG_CTSF = ((uint32_t)0X00000400),
    USART_FLAG_CTSIF = ((uint32_t)0X00000200),
    USART_FLAG_LBDF = ((uint32_t)0x00000100),
    USART_FLAG_TXBE = ((uint32_t)0X00000080),
    USART_FLAG_TXC = ((uint32_t)0X00000040),
    USART_FLAG_RXBNE = ((uint32_t)0X00000020),
    USART_FLAG_IDLEF = ((uint32_t)0X00000010),
    USART_FLAG_OVRE = ((uint32_t)0X00000008),
    USART_FLAG_NEF = ((uint32_t)0X00000004),
    USART_FLAG_FEF = ((uint32_t)0X00000002),
    USART_FLAG_PEF = ((uint32_t)0X00000001),
} USART_FLAG_T;




typedef enum
{
    USART_INT_WAKEUP = ((uint32_t)0x00400000),
    USART_INT_CMIE = ((uint32_t)0x00004000),
    USART_INT_EOBIE = ((uint32_t)0x08000000),
    USART_INT_RXTOIE = ((uint32_t)0x04000000),
    USART_INT_CTSIE = ((uint32_t)0x00000400),
    USART_INT_LBDIE = ((uint32_t)0X00000040),
    USART_INT_TXBEIE = ((uint32_t)0x00000080),
    USART_INT_TXCIE = ((uint32_t)0x40000040),
    USART_INT_RXBNEIE = ((uint32_t)0x00000020),
    USART_INT_IDLEIE = ((uint32_t)0x00000010),
    USART_INT_PEIE = ((uint32_t)0x00000100),
    USART_INT_ERRIE = ((uint32_t)0x00000001),
} USART_INT_T;




typedef enum
{
    USART_INT_FLAG_WAKEUP = ((uint32_t)0X00100000),
    USART_INT_FLAG_CMF = ((uint32_t)0X00020000),
    USART_INT_FLAG_EOBF = ((uint32_t)0X00001000),
    USART_INT_FLAG_RXTOF = ((uint32_t)0X00000800),
    USART_INT_FLAG_CTSIF = ((uint32_t)0X00000200),
    USART_INT_FLAG_LBDF = ((uint32_t)0X00000100),
    USART_INT_FLAG_TXBE = ((uint32_t)0X00000080),
    USART_INT_FLAG_TXC = ((uint32_t)0X00000040),
    USART_INT_FLAG_RXBNE = ((uint32_t)0X00000020),
    USART_INT_FLAG_IDLE = ((uint32_t)0X00000010),
    USART_INT_FLAG_OVRE = ((uint32_t)0X00000008),
    USART_INT_FLAG_NE = ((uint32_t)0X00000004),
    USART_INT_FLAG_FE = ((uint32_t)0X00000002),
    USART_INT_FLAG_PE = ((uint32_t)0X00000001),
} USART_INT_FLAG_T;
# 334 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_usart.h"
typedef struct
{
    uint32_t baudRate;
    USART_WORD_LEN_T wordLength;
    USART_STOP_BITS_T stopBits;
    USART_PARITY_T parity;
    USART_MODE_T mode;
    USART_HARDWARE_FLOW_CTRL_T hardwareFlowCtrl;
} USART_Config_T;




typedef struct
{
    USART_CLKEN_T enable;
    USART_CLKPOL_T polarity;
    USART_CLKPHA_T phase;
    USART_LBCP_T lastBitClock;
} USART_SyncClockConfig_T;
# 362 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_usart.h"
void USART_Reset(USART_T* usart);
void USART_Config(USART_T* uart, USART_Config_T* configStruct);
void USART_ConfigStructInit(USART_Config_T* configStruct);
void USART_ConfigSyncClock(USART_T* usart, USART_SyncClockConfig_T* SyncClockConfig);
void USART_ConfigSyncClockStructInit(USART_SyncClockConfig_T* SyncClockConfig);
void USART_Enable(USART_T* usart);
void USART_Disable(USART_T* usart);
void USART_EnableDirectionMode(USART_T* usart, USART_MODE_T mode);
void USART_DisableDirectionMode(USART_T* usart, USART_MODE_T mode);
void USART_ConfigDivider(USART_T* usart, uint8_t divider);
void USART_EnableOverSampling8(USART_T* usart);
void USART_DisableOverSampling8(USART_T* usart);
void USART_EnableMSBFirst(USART_T* usart);
void USART_DisableMSBFirst(USART_T* usart);
void USART_EnableOneBitMethod(USART_T* usart);
void USART_DisableOneBitMethod(USART_T* usart);
void USART_EnableDataInv(USART_T* usart);
void USART_DisableDataInv(USART_T* usart);
void USART_EnableInvPin(USART_T* usart, USART_INVERSION_T invPin);
void USART_DisableInvPin(USART_T* usart, USART_INVERSION_T invPin);
void USART_EnableSWAPPin(USART_T* usart);
void USART_DisableSWAPPin(USART_T* usart);
void USART_EnableReceiverTimeOut(USART_T* usart);
void USART_DisableReceiverTimeOut(USART_T* usart);
void USART_ReceiverTimeOutValue(USART_T* usart, uint32_t timeOut);
void USART_EnableAutoBaudRate(USART_T* usart);
void USART_DisableAutoBaudRate(USART_T* usart);
void USART_ConfigAutoBaudRate(USART_T* usart, USART_AUTO_BAUD_RATE_T mode);
void USART_ConfigOverrunDetection(USART_T* usart, USART_OVER_DETECTION_T overDetection);


void USART_EnableStopMode(USART_T* usart);
void USART_DisableStopMode(USART_T* usart);
void USART_ConfigStopModeWakeUpSource(USART_T* usart, USART_WAKEUP_SOURCE_T source);


void USART_Address(USART_T* usart, uint8_t address);
void USART_ConfigAddressDetection(USART_T* usart, USART_ADDRESS_MODE_T address);


void USART_TxData(USART_T* usart, uint16_t data);
uint16_t USART_RxData(USART_T* usart);


void USART_EnableMuteMode(USART_T* usart);
void USART_DisableMuteMode(USART_T* usart);
void USART_ConfigMuteModeWakeUp(USART_T* usart, USART_WAKEUP_T wakeup);


void USART_EnableLINmode(USART_T* usart);
void USART_DisableLINmode(USART_T* usart);
void USART_ConfigLINbreakDetectLength(USART_T* usart, USART_BREAK_LENGTH_T length);


void USART_EnableHalfDuplex(USART_T* usart);
void USART_DisableHalfDuplex(USART_T* usart);


void USART_EnableSmartCard(USART_T* usart);
void USART_DisableSmartCard(USART_T* usart);
void USART_EnableSmartCardNACK(USART_T* usart);
void USART_DisableSmartCardNACK(USART_T* usart);
void USART_ConfigGuardTime(USART_T* usart, uint8_t guardTime);
void USART_ConfigAutoCount(USART_T* usart, uint8_t autoCount);
void USART_ConfigBlockSize(USART_T* usart, uint8_t blockSize);


void USART_EnableIrDA(USART_T* usart);
void USART_DisableIrDA(USART_T* usart);
void USART_ConfigIrDAMode(USART_T* usart, USART_IRDA_MODE_T IrDAMode);


void USART_EnableDE(USART_T* usart);
void USART_DisableDE(USART_T* usart);
void USART_ConfigDEPolarity(USART_T* usart, USART_DE_POL_T polarity);
void USART_DEAssertionTimeValue(USART_T* usart, uint8_t value);
void USART_DEDeassertionTimeValue(USART_T* usart, uint8_t value);


void USART_EnableDMA(USART_T* usart, uint32_t dmaReq);
void USART_DisableDMA(USART_T* usart, uint32_t dmaReq);
void USART_ConfigDMAReceptionError(USART_T* usart, USART_DMA_RXERR_T error);


void USART_EnableRequest(USART_T* usart, USART_REQUEST_T request);
void USART_DisableRequest(USART_T* usart, USART_REQUEST_T request);


void USART_EnableInterrupt(USART_T* usart, USART_INT_T interrupt);
void USART_DisableInterrupt(USART_T* usart, USART_INT_T interrupt);
uint8_t USART_ReadIntFlag(USART_T* usart, USART_INT_FLAG_T flag);
void USART_ClearIntFlag(USART_T* usart, uint32_t flag);


uint8_t USART_ReadStatusFlag(USART_T* usart, USART_FLAG_T flag);
void USART_ClearStatusFlag(USART_T* usart, uint32_t flag);
# 36 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h" 2
# 1 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_rcm.h" 1
# 50 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_rcm.h"
typedef enum
{
    RCM_HSE_CLOSE =0x00,
    RCM_HSE_OPEN =0x01,
    RCM_HSE_BYPASS=0x05,
} RCM_HSE_T;




typedef enum
{
    RCM_LSE_CLOSE =0x00,
    RCM_LSE_OPEN =0x01,
    RCM_LSE_BYPASS=0x05,
} RCM_LSE_T;




typedef enum
{
    RCM_LSE_DRIVE_Low =0x00,
    RCM_LSE_DRIVE_MediumLow,
    RCM_LSE_DRIVE_MediumHigh,
    RCM_LSE_DRIVE_High,
} RCM_LSE_DRIVE_T;




typedef enum
{
    RCM_PLL_SEL_HSI_DIV2,
    RCM_PLL_SEL_HSI,
    RCM_PLL_SEL_HSE,
    RCM_PLL_SEL_HSI48
} RCM_PLL_SEL_T;




typedef enum
{
    RCM_PLLMF_2,
    RCM_PLLMF_3,
    RCM_PLLMF_4,
    RCM_PLLMF_5,
    RCM_PLLMF_6,
    RCM_PLLMF_7,
    RCM_PLLMF_8,
    RCM_PLLMF_9,
    RCM_PLLMF_10,
    RCM_PLLMF_11,
    RCM_PLLMF_12,
    RCM_PLLMF_13,
    RCM_PLLMF_14,
    RCM_PLLMF_15,
    RCM_PLLMF_16,
} RCM_PLLMF_T;




typedef enum
{
    RCM_CLK_DIV_1,
    RCM_CLK_DIV_2,
    RCM_CLK_DIV_3,
    RCM_CLK_DIV_4,
    RCM_CLK_DIV_5,
    RCM_CLK_DIV_6,
    RCM_CLK_DIV_7,
    RCM_CLK_DIV_8,
    RCM_CLK_DIV_9,
    RCM_CLK_DIV_10,
    RCM_CLK_DIV_11,
    RCM_CLK_DIV_12,
    RCM_CLK_DIV_13,
    RCM_CLK_DIV_14,
    RCM_CLK_DIV_15,
    RCM_CLK_DIV_16,
} RCM_CLK_DIV_T;




typedef enum
{
    RCM_COC_NO_CLOCK,
    RCM_COC_HSI14,
    RCM_COC_LSI,
    RCM_COC_LSE,
    RCM_COC_SYSCLK,
    RCM_COC_HSI,
    RCM_COC_HSE,
    RCM_COC_PLLCLK_DIV_2,
    RCM_COC_HSI48,
    RCM_COC_PLLCLK
} RCM_COCCLK_T;




typedef enum
{
    RCM_COC_DIV_1,
    RCM_COC_DIV_2,
    RCM_COC_DIV_4,
    RCM_COC_DIV_8,
    RCM_COC_DIV_16,
    RCM_COC_DIV_32,
    RCM_COC_DIV_64,
    RCM_COC_DIV_128,
} RCM_COCPRE_T;




typedef enum
{
    RCM_SYSCLK_SEL_HSI,
    RCM_SYSCLK_SEL_HSE,
    RCM_SYSCLK_SEL_PLL,
    RCM_SYSCLK_SEL_HSI48,
} RCM_SYSCLK_SEL_T;




typedef enum
{
    RCM_SYSCLK_DIV_1 = 7,
    RCM_SYSCLK_DIV_2,
    RCM_SYSCLK_DIV_4,
    RCM_SYSCLK_DIV_8,
    RCM_SYSCLK_DIV_16,
    RCM_SYSCLK_DIV_64,
    RCM_SYSCLK_DIV_128,
    RCM_SYSCLK_DIV_256,
    RCM_SYSCLK_DIV_512,
} RCM_AHBDIV_T;




typedef enum
{
    RCM_HCLK_DIV_1 = 3,
    RCM_HCLK_DIV_2,
    RCM_HCLK_DIV_4,
    RCM_HCLK_DIV_8,
    RCM_HCLK_DIV_16
} RCM_APBDIV_T;




typedef enum
{
    RCM_CECCLK_HSI_DIV_224,
    RCM_CECCLK_LSI_DIV,
} RCM_CECCLK_T;




typedef enum
{
    RCM_I2C1CLK_HSI,
    RCM_I2C1CLK_SYSCLK,
} RCM_I2CCLK_T;




typedef enum
{
    RCM_USART1CLK_PCLK = ((uint32_t)0x00010000),
    RCM_USART1CLK_SYSCLK = ((uint32_t)0x00010001),
    RCM_USART1CLK_LSE = ((uint32_t)0x00010002),
    RCM_USART1CLK_HSI = ((uint32_t)0x00010003),
    RCM_USART2CLK_PCLK = ((uint32_t)0x00020000),
    RCM_USART2CLK_SYSCLK = ((uint32_t)0x00020001),
    RCM_USART2CLK_LSE = ((uint32_t)0x00020002),
    RCM_USART2CLK_HSI = ((uint32_t)0x00020003),
    RCM_USART3CLK_PCLK = ((uint32_t)0x00040000),
    RCM_USART3CLK_SYSCLK = ((uint32_t)0x00040001),
    RCM_USART3CLK_LSE = ((uint32_t)0x00040002),
    RCM_USART3CLK_HSI = ((uint32_t)0x00040003),
} RCM_USARTCLK_T;




typedef enum
{
    RCM_USBCLK_HSI48,
    RCM_USBCLK_PLLCLK,
} RCM_USBCLK_T;




typedef enum
{
    RCM_RTCCLK_LSE = 0X01,
    RCM_RTCCLK_LSI,
    RCM_RTCCLK_HSE_DIV_32
} RCM_RTCCLK_T;




typedef enum
{
    RCM_AHB_PERIPH_DMA1 = 0x00000001,
    RCM_AHB_PERIPH_DMA2 = 0x00000002,
    RCM_AHB_PERIPH_SRAM = 0x00000004,
    RCM_AHB_PERIPH_FPU = 0x00000010,
    RCM_AHB_PERIPH_CRC = 0x00000040,
    RCM_AHB_PERIPH_GPIOA = 0x00020000,
    RCM_AHB_PERIPH_GPIOB = 0x00040000,
    RCM_AHB_PERIPH_GPIOC = 0x00080000,
    RCM_AHB_PERIPH_GPIOD = 0x00100000,
    RCM_AHB_PERIPH_GPIOE = 0x00200000,
    RCM_AHB_PERIPH_GPIOF = 0x00400000,
    RCM_AHB_PERIPH_TSC = 0x01000000,
} RCM_AHB_PERIPH_T;




typedef enum
{
    RCM_APB2_PERIPH_SYSCFG = 0x00000001,
    RCM_APB2_PERIPH_USART6 = 0x00000020,
    RCM_APB2_PERIPH_USART7 = 0x00000040,
    RCM_APB2_PERIPH_USART8 = 0x00000080,
    RCM_APB2_PERIPH_ADC1 = 0x00000200,
    RCM_APB2_PERIPH_TMR1 = 0x00000800,
    RCM_APB2_PERIPH_SPI1 = 0x00001000,
    RCM_APB2_PERIPH_USART1 = 0x00004000,
    RCM_APB2_PERIPH_TMR15 = 0x00010000,
    RCM_APB2_PERIPH_TMR16 = 0x00020000,
    RCM_APB2_PERIPH_TMR17 = 0x00040000,
    RCM_APB2_PERIPH_DBGMCU = 0x00400000,
} RCM_APB2_PERIPH_T;




typedef enum
{
    RCM_APB1_PERIPH_TMR2 = 0x00000001,
    RCM_APB1_PERIPH_TMR3 = 0x00000002,
    RCM_APB1_PERIPH_TMR6 = 0x00000010,
    RCM_APB1_PERIPH_TMR7 = 0x00000020,
    RCM_APB1_PERIPH_TMR14 = 0x00000100,
    RCM_APB1_PERIPH_WWDT = 0x00000800,
    RCM_APB1_PERIPH_SPI2 = 0x00004000,
    RCM_APB1_PERIPH_USART2 = 0x00020000,
    RCM_APB1_PERIPH_USART3 = 0x00040000,
    RCM_APB1_PERIPH_USART4 = 0x00080000,
    RCM_APB1_PERIPH_USART5 = 0x00100000,
    RCM_APB1_PERIPH_I2C1 = 0x00200000,
    RCM_APB1_PERIPH_I2C2 = 0x00400000,
    RCM_APB1_PERIPH_USB = 0x00800000,
    RCM_APB1_PERIPH_CAN = 0x02000000,
    RCM_APB1_PERIPH_CRS = 0x08000000,
    RCM_APB1_PERIPH_PMU = 0x10000000,
    RCM_APB1_PERIPH_DAC = 0x20000000,
    RCM_APB1_PERIPH_CEC = 0x40000000,
} RCM_APB1_PERIPH_T;




typedef enum
{
    RCM_INT_LSIRDY = 0x00000001,
    RCM_INT_LSERDY = 0x00000002,
    RCM_INT_HSIRDY = 0x00000004,
    RCM_INT_HSERDY = 0x00000008,
    RCM_INT_PLLRDY = 0x00000010,
    RCM_INT_HSI14RDY = 0x00000020,
    RCM_INT_HSI48RDY = 0x00000040,
    RCM_INT_CSS = 0x00000080
} RCM_INT_T;




typedef enum
{
    RCM_FLAG_HSIRDY = 0x001,
    RCM_FLAG_HSERDY = 0x011,
    RCM_FLAG_PLLRDY = 0x019,
    RCM_FLAG_LSERDY = 0x101,
    RCM_FLAG_LSIRDY = 0x201,
    RCM_FLAG_V18PRRST = 0x217,
    RCM_FLAG_OBRST = 0x219,
    RCM_FLAG_PINRST = 0x21A,
    RCM_FLAG_PWRRST = 0x21B,
    RCM_FLAG_SWRST = 0x21C,
    RCM_FLAG_IWDTRST = 0x21D,
    RCM_FLAG_WWDTRST = 0x21E,
    RCM_FLAG_LPRRST = 0x21F,
    RCM_FLAG_HSI14RDY = 0x301,
    RCM_FLAG_HSI48RDY = 0x311,
} RCM_FLAG_T;
# 370 "../../../../../Library/APM32F0xx_StdPeriphDriver/inc\\apm32f0xx_rcm.h"
void RCM_Reset(void);

void RCM_ConfigHSE(RCM_HSE_T state);
uint8_t RCM_WaitHSEReady(void);
void RCM_SetHSITrim(uint8_t HSITrim);
void RCM_EnableHSI(void);
void RCM_DisableHSI(void);

void RCM_SetHSI14Trim(uint8_t HSI14Trim);
void RCM_EnableHSI14(void);
void RCM_DisableHSI14(void);
void RCM_EnableHSI14ADC(void);
void RCM_DisableHSI14ADC(void);

void RCM_ConfigLSE(RCM_LSE_T state);
void RCM_ConfigDriveLSE(RCM_LSE_DRIVE_T state);

void RCM_EnableLSI(void);
void RCM_DisableLSI(void);

void RCM_ConfigPLL(RCM_PLL_SEL_T pllSelect, RCM_PLLMF_T pllMf);
void RCM_EnablePLL(void);
void RCM_DisablePLL(void);

void RCM_EnableHSI48(void);
void RCM_DisableHSI48(void);
uint32_t RCM_ReadHSI48CalibrationValue(void);

void RCM_ConfigCLKDIV(RCM_CLK_DIV_T state);

void RCM_EnableCCS(void);
void RCM_DisableCCS(void);


void RCM_ConfigCOC(RCM_COCCLK_T cocClock);




void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect);
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void);

void RCM_ConfigAHB(RCM_AHBDIV_T AHBDiv);
void RCM_ConfigAPB(RCM_APBDIV_T APBDiv);
void RCM_ConfigCECCLK(RCM_CECCLK_T CECClk);
void RCM_ConfigI2CCLK(RCM_I2CCLK_T I2CCLk);
void RCM_ConfigUSARTCLK(RCM_USARTCLK_T USARTClk);
void RCM_ConfigUSBCLK(RCM_USBCLK_T USBClk);

uint32_t RCM_ReadSYSCLKFreq(void);
uint32_t RCM_ReadHCLKFreq(void);
uint32_t RCM_ReadPCLKFreq(void);
uint32_t RCM_ReadADCCLKFreq(void);
uint32_t RCM_ReadCECCLKFreq(void);
uint32_t RCM_ReadI2C1CLKFreq(void);
uint32_t RCM_ReadUSART1CLKFreq(void);
uint32_t RCM_ReadUSART2CLKFreq(void);
uint32_t RCM_ReadUSBCLKFreq(void);

void RCM_ConfigRTCCLK(RCM_RTCCLK_T RTCClk);
void RCM_EnableRTCCLK(void);
void RCM_DisableRTCCLK(void);

void RCM_EnableBackupReset(void);
void RCM_DisableBackupReset(void);

void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph);

void RCM_EnableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph);

void RCM_EnableInterrupt(uint8_t interrupt);
void RCM_DisableInterrupt(uint8_t interrupt);
uint16_t RCM_ReadStatusFlag(RCM_FLAG_T flag);
void RCM_ClearStatusFlag(void);
uint8_t RCM_ReadIntFlag(RCM_INT_T flag);
void RCM_ClearIntFlag(uint8_t flag);
# 37 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h" 2

typedef enum
{
  LED2 = 0,
  LED3 = 1
} Led_TypeDef;

typedef enum
{
  BUTTON_KEY1 = 0,
  BUTTON_KEY2 = 1
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EINT = 1
} ButtonMode_TypeDef;

typedef enum
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;
# 130 "../../../../../Board/Board_APM32F030_MINI/Board_APM32F030_MINI.h"
void APM_MINI_LEDInit(Led_TypeDef Led);
void APM_MINI_LEDOn(Led_TypeDef Led);
void APM_MINI_LEDOff(Led_TypeDef Led);
void APM_MINI_LEDToggle(Led_TypeDef Led);


void APM_MINI_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t APM_MINI_PBGetState(Button_TypeDef Button);
void APM_MINI_PB_Led_Isr(void);

void APM_MINI_COMInit(COM_TypeDef COM);
# 35 "../../../../../Board\\Board.h" 2
# 27 "../../Source/main.c" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 1 3
# 53 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef unsigned int size_t;
# 68 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    typedef __builtin_va_list __va_list;
# 87 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __fpos_t_struct {
    unsigned long long int __pos;





    struct {
        unsigned int __state1, __state2;
    } __mbstate;
} fpos_t;
# 108 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
typedef struct __FILE FILE;
# 119 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
struct __FILE {
    union {
        long __FILE_alignment;



        char __FILE_size[84];

    } __FILE_opaque;
};
# 138 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern FILE __stdin, __stdout, __stderr;
extern FILE *__aeabi_stdin, *__aeabi_stdout, *__aeabi_stderr;
# 224 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int remove(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int rename(const char * , const char * ) __attribute__((__nonnull__(1,2)));
# 243 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *tmpfile(void);






extern __attribute__((__nothrow__)) char *tmpnam(char * );
# 265 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fclose(FILE * ) __attribute__((__nonnull__(1)));
# 275 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fflush(FILE * );
# 285 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *fopen(const char * __restrict ,
                           const char * __restrict ) __attribute__((__nonnull__(1,2)));
# 329 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) FILE *freopen(const char * __restrict ,
                    const char * __restrict ,
                    FILE * __restrict ) __attribute__((__nonnull__(2,3)));
# 342 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void setbuf(FILE * __restrict ,
                    char * __restrict ) __attribute__((__nonnull__(1)));






extern __attribute__((__nothrow__)) int setvbuf(FILE * __restrict ,
                   char * __restrict ,
                   int , size_t ) __attribute__((__nonnull__(1)));
# 370 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int fprintf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 393 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _fprintf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int _printf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __printf_args
extern __attribute__((__nothrow__)) int sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));








#pragma __printf_args
extern __attribute__((__nothrow__)) int _sprintf(char * __restrict , const char * __restrict , ...) __attribute__((__nonnull__(1,2)));






#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));


#pragma __printf_args
extern __attribute__((__nothrow__)) int snprintf(char * __restrict , size_t ,
                     const char * __restrict , ...) __attribute__((__nonnull__(3)));
# 460 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int _snprintf(char * __restrict , size_t ,
                      const char * __restrict , ...) __attribute__((__nonnull__(3)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int fscanf(FILE * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 503 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _fscanf(FILE * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));








#pragma __scanf_args
extern __attribute__((__nothrow__)) int _scanf(const char * __restrict , ...) __attribute__((__nonnull__(1)));





#pragma __scanf_args
extern __attribute__((__nothrow__)) int sscanf(const char * __restrict ,
                    const char * __restrict , ...) __attribute__((__nonnull__(1,2)));
# 541 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __scanf_args
extern __attribute__((__nothrow__)) int _sscanf(const char * __restrict ,
                     const char * __restrict , ...) __attribute__((__nonnull__(1,2)));







extern __attribute__((__nothrow__)) int vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int _vfscanf(FILE * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int _vscanf(const char * __restrict , __va_list) __attribute__((__nonnull__(1)));
extern __attribute__((__nothrow__)) int _vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));
extern __attribute__((__nothrow__)) int __ARM_vsscanf(const char * __restrict , const char * __restrict , __va_list) __attribute__((__nonnull__(1,2)));

extern __attribute__((__nothrow__)) int vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int _vprintf(const char * __restrict , __va_list ) __attribute__((__nonnull__(1)));





extern __attribute__((__nothrow__)) int vfprintf(FILE * __restrict ,
                    const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 584 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int vsprintf(char * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));
# 594 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int __ARM_vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));

extern __attribute__((__nothrow__)) int vsnprintf(char * __restrict , size_t ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 609 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _vsprintf(char * __restrict ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vfprintf(FILE * __restrict ,
                     const char * __restrict , __va_list ) __attribute__((__nonnull__(1,2)));





extern __attribute__((__nothrow__)) int _vsnprintf(char * __restrict , size_t ,
                      const char * __restrict , __va_list ) __attribute__((__nonnull__(3)));
# 635 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
#pragma __printf_args
extern __attribute__((__nothrow__)) int __ARM_asprintf(char ** , const char * __restrict , ...) __attribute__((__nonnull__(2)));
extern __attribute__((__nothrow__)) int __ARM_vasprintf(char ** , const char * __restrict , __va_list ) __attribute__((__nonnull__(2)));
# 649 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetc(FILE * ) __attribute__((__nonnull__(1)));
# 659 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *fgets(char * __restrict , int ,
                    FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 673 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputc(int , FILE * ) __attribute__((__nonnull__(2)));
# 683 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fputs(const char * __restrict , FILE * __restrict ) __attribute__((__nonnull__(1,2)));






extern __attribute__((__nothrow__)) int getc(FILE * ) __attribute__((__nonnull__(1)));
# 704 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (getchar)(void);
# 713 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) char *gets(char * ) __attribute__((__nonnull__(1)));
# 725 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int putc(int , FILE * ) __attribute__((__nonnull__(2)));
# 737 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
    extern __attribute__((__nothrow__)) int (putchar)(int );






extern __attribute__((__nothrow__)) int puts(const char * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int ungetc(int , FILE * ) __attribute__((__nonnull__(2)));
# 778 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fread(void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 794 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t __fread_bytes_avail(void * __restrict ,
                    size_t , FILE * __restrict ) __attribute__((__nonnull__(1,3)));
# 810 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) size_t fwrite(const void * __restrict ,
                    size_t , size_t , FILE * __restrict ) __attribute__((__nonnull__(1,4)));
# 822 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fgetpos(FILE * __restrict , fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 833 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fseek(FILE * , long int , int ) __attribute__((__nonnull__(1)));
# 850 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int fsetpos(FILE * __restrict , const fpos_t * __restrict ) __attribute__((__nonnull__(1,2)));
# 863 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) long int ftell(FILE * ) __attribute__((__nonnull__(1)));
# 877 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void rewind(FILE * ) __attribute__((__nonnull__(1)));
# 886 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) void clearerr(FILE * ) __attribute__((__nonnull__(1)));







extern __attribute__((__nothrow__)) int feof(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) int ferror(FILE * ) __attribute__((__nonnull__(1)));




extern __attribute__((__nothrow__)) void perror(const char * );
# 917 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdio.h" 3
extern __attribute__((__nothrow__)) int _fisatty(FILE * ) __attribute__((__nonnull__(1)));



extern __attribute__((__nothrow__)) void __use_no_semihosting_swi(void);
extern __attribute__((__nothrow__)) void __use_no_semihosting(void);
# 28 "../../Source/main.c" 2


void Delay(void);
# 41 "../../Source/main.c"
int main(void)
{
    GPIO_Config_T gpioConfig;

    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB|RCM_AHB_PERIPH_GPIOB);

    gpioConfig.pin = GPIO_PIN_6;
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;
    gpioConfig.pupd = GPIO_PUPD_NO;
    GPIO_Config(((GPIO_T*) ((((uint32_t)0x40000000) + 0x08000000) + 0x00000400)), &gpioConfig);


    gpioConfig.pin = GPIO_PIN_7;
    GPIO_Config(((GPIO_T*) ((((uint32_t)0x40000000) + 0x08000000) + 0x00000400)), &gpioConfig);


    GPIO_ClearBit(((GPIO_T*) ((((uint32_t)0x40000000) + 0x08000000) + 0x00000400)), GPIO_PIN_6);

    GPIO_SetBit(((GPIO_T*) ((((uint32_t)0x40000000) + 0x08000000) + 0x00000400)), GPIO_PIN_7);

    for(;;)
    {
        Delay();

        APM_MINI_LEDToggle(LED2);
        APM_MINI_LEDToggle(LED3);
    }
}
# 81 "../../Source/main.c"
void Delay(void)
{
    volatile uint32_t delay = 0xffff5;

    while(delay--);
}
