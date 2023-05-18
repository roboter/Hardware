   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 54 void BEEP_DeInit(void)
  49                     ; 55 {
  51                     .text:	section	.text,new
  52  0000               _BEEP_DeInit:
  56                     ; 56   BEEP->CSR = BEEP_CSR_RESET_VALUE;
  58  0000 351f50f3      	mov	20723,#31
  59                     ; 57 }
  62  0004 81            	ret	
 128                     ; 67 void BEEP_Init(BEEP_Frequency_TypeDef BEEP_Frequency)
 128                     ; 68 {
 129                     .text:	section	.text,new
 130  0000               _BEEP_Init:
 132  0000 88            	push	a
 133       00000000      OFST:	set	0
 136                     ; 70   assert_param(IS_BEEP_FREQUENCY_OK(BEEP_Frequency));
 138  0001 4d            	tnz	a
 139  0002 2716          	jreq	L41
 140  0004 a140          	cp	a,#64
 141  0006 2712          	jreq	L41
 142  0008 a180          	cp	a,#128
 143  000a 270e          	jreq	L41
 144  000c ae0046        	ldw	x,#70
 145  000f 89            	pushw	x
 146  0010 5f            	clrw	x
 147  0011 89            	pushw	x
 148  0012 ae000c        	ldw	x,#L15
 149  0015 cd0000        	call	_assert_failed
 151  0018 5b04          	addw	sp,#4
 152  001a               L41:
 153                     ; 73   if ((BEEP->CSR & BEEP_CSR_BEEPDIV) == BEEP_CSR_BEEPDIV)
 155  001a c650f3        	ld	a,20723
 156  001d a41f          	and	a,#31
 157  001f a11f          	cp	a,#31
 158  0021 2610          	jrne	L35
 159                     ; 75     BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPDIV); /* Clear bits */
 161  0023 c650f3        	ld	a,20723
 162  0026 a4e0          	and	a,#224
 163  0028 c750f3        	ld	20723,a
 164                     ; 76     BEEP->CSR |= BEEP_CALIBRATION_DEFAULT;
 166  002b c650f3        	ld	a,20723
 167  002e aa0b          	or	a,#11
 168  0030 c750f3        	ld	20723,a
 169  0033               L35:
 170                     ; 80   BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPSEL);
 172  0033 c650f3        	ld	a,20723
 173  0036 a43f          	and	a,#63
 174  0038 c750f3        	ld	20723,a
 175                     ; 81   BEEP->CSR |= (uint8_t)(BEEP_Frequency);
 177  003b c650f3        	ld	a,20723
 178  003e 1a01          	or	a,(OFST+1,sp)
 179  0040 c750f3        	ld	20723,a
 180                     ; 82 }
 183  0043 84            	pop	a
 184  0044 81            	ret	
 239                     ; 91 void BEEP_Cmd(FunctionalState NewState)
 239                     ; 92 {
 240                     .text:	section	.text,new
 241  0000               _BEEP_Cmd:
 245                     ; 93   if (NewState != DISABLE)
 247  0000 4d            	tnz	a
 248  0001 2705          	jreq	L301
 249                     ; 96     BEEP->CSR |= BEEP_CSR_BEEPEN;
 251  0003 721a50f3      	bset	20723,#5
 254  0007 81            	ret	
 255  0008               L301:
 256                     ; 101     BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPEN);
 258  0008 721b50f3      	bres	20723,#5
 259                     ; 103 }
 262  000c 81            	ret	
 316                     .const:	section	.text
 317  0000               L62:
 318  0000 0001adb0      	dc.l	110000
 319  0004               L03:
 320  0004 000249f1      	dc.l	150001
 321  0008               L63:
 322  0008 000003e8      	dc.l	1000
 323                     ; 118 void BEEP_LSICalibrationConfig(uint32_t LSIFreqHz)
 323                     ; 119 {
 324                     .text:	section	.text,new
 325  0000               _BEEP_LSICalibrationConfig:
 327  0000 5206          	subw	sp,#6
 328       00000006      OFST:	set	6
 331                     ; 124   assert_param(IS_LSI_FREQUENCY_OK(LSIFreqHz));
 333  0002 96            	ldw	x,sp
 334  0003 1c0009        	addw	x,#OFST+3
 335  0006 cd0000        	call	c_ltor
 337  0009 ae0000        	ldw	x,#L62
 338  000c cd0000        	call	c_lcmp
 340  000f 250f          	jrult	L42
 341  0011 96            	ldw	x,sp
 342  0012 1c0009        	addw	x,#OFST+3
 343  0015 cd0000        	call	c_ltor
 345  0018 ae0004        	ldw	x,#L03
 346  001b cd0000        	call	c_lcmp
 348  001e 250e          	jrult	L23
 349  0020               L42:
 350  0020 ae007c        	ldw	x,#124
 351  0023 89            	pushw	x
 352  0024 5f            	clrw	x
 353  0025 89            	pushw	x
 354  0026 ae000c        	ldw	x,#L15
 355  0029 cd0000        	call	_assert_failed
 357  002c 5b04          	addw	sp,#4
 358  002e               L23:
 359                     ; 126   lsifreqkhz = (uint16_t)(LSIFreqHz / 1000); /* Converts value in kHz */
 361  002e 96            	ldw	x,sp
 362  002f 1c0009        	addw	x,#OFST+3
 363  0032 cd0000        	call	c_ltor
 365  0035 ae0008        	ldw	x,#L63
 366  0038 cd0000        	call	c_ludv
 368  003b be02          	ldw	x,c_lreg+2
 369  003d 1f03          	ldw	(OFST-3,sp),x
 371                     ; 130   BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPDIV); /* Clear bits */
 373  003f c650f3        	ld	a,20723
 374  0042 a4e0          	and	a,#224
 375  0044 c750f3        	ld	20723,a
 376                     ; 132   A = (uint16_t)(lsifreqkhz >> 3U); /* Division by 8, keep integer part only */
 378  0047 54            	srlw	x
 379  0048 54            	srlw	x
 380  0049 54            	srlw	x
 381  004a 1f05          	ldw	(OFST-1,sp),x
 383                     ; 134   if ((8U * A) >= ((lsifreqkhz - (8U * A)) * (1U + (2U * A))))
 385  004c 58            	sllw	x
 386  004d 58            	sllw	x
 387  004e 58            	sllw	x
 388  004f 1f01          	ldw	(OFST-5,sp),x
 390  0051 1e03          	ldw	x,(OFST-3,sp)
 391  0053 72f001        	subw	x,(OFST-5,sp)
 392  0056 1605          	ldw	y,(OFST-1,sp)
 393  0058 9058          	sllw	y
 394  005a 905c          	incw	y
 395  005c cd0000        	call	c_imul
 397  005f 1605          	ldw	y,(OFST-1,sp)
 398  0061 9058          	sllw	y
 399  0063 9058          	sllw	y
 400  0065 bf00          	ldw	c_x,x
 401  0067 9058          	sllw	y
 402  0069 90b300        	cpw	y,c_x
 403  006c 7b06          	ld	a,(OFST+0,sp)
 404  006e 2504          	jrult	L531
 405                     ; 136     BEEP->CSR |= (uint8_t)(A - 2U);
 407  0070 a002          	sub	a,#2
 409  0072 2001          	jra	L731
 410  0074               L531:
 411                     ; 140     BEEP->CSR |= (uint8_t)(A - 1U);
 413  0074 4a            	dec	a
 414  0075               L731:
 415  0075 ca50f3        	or	a,20723
 416  0078 c750f3        	ld	20723,a
 417                     ; 142 }
 420  007b 5b06          	addw	sp,#6
 421  007d 81            	ret	
 434                     	xdef	_BEEP_LSICalibrationConfig
 435                     	xdef	_BEEP_Cmd
 436                     	xdef	_BEEP_Init
 437                     	xdef	_BEEP_DeInit
 438                     	xref	_assert_failed
 439                     	switch	.const
 440  000c               L15:
 441  000c 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 442  001e 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 443  0030 685f64726976  	dc.b	"h_driver\src\stm8s"
 444  0042 5f626565702e  	dc.b	"_beep.c",0
 445                     	xref.b	c_lreg
 446                     	xref.b	c_x
 466                     	xref	c_imul
 467                     	xref	c_ludv
 468                     	xref	c_lcmp
 469                     	xref	c_ltor
 470                     	end
