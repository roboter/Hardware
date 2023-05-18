   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 52 void TIM2_DeInit(void)
  49                     ; 53 {
  51                     .text:	section	.text,new
  52  0000               _TIM2_DeInit:
  56                     ; 54   TIM2->CR1 = (uint8_t)TIM2_CR1_RESET_VALUE;
  58  0000 725f5300      	clr	21248
  59                     ; 55   TIM2->IER = (uint8_t)TIM2_IER_RESET_VALUE;
  61  0004 725f5303      	clr	21251
  62                     ; 56   TIM2->SR2 = (uint8_t)TIM2_SR2_RESET_VALUE;
  64  0008 725f5305      	clr	21253
  65                     ; 59   TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  67  000c 725f530a      	clr	21258
  68                     ; 60   TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  70  0010 725f530b      	clr	21259
  71                     ; 64   TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  73  0014 725f530a      	clr	21258
  74                     ; 65   TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  76  0018 725f530b      	clr	21259
  77                     ; 66   TIM2->CCMR1 = (uint8_t)TIM2_CCMR1_RESET_VALUE;
  79  001c 725f5307      	clr	21255
  80                     ; 67   TIM2->CCMR2 = (uint8_t)TIM2_CCMR2_RESET_VALUE;
  82  0020 725f5308      	clr	21256
  83                     ; 68   TIM2->CCMR3 = (uint8_t)TIM2_CCMR3_RESET_VALUE;
  85  0024 725f5309      	clr	21257
  86                     ; 69   TIM2->CNTRH = (uint8_t)TIM2_CNTRH_RESET_VALUE;
  88  0028 725f530c      	clr	21260
  89                     ; 70   TIM2->CNTRL = (uint8_t)TIM2_CNTRL_RESET_VALUE;
  91  002c 725f530d      	clr	21261
  92                     ; 71   TIM2->PSCR = (uint8_t)TIM2_PSCR_RESET_VALUE;
  94  0030 725f530e      	clr	21262
  95                     ; 72   TIM2->ARRH  = (uint8_t)TIM2_ARRH_RESET_VALUE;
  97  0034 35ff530f      	mov	21263,#255
  98                     ; 73   TIM2->ARRL  = (uint8_t)TIM2_ARRL_RESET_VALUE;
 100  0038 35ff5310      	mov	21264,#255
 101                     ; 74   TIM2->CCR1H = (uint8_t)TIM2_CCR1H_RESET_VALUE;
 103  003c 725f5311      	clr	21265
 104                     ; 75   TIM2->CCR1L = (uint8_t)TIM2_CCR1L_RESET_VALUE;
 106  0040 725f5312      	clr	21266
 107                     ; 76   TIM2->CCR2H = (uint8_t)TIM2_CCR2H_RESET_VALUE;
 109  0044 725f5313      	clr	21267
 110                     ; 77   TIM2->CCR2L = (uint8_t)TIM2_CCR2L_RESET_VALUE;
 112  0048 725f5314      	clr	21268
 113                     ; 78   TIM2->CCR3H = (uint8_t)TIM2_CCR3H_RESET_VALUE;
 115  004c 725f5315      	clr	21269
 116                     ; 79   TIM2->CCR3L = (uint8_t)TIM2_CCR3L_RESET_VALUE;
 118  0050 725f5316      	clr	21270
 119                     ; 80   TIM2->SR1 = (uint8_t)TIM2_SR1_RESET_VALUE;
 121  0054 725f5304      	clr	21252
 122                     ; 81 }
 125  0058 81            	ret	
 293                     ; 89 void TIM2_TimeBaseInit( TIM2_Prescaler_TypeDef TIM2_Prescaler,
 293                     ; 90                         uint16_t TIM2_Period)
 293                     ; 91 {
 294                     .text:	section	.text,new
 295  0000               _TIM2_TimeBaseInit:
 297       ffffffff      OFST: set -1
 300                     ; 93   TIM2->PSCR = (uint8_t)(TIM2_Prescaler);
 302  0000 c7530e        	ld	21262,a
 303                     ; 95   TIM2->ARRH = (uint8_t)(TIM2_Period >> 8);
 305  0003 7b03          	ld	a,(OFST+4,sp)
 306  0005 c7530f        	ld	21263,a
 307                     ; 96   TIM2->ARRL = (uint8_t)(TIM2_Period);
 309  0008 7b04          	ld	a,(OFST+5,sp)
 310  000a c75310        	ld	21264,a
 311                     ; 97 }
 314  000d 81            	ret	
 472                     ; 108 void TIM2_OC1Init(TIM2_OCMode_TypeDef TIM2_OCMode,
 472                     ; 109                   TIM2_OutputState_TypeDef TIM2_OutputState,
 472                     ; 110                   uint16_t TIM2_Pulse,
 472                     ; 111                   TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
 472                     ; 112 {
 473                     .text:	section	.text,new
 474  0000               _TIM2_OC1Init:
 476  0000 89            	pushw	x
 477  0001 88            	push	a
 478       00000001      OFST:	set	1
 481                     ; 114   assert_param(IS_TIM2_OC_MODE_OK(TIM2_OCMode));
 483  0002 9e            	ld	a,xh
 484  0003 4d            	tnz	a
 485  0004 271e          	jreq	L61
 486  0006 9e            	ld	a,xh
 487  0007 a110          	cp	a,#16
 488  0009 2719          	jreq	L61
 489  000b 9e            	ld	a,xh
 490  000c a120          	cp	a,#32
 491  000e 2714          	jreq	L61
 492  0010 9e            	ld	a,xh
 493  0011 a130          	cp	a,#48
 494  0013 270f          	jreq	L61
 495  0015 9e            	ld	a,xh
 496  0016 a160          	cp	a,#96
 497  0018 270a          	jreq	L61
 498  001a 9e            	ld	a,xh
 499  001b a170          	cp	a,#112
 500  001d 2705          	jreq	L61
 501  001f ae0072        	ldw	x,#114
 502  0022 ad4b          	call	LC001
 503  0024               L61:
 504                     ; 115   assert_param(IS_TIM2_OUTPUT_STATE_OK(TIM2_OutputState));
 506  0024 7b03          	ld	a,(OFST+2,sp)
 507  0026 2709          	jreq	L62
 508  0028 a111          	cp	a,#17
 509  002a 2705          	jreq	L62
 510  002c ae0073        	ldw	x,#115
 511  002f ad3e          	call	LC001
 512  0031               L62:
 513                     ; 116   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
 515  0031 7b08          	ld	a,(OFST+7,sp)
 516  0033 2709          	jreq	L63
 517  0035 a122          	cp	a,#34
 518  0037 2705          	jreq	L63
 519  0039 ae0074        	ldw	x,#116
 520  003c ad31          	call	LC001
 521  003e               L63:
 522                     ; 119   TIM2->CCER1 &= (uint8_t)(~( TIM2_CCER1_CC1E | TIM2_CCER1_CC1P));
 524  003e c6530a        	ld	a,21258
 525  0041 a4fc          	and	a,#252
 526  0043 c7530a        	ld	21258,a
 527                     ; 121   TIM2->CCER1 |= (uint8_t)((uint8_t)(TIM2_OutputState & TIM2_CCER1_CC1E ) | 
 527                     ; 122                            (uint8_t)(TIM2_OCPolarity & TIM2_CCER1_CC1P));
 529  0046 7b08          	ld	a,(OFST+7,sp)
 530  0048 a402          	and	a,#2
 531  004a 6b01          	ld	(OFST+0,sp),a
 533  004c 7b03          	ld	a,(OFST+2,sp)
 534  004e a401          	and	a,#1
 535  0050 1a01          	or	a,(OFST+0,sp)
 536  0052 ca530a        	or	a,21258
 537  0055 c7530a        	ld	21258,a
 538                     ; 125   TIM2->CCMR1 = (uint8_t)((uint8_t)(TIM2->CCMR1 & (uint8_t)(~TIM2_CCMR_OCM)) |
 538                     ; 126                           (uint8_t)TIM2_OCMode);
 540  0058 c65307        	ld	a,21255
 541  005b a48f          	and	a,#143
 542  005d 1a02          	or	a,(OFST+1,sp)
 543  005f c75307        	ld	21255,a
 544                     ; 129   TIM2->CCR1H = (uint8_t)(TIM2_Pulse >> 8);
 546  0062 7b06          	ld	a,(OFST+5,sp)
 547  0064 c75311        	ld	21265,a
 548                     ; 130   TIM2->CCR1L = (uint8_t)(TIM2_Pulse);
 550  0067 7b07          	ld	a,(OFST+6,sp)
 551  0069 c75312        	ld	21266,a
 552                     ; 131 }
 555  006c 5b03          	addw	sp,#3
 556  006e 81            	ret	
 557  006f               LC001:
 558  006f 89            	pushw	x
 559  0070 5f            	clrw	x
 560  0071 89            	pushw	x
 561  0072 ae0000        	ldw	x,#L702
 562  0075 cd0000        	call	_assert_failed
 564  0078 5b04          	addw	sp,#4
 565  007a 81            	ret	
 630                     ; 142 void TIM2_OC2Init(TIM2_OCMode_TypeDef TIM2_OCMode,
 630                     ; 143                   TIM2_OutputState_TypeDef TIM2_OutputState,
 630                     ; 144                   uint16_t TIM2_Pulse,
 630                     ; 145                   TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
 630                     ; 146 {
 631                     .text:	section	.text,new
 632  0000               _TIM2_OC2Init:
 634  0000 89            	pushw	x
 635  0001 88            	push	a
 636       00000001      OFST:	set	1
 639                     ; 148   assert_param(IS_TIM2_OC_MODE_OK(TIM2_OCMode));
 641  0002 9e            	ld	a,xh
 642  0003 4d            	tnz	a
 643  0004 271e          	jreq	L05
 644  0006 9e            	ld	a,xh
 645  0007 a110          	cp	a,#16
 646  0009 2719          	jreq	L05
 647  000b 9e            	ld	a,xh
 648  000c a120          	cp	a,#32
 649  000e 2714          	jreq	L05
 650  0010 9e            	ld	a,xh
 651  0011 a130          	cp	a,#48
 652  0013 270f          	jreq	L05
 653  0015 9e            	ld	a,xh
 654  0016 a160          	cp	a,#96
 655  0018 270a          	jreq	L05
 656  001a 9e            	ld	a,xh
 657  001b a170          	cp	a,#112
 658  001d 2705          	jreq	L05
 659  001f ae0094        	ldw	x,#148
 660  0022 ad4b          	call	LC002
 661  0024               L05:
 662                     ; 149   assert_param(IS_TIM2_OUTPUT_STATE_OK(TIM2_OutputState));
 664  0024 7b03          	ld	a,(OFST+2,sp)
 665  0026 2709          	jreq	L06
 666  0028 a111          	cp	a,#17
 667  002a 2705          	jreq	L06
 668  002c ae0095        	ldw	x,#149
 669  002f ad3e          	call	LC002
 670  0031               L06:
 671                     ; 150   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
 673  0031 7b08          	ld	a,(OFST+7,sp)
 674  0033 2709          	jreq	L07
 675  0035 a122          	cp	a,#34
 676  0037 2705          	jreq	L07
 677  0039 ae0096        	ldw	x,#150
 678  003c ad31          	call	LC002
 679  003e               L07:
 680                     ; 154   TIM2->CCER1 &= (uint8_t)(~( TIM2_CCER1_CC2E |  TIM2_CCER1_CC2P ));
 682  003e c6530a        	ld	a,21258
 683  0041 a4cf          	and	a,#207
 684  0043 c7530a        	ld	21258,a
 685                     ; 156   TIM2->CCER1 |= (uint8_t)((uint8_t)(TIM2_OutputState  & TIM2_CCER1_CC2E ) |
 685                     ; 157                            (uint8_t)(TIM2_OCPolarity & TIM2_CCER1_CC2P));
 687  0046 7b08          	ld	a,(OFST+7,sp)
 688  0048 a420          	and	a,#32
 689  004a 6b01          	ld	(OFST+0,sp),a
 691  004c 7b03          	ld	a,(OFST+2,sp)
 692  004e a410          	and	a,#16
 693  0050 1a01          	or	a,(OFST+0,sp)
 694  0052 ca530a        	or	a,21258
 695  0055 c7530a        	ld	21258,a
 696                     ; 161   TIM2->CCMR2 = (uint8_t)((uint8_t)(TIM2->CCMR2 & (uint8_t)(~TIM2_CCMR_OCM)) | 
 696                     ; 162                           (uint8_t)TIM2_OCMode);
 698  0058 c65308        	ld	a,21256
 699  005b a48f          	and	a,#143
 700  005d 1a02          	or	a,(OFST+1,sp)
 701  005f c75308        	ld	21256,a
 702                     ; 166   TIM2->CCR2H = (uint8_t)(TIM2_Pulse >> 8);
 704  0062 7b06          	ld	a,(OFST+5,sp)
 705  0064 c75313        	ld	21267,a
 706                     ; 167   TIM2->CCR2L = (uint8_t)(TIM2_Pulse);
 708  0067 7b07          	ld	a,(OFST+6,sp)
 709  0069 c75314        	ld	21268,a
 710                     ; 168 }
 713  006c 5b03          	addw	sp,#3
 714  006e 81            	ret	
 715  006f               LC002:
 716  006f 89            	pushw	x
 717  0070 5f            	clrw	x
 718  0071 89            	pushw	x
 719  0072 ae0000        	ldw	x,#L702
 720  0075 cd0000        	call	_assert_failed
 722  0078 5b04          	addw	sp,#4
 723  007a 81            	ret	
 788                     ; 179 void TIM2_OC3Init(TIM2_OCMode_TypeDef TIM2_OCMode,
 788                     ; 180                   TIM2_OutputState_TypeDef TIM2_OutputState,
 788                     ; 181                   uint16_t TIM2_Pulse,
 788                     ; 182                   TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
 788                     ; 183 {
 789                     .text:	section	.text,new
 790  0000               _TIM2_OC3Init:
 792  0000 89            	pushw	x
 793  0001 88            	push	a
 794       00000001      OFST:	set	1
 797                     ; 185   assert_param(IS_TIM2_OC_MODE_OK(TIM2_OCMode));
 799  0002 9e            	ld	a,xh
 800  0003 4d            	tnz	a
 801  0004 271e          	jreq	L201
 802  0006 9e            	ld	a,xh
 803  0007 a110          	cp	a,#16
 804  0009 2719          	jreq	L201
 805  000b 9e            	ld	a,xh
 806  000c a120          	cp	a,#32
 807  000e 2714          	jreq	L201
 808  0010 9e            	ld	a,xh
 809  0011 a130          	cp	a,#48
 810  0013 270f          	jreq	L201
 811  0015 9e            	ld	a,xh
 812  0016 a160          	cp	a,#96
 813  0018 270a          	jreq	L201
 814  001a 9e            	ld	a,xh
 815  001b a170          	cp	a,#112
 816  001d 2705          	jreq	L201
 817  001f ae00b9        	ldw	x,#185
 818  0022 ad4b          	call	LC003
 819  0024               L201:
 820                     ; 186   assert_param(IS_TIM2_OUTPUT_STATE_OK(TIM2_OutputState));
 822  0024 7b03          	ld	a,(OFST+2,sp)
 823  0026 2709          	jreq	L211
 824  0028 a111          	cp	a,#17
 825  002a 2705          	jreq	L211
 826  002c ae00ba        	ldw	x,#186
 827  002f ad3e          	call	LC003
 828  0031               L211:
 829                     ; 187   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
 831  0031 7b08          	ld	a,(OFST+7,sp)
 832  0033 2709          	jreq	L221
 833  0035 a122          	cp	a,#34
 834  0037 2705          	jreq	L221
 835  0039 ae00bb        	ldw	x,#187
 836  003c ad31          	call	LC003
 837  003e               L221:
 838                     ; 189   TIM2->CCER2 &= (uint8_t)(~( TIM2_CCER2_CC3E  | TIM2_CCER2_CC3P));
 840  003e c6530b        	ld	a,21259
 841  0041 a4fc          	and	a,#252
 842  0043 c7530b        	ld	21259,a
 843                     ; 191   TIM2->CCER2 |= (uint8_t)((uint8_t)(TIM2_OutputState & TIM2_CCER2_CC3E) |  
 843                     ; 192                            (uint8_t)(TIM2_OCPolarity & TIM2_CCER2_CC3P));
 845  0046 7b08          	ld	a,(OFST+7,sp)
 846  0048 a402          	and	a,#2
 847  004a 6b01          	ld	(OFST+0,sp),a
 849  004c 7b03          	ld	a,(OFST+2,sp)
 850  004e a401          	and	a,#1
 851  0050 1a01          	or	a,(OFST+0,sp)
 852  0052 ca530b        	or	a,21259
 853  0055 c7530b        	ld	21259,a
 854                     ; 195   TIM2->CCMR3 = (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~TIM2_CCMR_OCM)) |
 854                     ; 196                           (uint8_t)TIM2_OCMode);
 856  0058 c65309        	ld	a,21257
 857  005b a48f          	and	a,#143
 858  005d 1a02          	or	a,(OFST+1,sp)
 859  005f c75309        	ld	21257,a
 860                     ; 199   TIM2->CCR3H = (uint8_t)(TIM2_Pulse >> 8);
 862  0062 7b06          	ld	a,(OFST+5,sp)
 863  0064 c75315        	ld	21269,a
 864                     ; 200   TIM2->CCR3L = (uint8_t)(TIM2_Pulse);
 866  0067 7b07          	ld	a,(OFST+6,sp)
 867  0069 c75316        	ld	21270,a
 868                     ; 201 }
 871  006c 5b03          	addw	sp,#3
 872  006e 81            	ret	
 873  006f               LC003:
 874  006f 89            	pushw	x
 875  0070 5f            	clrw	x
 876  0071 89            	pushw	x
 877  0072 ae0000        	ldw	x,#L702
 878  0075 cd0000        	call	_assert_failed
 880  0078 5b04          	addw	sp,#4
 881  007a 81            	ret	
1075                     ; 212 void TIM2_ICInit(TIM2_Channel_TypeDef TIM2_Channel,
1075                     ; 213                  TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
1075                     ; 214                  TIM2_ICSelection_TypeDef TIM2_ICSelection,
1075                     ; 215                  TIM2_ICPSC_TypeDef TIM2_ICPrescaler,
1075                     ; 216                  uint8_t TIM2_ICFilter)
1075                     ; 217 {
1076                     .text:	section	.text,new
1077  0000               _TIM2_ICInit:
1079  0000 89            	pushw	x
1080       00000000      OFST:	set	0
1083                     ; 219   assert_param(IS_TIM2_CHANNEL_OK(TIM2_Channel));
1085  0001 9e            	ld	a,xh
1086  0002 4d            	tnz	a
1087  0003 270f          	jreq	L431
1088  0005 9e            	ld	a,xh
1089  0006 4a            	dec	a
1090  0007 270b          	jreq	L431
1091  0009 9e            	ld	a,xh
1092  000a a102          	cp	a,#2
1093  000c 2706          	jreq	L431
1094  000e ae00db        	ldw	x,#219
1095  0011 cd0097        	call	LC004
1096  0014               L431:
1097                     ; 220   assert_param(IS_TIM2_IC_POLARITY_OK(TIM2_ICPolarity));
1099  0014 7b02          	ld	a,(OFST+2,sp)
1100  0016 2709          	jreq	L441
1101  0018 a144          	cp	a,#68
1102  001a 2705          	jreq	L441
1103  001c ae00dc        	ldw	x,#220
1104  001f ad76          	call	LC004
1105  0021               L441:
1106                     ; 221   assert_param(IS_TIM2_IC_SELECTION_OK(TIM2_ICSelection));
1108  0021 7b05          	ld	a,(OFST+5,sp)
1109  0023 a101          	cp	a,#1
1110  0025 270d          	jreq	L451
1111  0027 a102          	cp	a,#2
1112  0029 2709          	jreq	L451
1113  002b a103          	cp	a,#3
1114  002d 2705          	jreq	L451
1115  002f ae00dd        	ldw	x,#221
1116  0032 ad63          	call	LC004
1117  0034               L451:
1118                     ; 222   assert_param(IS_TIM2_IC_PRESCALER_OK(TIM2_ICPrescaler));
1120  0034 7b06          	ld	a,(OFST+6,sp)
1121  0036 2711          	jreq	L461
1122  0038 a104          	cp	a,#4
1123  003a 270d          	jreq	L461
1124  003c a108          	cp	a,#8
1125  003e 2709          	jreq	L461
1126  0040 a10c          	cp	a,#12
1127  0042 2705          	jreq	L461
1128  0044 ae00de        	ldw	x,#222
1129  0047 ad4e          	call	LC004
1130  0049               L461:
1131                     ; 223   assert_param(IS_TIM2_IC_FILTER_OK(TIM2_ICFilter));
1133  0049 7b07          	ld	a,(OFST+7,sp)
1134  004b a110          	cp	a,#16
1135  004d 2505          	jrult	L271
1136  004f ae00df        	ldw	x,#223
1137  0052 ad43          	call	LC004
1138  0054               L271:
1139                     ; 225   if (TIM2_Channel == TIM2_CHANNEL_1)
1141  0054 7b01          	ld	a,(OFST+1,sp)
1142  0056 2614          	jrne	L304
1143                     ; 228     TI1_Config((uint8_t)TIM2_ICPolarity,
1143                     ; 229                (uint8_t)TIM2_ICSelection,
1143                     ; 230                (uint8_t)TIM2_ICFilter);
1145  0058 7b07          	ld	a,(OFST+7,sp)
1146  005a 88            	push	a
1147  005b 7b06          	ld	a,(OFST+6,sp)
1148  005d 97            	ld	xl,a
1149  005e 7b03          	ld	a,(OFST+3,sp)
1150  0060 95            	ld	xh,a
1151  0061 cd0000        	call	L3_TI1_Config
1153  0064 84            	pop	a
1154                     ; 233     TIM2_SetIC1Prescaler(TIM2_ICPrescaler);
1156  0065 7b06          	ld	a,(OFST+6,sp)
1157  0067 cd0000        	call	_TIM2_SetIC1Prescaler
1160  006a 2029          	jra	L504
1161  006c               L304:
1162                     ; 235   else if (TIM2_Channel == TIM2_CHANNEL_2)
1164  006c 4a            	dec	a
1165  006d 2614          	jrne	L704
1166                     ; 238     TI2_Config((uint8_t)TIM2_ICPolarity,
1166                     ; 239                (uint8_t)TIM2_ICSelection,
1166                     ; 240                (uint8_t)TIM2_ICFilter);
1168  006f 7b07          	ld	a,(OFST+7,sp)
1169  0071 88            	push	a
1170  0072 7b06          	ld	a,(OFST+6,sp)
1171  0074 97            	ld	xl,a
1172  0075 7b03          	ld	a,(OFST+3,sp)
1173  0077 95            	ld	xh,a
1174  0078 cd0000        	call	L5_TI2_Config
1176  007b 84            	pop	a
1177                     ; 243     TIM2_SetIC2Prescaler(TIM2_ICPrescaler);
1179  007c 7b06          	ld	a,(OFST+6,sp)
1180  007e cd0000        	call	_TIM2_SetIC2Prescaler
1183  0081 2012          	jra	L504
1184  0083               L704:
1185                     ; 248     TI3_Config((uint8_t)TIM2_ICPolarity,
1185                     ; 249                (uint8_t)TIM2_ICSelection,
1185                     ; 250                (uint8_t)TIM2_ICFilter);
1187  0083 7b07          	ld	a,(OFST+7,sp)
1188  0085 88            	push	a
1189  0086 7b06          	ld	a,(OFST+6,sp)
1190  0088 97            	ld	xl,a
1191  0089 7b03          	ld	a,(OFST+3,sp)
1192  008b 95            	ld	xh,a
1193  008c cd0000        	call	L7_TI3_Config
1195  008f 84            	pop	a
1196                     ; 253     TIM2_SetIC3Prescaler(TIM2_ICPrescaler);
1198  0090 7b06          	ld	a,(OFST+6,sp)
1199  0092 cd0000        	call	_TIM2_SetIC3Prescaler
1201  0095               L504:
1202                     ; 255 }
1205  0095 85            	popw	x
1206  0096 81            	ret	
1207  0097               LC004:
1208  0097 89            	pushw	x
1209  0098 5f            	clrw	x
1210  0099 89            	pushw	x
1211  009a ae0000        	ldw	x,#L702
1212  009d cd0000        	call	_assert_failed
1214  00a0 5b04          	addw	sp,#4
1215  00a2 81            	ret	
1312                     ; 266 void TIM2_PWMIConfig(TIM2_Channel_TypeDef TIM2_Channel,
1312                     ; 267                      TIM2_ICPolarity_TypeDef TIM2_ICPolarity,
1312                     ; 268                      TIM2_ICSelection_TypeDef TIM2_ICSelection,
1312                     ; 269                      TIM2_ICPSC_TypeDef TIM2_ICPrescaler,
1312                     ; 270                      uint8_t TIM2_ICFilter)
1312                     ; 271 {
1313                     .text:	section	.text,new
1314  0000               _TIM2_PWMIConfig:
1316  0000 89            	pushw	x
1317  0001 89            	pushw	x
1318       00000002      OFST:	set	2
1321                     ; 272   uint8_t icpolarity = (uint8_t)TIM2_ICPOLARITY_RISING;
1323                     ; 273   uint8_t icselection = (uint8_t)TIM2_ICSELECTION_DIRECTTI;
1325                     ; 276   assert_param(IS_TIM2_PWMI_CHANNEL_OK(TIM2_Channel));
1327  0002 9e            	ld	a,xh
1328  0003 4d            	tnz	a
1329  0004 270a          	jreq	L022
1330  0006 9e            	ld	a,xh
1331  0007 4a            	dec	a
1332  0008 2706          	jreq	L022
1333  000a ae0114        	ldw	x,#276
1334  000d cd00b3        	call	LC005
1335  0010               L022:
1336                     ; 277   assert_param(IS_TIM2_IC_POLARITY_OK(TIM2_ICPolarity));
1338  0010 7b04          	ld	a,(OFST+2,sp)
1339  0012 270a          	jreq	L032
1340  0014 a144          	cp	a,#68
1341  0016 2706          	jreq	L032
1342  0018 ae0115        	ldw	x,#277
1343  001b cd00b3        	call	LC005
1344  001e               L032:
1345                     ; 278   assert_param(IS_TIM2_IC_SELECTION_OK(TIM2_ICSelection));
1347  001e 7b07          	ld	a,(OFST+5,sp)
1348  0020 a101          	cp	a,#1
1349  0022 270e          	jreq	L042
1350  0024 a102          	cp	a,#2
1351  0026 270a          	jreq	L042
1352  0028 a103          	cp	a,#3
1353  002a 2706          	jreq	L042
1354  002c ae0116        	ldw	x,#278
1355  002f cd00b3        	call	LC005
1356  0032               L042:
1357                     ; 279   assert_param(IS_TIM2_IC_PRESCALER_OK(TIM2_ICPrescaler));
1359  0032 7b08          	ld	a,(OFST+6,sp)
1360  0034 2711          	jreq	L052
1361  0036 a104          	cp	a,#4
1362  0038 270d          	jreq	L052
1363  003a a108          	cp	a,#8
1364  003c 2709          	jreq	L052
1365  003e a10c          	cp	a,#12
1366  0040 2705          	jreq	L052
1367  0042 ae0117        	ldw	x,#279
1368  0045 ad6c          	call	LC005
1369  0047               L052:
1370                     ; 282   if (TIM2_ICPolarity != TIM2_ICPOLARITY_FALLING)
1372  0047 7b04          	ld	a,(OFST+2,sp)
1373  0049 a144          	cp	a,#68
1374  004b 2706          	jreq	L164
1375                     ; 284     icpolarity = (uint8_t)TIM2_ICPOLARITY_FALLING;
1377  004d a644          	ld	a,#68
1378  004f 6b01          	ld	(OFST-1,sp),a
1381  0051 2002          	jra	L364
1382  0053               L164:
1383                     ; 288     icpolarity = (uint8_t)TIM2_ICPOLARITY_RISING;
1385  0053 0f01          	clr	(OFST-1,sp)
1387  0055               L364:
1388                     ; 292   if (TIM2_ICSelection == TIM2_ICSELECTION_DIRECTTI)
1390  0055 7b07          	ld	a,(OFST+5,sp)
1391  0057 4a            	dec	a
1392  0058 2604          	jrne	L564
1393                     ; 294     icselection = (uint8_t)TIM2_ICSELECTION_INDIRECTTI;
1395  005a a602          	ld	a,#2
1397  005c 2002          	jra	L764
1398  005e               L564:
1399                     ; 298     icselection = (uint8_t)TIM2_ICSELECTION_DIRECTTI;
1401  005e a601          	ld	a,#1
1402  0060               L764:
1403  0060 6b02          	ld	(OFST+0,sp),a
1405                     ; 301   if (TIM2_Channel == TIM2_CHANNEL_1)
1407  0062 7b03          	ld	a,(OFST+1,sp)
1408  0064 2626          	jrne	L174
1409                     ; 304     TI1_Config((uint8_t)TIM2_ICPolarity, (uint8_t)TIM2_ICSelection,
1409                     ; 305                (uint8_t)TIM2_ICFilter);
1411  0066 7b09          	ld	a,(OFST+7,sp)
1412  0068 88            	push	a
1413  0069 7b08          	ld	a,(OFST+6,sp)
1414  006b 97            	ld	xl,a
1415  006c 7b05          	ld	a,(OFST+3,sp)
1416  006e 95            	ld	xh,a
1417  006f cd0000        	call	L3_TI1_Config
1419  0072 84            	pop	a
1420                     ; 308     TIM2_SetIC1Prescaler(TIM2_ICPrescaler);
1422  0073 7b08          	ld	a,(OFST+6,sp)
1423  0075 cd0000        	call	_TIM2_SetIC1Prescaler
1425                     ; 311     TI2_Config(icpolarity, icselection, TIM2_ICFilter);
1427  0078 7b09          	ld	a,(OFST+7,sp)
1428  007a 88            	push	a
1429  007b 7b03          	ld	a,(OFST+1,sp)
1430  007d 97            	ld	xl,a
1431  007e 7b02          	ld	a,(OFST+0,sp)
1432  0080 95            	ld	xh,a
1433  0081 cd0000        	call	L5_TI2_Config
1435  0084 84            	pop	a
1436                     ; 314     TIM2_SetIC2Prescaler(TIM2_ICPrescaler);
1438  0085 7b08          	ld	a,(OFST+6,sp)
1439  0087 cd0000        	call	_TIM2_SetIC2Prescaler
1442  008a 2024          	jra	L374
1443  008c               L174:
1444                     ; 319     TI2_Config((uint8_t)TIM2_ICPolarity, (uint8_t)TIM2_ICSelection,
1444                     ; 320                (uint8_t)TIM2_ICFilter);
1446  008c 7b09          	ld	a,(OFST+7,sp)
1447  008e 88            	push	a
1448  008f 7b08          	ld	a,(OFST+6,sp)
1449  0091 97            	ld	xl,a
1450  0092 7b05          	ld	a,(OFST+3,sp)
1451  0094 95            	ld	xh,a
1452  0095 cd0000        	call	L5_TI2_Config
1454  0098 84            	pop	a
1455                     ; 323     TIM2_SetIC2Prescaler(TIM2_ICPrescaler);
1457  0099 7b08          	ld	a,(OFST+6,sp)
1458  009b cd0000        	call	_TIM2_SetIC2Prescaler
1460                     ; 326     TI1_Config((uint8_t)icpolarity, icselection, (uint8_t)TIM2_ICFilter);
1462  009e 7b09          	ld	a,(OFST+7,sp)
1463  00a0 88            	push	a
1464  00a1 7b03          	ld	a,(OFST+1,sp)
1465  00a3 97            	ld	xl,a
1466  00a4 7b02          	ld	a,(OFST+0,sp)
1467  00a6 95            	ld	xh,a
1468  00a7 cd0000        	call	L3_TI1_Config
1470  00aa 84            	pop	a
1471                     ; 329     TIM2_SetIC1Prescaler(TIM2_ICPrescaler);
1473  00ab 7b08          	ld	a,(OFST+6,sp)
1474  00ad cd0000        	call	_TIM2_SetIC1Prescaler
1476  00b0               L374:
1477                     ; 331 }
1480  00b0 5b04          	addw	sp,#4
1481  00b2 81            	ret	
1482  00b3               LC005:
1483  00b3 89            	pushw	x
1484  00b4 5f            	clrw	x
1485  00b5 89            	pushw	x
1486  00b6 ae0000        	ldw	x,#L702
1487  00b9 cd0000        	call	_assert_failed
1489  00bc 5b04          	addw	sp,#4
1490  00be 81            	ret	
1546                     ; 339 void TIM2_Cmd(FunctionalState NewState)
1546                     ; 340 {
1547                     .text:	section	.text,new
1548  0000               _TIM2_Cmd:
1550  0000 88            	push	a
1551       00000000      OFST:	set	0
1554                     ; 342   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1556  0001 4d            	tnz	a
1557  0002 2711          	jreq	L203
1558  0004 4a            	dec	a
1559  0005 270e          	jreq	L203
1560  0007 ae0156        	ldw	x,#342
1561  000a 89            	pushw	x
1562  000b 5f            	clrw	x
1563  000c 89            	pushw	x
1564  000d ae0000        	ldw	x,#L702
1565  0010 cd0000        	call	_assert_failed
1567  0013 5b04          	addw	sp,#4
1568  0015               L203:
1569                     ; 345   if (NewState != DISABLE)
1571  0015 7b01          	ld	a,(OFST+1,sp)
1572  0017 2706          	jreq	L325
1573                     ; 347     TIM2->CR1 |= (uint8_t)TIM2_CR1_CEN;
1575  0019 72105300      	bset	21248,#0
1577  001d 2004          	jra	L525
1578  001f               L325:
1579                     ; 351     TIM2->CR1 &= (uint8_t)(~TIM2_CR1_CEN);
1581  001f 72115300      	bres	21248,#0
1582  0023               L525:
1583                     ; 353 }
1586  0023 84            	pop	a
1587  0024 81            	ret	
1667                     ; 368 void TIM2_ITConfig(TIM2_IT_TypeDef TIM2_IT, FunctionalState NewState)
1667                     ; 369 {
1668                     .text:	section	.text,new
1669  0000               _TIM2_ITConfig:
1671  0000 89            	pushw	x
1672       00000000      OFST:	set	0
1675                     ; 371   assert_param(IS_TIM2_IT_OK(TIM2_IT));
1677  0001 9e            	ld	a,xh
1678  0002 4d            	tnz	a
1679  0003 2705          	jreq	L013
1680  0005 9e            	ld	a,xh
1681  0006 a110          	cp	a,#16
1682  0008 2505          	jrult	L213
1683  000a               L013:
1684  000a ae0173        	ldw	x,#371
1685  000d ad22          	call	LC006
1686  000f               L213:
1687                     ; 372   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1689  000f 7b02          	ld	a,(OFST+2,sp)
1690  0011 2708          	jreq	L223
1691  0013 4a            	dec	a
1692  0014 2705          	jreq	L223
1693  0016 ae0174        	ldw	x,#372
1694  0019 ad16          	call	LC006
1695  001b               L223:
1696                     ; 374   if (NewState != DISABLE)
1698  001b 7b02          	ld	a,(OFST+2,sp)
1699  001d 2707          	jreq	L565
1700                     ; 377     TIM2->IER |= (uint8_t)TIM2_IT;
1702  001f c65303        	ld	a,21251
1703  0022 1a01          	or	a,(OFST+1,sp)
1705  0024 2006          	jra	L765
1706  0026               L565:
1707                     ; 382     TIM2->IER &= (uint8_t)(~TIM2_IT);
1709  0026 7b01          	ld	a,(OFST+1,sp)
1710  0028 43            	cpl	a
1711  0029 c45303        	and	a,21251
1712  002c               L765:
1713  002c c75303        	ld	21251,a
1714                     ; 384 }
1717  002f 85            	popw	x
1718  0030 81            	ret	
1719  0031               LC006:
1720  0031 89            	pushw	x
1721  0032 5f            	clrw	x
1722  0033 89            	pushw	x
1723  0034 ae0000        	ldw	x,#L702
1724  0037 cd0000        	call	_assert_failed
1726  003a 5b04          	addw	sp,#4
1727  003c 81            	ret	
1764                     ; 392 void TIM2_UpdateDisableConfig(FunctionalState NewState)
1764                     ; 393 {
1765                     .text:	section	.text,new
1766  0000               _TIM2_UpdateDisableConfig:
1768  0000 88            	push	a
1769       00000000      OFST:	set	0
1772                     ; 395   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1774  0001 4d            	tnz	a
1775  0002 2711          	jreq	L433
1776  0004 4a            	dec	a
1777  0005 270e          	jreq	L433
1778  0007 ae018b        	ldw	x,#395
1779  000a 89            	pushw	x
1780  000b 5f            	clrw	x
1781  000c 89            	pushw	x
1782  000d ae0000        	ldw	x,#L702
1783  0010 cd0000        	call	_assert_failed
1785  0013 5b04          	addw	sp,#4
1786  0015               L433:
1787                     ; 398   if (NewState != DISABLE)
1789  0015 7b01          	ld	a,(OFST+1,sp)
1790  0017 2706          	jreq	L706
1791                     ; 400     TIM2->CR1 |= (uint8_t)TIM2_CR1_UDIS;
1793  0019 72125300      	bset	21248,#1
1795  001d 2004          	jra	L116
1796  001f               L706:
1797                     ; 404     TIM2->CR1 &= (uint8_t)(~TIM2_CR1_UDIS);
1799  001f 72135300      	bres	21248,#1
1800  0023               L116:
1801                     ; 406 }
1804  0023 84            	pop	a
1805  0024 81            	ret	
1864                     ; 416 void TIM2_UpdateRequestConfig(TIM2_UpdateSource_TypeDef TIM2_UpdateSource)
1864                     ; 417 {
1865                     .text:	section	.text,new
1866  0000               _TIM2_UpdateRequestConfig:
1868  0000 88            	push	a
1869       00000000      OFST:	set	0
1872                     ; 419   assert_param(IS_TIM2_UPDATE_SOURCE_OK(TIM2_UpdateSource));
1874  0001 4d            	tnz	a
1875  0002 2711          	jreq	L643
1876  0004 4a            	dec	a
1877  0005 270e          	jreq	L643
1878  0007 ae01a3        	ldw	x,#419
1879  000a 89            	pushw	x
1880  000b 5f            	clrw	x
1881  000c 89            	pushw	x
1882  000d ae0000        	ldw	x,#L702
1883  0010 cd0000        	call	_assert_failed
1885  0013 5b04          	addw	sp,#4
1886  0015               L643:
1887                     ; 422   if (TIM2_UpdateSource != TIM2_UPDATESOURCE_GLOBAL)
1889  0015 7b01          	ld	a,(OFST+1,sp)
1890  0017 2706          	jreq	L146
1891                     ; 424     TIM2->CR1 |= (uint8_t)TIM2_CR1_URS;
1893  0019 72145300      	bset	21248,#2
1895  001d 2004          	jra	L346
1896  001f               L146:
1897                     ; 428     TIM2->CR1 &= (uint8_t)(~TIM2_CR1_URS);
1899  001f 72155300      	bres	21248,#2
1900  0023               L346:
1901                     ; 430 }
1904  0023 84            	pop	a
1905  0024 81            	ret	
1963                     ; 440 void TIM2_SelectOnePulseMode(TIM2_OPMode_TypeDef TIM2_OPMode)
1963                     ; 441 {
1964                     .text:	section	.text,new
1965  0000               _TIM2_SelectOnePulseMode:
1967  0000 88            	push	a
1968       00000000      OFST:	set	0
1971                     ; 443   assert_param(IS_TIM2_OPM_MODE_OK(TIM2_OPMode));
1973  0001 a101          	cp	a,#1
1974  0003 2711          	jreq	L063
1975  0005 4d            	tnz	a
1976  0006 270e          	jreq	L063
1977  0008 ae01bb        	ldw	x,#443
1978  000b 89            	pushw	x
1979  000c 5f            	clrw	x
1980  000d 89            	pushw	x
1981  000e ae0000        	ldw	x,#L702
1982  0011 cd0000        	call	_assert_failed
1984  0014 5b04          	addw	sp,#4
1985  0016               L063:
1986                     ; 446   if (TIM2_OPMode != TIM2_OPMODE_REPETITIVE)
1988  0016 7b01          	ld	a,(OFST+1,sp)
1989  0018 2706          	jreq	L376
1990                     ; 448     TIM2->CR1 |= (uint8_t)TIM2_CR1_OPM;
1992  001a 72165300      	bset	21248,#3
1994  001e 2004          	jra	L576
1995  0020               L376:
1996                     ; 452     TIM2->CR1 &= (uint8_t)(~TIM2_CR1_OPM);
1998  0020 72175300      	bres	21248,#3
1999  0024               L576:
2000                     ; 454 }
2003  0024 84            	pop	a
2004  0025 81            	ret	
2073                     ; 484 void TIM2_PrescalerConfig(TIM2_Prescaler_TypeDef Prescaler,
2073                     ; 485                           TIM2_PSCReloadMode_TypeDef TIM2_PSCReloadMode)
2073                     ; 486 {
2074                     .text:	section	.text,new
2075  0000               _TIM2_PrescalerConfig:
2077  0000 89            	pushw	x
2078       00000000      OFST:	set	0
2081                     ; 488   assert_param(IS_TIM2_PRESCALER_RELOAD_OK(TIM2_PSCReloadMode));
2083  0001 9f            	ld	a,xl
2084  0002 4d            	tnz	a
2085  0003 2709          	jreq	L273
2086  0005 9f            	ld	a,xl
2087  0006 4a            	dec	a
2088  0007 2705          	jreq	L273
2089  0009 ae01e8        	ldw	x,#488
2090  000c ad51          	call	LC007
2091  000e               L273:
2092                     ; 489   assert_param(IS_TIM2_PRESCALER_OK(Prescaler));
2094  000e 7b01          	ld	a,(OFST+1,sp)
2095  0010 2743          	jreq	L204
2096  0012 a101          	cp	a,#1
2097  0014 273f          	jreq	L204
2098  0016 a102          	cp	a,#2
2099  0018 273b          	jreq	L204
2100  001a a103          	cp	a,#3
2101  001c 2737          	jreq	L204
2102  001e a104          	cp	a,#4
2103  0020 2733          	jreq	L204
2104  0022 a105          	cp	a,#5
2105  0024 272f          	jreq	L204
2106  0026 a106          	cp	a,#6
2107  0028 272b          	jreq	L204
2108  002a a107          	cp	a,#7
2109  002c 2727          	jreq	L204
2110  002e a108          	cp	a,#8
2111  0030 2723          	jreq	L204
2112  0032 a109          	cp	a,#9
2113  0034 271f          	jreq	L204
2114  0036 a10a          	cp	a,#10
2115  0038 271b          	jreq	L204
2116  003a a10b          	cp	a,#11
2117  003c 2717          	jreq	L204
2118  003e a10c          	cp	a,#12
2119  0040 2713          	jreq	L204
2120  0042 a10d          	cp	a,#13
2121  0044 270f          	jreq	L204
2122  0046 a10e          	cp	a,#14
2123  0048 270b          	jreq	L204
2124  004a a10f          	cp	a,#15
2125  004c 2707          	jreq	L204
2126  004e ae01e9        	ldw	x,#489
2127  0051 ad0c          	call	LC007
2128  0053 7b01          	ld	a,(OFST+1,sp)
2129  0055               L204:
2130                     ; 492   TIM2->PSCR = (uint8_t)Prescaler;
2132  0055 c7530e        	ld	21262,a
2133                     ; 495   TIM2->EGR = (uint8_t)TIM2_PSCReloadMode;
2135  0058 7b02          	ld	a,(OFST+2,sp)
2136  005a c75306        	ld	21254,a
2137                     ; 496 }
2140  005d 85            	popw	x
2141  005e 81            	ret	
2142  005f               LC007:
2143  005f 89            	pushw	x
2144  0060 5f            	clrw	x
2145  0061 89            	pushw	x
2146  0062 ae0000        	ldw	x,#L702
2147  0065 cd0000        	call	_assert_failed
2149  0068 5b04          	addw	sp,#4
2150  006a 81            	ret	
2209                     ; 507 void TIM2_ForcedOC1Config(TIM2_ForcedAction_TypeDef TIM2_ForcedAction)
2209                     ; 508 {
2210                     .text:	section	.text,new
2211  0000               _TIM2_ForcedOC1Config:
2213  0000 88            	push	a
2214       00000000      OFST:	set	0
2217                     ; 510   assert_param(IS_TIM2_FORCED_ACTION_OK(TIM2_ForcedAction));
2219  0001 a150          	cp	a,#80
2220  0003 2712          	jreq	L414
2221  0005 a140          	cp	a,#64
2222  0007 270e          	jreq	L414
2223  0009 ae01fe        	ldw	x,#510
2224  000c 89            	pushw	x
2225  000d 5f            	clrw	x
2226  000e 89            	pushw	x
2227  000f ae0000        	ldw	x,#L702
2228  0012 cd0000        	call	_assert_failed
2230  0015 5b04          	addw	sp,#4
2231  0017               L414:
2232                     ; 513   TIM2->CCMR1  =  (uint8_t)((uint8_t)(TIM2->CCMR1 & (uint8_t)(~TIM2_CCMR_OCM))  
2232                     ; 514                             | (uint8_t)TIM2_ForcedAction);
2234  0017 c65307        	ld	a,21255
2235  001a a48f          	and	a,#143
2236  001c 1a01          	or	a,(OFST+1,sp)
2237  001e c75307        	ld	21255,a
2238                     ; 515 }
2241  0021 84            	pop	a
2242  0022 81            	ret	
2279                     ; 526 void TIM2_ForcedOC2Config(TIM2_ForcedAction_TypeDef TIM2_ForcedAction)
2279                     ; 527 {
2280                     .text:	section	.text,new
2281  0000               _TIM2_ForcedOC2Config:
2283  0000 88            	push	a
2284       00000000      OFST:	set	0
2287                     ; 529   assert_param(IS_TIM2_FORCED_ACTION_OK(TIM2_ForcedAction));
2289  0001 a150          	cp	a,#80
2290  0003 2712          	jreq	L624
2291  0005 a140          	cp	a,#64
2292  0007 270e          	jreq	L624
2293  0009 ae0211        	ldw	x,#529
2294  000c 89            	pushw	x
2295  000d 5f            	clrw	x
2296  000e 89            	pushw	x
2297  000f ae0000        	ldw	x,#L702
2298  0012 cd0000        	call	_assert_failed
2300  0015 5b04          	addw	sp,#4
2301  0017               L624:
2302                     ; 532   TIM2->CCMR2 = (uint8_t)((uint8_t)(TIM2->CCMR2 & (uint8_t)(~TIM2_CCMR_OCM))  
2302                     ; 533                           | (uint8_t)TIM2_ForcedAction);
2304  0017 c65308        	ld	a,21256
2305  001a a48f          	and	a,#143
2306  001c 1a01          	or	a,(OFST+1,sp)
2307  001e c75308        	ld	21256,a
2308                     ; 534 }
2311  0021 84            	pop	a
2312  0022 81            	ret	
2349                     ; 545 void TIM2_ForcedOC3Config(TIM2_ForcedAction_TypeDef TIM2_ForcedAction)
2349                     ; 546 {
2350                     .text:	section	.text,new
2351  0000               _TIM2_ForcedOC3Config:
2353  0000 88            	push	a
2354       00000000      OFST:	set	0
2357                     ; 548   assert_param(IS_TIM2_FORCED_ACTION_OK(TIM2_ForcedAction));
2359  0001 a150          	cp	a,#80
2360  0003 2712          	jreq	L044
2361  0005 a140          	cp	a,#64
2362  0007 270e          	jreq	L044
2363  0009 ae0224        	ldw	x,#548
2364  000c 89            	pushw	x
2365  000d 5f            	clrw	x
2366  000e 89            	pushw	x
2367  000f ae0000        	ldw	x,#L702
2368  0012 cd0000        	call	_assert_failed
2370  0015 5b04          	addw	sp,#4
2371  0017               L044:
2372                     ; 551   TIM2->CCMR3  =  (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~TIM2_CCMR_OCM))
2372                     ; 552                             | (uint8_t)TIM2_ForcedAction);
2374  0017 c65309        	ld	a,21257
2375  001a a48f          	and	a,#143
2376  001c 1a01          	or	a,(OFST+1,sp)
2377  001e c75309        	ld	21257,a
2378                     ; 553 }
2381  0021 84            	pop	a
2382  0022 81            	ret	
2419                     ; 561 void TIM2_ARRPreloadConfig(FunctionalState NewState)
2419                     ; 562 {
2420                     .text:	section	.text,new
2421  0000               _TIM2_ARRPreloadConfig:
2423  0000 88            	push	a
2424       00000000      OFST:	set	0
2427                     ; 564   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2429  0001 4d            	tnz	a
2430  0002 2711          	jreq	L254
2431  0004 4a            	dec	a
2432  0005 270e          	jreq	L254
2433  0007 ae0234        	ldw	x,#564
2434  000a 89            	pushw	x
2435  000b 5f            	clrw	x
2436  000c 89            	pushw	x
2437  000d ae0000        	ldw	x,#L702
2438  0010 cd0000        	call	_assert_failed
2440  0013 5b04          	addw	sp,#4
2441  0015               L254:
2442                     ; 567   if (NewState != DISABLE)
2444  0015 7b01          	ld	a,(OFST+1,sp)
2445  0017 2706          	jreq	L1301
2446                     ; 569     TIM2->CR1 |= (uint8_t)TIM2_CR1_ARPE;
2448  0019 721e5300      	bset	21248,#7
2450  001d 2004          	jra	L3301
2451  001f               L1301:
2452                     ; 573     TIM2->CR1 &= (uint8_t)(~TIM2_CR1_ARPE);
2454  001f 721f5300      	bres	21248,#7
2455  0023               L3301:
2456                     ; 575 }
2459  0023 84            	pop	a
2460  0024 81            	ret	
2497                     ; 583 void TIM2_OC1PreloadConfig(FunctionalState NewState)
2497                     ; 584 {
2498                     .text:	section	.text,new
2499  0000               _TIM2_OC1PreloadConfig:
2501  0000 88            	push	a
2502       00000000      OFST:	set	0
2505                     ; 586   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2507  0001 4d            	tnz	a
2508  0002 2711          	jreq	L464
2509  0004 4a            	dec	a
2510  0005 270e          	jreq	L464
2511  0007 ae024a        	ldw	x,#586
2512  000a 89            	pushw	x
2513  000b 5f            	clrw	x
2514  000c 89            	pushw	x
2515  000d ae0000        	ldw	x,#L702
2516  0010 cd0000        	call	_assert_failed
2518  0013 5b04          	addw	sp,#4
2519  0015               L464:
2520                     ; 589   if (NewState != DISABLE)
2522  0015 7b01          	ld	a,(OFST+1,sp)
2523  0017 2706          	jreq	L3501
2524                     ; 591     TIM2->CCMR1 |= (uint8_t)TIM2_CCMR_OCxPE;
2526  0019 72165307      	bset	21255,#3
2528  001d 2004          	jra	L5501
2529  001f               L3501:
2530                     ; 595     TIM2->CCMR1 &= (uint8_t)(~TIM2_CCMR_OCxPE);
2532  001f 72175307      	bres	21255,#3
2533  0023               L5501:
2534                     ; 597 }
2537  0023 84            	pop	a
2538  0024 81            	ret	
2575                     ; 605 void TIM2_OC2PreloadConfig(FunctionalState NewState)
2575                     ; 606 {
2576                     .text:	section	.text,new
2577  0000               _TIM2_OC2PreloadConfig:
2579  0000 88            	push	a
2580       00000000      OFST:	set	0
2583                     ; 608   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2585  0001 4d            	tnz	a
2586  0002 2711          	jreq	L674
2587  0004 4a            	dec	a
2588  0005 270e          	jreq	L674
2589  0007 ae0260        	ldw	x,#608
2590  000a 89            	pushw	x
2591  000b 5f            	clrw	x
2592  000c 89            	pushw	x
2593  000d ae0000        	ldw	x,#L702
2594  0010 cd0000        	call	_assert_failed
2596  0013 5b04          	addw	sp,#4
2597  0015               L674:
2598                     ; 611   if (NewState != DISABLE)
2600  0015 7b01          	ld	a,(OFST+1,sp)
2601  0017 2706          	jreq	L5701
2602                     ; 613     TIM2->CCMR2 |= (uint8_t)TIM2_CCMR_OCxPE;
2604  0019 72165308      	bset	21256,#3
2606  001d 2004          	jra	L7701
2607  001f               L5701:
2608                     ; 617     TIM2->CCMR2 &= (uint8_t)(~TIM2_CCMR_OCxPE);
2610  001f 72175308      	bres	21256,#3
2611  0023               L7701:
2612                     ; 619 }
2615  0023 84            	pop	a
2616  0024 81            	ret	
2653                     ; 627 void TIM2_OC3PreloadConfig(FunctionalState NewState)
2653                     ; 628 {
2654                     .text:	section	.text,new
2655  0000               _TIM2_OC3PreloadConfig:
2657  0000 88            	push	a
2658       00000000      OFST:	set	0
2661                     ; 630   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2663  0001 4d            	tnz	a
2664  0002 2711          	jreq	L015
2665  0004 4a            	dec	a
2666  0005 270e          	jreq	L015
2667  0007 ae0276        	ldw	x,#630
2668  000a 89            	pushw	x
2669  000b 5f            	clrw	x
2670  000c 89            	pushw	x
2671  000d ae0000        	ldw	x,#L702
2672  0010 cd0000        	call	_assert_failed
2674  0013 5b04          	addw	sp,#4
2675  0015               L015:
2676                     ; 633   if (NewState != DISABLE)
2678  0015 7b01          	ld	a,(OFST+1,sp)
2679  0017 2706          	jreq	L7111
2680                     ; 635     TIM2->CCMR3 |= (uint8_t)TIM2_CCMR_OCxPE;
2682  0019 72165309      	bset	21257,#3
2684  001d 2004          	jra	L1211
2685  001f               L7111:
2686                     ; 639     TIM2->CCMR3 &= (uint8_t)(~TIM2_CCMR_OCxPE);
2688  001f 72175309      	bres	21257,#3
2689  0023               L1211:
2690                     ; 641 }
2693  0023 84            	pop	a
2694  0024 81            	ret	
2768                     ; 653 void TIM2_GenerateEvent(TIM2_EventSource_TypeDef TIM2_EventSource)
2768                     ; 654 {
2769                     .text:	section	.text,new
2770  0000               _TIM2_GenerateEvent:
2772  0000 88            	push	a
2773       00000000      OFST:	set	0
2776                     ; 656   assert_param(IS_TIM2_EVENT_SOURCE_OK(TIM2_EventSource));
2778  0001 4d            	tnz	a
2779  0002 260e          	jrne	L025
2780  0004 ae0290        	ldw	x,#656
2781  0007 89            	pushw	x
2782  0008 5f            	clrw	x
2783  0009 89            	pushw	x
2784  000a ae0000        	ldw	x,#L702
2785  000d cd0000        	call	_assert_failed
2787  0010 5b04          	addw	sp,#4
2788  0012               L025:
2789                     ; 659   TIM2->EGR = (uint8_t)TIM2_EventSource;
2791  0012 7b01          	ld	a,(OFST+1,sp)
2792  0014 c75306        	ld	21254,a
2793                     ; 660 }
2796  0017 84            	pop	a
2797  0018 81            	ret	
2834                     ; 670 void TIM2_OC1PolarityConfig(TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
2834                     ; 671 {
2835                     .text:	section	.text,new
2836  0000               _TIM2_OC1PolarityConfig:
2838  0000 88            	push	a
2839       00000000      OFST:	set	0
2842                     ; 673   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
2844  0001 4d            	tnz	a
2845  0002 2712          	jreq	L235
2846  0004 a122          	cp	a,#34
2847  0006 270e          	jreq	L235
2848  0008 ae02a1        	ldw	x,#673
2849  000b 89            	pushw	x
2850  000c 5f            	clrw	x
2851  000d 89            	pushw	x
2852  000e ae0000        	ldw	x,#L702
2853  0011 cd0000        	call	_assert_failed
2855  0014 5b04          	addw	sp,#4
2856  0016               L235:
2857                     ; 676   if (TIM2_OCPolarity != TIM2_OCPOLARITY_HIGH)
2859  0016 7b01          	ld	a,(OFST+1,sp)
2860  0018 2706          	jreq	L3711
2861                     ; 678     TIM2->CCER1 |= (uint8_t)TIM2_CCER1_CC1P;
2863  001a 7212530a      	bset	21258,#1
2865  001e 2004          	jra	L5711
2866  0020               L3711:
2867                     ; 682     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC1P);
2869  0020 7213530a      	bres	21258,#1
2870  0024               L5711:
2871                     ; 684 }
2874  0024 84            	pop	a
2875  0025 81            	ret	
2912                     ; 694 void TIM2_OC2PolarityConfig(TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
2912                     ; 695 {
2913                     .text:	section	.text,new
2914  0000               _TIM2_OC2PolarityConfig:
2916  0000 88            	push	a
2917       00000000      OFST:	set	0
2920                     ; 697   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
2922  0001 4d            	tnz	a
2923  0002 2712          	jreq	L445
2924  0004 a122          	cp	a,#34
2925  0006 270e          	jreq	L445
2926  0008 ae02b9        	ldw	x,#697
2927  000b 89            	pushw	x
2928  000c 5f            	clrw	x
2929  000d 89            	pushw	x
2930  000e ae0000        	ldw	x,#L702
2931  0011 cd0000        	call	_assert_failed
2933  0014 5b04          	addw	sp,#4
2934  0016               L445:
2935                     ; 700   if (TIM2_OCPolarity != TIM2_OCPOLARITY_HIGH)
2937  0016 7b01          	ld	a,(OFST+1,sp)
2938  0018 2706          	jreq	L5121
2939                     ; 702     TIM2->CCER1 |= TIM2_CCER1_CC2P;
2941  001a 721a530a      	bset	21258,#5
2943  001e 2004          	jra	L7121
2944  0020               L5121:
2945                     ; 706     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC2P);
2947  0020 721b530a      	bres	21258,#5
2948  0024               L7121:
2949                     ; 708 }
2952  0024 84            	pop	a
2953  0025 81            	ret	
2990                     ; 718 void TIM2_OC3PolarityConfig(TIM2_OCPolarity_TypeDef TIM2_OCPolarity)
2990                     ; 719 {
2991                     .text:	section	.text,new
2992  0000               _TIM2_OC3PolarityConfig:
2994  0000 88            	push	a
2995       00000000      OFST:	set	0
2998                     ; 721   assert_param(IS_TIM2_OC_POLARITY_OK(TIM2_OCPolarity));
3000  0001 4d            	tnz	a
3001  0002 2712          	jreq	L655
3002  0004 a122          	cp	a,#34
3003  0006 270e          	jreq	L655
3004  0008 ae02d1        	ldw	x,#721
3005  000b 89            	pushw	x
3006  000c 5f            	clrw	x
3007  000d 89            	pushw	x
3008  000e ae0000        	ldw	x,#L702
3009  0011 cd0000        	call	_assert_failed
3011  0014 5b04          	addw	sp,#4
3012  0016               L655:
3013                     ; 724   if (TIM2_OCPolarity != TIM2_OCPOLARITY_HIGH)
3015  0016 7b01          	ld	a,(OFST+1,sp)
3016  0018 2706          	jreq	L7321
3017                     ; 726     TIM2->CCER2 |= (uint8_t)TIM2_CCER2_CC3P;
3019  001a 7212530b      	bset	21259,#1
3021  001e 2004          	jra	L1421
3022  0020               L7321:
3023                     ; 730     TIM2->CCER2 &= (uint8_t)(~TIM2_CCER2_CC3P);
3025  0020 7213530b      	bres	21259,#1
3026  0024               L1421:
3027                     ; 732 }
3030  0024 84            	pop	a
3031  0025 81            	ret	
3077                     ; 745 void TIM2_CCxCmd(TIM2_Channel_TypeDef TIM2_Channel, FunctionalState NewState)
3077                     ; 746 {
3078                     .text:	section	.text,new
3079  0000               _TIM2_CCxCmd:
3081  0000 89            	pushw	x
3082       00000000      OFST:	set	0
3085                     ; 748   assert_param(IS_TIM2_CHANNEL_OK(TIM2_Channel));
3087  0001 9e            	ld	a,xh
3088  0002 4d            	tnz	a
3089  0003 270e          	jreq	L075
3090  0005 9e            	ld	a,xh
3091  0006 4a            	dec	a
3092  0007 270a          	jreq	L075
3093  0009 9e            	ld	a,xh
3094  000a a102          	cp	a,#2
3095  000c 2705          	jreq	L075
3096  000e ae02ec        	ldw	x,#748
3097  0011 ad43          	call	LC008
3098  0013               L075:
3099                     ; 749   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
3101  0013 7b02          	ld	a,(OFST+2,sp)
3102  0015 2708          	jreq	L006
3103  0017 4a            	dec	a
3104  0018 2705          	jreq	L006
3105  001a ae02ed        	ldw	x,#749
3106  001d ad37          	call	LC008
3107  001f               L006:
3108                     ; 751   if (TIM2_Channel == TIM2_CHANNEL_1)
3110  001f 7b01          	ld	a,(OFST+1,sp)
3111  0021 2610          	jrne	L5621
3112                     ; 754     if (NewState != DISABLE)
3114  0023 7b02          	ld	a,(OFST+2,sp)
3115  0025 2706          	jreq	L7621
3116                     ; 756       TIM2->CCER1 |= (uint8_t)TIM2_CCER1_CC1E;
3118  0027 7210530a      	bset	21258,#0
3120  002b 2027          	jra	L3721
3121  002d               L7621:
3122                     ; 760       TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC1E);
3124  002d 7211530a      	bres	21258,#0
3125  0031 2021          	jra	L3721
3126  0033               L5621:
3127                     ; 764   else if (TIM2_Channel == TIM2_CHANNEL_2)
3129  0033 4a            	dec	a
3130  0034 2610          	jrne	L5721
3131                     ; 767     if (NewState != DISABLE)
3133  0036 7b02          	ld	a,(OFST+2,sp)
3134  0038 2706          	jreq	L7721
3135                     ; 769       TIM2->CCER1 |= (uint8_t)TIM2_CCER1_CC2E;
3137  003a 7218530a      	bset	21258,#4
3139  003e 2014          	jra	L3721
3140  0040               L7721:
3141                     ; 773       TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC2E);
3143  0040 7219530a      	bres	21258,#4
3144  0044 200e          	jra	L3721
3145  0046               L5721:
3146                     ; 779     if (NewState != DISABLE)
3148  0046 7b02          	ld	a,(OFST+2,sp)
3149  0048 2706          	jreq	L5031
3150                     ; 781       TIM2->CCER2 |= (uint8_t)TIM2_CCER2_CC3E;
3152  004a 7210530b      	bset	21259,#0
3154  004e 2004          	jra	L3721
3155  0050               L5031:
3156                     ; 785       TIM2->CCER2 &= (uint8_t)(~TIM2_CCER2_CC3E);
3158  0050 7211530b      	bres	21259,#0
3159  0054               L3721:
3160                     ; 788 }
3163  0054 85            	popw	x
3164  0055 81            	ret	
3165  0056               LC008:
3166  0056 89            	pushw	x
3167  0057 5f            	clrw	x
3168  0058 89            	pushw	x
3169  0059 ae0000        	ldw	x,#L702
3170  005c cd0000        	call	_assert_failed
3172  005f 5b04          	addw	sp,#4
3173  0061 81            	ret	
3219                     ; 810 void TIM2_SelectOCxM(TIM2_Channel_TypeDef TIM2_Channel, TIM2_OCMode_TypeDef TIM2_OCMode)
3219                     ; 811 {
3220                     .text:	section	.text,new
3221  0000               _TIM2_SelectOCxM:
3223  0000 89            	pushw	x
3224       00000000      OFST:	set	0
3227                     ; 813   assert_param(IS_TIM2_CHANNEL_OK(TIM2_Channel));
3229  0001 9e            	ld	a,xh
3230  0002 4d            	tnz	a
3231  0003 270e          	jreq	L216
3232  0005 9e            	ld	a,xh
3233  0006 4a            	dec	a
3234  0007 270a          	jreq	L216
3235  0009 9e            	ld	a,xh
3236  000a a102          	cp	a,#2
3237  000c 2705          	jreq	L216
3238  000e ae032d        	ldw	x,#813
3239  0011 ad5c          	call	LC009
3240  0013               L216:
3241                     ; 814   assert_param(IS_TIM2_OCM_OK(TIM2_OCMode));
3243  0013 7b02          	ld	a,(OFST+2,sp)
3244  0015 2721          	jreq	L226
3245  0017 a110          	cp	a,#16
3246  0019 271d          	jreq	L226
3247  001b a120          	cp	a,#32
3248  001d 2719          	jreq	L226
3249  001f a130          	cp	a,#48
3250  0021 2715          	jreq	L226
3251  0023 a160          	cp	a,#96
3252  0025 2711          	jreq	L226
3253  0027 a170          	cp	a,#112
3254  0029 270d          	jreq	L226
3255  002b a150          	cp	a,#80
3256  002d 2709          	jreq	L226
3257  002f a140          	cp	a,#64
3258  0031 2705          	jreq	L226
3259  0033 ae032e        	ldw	x,#814
3260  0036 ad37          	call	LC009
3261  0038               L226:
3262                     ; 816   if (TIM2_Channel == TIM2_CHANNEL_1)
3264  0038 7b01          	ld	a,(OFST+1,sp)
3265  003a 2610          	jrne	L3331
3266                     ; 819     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC1E);
3268  003c 7211530a      	bres	21258,#0
3269                     ; 822     TIM2->CCMR1 = (uint8_t)((uint8_t)(TIM2->CCMR1 & (uint8_t)(~TIM2_CCMR_OCM))
3269                     ; 823                             | (uint8_t)TIM2_OCMode);
3271  0040 c65307        	ld	a,21255
3272  0043 a48f          	and	a,#143
3273  0045 1a02          	or	a,(OFST+2,sp)
3274  0047 c75307        	ld	21255,a
3276  004a 2021          	jra	L5331
3277  004c               L3331:
3278                     ; 825   else if (TIM2_Channel == TIM2_CHANNEL_2)
3280  004c 4a            	dec	a
3281  004d 2610          	jrne	L7331
3282                     ; 828     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC2E);
3284  004f 7219530a      	bres	21258,#4
3285                     ; 831     TIM2->CCMR2 = (uint8_t)((uint8_t)(TIM2->CCMR2 & (uint8_t)(~TIM2_CCMR_OCM))
3285                     ; 832                             | (uint8_t)TIM2_OCMode);
3287  0053 c65308        	ld	a,21256
3288  0056 a48f          	and	a,#143
3289  0058 1a02          	or	a,(OFST+2,sp)
3290  005a c75308        	ld	21256,a
3292  005d 200e          	jra	L5331
3293  005f               L7331:
3294                     ; 837     TIM2->CCER2 &= (uint8_t)(~TIM2_CCER2_CC3E);
3296  005f 7211530b      	bres	21259,#0
3297                     ; 840     TIM2->CCMR3 = (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~TIM2_CCMR_OCM))
3297                     ; 841                             | (uint8_t)TIM2_OCMode);
3299  0063 c65309        	ld	a,21257
3300  0066 a48f          	and	a,#143
3301  0068 1a02          	or	a,(OFST+2,sp)
3302  006a c75309        	ld	21257,a
3303  006d               L5331:
3304                     ; 843 }
3307  006d 85            	popw	x
3308  006e 81            	ret	
3309  006f               LC009:
3310  006f 89            	pushw	x
3311  0070 5f            	clrw	x
3312  0071 89            	pushw	x
3313  0072 ae0000        	ldw	x,#L702
3314  0075 cd0000        	call	_assert_failed
3316  0078 5b04          	addw	sp,#4
3317  007a 81            	ret	
3351                     ; 851 void TIM2_SetCounter(uint16_t Counter)
3351                     ; 852 {
3352                     .text:	section	.text,new
3353  0000               _TIM2_SetCounter:
3357                     ; 854   TIM2->CNTRH = (uint8_t)(Counter >> 8);
3359  0000 9e            	ld	a,xh
3360  0001 c7530c        	ld	21260,a
3361                     ; 855   TIM2->CNTRL = (uint8_t)(Counter);
3363  0004 9f            	ld	a,xl
3364  0005 c7530d        	ld	21261,a
3365                     ; 856 }
3368  0008 81            	ret	
3402                     ; 864 void TIM2_SetAutoreload(uint16_t Autoreload)
3402                     ; 865 {
3403                     .text:	section	.text,new
3404  0000               _TIM2_SetAutoreload:
3408                     ; 867   TIM2->ARRH = (uint8_t)(Autoreload >> 8);
3410  0000 9e            	ld	a,xh
3411  0001 c7530f        	ld	21263,a
3412                     ; 868   TIM2->ARRL = (uint8_t)(Autoreload);
3414  0004 9f            	ld	a,xl
3415  0005 c75310        	ld	21264,a
3416                     ; 869 }
3419  0008 81            	ret	
3453                     ; 877 void TIM2_SetCompare1(uint16_t Compare1)
3453                     ; 878 {
3454                     .text:	section	.text,new
3455  0000               _TIM2_SetCompare1:
3459                     ; 880   TIM2->CCR1H = (uint8_t)(Compare1 >> 8);
3461  0000 9e            	ld	a,xh
3462  0001 c75311        	ld	21265,a
3463                     ; 881   TIM2->CCR1L = (uint8_t)(Compare1);
3465  0004 9f            	ld	a,xl
3466  0005 c75312        	ld	21266,a
3467                     ; 882 }
3470  0008 81            	ret	
3504                     ; 890 void TIM2_SetCompare2(uint16_t Compare2)
3504                     ; 891 {
3505                     .text:	section	.text,new
3506  0000               _TIM2_SetCompare2:
3510                     ; 893   TIM2->CCR2H = (uint8_t)(Compare2 >> 8);
3512  0000 9e            	ld	a,xh
3513  0001 c75313        	ld	21267,a
3514                     ; 894   TIM2->CCR2L = (uint8_t)(Compare2);
3516  0004 9f            	ld	a,xl
3517  0005 c75314        	ld	21268,a
3518                     ; 895 }
3521  0008 81            	ret	
3555                     ; 903 void TIM2_SetCompare3(uint16_t Compare3)
3555                     ; 904 {
3556                     .text:	section	.text,new
3557  0000               _TIM2_SetCompare3:
3561                     ; 906   TIM2->CCR3H = (uint8_t)(Compare3 >> 8);
3563  0000 9e            	ld	a,xh
3564  0001 c75315        	ld	21269,a
3565                     ; 907   TIM2->CCR3L = (uint8_t)(Compare3);
3567  0004 9f            	ld	a,xl
3568  0005 c75316        	ld	21270,a
3569                     ; 908 }
3572  0008 81            	ret	
3609                     ; 920 void TIM2_SetIC1Prescaler(TIM2_ICPSC_TypeDef TIM2_IC1Prescaler)
3609                     ; 921 {
3610                     .text:	section	.text,new
3611  0000               _TIM2_SetIC1Prescaler:
3613  0000 88            	push	a
3614       00000000      OFST:	set	0
3617                     ; 923   assert_param(IS_TIM2_IC_PRESCALER_OK(TIM2_IC1Prescaler));
3619  0001 4d            	tnz	a
3620  0002 271a          	jreq	L646
3621  0004 a104          	cp	a,#4
3622  0006 2716          	jreq	L646
3623  0008 a108          	cp	a,#8
3624  000a 2712          	jreq	L646
3625  000c a10c          	cp	a,#12
3626  000e 270e          	jreq	L646
3627  0010 ae039b        	ldw	x,#923
3628  0013 89            	pushw	x
3629  0014 5f            	clrw	x
3630  0015 89            	pushw	x
3631  0016 ae0000        	ldw	x,#L702
3632  0019 cd0000        	call	_assert_failed
3634  001c 5b04          	addw	sp,#4
3635  001e               L646:
3636                     ; 926   TIM2->CCMR1 = (uint8_t)((uint8_t)(TIM2->CCMR1 & (uint8_t)(~TIM2_CCMR_ICxPSC))
3636                     ; 927                           | (uint8_t)TIM2_IC1Prescaler);
3638  001e c65307        	ld	a,21255
3639  0021 a4f3          	and	a,#243
3640  0023 1a01          	or	a,(OFST+1,sp)
3641  0025 c75307        	ld	21255,a
3642                     ; 928 }
3645  0028 84            	pop	a
3646  0029 81            	ret	
3683                     ; 940 void TIM2_SetIC2Prescaler(TIM2_ICPSC_TypeDef TIM2_IC2Prescaler)
3683                     ; 941 {
3684                     .text:	section	.text,new
3685  0000               _TIM2_SetIC2Prescaler:
3687  0000 88            	push	a
3688       00000000      OFST:	set	0
3691                     ; 943   assert_param(IS_TIM2_IC_PRESCALER_OK(TIM2_IC2Prescaler));
3693  0001 4d            	tnz	a
3694  0002 271a          	jreq	L066
3695  0004 a104          	cp	a,#4
3696  0006 2716          	jreq	L066
3697  0008 a108          	cp	a,#8
3698  000a 2712          	jreq	L066
3699  000c a10c          	cp	a,#12
3700  000e 270e          	jreq	L066
3701  0010 ae03af        	ldw	x,#943
3702  0013 89            	pushw	x
3703  0014 5f            	clrw	x
3704  0015 89            	pushw	x
3705  0016 ae0000        	ldw	x,#L702
3706  0019 cd0000        	call	_assert_failed
3708  001c 5b04          	addw	sp,#4
3709  001e               L066:
3710                     ; 946   TIM2->CCMR2 = (uint8_t)((uint8_t)(TIM2->CCMR2 & (uint8_t)(~TIM2_CCMR_ICxPSC))
3710                     ; 947                           | (uint8_t)TIM2_IC2Prescaler);
3712  001e c65308        	ld	a,21256
3713  0021 a4f3          	and	a,#243
3714  0023 1a01          	or	a,(OFST+1,sp)
3715  0025 c75308        	ld	21256,a
3716                     ; 948 }
3719  0028 84            	pop	a
3720  0029 81            	ret	
3757                     ; 960 void TIM2_SetIC3Prescaler(TIM2_ICPSC_TypeDef TIM2_IC3Prescaler)
3757                     ; 961 {
3758                     .text:	section	.text,new
3759  0000               _TIM2_SetIC3Prescaler:
3761  0000 88            	push	a
3762       00000000      OFST:	set	0
3765                     ; 964   assert_param(IS_TIM2_IC_PRESCALER_OK(TIM2_IC3Prescaler));
3767  0001 4d            	tnz	a
3768  0002 271a          	jreq	L276
3769  0004 a104          	cp	a,#4
3770  0006 2716          	jreq	L276
3771  0008 a108          	cp	a,#8
3772  000a 2712          	jreq	L276
3773  000c a10c          	cp	a,#12
3774  000e 270e          	jreq	L276
3775  0010 ae03c4        	ldw	x,#964
3776  0013 89            	pushw	x
3777  0014 5f            	clrw	x
3778  0015 89            	pushw	x
3779  0016 ae0000        	ldw	x,#L702
3780  0019 cd0000        	call	_assert_failed
3782  001c 5b04          	addw	sp,#4
3783  001e               L276:
3784                     ; 966   TIM2->CCMR3 = (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~TIM2_CCMR_ICxPSC))
3784                     ; 967                           | (uint8_t)TIM2_IC3Prescaler);
3786  001e c65309        	ld	a,21257
3787  0021 a4f3          	and	a,#243
3788  0023 1a01          	or	a,(OFST+1,sp)
3789  0025 c75309        	ld	21257,a
3790                     ; 968 }
3793  0028 84            	pop	a
3794  0029 81            	ret	
3846                     ; 975 uint16_t TIM2_GetCapture1(void)
3846                     ; 976 {
3847                     .text:	section	.text,new
3848  0000               _TIM2_GetCapture1:
3850  0000 5204          	subw	sp,#4
3851       00000004      OFST:	set	4
3854                     ; 978   uint16_t tmpccr1 = 0;
3856                     ; 979   uint8_t tmpccr1l=0, tmpccr1h=0;
3860                     ; 981   tmpccr1h = TIM2->CCR1H;
3862  0002 c65311        	ld	a,21265
3863  0005 6b02          	ld	(OFST-2,sp),a
3865                     ; 982   tmpccr1l = TIM2->CCR1L;
3867  0007 c65312        	ld	a,21266
3868  000a 6b01          	ld	(OFST-3,sp),a
3870                     ; 984   tmpccr1 = (uint16_t)(tmpccr1l);
3872  000c 5f            	clrw	x
3873  000d 97            	ld	xl,a
3874  000e 1f03          	ldw	(OFST-1,sp),x
3876                     ; 985   tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);
3878  0010 5f            	clrw	x
3879  0011 7b02          	ld	a,(OFST-2,sp)
3880  0013 97            	ld	xl,a
3881  0014 7b04          	ld	a,(OFST+0,sp)
3882  0016 01            	rrwa	x,a
3883  0017 1a03          	or	a,(OFST-1,sp)
3884  0019 01            	rrwa	x,a
3886                     ; 987   return (uint16_t)tmpccr1;
3890  001a 5b04          	addw	sp,#4
3891  001c 81            	ret	
3943                     ; 995 uint16_t TIM2_GetCapture2(void)
3943                     ; 996 {
3944                     .text:	section	.text,new
3945  0000               _TIM2_GetCapture2:
3947  0000 5204          	subw	sp,#4
3948       00000004      OFST:	set	4
3951                     ; 998   uint16_t tmpccr2 = 0;
3953                     ; 999   uint8_t tmpccr2l=0, tmpccr2h=0;
3957                     ; 1001   tmpccr2h = TIM2->CCR2H;
3959  0002 c65313        	ld	a,21267
3960  0005 6b02          	ld	(OFST-2,sp),a
3962                     ; 1002   tmpccr2l = TIM2->CCR2L;
3964  0007 c65314        	ld	a,21268
3965  000a 6b01          	ld	(OFST-3,sp),a
3967                     ; 1004   tmpccr2 = (uint16_t)(tmpccr2l);
3969  000c 5f            	clrw	x
3970  000d 97            	ld	xl,a
3971  000e 1f03          	ldw	(OFST-1,sp),x
3973                     ; 1005   tmpccr2 |= (uint16_t)((uint16_t)tmpccr2h << 8);
3975  0010 5f            	clrw	x
3976  0011 7b02          	ld	a,(OFST-2,sp)
3977  0013 97            	ld	xl,a
3978  0014 7b04          	ld	a,(OFST+0,sp)
3979  0016 01            	rrwa	x,a
3980  0017 1a03          	or	a,(OFST-1,sp)
3981  0019 01            	rrwa	x,a
3983                     ; 1007   return (uint16_t)tmpccr2;
3987  001a 5b04          	addw	sp,#4
3988  001c 81            	ret	
4040                     ; 1015 uint16_t TIM2_GetCapture3(void)
4040                     ; 1016 {
4041                     .text:	section	.text,new
4042  0000               _TIM2_GetCapture3:
4044  0000 5204          	subw	sp,#4
4045       00000004      OFST:	set	4
4048                     ; 1018   uint16_t tmpccr3 = 0;
4050                     ; 1019   uint8_t tmpccr3l=0, tmpccr3h=0;
4054                     ; 1021   tmpccr3h = TIM2->CCR3H;
4056  0002 c65315        	ld	a,21269
4057  0005 6b02          	ld	(OFST-2,sp),a
4059                     ; 1022   tmpccr3l = TIM2->CCR3L;
4061  0007 c65316        	ld	a,21270
4062  000a 6b01          	ld	(OFST-3,sp),a
4064                     ; 1024   tmpccr3 = (uint16_t)(tmpccr3l);
4066  000c 5f            	clrw	x
4067  000d 97            	ld	xl,a
4068  000e 1f03          	ldw	(OFST-1,sp),x
4070                     ; 1025   tmpccr3 |= (uint16_t)((uint16_t)tmpccr3h << 8);
4072  0010 5f            	clrw	x
4073  0011 7b02          	ld	a,(OFST-2,sp)
4074  0013 97            	ld	xl,a
4075  0014 7b04          	ld	a,(OFST+0,sp)
4076  0016 01            	rrwa	x,a
4077  0017 1a03          	or	a,(OFST-1,sp)
4078  0019 01            	rrwa	x,a
4080                     ; 1027   return (uint16_t)tmpccr3;
4084  001a 5b04          	addw	sp,#4
4085  001c 81            	ret	
4119                     ; 1035 uint16_t TIM2_GetCounter(void)
4119                     ; 1036 {
4120                     .text:	section	.text,new
4121  0000               _TIM2_GetCounter:
4123  0000 89            	pushw	x
4124       00000002      OFST:	set	2
4127                     ; 1037   uint16_t tmpcntr = 0;
4129                     ; 1039   tmpcntr =  ((uint16_t)TIM2->CNTRH << 8);
4131  0001 c6530c        	ld	a,21260
4132  0004 97            	ld	xl,a
4133  0005 4f            	clr	a
4134  0006 02            	rlwa	x,a
4135  0007 1f01          	ldw	(OFST-1,sp),x
4137                     ; 1041   return (uint16_t)( tmpcntr| (uint16_t)(TIM2->CNTRL));
4139  0009 c6530d        	ld	a,21261
4140  000c 5f            	clrw	x
4141  000d 97            	ld	xl,a
4142  000e 01            	rrwa	x,a
4143  000f 1a02          	or	a,(OFST+0,sp)
4144  0011 01            	rrwa	x,a
4145  0012 1a01          	or	a,(OFST-1,sp)
4146  0014 01            	rrwa	x,a
4149  0015 5b02          	addw	sp,#2
4150  0017 81            	ret	
4174                     ; 1049 TIM2_Prescaler_TypeDef TIM2_GetPrescaler(void)
4174                     ; 1050 {
4175                     .text:	section	.text,new
4176  0000               _TIM2_GetPrescaler:
4180                     ; 1052   return (TIM2_Prescaler_TypeDef)(TIM2->PSCR);
4182  0000 c6530e        	ld	a,21262
4185  0003 81            	ret	
4325                     ; 1068 FlagStatus TIM2_GetFlagStatus(TIM2_FLAG_TypeDef TIM2_FLAG)
4325                     ; 1069 {
4326                     .text:	section	.text,new
4327  0000               _TIM2_GetFlagStatus:
4329  0000 89            	pushw	x
4330  0001 89            	pushw	x
4331       00000002      OFST:	set	2
4334                     ; 1070   FlagStatus bitstatus = RESET;
4336                     ; 1071   uint8_t tim2_flag_l = 0, tim2_flag_h = 0;
4340                     ; 1074   assert_param(IS_TIM2_GET_FLAG_OK(TIM2_FLAG));
4342  0002 a30001        	cpw	x,#1
4343  0005 272c          	jreq	L617
4344  0007 a30002        	cpw	x,#2
4345  000a 2727          	jreq	L617
4346  000c a30004        	cpw	x,#4
4347  000f 2722          	jreq	L617
4348  0011 a30008        	cpw	x,#8
4349  0014 271d          	jreq	L617
4350  0016 a30200        	cpw	x,#512
4351  0019 2718          	jreq	L617
4352  001b a30400        	cpw	x,#1024
4353  001e 2713          	jreq	L617
4354  0020 a30800        	cpw	x,#2048
4355  0023 270e          	jreq	L617
4356  0025 ae0432        	ldw	x,#1074
4357  0028 89            	pushw	x
4358  0029 5f            	clrw	x
4359  002a 89            	pushw	x
4360  002b ae0000        	ldw	x,#L702
4361  002e cd0000        	call	_assert_failed
4363  0031 5b04          	addw	sp,#4
4364  0033               L617:
4365                     ; 1076   tim2_flag_l = (uint8_t)(TIM2->SR1 & (uint8_t)TIM2_FLAG);
4367  0033 c65304        	ld	a,21252
4368  0036 1404          	and	a,(OFST+2,sp)
4369  0038 6b01          	ld	(OFST-1,sp),a
4371                     ; 1077   tim2_flag_h = (uint8_t)((uint16_t)TIM2_FLAG >> 8);
4373  003a 7b03          	ld	a,(OFST+1,sp)
4374  003c 6b02          	ld	(OFST+0,sp),a
4376                     ; 1079   if ((tim2_flag_l | (uint8_t)(TIM2->SR2 & tim2_flag_h)) != (uint8_t)RESET )
4378  003e c45305        	and	a,21253
4379  0041 1a01          	or	a,(OFST-1,sp)
4380  0043 2702          	jreq	L7371
4381                     ; 1081     bitstatus = SET;
4383  0045 a601          	ld	a,#1
4386  0047               L7371:
4387                     ; 1085     bitstatus = RESET;
4390                     ; 1087   return (FlagStatus)bitstatus;
4394  0047 5b04          	addw	sp,#4
4395  0049 81            	ret	
4431                     ; 1103 void TIM2_ClearFlag(TIM2_FLAG_TypeDef TIM2_FLAG)
4431                     ; 1104 {
4432                     .text:	section	.text,new
4433  0000               _TIM2_ClearFlag:
4435  0000 89            	pushw	x
4436       00000000      OFST:	set	0
4439                     ; 1106   assert_param(IS_TIM2_CLEAR_FLAG_OK(TIM2_FLAG));
4441  0001 01            	rrwa	x,a
4442  0002 a4f0          	and	a,#240
4443  0004 01            	rrwa	x,a
4444  0005 a4f1          	and	a,#241
4445  0007 01            	rrwa	x,a
4446  0008 5d            	tnzw	x
4447  0009 2604          	jrne	L427
4448  000b 1e01          	ldw	x,(OFST+1,sp)
4449  000d 260e          	jrne	L627
4450  000f               L427:
4451  000f ae0452        	ldw	x,#1106
4452  0012 89            	pushw	x
4453  0013 5f            	clrw	x
4454  0014 89            	pushw	x
4455  0015 ae0000        	ldw	x,#L702
4456  0018 cd0000        	call	_assert_failed
4458  001b 5b04          	addw	sp,#4
4459  001d               L627:
4460                     ; 1109   TIM2->SR1 = (uint8_t)(~((uint8_t)(TIM2_FLAG)));
4462  001d 7b02          	ld	a,(OFST+2,sp)
4463  001f 43            	cpl	a
4464  0020 c75304        	ld	21252,a
4465                     ; 1110   TIM2->SR2 = (uint8_t)(~((uint8_t)((uint8_t)TIM2_FLAG >> 8)));
4467  0023 35ff5305      	mov	21253,#255
4468                     ; 1111 }
4471  0027 85            	popw	x
4472  0028 81            	ret	
4537                     ; 1123 ITStatus TIM2_GetITStatus(TIM2_IT_TypeDef TIM2_IT)
4537                     ; 1124 {
4538                     .text:	section	.text,new
4539  0000               _TIM2_GetITStatus:
4541  0000 88            	push	a
4542  0001 89            	pushw	x
4543       00000002      OFST:	set	2
4546                     ; 1125   ITStatus bitstatus = RESET;
4548                     ; 1126   uint8_t TIM2_itStatus = 0, TIM2_itEnable = 0;
4552                     ; 1129   assert_param(IS_TIM2_GET_IT_OK(TIM2_IT));
4554  0002 a101          	cp	a,#1
4555  0004 271a          	jreq	L047
4556  0006 a102          	cp	a,#2
4557  0008 2716          	jreq	L047
4558  000a a104          	cp	a,#4
4559  000c 2712          	jreq	L047
4560  000e a108          	cp	a,#8
4561  0010 270e          	jreq	L047
4562  0012 ae0469        	ldw	x,#1129
4563  0015 89            	pushw	x
4564  0016 5f            	clrw	x
4565  0017 89            	pushw	x
4566  0018 ae0000        	ldw	x,#L702
4567  001b cd0000        	call	_assert_failed
4569  001e 5b04          	addw	sp,#4
4570  0020               L047:
4571                     ; 1131   TIM2_itStatus = (uint8_t)(TIM2->SR1 & TIM2_IT);
4573  0020 c65304        	ld	a,21252
4574  0023 1403          	and	a,(OFST+1,sp)
4575  0025 6b01          	ld	(OFST-1,sp),a
4577                     ; 1133   TIM2_itEnable = (uint8_t)(TIM2->IER & TIM2_IT);
4579  0027 c65303        	ld	a,21251
4580  002a 1403          	and	a,(OFST+1,sp)
4581  002c 6b02          	ld	(OFST+0,sp),a
4583                     ; 1135   if ((TIM2_itStatus != (uint8_t)RESET ) && (TIM2_itEnable != (uint8_t)RESET ))
4585  002e 7b01          	ld	a,(OFST-1,sp)
4586  0030 2708          	jreq	L3102
4588  0032 7b02          	ld	a,(OFST+0,sp)
4589  0034 2704          	jreq	L3102
4590                     ; 1137     bitstatus = SET;
4592  0036 a601          	ld	a,#1
4595  0038 2001          	jra	L5102
4596  003a               L3102:
4597                     ; 1141     bitstatus = RESET;
4599  003a 4f            	clr	a
4601  003b               L5102:
4602                     ; 1143   return (ITStatus)(bitstatus);
4606  003b 5b03          	addw	sp,#3
4607  003d 81            	ret	
4644                     ; 1156 void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT)
4644                     ; 1157 {
4645                     .text:	section	.text,new
4646  0000               _TIM2_ClearITPendingBit:
4648  0000 88            	push	a
4649       00000000      OFST:	set	0
4652                     ; 1159   assert_param(IS_TIM2_IT_OK(TIM2_IT));
4654  0001 4d            	tnz	a
4655  0002 2704          	jreq	L647
4656  0004 a110          	cp	a,#16
4657  0006 250e          	jrult	L057
4658  0008               L647:
4659  0008 ae0487        	ldw	x,#1159
4660  000b 89            	pushw	x
4661  000c 5f            	clrw	x
4662  000d 89            	pushw	x
4663  000e ae0000        	ldw	x,#L702
4664  0011 cd0000        	call	_assert_failed
4666  0014 5b04          	addw	sp,#4
4667  0016               L057:
4668                     ; 1162   TIM2->SR1 = (uint8_t)(~TIM2_IT);
4670  0016 7b01          	ld	a,(OFST+1,sp)
4671  0018 43            	cpl	a
4672  0019 c75304        	ld	21252,a
4673                     ; 1163 }
4676  001c 84            	pop	a
4677  001d 81            	ret	
4729                     ; 1181 static void TI1_Config(uint8_t TIM2_ICPolarity,
4729                     ; 1182                        uint8_t TIM2_ICSelection,
4729                     ; 1183                        uint8_t TIM2_ICFilter)
4729                     ; 1184 {
4730                     .text:	section	.text,new
4731  0000               L3_TI1_Config:
4733  0000 89            	pushw	x
4734  0001 88            	push	a
4735       00000001      OFST:	set	1
4738                     ; 1186   TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC1E);
4740  0002 7211530a      	bres	21258,#0
4741                     ; 1189   TIM2->CCMR1  = (uint8_t)((uint8_t)(TIM2->CCMR1 & (uint8_t)(~(uint8_t)( TIM2_CCMR_CCxS | TIM2_CCMR_ICxF )))
4741                     ; 1190                            | (uint8_t)(((TIM2_ICSelection)) | ((uint8_t)( TIM2_ICFilter << 4))));
4743  0006 7b06          	ld	a,(OFST+5,sp)
4744  0008 97            	ld	xl,a
4745  0009 a610          	ld	a,#16
4746  000b 42            	mul	x,a
4747  000c 9f            	ld	a,xl
4748  000d 1a03          	or	a,(OFST+2,sp)
4749  000f 6b01          	ld	(OFST+0,sp),a
4751  0011 c65307        	ld	a,21255
4752  0014 a40c          	and	a,#12
4753  0016 1a01          	or	a,(OFST+0,sp)
4754  0018 c75307        	ld	21255,a
4755                     ; 1193   if (TIM2_ICPolarity != TIM2_ICPOLARITY_RISING)
4757  001b 7b02          	ld	a,(OFST+1,sp)
4758  001d 2706          	jreq	L3602
4759                     ; 1195     TIM2->CCER1 |= TIM2_CCER1_CC1P;
4761  001f 7212530a      	bset	21258,#1
4763  0023 2004          	jra	L5602
4764  0025               L3602:
4765                     ; 1199     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC1P);
4767  0025 7213530a      	bres	21258,#1
4768  0029               L5602:
4769                     ; 1202   TIM2->CCER1 |= TIM2_CCER1_CC1E;
4771  0029 7210530a      	bset	21258,#0
4772                     ; 1203 }
4775  002d 5b03          	addw	sp,#3
4776  002f 81            	ret	
4828                     ; 1221 static void TI2_Config(uint8_t TIM2_ICPolarity,
4828                     ; 1222                        uint8_t TIM2_ICSelection,
4828                     ; 1223                        uint8_t TIM2_ICFilter)
4828                     ; 1224 {
4829                     .text:	section	.text,new
4830  0000               L5_TI2_Config:
4832  0000 89            	pushw	x
4833  0001 88            	push	a
4834       00000001      OFST:	set	1
4837                     ; 1226   TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC2E);
4839  0002 7219530a      	bres	21258,#4
4840                     ; 1229   TIM2->CCMR2 = (uint8_t)((uint8_t)(TIM2->CCMR2 & (uint8_t)(~(uint8_t)( TIM2_CCMR_CCxS | TIM2_CCMR_ICxF ))) 
4840                     ; 1230                           | (uint8_t)(( (TIM2_ICSelection)) | ((uint8_t)( TIM2_ICFilter << 4))));
4842  0006 7b06          	ld	a,(OFST+5,sp)
4843  0008 97            	ld	xl,a
4844  0009 a610          	ld	a,#16
4845  000b 42            	mul	x,a
4846  000c 9f            	ld	a,xl
4847  000d 1a03          	or	a,(OFST+2,sp)
4848  000f 6b01          	ld	(OFST+0,sp),a
4850  0011 c65308        	ld	a,21256
4851  0014 a40c          	and	a,#12
4852  0016 1a01          	or	a,(OFST+0,sp)
4853  0018 c75308        	ld	21256,a
4854                     ; 1234   if (TIM2_ICPolarity != TIM2_ICPOLARITY_RISING)
4856  001b 7b02          	ld	a,(OFST+1,sp)
4857  001d 2706          	jreq	L5112
4858                     ; 1236     TIM2->CCER1 |= TIM2_CCER1_CC2P;
4860  001f 721a530a      	bset	21258,#5
4862  0023 2004          	jra	L7112
4863  0025               L5112:
4864                     ; 1240     TIM2->CCER1 &= (uint8_t)(~TIM2_CCER1_CC2P);
4866  0025 721b530a      	bres	21258,#5
4867  0029               L7112:
4868                     ; 1244   TIM2->CCER1 |= TIM2_CCER1_CC2E;
4870  0029 7218530a      	bset	21258,#4
4871                     ; 1245 }
4874  002d 5b03          	addw	sp,#3
4875  002f 81            	ret	
4927                     ; 1261 static void TI3_Config(uint8_t TIM2_ICPolarity, uint8_t TIM2_ICSelection,
4927                     ; 1262                        uint8_t TIM2_ICFilter)
4927                     ; 1263 {
4928                     .text:	section	.text,new
4929  0000               L7_TI3_Config:
4931  0000 89            	pushw	x
4932  0001 88            	push	a
4933       00000001      OFST:	set	1
4936                     ; 1265   TIM2->CCER2 &=  (uint8_t)(~TIM2_CCER2_CC3E);
4938  0002 7211530b      	bres	21259,#0
4939                     ; 1268   TIM2->CCMR3 = (uint8_t)((uint8_t)(TIM2->CCMR3 & (uint8_t)(~( TIM2_CCMR_CCxS | TIM2_CCMR_ICxF))) 
4939                     ; 1269                           | (uint8_t)(( (TIM2_ICSelection)) | ((uint8_t)( TIM2_ICFilter << 4))));
4941  0006 7b06          	ld	a,(OFST+5,sp)
4942  0008 97            	ld	xl,a
4943  0009 a610          	ld	a,#16
4944  000b 42            	mul	x,a
4945  000c 9f            	ld	a,xl
4946  000d 1a03          	or	a,(OFST+2,sp)
4947  000f 6b01          	ld	(OFST+0,sp),a
4949  0011 c65309        	ld	a,21257
4950  0014 a40c          	and	a,#12
4951  0016 1a01          	or	a,(OFST+0,sp)
4952  0018 c75309        	ld	21257,a
4953                     ; 1273   if (TIM2_ICPolarity != TIM2_ICPOLARITY_RISING)
4955  001b 7b02          	ld	a,(OFST+1,sp)
4956  001d 2706          	jreq	L7412
4957                     ; 1275     TIM2->CCER2 |= TIM2_CCER2_CC3P;
4959  001f 7212530b      	bset	21259,#1
4961  0023 2004          	jra	L1512
4962  0025               L7412:
4963                     ; 1279     TIM2->CCER2 &= (uint8_t)(~TIM2_CCER2_CC3P);
4965  0025 7213530b      	bres	21259,#1
4966  0029               L1512:
4967                     ; 1282   TIM2->CCER2 |= TIM2_CCER2_CC3E;
4969  0029 7210530b      	bset	21259,#0
4970                     ; 1283 }
4973  002d 5b03          	addw	sp,#3
4974  002f 81            	ret	
4987                     	xdef	_TIM2_ClearITPendingBit
4988                     	xdef	_TIM2_GetITStatus
4989                     	xdef	_TIM2_ClearFlag
4990                     	xdef	_TIM2_GetFlagStatus
4991                     	xdef	_TIM2_GetPrescaler
4992                     	xdef	_TIM2_GetCounter
4993                     	xdef	_TIM2_GetCapture3
4994                     	xdef	_TIM2_GetCapture2
4995                     	xdef	_TIM2_GetCapture1
4996                     	xdef	_TIM2_SetIC3Prescaler
4997                     	xdef	_TIM2_SetIC2Prescaler
4998                     	xdef	_TIM2_SetIC1Prescaler
4999                     	xdef	_TIM2_SetCompare3
5000                     	xdef	_TIM2_SetCompare2
5001                     	xdef	_TIM2_SetCompare1
5002                     	xdef	_TIM2_SetAutoreload
5003                     	xdef	_TIM2_SetCounter
5004                     	xdef	_TIM2_SelectOCxM
5005                     	xdef	_TIM2_CCxCmd
5006                     	xdef	_TIM2_OC3PolarityConfig
5007                     	xdef	_TIM2_OC2PolarityConfig
5008                     	xdef	_TIM2_OC1PolarityConfig
5009                     	xdef	_TIM2_GenerateEvent
5010                     	xdef	_TIM2_OC3PreloadConfig
5011                     	xdef	_TIM2_OC2PreloadConfig
5012                     	xdef	_TIM2_OC1PreloadConfig
5013                     	xdef	_TIM2_ARRPreloadConfig
5014                     	xdef	_TIM2_ForcedOC3Config
5015                     	xdef	_TIM2_ForcedOC2Config
5016                     	xdef	_TIM2_ForcedOC1Config
5017                     	xdef	_TIM2_PrescalerConfig
5018                     	xdef	_TIM2_SelectOnePulseMode
5019                     	xdef	_TIM2_UpdateRequestConfig
5020                     	xdef	_TIM2_UpdateDisableConfig
5021                     	xdef	_TIM2_ITConfig
5022                     	xdef	_TIM2_Cmd
5023                     	xdef	_TIM2_PWMIConfig
5024                     	xdef	_TIM2_ICInit
5025                     	xdef	_TIM2_OC3Init
5026                     	xdef	_TIM2_OC2Init
5027                     	xdef	_TIM2_OC1Init
5028                     	xdef	_TIM2_TimeBaseInit
5029                     	xdef	_TIM2_DeInit
5030                     	xref	_assert_failed
5031                     .const:	section	.text
5032  0000               L702:
5033  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
5034  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
5035  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
5036  0036 5f74696d322e  	dc.b	"_tim2.c",0
5056                     	end
