                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.2.0 #13081 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl __this_is_a_example
                                     12 	.globl _TRAP_IRQHandler
                                     13 	.globl _main
                                     14 	.globl _TIM4_SelectOnePulseMode
                                     15 	.globl _TIM4_TimeBaseInit
                                     16 	.globl _GPIO_WriteReverse
                                     17 	.globl _GPIO_Init
                                     18 	.globl _CLK_HSIPrescalerConfig
                                     19 	.globl _CLK_PeripheralClockConfig
                                     20 	.globl _DelayInit
                                     21 	.globl _DelayMs
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area DATA
                                     26 ;--------------------------------------------------------
                                     27 ; ram data
                                     28 ;--------------------------------------------------------
                                     29 	.area INITIALIZED
                                     30 ;--------------------------------------------------------
                                     31 ; Stack segment in internal ram
                                     32 ;--------------------------------------------------------
                                     33 	.area	SSEG
      000001                         34 __start__stack:
      000001                         35 	.ds	1
                                     36 
                                     37 ;--------------------------------------------------------
                                     38 ; absolute external ram data
                                     39 ;--------------------------------------------------------
                                     40 	.area DABS (ABS)
                                     41 
                                     42 ; default segment ordering for linker
                                     43 	.area HOME
                                     44 	.area GSINIT
                                     45 	.area GSFINAL
                                     46 	.area CONST
                                     47 	.area INITIALIZER
                                     48 	.area CODE
                                     49 
                                     50 ;--------------------------------------------------------
                                     51 ; interrupt vector
                                     52 ;--------------------------------------------------------
                                     53 	.area HOME
      008000                         54 __interrupt_vect:
      008000 82 00 80 1B             55 	int s_GSINIT ; reset
      008004 82 00 80 94             56 	int _TRAP_IRQHandler ; trap
      008008 82 00 00 00             57 	int 0x000000 ; int0
      00800C 82 00 00 00             58 	int 0x000000 ; int1
      008010 82 00 00 00             59 	int 0x000000 ; int2
      008014 82 00 80 9A             60 	int __this_is_a_example ; int3
                                     61 ;--------------------------------------------------------
                                     62 ; global & static initialisations
                                     63 ;--------------------------------------------------------
                                     64 	.area HOME
                                     65 	.area GSINIT
                                     66 	.area GSFINAL
                                     67 	.area GSINIT
      00801B                         68 __sdcc_init_data:
                                     69 ; stm8_genXINIT() start
      00801B AE 00 00         [ 2]   70 	ldw x, #l_DATA
      00801E 27 07            [ 1]   71 	jreq	00002$
      008020                         72 00001$:
      008020 72 4F 00 00      [ 1]   73 	clr (s_DATA - 1, x)
      008024 5A               [ 2]   74 	decw x
      008025 26 F9            [ 1]   75 	jrne	00001$
      008027                         76 00002$:
      008027 AE 00 00         [ 2]   77 	ldw	x, #l_INITIALIZER
      00802A 27 09            [ 1]   78 	jreq	00004$
      00802C                         79 00003$:
      00802C D6 80 43         [ 1]   80 	ld	a, (s_INITIALIZER - 1, x)
      00802F D7 00 00         [ 1]   81 	ld	(s_INITIALIZED - 1, x), a
      008032 5A               [ 2]   82 	decw	x
      008033 26 F7            [ 1]   83 	jrne	00003$
      008035                         84 00004$:
                                     85 ; stm8_genXINIT() end
                                     86 	.area GSFINAL
      008035 CC 80 18         [ 2]   87 	jp	__sdcc_program_startup
                                     88 ;--------------------------------------------------------
                                     89 ; Home
                                     90 ;--------------------------------------------------------
                                     91 	.area HOME
                                     92 	.area HOME
      008018                         93 __sdcc_program_startup:
      008018 CC 80 44         [ 2]   94 	jp	_main
                                     95 ;	return from main will return to caller
                                     96 ;--------------------------------------------------------
                                     97 ; code
                                     98 ;--------------------------------------------------------
                                     99 	.area CODE
                                    100 ;	.\src\main.c: 20: void main(void)
                                    101 ;	-----------------------------------------
                                    102 ;	 function main
                                    103 ;	-----------------------------------------
      008044                        104 _main:
                                    105 ;	.\src\main.c: 23: CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
      008044 4F               [ 1]  106 	clr	a
      008045 CD 83 1E         [ 4]  107 	call	_CLK_HSIPrescalerConfig
                                    108 ;	.\src\main.c: 26: DelayInit();
      008048 CD 80 66         [ 4]  109 	call	_DelayInit
                                    110 ;	.\src\main.c: 29: GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
      00804B 4B E0            [ 1]  111 	push	#0xe0
      00804D A6 20            [ 1]  112 	ld	a, #0x20
      00804F AE 50 05         [ 2]  113 	ldw	x, #0x5005
      008052 CD 80 AA         [ 4]  114 	call	_GPIO_Init
                                    115 ;	.\src\main.c: 31: while (1)
      008055                        116 00102$:
                                    117 ;	.\src\main.c: 33: GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
      008055 A6 20            [ 1]  118 	ld	a, #0x20
      008057 AE 50 05         [ 2]  119 	ldw	x, #0x5005
      00805A CD 81 3A         [ 4]  120 	call	_GPIO_WriteReverse
                                    121 ;	.\src\main.c: 34: DelayMs(500);
      00805D AE 01 F4         [ 2]  122 	ldw	x, #0x01f4
      008060 CD 80 79         [ 4]  123 	call	_DelayMs
      008063 20 F0            [ 2]  124 	jra	00102$
                                    125 ;	.\src\main.c: 36: }
      008065 81               [ 4]  126 	ret
                                    127 ;	.\src\main.c: 38: void DelayInit(void)
                                    128 ;	-----------------------------------------
                                    129 ;	 function DelayInit
                                    130 ;	-----------------------------------------
      008066                        131 _DelayInit:
                                    132 ;	.\src\main.c: 40: CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
      008066 4B 01            [ 1]  133 	push	#0x01
      008068 A6 04            [ 1]  134 	ld	a, #0x04
      00806A CD 82 29         [ 4]  135 	call	_CLK_PeripheralClockConfig
                                    136 ;	.\src\main.c: 41: TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249); // 1ms
      00806D 4B F9            [ 1]  137 	push	#0xf9
      00806F A6 06            [ 1]  138 	ld	a, #0x06
      008071 CD 84 C5         [ 4]  139 	call	_TIM4_TimeBaseInit
                                    140 ;	.\src\main.c: 42: TIM4_SelectOnePulseMode(TIM4_OPMODE_SINGLE);
      008074 A6 01            [ 1]  141 	ld	a, #0x01
                                    142 ;	.\src\main.c: 43: }
      008076 CC 85 28         [ 2]  143 	jp	_TIM4_SelectOnePulseMode
                                    144 ;	.\src\main.c: 45: void DelayMs(uint16_t ms)
                                    145 ;	-----------------------------------------
                                    146 ;	 function DelayMs
                                    147 ;	-----------------------------------------
      008079                        148 _DelayMs:
      008079 52 02            [ 2]  149 	sub	sp, #2
                                    150 ;	.\src\main.c: 47: while (ms--)
      00807B                        151 00104$:
      00807B 1F 01            [ 2]  152 	ldw	(0x01, sp), x
      00807D 5A               [ 2]  153 	decw	x
      00807E 16 01            [ 2]  154 	ldw	y, (0x01, sp)
      008080 27 0F            [ 1]  155 	jreq	00107$
                                    156 ;	.\src\main.c: 49: TIM4->SR1 = (uint8_t)(~TIM4_FLAG_UPDATE);
      008082 35 FE 53 44      [ 1]  157 	mov	0x5344+0, #0xfe
                                    158 ;	.\src\main.c: 50: TIM4->CR1 |= TIM4_CR1_CEN;
      008086 72 10 53 40      [ 1]  159 	bset	0x5340, #0
                                    160 ;	.\src\main.c: 51: while ((TIM4->SR1 & (uint8_t)TIM4_FLAG_UPDATE) == 0)
      00808A                        161 00101$:
      00808A 72 00 53 44 EC   [ 2]  162 	btjt	0x5344, #0, 00104$
      00808F 20 F9            [ 2]  163 	jra	00101$
      008091                        164 00107$:
                                    165 ;	.\src\main.c: 54: }
      008091 5B 02            [ 2]  166 	addw	sp, #2
      008093 81               [ 4]  167 	ret
                                    168 ;	.\src\main.c: 67: INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
                                    169 ;	-----------------------------------------
                                    170 ;	 function TRAP_IRQHandler
                                    171 ;	-----------------------------------------
      008094                        172 _TRAP_IRQHandler:
      008094 4F               [ 1]  173 	clr	a
      008095 62               [ 2]  174 	div	x, a
                                    175 ;	.\src\main.c: 69: while (1)
      008096                        176 00102$:
                                    177 ;	.\src\main.c: 71: nop();
      008096 9D               [ 1]  178 	nop
      008097 20 FD            [ 2]  179 	jra	00102$
                                    180 ;	.\src\main.c: 73: }
      008099 80               [11]  181 	iret
                                    182 ;	.\src\main.c: 80: INTERRUPT_HANDLER(_this_is_a_example, EXTI_PORTA_IRQn)
                                    183 ;	-----------------------------------------
                                    184 ;	 function _this_is_a_example
                                    185 ;	-----------------------------------------
      00809A                        186 __this_is_a_example:
                                    187 ;	.\src\main.c: 83: }
      00809A 80               [11]  188 	iret
                                    189 	.area CODE
                                    190 	.area CONST
                                    191 	.area INITIALIZER
                                    192 	.area CABS (ABS)
