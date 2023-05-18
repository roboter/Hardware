   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  21                     .const:	section	.text
  22  0000               _APR_Array:
  23  0000 00            	dc.b	0
  24  0001 1e            	dc.b	30
  25  0002 1e            	dc.b	30
  26  0003 1e            	dc.b	30
  27  0004 1e            	dc.b	30
  28  0005 1e            	dc.b	30
  29  0006 1e            	dc.b	30
  30  0007 1e            	dc.b	30
  31  0008 1e            	dc.b	30
  32  0009 1e            	dc.b	30
  33  000a 1e            	dc.b	30
  34  000b 1e            	dc.b	30
  35  000c 1e            	dc.b	30
  36  000d 3d            	dc.b	61
  37  000e 17            	dc.b	23
  38  000f 17            	dc.b	23
  39  0010 3e            	dc.b	62
  40  0011               _TBR_Array:
  41  0011 00            	dc.b	0
  42  0012 01            	dc.b	1
  43  0013 02            	dc.b	2
  44  0014 03            	dc.b	3
  45  0015 04            	dc.b	4
  46  0016 05            	dc.b	5
  47  0017 06            	dc.b	6
  48  0018 07            	dc.b	7
  49  0019 08            	dc.b	8
  50  001a 09            	dc.b	9
  51  001b 0a            	dc.b	10
  52  001c 0b            	dc.b	11
  53  001d 0c            	dc.b	12
  54  001e 0c            	dc.b	12
  55  001f 0e            	dc.b	14
  56  0020 0f            	dc.b	15
  57  0021 0f            	dc.b	15
  86                     ; 73 void AWU_DeInit(void)
  86                     ; 74 {
  88                     .text:	section	.text,new
  89  0000               _AWU_DeInit:
  93                     ; 75   AWU->CSR = AWU_CSR_RESET_VALUE;
  95  0000 725f50f0      	clr	20720
  96                     ; 76   AWU->APR = AWU_APR_RESET_VALUE;
  98  0004 353f50f1      	mov	20721,#63
  99                     ; 77   AWU->TBR = AWU_TBR_RESET_VALUE;
 101  0008 725f50f2      	clr	20722
 102                     ; 78 }
 105  000c 81            	ret	
 268                     ; 88 void AWU_Init(AWU_Timebase_TypeDef AWU_TimeBase)
 268                     ; 89 {
 269                     .text:	section	.text,new
 270  0000               _AWU_Init:
 272  0000 88            	push	a
 273       00000000      OFST:	set	0
 276                     ; 91   assert_param(IS_AWU_TIMEBASE_OK(AWU_TimeBase));
 278  0001 4d            	tnz	a
 279  0002 274e          	jreq	L41
 280  0004 a101          	cp	a,#1
 281  0006 274a          	jreq	L41
 282  0008 a102          	cp	a,#2
 283  000a 2746          	jreq	L41
 284  000c a103          	cp	a,#3
 285  000e 2742          	jreq	L41
 286  0010 a104          	cp	a,#4
 287  0012 273e          	jreq	L41
 288  0014 a105          	cp	a,#5
 289  0016 273a          	jreq	L41
 290  0018 a106          	cp	a,#6
 291  001a 2736          	jreq	L41
 292  001c a107          	cp	a,#7
 293  001e 2732          	jreq	L41
 294  0020 a108          	cp	a,#8
 295  0022 272e          	jreq	L41
 296  0024 a109          	cp	a,#9
 297  0026 272a          	jreq	L41
 298  0028 a10a          	cp	a,#10
 299  002a 2726          	jreq	L41
 300  002c a10b          	cp	a,#11
 301  002e 2722          	jreq	L41
 302  0030 a10c          	cp	a,#12
 303  0032 271e          	jreq	L41
 304  0034 a10d          	cp	a,#13
 305  0036 271a          	jreq	L41
 306  0038 a10e          	cp	a,#14
 307  003a 2716          	jreq	L41
 308  003c a10f          	cp	a,#15
 309  003e 2712          	jreq	L41
 310  0040 a110          	cp	a,#16
 311  0042 270e          	jreq	L41
 312  0044 ae005b        	ldw	x,#91
 313  0047 89            	pushw	x
 314  0048 5f            	clrw	x
 315  0049 89            	pushw	x
 316  004a ae002e        	ldw	x,#L501
 317  004d cd0000        	call	_assert_failed
 319  0050 5b04          	addw	sp,#4
 320  0052               L41:
 321                     ; 94   AWU->CSR |= AWU_CSR_AWUEN;
 323  0052 721850f0      	bset	20720,#4
 324                     ; 97   AWU->TBR &= (uint8_t)(~AWU_TBR_AWUTB);
 326  0056 c650f2        	ld	a,20722
 327  0059 a4f0          	and	a,#240
 328  005b c750f2        	ld	20722,a
 329                     ; 98   AWU->TBR |= TBR_Array[(uint8_t)AWU_TimeBase];
 331  005e 7b01          	ld	a,(OFST+1,sp)
 332  0060 5f            	clrw	x
 333  0061 97            	ld	xl,a
 334  0062 c650f2        	ld	a,20722
 335  0065 da0011        	or	a,(_TBR_Array,x)
 336  0068 c750f2        	ld	20722,a
 337                     ; 101   AWU->APR &= (uint8_t)(~AWU_APR_APR);
 339  006b c650f1        	ld	a,20721
 340  006e a4c0          	and	a,#192
 341  0070 c750f1        	ld	20721,a
 342                     ; 102   AWU->APR |= APR_Array[(uint8_t)AWU_TimeBase];
 344  0073 7b01          	ld	a,(OFST+1,sp)
 345  0075 5f            	clrw	x
 346  0076 97            	ld	xl,a
 347  0077 c650f1        	ld	a,20721
 348  007a da0000        	or	a,(_APR_Array,x)
 349  007d c750f1        	ld	20721,a
 350                     ; 103 }
 353  0080 84            	pop	a
 354  0081 81            	ret	
 409                     ; 112 void AWU_Cmd(FunctionalState NewState)
 409                     ; 113 {
 410                     .text:	section	.text,new
 411  0000               _AWU_Cmd:
 415                     ; 114   if (NewState != DISABLE)
 417  0000 4d            	tnz	a
 418  0001 2705          	jreq	L531
 419                     ; 117     AWU->CSR |= AWU_CSR_AWUEN;
 421  0003 721850f0      	bset	20720,#4
 424  0007 81            	ret	
 425  0008               L531:
 426                     ; 122     AWU->CSR &= (uint8_t)(~AWU_CSR_AWUEN);
 428  0008 721950f0      	bres	20720,#4
 429                     ; 124 }
 432  000c 81            	ret	
 486                     	switch	.const
 487  0022               L62:
 488  0022 0001adb0      	dc.l	110000
 489  0026               L03:
 490  0026 000249f1      	dc.l	150001
 491  002a               L63:
 492  002a 000003e8      	dc.l	1000
 493                     ; 139 void AWU_LSICalibrationConfig(uint32_t LSIFreqHz)
 493                     ; 140 {
 494                     .text:	section	.text,new
 495  0000               _AWU_LSICalibrationConfig:
 497  0000 5206          	subw	sp,#6
 498       00000006      OFST:	set	6
 501                     ; 141   uint16_t lsifreqkhz = 0x0;
 503                     ; 142   uint16_t A = 0x0;
 505                     ; 145   assert_param(IS_LSI_FREQUENCY_OK(LSIFreqHz));
 507  0002 96            	ldw	x,sp
 508  0003 1c0009        	addw	x,#OFST+3
 509  0006 cd0000        	call	c_ltor
 511  0009 ae0022        	ldw	x,#L62
 512  000c cd0000        	call	c_lcmp
 514  000f 250f          	jrult	L42
 515  0011 96            	ldw	x,sp
 516  0012 1c0009        	addw	x,#OFST+3
 517  0015 cd0000        	call	c_ltor
 519  0018 ae0026        	ldw	x,#L03
 520  001b cd0000        	call	c_lcmp
 522  001e 250e          	jrult	L23
 523  0020               L42:
 524  0020 ae0091        	ldw	x,#145
 525  0023 89            	pushw	x
 526  0024 5f            	clrw	x
 527  0025 89            	pushw	x
 528  0026 ae002e        	ldw	x,#L501
 529  0029 cd0000        	call	_assert_failed
 531  002c 5b04          	addw	sp,#4
 532  002e               L23:
 533                     ; 147   lsifreqkhz = (uint16_t)(LSIFreqHz / 1000); /* Converts value in kHz */
 535  002e 96            	ldw	x,sp
 536  002f 1c0009        	addw	x,#OFST+3
 537  0032 cd0000        	call	c_ltor
 539  0035 ae002a        	ldw	x,#L63
 540  0038 cd0000        	call	c_ludv
 542  003b be02          	ldw	x,c_lreg+2
 543  003d 1f03          	ldw	(OFST-3,sp),x
 545                     ; 151   A = (uint16_t)(lsifreqkhz >> 2U); /* Division by 4, keep integer part only */
 547  003f 54            	srlw	x
 548  0040 54            	srlw	x
 549  0041 1f05          	ldw	(OFST-1,sp),x
 551                     ; 153   if ((4U * A) >= ((lsifreqkhz - (4U * A)) * (1U + (2U * A))))
 553  0043 58            	sllw	x
 554  0044 58            	sllw	x
 555  0045 1f01          	ldw	(OFST-5,sp),x
 557  0047 1e03          	ldw	x,(OFST-3,sp)
 558  0049 72f001        	subw	x,(OFST-5,sp)
 559  004c 1605          	ldw	y,(OFST-1,sp)
 560  004e 9058          	sllw	y
 561  0050 905c          	incw	y
 562  0052 cd0000        	call	c_imul
 564  0055 1605          	ldw	y,(OFST-1,sp)
 565  0057 9058          	sllw	y
 566  0059 bf00          	ldw	c_x,x
 567  005b 9058          	sllw	y
 568  005d 90b300        	cpw	y,c_x
 569  0060 7b06          	ld	a,(OFST+0,sp)
 570  0062 2504          	jrult	L761
 571                     ; 155     AWU->APR = (uint8_t)(A - 2U);
 573  0064 a002          	sub	a,#2
 575  0066 2001          	jra	L171
 576  0068               L761:
 577                     ; 159     AWU->APR = (uint8_t)(A - 1U);
 579  0068 4a            	dec	a
 580  0069               L171:
 581  0069 c750f1        	ld	20721,a
 582                     ; 161 }
 585  006c 5b06          	addw	sp,#6
 586  006e 81            	ret	
 609                     ; 168 void AWU_IdleModeEnable(void)
 609                     ; 169 {
 610                     .text:	section	.text,new
 611  0000               _AWU_IdleModeEnable:
 615                     ; 171   AWU->CSR &= (uint8_t)(~AWU_CSR_AWUEN);
 617  0000 721950f0      	bres	20720,#4
 618                     ; 174   AWU->TBR = (uint8_t)(~AWU_TBR_AWUTB);
 620  0004 35f050f2      	mov	20722,#240
 621                     ; 175 }
 624  0008 81            	ret	
 668                     ; 183 FlagStatus AWU_GetFlagStatus(void)
 668                     ; 184 {
 669                     .text:	section	.text,new
 670  0000               _AWU_GetFlagStatus:
 674                     ; 185   return((FlagStatus)(((uint8_t)(AWU->CSR & AWU_CSR_AWUF) == (uint8_t)0x00) ? RESET : SET));
 676  0000 720a50f002    	btjt	20720,#5,L44
 677  0005 4f            	clr	a
 679  0006 81            	ret	
 680  0007               L44:
 681  0007 a601          	ld	a,#1
 684  0009 81            	ret	
 719                     	xdef	_TBR_Array
 720                     	xdef	_APR_Array
 721                     	xdef	_AWU_GetFlagStatus
 722                     	xdef	_AWU_IdleModeEnable
 723                     	xdef	_AWU_LSICalibrationConfig
 724                     	xdef	_AWU_Cmd
 725                     	xdef	_AWU_Init
 726                     	xdef	_AWU_DeInit
 727                     	xref	_assert_failed
 728                     	switch	.const
 729  002e               L501:
 730  002e 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 731  0040 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 732  0052 685f64726976  	dc.b	"h_driver\src\stm8s"
 733  0064 5f6177752e63  	dc.b	"_awu.c",0
 734                     	xref.b	c_lreg
 735                     	xref.b	c_x
 755                     	xref	c_imul
 756                     	xref	c_ludv
 757                     	xref	c_lcmp
 758                     	xref	c_ltor
 759                     	end
