   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
 124                     ; 54 FlagStatus RST_GetFlagStatus(RST_Flag_TypeDef RST_Flag)
 124                     ; 55 {
 126                     .text:	section	.text,new
 127  0000               _RST_GetFlagStatus:
 129  0000 88            	push	a
 130       00000000      OFST:	set	0
 133                     ; 57   assert_param(IS_RST_FLAG_OK(RST_Flag));
 135  0001 a110          	cp	a,#16
 136  0003 271d          	jreq	L21
 137  0005 a108          	cp	a,#8
 138  0007 2719          	jreq	L21
 139  0009 a104          	cp	a,#4
 140  000b 2715          	jreq	L21
 141  000d a102          	cp	a,#2
 142  000f 2711          	jreq	L21
 143  0011 4a            	dec	a
 144  0012 270e          	jreq	L21
 145  0014 ae0039        	ldw	x,#57
 146  0017 89            	pushw	x
 147  0018 5f            	clrw	x
 148  0019 89            	pushw	x
 149  001a ae0000        	ldw	x,#L55
 150  001d cd0000        	call	_assert_failed
 152  0020 5b04          	addw	sp,#4
 153  0022               L21:
 154                     ; 60   return((FlagStatus)(((uint8_t)(RST->SR & RST_Flag) == (uint8_t)0x00) ? RESET : SET));
 156  0022 c650b3        	ld	a,20659
 157  0025 1501          	bcp	a,(OFST+1,sp)
 158  0027 2603          	jrne	L61
 159  0029 4f            	clr	a
 160  002a 2002          	jra	L02
 161  002c               L61:
 162  002c a601          	ld	a,#1
 163  002e               L02:
 166  002e 5b01          	addw	sp,#1
 167  0030 81            	ret	
 203                     ; 69 void RST_ClearFlag(RST_Flag_TypeDef RST_Flag)
 203                     ; 70 {
 204                     .text:	section	.text,new
 205  0000               _RST_ClearFlag:
 207  0000 88            	push	a
 208       00000000      OFST:	set	0
 211                     ; 72   assert_param(IS_RST_FLAG_OK(RST_Flag));
 213  0001 a110          	cp	a,#16
 214  0003 271d          	jreq	L03
 215  0005 a108          	cp	a,#8
 216  0007 2719          	jreq	L03
 217  0009 a104          	cp	a,#4
 218  000b 2715          	jreq	L03
 219  000d a102          	cp	a,#2
 220  000f 2711          	jreq	L03
 221  0011 4a            	dec	a
 222  0012 270e          	jreq	L03
 223  0014 ae0048        	ldw	x,#72
 224  0017 89            	pushw	x
 225  0018 5f            	clrw	x
 226  0019 89            	pushw	x
 227  001a ae0000        	ldw	x,#L55
 228  001d cd0000        	call	_assert_failed
 230  0020 5b04          	addw	sp,#4
 231  0022               L03:
 232                     ; 74   RST->SR = (uint8_t)RST_Flag;
 234  0022 7b01          	ld	a,(OFST+1,sp)
 235  0024 c750b3        	ld	20659,a
 236                     ; 75 }
 239  0027 84            	pop	a
 240  0028 81            	ret	
 253                     	xdef	_RST_ClearFlag
 254                     	xdef	_RST_GetFlagStatus
 255                     	xref	_assert_failed
 256                     .const:	section	.text
 257  0000               L55:
 258  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 259  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 260  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
 261  0036 5f7273742e63  	dc.b	"_rst.c",0
 281                     	end
