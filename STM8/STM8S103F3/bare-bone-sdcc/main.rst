                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 4.1.0 #12072 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 ;--------------------------------------------------------
                                     13 ; ram data
                                     14 ;--------------------------------------------------------
                                     15 	.area DATA
                                     16 ;--------------------------------------------------------
                                     17 ; ram data
                                     18 ;--------------------------------------------------------
                                     19 	.area INITIALIZED
                                     20 ;--------------------------------------------------------
                                     21 ; Stack segment in internal ram 
                                     22 ;--------------------------------------------------------
                                     23 	.area	SSEG
      000001                         24 __start__stack:
      000001                         25 	.ds	1
                                     26 
                                     27 ;--------------------------------------------------------
                                     28 ; absolute external ram data
                                     29 ;--------------------------------------------------------
                                     30 	.area DABS (ABS)
                                     31 
                                     32 ; default segment ordering for linker
                                     33 	.area HOME
                                     34 	.area GSINIT
                                     35 	.area GSFINAL
                                     36 	.area CONST
                                     37 	.area INITIALIZER
                                     38 	.area CODE
                                     39 
                                     40 ;--------------------------------------------------------
                                     41 ; interrupt vector 
                                     42 ;--------------------------------------------------------
                                     43 	.area HOME
      008000                         44 __interrupt_vect:
      008000 82 00 80 07             45 	int s_GSINIT ; reset
                                     46 ;--------------------------------------------------------
                                     47 ; global & static initialisations
                                     48 ;--------------------------------------------------------
                                     49 	.area HOME
                                     50 	.area GSINIT
                                     51 	.area GSFINAL
                                     52 	.area GSINIT
      008007                         53 __sdcc_init_data:
                                     54 ; stm8_genXINIT() start
      008007 AE 00 00         [ 2]   55 	ldw x, #l_DATA
      00800A 27 07            [ 1]   56 	jreq	00002$
      00800C                         57 00001$:
      00800C 72 4F 00 00      [ 1]   58 	clr (s_DATA - 1, x)
      008010 5A               [ 2]   59 	decw x
      008011 26 F9            [ 1]   60 	jrne	00001$
      008013                         61 00002$:
      008013 AE 00 00         [ 2]   62 	ldw	x, #l_INITIALIZER
      008016 27 09            [ 1]   63 	jreq	00004$
      008018                         64 00003$:
      008018 D6 80 23         [ 1]   65 	ld	a, (s_INITIALIZER - 1, x)
      00801B D7 00 00         [ 1]   66 	ld	(s_INITIALIZED - 1, x), a
      00801E 5A               [ 2]   67 	decw	x
      00801F 26 F7            [ 1]   68 	jrne	00003$
      008021                         69 00004$:
                                     70 ; stm8_genXINIT() end
                                     71 	.area GSFINAL
      008021 CC 80 04         [ 2]   72 	jp	__sdcc_program_startup
                                     73 ;--------------------------------------------------------
                                     74 ; Home
                                     75 ;--------------------------------------------------------
                                     76 	.area HOME
                                     77 	.area HOME
      008004                         78 __sdcc_program_startup:
      008004 CC 80 5B         [ 2]   79 	jp	_main
                                     80 ;	return from main will return to caller
                                     81 ;--------------------------------------------------------
                                     82 ; code
                                     83 ;--------------------------------------------------------
                                     84 	.area CODE
                                     85 ;	main.c: 9: static inline void delay_ms(uint16_t ms) {
                                     86 ;	-----------------------------------------
                                     87 ;	 function delay_ms
                                     88 ;	-----------------------------------------
      008024                         89 _delay_ms:
      008024 52 08            [ 2]   90 	sub	sp, #8
                                     91 ;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008026 5F               [ 1]   92 	clrw	x
      008027 1F 07            [ 2]   93 	ldw	(0x07, sp), x
      008029 1F 05            [ 2]   94 	ldw	(0x05, sp), x
      00802B                         95 00103$:
      00802B 1E 0B            [ 2]   96 	ldw	x, (0x0b, sp)
      00802D 89               [ 2]   97 	pushw	x
      00802E 4B 6F            [ 1]   98 	push	#0x6f
      008030 4B 00            [ 1]   99 	push	#0x00
      008032 CD 80 7F         [ 4]  100 	call	___muluint2ulong
      008035 5B 04            [ 2]  101 	addw	sp, #4
      008037 1F 03            [ 2]  102 	ldw	(0x03, sp), x
      008039 17 01            [ 2]  103 	ldw	(0x01, sp), y
      00803B 1E 07            [ 2]  104 	ldw	x, (0x07, sp)
      00803D 13 03            [ 2]  105 	cpw	x, (0x03, sp)
      00803F 7B 06            [ 1]  106 	ld	a, (0x06, sp)
      008041 12 02            [ 1]  107 	sbc	a, (0x02, sp)
      008043 7B 05            [ 1]  108 	ld	a, (0x05, sp)
      008045 12 01            [ 1]  109 	sbc	a, (0x01, sp)
      008047 24 0F            [ 1]  110 	jrnc	00105$
                                    111 ;	main.c: 12: __asm__("nop");
      008049 9D               [ 1]  112 	nop
                                    113 ;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      00804A 1E 07            [ 2]  114 	ldw	x, (0x07, sp)
      00804C 5C               [ 1]  115 	incw	x
      00804D 1F 07            [ 2]  116 	ldw	(0x07, sp), x
      00804F 26 DA            [ 1]  117 	jrne	00103$
      008051 1E 05            [ 2]  118 	ldw	x, (0x05, sp)
      008053 5C               [ 1]  119 	incw	x
      008054 1F 05            [ 2]  120 	ldw	(0x05, sp), x
      008056 20 D3            [ 2]  121 	jra	00103$
      008058                        122 00105$:
                                    123 ;	main.c: 13: }
      008058 5B 08            [ 2]  124 	addw	sp, #8
      00805A 81               [ 4]  125 	ret
                                    126 ;	main.c: 14: void main() {
                                    127 ;	-----------------------------------------
                                    128 ;	 function main
                                    129 ;	-----------------------------------------
      00805B                        130 _main:
                                    131 ;	main.c: 15: PD_DDR |= (1 << LED_PIN); // configure PD4 as output
      00805B 72 18 50 11      [ 1]  132 	bset	20497, #4
                                    133 ;	main.c: 16: PD_CR1 |= (1 << LED_PIN); // push-pull mode
      00805F 72 18 50 12      [ 1]  134 	bset	20498, #4
                                    135 ;	main.c: 17: while (1) {
      008063                        136 00102$:
                                    137 ;	main.c: 19: PD_ODR ^= (1 << LED_PIN);
      008063 90 18 50 0F      [ 1]  138 	bcpl	20495, #4
                                    139 ;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008067 90 5F            [ 1]  140 	clrw	y
      008069 5F               [ 1]  141 	clrw	x
      00806A                        142 00107$:
      00806A 90 A3 6C 66      [ 2]  143 	cpw	y, #0x6c66
      00806E 9F               [ 1]  144 	ld	a, xl
      00806F A2 00            [ 1]  145 	sbc	a, #0x00
      008071 9E               [ 1]  146 	ld	a, xh
      008072 A2 00            [ 1]  147 	sbc	a, #0x00
      008074 24 ED            [ 1]  148 	jrnc	00102$
                                    149 ;	main.c: 12: __asm__("nop");
      008076 9D               [ 1]  150 	nop
                                    151 ;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
      008077 90 5C            [ 1]  152 	incw	y
      008079 26 EF            [ 1]  153 	jrne	00107$
      00807B 5C               [ 1]  154 	incw	x
      00807C 20 EC            [ 2]  155 	jra	00107$
                                    156 ;	main.c: 20: delay_ms(250);
                                    157 ;	main.c: 22: }
      00807E 81               [ 4]  158 	ret
                                    159 	.area CODE
                                    160 	.area CONST
                                    161 	.area INITIALIZER
                                    162 	.area CABS (ABS)
