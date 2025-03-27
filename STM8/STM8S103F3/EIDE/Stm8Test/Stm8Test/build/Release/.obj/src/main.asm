;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.2.0 #13081 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl __this_is_a_example
	.globl _TRAP_IRQHandler
	.globl _main
	.globl _TIM4_SelectOnePulseMode
	.globl _TIM4_TimeBaseInit
	.globl _GPIO_WriteReverse
	.globl _GPIO_Init
	.globl _CLK_HSIPrescalerConfig
	.globl _CLK_PeripheralClockConfig
	.globl _DelayInit
	.globl _DelayMs
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ; reset
	int _TRAP_IRQHandler ; trap
	int 0x000000 ; int0
	int 0x000000 ; int1
	int 0x000000 ; int2
	int __this_is_a_example ; int3
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	.\src\main.c: 20: void main(void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	.\src\main.c: 23: CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	clr	a
	call	_CLK_HSIPrescalerConfig
;	.\src\main.c: 26: DelayInit();
	call	_DelayInit
;	.\src\main.c: 29: GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
	push	#0xe0
	ld	a, #0x20
	ldw	x, #0x5005
	call	_GPIO_Init
;	.\src\main.c: 31: while (1)
00102$:
;	.\src\main.c: 33: GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
	ld	a, #0x20
	ldw	x, #0x5005
	call	_GPIO_WriteReverse
;	.\src\main.c: 34: DelayMs(500);
	ldw	x, #0x01f4
	call	_DelayMs
	jra	00102$
;	.\src\main.c: 36: }
	ret
;	.\src\main.c: 38: void DelayInit(void)
;	-----------------------------------------
;	 function DelayInit
;	-----------------------------------------
_DelayInit:
;	.\src\main.c: 40: CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
	push	#0x01
	ld	a, #0x04
	call	_CLK_PeripheralClockConfig
;	.\src\main.c: 41: TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249); // 1ms
	push	#0xf9
	ld	a, #0x06
	call	_TIM4_TimeBaseInit
;	.\src\main.c: 42: TIM4_SelectOnePulseMode(TIM4_OPMODE_SINGLE);
	ld	a, #0x01
;	.\src\main.c: 43: }
	jp	_TIM4_SelectOnePulseMode
;	.\src\main.c: 45: void DelayMs(uint16_t ms)
;	-----------------------------------------
;	 function DelayMs
;	-----------------------------------------
_DelayMs:
	sub	sp, #2
;	.\src\main.c: 47: while (ms--)
00104$:
	ldw	(0x01, sp), x
	decw	x
	ldw	y, (0x01, sp)
	jreq	00107$
;	.\src\main.c: 49: TIM4->SR1 = (uint8_t)(~TIM4_FLAG_UPDATE);
	mov	0x5344+0, #0xfe
;	.\src\main.c: 50: TIM4->CR1 |= TIM4_CR1_CEN;
	bset	0x5340, #0
;	.\src\main.c: 51: while ((TIM4->SR1 & (uint8_t)TIM4_FLAG_UPDATE) == 0)
00101$:
	btjt	0x5344, #0, 00104$
	jra	00101$
00107$:
;	.\src\main.c: 54: }
	addw	sp, #2
	ret
;	.\src\main.c: 67: INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
;	-----------------------------------------
;	 function TRAP_IRQHandler
;	-----------------------------------------
_TRAP_IRQHandler:
	clr	a
	div	x, a
;	.\src\main.c: 69: while (1)
00102$:
;	.\src\main.c: 71: nop();
	nop
	jra	00102$
;	.\src\main.c: 73: }
	iret
;	.\src\main.c: 80: INTERRUPT_HANDLER(_this_is_a_example, EXTI_PORTA_IRQn)
;	-----------------------------------------
;	 function _this_is_a_example
;	-----------------------------------------
__this_is_a_example:
;	.\src\main.c: 83: }
	iret
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
