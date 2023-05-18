   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 67 void I2C_DeInit(void)
  49                     ; 68 {
  51                     .text:	section	.text,new
  52  0000               _I2C_DeInit:
  56                     ; 69   I2C->CR1 = I2C_CR1_RESET_VALUE;
  58  0000 725f5210      	clr	21008
  59                     ; 70   I2C->CR2 = I2C_CR2_RESET_VALUE;
  61  0004 725f5211      	clr	21009
  62                     ; 71   I2C->FREQR = I2C_FREQR_RESET_VALUE;
  64  0008 725f5212      	clr	21010
  65                     ; 72   I2C->OARL = I2C_OARL_RESET_VALUE;
  67  000c 725f5213      	clr	21011
  68                     ; 73   I2C->OARH = I2C_OARH_RESET_VALUE;
  70  0010 725f5214      	clr	21012
  71                     ; 74   I2C->ITR = I2C_ITR_RESET_VALUE;
  73  0014 725f521a      	clr	21018
  74                     ; 75   I2C->CCRL = I2C_CCRL_RESET_VALUE;
  76  0018 725f521b      	clr	21019
  77                     ; 76   I2C->CCRH = I2C_CCRH_RESET_VALUE;
  79  001c 725f521c      	clr	21020
  80                     ; 77   I2C->TRISER = I2C_TRISER_RESET_VALUE;
  82  0020 3502521d      	mov	21021,#2
  83                     ; 78 }
  86  0024 81            	ret	
 266                     .const:	section	.text
 267  0000               L65:
 268  0000 00061a81      	dc.l	400001
 269  0004               L46:
 270  0004 000186a1      	dc.l	100001
 271  0008               L66:
 272  0008 000f4240      	dc.l	1000000
 273                     ; 96 void I2C_Init(uint32_t OutputClockFrequencyHz, uint16_t OwnAddress, 
 273                     ; 97               I2C_DutyCycle_TypeDef I2C_DutyCycle, I2C_Ack_TypeDef Ack, 
 273                     ; 98               I2C_AddMode_TypeDef AddMode, uint8_t InputClockFrequencyMHz )
 273                     ; 99 {
 274                     .text:	section	.text,new
 275  0000               _I2C_Init:
 277  0000 5209          	subw	sp,#9
 278       00000009      OFST:	set	9
 281                     ; 100   uint16_t result = 0x0004;
 283                     ; 101   uint16_t tmpval = 0;
 285                     ; 102   uint8_t tmpccrh = 0;
 287  0002 0f07          	clr	(OFST-2,sp)
 289                     ; 105   assert_param(IS_I2C_ACK_OK(Ack));
 291  0004 7b13          	ld	a,(OFST+10,sp)
 292  0006 270e          	jreq	L41
 293  0008 a101          	cp	a,#1
 294  000a 270a          	jreq	L41
 295  000c a102          	cp	a,#2
 296  000e 2706          	jreq	L41
 297  0010 ae0069        	ldw	x,#105
 298  0013 cd0158        	call	LC001
 299  0016               L41:
 300                     ; 106   assert_param(IS_I2C_ADDMODE_OK(AddMode));
 302  0016 7b14          	ld	a,(OFST+11,sp)
 303  0018 270a          	jreq	L42
 304  001a a180          	cp	a,#128
 305  001c 2706          	jreq	L42
 306  001e ae006a        	ldw	x,#106
 307  0021 cd0158        	call	LC001
 308  0024               L42:
 309                     ; 107   assert_param(IS_I2C_OWN_ADDRESS_OK(OwnAddress));
 311  0024 1e10          	ldw	x,(OFST+7,sp)
 312  0026 a30400        	cpw	x,#1024
 313  0029 2506          	jrult	L23
 314  002b ae006b        	ldw	x,#107
 315  002e cd0158        	call	LC001
 316  0031               L23:
 317                     ; 108   assert_param(IS_I2C_DUTYCYCLE_OK(I2C_DutyCycle));  
 319  0031 7b12          	ld	a,(OFST+9,sp)
 320  0033 270a          	jreq	L24
 321  0035 a140          	cp	a,#64
 322  0037 2706          	jreq	L24
 323  0039 ae006c        	ldw	x,#108
 324  003c cd0158        	call	LC001
 325  003f               L24:
 326                     ; 109   assert_param(IS_I2C_INPUT_CLOCK_FREQ_OK(InputClockFrequencyMHz));
 328  003f 7b15          	ld	a,(OFST+12,sp)
 329  0041 2704          	jreq	L64
 330  0043 a111          	cp	a,#17
 331  0045 2506          	jrult	L05
 332  0047               L64:
 333  0047 ae006d        	ldw	x,#109
 334  004a cd0158        	call	LC001
 335  004d               L05:
 336                     ; 110   assert_param(IS_I2C_OUTPUT_CLOCK_FREQ_OK(OutputClockFrequencyHz));
 338  004d 96            	ldw	x,sp
 339  004e 1c000c        	addw	x,#OFST+3
 340  0051 cd0000        	call	c_lzmp
 342  0054 270f          	jreq	L45
 343  0056 96            	ldw	x,sp
 344  0057 1c000c        	addw	x,#OFST+3
 345  005a cd0000        	call	c_ltor
 347  005d ae0000        	ldw	x,#L65
 348  0060 cd0000        	call	c_lcmp
 350  0063 2506          	jrult	L06
 351  0065               L45:
 352  0065 ae006e        	ldw	x,#110
 353  0068 cd0158        	call	LC001
 354  006b               L06:
 355                     ; 115   I2C->FREQR &= (uint8_t)(~I2C_FREQR_FREQ);
 357  006b c65212        	ld	a,21010
 358  006e a4c0          	and	a,#192
 359  0070 c75212        	ld	21010,a
 360                     ; 117   I2C->FREQR |= InputClockFrequencyMHz;
 362  0073 c65212        	ld	a,21010
 363  0076 1a15          	or	a,(OFST+12,sp)
 364  0078 c75212        	ld	21010,a
 365                     ; 121   I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);
 367  007b 72115210      	bres	21008,#0
 368                     ; 124   I2C->CCRH &= (uint8_t)(~(I2C_CCRH_FS | I2C_CCRH_DUTY | I2C_CCRH_CCR));
 370  007f c6521c        	ld	a,21020
 371  0082 a430          	and	a,#48
 372  0084 c7521c        	ld	21020,a
 373                     ; 125   I2C->CCRL &= (uint8_t)(~I2C_CCRL_CCR);
 375  0087 725f521b      	clr	21019
 376                     ; 128   if (OutputClockFrequencyHz > I2C_MAX_STANDARD_FREQ) /* FAST MODE */
 378  008b 96            	ldw	x,sp
 379  008c 1c000c        	addw	x,#OFST+3
 380  008f cd0000        	call	c_ltor
 382  0092 ae0004        	ldw	x,#L46
 383  0095 cd0000        	call	c_lcmp
 385  0098 2560          	jrult	L331
 386                     ; 131     tmpccrh = I2C_CCRH_FS;
 388  009a a680          	ld	a,#128
 389  009c 6b07          	ld	(OFST-2,sp),a
 391                     ; 133     if (I2C_DutyCycle == I2C_DUTYCYCLE_2)
 393  009e 96            	ldw	x,sp
 394  009f 0d12          	tnz	(OFST+9,sp)
 395  00a1 261d          	jrne	L531
 396                     ; 136       result = (uint16_t) ((InputClockFrequencyMHz * 1000000) / (OutputClockFrequencyHz * 3));
 398  00a3 1c000c        	addw	x,#OFST+3
 399  00a6 cd0000        	call	c_ltor
 401  00a9 a603          	ld	a,#3
 402  00ab cd0000        	call	c_smul
 404  00ae 96            	ldw	x,sp
 405  00af 5c            	incw	x
 406  00b0 cd0000        	call	c_rtol
 409  00b3 7b15          	ld	a,(OFST+12,sp)
 410  00b5 cd0164        	call	LC002
 412  00b8 96            	ldw	x,sp
 413  00b9 cd0172        	call	LC003
 414  00bc 1f08          	ldw	(OFST-1,sp),x
 417  00be 2021          	jra	L731
 418  00c0               L531:
 419                     ; 141       result = (uint16_t) ((InputClockFrequencyMHz * 1000000) / (OutputClockFrequencyHz * 25));
 421  00c0 1c000c        	addw	x,#OFST+3
 422  00c3 cd0000        	call	c_ltor
 424  00c6 a619          	ld	a,#25
 425  00c8 cd0000        	call	c_smul
 427  00cb 96            	ldw	x,sp
 428  00cc 5c            	incw	x
 429  00cd cd0000        	call	c_rtol
 432  00d0 7b15          	ld	a,(OFST+12,sp)
 433  00d2 cd0164        	call	LC002
 435  00d5 96            	ldw	x,sp
 436  00d6 cd0172        	call	LC003
 437  00d9 1f08          	ldw	(OFST-1,sp),x
 439                     ; 143       tmpccrh |= I2C_CCRH_DUTY;
 441  00db 7b07          	ld	a,(OFST-2,sp)
 442  00dd aa40          	or	a,#64
 443  00df 6b07          	ld	(OFST-2,sp),a
 445  00e1               L731:
 446                     ; 147     if (result < (uint16_t)0x01)
 448  00e1 1e08          	ldw	x,(OFST-1,sp)
 449  00e3 2603          	jrne	L141
 450                     ; 150       result = (uint16_t)0x0001;
 452  00e5 5c            	incw	x
 453  00e6 1f08          	ldw	(OFST-1,sp),x
 455  00e8               L141:
 456                     ; 156     tmpval = ((InputClockFrequencyMHz * 3) / 10) + 1;
 458  00e8 7b15          	ld	a,(OFST+12,sp)
 459  00ea 97            	ld	xl,a
 460  00eb a603          	ld	a,#3
 461  00ed 42            	mul	x,a
 462  00ee a60a          	ld	a,#10
 463  00f0 cd0000        	call	c_sdivx
 465  00f3 5c            	incw	x
 466  00f4 1f05          	ldw	(OFST-4,sp),x
 468                     ; 157     I2C->TRISER = (uint8_t)tmpval;
 470  00f6 7b06          	ld	a,(OFST-3,sp)
 472  00f8 2028          	jra	L341
 473  00fa               L331:
 474                     ; 164     result = (uint16_t)((InputClockFrequencyMHz * 1000000) / (OutputClockFrequencyHz << (uint8_t)1));
 476  00fa 96            	ldw	x,sp
 477  00fb 1c000c        	addw	x,#OFST+3
 478  00fe cd0000        	call	c_ltor
 480  0101 3803          	sll	c_lreg+3
 481  0103 3902          	rlc	c_lreg+2
 482  0105 3901          	rlc	c_lreg+1
 483  0107 96            	ldw	x,sp
 484  0108 3900          	rlc	c_lreg
 485  010a 5c            	incw	x
 486  010b cd0000        	call	c_rtol
 489  010e 7b15          	ld	a,(OFST+12,sp)
 490  0110 ad52          	call	LC002
 492  0112 96            	ldw	x,sp
 493  0113 ad5d          	call	LC003
 495                     ; 167     if (result < (uint16_t)0x0004)
 497  0115 a30004        	cpw	x,#4
 498  0118 2403          	jruge	L541
 499                     ; 170       result = (uint16_t)0x0004;
 501  011a ae0004        	ldw	x,#4
 503  011d               L541:
 504  011d 1f08          	ldw	(OFST-1,sp),x
 505                     ; 176     I2C->TRISER = (uint8_t)(InputClockFrequencyMHz + (uint8_t)1);
 507  011f 7b15          	ld	a,(OFST+12,sp)
 508  0121 4c            	inc	a
 509  0122               L341:
 510  0122 c7521d        	ld	21021,a
 511                     ; 181   I2C->CCRL = (uint8_t)result;
 513  0125 7b09          	ld	a,(OFST+0,sp)
 514  0127 c7521b        	ld	21019,a
 515                     ; 182   I2C->CCRH = (uint8_t)((uint8_t)((uint8_t)(result >> 8) & I2C_CCRH_CCR) | tmpccrh);
 517  012a 7b08          	ld	a,(OFST-1,sp)
 518  012c a40f          	and	a,#15
 519  012e 1a07          	or	a,(OFST-2,sp)
 520  0130 c7521c        	ld	21020,a
 521                     ; 185   I2C->CR1 |= I2C_CR1_PE;
 523  0133 72105210      	bset	21008,#0
 524                     ; 188   I2C_AcknowledgeConfig(Ack);
 526  0137 7b13          	ld	a,(OFST+10,sp)
 527  0139 cd0000        	call	_I2C_AcknowledgeConfig
 529                     ; 191   I2C->OARL = (uint8_t)(OwnAddress);
 531  013c 7b11          	ld	a,(OFST+8,sp)
 532  013e c75213        	ld	21011,a
 533                     ; 192   I2C->OARH = (uint8_t)((uint8_t)(AddMode | I2C_OARH_ADDCONF) |
 533                     ; 193                    (uint8_t)((OwnAddress & (uint16_t)0x0300) >> (uint8_t)7));
 535  0141 1e10          	ldw	x,(OFST+7,sp)
 536  0143 4f            	clr	a
 537  0144 01            	rrwa	x,a
 538  0145 48            	sll	a
 539  0146 01            	rrwa	x,a
 540  0147 49            	rlc	a
 541  0148 a406          	and	a,#6
 542  014a 6b04          	ld	(OFST-5,sp),a
 544  014c 7b14          	ld	a,(OFST+11,sp)
 545  014e aa40          	or	a,#64
 546  0150 1a04          	or	a,(OFST-5,sp)
 547  0152 c75214        	ld	21012,a
 548                     ; 194 }
 551  0155 5b09          	addw	sp,#9
 552  0157 81            	ret	
 553  0158               LC001:
 554  0158 89            	pushw	x
 555  0159 5f            	clrw	x
 556  015a 89            	pushw	x
 557  015b ae000c        	ldw	x,#L131
 558  015e cd0000        	call	_assert_failed
 560  0161 5b04          	addw	sp,#4
 561  0163 81            	ret	
 562  0164               LC002:
 563  0164 b703          	ld	c_lreg+3,a
 564  0166 3f02          	clr	c_lreg+2
 565  0168 3f01          	clr	c_lreg+1
 566  016a 3f00          	clr	c_lreg
 567  016c ae0008        	ldw	x,#L66
 568  016f cc0000        	jp	c_lmul
 569  0172               LC003:
 570  0172 5c            	incw	x
 571  0173 cd0000        	call	c_ludv
 573  0176 be02          	ldw	x,c_lreg+2
 574  0178 81            	ret	
 630                     ; 202 void I2C_Cmd(FunctionalState NewState)
 630                     ; 203 {
 631                     .text:	section	.text,new
 632  0000               _I2C_Cmd:
 634  0000 88            	push	a
 635       00000000      OFST:	set	0
 638                     ; 205   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 640  0001 4d            	tnz	a
 641  0002 2711          	jreq	L001
 642  0004 4a            	dec	a
 643  0005 270e          	jreq	L001
 644  0007 ae00cd        	ldw	x,#205
 645  000a 89            	pushw	x
 646  000b 5f            	clrw	x
 647  000c 89            	pushw	x
 648  000d ae000c        	ldw	x,#L131
 649  0010 cd0000        	call	_assert_failed
 651  0013 5b04          	addw	sp,#4
 652  0015               L001:
 653                     ; 207   if (NewState != DISABLE)
 655  0015 7b01          	ld	a,(OFST+1,sp)
 656  0017 2706          	jreq	L571
 657                     ; 210     I2C->CR1 |= I2C_CR1_PE;
 659  0019 72105210      	bset	21008,#0
 661  001d 2004          	jra	L771
 662  001f               L571:
 663                     ; 215     I2C->CR1 &= (uint8_t)(~I2C_CR1_PE);
 665  001f 72115210      	bres	21008,#0
 666  0023               L771:
 667                     ; 217 }
 670  0023 84            	pop	a
 671  0024 81            	ret	
 707                     ; 225 void I2C_GeneralCallCmd(FunctionalState NewState)
 707                     ; 226 {
 708                     .text:	section	.text,new
 709  0000               _I2C_GeneralCallCmd:
 711  0000 88            	push	a
 712       00000000      OFST:	set	0
 715                     ; 228   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 717  0001 4d            	tnz	a
 718  0002 2711          	jreq	L211
 719  0004 4a            	dec	a
 720  0005 270e          	jreq	L211
 721  0007 ae00e4        	ldw	x,#228
 722  000a 89            	pushw	x
 723  000b 5f            	clrw	x
 724  000c 89            	pushw	x
 725  000d ae000c        	ldw	x,#L131
 726  0010 cd0000        	call	_assert_failed
 728  0013 5b04          	addw	sp,#4
 729  0015               L211:
 730                     ; 230   if (NewState != DISABLE)
 732  0015 7b01          	ld	a,(OFST+1,sp)
 733  0017 2706          	jreq	L712
 734                     ; 233     I2C->CR1 |= I2C_CR1_ENGC;
 736  0019 721c5210      	bset	21008,#6
 738  001d 2004          	jra	L122
 739  001f               L712:
 740                     ; 238     I2C->CR1 &= (uint8_t)(~I2C_CR1_ENGC);
 742  001f 721d5210      	bres	21008,#6
 743  0023               L122:
 744                     ; 240 }
 747  0023 84            	pop	a
 748  0024 81            	ret	
 784                     ; 250 void I2C_GenerateSTART(FunctionalState NewState)
 784                     ; 251 {
 785                     .text:	section	.text,new
 786  0000               _I2C_GenerateSTART:
 788  0000 88            	push	a
 789       00000000      OFST:	set	0
 792                     ; 253   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 794  0001 4d            	tnz	a
 795  0002 2711          	jreq	L421
 796  0004 4a            	dec	a
 797  0005 270e          	jreq	L421
 798  0007 ae00fd        	ldw	x,#253
 799  000a 89            	pushw	x
 800  000b 5f            	clrw	x
 801  000c 89            	pushw	x
 802  000d ae000c        	ldw	x,#L131
 803  0010 cd0000        	call	_assert_failed
 805  0013 5b04          	addw	sp,#4
 806  0015               L421:
 807                     ; 255   if (NewState != DISABLE)
 809  0015 7b01          	ld	a,(OFST+1,sp)
 810  0017 2706          	jreq	L142
 811                     ; 258     I2C->CR2 |= I2C_CR2_START;
 813  0019 72105211      	bset	21009,#0
 815  001d 2004          	jra	L342
 816  001f               L142:
 817                     ; 263     I2C->CR2 &= (uint8_t)(~I2C_CR2_START);
 819  001f 72115211      	bres	21009,#0
 820  0023               L342:
 821                     ; 265 }
 824  0023 84            	pop	a
 825  0024 81            	ret	
 861                     ; 273 void I2C_GenerateSTOP(FunctionalState NewState)
 861                     ; 274 {
 862                     .text:	section	.text,new
 863  0000               _I2C_GenerateSTOP:
 865  0000 88            	push	a
 866       00000000      OFST:	set	0
 869                     ; 276   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 871  0001 4d            	tnz	a
 872  0002 2711          	jreq	L631
 873  0004 4a            	dec	a
 874  0005 270e          	jreq	L631
 875  0007 ae0114        	ldw	x,#276
 876  000a 89            	pushw	x
 877  000b 5f            	clrw	x
 878  000c 89            	pushw	x
 879  000d ae000c        	ldw	x,#L131
 880  0010 cd0000        	call	_assert_failed
 882  0013 5b04          	addw	sp,#4
 883  0015               L631:
 884                     ; 278   if (NewState != DISABLE)
 886  0015 7b01          	ld	a,(OFST+1,sp)
 887  0017 2706          	jreq	L362
 888                     ; 281     I2C->CR2 |= I2C_CR2_STOP;
 890  0019 72125211      	bset	21009,#1
 892  001d 2004          	jra	L562
 893  001f               L362:
 894                     ; 286     I2C->CR2 &= (uint8_t)(~I2C_CR2_STOP);
 896  001f 72135211      	bres	21009,#1
 897  0023               L562:
 898                     ; 288 }
 901  0023 84            	pop	a
 902  0024 81            	ret	
 939                     ; 296 void I2C_SoftwareResetCmd(FunctionalState NewState)
 939                     ; 297 {
 940                     .text:	section	.text,new
 941  0000               _I2C_SoftwareResetCmd:
 943  0000 88            	push	a
 944       00000000      OFST:	set	0
 947                     ; 299   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 949  0001 4d            	tnz	a
 950  0002 2711          	jreq	L051
 951  0004 4a            	dec	a
 952  0005 270e          	jreq	L051
 953  0007 ae012b        	ldw	x,#299
 954  000a 89            	pushw	x
 955  000b 5f            	clrw	x
 956  000c 89            	pushw	x
 957  000d ae000c        	ldw	x,#L131
 958  0010 cd0000        	call	_assert_failed
 960  0013 5b04          	addw	sp,#4
 961  0015               L051:
 962                     ; 301   if (NewState != DISABLE)
 964  0015 7b01          	ld	a,(OFST+1,sp)
 965  0017 2706          	jreq	L503
 966                     ; 304     I2C->CR2 |= I2C_CR2_SWRST;
 968  0019 721e5211      	bset	21009,#7
 970  001d 2004          	jra	L703
 971  001f               L503:
 972                     ; 309     I2C->CR2 &= (uint8_t)(~I2C_CR2_SWRST);
 974  001f 721f5211      	bres	21009,#7
 975  0023               L703:
 976                     ; 311 }
 979  0023 84            	pop	a
 980  0024 81            	ret	
1017                     ; 320 void I2C_StretchClockCmd(FunctionalState NewState)
1017                     ; 321 {
1018                     .text:	section	.text,new
1019  0000               _I2C_StretchClockCmd:
1021  0000 88            	push	a
1022       00000000      OFST:	set	0
1025                     ; 323   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1027  0001 4d            	tnz	a
1028  0002 2711          	jreq	L261
1029  0004 4a            	dec	a
1030  0005 270e          	jreq	L261
1031  0007 ae0143        	ldw	x,#323
1032  000a 89            	pushw	x
1033  000b 5f            	clrw	x
1034  000c 89            	pushw	x
1035  000d ae000c        	ldw	x,#L131
1036  0010 cd0000        	call	_assert_failed
1038  0013 5b04          	addw	sp,#4
1039  0015               L261:
1040                     ; 325   if (NewState != DISABLE)
1042  0015 7b01          	ld	a,(OFST+1,sp)
1043  0017 2706          	jreq	L723
1044                     ; 328     I2C->CR1 &= (uint8_t)(~I2C_CR1_NOSTRETCH);
1046  0019 721f5210      	bres	21008,#7
1048  001d 2004          	jra	L133
1049  001f               L723:
1050                     ; 334     I2C->CR1 |= I2C_CR1_NOSTRETCH;
1052  001f 721e5210      	bset	21008,#7
1053  0023               L133:
1054                     ; 336 }
1057  0023 84            	pop	a
1058  0024 81            	ret	
1095                     ; 345 void I2C_AcknowledgeConfig(I2C_Ack_TypeDef Ack)
1095                     ; 346 {
1096                     .text:	section	.text,new
1097  0000               _I2C_AcknowledgeConfig:
1099  0000 88            	push	a
1100       00000000      OFST:	set	0
1103                     ; 348   assert_param(IS_I2C_ACK_OK(Ack));
1105  0001 4d            	tnz	a
1106  0002 2716          	jreq	L471
1107  0004 a101          	cp	a,#1
1108  0006 2712          	jreq	L471
1109  0008 a102          	cp	a,#2
1110  000a 270e          	jreq	L471
1111  000c ae015c        	ldw	x,#348
1112  000f 89            	pushw	x
1113  0010 5f            	clrw	x
1114  0011 89            	pushw	x
1115  0012 ae000c        	ldw	x,#L131
1116  0015 cd0000        	call	_assert_failed
1118  0018 5b04          	addw	sp,#4
1119  001a               L471:
1120                     ; 350   if (Ack == I2C_ACK_NONE)
1122  001a 7b01          	ld	a,(OFST+1,sp)
1123  001c 2606          	jrne	L153
1124                     ; 353     I2C->CR2 &= (uint8_t)(~I2C_CR2_ACK);
1126  001e 72155211      	bres	21009,#2
1128  0022 2011          	jra	L353
1129  0024               L153:
1130                     ; 358     I2C->CR2 |= I2C_CR2_ACK;
1132  0024 72145211      	bset	21009,#2
1133                     ; 360     if (Ack == I2C_ACK_CURR)
1135  0028 4a            	dec	a
1136  0029 2606          	jrne	L553
1137                     ; 363       I2C->CR2 &= (uint8_t)(~I2C_CR2_POS);
1139  002b 72175211      	bres	21009,#3
1141  002f 2004          	jra	L353
1142  0031               L553:
1143                     ; 368       I2C->CR2 |= I2C_CR2_POS;
1145  0031 72165211      	bset	21009,#3
1146  0035               L353:
1147                     ; 371 }
1150  0035 84            	pop	a
1151  0036 81            	ret	
1224                     ; 381 void I2C_ITConfig(I2C_IT_TypeDef I2C_IT, FunctionalState NewState)
1224                     ; 382 {
1225                     .text:	section	.text,new
1226  0000               _I2C_ITConfig:
1228  0000 89            	pushw	x
1229       00000000      OFST:	set	0
1232                     ; 384   assert_param(IS_I2C_INTERRUPT_OK(I2C_IT));
1234  0001 9e            	ld	a,xh
1235  0002 4a            	dec	a
1236  0003 2723          	jreq	L602
1237  0005 9e            	ld	a,xh
1238  0006 a102          	cp	a,#2
1239  0008 271e          	jreq	L602
1240  000a 9e            	ld	a,xh
1241  000b a104          	cp	a,#4
1242  000d 2719          	jreq	L602
1243  000f 9e            	ld	a,xh
1244  0010 a103          	cp	a,#3
1245  0012 2714          	jreq	L602
1246  0014 9e            	ld	a,xh
1247  0015 a105          	cp	a,#5
1248  0017 270f          	jreq	L602
1249  0019 9e            	ld	a,xh
1250  001a a106          	cp	a,#6
1251  001c 270a          	jreq	L602
1252  001e 9e            	ld	a,xh
1253  001f a107          	cp	a,#7
1254  0021 2705          	jreq	L602
1255  0023 ae0180        	ldw	x,#384
1256  0026 ad22          	call	LC004
1257  0028               L602:
1258                     ; 385   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1260  0028 7b02          	ld	a,(OFST+2,sp)
1261  002a 2708          	jreq	L612
1262  002c 4a            	dec	a
1263  002d 2705          	jreq	L612
1264  002f ae0181        	ldw	x,#385
1265  0032 ad16          	call	LC004
1266  0034               L612:
1267                     ; 387   if (NewState != DISABLE)
1269  0034 7b02          	ld	a,(OFST+2,sp)
1270  0036 2707          	jreq	L514
1271                     ; 390     I2C->ITR |= (uint8_t)I2C_IT;
1273  0038 c6521a        	ld	a,21018
1274  003b 1a01          	or	a,(OFST+1,sp)
1276  003d 2006          	jra	L714
1277  003f               L514:
1278                     ; 395     I2C->ITR &= (uint8_t)(~(uint8_t)I2C_IT);
1280  003f 7b01          	ld	a,(OFST+1,sp)
1281  0041 43            	cpl	a
1282  0042 c4521a        	and	a,21018
1283  0045               L714:
1284  0045 c7521a        	ld	21018,a
1285                     ; 397 }
1288  0048 85            	popw	x
1289  0049 81            	ret	
1290  004a               LC004:
1291  004a 89            	pushw	x
1292  004b 5f            	clrw	x
1293  004c 89            	pushw	x
1294  004d ae000c        	ldw	x,#L131
1295  0050 cd0000        	call	_assert_failed
1297  0053 5b04          	addw	sp,#4
1298  0055 81            	ret	
1335                     ; 405 void I2C_FastModeDutyCycleConfig(I2C_DutyCycle_TypeDef I2C_DutyCycle)
1335                     ; 406 {
1336                     .text:	section	.text,new
1337  0000               _I2C_FastModeDutyCycleConfig:
1339  0000 88            	push	a
1340       00000000      OFST:	set	0
1343                     ; 408   assert_param(IS_I2C_DUTYCYCLE_OK(I2C_DutyCycle));
1345  0001 4d            	tnz	a
1346  0002 2712          	jreq	L032
1347  0004 a140          	cp	a,#64
1348  0006 270e          	jreq	L032
1349  0008 ae0198        	ldw	x,#408
1350  000b 89            	pushw	x
1351  000c 5f            	clrw	x
1352  000d 89            	pushw	x
1353  000e ae000c        	ldw	x,#L131
1354  0011 cd0000        	call	_assert_failed
1356  0014 5b04          	addw	sp,#4
1357  0016               L032:
1358                     ; 410   if (I2C_DutyCycle == I2C_DUTYCYCLE_16_9)
1360  0016 7b01          	ld	a,(OFST+1,sp)
1361  0018 a140          	cp	a,#64
1362  001a 2606          	jrne	L734
1363                     ; 413     I2C->CCRH |= I2C_CCRH_DUTY;
1365  001c 721c521c      	bset	21020,#6
1367  0020 2004          	jra	L144
1368  0022               L734:
1369                     ; 418     I2C->CCRH &= (uint8_t)(~I2C_CCRH_DUTY);
1371  0022 721d521c      	bres	21020,#6
1372  0026               L144:
1373                     ; 420 }
1376  0026 84            	pop	a
1377  0027 81            	ret	
1400                     ; 427 uint8_t I2C_ReceiveData(void)
1400                     ; 428 {
1401                     .text:	section	.text,new
1402  0000               _I2C_ReceiveData:
1406                     ; 430   return ((uint8_t)I2C->DR);
1408  0000 c65216        	ld	a,21014
1411  0003 81            	ret	
1477                     ; 440 void I2C_Send7bitAddress(uint8_t Address, I2C_Direction_TypeDef Direction)
1477                     ; 441 {
1478                     .text:	section	.text,new
1479  0000               _I2C_Send7bitAddress:
1481  0000 89            	pushw	x
1482       00000000      OFST:	set	0
1485                     ; 443   assert_param(IS_I2C_ADDRESS_OK(Address));
1487  0001 9e            	ld	a,xh
1488  0002 a501          	bcp	a,#1
1489  0004 2705          	jreq	L242
1490  0006 ae01bb        	ldw	x,#443
1491  0009 ad19          	call	LC005
1492  000b               L242:
1493                     ; 444   assert_param(IS_I2C_DIRECTION_OK(Direction));
1495  000b 7b02          	ld	a,(OFST+2,sp)
1496  000d 2708          	jreq	L252
1497  000f 4a            	dec	a
1498  0010 2705          	jreq	L252
1499  0012 ae01bc        	ldw	x,#444
1500  0015 ad0d          	call	LC005
1501  0017               L252:
1502                     ; 447   Address &= (uint8_t)0xFE;
1504  0017 7b01          	ld	a,(OFST+1,sp)
1505  0019 a4fe          	and	a,#254
1506  001b 6b01          	ld	(OFST+1,sp),a
1507                     ; 450   I2C->DR = (uint8_t)(Address | (uint8_t)Direction);
1509  001d 1a02          	or	a,(OFST+2,sp)
1510  001f c75216        	ld	21014,a
1511                     ; 451 }
1514  0022 85            	popw	x
1515  0023 81            	ret	
1516  0024               LC005:
1517  0024 89            	pushw	x
1518  0025 5f            	clrw	x
1519  0026 89            	pushw	x
1520  0027 ae000c        	ldw	x,#L131
1521  002a cd0000        	call	_assert_failed
1523  002d 5b04          	addw	sp,#4
1524  002f 81            	ret	
1558                     ; 458 void I2C_SendData(uint8_t Data)
1558                     ; 459 {
1559                     .text:	section	.text,new
1560  0000               _I2C_SendData:
1564                     ; 461   I2C->DR = Data;
1566  0000 c75216        	ld	21014,a
1567                     ; 462 }
1570  0003 81            	ret	
1795                     ; 578 ErrorStatus I2C_CheckEvent(I2C_Event_TypeDef I2C_Event)
1795                     ; 579 {
1796                     .text:	section	.text,new
1797  0000               _I2C_CheckEvent:
1799  0000 89            	pushw	x
1800  0001 5206          	subw	sp,#6
1801       00000006      OFST:	set	6
1804                     ; 580   __IO uint16_t lastevent = 0x00;
1806  0003 5f            	clrw	x
1807  0004 1f04          	ldw	(OFST-2,sp),x
1809                     ; 581   uint8_t flag1 = 0x00 ;
1811                     ; 582   uint8_t flag2 = 0x00;
1813                     ; 583   ErrorStatus status = ERROR;
1815                     ; 586   assert_param(IS_I2C_EVENT_OK(I2C_Event));
1817  0006 1e07          	ldw	x,(OFST+1,sp)
1818  0008 a30682        	cpw	x,#1666
1819  000b 275b          	jreq	L662
1820  000d a30202        	cpw	x,#514
1821  0010 2756          	jreq	L662
1822  0012 a31200        	cpw	x,#4608
1823  0015 2751          	jreq	L662
1824  0017 a30240        	cpw	x,#576
1825  001a 274c          	jreq	L662
1826  001c a30350        	cpw	x,#848
1827  001f 2747          	jreq	L662
1828  0021 a30684        	cpw	x,#1668
1829  0024 2742          	jreq	L662
1830  0026 a30794        	cpw	x,#1940
1831  0029 273d          	jreq	L662
1832  002b a30004        	cpw	x,#4
1833  002e 2738          	jreq	L662
1834  0030 a30010        	cpw	x,#16
1835  0033 2733          	jreq	L662
1836  0035 a30301        	cpw	x,#769
1837  0038 272e          	jreq	L662
1838  003a a30782        	cpw	x,#1922
1839  003d 2729          	jreq	L662
1840  003f a30302        	cpw	x,#770
1841  0042 2724          	jreq	L662
1842  0044 a30340        	cpw	x,#832
1843  0047 271f          	jreq	L662
1844  0049 a30784        	cpw	x,#1924
1845  004c 271a          	jreq	L662
1846  004e a30780        	cpw	x,#1920
1847  0051 2715          	jreq	L662
1848  0053 a30308        	cpw	x,#776
1849  0056 2710          	jreq	L662
1850  0058 ae024a        	ldw	x,#586
1851  005b 89            	pushw	x
1852  005c 5f            	clrw	x
1853  005d 89            	pushw	x
1854  005e ae000c        	ldw	x,#L131
1855  0061 cd0000        	call	_assert_failed
1857  0064 5b04          	addw	sp,#4
1858  0066 1e07          	ldw	x,(OFST+1,sp)
1859  0068               L662:
1860                     ; 588   if (I2C_Event == I2C_EVENT_SLAVE_ACK_FAILURE)
1862  0068 a30004        	cpw	x,#4
1863  006b 2609          	jrne	L336
1864                     ; 590     lastevent = I2C->SR2 & I2C_SR2_AF;
1866  006d c65218        	ld	a,21016
1867  0070 a404          	and	a,#4
1868  0072 5f            	clrw	x
1869  0073 97            	ld	xl,a
1871  0074 201a          	jra	L536
1872  0076               L336:
1873                     ; 594     flag1 = I2C->SR1;
1875  0076 c65217        	ld	a,21015
1876  0079 6b03          	ld	(OFST-3,sp),a
1878                     ; 595     flag2 = I2C->SR3;
1880  007b c65219        	ld	a,21017
1881  007e 6b06          	ld	(OFST+0,sp),a
1883                     ; 596     lastevent = ((uint16_t)((uint16_t)flag2 << (uint16_t)8) | (uint16_t)flag1);
1885  0080 5f            	clrw	x
1886  0081 7b03          	ld	a,(OFST-3,sp)
1887  0083 97            	ld	xl,a
1888  0084 1f01          	ldw	(OFST-5,sp),x
1890  0086 5f            	clrw	x
1891  0087 7b06          	ld	a,(OFST+0,sp)
1892  0089 97            	ld	xl,a
1893  008a 7b02          	ld	a,(OFST-4,sp)
1894  008c 01            	rrwa	x,a
1895  008d 1a01          	or	a,(OFST-5,sp)
1896  008f 01            	rrwa	x,a
1897  0090               L536:
1898  0090 1f04          	ldw	(OFST-2,sp),x
1900                     ; 599   if (((uint16_t)lastevent & (uint16_t)I2C_Event) == (uint16_t)I2C_Event)
1902  0092 1e04          	ldw	x,(OFST-2,sp)
1903  0094 01            	rrwa	x,a
1904  0095 1408          	and	a,(OFST+2,sp)
1905  0097 01            	rrwa	x,a
1906  0098 1407          	and	a,(OFST+1,sp)
1907  009a 01            	rrwa	x,a
1908  009b 1307          	cpw	x,(OFST+1,sp)
1909  009d 2604          	jrne	L736
1910                     ; 602     status = SUCCESS;
1912  009f a601          	ld	a,#1
1915  00a1 2001          	jra	L146
1916  00a3               L736:
1917                     ; 607     status = ERROR;
1919  00a3 4f            	clr	a
1921  00a4               L146:
1922                     ; 611   return status;
1926  00a4 5b08          	addw	sp,#8
1927  00a6 81            	ret	
1980                     ; 628 I2C_Event_TypeDef I2C_GetLastEvent(void)
1980                     ; 629 {
1981                     .text:	section	.text,new
1982  0000               _I2C_GetLastEvent:
1984  0000 5206          	subw	sp,#6
1985       00000006      OFST:	set	6
1988                     ; 630   __IO uint16_t lastevent = 0;
1990  0002 5f            	clrw	x
1991  0003 1f05          	ldw	(OFST-1,sp),x
1993                     ; 631   uint16_t flag1 = 0;
1995                     ; 632   uint16_t flag2 = 0;
1997                     ; 634   if ((I2C->SR2 & I2C_SR2_AF) != 0x00)
1999  0005 7205521805    	btjf	21016,#2,L176
2000                     ; 636     lastevent = I2C_EVENT_SLAVE_ACK_FAILURE;
2002  000a ae0004        	ldw	x,#4
2004  000d 2013          	jra	L376
2005  000f               L176:
2006                     ; 641     flag1 = I2C->SR1;
2008  000f c65217        	ld	a,21015
2009  0012 97            	ld	xl,a
2010  0013 1f01          	ldw	(OFST-5,sp),x
2012                     ; 642     flag2 = I2C->SR3;
2014  0015 c65219        	ld	a,21017
2015  0018 5f            	clrw	x
2016  0019 97            	ld	xl,a
2017  001a 1f03          	ldw	(OFST-3,sp),x
2019                     ; 645     lastevent = ((uint16_t)((uint16_t)flag2 << 8) | (uint16_t)flag1);
2021  001c 7b02          	ld	a,(OFST-4,sp)
2022  001e 01            	rrwa	x,a
2023  001f 1a01          	or	a,(OFST-5,sp)
2024  0021 01            	rrwa	x,a
2025  0022               L376:
2026  0022 1f05          	ldw	(OFST-1,sp),x
2028                     ; 648   return (I2C_Event_TypeDef)lastevent;
2030  0024 1e05          	ldw	x,(OFST-1,sp)
2033  0026 5b06          	addw	sp,#6
2034  0028 81            	ret	
2250                     ; 679 FlagStatus I2C_GetFlagStatus(I2C_Flag_TypeDef I2C_Flag)
2250                     ; 680 {
2251                     .text:	section	.text,new
2252  0000               _I2C_GetFlagStatus:
2254  0000 89            	pushw	x
2255  0001 89            	pushw	x
2256       00000002      OFST:	set	2
2259                     ; 681   uint8_t tempreg = 0;
2261  0002 0f02          	clr	(OFST+0,sp)
2263                     ; 682   uint8_t regindex = 0;
2265                     ; 683   FlagStatus bitstatus = RESET;
2267                     ; 686   assert_param(IS_I2C_FLAG_OK(I2C_Flag));
2269  0004 a30180        	cpw	x,#384
2270  0007 2759          	jreq	L203
2271  0009 a30140        	cpw	x,#320
2272  000c 2754          	jreq	L203
2273  000e a30110        	cpw	x,#272
2274  0011 274f          	jreq	L203
2275  0013 a30108        	cpw	x,#264
2276  0016 274a          	jreq	L203
2277  0018 a30104        	cpw	x,#260
2278  001b 2745          	jreq	L203
2279  001d a30102        	cpw	x,#258
2280  0020 2740          	jreq	L203
2281  0022 a30101        	cpw	x,#257
2282  0025 273b          	jreq	L203
2283  0027 a30220        	cpw	x,#544
2284  002a 2736          	jreq	L203
2285  002c a30208        	cpw	x,#520
2286  002f 2731          	jreq	L203
2287  0031 a30204        	cpw	x,#516
2288  0034 272c          	jreq	L203
2289  0036 a30202        	cpw	x,#514
2290  0039 2727          	jreq	L203
2291  003b a30201        	cpw	x,#513
2292  003e 2722          	jreq	L203
2293  0040 a30310        	cpw	x,#784
2294  0043 271d          	jreq	L203
2295  0045 a30304        	cpw	x,#772
2296  0048 2718          	jreq	L203
2297  004a a30302        	cpw	x,#770
2298  004d 2713          	jreq	L203
2299  004f a30301        	cpw	x,#769
2300  0052 270e          	jreq	L203
2301  0054 ae02ae        	ldw	x,#686
2302  0057 89            	pushw	x
2303  0058 5f            	clrw	x
2304  0059 89            	pushw	x
2305  005a ae000c        	ldw	x,#L131
2306  005d cd0000        	call	_assert_failed
2308  0060 5b04          	addw	sp,#4
2309  0062               L203:
2310                     ; 689   regindex = (uint8_t)((uint16_t)I2C_Flag >> 8);
2312  0062 7b03          	ld	a,(OFST+1,sp)
2313  0064 6b01          	ld	(OFST-1,sp),a
2315                     ; 691   switch (regindex)
2318                     ; 708     default:
2318                     ; 709       break;
2319  0066 4a            	dec	a
2320  0067 2708          	jreq	L576
2321  0069 4a            	dec	a
2322  006a 270a          	jreq	L776
2323  006c 4a            	dec	a
2324  006d 270c          	jreq	L107
2325  006f 200f          	jra	L5101
2326  0071               L576:
2327                     ; 694     case 0x01:
2327                     ; 695       tempreg = (uint8_t)I2C->SR1;
2329  0071 c65217        	ld	a,21015
2330                     ; 696       break;
2332  0074 2008          	jp	LC006
2333  0076               L776:
2334                     ; 699     case 0x02:
2334                     ; 700       tempreg = (uint8_t)I2C->SR2;
2336  0076 c65218        	ld	a,21016
2337                     ; 701       break;
2339  0079 2003          	jp	LC006
2340  007b               L107:
2341                     ; 704     case 0x03:
2341                     ; 705       tempreg = (uint8_t)I2C->SR3;
2343  007b c65219        	ld	a,21017
2344  007e               LC006:
2345  007e 6b02          	ld	(OFST+0,sp),a
2347                     ; 706       break;
2349                     ; 708     default:
2349                     ; 709       break;
2351  0080               L5101:
2352                     ; 713   if ((tempreg & (uint8_t)I2C_Flag ) != 0)
2354  0080 7b04          	ld	a,(OFST+2,sp)
2355  0082 1502          	bcp	a,(OFST+0,sp)
2356  0084 2704          	jreq	L7101
2357                     ; 716     bitstatus = SET;
2359  0086 a601          	ld	a,#1
2362  0088 2001          	jra	L1201
2363  008a               L7101:
2364                     ; 721     bitstatus = RESET;
2366  008a 4f            	clr	a
2368  008b               L1201:
2369                     ; 724   return bitstatus;
2373  008b 5b04          	addw	sp,#4
2374  008d 81            	ret	
2419                     ; 759 void I2C_ClearFlag(I2C_Flag_TypeDef I2C_FLAG)
2419                     ; 760 {
2420                     .text:	section	.text,new
2421  0000               _I2C_ClearFlag:
2423  0000 89            	pushw	x
2424  0001 89            	pushw	x
2425       00000002      OFST:	set	2
2428                     ; 761   uint16_t flagpos = 0;
2430                     ; 763   assert_param(IS_I2C_CLEAR_FLAG_OK(I2C_FLAG));
2432  0002 01            	rrwa	x,a
2433  0003 9f            	ld	a,xl
2434  0004 a4fd          	and	a,#253
2435  0006 97            	ld	xl,a
2436  0007 4f            	clr	a
2437  0008 02            	rlwa	x,a
2438  0009 5d            	tnzw	x
2439  000a 2604          	jrne	L013
2440  000c 1e03          	ldw	x,(OFST+1,sp)
2441  000e 260e          	jrne	L213
2442  0010               L013:
2443  0010 ae02fb        	ldw	x,#763
2444  0013 89            	pushw	x
2445  0014 5f            	clrw	x
2446  0015 89            	pushw	x
2447  0016 ae000c        	ldw	x,#L131
2448  0019 cd0000        	call	_assert_failed
2450  001c 5b04          	addw	sp,#4
2451  001e               L213:
2452                     ; 766   flagpos = (uint16_t)I2C_FLAG & FLAG_Mask;
2454  001e 7b04          	ld	a,(OFST+2,sp)
2455  0020 5f            	clrw	x
2456  0021 02            	rlwa	x,a
2457  0022 1f01          	ldw	(OFST-1,sp),x
2459                     ; 768   I2C->SR2 = (uint8_t)((uint16_t)(~flagpos));
2461  0024 7b02          	ld	a,(OFST+0,sp)
2462  0026 43            	cpl	a
2463  0027 c75218        	ld	21016,a
2464                     ; 769 }
2467  002a 5b04          	addw	sp,#4
2468  002c 81            	ret	
2635                     ; 791 ITStatus I2C_GetITStatus(I2C_ITPendingBit_TypeDef I2C_ITPendingBit)
2635                     ; 792 {
2636                     .text:	section	.text,new
2637  0000               _I2C_GetITStatus:
2639  0000 89            	pushw	x
2640  0001 5204          	subw	sp,#4
2641       00000004      OFST:	set	4
2644                     ; 793   ITStatus bitstatus = RESET;
2646                     ; 794   __IO uint8_t enablestatus = 0;
2648  0003 0f03          	clr	(OFST-1,sp)
2650                     ; 795   uint16_t tempregister = 0;
2652                     ; 798     assert_param(IS_I2C_ITPENDINGBIT_OK(I2C_ITPendingBit));
2654  0005 a31680        	cpw	x,#5760
2655  0008 2745          	jreq	L423
2656  000a a31640        	cpw	x,#5696
2657  000d 2740          	jreq	L423
2658  000f a31210        	cpw	x,#4624
2659  0012 273b          	jreq	L423
2660  0014 a31208        	cpw	x,#4616
2661  0017 2736          	jreq	L423
2662  0019 a31204        	cpw	x,#4612
2663  001c 2731          	jreq	L423
2664  001e a31202        	cpw	x,#4610
2665  0021 272c          	jreq	L423
2666  0023 a31201        	cpw	x,#4609
2667  0026 2727          	jreq	L423
2668  0028 a32220        	cpw	x,#8736
2669  002b 2722          	jreq	L423
2670  002d a32108        	cpw	x,#8456
2671  0030 271d          	jreq	L423
2672  0032 a32104        	cpw	x,#8452
2673  0035 2718          	jreq	L423
2674  0037 a32102        	cpw	x,#8450
2675  003a 2713          	jreq	L423
2676  003c a32101        	cpw	x,#8449
2677  003f 270e          	jreq	L423
2678  0041 ae031e        	ldw	x,#798
2679  0044 89            	pushw	x
2680  0045 5f            	clrw	x
2681  0046 89            	pushw	x
2682  0047 ae000c        	ldw	x,#L131
2683  004a cd0000        	call	_assert_failed
2685  004d 5b04          	addw	sp,#4
2686  004f               L423:
2687                     ; 800   tempregister = (uint8_t)( ((uint16_t)((uint16_t)I2C_ITPendingBit & ITEN_Mask)) >> 8);
2689  004f 7b05          	ld	a,(OFST+1,sp)
2690  0051 a407          	and	a,#7
2691  0053 5f            	clrw	x
2692  0054 97            	ld	xl,a
2693  0055 1f01          	ldw	(OFST-3,sp),x
2695                     ; 803   enablestatus = (uint8_t)(I2C->ITR & ( uint8_t)tempregister);
2697  0057 c6521a        	ld	a,21018
2698  005a 1402          	and	a,(OFST-2,sp)
2699  005c 6b03          	ld	(OFST-1,sp),a
2701                     ; 805   if ((uint16_t)((uint16_t)I2C_ITPendingBit & REGISTER_Mask) == REGISTER_SR1_Index)
2703  005e 7b05          	ld	a,(OFST+1,sp)
2704  0060 a430          	and	a,#48
2705  0062 97            	ld	xl,a
2706  0063 4f            	clr	a
2707  0064 02            	rlwa	x,a
2708  0065 a30100        	cpw	x,#256
2709  0068 260d          	jrne	L3311
2710                     ; 808     if (((I2C->SR1 & (uint8_t)I2C_ITPendingBit) != RESET) && enablestatus)
2712  006a c65217        	ld	a,21015
2713  006d 1506          	bcp	a,(OFST+2,sp)
2714  006f 2715          	jreq	L3411
2716  0071 0d03          	tnz	(OFST-1,sp)
2717  0073 2711          	jreq	L3411
2718                     ; 811       bitstatus = SET;
2720  0075 200b          	jp	LC008
2721                     ; 816       bitstatus = RESET;
2722  0077               L3311:
2723                     ; 822     if (((I2C->SR2 & (uint8_t)I2C_ITPendingBit) != RESET) && enablestatus)
2725  0077 c65218        	ld	a,21016
2726  007a 1506          	bcp	a,(OFST+2,sp)
2727  007c 2708          	jreq	L3411
2729  007e 0d03          	tnz	(OFST-1,sp)
2730  0080 2704          	jreq	L3411
2731                     ; 825       bitstatus = SET;
2733  0082               LC008:
2735  0082 a601          	ld	a,#1
2738  0084 2001          	jra	L1411
2739  0086               L3411:
2740                     ; 830       bitstatus = RESET;
2743  0086 4f            	clr	a
2745  0087               L1411:
2746                     ; 834   return  bitstatus;
2750  0087 5b06          	addw	sp,#6
2751  0089 81            	ret	
2797                     ; 871 void I2C_ClearITPendingBit(I2C_ITPendingBit_TypeDef I2C_ITPendingBit)
2797                     ; 872 {
2798                     .text:	section	.text,new
2799  0000               _I2C_ClearITPendingBit:
2801  0000 89            	pushw	x
2802  0001 89            	pushw	x
2803       00000002      OFST:	set	2
2806                     ; 873   uint16_t flagpos = 0;
2808                     ; 876   assert_param(IS_I2C_CLEAR_ITPENDINGBIT_OK(I2C_ITPendingBit));
2810  0002 a32220        	cpw	x,#8736
2811  0005 2722          	jreq	L633
2812  0007 a32108        	cpw	x,#8456
2813  000a 271d          	jreq	L633
2814  000c a32104        	cpw	x,#8452
2815  000f 2718          	jreq	L633
2816  0011 a32102        	cpw	x,#8450
2817  0014 2713          	jreq	L633
2818  0016 a32101        	cpw	x,#8449
2819  0019 270e          	jreq	L633
2820  001b ae036c        	ldw	x,#876
2821  001e 89            	pushw	x
2822  001f 5f            	clrw	x
2823  0020 89            	pushw	x
2824  0021 ae000c        	ldw	x,#L131
2825  0024 cd0000        	call	_assert_failed
2827  0027 5b04          	addw	sp,#4
2828  0029               L633:
2829                     ; 879   flagpos = (uint16_t)I2C_ITPendingBit & FLAG_Mask;
2831  0029 7b04          	ld	a,(OFST+2,sp)
2832  002b 5f            	clrw	x
2833  002c 02            	rlwa	x,a
2834  002d 1f01          	ldw	(OFST-1,sp),x
2836                     ; 882   I2C->SR2 = (uint8_t)((uint16_t)~flagpos);
2838  002f 7b02          	ld	a,(OFST+0,sp)
2839  0031 43            	cpl	a
2840  0032 c75218        	ld	21016,a
2841                     ; 883 }
2844  0035 5b04          	addw	sp,#4
2845  0037 81            	ret	
2858                     	xdef	_I2C_ClearITPendingBit
2859                     	xdef	_I2C_GetITStatus
2860                     	xdef	_I2C_ClearFlag
2861                     	xdef	_I2C_GetFlagStatus
2862                     	xdef	_I2C_GetLastEvent
2863                     	xdef	_I2C_CheckEvent
2864                     	xdef	_I2C_SendData
2865                     	xdef	_I2C_Send7bitAddress
2866                     	xdef	_I2C_ReceiveData
2867                     	xdef	_I2C_ITConfig
2868                     	xdef	_I2C_FastModeDutyCycleConfig
2869                     	xdef	_I2C_AcknowledgeConfig
2870                     	xdef	_I2C_StretchClockCmd
2871                     	xdef	_I2C_SoftwareResetCmd
2872                     	xdef	_I2C_GenerateSTOP
2873                     	xdef	_I2C_GenerateSTART
2874                     	xdef	_I2C_GeneralCallCmd
2875                     	xdef	_I2C_Cmd
2876                     	xdef	_I2C_Init
2877                     	xdef	_I2C_DeInit
2878                     	xref	_assert_failed
2879                     	switch	.const
2880  000c               L131:
2881  000c 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
2882  001e 6965735c7374  	dc.b	"ies\stm8s_stdperip"
2883  0030 685f64726976  	dc.b	"h_driver\src\stm8s"
2884  0042 5f6932632e63  	dc.b	"_i2c.c",0
2885                     	xref.b	c_lreg
2886                     	xref.b	c_x
2906                     	xref	c_sdivx
2907                     	xref	c_ludv
2908                     	xref	c_rtol
2909                     	xref	c_smul
2910                     	xref	c_lmul
2911                     	xref	c_lcmp
2912                     	xref	c_ltor
2913                     	xref	c_lzmp
2914                     	end
