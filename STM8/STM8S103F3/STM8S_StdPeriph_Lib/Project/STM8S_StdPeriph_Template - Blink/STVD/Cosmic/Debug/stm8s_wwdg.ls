   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  70                     ; 53 void WWDG_Init(uint8_t Counter, uint8_t WindowValue)
  70                     ; 54 {
  72                     .text:	section	.text,new
  73  0000               _WWDG_Init:
  75  0000 89            	pushw	x
  76       00000000      OFST:	set	0
  79                     ; 56   assert_param(IS_WWDG_WINDOWLIMITVALUE_OK(WindowValue));
  81  0001 9f            	ld	a,xl
  82  0002 a180          	cp	a,#128
  83  0004 250e          	jrult	L01
  84  0006 ae0038        	ldw	x,#56
  85  0009 89            	pushw	x
  86  000a 5f            	clrw	x
  87  000b 89            	pushw	x
  88  000c ae0000        	ldw	x,#L33
  89  000f cd0000        	call	_assert_failed
  91  0012 5b04          	addw	sp,#4
  92  0014               L01:
  93                     ; 58   WWDG->WR = WWDG_WR_RESET_VALUE;
  95  0014 357f50d2      	mov	20690,#127
  96                     ; 59   WWDG->CR = (uint8_t)((uint8_t)(WWDG_CR_WDGA | WWDG_CR_T6) | (uint8_t)Counter);
  98  0018 7b01          	ld	a,(OFST+1,sp)
  99  001a aac0          	or	a,#192
 100  001c c750d1        	ld	20689,a
 101                     ; 60   WWDG->WR = (uint8_t)((uint8_t)(~WWDG_CR_WDGA) & (uint8_t)(WWDG_CR_T6 | WindowValue));
 103  001f 7b02          	ld	a,(OFST+2,sp)
 104  0021 a47f          	and	a,#127
 105  0023 aa40          	or	a,#64
 106  0025 c750d2        	ld	20690,a
 107                     ; 61 }
 110  0028 85            	popw	x
 111  0029 81            	ret	
 146                     ; 69 void WWDG_SetCounter(uint8_t Counter)
 146                     ; 70 {
 147                     .text:	section	.text,new
 148  0000               _WWDG_SetCounter:
 150  0000 88            	push	a
 151       00000000      OFST:	set	0
 154                     ; 72   assert_param(IS_WWDG_COUNTERVALUE_OK(Counter));
 156  0001 a180          	cp	a,#128
 157  0003 250e          	jrult	L02
 158  0005 ae0048        	ldw	x,#72
 159  0008 89            	pushw	x
 160  0009 5f            	clrw	x
 161  000a 89            	pushw	x
 162  000b ae0000        	ldw	x,#L33
 163  000e cd0000        	call	_assert_failed
 165  0011 5b04          	addw	sp,#4
 166  0013               L02:
 167                     ; 76   WWDG->CR = (uint8_t)(Counter & (uint8_t)BIT_MASK);
 169  0013 7b01          	ld	a,(OFST+1,sp)
 170  0015 a47f          	and	a,#127
 171  0017 c750d1        	ld	20689,a
 172                     ; 77 }
 175  001a 84            	pop	a
 176  001b 81            	ret	
 199                     ; 86 uint8_t WWDG_GetCounter(void)
 199                     ; 87 {
 200                     .text:	section	.text,new
 201  0000               _WWDG_GetCounter:
 205                     ; 88   return(WWDG->CR);
 207  0000 c650d1        	ld	a,20689
 210  0003 81            	ret	
 233                     ; 96 void WWDG_SWReset(void)
 233                     ; 97 {
 234                     .text:	section	.text,new
 235  0000               _WWDG_SWReset:
 239                     ; 98   WWDG->CR = WWDG_CR_WDGA; /* Activate WWDG, with clearing T6 */
 241  0000 358050d1      	mov	20689,#128
 242                     ; 99 }
 245  0004 81            	ret	
 281                     ; 108 void WWDG_SetWindowValue(uint8_t WindowValue)
 281                     ; 109 {
 282                     .text:	section	.text,new
 283  0000               _WWDG_SetWindowValue:
 285  0000 88            	push	a
 286       00000000      OFST:	set	0
 289                     ; 111   assert_param(IS_WWDG_WINDOWLIMITVALUE_OK(WindowValue));
 291  0001 a180          	cp	a,#128
 292  0003 250e          	jrult	L43
 293  0005 ae006f        	ldw	x,#111
 294  0008 89            	pushw	x
 295  0009 5f            	clrw	x
 296  000a 89            	pushw	x
 297  000b ae0000        	ldw	x,#L33
 298  000e cd0000        	call	_assert_failed
 300  0011 5b04          	addw	sp,#4
 301  0013               L43:
 302                     ; 113   WWDG->WR = (uint8_t)((uint8_t)(~WWDG_CR_WDGA) & (uint8_t)(WWDG_CR_T6 | WindowValue));
 304  0013 7b01          	ld	a,(OFST+1,sp)
 305  0015 a47f          	and	a,#127
 306  0017 aa40          	or	a,#64
 307  0019 c750d2        	ld	20690,a
 308                     ; 114 }
 311  001c 84            	pop	a
 312  001d 81            	ret	
 325                     	xdef	_WWDG_SetWindowValue
 326                     	xdef	_WWDG_SWReset
 327                     	xdef	_WWDG_GetCounter
 328                     	xdef	_WWDG_SetCounter
 329                     	xdef	_WWDG_Init
 330                     	xref	_assert_failed
 331                     .const:	section	.text
 332  0000               L33:
 333  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 334  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 335  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
 336  0036 5f777764672e  	dc.b	"_wwdg.c",0
 356                     	end
