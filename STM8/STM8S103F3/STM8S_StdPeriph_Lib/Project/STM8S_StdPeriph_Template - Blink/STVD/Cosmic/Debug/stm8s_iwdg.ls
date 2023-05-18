   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  85                     ; 48 void IWDG_WriteAccessCmd(IWDG_WriteAccess_TypeDef IWDG_WriteAccess)
  85                     ; 49 {
  87                     .text:	section	.text,new
  88  0000               _IWDG_WriteAccessCmd:
  90  0000 88            	push	a
  91       00000000      OFST:	set	0
  94                     ; 51   assert_param(IS_IWDG_WRITEACCESS_MODE_OK(IWDG_WriteAccess));
  96  0001 a155          	cp	a,#85
  97  0003 2711          	jreq	L21
  98  0005 4d            	tnz	a
  99  0006 270e          	jreq	L21
 100  0008 ae0033        	ldw	x,#51
 101  000b 89            	pushw	x
 102  000c 5f            	clrw	x
 103  000d 89            	pushw	x
 104  000e ae0000        	ldw	x,#L73
 105  0011 cd0000        	call	_assert_failed
 107  0014 5b04          	addw	sp,#4
 108  0016               L21:
 109                     ; 53   IWDG->KR = (uint8_t)IWDG_WriteAccess; /* Write Access */
 111  0016 7b01          	ld	a,(OFST+1,sp)
 112  0018 c750e0        	ld	20704,a
 113                     ; 54 }
 116  001b 84            	pop	a
 117  001c 81            	ret	
 208                     ; 63 void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_Prescaler)
 208                     ; 64 {
 209                     .text:	section	.text,new
 210  0000               _IWDG_SetPrescaler:
 212  0000 88            	push	a
 213       00000000      OFST:	set	0
 216                     ; 66   assert_param(IS_IWDG_PRESCALER_OK(IWDG_Prescaler));
 218  0001 4d            	tnz	a
 219  0002 2726          	jreq	L42
 220  0004 a101          	cp	a,#1
 221  0006 2722          	jreq	L42
 222  0008 a102          	cp	a,#2
 223  000a 271e          	jreq	L42
 224  000c a103          	cp	a,#3
 225  000e 271a          	jreq	L42
 226  0010 a104          	cp	a,#4
 227  0012 2716          	jreq	L42
 228  0014 a105          	cp	a,#5
 229  0016 2712          	jreq	L42
 230  0018 a106          	cp	a,#6
 231  001a 270e          	jreq	L42
 232  001c ae0042        	ldw	x,#66
 233  001f 89            	pushw	x
 234  0020 5f            	clrw	x
 235  0021 89            	pushw	x
 236  0022 ae0000        	ldw	x,#L73
 237  0025 cd0000        	call	_assert_failed
 239  0028 5b04          	addw	sp,#4
 240  002a               L42:
 241                     ; 68   IWDG->PR = (uint8_t)IWDG_Prescaler;
 243  002a 7b01          	ld	a,(OFST+1,sp)
 244  002c c750e1        	ld	20705,a
 245                     ; 69 }
 248  002f 84            	pop	a
 249  0030 81            	ret	
 283                     ; 78 void IWDG_SetReload(uint8_t IWDG_Reload)
 283                     ; 79 {
 284                     .text:	section	.text,new
 285  0000               _IWDG_SetReload:
 289                     ; 80   IWDG->RLR = IWDG_Reload;
 291  0000 c750e2        	ld	20706,a
 292                     ; 81 }
 295  0003 81            	ret	
 318                     ; 89 void IWDG_ReloadCounter(void)
 318                     ; 90 {
 319                     .text:	section	.text,new
 320  0000               _IWDG_ReloadCounter:
 324                     ; 91   IWDG->KR = IWDG_KEY_REFRESH;
 326  0000 35aa50e0      	mov	20704,#170
 327                     ; 92 }
 330  0004 81            	ret	
 353                     ; 99 void IWDG_Enable(void)
 353                     ; 100 {
 354                     .text:	section	.text,new
 355  0000               _IWDG_Enable:
 359                     ; 101   IWDG->KR = IWDG_KEY_ENABLE;
 361  0000 35cc50e0      	mov	20704,#204
 362                     ; 102 }
 365  0004 81            	ret	
 378                     	xdef	_IWDG_Enable
 379                     	xdef	_IWDG_ReloadCounter
 380                     	xdef	_IWDG_SetReload
 381                     	xdef	_IWDG_SetPrescaler
 382                     	xdef	_IWDG_WriteAccessCmd
 383                     	xref	_assert_failed
 384                     .const:	section	.text
 385  0000               L73:
 386  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 387  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 388  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
 389  0036 5f697764672e  	dc.b	"_iwdg.c",0
 409                     	end
