   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 53 void UART1_DeInit(void)
  49                     ; 54 {
  51                     .text:	section	.text,new
  52  0000               _UART1_DeInit:
  56                     ; 57   (void)UART1->SR;
  58  0000 c65230        	ld	a,21040
  59                     ; 58   (void)UART1->DR;
  61  0003 c65231        	ld	a,21041
  62                     ; 60   UART1->BRR2 = UART1_BRR2_RESET_VALUE;  /* Set UART1_BRR2 to reset value 0x00 */
  64  0006 725f5233      	clr	21043
  65                     ; 61   UART1->BRR1 = UART1_BRR1_RESET_VALUE;  /* Set UART1_BRR1 to reset value 0x00 */
  67  000a 725f5232      	clr	21042
  68                     ; 63   UART1->CR1 = UART1_CR1_RESET_VALUE;  /* Set UART1_CR1 to reset value 0x00 */
  70  000e 725f5234      	clr	21044
  71                     ; 64   UART1->CR2 = UART1_CR2_RESET_VALUE;  /* Set UART1_CR2 to reset value 0x00 */
  73  0012 725f5235      	clr	21045
  74                     ; 65   UART1->CR3 = UART1_CR3_RESET_VALUE;  /* Set UART1_CR3 to reset value 0x00 */
  76  0016 725f5236      	clr	21046
  77                     ; 66   UART1->CR4 = UART1_CR4_RESET_VALUE;  /* Set UART1_CR4 to reset value 0x00 */
  79  001a 725f5237      	clr	21047
  80                     ; 67   UART1->CR5 = UART1_CR5_RESET_VALUE;  /* Set UART1_CR5 to reset value 0x00 */
  82  001e 725f5238      	clr	21048
  83                     ; 69   UART1->GTR = UART1_GTR_RESET_VALUE;
  85  0022 725f5239      	clr	21049
  86                     ; 70   UART1->PSCR = UART1_PSCR_RESET_VALUE;
  88  0026 725f523a      	clr	21050
  89                     ; 71 }
  92  002a 81            	ret	
 396                     .const:	section	.text
 397  0000               L21:
 398  0000 00098969      	dc.l	625001
 399  0004               L27:
 400  0004 00000064      	dc.l	100
 401                     ; 90 void UART1_Init(uint32_t BaudRate, UART1_WordLength_TypeDef WordLength, 
 401                     ; 91                 UART1_StopBits_TypeDef StopBits, UART1_Parity_TypeDef Parity, 
 401                     ; 92                 UART1_SyncMode_TypeDef SyncMode, UART1_Mode_TypeDef Mode)
 401                     ; 93 {
 402                     .text:	section	.text,new
 403  0000               _UART1_Init:
 405  0000 520c          	subw	sp,#12
 406       0000000c      OFST:	set	12
 409                     ; 94   uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
 413                     ; 97   assert_param(IS_UART1_BAUDRATE_OK(BaudRate));
 415  0002 96            	ldw	x,sp
 416  0003 1c000f        	addw	x,#OFST+3
 417  0006 cd0000        	call	c_ltor
 419  0009 ae0000        	ldw	x,#L21
 420  000c cd0000        	call	c_lcmp
 422  000f 2506          	jrult	L41
 423  0011 ae0061        	ldw	x,#97
 424  0014 cd01a6        	call	LC001
 425  0017               L41:
 426                     ; 98   assert_param(IS_UART1_WORDLENGTH_OK(WordLength));
 428  0017 7b13          	ld	a,(OFST+7,sp)
 429  0019 270a          	jreq	L42
 430  001b a110          	cp	a,#16
 431  001d 2706          	jreq	L42
 432  001f ae0062        	ldw	x,#98
 433  0022 cd01a6        	call	LC001
 434  0025               L42:
 435                     ; 99   assert_param(IS_UART1_STOPBITS_OK(StopBits));
 437  0025 7b14          	ld	a,(OFST+8,sp)
 438  0027 2712          	jreq	L43
 439  0029 a110          	cp	a,#16
 440  002b 270e          	jreq	L43
 441  002d a120          	cp	a,#32
 442  002f 270a          	jreq	L43
 443  0031 a130          	cp	a,#48
 444  0033 2706          	jreq	L43
 445  0035 ae0063        	ldw	x,#99
 446  0038 cd01a6        	call	LC001
 447  003b               L43:
 448                     ; 100   assert_param(IS_UART1_PARITY_OK(Parity));
 450  003b 7b15          	ld	a,(OFST+9,sp)
 451  003d 270e          	jreq	L44
 452  003f a104          	cp	a,#4
 453  0041 270a          	jreq	L44
 454  0043 a106          	cp	a,#6
 455  0045 2706          	jreq	L44
 456  0047 ae0064        	ldw	x,#100
 457  004a cd01a6        	call	LC001
 458  004d               L44:
 459                     ; 101   assert_param(IS_UART1_MODE_OK((uint8_t)Mode));
 461  004d 7b17          	ld	a,(OFST+11,sp)
 462  004f a108          	cp	a,#8
 463  0051 2722          	jreq	L45
 464  0053 a140          	cp	a,#64
 465  0055 271e          	jreq	L45
 466  0057 a104          	cp	a,#4
 467  0059 271a          	jreq	L45
 468  005b a180          	cp	a,#128
 469  005d 2716          	jreq	L45
 470  005f a10c          	cp	a,#12
 471  0061 2712          	jreq	L45
 472  0063 a144          	cp	a,#68
 473  0065 270e          	jreq	L45
 474  0067 a1c0          	cp	a,#192
 475  0069 270a          	jreq	L45
 476  006b a188          	cp	a,#136
 477  006d 2706          	jreq	L45
 478  006f ae0065        	ldw	x,#101
 479  0072 cd01a6        	call	LC001
 480  0075               L45:
 481                     ; 102   assert_param(IS_UART1_SYNCMODE_OK((uint8_t)SyncMode));
 483  0075 7b16          	ld	a,(OFST+10,sp)
 484  0077 a488          	and	a,#136
 485  0079 a188          	cp	a,#136
 486  007b 2718          	jreq	L06
 487  007d 7b16          	ld	a,(OFST+10,sp)
 488  007f a444          	and	a,#68
 489  0081 a144          	cp	a,#68
 490  0083 2710          	jreq	L06
 491  0085 7b16          	ld	a,(OFST+10,sp)
 492  0087 a422          	and	a,#34
 493  0089 a122          	cp	a,#34
 494  008b 2708          	jreq	L06
 495  008d 7b16          	ld	a,(OFST+10,sp)
 496  008f a411          	and	a,#17
 497  0091 a111          	cp	a,#17
 498  0093 2606          	jrne	L26
 499  0095               L06:
 500  0095 ae0066        	ldw	x,#102
 501  0098 cd01a6        	call	LC001
 502  009b               L26:
 503                     ; 105   UART1->CR1 &= (uint8_t)(~UART1_CR1_M);  
 505  009b 72195234      	bres	21044,#4
 506                     ; 108   UART1->CR1 |= (uint8_t)WordLength;
 508  009f c65234        	ld	a,21044
 509  00a2 1a13          	or	a,(OFST+7,sp)
 510  00a4 c75234        	ld	21044,a
 511                     ; 111   UART1->CR3 &= (uint8_t)(~UART1_CR3_STOP);  
 513  00a7 c65236        	ld	a,21046
 514  00aa a4cf          	and	a,#207
 515  00ac c75236        	ld	21046,a
 516                     ; 113   UART1->CR3 |= (uint8_t)StopBits;  
 518  00af c65236        	ld	a,21046
 519  00b2 1a14          	or	a,(OFST+8,sp)
 520  00b4 c75236        	ld	21046,a
 521                     ; 116   UART1->CR1 &= (uint8_t)(~(UART1_CR1_PCEN | UART1_CR1_PS  ));  
 523  00b7 c65234        	ld	a,21044
 524  00ba a4f9          	and	a,#249
 525  00bc c75234        	ld	21044,a
 526                     ; 118   UART1->CR1 |= (uint8_t)Parity;  
 528  00bf c65234        	ld	a,21044
 529  00c2 1a15          	or	a,(OFST+9,sp)
 530  00c4 c75234        	ld	21044,a
 531                     ; 121   UART1->BRR1 &= (uint8_t)(~UART1_BRR1_DIVM);  
 533  00c7 725f5232      	clr	21042
 534                     ; 123   UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVM);  
 536  00cb c65233        	ld	a,21043
 537  00ce a40f          	and	a,#15
 538  00d0 c75233        	ld	21043,a
 539                     ; 125   UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVF);  
 541  00d3 c65233        	ld	a,21043
 542  00d6 a4f0          	and	a,#240
 543  00d8 c75233        	ld	21043,a
 544                     ; 128   BaudRate_Mantissa    = ((uint32_t)CLK_GetClockFreq() / (BaudRate << 4));
 546  00db 96            	ldw	x,sp
 547  00dc cd01b2        	call	LC002
 549  00df 96            	ldw	x,sp
 550  00e0 5c            	incw	x
 551  00e1 cd0000        	call	c_rtol
 554  00e4 cd0000        	call	_CLK_GetClockFreq
 556  00e7 96            	ldw	x,sp
 557  00e8 5c            	incw	x
 558  00e9 cd0000        	call	c_ludv
 560  00ec 96            	ldw	x,sp
 561  00ed 1c0009        	addw	x,#OFST-3
 562  00f0 cd0000        	call	c_rtol
 565                     ; 129   BaudRate_Mantissa100 = (((uint32_t)CLK_GetClockFreq() * 100) / (BaudRate << 4));
 567  00f3 96            	ldw	x,sp
 568  00f4 cd01b2        	call	LC002
 570  00f7 96            	ldw	x,sp
 571  00f8 5c            	incw	x
 572  00f9 cd0000        	call	c_rtol
 575  00fc cd0000        	call	_CLK_GetClockFreq
 577  00ff a664          	ld	a,#100
 578  0101 cd0000        	call	c_smul
 580  0104 96            	ldw	x,sp
 581  0105 5c            	incw	x
 582  0106 cd0000        	call	c_ludv
 584  0109 96            	ldw	x,sp
 585  010a 1c0005        	addw	x,#OFST-7
 586  010d cd0000        	call	c_rtol
 589                     ; 131   UART1->BRR2 |= (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8_t)0x0F); 
 591  0110 96            	ldw	x,sp
 592  0111 1c0009        	addw	x,#OFST-3
 593  0114 cd0000        	call	c_ltor
 595  0117 a664          	ld	a,#100
 596  0119 cd0000        	call	c_smul
 598  011c 96            	ldw	x,sp
 599  011d 5c            	incw	x
 600  011e cd0000        	call	c_rtol
 603  0121 96            	ldw	x,sp
 604  0122 1c0005        	addw	x,#OFST-7
 605  0125 cd0000        	call	c_ltor
 607  0128 96            	ldw	x,sp
 608  0129 5c            	incw	x
 609  012a cd0000        	call	c_lsub
 611  012d a604          	ld	a,#4
 612  012f cd0000        	call	c_llsh
 614  0132 ae0004        	ldw	x,#L27
 615  0135 cd0000        	call	c_ludv
 617  0138 b603          	ld	a,c_lreg+3
 618  013a a40f          	and	a,#15
 619  013c ca5233        	or	a,21043
 620  013f c75233        	ld	21043,a
 621                     ; 133   UART1->BRR2 |= (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0); 
 623  0142 1e0b          	ldw	x,(OFST-1,sp)
 624  0144 54            	srlw	x
 625  0145 54            	srlw	x
 626  0146 54            	srlw	x
 627  0147 54            	srlw	x
 628  0148 01            	rrwa	x,a
 629  0149 a4f0          	and	a,#240
 630  014b ca5233        	or	a,21043
 631  014e c75233        	ld	21043,a
 632                     ; 135   UART1->BRR1 |= (uint8_t)BaudRate_Mantissa;           
 634  0151 c65232        	ld	a,21042
 635  0154 1a0c          	or	a,(OFST+0,sp)
 636  0156 c75232        	ld	21042,a
 637                     ; 138   UART1->CR2 &= (uint8_t)~(UART1_CR2_TEN | UART1_CR2_REN); 
 639  0159 c65235        	ld	a,21045
 640  015c a4f3          	and	a,#243
 641  015e c75235        	ld	21045,a
 642                     ; 140   UART1->CR3 &= (uint8_t)~(UART1_CR3_CPOL | UART1_CR3_CPHA | UART1_CR3_LBCL); 
 644  0161 c65236        	ld	a,21046
 645  0164 a4f8          	and	a,#248
 646  0166 c75236        	ld	21046,a
 647                     ; 142   UART1->CR3 |= (uint8_t)((uint8_t)SyncMode & (uint8_t)(UART1_CR3_CPOL | 
 647                     ; 143                                                         UART1_CR3_CPHA | UART1_CR3_LBCL));  
 649  0169 7b16          	ld	a,(OFST+10,sp)
 650  016b a407          	and	a,#7
 651  016d ca5236        	or	a,21046
 652  0170 c75236        	ld	21046,a
 653                     ; 145   if ((uint8_t)(Mode & UART1_MODE_TX_ENABLE))
 655  0173 7b17          	ld	a,(OFST+11,sp)
 656  0175 a504          	bcp	a,#4
 657  0177 2706          	jreq	L571
 658                     ; 148     UART1->CR2 |= (uint8_t)UART1_CR2_TEN;  
 660  0179 72165235      	bset	21045,#3
 662  017d 2004          	jra	L771
 663  017f               L571:
 664                     ; 153     UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN);  
 666  017f 72175235      	bres	21045,#3
 667  0183               L771:
 668                     ; 155   if ((uint8_t)(Mode & UART1_MODE_RX_ENABLE))
 670  0183 a508          	bcp	a,#8
 671  0185 2706          	jreq	L102
 672                     ; 158     UART1->CR2 |= (uint8_t)UART1_CR2_REN;  
 674  0187 72145235      	bset	21045,#2
 676  018b 2004          	jra	L302
 677  018d               L102:
 678                     ; 163     UART1->CR2 &= (uint8_t)(~UART1_CR2_REN);  
 680  018d 72155235      	bres	21045,#2
 681  0191               L302:
 682                     ; 167   if ((uint8_t)(SyncMode & UART1_SYNCMODE_CLOCK_DISABLE))
 684  0191 7b16          	ld	a,(OFST+10,sp)
 685  0193 2a06          	jrpl	L502
 686                     ; 170     UART1->CR3 &= (uint8_t)(~UART1_CR3_CKEN); 
 688  0195 72175236      	bres	21046,#3
 690  0199 2008          	jra	L702
 691  019b               L502:
 692                     ; 174     UART1->CR3 |= (uint8_t)((uint8_t)SyncMode & UART1_CR3_CKEN);
 694  019b a408          	and	a,#8
 695  019d ca5236        	or	a,21046
 696  01a0 c75236        	ld	21046,a
 697  01a3               L702:
 698                     ; 176 }
 701  01a3 5b0c          	addw	sp,#12
 702  01a5 81            	ret	
 703  01a6               LC001:
 704  01a6 89            	pushw	x
 705  01a7 5f            	clrw	x
 706  01a8 89            	pushw	x
 707  01a9 ae0008        	ldw	x,#L371
 708  01ac cd0000        	call	_assert_failed
 710  01af 5b04          	addw	sp,#4
 711  01b1 81            	ret	
 712  01b2               LC002:
 713  01b2 1c000f        	addw	x,#OFST+3
 714  01b5 cd0000        	call	c_ltor
 716  01b8 a604          	ld	a,#4
 717  01ba cc0000        	jp	c_llsh
 772                     ; 184 void UART1_Cmd(FunctionalState NewState)
 772                     ; 185 {
 773                     .text:	section	.text,new
 774  0000               _UART1_Cmd:
 778                     ; 186   if (NewState != DISABLE)
 780  0000 4d            	tnz	a
 781  0001 2705          	jreq	L732
 782                     ; 189     UART1->CR1 &= (uint8_t)(~UART1_CR1_UARTD); 
 784  0003 721b5234      	bres	21044,#5
 787  0007 81            	ret	
 788  0008               L732:
 789                     ; 194     UART1->CR1 |= UART1_CR1_UARTD;  
 791  0008 721a5234      	bset	21044,#5
 792                     ; 196 }
 795  000c 81            	ret	
 921                     ; 211 void UART1_ITConfig(UART1_IT_TypeDef UART1_IT, FunctionalState NewState)
 921                     ; 212 {
 922                     .text:	section	.text,new
 923  0000               _UART1_ITConfig:
 925  0000 89            	pushw	x
 926  0001 89            	pushw	x
 927       00000002      OFST:	set	2
 930                     ; 213   uint8_t uartreg = 0, itpos = 0x00;
 934                     ; 216   assert_param(IS_UART1_CONFIG_IT_OK(UART1_IT));
 936  0002 a30100        	cpw	x,#256
 937  0005 271e          	jreq	L401
 938  0007 a30277        	cpw	x,#631
 939  000a 2719          	jreq	L401
 940  000c a30266        	cpw	x,#614
 941  000f 2714          	jreq	L401
 942  0011 a30205        	cpw	x,#517
 943  0014 270f          	jreq	L401
 944  0016 a30244        	cpw	x,#580
 945  0019 270a          	jreq	L401
 946  001b a30346        	cpw	x,#838
 947  001e 2705          	jreq	L401
 948  0020 ae00d8        	ldw	x,#216
 949  0023 ad70          	call	LC006
 950  0025               L401:
 951                     ; 217   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 953  0025 7b07          	ld	a,(OFST+5,sp)
 954  0027 2708          	jreq	L411
 955  0029 4a            	dec	a
 956  002a 2705          	jreq	L411
 957  002c ae00d9        	ldw	x,#217
 958  002f ad64          	call	LC006
 959  0031               L411:
 960                     ; 220   uartreg = (uint8_t)((uint16_t)UART1_IT >> 0x08);
 962  0031 7b03          	ld	a,(OFST+1,sp)
 963  0033 6b01          	ld	(OFST-1,sp),a
 965                     ; 222   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART1_IT & (uint8_t)0x0F));
 967  0035 7b04          	ld	a,(OFST+2,sp)
 968  0037 a40f          	and	a,#15
 969  0039 5f            	clrw	x
 970  003a 97            	ld	xl,a
 971  003b a601          	ld	a,#1
 972  003d 5d            	tnzw	x
 973  003e 2704          	jreq	L021
 974  0040               L221:
 975  0040 48            	sll	a
 976  0041 5a            	decw	x
 977  0042 26fc          	jrne	L221
 978  0044               L021:
 979  0044 6b02          	ld	(OFST+0,sp),a
 981                     ; 224   if (NewState != DISABLE)
 983  0046 7b07          	ld	a,(OFST+5,sp)
 984  0048 271f          	jreq	L123
 985                     ; 227     if (uartreg == 0x01)
 987  004a 7b01          	ld	a,(OFST-1,sp)
 988  004c a101          	cp	a,#1
 989  004e 2607          	jrne	L323
 990                     ; 229       UART1->CR1 |= itpos;
 992  0050 c65234        	ld	a,21044
 993  0053 1a02          	or	a,(OFST+0,sp)
 995  0055 201e          	jp	LC004
 996  0057               L323:
 997                     ; 231     else if (uartreg == 0x02)
 999  0057 a102          	cp	a,#2
1000  0059 2607          	jrne	L723
1001                     ; 233       UART1->CR2 |= itpos;
1003  005b c65235        	ld	a,21045
1004  005e 1a02          	or	a,(OFST+0,sp)
1006  0060 2022          	jp	LC005
1007  0062               L723:
1008                     ; 237       UART1->CR4 |= itpos;
1010  0062 c65237        	ld	a,21047
1011  0065 1a02          	or	a,(OFST+0,sp)
1012  0067 2026          	jp	LC003
1013  0069               L123:
1014                     ; 243     if (uartreg == 0x01)
1016  0069 7b01          	ld	a,(OFST-1,sp)
1017  006b a101          	cp	a,#1
1018  006d 260b          	jrne	L533
1019                     ; 245       UART1->CR1 &= (uint8_t)(~itpos);
1021  006f 7b02          	ld	a,(OFST+0,sp)
1022  0071 43            	cpl	a
1023  0072 c45234        	and	a,21044
1024  0075               LC004:
1025  0075 c75234        	ld	21044,a
1027  0078 2018          	jra	L333
1028  007a               L533:
1029                     ; 247     else if (uartreg == 0x02)
1031  007a a102          	cp	a,#2
1032  007c 260b          	jrne	L143
1033                     ; 249       UART1->CR2 &= (uint8_t)(~itpos);
1035  007e 7b02          	ld	a,(OFST+0,sp)
1036  0080 43            	cpl	a
1037  0081 c45235        	and	a,21045
1038  0084               LC005:
1039  0084 c75235        	ld	21045,a
1041  0087 2009          	jra	L333
1042  0089               L143:
1043                     ; 253       UART1->CR4 &= (uint8_t)(~itpos);
1045  0089 7b02          	ld	a,(OFST+0,sp)
1046  008b 43            	cpl	a
1047  008c c45237        	and	a,21047
1048  008f               LC003:
1049  008f c75237        	ld	21047,a
1050  0092               L333:
1051                     ; 257 }
1054  0092 5b04          	addw	sp,#4
1055  0094 81            	ret	
1056  0095               LC006:
1057  0095 89            	pushw	x
1058  0096 5f            	clrw	x
1059  0097 89            	pushw	x
1060  0098 ae0008        	ldw	x,#L371
1061  009b cd0000        	call	_assert_failed
1063  009e 5b04          	addw	sp,#4
1064  00a0 81            	ret	
1101                     ; 265 void UART1_HalfDuplexCmd(FunctionalState NewState)
1101                     ; 266 {
1102                     .text:	section	.text,new
1103  0000               _UART1_HalfDuplexCmd:
1105  0000 88            	push	a
1106       00000000      OFST:	set	0
1109                     ; 267   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1111  0001 4d            	tnz	a
1112  0002 2711          	jreq	L231
1113  0004 4a            	dec	a
1114  0005 270e          	jreq	L231
1115  0007 ae010b        	ldw	x,#267
1116  000a 89            	pushw	x
1117  000b 5f            	clrw	x
1118  000c 89            	pushw	x
1119  000d ae0008        	ldw	x,#L371
1120  0010 cd0000        	call	_assert_failed
1122  0013 5b04          	addw	sp,#4
1123  0015               L231:
1124                     ; 269   if (NewState != DISABLE)
1126  0015 7b01          	ld	a,(OFST+1,sp)
1127  0017 2706          	jreq	L363
1128                     ; 271     UART1->CR5 |= UART1_CR5_HDSEL;  /**< UART1 Half Duplex Enable  */
1130  0019 72165238      	bset	21048,#3
1132  001d 2004          	jra	L563
1133  001f               L363:
1134                     ; 275     UART1->CR5 &= (uint8_t)~UART1_CR5_HDSEL; /**< UART1 Half Duplex Disable */
1136  001f 72175238      	bres	21048,#3
1137  0023               L563:
1138                     ; 277 }
1141  0023 84            	pop	a
1142  0024 81            	ret	
1200                     ; 285 void UART1_IrDAConfig(UART1_IrDAMode_TypeDef UART1_IrDAMode)
1200                     ; 286 {
1201                     .text:	section	.text,new
1202  0000               _UART1_IrDAConfig:
1204  0000 88            	push	a
1205       00000000      OFST:	set	0
1208                     ; 287   assert_param(IS_UART1_IRDAMODE_OK(UART1_IrDAMode));
1210  0001 a101          	cp	a,#1
1211  0003 2711          	jreq	L441
1212  0005 4d            	tnz	a
1213  0006 270e          	jreq	L441
1214  0008 ae011f        	ldw	x,#287
1215  000b 89            	pushw	x
1216  000c 5f            	clrw	x
1217  000d 89            	pushw	x
1218  000e ae0008        	ldw	x,#L371
1219  0011 cd0000        	call	_assert_failed
1221  0014 5b04          	addw	sp,#4
1222  0016               L441:
1223                     ; 289   if (UART1_IrDAMode != UART1_IRDAMODE_NORMAL)
1225  0016 7b01          	ld	a,(OFST+1,sp)
1226  0018 2706          	jreq	L514
1227                     ; 291     UART1->CR5 |= UART1_CR5_IRLP;
1229  001a 72145238      	bset	21048,#2
1231  001e 2004          	jra	L714
1232  0020               L514:
1233                     ; 295     UART1->CR5 &= ((uint8_t)~UART1_CR5_IRLP);
1235  0020 72155238      	bres	21048,#2
1236  0024               L714:
1237                     ; 297 }
1240  0024 84            	pop	a
1241  0025 81            	ret	
1277                     ; 305 void UART1_IrDACmd(FunctionalState NewState)
1277                     ; 306 {
1278                     .text:	section	.text,new
1279  0000               _UART1_IrDACmd:
1281  0000 88            	push	a
1282       00000000      OFST:	set	0
1285                     ; 308   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1287  0001 4d            	tnz	a
1288  0002 2711          	jreq	L651
1289  0004 4a            	dec	a
1290  0005 270e          	jreq	L651
1291  0007 ae0134        	ldw	x,#308
1292  000a 89            	pushw	x
1293  000b 5f            	clrw	x
1294  000c 89            	pushw	x
1295  000d ae0008        	ldw	x,#L371
1296  0010 cd0000        	call	_assert_failed
1298  0013 5b04          	addw	sp,#4
1299  0015               L651:
1300                     ; 310   if (NewState != DISABLE)
1302  0015 7b01          	ld	a,(OFST+1,sp)
1303  0017 2706          	jreq	L734
1304                     ; 313     UART1->CR5 |= UART1_CR5_IREN;
1306  0019 72125238      	bset	21048,#1
1308  001d 2004          	jra	L144
1309  001f               L734:
1310                     ; 318     UART1->CR5 &= ((uint8_t)~UART1_CR5_IREN);
1312  001f 72135238      	bres	21048,#1
1313  0023               L144:
1314                     ; 320 }
1317  0023 84            	pop	a
1318  0024 81            	ret	
1378                     ; 329 void UART1_LINBreakDetectionConfig(UART1_LINBreakDetectionLength_TypeDef UART1_LINBreakDetectionLength)
1378                     ; 330 {
1379                     .text:	section	.text,new
1380  0000               _UART1_LINBreakDetectionConfig:
1382  0000 88            	push	a
1383       00000000      OFST:	set	0
1386                     ; 331   assert_param(IS_UART1_LINBREAKDETECTIONLENGTH_OK(UART1_LINBreakDetectionLength));
1388  0001 4d            	tnz	a
1389  0002 2711          	jreq	L071
1390  0004 4a            	dec	a
1391  0005 270e          	jreq	L071
1392  0007 ae014b        	ldw	x,#331
1393  000a 89            	pushw	x
1394  000b 5f            	clrw	x
1395  000c 89            	pushw	x
1396  000d ae0008        	ldw	x,#L371
1397  0010 cd0000        	call	_assert_failed
1399  0013 5b04          	addw	sp,#4
1400  0015               L071:
1401                     ; 333   if (UART1_LINBreakDetectionLength != UART1_LINBREAKDETECTIONLENGTH_10BITS)
1403  0015 7b01          	ld	a,(OFST+1,sp)
1404  0017 2706          	jreq	L174
1405                     ; 335     UART1->CR4 |= UART1_CR4_LBDL;
1407  0019 721a5237      	bset	21047,#5
1409  001d 2004          	jra	L374
1410  001f               L174:
1411                     ; 339     UART1->CR4 &= ((uint8_t)~UART1_CR4_LBDL);
1413  001f 721b5237      	bres	21047,#5
1414  0023               L374:
1415                     ; 341 }
1418  0023 84            	pop	a
1419  0024 81            	ret	
1455                     ; 349 void UART1_LINCmd(FunctionalState NewState)
1455                     ; 350 {
1456                     .text:	section	.text,new
1457  0000               _UART1_LINCmd:
1459  0000 88            	push	a
1460       00000000      OFST:	set	0
1463                     ; 351   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1465  0001 4d            	tnz	a
1466  0002 2711          	jreq	L202
1467  0004 4a            	dec	a
1468  0005 270e          	jreq	L202
1469  0007 ae015f        	ldw	x,#351
1470  000a 89            	pushw	x
1471  000b 5f            	clrw	x
1472  000c 89            	pushw	x
1473  000d ae0008        	ldw	x,#L371
1474  0010 cd0000        	call	_assert_failed
1476  0013 5b04          	addw	sp,#4
1477  0015               L202:
1478                     ; 353   if (NewState != DISABLE)
1480  0015 7b01          	ld	a,(OFST+1,sp)
1481  0017 2706          	jreq	L315
1482                     ; 356     UART1->CR3 |= UART1_CR3_LINEN;
1484  0019 721c5236      	bset	21046,#6
1486  001d 2004          	jra	L515
1487  001f               L315:
1488                     ; 361     UART1->CR3 &= ((uint8_t)~UART1_CR3_LINEN);
1490  001f 721d5236      	bres	21046,#6
1491  0023               L515:
1492                     ; 363 }
1495  0023 84            	pop	a
1496  0024 81            	ret	
1532                     ; 371 void UART1_SmartCardCmd(FunctionalState NewState)
1532                     ; 372 {
1533                     .text:	section	.text,new
1534  0000               _UART1_SmartCardCmd:
1536  0000 88            	push	a
1537       00000000      OFST:	set	0
1540                     ; 373   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1542  0001 4d            	tnz	a
1543  0002 2711          	jreq	L412
1544  0004 4a            	dec	a
1545  0005 270e          	jreq	L412
1546  0007 ae0175        	ldw	x,#373
1547  000a 89            	pushw	x
1548  000b 5f            	clrw	x
1549  000c 89            	pushw	x
1550  000d ae0008        	ldw	x,#L371
1551  0010 cd0000        	call	_assert_failed
1553  0013 5b04          	addw	sp,#4
1554  0015               L412:
1555                     ; 375   if (NewState != DISABLE)
1557  0015 7b01          	ld	a,(OFST+1,sp)
1558  0017 2706          	jreq	L535
1559                     ; 378     UART1->CR5 |= UART1_CR5_SCEN;
1561  0019 721a5238      	bset	21048,#5
1563  001d 2004          	jra	L735
1564  001f               L535:
1565                     ; 383     UART1->CR5 &= ((uint8_t)(~UART1_CR5_SCEN));
1567  001f 721b5238      	bres	21048,#5
1568  0023               L735:
1569                     ; 385 }
1572  0023 84            	pop	a
1573  0024 81            	ret	
1610                     ; 394 void UART1_SmartCardNACKCmd(FunctionalState NewState)
1610                     ; 395 {
1611                     .text:	section	.text,new
1612  0000               _UART1_SmartCardNACKCmd:
1614  0000 88            	push	a
1615       00000000      OFST:	set	0
1618                     ; 396   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1620  0001 4d            	tnz	a
1621  0002 2711          	jreq	L622
1622  0004 4a            	dec	a
1623  0005 270e          	jreq	L622
1624  0007 ae018c        	ldw	x,#396
1625  000a 89            	pushw	x
1626  000b 5f            	clrw	x
1627  000c 89            	pushw	x
1628  000d ae0008        	ldw	x,#L371
1629  0010 cd0000        	call	_assert_failed
1631  0013 5b04          	addw	sp,#4
1632  0015               L622:
1633                     ; 398   if (NewState != DISABLE)
1635  0015 7b01          	ld	a,(OFST+1,sp)
1636  0017 2706          	jreq	L755
1637                     ; 401     UART1->CR5 |= UART1_CR5_NACK;
1639  0019 72185238      	bset	21048,#4
1641  001d 2004          	jra	L165
1642  001f               L755:
1643                     ; 406     UART1->CR5 &= ((uint8_t)~(UART1_CR5_NACK));
1645  001f 72195238      	bres	21048,#4
1646  0023               L165:
1647                     ; 408 }
1650  0023 84            	pop	a
1651  0024 81            	ret	
1709                     ; 416 void UART1_WakeUpConfig(UART1_WakeUp_TypeDef UART1_WakeUp)
1709                     ; 417 {
1710                     .text:	section	.text,new
1711  0000               _UART1_WakeUpConfig:
1713  0000 88            	push	a
1714       00000000      OFST:	set	0
1717                     ; 418   assert_param(IS_UART1_WAKEUP_OK(UART1_WakeUp));
1719  0001 4d            	tnz	a
1720  0002 2712          	jreq	L042
1721  0004 a108          	cp	a,#8
1722  0006 270e          	jreq	L042
1723  0008 ae01a2        	ldw	x,#418
1724  000b 89            	pushw	x
1725  000c 5f            	clrw	x
1726  000d 89            	pushw	x
1727  000e ae0008        	ldw	x,#L371
1728  0011 cd0000        	call	_assert_failed
1730  0014 5b04          	addw	sp,#4
1731  0016               L042:
1732                     ; 420   UART1->CR1 &= ((uint8_t)~UART1_CR1_WAKE);
1734  0016 72175234      	bres	21044,#3
1735                     ; 421   UART1->CR1 |= (uint8_t)UART1_WakeUp;
1737  001a c65234        	ld	a,21044
1738  001d 1a01          	or	a,(OFST+1,sp)
1739  001f c75234        	ld	21044,a
1740                     ; 422 }
1743  0022 84            	pop	a
1744  0023 81            	ret	
1781                     ; 430 void UART1_ReceiverWakeUpCmd(FunctionalState NewState)
1781                     ; 431 {
1782                     .text:	section	.text,new
1783  0000               _UART1_ReceiverWakeUpCmd:
1785  0000 88            	push	a
1786       00000000      OFST:	set	0
1789                     ; 432   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1791  0001 4d            	tnz	a
1792  0002 2711          	jreq	L252
1793  0004 4a            	dec	a
1794  0005 270e          	jreq	L252
1795  0007 ae01b0        	ldw	x,#432
1796  000a 89            	pushw	x
1797  000b 5f            	clrw	x
1798  000c 89            	pushw	x
1799  000d ae0008        	ldw	x,#L371
1800  0010 cd0000        	call	_assert_failed
1802  0013 5b04          	addw	sp,#4
1803  0015               L252:
1804                     ; 434   if (NewState != DISABLE)
1806  0015 7b01          	ld	a,(OFST+1,sp)
1807  0017 2706          	jreq	L726
1808                     ; 437     UART1->CR2 |= UART1_CR2_RWU;
1810  0019 72125235      	bset	21045,#1
1812  001d 2004          	jra	L136
1813  001f               L726:
1814                     ; 442     UART1->CR2 &= ((uint8_t)~UART1_CR2_RWU);
1816  001f 72135235      	bres	21045,#1
1817  0023               L136:
1818                     ; 444 }
1821  0023 84            	pop	a
1822  0024 81            	ret	
1845                     ; 451 uint8_t UART1_ReceiveData8(void)
1845                     ; 452 {
1846                     .text:	section	.text,new
1847  0000               _UART1_ReceiveData8:
1851                     ; 453   return ((uint8_t)UART1->DR);
1853  0000 c65231        	ld	a,21041
1856  0003 81            	ret	
1890                     ; 461 uint16_t UART1_ReceiveData9(void)
1890                     ; 462 {
1891                     .text:	section	.text,new
1892  0000               _UART1_ReceiveData9:
1894  0000 89            	pushw	x
1895       00000002      OFST:	set	2
1898                     ; 463   uint16_t temp = 0;
1900                     ; 465   temp = (uint16_t)(((uint16_t)( (uint16_t)UART1->CR1 & (uint16_t)UART1_CR1_R8)) << 1);
1902  0001 c65234        	ld	a,21044
1903  0004 a480          	and	a,#128
1904  0006 5f            	clrw	x
1905  0007 02            	rlwa	x,a
1906  0008 58            	sllw	x
1907  0009 1f01          	ldw	(OFST-1,sp),x
1909                     ; 466   return (uint16_t)( (((uint16_t) UART1->DR) | temp ) & ((uint16_t)0x01FF));
1911  000b c65231        	ld	a,21041
1912  000e 5f            	clrw	x
1913  000f 97            	ld	xl,a
1914  0010 01            	rrwa	x,a
1915  0011 1a02          	or	a,(OFST+0,sp)
1916  0013 01            	rrwa	x,a
1917  0014 1a01          	or	a,(OFST-1,sp)
1918  0016 a401          	and	a,#1
1919  0018 01            	rrwa	x,a
1922  0019 5b02          	addw	sp,#2
1923  001b 81            	ret	
1957                     ; 474 void UART1_SendData8(uint8_t Data)
1957                     ; 475 {
1958                     .text:	section	.text,new
1959  0000               _UART1_SendData8:
1963                     ; 477   UART1->DR = Data;
1965  0000 c75231        	ld	21041,a
1966                     ; 478 }
1969  0003 81            	ret	
2003                     ; 486 void UART1_SendData9(uint16_t Data)
2003                     ; 487 {
2004                     .text:	section	.text,new
2005  0000               _UART1_SendData9:
2007  0000 89            	pushw	x
2008       00000000      OFST:	set	0
2011                     ; 489   UART1->CR1 &= ((uint8_t)~UART1_CR1_T8);
2013  0001 721d5234      	bres	21044,#6
2014                     ; 491   UART1->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & UART1_CR1_T8);
2016  0005 54            	srlw	x
2017  0006 54            	srlw	x
2018  0007 9f            	ld	a,xl
2019  0008 a440          	and	a,#64
2020  000a ca5234        	or	a,21044
2021  000d c75234        	ld	21044,a
2022                     ; 493   UART1->DR   = (uint8_t)(Data);
2024  0010 7b02          	ld	a,(OFST+2,sp)
2025  0012 c75231        	ld	21041,a
2026                     ; 494 }
2029  0015 85            	popw	x
2030  0016 81            	ret	
2053                     ; 501 void UART1_SendBreak(void)
2053                     ; 502 {
2054                     .text:	section	.text,new
2055  0000               _UART1_SendBreak:
2059                     ; 503   UART1->CR2 |= UART1_CR2_SBK;
2061  0000 72105235      	bset	21045,#0
2062                     ; 504 }
2065  0004 81            	ret	
2100                     ; 511 void UART1_SetAddress(uint8_t UART1_Address)
2100                     ; 512 {
2101                     .text:	section	.text,new
2102  0000               _UART1_SetAddress:
2104  0000 88            	push	a
2105       00000000      OFST:	set	0
2108                     ; 514   assert_param(IS_UART1_ADDRESS_OK(UART1_Address));
2110  0001 a110          	cp	a,#16
2111  0003 250e          	jrult	L472
2112  0005 ae0202        	ldw	x,#514
2113  0008 89            	pushw	x
2114  0009 5f            	clrw	x
2115  000a 89            	pushw	x
2116  000b ae0008        	ldw	x,#L371
2117  000e cd0000        	call	_assert_failed
2119  0011 5b04          	addw	sp,#4
2120  0013               L472:
2121                     ; 517   UART1->CR4 &= ((uint8_t)~UART1_CR4_ADD);
2123  0013 c65237        	ld	a,21047
2124  0016 a4f0          	and	a,#240
2125  0018 c75237        	ld	21047,a
2126                     ; 519   UART1->CR4 |= UART1_Address;
2128  001b c65237        	ld	a,21047
2129  001e 1a01          	or	a,(OFST+1,sp)
2130  0020 c75237        	ld	21047,a
2131                     ; 520 }
2134  0023 84            	pop	a
2135  0024 81            	ret	
2169                     ; 528 void UART1_SetGuardTime(uint8_t UART1_GuardTime)
2169                     ; 529 {
2170                     .text:	section	.text,new
2171  0000               _UART1_SetGuardTime:
2175                     ; 531   UART1->GTR = UART1_GuardTime;
2177  0000 c75239        	ld	21049,a
2178                     ; 532 }
2181  0003 81            	ret	
2215                     ; 556 void UART1_SetPrescaler(uint8_t UART1_Prescaler)
2215                     ; 557 {
2216                     .text:	section	.text,new
2217  0000               _UART1_SetPrescaler:
2221                     ; 559   UART1->PSCR = UART1_Prescaler;
2223  0000 c7523a        	ld	21050,a
2224                     ; 560 }
2227  0003 81            	ret	
2371                     ; 568 FlagStatus UART1_GetFlagStatus(UART1_Flag_TypeDef UART1_FLAG)
2371                     ; 569 {
2372                     .text:	section	.text,new
2373  0000               _UART1_GetFlagStatus:
2375  0000 89            	pushw	x
2376  0001 88            	push	a
2377       00000001      OFST:	set	1
2380                     ; 570   FlagStatus status = RESET;
2382                     ; 573   assert_param(IS_UART1_FLAG_OK(UART1_FLAG));
2384  0002 a30080        	cpw	x,#128
2385  0005 273b          	jreq	L213
2386  0007 a30040        	cpw	x,#64
2387  000a 2736          	jreq	L213
2388  000c a30020        	cpw	x,#32
2389  000f 2731          	jreq	L213
2390  0011 a30010        	cpw	x,#16
2391  0014 272c          	jreq	L213
2392  0016 a30008        	cpw	x,#8
2393  0019 2727          	jreq	L213
2394  001b a30004        	cpw	x,#4
2395  001e 2722          	jreq	L213
2396  0020 a30002        	cpw	x,#2
2397  0023 271d          	jreq	L213
2398  0025 a30001        	cpw	x,#1
2399  0028 2718          	jreq	L213
2400  002a a30101        	cpw	x,#257
2401  002d 2713          	jreq	L213
2402  002f a30210        	cpw	x,#528
2403  0032 270e          	jreq	L213
2404  0034 ae023d        	ldw	x,#573
2405  0037 89            	pushw	x
2406  0038 5f            	clrw	x
2407  0039 89            	pushw	x
2408  003a ae0008        	ldw	x,#L371
2409  003d cd0000        	call	_assert_failed
2411  0040 5b04          	addw	sp,#4
2412  0042               L213:
2413                     ; 577   if (UART1_FLAG == UART1_FLAG_LBDF)
2415  0042 1e02          	ldw	x,(OFST+1,sp)
2416  0044 a30210        	cpw	x,#528
2417  0047 2605          	jrne	L1601
2418                     ; 579     if ((UART1->CR4 & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2420  0049 c65237        	ld	a,21047
2421                     ; 582       status = SET;
2423  004c 2008          	jp	LC009
2424                     ; 587       status = RESET;
2425  004e               L1601:
2426                     ; 590   else if (UART1_FLAG == UART1_FLAG_SBK)
2428  004e a30101        	cpw	x,#257
2429  0051 260b          	jrne	L1701
2430                     ; 592     if ((UART1->CR2 & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2432  0053 c65235        	ld	a,21045
2433  0056               LC009:
2434  0056 1503          	bcp	a,(OFST+2,sp)
2435  0058 270b          	jreq	L1011
2436                     ; 595       status = SET;
2438  005a               LC008:
2441  005a a601          	ld	a,#1
2444  005c 2008          	jra	L7601
2445                     ; 600       status = RESET;
2446  005e               L1701:
2447                     ; 605     if ((UART1->SR & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2449  005e c65230        	ld	a,21040
2450  0061 1503          	bcp	a,(OFST+2,sp)
2451                     ; 608       status = SET;
2453  0063 26f5          	jrne	LC008
2454  0065               L1011:
2455                     ; 613       status = RESET;
2459  0065 4f            	clr	a
2461  0066               L7601:
2462                     ; 617   return status;
2466  0066 5b03          	addw	sp,#3
2467  0068 81            	ret	
2503                     ; 646 void UART1_ClearFlag(UART1_Flag_TypeDef UART1_FLAG)
2503                     ; 647 {
2504                     .text:	section	.text,new
2505  0000               _UART1_ClearFlag:
2507  0000 89            	pushw	x
2508       00000000      OFST:	set	0
2511                     ; 648   assert_param(IS_UART1_CLEAR_FLAG_OK(UART1_FLAG));
2513  0001 a30020        	cpw	x,#32
2514  0004 2713          	jreq	L423
2515  0006 a30210        	cpw	x,#528
2516  0009 270e          	jreq	L423
2517  000b ae0288        	ldw	x,#648
2518  000e 89            	pushw	x
2519  000f 5f            	clrw	x
2520  0010 89            	pushw	x
2521  0011 ae0008        	ldw	x,#L371
2522  0014 cd0000        	call	_assert_failed
2524  0017 5b04          	addw	sp,#4
2525  0019               L423:
2526                     ; 651   if (UART1_FLAG == UART1_FLAG_RXNE)
2528  0019 1e01          	ldw	x,(OFST+1,sp)
2529  001b a30020        	cpw	x,#32
2530  001e 2606          	jrne	L3211
2531                     ; 653     UART1->SR = (uint8_t)~(UART1_SR_RXNE);
2533  0020 35df5230      	mov	21040,#223
2535  0024 2004          	jra	L5211
2536  0026               L3211:
2537                     ; 658     UART1->CR4 &= (uint8_t)~(UART1_CR4_LBDF);
2539  0026 72195237      	bres	21047,#4
2540  002a               L5211:
2541                     ; 660 }
2544  002a 85            	popw	x
2545  002b 81            	ret	
2628                     ; 675 ITStatus UART1_GetITStatus(UART1_IT_TypeDef UART1_IT)
2628                     ; 676 {
2629                     .text:	section	.text,new
2630  0000               _UART1_GetITStatus:
2632  0000 89            	pushw	x
2633  0001 89            	pushw	x
2634       00000002      OFST:	set	2
2637                     ; 677   ITStatus pendingbitstatus = RESET;
2639                     ; 678   uint8_t itpos = 0;
2641                     ; 679   uint8_t itmask1 = 0;
2643                     ; 680   uint8_t itmask2 = 0;
2645                     ; 681   uint8_t enablestatus = 0;
2647                     ; 684   assert_param(IS_UART1_GET_IT_OK(UART1_IT));
2649  0002 a30277        	cpw	x,#631
2650  0005 272c          	jreq	L633
2651  0007 a30266        	cpw	x,#614
2652  000a 2727          	jreq	L633
2653  000c a30255        	cpw	x,#597
2654  000f 2722          	jreq	L633
2655  0011 a30244        	cpw	x,#580
2656  0014 271d          	jreq	L633
2657  0016 a30235        	cpw	x,#565
2658  0019 2718          	jreq	L633
2659  001b a30346        	cpw	x,#838
2660  001e 2713          	jreq	L633
2661  0020 a30100        	cpw	x,#256
2662  0023 270e          	jreq	L633
2663  0025 ae02ac        	ldw	x,#684
2664  0028 89            	pushw	x
2665  0029 5f            	clrw	x
2666  002a 89            	pushw	x
2667  002b ae0008        	ldw	x,#L371
2668  002e cd0000        	call	_assert_failed
2670  0031 5b04          	addw	sp,#4
2671  0033               L633:
2672                     ; 687   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART1_IT & (uint8_t)0x0F));
2674  0033 7b04          	ld	a,(OFST+2,sp)
2675  0035 a40f          	and	a,#15
2676  0037 5f            	clrw	x
2677  0038 97            	ld	xl,a
2678  0039 a601          	ld	a,#1
2679  003b 5d            	tnzw	x
2680  003c 2704          	jreq	L243
2681  003e               L443:
2682  003e 48            	sll	a
2683  003f 5a            	decw	x
2684  0040 26fc          	jrne	L443
2685  0042               L243:
2686  0042 6b01          	ld	(OFST-1,sp),a
2688                     ; 689   itmask1 = (uint8_t)((uint8_t)UART1_IT >> (uint8_t)4);
2690  0044 7b04          	ld	a,(OFST+2,sp)
2691  0046 4e            	swap	a
2692  0047 a40f          	and	a,#15
2693  0049 6b02          	ld	(OFST+0,sp),a
2695                     ; 691   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
2697  004b 5f            	clrw	x
2698  004c 97            	ld	xl,a
2699  004d a601          	ld	a,#1
2700  004f 5d            	tnzw	x
2701  0050 2704          	jreq	L643
2702  0052               L053:
2703  0052 48            	sll	a
2704  0053 5a            	decw	x
2705  0054 26fc          	jrne	L053
2706  0056               L643:
2707  0056 6b02          	ld	(OFST+0,sp),a
2709                     ; 695   if (UART1_IT == UART1_IT_PE)
2711  0058 1e03          	ldw	x,(OFST+1,sp)
2712  005a a30100        	cpw	x,#256
2713  005d 260c          	jrne	L1711
2714                     ; 698     enablestatus = (uint8_t)((uint8_t)UART1->CR1 & itmask2);
2716  005f c65234        	ld	a,21044
2717  0062 1402          	and	a,(OFST+0,sp)
2718  0064 6b02          	ld	(OFST+0,sp),a
2720                     ; 701     if (((UART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
2722  0066 c65230        	ld	a,21040
2724                     ; 704       pendingbitstatus = SET;
2726  0069 200f          	jp	LC012
2727                     ; 709       pendingbitstatus = RESET;
2728  006b               L1711:
2729                     ; 713   else if (UART1_IT == UART1_IT_LBDF)
2731  006b a30346        	cpw	x,#838
2732  006e 2616          	jrne	L1021
2733                     ; 716     enablestatus = (uint8_t)((uint8_t)UART1->CR4 & itmask2);
2735  0070 c65237        	ld	a,21047
2736  0073 1402          	and	a,(OFST+0,sp)
2737  0075 6b02          	ld	(OFST+0,sp),a
2739                     ; 718     if (((UART1->CR4 & itpos) != (uint8_t)0x00) && enablestatus)
2741  0077 c65237        	ld	a,21047
2743  007a               LC012:
2744  007a 1501          	bcp	a,(OFST-1,sp)
2745  007c 271a          	jreq	L1121
2746  007e 7b02          	ld	a,(OFST+0,sp)
2747  0080 2716          	jreq	L1121
2748                     ; 721       pendingbitstatus = SET;
2750  0082               LC011:
2753  0082 a601          	ld	a,#1
2756  0084 2013          	jra	L7711
2757                     ; 726       pendingbitstatus = RESET;
2758  0086               L1021:
2759                     ; 732     enablestatus = (uint8_t)((uint8_t)UART1->CR2 & itmask2);
2761  0086 c65235        	ld	a,21045
2762  0089 1402          	and	a,(OFST+0,sp)
2763  008b 6b02          	ld	(OFST+0,sp),a
2765                     ; 734     if (((UART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
2767  008d c65230        	ld	a,21040
2768  0090 1501          	bcp	a,(OFST-1,sp)
2769  0092 2704          	jreq	L1121
2771  0094 7b02          	ld	a,(OFST+0,sp)
2772                     ; 737       pendingbitstatus = SET;
2774  0096 26ea          	jrne	LC011
2775  0098               L1121:
2776                     ; 742       pendingbitstatus = RESET;
2780  0098 4f            	clr	a
2782  0099               L7711:
2783                     ; 747   return  pendingbitstatus;
2787  0099 5b04          	addw	sp,#4
2788  009b 81            	ret	
2825                     ; 775 void UART1_ClearITPendingBit(UART1_IT_TypeDef UART1_IT)
2825                     ; 776 {
2826                     .text:	section	.text,new
2827  0000               _UART1_ClearITPendingBit:
2829  0000 89            	pushw	x
2830       00000000      OFST:	set	0
2833                     ; 777   assert_param(IS_UART1_CLEAR_IT_OK(UART1_IT));
2835  0001 a30255        	cpw	x,#597
2836  0004 2713          	jreq	L063
2837  0006 a30346        	cpw	x,#838
2838  0009 270e          	jreq	L063
2839  000b ae0309        	ldw	x,#777
2840  000e 89            	pushw	x
2841  000f 5f            	clrw	x
2842  0010 89            	pushw	x
2843  0011 ae0008        	ldw	x,#L371
2844  0014 cd0000        	call	_assert_failed
2846  0017 5b04          	addw	sp,#4
2847  0019               L063:
2848                     ; 780   if (UART1_IT == UART1_IT_RXNE)
2850  0019 1e01          	ldw	x,(OFST+1,sp)
2851  001b a30255        	cpw	x,#597
2852  001e 2606          	jrne	L3321
2853                     ; 782     UART1->SR = (uint8_t)~(UART1_SR_RXNE);
2855  0020 35df5230      	mov	21040,#223
2857  0024 2004          	jra	L5321
2858  0026               L3321:
2859                     ; 787     UART1->CR4 &= (uint8_t)~(UART1_CR4_LBDF);
2861  0026 72195237      	bres	21047,#4
2862  002a               L5321:
2863                     ; 789 }
2866  002a 85            	popw	x
2867  002b 81            	ret	
2880                     	xdef	_UART1_ClearITPendingBit
2881                     	xdef	_UART1_GetITStatus
2882                     	xdef	_UART1_ClearFlag
2883                     	xdef	_UART1_GetFlagStatus
2884                     	xdef	_UART1_SetPrescaler
2885                     	xdef	_UART1_SetGuardTime
2886                     	xdef	_UART1_SetAddress
2887                     	xdef	_UART1_SendBreak
2888                     	xdef	_UART1_SendData9
2889                     	xdef	_UART1_SendData8
2890                     	xdef	_UART1_ReceiveData9
2891                     	xdef	_UART1_ReceiveData8
2892                     	xdef	_UART1_ReceiverWakeUpCmd
2893                     	xdef	_UART1_WakeUpConfig
2894                     	xdef	_UART1_SmartCardNACKCmd
2895                     	xdef	_UART1_SmartCardCmd
2896                     	xdef	_UART1_LINCmd
2897                     	xdef	_UART1_LINBreakDetectionConfig
2898                     	xdef	_UART1_IrDACmd
2899                     	xdef	_UART1_IrDAConfig
2900                     	xdef	_UART1_HalfDuplexCmd
2901                     	xdef	_UART1_ITConfig
2902                     	xdef	_UART1_Cmd
2903                     	xdef	_UART1_Init
2904                     	xdef	_UART1_DeInit
2905                     	xref	_assert_failed
2906                     	xref	_CLK_GetClockFreq
2907                     	switch	.const
2908  0008               L371:
2909  0008 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
2910  001a 6965735c7374  	dc.b	"ies\stm8s_stdperip"
2911  002c 685f64726976  	dc.b	"h_driver\src\stm8s"
2912  003e 5f7561727431  	dc.b	"_uart1.c",0
2913                     	xref.b	c_lreg
2914                     	xref.b	c_x
2934                     	xref	c_lsub
2935                     	xref	c_smul
2936                     	xref	c_ludv
2937                     	xref	c_rtol
2938                     	xref	c_llsh
2939                     	xref	c_lcmp
2940                     	xref	c_ltor
2941                     	end
