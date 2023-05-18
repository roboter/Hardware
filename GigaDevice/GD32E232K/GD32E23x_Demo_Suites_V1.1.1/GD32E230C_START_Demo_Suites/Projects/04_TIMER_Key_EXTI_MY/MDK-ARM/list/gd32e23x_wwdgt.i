# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 374 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c" 2
# 38 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c"
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_wwdgt.h" 1
# 41 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_wwdgt.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 114 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h"
typedef enum IRQn
{

    NonMaskableInt_IRQn = -14,
    HardFault_IRQn = -13,

    SVCall_IRQn = -5,

    PendSV_IRQn = -2,
    SysTick_IRQn = -1,

    WWDGT_IRQn = 0,
    LVD_IRQn = 1,
    RTC_IRQn = 2,
    FMC_IRQn = 3,
    RCU_IRQn = 4,
    EXTI0_1_IRQn = 5,
    EXTI2_3_IRQn = 6,
    EXTI4_15_IRQn = 7,
    DMA_Channel0_IRQn = 9,
    DMA_Channel1_2_IRQn = 10,
    DMA_Channel3_4_IRQn = 11,
    ADC_CMP_IRQn = 12,
    TIMER0_BRK_UP_TRG_COM_IRQn = 13,
    TIMER0_Channel_IRQn = 14,
    TIMER2_IRQn = 16,
    TIMER5_IRQn = 17,
    TIMER13_IRQn = 19,
    TIMER14_IRQn = 20,
    TIMER15_IRQn = 21,
    TIMER16_IRQn = 22,
    I2C0_EV_IRQn = 23,
    I2C1_EV_IRQn = 24,
    SPI0_IRQn = 25,
    SPI1_IRQn = 26,
    USART0_IRQn = 27,
    USART1_IRQn = 28,
    I2C0_ER_IRQn = 32,
    I2C1_ER_IRQn = 34,
} IRQn_Type;


# 1 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 1
# 29 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3







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
# 37 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 2 3
# 65 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
# 1 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_version.h" 1 3
# 29 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_version.h" 3
# 66 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 2 3
# 117 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
# 1 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_compiler.h" 1 3
# 47 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_compiler.h" 3
# 1 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 1 3
# 31 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
# 64 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpacked"

  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma clang diagnostic pop
# 260 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 295 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __CLZ(uint32_t value)
{
# 306 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 526 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
# 551 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
# 584 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint8_t __LDAB(volatile uint8_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldab %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return ((uint8_t) result);
}
# 599 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint16_t __LDAH(volatile uint16_t *ptr)
{
  uint32_t result;

  __asm volatile ("ldah %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return ((uint16_t) result);
}
# 614 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __LDA(volatile uint32_t *ptr)
{
  uint32_t result;

  __asm volatile ("lda %0, %1" : "=r" (result) : "Q" (*ptr) : "memory" );
  return(result);
}
# 629 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STLB(uint8_t value, volatile uint8_t *ptr)
{
  __asm volatile ("stlb %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 641 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STLH(uint16_t value, volatile uint16_t *ptr)
{
  __asm volatile ("stlh %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 653 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __STL(uint32_t value, volatile uint32_t *ptr)
{
  __asm volatile ("stl %1, %0" : "=Q" (*ptr) : "r" ((uint32_t)value) : "memory" );
}
# 737 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}
# 750 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}
# 762 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 792 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __builtin_arm_isb(0xF);
}
# 818 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static __inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 890 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 914 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 944 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 995 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1025 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 1208 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_PSPLIM(void)
{




  return 0U;





}
# 1256 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_PSPLIM(uint32_t ProcStackPtrLimit)
{




  (void)ProcStackPtrLimit;



}
# 1300 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline uint32_t __get_MSPLIM(void)
{




  return 0U;





}
# 1347 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_armclang.h" 3
__attribute__((always_inline)) static __inline void __set_MSPLIM(uint32_t MainStackPtrLimit)
{




  (void)MainStackPtrLimit;



}
# 48 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include/cmsis_compiler.h" 2 3
# 118 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 2 3
# 235 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef union
{
  struct
  {
    uint32_t _reserved0:28;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} APSR_Type;
# 265 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:23;
  } b;
  uint32_t w;
} IPSR_Type;
# 283 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef union
{
  struct
  {
    uint32_t ISR:9;
    uint32_t _reserved0:15;
    uint32_t T:1;
    uint32_t _reserved1:3;
    uint32_t V:1;
    uint32_t C:1;
    uint32_t Z:1;
    uint32_t N:1;
  } b;
  uint32_t w;
} xPSR_Type;
# 322 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef union
{
  struct
  {
    uint32_t nPRIV:1;
    uint32_t SPSEL:1;
    uint32_t _reserved1:30;
  } b;
  uint32_t w;
} CONTROL_Type;
# 353 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t ISER[16U];
        uint32_t RESERVED0[16U];
  volatile uint32_t ICER[16U];
        uint32_t RSERVED1[16U];
  volatile uint32_t ISPR[16U];
        uint32_t RESERVED2[16U];
  volatile uint32_t ICPR[16U];
        uint32_t RESERVED3[16U];
  volatile uint32_t IABR[16U];
        uint32_t RESERVED4[16U];
  volatile uint32_t ITNS[16U];
        uint32_t RESERVED5[16U];
  volatile uint32_t IPR[124U];
} NVIC_Type;
# 383 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile const uint32_t CPUID;
  volatile uint32_t ICSR;

  volatile uint32_t VTOR;



  volatile uint32_t AIRCR;
  volatile uint32_t SCR;
  volatile uint32_t CCR;
        uint32_t RESERVED1;
  volatile uint32_t SHPR[2U];
  volatile uint32_t SHCSR;
} SCB_Type;
# 560 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile const uint32_t CALIB;
} SysTick_Type;
# 612 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t CTRL;
        uint32_t RESERVED0[6U];
  volatile const uint32_t PCSR;
  volatile uint32_t COMP0;
        uint32_t RESERVED1[1U];
  volatile uint32_t FUNCTION0;
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP1;
        uint32_t RESERVED3[1U];
  volatile uint32_t FUNCTION1;
        uint32_t RESERVED4[1U];
  volatile uint32_t COMP2;
        uint32_t RESERVED5[1U];
  volatile uint32_t FUNCTION2;
        uint32_t RESERVED6[1U];
  volatile uint32_t COMP3;
        uint32_t RESERVED7[1U];
  volatile uint32_t FUNCTION3;
        uint32_t RESERVED8[1U];
  volatile uint32_t COMP4;
        uint32_t RESERVED9[1U];
  volatile uint32_t FUNCTION4;
        uint32_t RESERVED10[1U];
  volatile uint32_t COMP5;
        uint32_t RESERVED11[1U];
  volatile uint32_t FUNCTION5;
        uint32_t RESERVED12[1U];
  volatile uint32_t COMP6;
        uint32_t RESERVED13[1U];
  volatile uint32_t FUNCTION6;
        uint32_t RESERVED14[1U];
  volatile uint32_t COMP7;
        uint32_t RESERVED15[1U];
  volatile uint32_t FUNCTION7;
        uint32_t RESERVED16[1U];
  volatile uint32_t COMP8;
        uint32_t RESERVED17[1U];
  volatile uint32_t FUNCTION8;
        uint32_t RESERVED18[1U];
  volatile uint32_t COMP9;
        uint32_t RESERVED19[1U];
  volatile uint32_t FUNCTION9;
        uint32_t RESERVED20[1U];
  volatile uint32_t COMP10;
        uint32_t RESERVED21[1U];
  volatile uint32_t FUNCTION10;
        uint32_t RESERVED22[1U];
  volatile uint32_t COMP11;
        uint32_t RESERVED23[1U];
  volatile uint32_t FUNCTION11;
        uint32_t RESERVED24[1U];
  volatile uint32_t COMP12;
        uint32_t RESERVED25[1U];
  volatile uint32_t FUNCTION12;
        uint32_t RESERVED26[1U];
  volatile uint32_t COMP13;
        uint32_t RESERVED27[1U];
  volatile uint32_t FUNCTION13;
        uint32_t RESERVED28[1U];
  volatile uint32_t COMP14;
        uint32_t RESERVED29[1U];
  volatile uint32_t FUNCTION14;
        uint32_t RESERVED30[1U];
  volatile uint32_t COMP15;
        uint32_t RESERVED31[1U];
  volatile uint32_t FUNCTION15;
} DWT_Type;
# 727 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile const uint32_t SSPSR;
  volatile uint32_t CSPSR;
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;
        uint32_t RESERVED2[131U];
  volatile const uint32_t FFSR;
  volatile uint32_t FFCR;
  volatile uint32_t PSCR;
        uint32_t RESERVED3[759U];
  volatile const uint32_t TRIGGER;
  volatile const uint32_t ITFTTD0;
  volatile uint32_t ITATBCTR2;
        uint32_t RESERVED4[1U];
  volatile const uint32_t ITATBCTR0;
  volatile const uint32_t ITFTTD1;
  volatile uint32_t ITCTRL;
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;
  volatile uint32_t CLAIMCLR;
        uint32_t RESERVED7[8U];
  volatile const uint32_t DEVID;
  volatile const uint32_t DEVTYPE;
} TPI_Type;
# 1066 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
        uint32_t RESERVED0[1U];
  volatile uint32_t DAUTHCTRL;
  volatile uint32_t DSCSR;
} CoreDebug_Type;
# 1167 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t DHCSR;
  volatile uint32_t DCRSR;
  volatile uint32_t DCRDR;
  volatile uint32_t DEMCR;
        uint32_t RESERVED0[1U];
  volatile uint32_t DAUTHCTRL;
  volatile uint32_t DSCSR;
} DCB_Type;
# 1279 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
typedef struct
{
  volatile uint32_t DLAR;
  volatile const uint32_t DLSR;
  volatile const uint32_t DAUTHSTATUS;
  volatile const uint32_t DDEVARCH;
  volatile const uint32_t DDEVTYPE;
} DIB_Type;
# 1524 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __asm volatile("":::"memory");
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __asm volatile("":::"memory");
  }
}
# 1543 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1562 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
  }
}
# 1581 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1600 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 1615 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}
# 1632 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}
# 1721 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] = ((uint32_t)(((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] = ((uint32_t)(((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] & ~(0xFFUL << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL))) |
       (((priority << (8U - 2U)) & (uint32_t)0xFFUL) << ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL)));
  }
}
# 1745 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IPR[ ( (((uint32_t)(int32_t)(IRQn)) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
  else
  {
    return((uint32_t)(((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHPR[( (((((uint32_t)(int32_t)(IRQn)) & 0x0FUL)-8UL) >> 2UL) )] >> ( ((((uint32_t)(int32_t)(IRQn)) ) & 0x03UL) * 8UL) ) & (uint32_t)0xFFUL) >> (8U - 2U)));
  }
}
# 1770 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority & (uint32_t)((1UL << (SubPriorityBits )) - 1UL)))
         );
}
# 1797 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(2U)) ? (uint32_t)(2U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits = ((PriorityGroupTmp + (uint32_t)(2U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(2U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority = (Priority ) & (uint32_t)((1UL << (SubPriorityBits )) - 1UL);
}
# 1821 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{

  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;



  vectors[(int32_t)IRQn + 16] = vector;
  __builtin_arm_dsb(0xF);
}
# 1841 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{

  uint32_t *vectors = (uint32_t *)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;



  return vectors[(int32_t)IRQn + 16];
}






__attribute__((__noreturn__)) static __inline void __NVIC_SystemReset(void)
{
  __builtin_arm_dsb(0xF);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR = ((0x5FAUL << 16U) |
                 (1UL << 2U));
  __builtin_arm_dsb(0xF);

  for(;;)
  {
    __builtin_arm_nop();
  }
}
# 2066 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t SCB_GetFPUType(void)
{
    return 0U;
}
# 2127 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline void DCB_SetAuthCtrl(uint32_t value)
{
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
    ((DCB_Type *) (0xE000EDF0UL) )->DAUTHCTRL = value;
    __builtin_arm_dsb(0xF);
    __builtin_arm_isb(0xF);
}







static __inline uint32_t DCB_GetAuthCtrl(void)
{
    return (((DCB_Type *) (0xE000EDF0UL) )->DAUTHCTRL);
}
# 2194 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t DIB_GetAuthStatus(void)
{
    return (((DIB_Type *) (0xE000EFB0UL) )->DAUTHSTATUS);
}
# 2238 "C:/Users/roboter/AppData/Local/Arm/Packs/ARM/CMSIS/5.9.0/CMSIS/Core/Include\\core_cm23.h" 3
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD = (uint32_t)(ticks - 1UL);
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 2U) - 1UL);
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL = 0UL;
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL = (1UL << 2U) |
                   (1UL << 1U) |
                   (1UL );
  return (0UL);
}
# 157 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include/system_gd32e23x.h" 1
# 46 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include/system_gd32e23x.h"
extern uint32_t SystemCoreClock;



extern void SystemInit (void);

extern void SystemCoreClockUpdate (void);
# 158 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 2



typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;
# 210 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h"
# 1 "..\\gd32e23x_libopt.h" 1
# 39 "..\\gd32e23x_libopt.h"
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_adc.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_adc.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_adc.h" 2
# 274 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_adc.h"
void adc_deinit(void);

void adc_enable(void);

void adc_disable(void);


void adc_calibration_enable(void);

void adc_dma_mode_enable(void);

void adc_dma_mode_disable(void);


void adc_tempsensor_vrefint_enable(void);

void adc_tempsensor_vrefint_disable(void);


void adc_discontinuous_mode_config(uint8_t channel_group, uint8_t length);

void adc_special_function_config(uint32_t function, ControlStatus newvalue);


void adc_data_alignment_config(uint32_t data_alignment);

void adc_channel_length_config(uint8_t channel_group, uint32_t length);

void adc_regular_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time);

void adc_inserted_channel_config(uint8_t rank, uint8_t channel, uint32_t sample_time);

void adc_inserted_channel_offset_config(uint8_t inserted_channel, uint16_t offset);

void adc_external_trigger_config(uint8_t channel_group, ControlStatus newvalue);

void adc_external_trigger_source_config(uint8_t channel_group, uint32_t external_trigger_source);

void adc_software_trigger_enable(uint8_t channel_group);


uint16_t adc_regular_data_read(void);

uint16_t adc_inserted_data_read(uint8_t inserted_channel);


FlagStatus adc_flag_get(uint32_t flag);

void adc_flag_clear(uint32_t flag);

FlagStatus adc_interrupt_flag_get(uint32_t flag);

void adc_interrupt_flag_clear(uint32_t flag);

void adc_interrupt_enable(uint32_t interrupt);

void adc_interrupt_disable(uint32_t interrupt);


void adc_watchdog_single_channel_enable(uint8_t channel);

void adc_watchdog_group_channel_enable(uint8_t channel_group);

void adc_watchdog_disable(void);

void adc_watchdog_threshold_config(uint16_t low_threshold, uint16_t high_threshold);


void adc_resolution_config(uint32_t resolution);

void adc_oversample_mode_config(uint8_t mode, uint16_t shift, uint8_t ratio);

void adc_oversample_mode_enable(void);

void adc_oversample_mode_disable(void);
# 40 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_crc.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_crc.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_crc.h" 2
# 92 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_crc.h"
void crc_deinit(void);


void crc_reverse_output_data_enable(void);

void crc_reverse_output_data_disable(void);


void crc_data_register_reset(void);

uint32_t crc_data_register_read(void);


uint8_t crc_free_data_register_read(void);

void crc_free_data_register_write(uint8_t free_data);


void crc_init_data_register_write(uint32_t init_data);

void crc_input_data_reverse_config(uint32_t data_reverse);


void crc_polynomial_size_set(uint32_t poly_size);

void crc_polynomial_set(uint32_t poly);


uint32_t crc_single_data_calculate(uint32_t sdata, uint8_t data_format);

uint32_t crc_block_data_calculate(void *array, uint32_t size, uint8_t data_format);
# 41 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dbg.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dbg.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dbg.h" 2
# 83 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dbg.h"
enum dbg_reg_idx
{
    DBG_IDX_CTL0 = 0x04U,
    DBG_IDX_CTL1 = 0x08U,
};


typedef enum
{
    DBG_FWDGT_HOLD = (((DBG_IDX_CTL0) << 6) | (8U)),
    DBG_WWDGT_HOLD = (((DBG_IDX_CTL0) << 6) | (9U)),
    DBG_TIMER0_HOLD = (((DBG_IDX_CTL0) << 6) | (10U)),
    DBG_TIMER2_HOLD = (((DBG_IDX_CTL0) << 6) | (12U)),
    DBG_TIMER5_HOLD = (((DBG_IDX_CTL0) << 6) | (19U)),
    DBG_TIMER13_HOLD = (((DBG_IDX_CTL0) << 6) | (27U)),
    DBG_TIMER14_HOLD = (((DBG_IDX_CTL1) << 6) | (16U)),
    DBG_TIMER15_HOLD = (((DBG_IDX_CTL1) << 6) | (17U)),
    DBG_TIMER16_HOLD = (((DBG_IDX_CTL1) << 6) | (18U)),
    DBG_I2C0_HOLD = (((DBG_IDX_CTL0) << 6) | (15U)),
    DBG_I2C1_HOLD = (((DBG_IDX_CTL0) << 6) | (16U)),
    DBG_RTC_HOLD = (((DBG_IDX_CTL1) << 6) | (10U)),
}dbg_periph_enum;



void dbg_deinit(void);

uint32_t dbg_id_get(void);


void dbg_low_power_enable(uint32_t dbg_low_power);

void dbg_low_power_disable(uint32_t dbg_low_power);


void dbg_periph_enable(dbg_periph_enum dbg_periph);

void dbg_periph_disable(dbg_periph_enum dbg_periph);
# 42 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dma.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dma.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dma.h" 2
# 106 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dma.h"
typedef enum
{
    DMA_CH0 = 0,
    DMA_CH1,
    DMA_CH2,
    DMA_CH3,
    DMA_CH4,
} dma_channel_enum;


typedef struct
{
    uint32_t periph_addr;
    uint32_t periph_width;
    uint32_t memory_addr;
    uint32_t memory_width;
    uint32_t number;
    uint32_t priority;
    uint8_t periph_inc;
    uint8_t memory_inc;
    uint8_t direction;
} dma_parameter_struct;
# 207 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_dma.h"
void dma_deinit(dma_channel_enum channelx);

void dma_struct_para_init(dma_parameter_struct* init_struct);

void dma_init(dma_channel_enum channelx, dma_parameter_struct* init_struct);

void dma_circulation_enable(dma_channel_enum channelx);

void dma_circulation_disable(dma_channel_enum channelx);

void dma_memory_to_memory_enable(dma_channel_enum channelx);

void dma_memory_to_memory_disable(dma_channel_enum channelx);

void dma_channel_enable(dma_channel_enum channelx);

void dma_channel_disable(dma_channel_enum channelx);


void dma_periph_address_config(dma_channel_enum channelx, uint32_t address);

void dma_memory_address_config(dma_channel_enum channelx, uint32_t address);

void dma_transfer_number_config(dma_channel_enum channelx, uint32_t number);

uint32_t dma_transfer_number_get(dma_channel_enum channelx);

void dma_priority_config(dma_channel_enum channelx, uint32_t priority);

void dma_memory_width_config (dma_channel_enum channelx, uint32_t mwidth);

void dma_periph_width_config (dma_channel_enum channelx, uint32_t pwidth);

void dma_memory_increase_enable(dma_channel_enum channelx);

void dma_memory_increase_disable(dma_channel_enum channelx);

void dma_periph_increase_enable(dma_channel_enum channelx);

void dma_periph_increase_disable(dma_channel_enum channelx);

void dma_transfer_direction_config(dma_channel_enum channelx, uint8_t direction);


FlagStatus dma_flag_get(dma_channel_enum channelx, uint32_t flag);

void dma_flag_clear(dma_channel_enum channelx, uint32_t flag);

FlagStatus dma_interrupt_flag_get(dma_channel_enum channelx, uint32_t flag);

void dma_interrupt_flag_clear(dma_channel_enum channelx, uint32_t flag);

void dma_interrupt_enable(dma_channel_enum channelx, uint32_t source);

void dma_interrupt_disable(dma_channel_enum channelx, uint32_t source);
# 43 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_exti.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_exti.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_exti.h" 2
# 203 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_exti.h"
typedef enum
{
    EXTI_0 = ((uint32_t)((uint32_t)0x01U<<(0))),
    EXTI_1 = ((uint32_t)((uint32_t)0x01U<<(1))),
    EXTI_2 = ((uint32_t)((uint32_t)0x01U<<(2))),
    EXTI_3 = ((uint32_t)((uint32_t)0x01U<<(3))),
    EXTI_4 = ((uint32_t)((uint32_t)0x01U<<(4))),
    EXTI_5 = ((uint32_t)((uint32_t)0x01U<<(5))),
    EXTI_6 = ((uint32_t)((uint32_t)0x01U<<(6))),
    EXTI_7 = ((uint32_t)((uint32_t)0x01U<<(7))),
    EXTI_8 = ((uint32_t)((uint32_t)0x01U<<(8))),
    EXTI_9 = ((uint32_t)((uint32_t)0x01U<<(9))),
    EXTI_10 = ((uint32_t)((uint32_t)0x01U<<(10))),
    EXTI_11 = ((uint32_t)((uint32_t)0x01U<<(11))),
    EXTI_12 = ((uint32_t)((uint32_t)0x01U<<(12))),
    EXTI_13 = ((uint32_t)((uint32_t)0x01U<<(13))),
    EXTI_14 = ((uint32_t)((uint32_t)0x01U<<(14))),
    EXTI_15 = ((uint32_t)((uint32_t)0x01U<<(15))),
    EXTI_16 = ((uint32_t)((uint32_t)0x01U<<(16))),
    EXTI_17 = ((uint32_t)((uint32_t)0x01U<<(17))),
    EXTI_18 = ((uint32_t)((uint32_t)0x01U<<(18))),
    EXTI_19 = ((uint32_t)((uint32_t)0x01U<<(19))),
    EXTI_20 = ((uint32_t)((uint32_t)0x01U<<(20))),
    EXTI_21 = ((uint32_t)((uint32_t)0x01U<<(21))),
    EXTI_22 = ((uint32_t)((uint32_t)0x01U<<(22))),
    EXTI_23 = ((uint32_t)((uint32_t)0x01U<<(23))),
    EXTI_24 = ((uint32_t)((uint32_t)0x01U<<(24))),
    EXTI_25 = ((uint32_t)((uint32_t)0x01U<<(25))),
    EXTI_26 = ((uint32_t)((uint32_t)0x01U<<(26))),
    EXTI_27 = ((uint32_t)((uint32_t)0x01U<<(27))),
}exti_line_enum;


typedef enum
{
    EXTI_INTERRUPT = 0,
    EXTI_EVENT
}exti_mode_enum;


typedef enum
{
    EXTI_TRIG_RISING = 0,
    EXTI_TRIG_FALLING,
    EXTI_TRIG_BOTH,
    EXTI_TRIG_NONE
}exti_trig_type_enum;




void exti_deinit(void);

void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);



void exti_interrupt_enable(exti_line_enum linex);

void exti_interrupt_disable(exti_line_enum linex);

void exti_event_enable(exti_line_enum linex);

void exti_event_disable(exti_line_enum linex);



void exti_software_interrupt_enable(exti_line_enum linex);

void exti_software_interrupt_disable(exti_line_enum linex);

FlagStatus exti_flag_get(exti_line_enum linex);

void exti_flag_clear(exti_line_enum linex);

FlagStatus exti_interrupt_flag_get(exti_line_enum linex);

void exti_interrupt_flag_clear(exti_line_enum linex);
# 44 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fmc.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fmc.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fmc.h" 2
# 110 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fmc.h"
typedef enum
{
    FMC_READY,
    FMC_BUSY,
    FMC_PGERR,
    FMC_PGAERR,
    FMC_WPERR,
    FMC_TOERR,
    FMC_OB_HSPC
}fmc_state_enum;
# 206 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fmc.h"
void fmc_unlock(void);

void fmc_lock(void);

void fmc_wscnt_set(uint8_t wscnt);


void fmc_prefetch_enable(void);

void fmc_prefetch_disable(void);

fmc_state_enum fmc_page_erase(uint32_t page_address);

fmc_state_enum fmc_mass_erase(void);

fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);

fmc_state_enum fmc_word_program(uint32_t address, uint32_t data);



void ob_unlock(void);

void ob_lock(void);

void ob_reset(void);

uint32_t option_byte_value_get(uint32_t addr);

fmc_state_enum ob_erase(void);

fmc_state_enum ob_write_protection_enable(uint16_t ob_wp);

fmc_state_enum ob_security_protection_config(uint16_t ob_spc);

fmc_state_enum ob_user_write(uint8_t ob_user);

fmc_state_enum ob_data_program(uint16_t data);

uint8_t ob_user_get(void);

uint16_t ob_data_get(void);

uint16_t ob_write_protection_get(void);

uint32_t ob_obstat_plevel_get(void);



void fmc_interrupt_enable(uint32_t interrupt);

void fmc_interrupt_disable(uint32_t interrupt);

FlagStatus fmc_flag_get(uint32_t flag);

void fmc_flag_clear(uint32_t flag);

FlagStatus fmc_interrupt_flag_get(uint32_t int_flag);

void fmc_interrupt_flag_clear(uint32_t int_flag);

fmc_state_enum fmc_state_get(void);

fmc_state_enum fmc_ready_wait(uint32_t timeout);
# 45 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_gpio.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_gpio.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 41 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_gpio.h" 2
# 281 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_gpio.h"
typedef FlagStatus bit_status;
# 354 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_gpio.h"
void gpio_deinit(uint32_t gpio_periph);

void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin);

void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin);


void gpio_bit_set(uint32_t gpio_periph, uint32_t pin);

void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin);

void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value);

void gpio_port_write(uint32_t gpio_periph, uint16_t data);


FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin);

uint16_t gpio_input_port_get(uint32_t gpio_periph);

FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin);

uint16_t gpio_output_port_get(uint32_t gpio_periph);


void gpio_af_set(uint32_t gpio_periph,uint32_t alt_func_num, uint32_t pin);

void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin);


void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin);

void gpio_port_toggle(uint32_t gpio_periph);
# 46 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_syscfg.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_syscfg.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_syscfg.h" 2
# 165 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_syscfg.h"
void syscfg_deinit(void);


void syscfg_dma_remap_enable(uint32_t syscfg_dma_remap);

void syscfg_dma_remap_disable(uint32_t syscfg_dma_remap);



void syscfg_high_current_enable(void);

void syscfg_high_current_disable(void);



void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);

void syscfg_lock_config(uint32_t syscfg_lock);


void irq_latency_set(uint8_t irq_latency);


FlagStatus syscfg_flag_get(uint32_t syscfg_flag);

void syscfg_flag_clear(uint32_t syscfg_flag);
# 47 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_i2c.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_i2c.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_i2c.h" 2
# 164 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_i2c.h"
typedef enum {

    I2C_FLAG_SBSEND = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(0U)),
    I2C_FLAG_ADDSEND = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(1U)),
    I2C_FLAG_BTC = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(2U)),
    I2C_FLAG_ADD10SEND = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(3U)),
    I2C_FLAG_STPDET = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(4U)),
    I2C_FLAG_RBNE = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(6U)),
    I2C_FLAG_TBE = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(7U)),
    I2C_FLAG_BERR = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(8U)),
    I2C_FLAG_LOSTARB = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(9U)),
    I2C_FLAG_AERR = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(10U)),
    I2C_FLAG_OUERR = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(11U)),
    I2C_FLAG_PECERR = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(12U)),
    I2C_FLAG_SMBTO = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(14U)),
    I2C_FLAG_SMBALT = (((uint32_t)(((uint32_t)0x00000014U)) << 6) | (uint32_t)(15U)),

    I2C_FLAG_MASTER = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(0U)),
    I2C_FLAG_I2CBSY = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(1U)),
    I2C_FLAG_TR = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(2U)),
    I2C_FLAG_RXGC = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(4U)),
    I2C_FLAG_DEFSMB = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(5U)),
    I2C_FLAG_HSTSMB = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(6U)),
    I2C_FLAG_DUMOD = (((uint32_t)(((uint32_t)0x00000018U)) << 6) | (uint32_t)(7U)),

    I2C_FLAG_TFF = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(12U)),
    I2C_FLAG_TFR = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(13U)),
    I2C_FLAG_RFF = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(14U)),
    I2C_FLAG_RFR = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(15U))
} i2c_flag_enum;


typedef enum {

    I2C_INT_FLAG_SBSEND = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((0U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_ADDSEND = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((1U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_BTC = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((2U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_ADD10SEND = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_STPDET = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((4U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_RBNE = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((6U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_TBE = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((7U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U))),
    I2C_INT_FLAG_BERR = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((8U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_LOSTARB = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((9U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_AERR = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((10U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_OUERR = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((11U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_PECERR = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((12U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_SMBTO = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((14U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),
    I2C_INT_FLAG_SMBALT = (((uint32_t)(((uint32_t)0x00000014U)) << 22) | (uint32_t)((15U) << 16) | (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U))),

    I2C_INT_FLAG_TFF = (((uint32_t)(((uint32_t)0x00000080U)) << 22) | (uint32_t)((12U) << 16) | (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(4U))),
    I2C_INT_FLAG_TFR = (((uint32_t)(((uint32_t)0x00000080U)) << 22) | (uint32_t)((13U) << 16) | (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(5U))),
    I2C_INT_FLAG_RFF = (((uint32_t)(((uint32_t)0x00000080U)) << 22) | (uint32_t)((14U) << 16) | (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(6U))),
    I2C_INT_FLAG_RFR = (((uint32_t)(((uint32_t)0x00000080U)) << 22) | (uint32_t)((15U) << 16) | (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(7U)))
} i2c_interrupt_flag_enum;


typedef enum {

    I2C_INT_ERR = (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(8U)),
    I2C_INT_EV = (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(9U)),
    I2C_INT_BUF = (((uint32_t)(((uint32_t)0x00000004U)) << 6) | (uint32_t)(10U)),

    I2C_INT_TFF = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(4U)),
    I2C_INT_TFR = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(5U)),
    I2C_INT_RFF = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(6U)),
    I2C_INT_RFR = (((uint32_t)(((uint32_t)0x00000080U)) << 6) | (uint32_t)(7U))
} i2c_interrupt_enum;
# 308 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_i2c.h"
void i2c_deinit(uint32_t i2c_periph);

void i2c_clock_config(uint32_t i2c_periph, uint32_t clkspeed, uint32_t dutycyc);

void i2c_mode_addr_config(uint32_t i2c_periph, uint32_t mode, uint32_t addformat, uint32_t addr);



void i2c_smbus_type_config(uint32_t i2c_periph, uint32_t type);

void i2c_ack_config(uint32_t i2c_periph, uint32_t ack);

void i2c_ackpos_config(uint32_t i2c_periph, uint32_t pos);

void i2c_master_addressing(uint32_t i2c_periph, uint32_t addr, uint32_t trandirection);

void i2c_dualaddr_enable(uint32_t i2c_periph, uint32_t addr);

void i2c_dualaddr_disable(uint32_t i2c_periph);

void i2c_enable(uint32_t i2c_periph);

void i2c_disable(uint32_t i2c_periph);

void i2c_start_on_bus(uint32_t i2c_periph);

void i2c_stop_on_bus(uint32_t i2c_periph);

void i2c_data_transmit(uint32_t i2c_periph, uint8_t data);

uint8_t i2c_data_receive(uint32_t i2c_periph);

void i2c_dma_config(uint32_t i2c_periph, uint32_t dmastate);

void i2c_dma_last_transfer_config(uint32_t i2c_periph, uint32_t dmalast);

void i2c_stretch_scl_low_config(uint32_t i2c_periph, uint32_t stretchpara);

void i2c_slave_response_to_gcall_config(uint32_t i2c_periph, uint32_t gcallpara);

void i2c_software_reset_config(uint32_t i2c_periph, uint32_t sreset);

void i2c_pec_config(uint32_t i2c_periph, uint32_t pecstate);

void i2c_pec_transfer_config(uint32_t i2c_periph, uint32_t pecpara);

uint8_t i2c_pec_value_get(uint32_t i2c_periph);

void i2c_smbus_alert_config(uint32_t i2c_periph, uint32_t smbuspara);

void i2c_smbus_arp_config(uint32_t i2c_periph, uint32_t arpstate);

void i2c_sam_enable(uint32_t i2c_periph);

void i2c_sam_disable(uint32_t i2c_periph);

void i2c_sam_timeout_enable(uint32_t i2c_periph);

void i2c_sam_timeout_disable(uint32_t i2c_periph);



FlagStatus i2c_flag_get(uint32_t i2c_periph, i2c_flag_enum flag);

void i2c_flag_clear(uint32_t i2c_periph, i2c_flag_enum flag);

void i2c_interrupt_enable(uint32_t i2c_periph, i2c_interrupt_enum interrupt);

void i2c_interrupt_disable(uint32_t i2c_periph, i2c_interrupt_enum interrupt);

FlagStatus i2c_interrupt_flag_get(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);

void i2c_interrupt_flag_clear(uint32_t i2c_periph, i2c_interrupt_flag_enum int_flag);
# 48 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fwdgt.h" 1
# 41 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fwdgt.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 42 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fwdgt.h" 2
# 105 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_fwdgt.h"
void fwdgt_write_enable(void);

void fwdgt_write_disable(void);

void fwdgt_enable(void);


ErrStatus fwdgt_prescaler_value_config(uint16_t prescaler_value);

ErrStatus fwdgt_reload_value_config(uint16_t reload_value);

ErrStatus fwdgt_window_value_config(uint16_t window_value);

void fwdgt_counter_reload(void);

ErrStatus fwdgt_config(uint16_t reload_value, uint8_t prescaler_div);


FlagStatus fwdgt_flag_get(uint16_t flag);
# 49 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_pmu.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_pmu.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_pmu.h" 2
# 116 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_pmu.h"
void pmu_deinit(void);


void pmu_lvd_select(uint32_t lvdt_n);

void pmu_ldo_output_select(uint32_t ldo_output);

void pmu_lvd_disable(void);



void pmu_to_sleepmode(uint8_t sleepmodecmd);

void pmu_to_deepsleepmode(uint32_t ldo, uint8_t deepsleepmodecmd);

void pmu_to_standbymode(void);

void pmu_wakeup_pin_enable(uint32_t wakeup_pin);

void pmu_wakeup_pin_disable(uint32_t wakeup_pin);



void pmu_backup_write_enable(void);

void pmu_backup_write_disable(void);



FlagStatus pmu_flag_get(uint32_t flag);

void pmu_flag_clear(uint32_t flag);
# 50 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rcu.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rcu.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rcu.h" 2
# 223 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rcu.h"
typedef enum
{

    IDX_AHBEN = 0x14U,
    IDX_APB2EN = 0x18U,
    IDX_APB1EN = 0x1CU,

    IDX_AHBRST = 0x28U,
    IDX_APB2RST = 0x0CU,
    IDX_APB1RST = 0x10U,

    IDX_CTL0 = 0x00U,
    IDX_BDCTL = 0x20U,
    IDX_CTL1 = 0x34U,

    IDX_RSTSCK = 0x24U,

    IDX_INT = 0x08U,

    IDX_CFG0 = 0x04U,
    IDX_CFG2 = 0x30U
}reg_idx;


typedef enum
{

    RCU_DMA = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(0U)),
    RCU_CRC = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(6U)),
    RCU_GPIOA = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(17U)),
    RCU_GPIOB = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(18U)),
    RCU_GPIOC = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(19U)),
    RCU_GPIOF = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(22U)),


    RCU_CFGCMP = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(0U)),
    RCU_ADC = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(9U)),
    RCU_TIMER0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(11U)),
    RCU_SPI0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(12U)),
    RCU_USART0 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(14U)),
    RCU_TIMER14 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(16U)),
    RCU_TIMER15 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(17U)),
    RCU_TIMER16 = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(18U)),
    RCU_DBGMCU = (((uint32_t)(IDX_APB2EN)<<6) | (uint32_t)(22U)),


    RCU_TIMER2 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(1U)),
    RCU_TIMER5 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(4U)),
    RCU_TIMER13 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(8U)),
    RCU_WWDGT = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(11U)),
    RCU_SPI1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(14U)),
    RCU_USART1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(17U)),
    RCU_I2C0 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(21U)),
    RCU_I2C1 = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(22U)),
    RCU_PMU = (((uint32_t)(IDX_APB1EN)<<6) | (uint32_t)(28U)),


    RCU_RTC = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(15U))
}rcu_periph_enum;


typedef enum
{

    RCU_SRAM_SLP = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(2U)),
    RCU_FMC_SLP = (((uint32_t)(IDX_AHBEN)<<6) | (uint32_t)(4U)),
}rcu_periph_sleep_enum;


typedef enum
{

    RCU_GPIOARST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(17U)),
    RCU_GPIOBRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(18U)),
    RCU_GPIOCRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(19U)),
    RCU_GPIOFRST = (((uint32_t)(IDX_AHBRST)<<6) | (uint32_t)(22U)),


    RCU_CFGCMPRST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(0U)),
    RCU_ADCRST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(9U)),
    RCU_TIMER0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(11U)),
    RCU_SPI0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(12U)),
    RCU_USART0RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(14U)),
    RCU_TIMER14RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(16U)),
    RCU_TIMER15RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(17U)),
    RCU_TIMER16RST = (((uint32_t)(IDX_APB2RST)<<6) | (uint32_t)(18U)),


    RCU_TIMER2RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(1U)),
    RCU_TIMER5RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(4U)),
    RCU_TIMER13RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(8U)),
    RCU_WWDGTRST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(11U)),
    RCU_SPI1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(14U)),
    RCU_USART1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(17U)),
    RCU_I2C0RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(21U)),
    RCU_I2C1RST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(22U)),
    RCU_PMURST = (((uint32_t)(IDX_APB1RST)<<6) | (uint32_t)(28U)),
}rcu_periph_reset_enum;


typedef enum
{
    RCU_FLAG_IRC40KSTB = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(1U)),
    RCU_FLAG_LXTALSTB = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(1U)),
    RCU_FLAG_IRC8MSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(1U)),
    RCU_FLAG_HXTALSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(17U)),
    RCU_FLAG_PLLSTB = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(25U)),
    RCU_FLAG_IRC28MSTB = (((uint32_t)(IDX_CTL1)<<6) | (uint32_t)(1U)),

    RCU_FLAG_V12RST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(23U)),
    RCU_FLAG_OBLRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(25U)),
    RCU_FLAG_EPRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(26U)),
    RCU_FLAG_PORRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(27U)),
    RCU_FLAG_SWRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(28U)),
    RCU_FLAG_FWDGTRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(29U)),
    RCU_FLAG_WWDGTRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(30U)),
    RCU_FLAG_LPRST = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(31U))
}rcu_flag_enum;


typedef enum
{
    RCU_INT_FLAG_IRC40KSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(0U)),
    RCU_INT_FLAG_LXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(1U)),
    RCU_INT_FLAG_IRC8MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(2U)),
    RCU_INT_FLAG_HXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(3U)),
    RCU_INT_FLAG_PLLSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(4U)),
    RCU_INT_FLAG_IRC28MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(5U)),
    RCU_INT_FLAG_CKM = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(7U)),
}rcu_int_flag_enum;


typedef enum
{
    RCU_INT_FLAG_IRC40KSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(16U)),
    RCU_INT_FLAG_LXTALSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(17U)),
    RCU_INT_FLAG_IRC8MSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(18U)),
    RCU_INT_FLAG_HXTALSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(19U)),
    RCU_INT_FLAG_PLLSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(20U)),
    RCU_INT_FLAG_IRC28MSTB_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(21U)),
    RCU_INT_FLAG_CKM_CLR = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(23U)),
}rcu_int_flag_clear_enum;


typedef enum
{
    RCU_INT_IRC40KSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(8U)),
    RCU_INT_LXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(9U)),
    RCU_INT_IRC8MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(10U)),
    RCU_INT_HXTALSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(11U)),
    RCU_INT_PLLSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(12U)),
    RCU_INT_IRC28MSTB = (((uint32_t)(IDX_INT)<<6) | (uint32_t)(13U)),
}rcu_int_enum;


typedef enum
{
    RCU_ADCCK_IRC28M_DIV2 = 0U,
    RCU_ADCCK_IRC28M,
    RCU_ADCCK_APB2_DIV2,
    RCU_ADCCK_AHB_DIV3,
    RCU_ADCCK_APB2_DIV4,
    RCU_ADCCK_AHB_DIV5,
    RCU_ADCCK_APB2_DIV6,
    RCU_ADCCK_AHB_DIV7,
    RCU_ADCCK_APB2_DIV8,
    RCU_ADCCK_AHB_DIV9
}rcu_adc_clock_enum;


typedef enum
{
    RCU_HXTAL = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(16U)),
    RCU_LXTAL = (((uint32_t)(IDX_BDCTL)<<6) | (uint32_t)(0U)),
    RCU_IRC8M = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(0U)),
    RCU_IRC28M = (((uint32_t)(IDX_CTL1)<<6) | (uint32_t)(0U)),
    RCU_IRC40K = (((uint32_t)(IDX_RSTSCK)<<6) | (uint32_t)(0U)),
    RCU_PLL_CK = (((uint32_t)(IDX_CTL0)<<6) | (uint32_t)(24U))
}rcu_osci_type_enum;


typedef enum
{
    CK_SYS = 0U,
    CK_AHB,
    CK_APB1,
    CK_APB2,
    CK_ADC,
    CK_USART
}rcu_clock_freq_enum;
# 587 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rcu.h"
void rcu_deinit(void);

void rcu_periph_clock_enable(rcu_periph_enum periph);

void rcu_periph_clock_disable(rcu_periph_enum periph);

void rcu_periph_clock_sleep_enable(rcu_periph_sleep_enum periph);

void rcu_periph_clock_sleep_disable(rcu_periph_sleep_enum periph);

void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);

void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);

void rcu_bkp_reset_enable(void);

void rcu_bkp_reset_disable(void);


void rcu_system_clock_source_config(uint32_t ck_sys);

uint32_t rcu_system_clock_source_get(void);

void rcu_ahb_clock_config(uint32_t ck_ahb);

void rcu_apb1_clock_config(uint32_t ck_apb1);

void rcu_apb2_clock_config(uint32_t ck_apb2);

void rcu_adc_clock_config(rcu_adc_clock_enum ck_adc);

void rcu_ckout_config(uint32_t ckout_src, uint32_t ckout_div);


void rcu_pll_config(uint32_t pll_src, uint32_t pll_mul);

void rcu_usart_clock_config(uint32_t ck_usart);

void rcu_rtc_clock_config(uint32_t rtc_clock_source);

void rcu_hxtal_prediv_config(uint32_t hxtal_prediv);

void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);


ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);

void rcu_osci_on(rcu_osci_type_enum osci);

void rcu_osci_off(rcu_osci_type_enum osci);

void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);

void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);

void rcu_hxtal_clock_monitor_enable(void);

void rcu_hxtal_clock_monitor_disable(void);


void rcu_irc8m_adjust_value_set(uint8_t irc8m_adjval);

void rcu_irc28m_adjust_value_set(uint8_t irc28m_adjval);

void rcu_voltage_key_unlock(void);

void rcu_deepsleep_voltage_set(uint32_t dsvol);


uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);


FlagStatus rcu_flag_get(rcu_flag_enum flag);

void rcu_all_reset_flag_clear(void);

FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);

void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag_clear);

void rcu_interrupt_enable(rcu_int_enum stab_int);

void rcu_interrupt_disable(rcu_int_enum stab_int);
# 51 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rtc.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rtc.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rtc.h" 2
# 210 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rtc.h"
typedef struct
{
    uint8_t rtc_year;
    uint8_t rtc_month;
    uint8_t rtc_date;
    uint8_t rtc_day_of_week;
    uint8_t rtc_hour;
    uint8_t rtc_minute;
    uint8_t rtc_second;
    uint16_t rtc_factor_asyn;
    uint16_t rtc_factor_syn;
    uint32_t rtc_am_pm;
    uint32_t rtc_display_format;
}rtc_parameter_struct;


typedef struct
{
    uint32_t rtc_alarm_mask;
    uint32_t rtc_weekday_or_date;
    uint8_t rtc_alarm_day;
    uint8_t rtc_alarm_hour;
    uint8_t rtc_alarm_minute;
    uint8_t rtc_alarm_second;
    uint32_t rtc_am_pm;
}rtc_alarm_struct;


typedef struct
{
    uint8_t rtc_timestamp_month;
    uint8_t rtc_timestamp_date;
    uint8_t rtc_timestamp_day;
    uint8_t rtc_timestamp_hour;
    uint8_t rtc_timestamp_minute;
    uint8_t rtc_timestamp_second;
    uint32_t rtc_am_pm;
}rtc_timestamp_struct;


typedef struct
{
    uint32_t rtc_tamper_source;
    uint32_t rtc_tamper_trigger;
    uint32_t rtc_tamper_filter;
    uint32_t rtc_tamper_sample_frequency;
    ControlStatus rtc_tamper_precharge_enable;
    uint32_t rtc_tamper_precharge_time;
    ControlStatus rtc_tamper_with_timestamp;
}rtc_tamper_struct;
# 492 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_rtc.h"
ErrStatus rtc_deinit(void);

ErrStatus rtc_init(rtc_parameter_struct* rtc_initpara_struct);

ErrStatus rtc_init_mode_enter(void);

void rtc_init_mode_exit(void);

ErrStatus rtc_register_sync_wait(void);


void rtc_current_time_get(rtc_parameter_struct* rtc_initpara_struct);

uint32_t rtc_subsecond_get(void);


void rtc_alarm_config(rtc_alarm_struct* rtc_alarm_time);

void rtc_alarm_subsecond_config(uint32_t mask_subsecond, uint32_t subsecond);

void rtc_alarm_get(rtc_alarm_struct* rtc_alarm_time);

uint32_t rtc_alarm_subsecond_get(void);

void rtc_alarm_enable(void);

ErrStatus rtc_alarm_disable(void);


void rtc_timestamp_enable(uint32_t edge);

void rtc_timestamp_disable(void);

void rtc_timestamp_get(rtc_timestamp_struct* rtc_timestamp);

uint32_t rtc_timestamp_subsecond_get(void);


void rtc_tamper_enable(rtc_tamper_struct* rtc_tamper);

void rtc_tamper_disable(uint32_t source);


void rtc_interrupt_enable(uint32_t interrupt);

void rtc_interrupt_disable(uint32_t interrupt);

FlagStatus rtc_flag_get(uint32_t flag);

void rtc_flag_clear(uint32_t flag);

void rtc_alter_output_config(uint32_t source, uint32_t mode);


ErrStatus rtc_calibration_config(uint32_t window, uint32_t plus, uint32_t minus);

void rtc_hour_adjust(uint32_t operation);

ErrStatus rtc_second_adjust(uint32_t add, uint32_t minus);

void rtc_bypass_shadow_enable(void);

void rtc_bypass_shadow_disable(void);

ErrStatus rtc_refclock_detection_enable(void);

ErrStatus rtc_refclock_detection_disable(void);
# 52 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_spi.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_spi.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_spi.h" 2
# 140 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_spi.h"
typedef struct {
    uint32_t device_mode;
    uint32_t trans_mode;
    uint32_t frame_size;
    uint32_t nss;
    uint32_t endian;
    uint32_t clock_polarity_phase;
    uint32_t prescale;
} spi_parameter_struct;
# 317 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_spi.h"
void spi_i2s_deinit(uint32_t spi_periph);

void spi_struct_para_init(spi_parameter_struct *spi_struct);

ErrStatus spi_init(uint32_t spi_periph, spi_parameter_struct *spi_struct);

void spi_enable(uint32_t spi_periph);

void spi_disable(uint32_t spi_periph);



void i2s_init(uint32_t spi_periph, uint32_t mode, uint32_t standard, uint32_t ckpl);

void i2s_psc_config(uint32_t spi_periph, uint32_t audiosample, uint32_t frameformat, uint32_t mckout);

void i2s_enable(uint32_t spi_periph);

void i2s_disable(uint32_t spi_periph);



void spi_nss_output_enable(uint32_t spi_periph);

void spi_nss_output_disable(uint32_t spi_periph);

void spi_nss_internal_high(uint32_t spi_periph);

void spi_nss_internal_low(uint32_t spi_periph);



void spi_dma_enable(uint32_t spi_periph, uint8_t dma);

void spi_dma_disable(uint32_t spi_periph, uint8_t dma);

void spi_transmit_odd_config(uint32_t spi_periph, uint16_t odd);

void spi_receive_odd_config(uint32_t spi_periph, uint16_t odd);



ErrStatus spi_i2s_data_frame_format_config(uint32_t spi_periph, uint16_t frame_format);

void spi_fifo_access_size_config(uint32_t spi_periph, uint16_t fifo_access_size);

void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction);

void spi_i2s_data_transmit(uint32_t spi_periph, uint16_t data);

uint16_t spi_i2s_data_receive(uint32_t spi_periph);



void spi_crc_polynomial_set(uint32_t spi_periph, uint16_t crc_poly);

uint16_t spi_crc_polynomial_get(uint32_t spi_periph);

void spi_crc_length_set(uint32_t spi_periph, uint16_t crc_length);

void spi_crc_on(uint32_t spi_periph);

void spi_crc_off(uint32_t spi_periph);

void spi_crc_next(uint32_t spi_periph);

uint16_t spi_crc_get(uint32_t spi_periph, uint8_t crc);



void spi_ti_mode_enable(uint32_t spi_periph);

void spi_ti_mode_disable(uint32_t spi_periph);



void spi_nssp_mode_enable(uint32_t spi_periph);

void spi_nssp_mode_disable(uint32_t spi_periph);



void spi_quad_enable(uint32_t spi_periph);

void spi_quad_disable(uint32_t spi_periph);

void spi_quad_write_enable(uint32_t spi_periph);

void spi_quad_read_enable(uint32_t spi_periph);

void spi_quad_io23_output_enable(uint32_t spi_periph);

void spi_quad_io23_output_disable(uint32_t spi_periph);



FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag);

void spi_i2s_interrupt_enable(uint32_t spi_periph, uint8_t interrupt);

void spi_i2s_interrupt_disable(uint32_t spi_periph, uint8_t interrupt);

FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt);

void spi_crc_error_clear(uint32_t spi_periph);
# 53 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_timer.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_timer.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_timer.h" 2
# 253 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_timer.h"
typedef struct
{
    uint16_t prescaler;
    uint16_t alignedmode;
    uint16_t counterdirection;
    uint16_t clockdivision;
    uint32_t period;
    uint8_t repetitioncounter;
}timer_parameter_struct;


typedef struct
{
    uint16_t runoffstate;
    uint16_t ideloffstate;
    uint16_t deadtime;
    uint16_t breakpolarity;
    uint16_t outputautostate;
    uint16_t protectmode;
    uint16_t breakstate;
}timer_break_parameter_struct;


typedef struct
{
    uint16_t outputstate;
    uint16_t outputnstate;
    uint16_t ocpolarity;
    uint16_t ocnpolarity;
    uint16_t ocidlestate;
    uint16_t ocnidlestate;
}timer_oc_parameter_struct;


typedef struct
{
    uint16_t icpolarity;
    uint16_t icselection;
    uint16_t icprescaler;
    uint16_t icfilter;
}timer_ic_parameter_struct;
# 599 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_timer.h"
void timer_deinit(uint32_t timer_periph);

void timer_struct_para_init(timer_parameter_struct* initpara);

void timer_init(uint32_t timer_periph, timer_parameter_struct* initpara);

void timer_enable(uint32_t timer_periph);

void timer_disable(uint32_t timer_periph);

void timer_auto_reload_shadow_enable(uint32_t timer_periph);

void timer_auto_reload_shadow_disable(uint32_t timer_periph);

void timer_update_event_enable(uint32_t timer_periph);

void timer_update_event_disable(uint32_t timer_periph);

void timer_counter_alignment(uint32_t timer_periph, uint16_t aligned);

void timer_counter_up_direction(uint32_t timer_periph);

void timer_counter_down_direction(uint32_t timer_periph);

void timer_prescaler_config(uint32_t timer_periph, uint16_t prescaler, uint8_t pscreload);

void timer_repetition_value_config(uint32_t timer_periph, uint16_t repetition);

void timer_autoreload_value_config(uint32_t timer_periph, uint16_t autoreload);

void timer_counter_value_config(uint32_t timer_periph , uint16_t counter);

uint32_t timer_counter_read(uint32_t timer_periph);

uint16_t timer_prescaler_read(uint32_t timer_periph);

void timer_single_pulse_mode_config(uint32_t timer_periph, uint32_t spmode);

void timer_update_source_config(uint32_t timer_periph, uint32_t update);

void timer_ocpre_clear_source_config(uint32_t timer_periph, uint8_t ocpreclear);



void timer_interrupt_enable(uint32_t timer_periph, uint32_t interrupt);

void timer_interrupt_disable(uint32_t timer_periph, uint32_t interrupt);

FlagStatus timer_interrupt_flag_get(uint32_t timer_periph, uint32_t interrupt);

void timer_interrupt_flag_clear(uint32_t timer_periph, uint32_t interrupt);

FlagStatus timer_flag_get(uint32_t timer_periph, uint32_t flag);

void timer_flag_clear(uint32_t timer_periph, uint32_t flag);



void timer_dma_enable(uint32_t timer_periph, uint16_t dma);

void timer_dma_disable(uint32_t timer_periph, uint16_t dma);

void timer_channel_dma_request_source_select(uint32_t timer_periph, uint8_t dma_request);

void timer_dma_transfer_config(uint32_t timer_periph,uint32_t dma_baseaddr, uint32_t dma_lenth);

void timer_event_software_generate(uint32_t timer_periph, uint16_t event);



void timer_break_struct_para_init(timer_break_parameter_struct* breakpara);

void timer_break_config(uint32_t timer_periph, timer_break_parameter_struct* breakpara);

void timer_break_enable(uint32_t timer_periph);

void timer_break_disable(uint32_t timer_periph);

void timer_automatic_output_enable(uint32_t timer_periph);

void timer_automatic_output_disable(uint32_t timer_periph);

void timer_primary_output_config(uint32_t timer_periph, ControlStatus newvalue);

void timer_channel_control_shadow_config(uint32_t timer_periph, ControlStatus newvalue);

void timer_channel_control_shadow_update_config(uint32_t timer_periph, uint8_t ccuctl);



void timer_channel_output_struct_para_init(timer_oc_parameter_struct* ocpara);

void timer_channel_output_config(uint32_t timer_periph,uint16_t channel, timer_oc_parameter_struct* ocpara);

void timer_channel_output_mode_config(uint32_t timer_periph, uint16_t channel,uint16_t ocmode);

void timer_channel_output_pulse_value_config(uint32_t timer_periph, uint16_t channel, uint32_t pulse);

void timer_channel_output_shadow_config(uint32_t timer_periph, uint16_t channel, uint16_t ocshadow);

void timer_channel_output_fast_config(uint32_t timer_periph, uint16_t channel, uint16_t ocfast);

void timer_channel_output_clear_config(uint32_t timer_periph,uint16_t channel,uint16_t occlear);

void timer_channel_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocpolarity);

void timer_channel_complementary_output_polarity_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnpolarity);

void timer_channel_output_state_config(uint32_t timer_periph, uint16_t channel, uint32_t state);

void timer_channel_complementary_output_state_config(uint32_t timer_periph, uint16_t channel, uint16_t ocnstate);



void timer_channel_input_struct_para_init(timer_ic_parameter_struct* icpara);

void timer_input_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct* icpara);

void timer_channel_input_capture_prescaler_config(uint32_t timer_periph, uint16_t channel, uint16_t prescaler);

uint32_t timer_channel_capture_value_register_read(uint32_t timer_periph, uint16_t channel);

void timer_input_pwm_capture_config(uint32_t timer_periph, uint16_t channel, timer_ic_parameter_struct* icpwm);

void timer_hall_mode_config(uint32_t timer_periph, uint32_t hallmode);



void timer_input_trigger_source_select(uint32_t timer_periph, uint32_t intrigger);

void timer_master_output_trigger_source_select(uint32_t timer_periph, uint32_t outrigger);

void timer_slave_mode_select(uint32_t timer_periph,uint32_t slavemode);

void timer_master_slave_mode_config(uint32_t timer_periph, uint32_t masterslave);

void timer_external_trigger_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_quadrature_decoder_mode_config(uint32_t timer_periph, uint32_t decomode, uint16_t ic0polarity, uint16_t ic1polarity);

void timer_internal_clock_config(uint32_t timer_periph);

void timer_internal_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t intrigger);

void timer_external_trigger_as_external_clock_config(uint32_t timer_periph, uint32_t extrigger, uint16_t extpolarity,uint32_t extfilter);

void timer_external_clock_mode0_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_external_clock_mode1_config(uint32_t timer_periph, uint32_t extprescaler, uint32_t extpolarity, uint32_t extfilter);

void timer_external_clock_mode1_disable(uint32_t timer_periph);

void timer_channel_remap_config(uint32_t timer_periph,uint32_t remap);



void timer_write_chxval_register_config(uint32_t timer_periph, uint16_t ccsel);

void timer_output_value_selection_config(uint32_t timer_periph, uint16_t outsel);
# 54 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_usart.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_usart.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_usart.h" 2
# 214 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_usart.h"
typedef enum{

    USART_FLAG_REA = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(22U)),
    USART_FLAG_TEA = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(21U)),
    USART_FLAG_WU = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(20U)),
    USART_FLAG_RWU = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(19U)),
    USART_FLAG_SB = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(18U)),
    USART_FLAG_AM = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(17U)),
    USART_FLAG_BSY = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(16U)),
    USART_FLAG_EB = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(12U)),
    USART_FLAG_RT = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(11U)),
    USART_FLAG_CTS = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(10U)),
    USART_FLAG_CTSF = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(9U)),
    USART_FLAG_LBD = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(8U)),
    USART_FLAG_TBE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(7U)),
    USART_FLAG_TC = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(6U)),
    USART_FLAG_RBNE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(5U)),
    USART_FLAG_IDLE = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(4U)),
    USART_FLAG_ORERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(3U)),
    USART_FLAG_NERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(2U)),
    USART_FLAG_FERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(1U)),
    USART_FLAG_PERR = (((uint32_t)(0x0000001CU) << 6) | (uint32_t)(0U)),

    USART_FLAG_EPERR = (((uint32_t)(0x000000C0U) << 6) | (uint32_t)(8U)),

    USART_FLAG_RFFINT = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(15U)),
    USART_FLAG_RFF = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(11U)),
    USART_FLAG_RFE = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(10U)),
}usart_flag_enum;


typedef enum
{

    USART_INT_FLAG_EB = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((12U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(27U))),
    USART_INT_FLAG_RT = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((11U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(26U))),
    USART_INT_FLAG_AM = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((17U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(14U))),
    USART_INT_FLAG_PERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((0U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(8U))),
    USART_INT_FLAG_TBE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((7U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(7U))),
    USART_INT_FLAG_TC = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((6U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(6U))),
    USART_INT_FLAG_RBNE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((5U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U))),
    USART_INT_FLAG_RBNE_ORERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U))),
    USART_INT_FLAG_IDLE = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((4U) << 16) | (((uint32_t)(0x00000000U) << 6) | (uint32_t)(4U))),

    USART_INT_FLAG_LBD = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((8U) << 16) | (((uint32_t)(0x00000004U) << 6) | (uint32_t)(6U))),

    USART_INT_FLAG_WU = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((20U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(22U))),
    USART_INT_FLAG_CTS = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((9U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(10U))),
    USART_INT_FLAG_ERR_NERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((2U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),
    USART_INT_FLAG_ERR_ORERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((3U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),
    USART_INT_FLAG_ERR_FERR = (((uint32_t)(0x0000001CU) << 22) | (uint32_t)((1U) << 16) | (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U))),

    USART_INT_FLAG_RFF = (((uint32_t)(0x000000D0U) << 22) | (uint32_t)((15U) << 16) | (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(9U))),
}usart_interrupt_flag_enum;


typedef enum
{

    USART_INT_EB = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(27U)),
    USART_INT_RT = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(26U)),
    USART_INT_AM = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(14U)),
    USART_INT_PERR = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(8U)),
    USART_INT_TBE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(7U)),
    USART_INT_TC = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(6U)),
    USART_INT_RBNE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(5U)),
    USART_INT_IDLE = (((uint32_t)(0x00000000U) << 6) | (uint32_t)(4U)),

    USART_INT_LBD = (((uint32_t)(0x00000004U) << 6) | (uint32_t)(6U)),

    USART_INT_WU = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(22U)),
    USART_INT_CTS = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(10U)),
    USART_INT_ERR = (((uint32_t)(0x00000008U) << 6) | (uint32_t)(0U)),

    USART_INT_RFF = (((uint32_t)(0x000000D0U) << 6) | (uint32_t)(9U)),
}usart_interrupt_enum;


typedef enum {

    USART_DINV_ENABLE,
    USART_DINV_DISABLE,

    USART_TXPIN_ENABLE,
    USART_TXPIN_DISABLE,

    USART_RXPIN_ENABLE,
    USART_RXPIN_DISABLE,

    USART_SWAP_ENABLE,
    USART_SWAP_DISABLE,
}usart_invert_enum;
# 424 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_usart.h"
void usart_deinit(uint32_t usart_periph);

void usart_baudrate_set(uint32_t usart_periph, uint32_t baudval);

void usart_parity_config(uint32_t usart_periph, uint32_t paritycfg);

void usart_word_length_set(uint32_t usart_periph, uint32_t wlen);

void usart_stop_bit_set(uint32_t usart_periph, uint32_t stblen);

void usart_enable(uint32_t usart_periph);

void usart_disable(uint32_t usart_periph);

void usart_transmit_config(uint32_t usart_periph, uint32_t txconfig);

void usart_receive_config(uint32_t usart_periph, uint32_t rxconfig);



void usart_data_first_config(uint32_t usart_periph, uint32_t msbf);

void usart_invert_config(uint32_t usart_periph, usart_invert_enum invertpara);

void usart_overrun_enable(uint32_t usart_periph);

void usart_overrun_disable(uint32_t usart_periph);

void usart_oversample_config(uint32_t usart_periph, uint32_t oversamp);

void usart_sample_bit_config(uint32_t usart_periph, uint32_t osb);

void usart_receiver_timeout_enable(uint32_t usart_periph);

void usart_receiver_timeout_disable(uint32_t usart_periph);

void usart_receiver_timeout_threshold_config(uint32_t usart_periph, uint32_t rtimeout);

void usart_data_transmit(uint32_t usart_periph, uint32_t data);

uint16_t usart_data_receive(uint32_t usart_periph);



void usart_address_config(uint32_t usart_periph, uint8_t addr);

void usart_address_detection_mode_config(uint32_t usart_periph, uint32_t addmod);

void usart_mute_mode_enable(uint32_t usart_periph);

void usart_mute_mode_disable(uint32_t usart_periph);

void usart_mute_mode_wakeup_config(uint32_t usart_periph, uint32_t wmethod);



void usart_lin_mode_enable(uint32_t usart_periph);

void usart_lin_mode_disable(uint32_t usart_periph);

void usart_lin_break_detection_length_config(uint32_t usart_periph, uint32_t lblen);



void usart_halfduplex_enable(uint32_t usart_periph);

void usart_halfduplex_disable(uint32_t usart_periph);



void usart_clock_enable(uint32_t usart_periph);

void usart_clock_disable(uint32_t usart_periph);

void usart_synchronous_clock_config(uint32_t usart_periph, uint32_t clen, uint32_t cph, uint32_t cpl);



void usart_guard_time_config(uint32_t usart_periph, uint32_t guat);

void usart_smartcard_mode_enable(uint32_t usart_periph);

void usart_smartcard_mode_disable(uint32_t usart_periph);

void usart_smartcard_mode_nack_enable(uint32_t usart_periph);

void usart_smartcard_mode_nack_disable(uint32_t usart_periph);

void usart_smartcard_mode_early_nack_enable(uint32_t usart_periph);

void usart_smartcard_mode_early_nack_disable(uint32_t usart_periph);

void usart_smartcard_autoretry_config(uint32_t usart_periph, uint32_t scrtnum);

void usart_block_length_config(uint32_t usart_periph, uint32_t bl);



void usart_irda_mode_enable(uint32_t usart_periph);

void usart_irda_mode_disable(uint32_t usart_periph);

void usart_prescaler_config(uint32_t usart_periph, uint32_t psc);

void usart_irda_lowpower_config(uint32_t usart_periph, uint32_t irlp);



void usart_hardware_flow_rts_config(uint32_t usart_periph, uint32_t rtsconfig);

void usart_hardware_flow_cts_config(uint32_t usart_periph, uint32_t ctsconfig);



void usart_hardware_flow_coherence_config(uint32_t usart_periph, uint32_t hcm);


void usart_rs485_driver_enable(uint32_t usart_periph);

void usart_rs485_driver_disable(uint32_t usart_periph);

void usart_driver_assertime_config(uint32_t usart_periph, uint32_t deatime);

void usart_driver_deassertime_config(uint32_t usart_periph, uint32_t dedtime);

void usart_depolarity_config(uint32_t usart_periph, uint32_t dep);



void usart_dma_receive_config(uint32_t usart_periph, uint32_t dmacmd);

void usart_dma_transmit_config(uint32_t usart_periph, uint32_t dmacmd);

void usart_reception_error_dma_disable(uint32_t usart_periph);

void usart_reception_error_dma_enable(uint32_t usart_periph);


void usart_wakeup_enable(uint32_t usart_periph);

void usart_wakeup_disable(uint32_t usart_periph);

void usart_wakeup_mode_config(uint32_t usart_periph, uint32_t wum);



void usart_receive_fifo_enable(uint32_t usart_periph);

void usart_receive_fifo_disable(uint32_t usart_periph);

uint8_t usart_receive_fifo_counter_number(uint32_t usart_periph);



FlagStatus usart_flag_get(uint32_t usart_periph, usart_flag_enum flag);

void usart_flag_clear(uint32_t usart_periph, usart_flag_enum flag);

void usart_interrupt_enable(uint32_t usart_periph, usart_interrupt_enum interrupt);

void usart_interrupt_disable(uint32_t usart_periph, usart_interrupt_enum interrupt);

void usart_command_enable(uint32_t usart_periph, uint32_t cmdtype);

FlagStatus usart_interrupt_flag_get(uint32_t usart_periph, usart_interrupt_flag_enum int_flag);

void usart_interrupt_flag_clear(uint32_t usart_periph, usart_interrupt_flag_enum flag);
# 55 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_wwdgt.h" 1
# 56 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_misc.h" 1
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_misc.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_misc.h" 2
# 68 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_misc.h"
void nvic_irq_enable(uint8_t nvic_irq, uint8_t nvic_irq_priority);

void nvic_irq_disable(uint8_t nvic_irq);

void nvic_system_reset(void);


void nvic_vector_table_set(uint32_t nvic_vict_tab, uint32_t offset);


void system_lowpower_set(uint8_t lowpower_mode);

void system_lowpower_reset(uint8_t lowpower_mode);


void systick_clksource_set(uint32_t systick_clksource);
# 57 "..\\gd32e23x_libopt.h" 2
# 1 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_cmp.h" 1
# 40 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_cmp.h"
# 1 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 1
# 41 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_cmp.h" 2
# 61 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_cmp.h"
typedef enum{
    CMP_HIGHSPEED = 0,
    CMP_MIDDLESPEED,
    CMP_LOWSPEED,
    CMP_VERYLOWSPEED
}operating_mode_enum;


typedef enum{
    CMP_1_4VREFINT = 0,
    CMP_1_2VREFINT,
    CMP_3_4VREFINT,
    CMP_VREFINT,
    CMP_PA4,
    CMP_PA5,
    CMP_PA0,
    CMP_PA2
}inverting_input_enum;


typedef enum{
    CMP_HYSTERESIS_NO = 0,
    CMP_HYSTERESIS_LOW,
    CMP_HYSTERESIS_MIDDLE,
    CMP_HYSTERESIS_HIGH
}cmp_hysteresis_enum;


typedef enum{
    CMP_OUTPUT_NONE = 0x0U,
    CMP_OUTPUT_TIMER0BKIN = 0x1U,
    CMP_OUTPUT_TIMER0IC0 = 0x2U,
    CMP_OUTPUT_TIMER0OCPRECLR = 0x3U,
    CMP_OUTPUT_TIMER2IC0 = 0x06U,
    CMP_OUTPUT_TIMER2OCPRECLR = 0x7U
}cmp_output_enum;
# 144 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_cmp.h"
void cmp_deinit(void);

void cmp_mode_init(operating_mode_enum operating_mode, inverting_input_enum inverting_input, cmp_hysteresis_enum output_hysteresis);

void cmp_output_init(cmp_output_enum output_selection, uint32_t output_polarity);

void cmp_enable(void);

void cmp_disable(void);

void cmp_switch_enable(void);

void cmp_switch_disable(void);

uint32_t cmp_output_level_get(void);

void cmp_lock_enable(void);
# 58 "..\\gd32e23x_libopt.h" 2
# 211 "../../../../GD32E23x_Firmware_Library/CMSIS/GD/GD32E23x/Include\\gd32e23x.h" 2
# 42 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_wwdgt.h" 2
# 78 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Include\\gd32e23x_wwdgt.h"
void wwdgt_deinit(void);

void wwdgt_enable(void);


void wwdgt_counter_update(uint16_t counter_value);

void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler);


FlagStatus wwdgt_flag_get(void);

void wwdgt_flag_clear(void);

void wwdgt_interrupt_enable(void);
# 39 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c" 2







void wwdgt_deinit(void)
{
    rcu_periph_reset_enable(RCU_WWDGTRST);
    rcu_periph_reset_disable(RCU_WWDGTRST);
}







void wwdgt_enable(void)
{
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000000U)) |= ((uint32_t)((uint32_t)0x01U<<(7)));
}







void wwdgt_counter_update(uint16_t counter_value)
{
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000000U)) = (uint32_t)((((0xFFFFFFFFUL << (0)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(6)))) & ((uint32_t)(counter_value) << 0U)));
}
# 87 "../../../../GD32E23x_Firmware_Library/GD32E23x_standard_peripheral/Source/gd32e23x_wwdgt.c"
void wwdgt_config(uint16_t counter, uint16_t window, uint32_t prescaler)
{
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000004U)) = (uint32_t)((((0xFFFFFFFFUL << (0)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(6)))) & ((uint32_t)(window) << 0U)) | prescaler);
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000000U)) = (uint32_t)((((0xFFFFFFFFUL << (0)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(6)))) & ((uint32_t)(counter) << 0U)));
}







FlagStatus wwdgt_flag_get(void)
{
  if(RESET != ((*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000008U)) & ((uint32_t)((uint32_t)0x01U<<(0))))){
        return SET;
  }
    return RESET;
}







void wwdgt_flag_clear(void)
{
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000008U)) &= (~(uint32_t)((uint32_t)((uint32_t)0x01U<<(0))));
}







void wwdgt_interrupt_enable(void)
{
    (*(volatile uint32_t *)(uint32_t)(((((uint32_t)0x40000000U) + 0x00002C00U)) + 0x00000004U)) |= ((uint32_t)((uint32_t)0x01U<<(9)));
}
