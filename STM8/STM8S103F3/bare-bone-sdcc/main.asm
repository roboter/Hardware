;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.0 #12072 (MINGW64)
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
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
;	main.c: 9: static inline void delay_ms(uint16_t ms) {
;	-----------------------------------------
;	 function delay_ms
;	-----------------------------------------
_delay_ms:
	sub	sp, #8
;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	x
	ldw	(0x07, sp), x
	ldw	(0x05, sp), x
00103$:
	ldw	x, (0x0b, sp)
	pushw	x
	push	#0x6f
	push	#0x00
	call	___muluint2ulong
	addw	sp, #4
	ldw	(0x03, sp), x
	ldw	(0x01, sp), y
	ldw	x, (0x07, sp)
	cpw	x, (0x03, sp)
	ld	a, (0x06, sp)
	sbc	a, (0x02, sp)
	ld	a, (0x05, sp)
	sbc	a, (0x01, sp)
	jrnc	00105$
;	main.c: 12: __asm__("nop");
	nop
;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	ldw	x, (0x07, sp)
	incw	x
	ldw	(0x07, sp), x
	jrne	00103$
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
	jra	00103$
00105$:
;	main.c: 13: }
	addw	sp, #8
	ret
;	main.c: 14: void main() {
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	main.c: 15: PD_DDR |= (1 << LED_PIN); // configure PD4 as output
	bset	20497, #4
;	main.c: 16: PD_CR1 |= (1 << LED_PIN); // push-pull mode
	bset	20498, #4
;	main.c: 17: while (1) {
00102$:
;	main.c: 19: PD_ODR ^= (1 << LED_PIN);
	bcpl	20495, #4
;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	clrw	y
	clrw	x
00107$:
	cpw	y, #0x6c66
	ld	a, xl
	sbc	a, #0x00
	ld	a, xh
	sbc	a, #0x00
	jrnc	00102$
;	main.c: 12: __asm__("nop");
	nop
;	main.c: 11: for (i = 0; i < ((F_CPU / 18000UL) * ms); i++)
	incw	y
	jrne	00107$
	incw	x
	jra	00107$
;	main.c: 20: delay_ms(250);
;	main.c: 22: }
	ret
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
