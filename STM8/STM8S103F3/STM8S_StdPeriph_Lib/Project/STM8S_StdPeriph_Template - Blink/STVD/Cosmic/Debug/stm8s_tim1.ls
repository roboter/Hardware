   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 58 void TIM1_DeInit(void)
  49                     ; 59 {
  51                     .text:	section	.text,new
  52  0000               _TIM1_DeInit:
  56                     ; 60   TIM1->CR1  = TIM1_CR1_RESET_VALUE;
  58  0000 725f5250      	clr	21072
  59                     ; 61   TIM1->CR2  = TIM1_CR2_RESET_VALUE;
  61  0004 725f5251      	clr	21073
  62                     ; 62   TIM1->SMCR = TIM1_SMCR_RESET_VALUE;
  64  0008 725f5252      	clr	21074
  65                     ; 63   TIM1->ETR  = TIM1_ETR_RESET_VALUE;
  67  000c 725f5253      	clr	21075
  68                     ; 64   TIM1->IER  = TIM1_IER_RESET_VALUE;
  70  0010 725f5254      	clr	21076
  71                     ; 65   TIM1->SR2  = TIM1_SR2_RESET_VALUE;
  73  0014 725f5256      	clr	21078
  74                     ; 67   TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  76  0018 725f525c      	clr	21084
  77                     ; 68   TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  79  001c 725f525d      	clr	21085
  80                     ; 70   TIM1->CCMR1 = 0x01;
  82  0020 35015258      	mov	21080,#1
  83                     ; 71   TIM1->CCMR2 = 0x01;
  85  0024 35015259      	mov	21081,#1
  86                     ; 72   TIM1->CCMR3 = 0x01;
  88  0028 3501525a      	mov	21082,#1
  89                     ; 73   TIM1->CCMR4 = 0x01;
  91  002c 3501525b      	mov	21083,#1
  92                     ; 75   TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  94  0030 725f525c      	clr	21084
  95                     ; 76   TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  97  0034 725f525d      	clr	21085
  98                     ; 77   TIM1->CCMR1 = TIM1_CCMR1_RESET_VALUE;
 100  0038 725f5258      	clr	21080
 101                     ; 78   TIM1->CCMR2 = TIM1_CCMR2_RESET_VALUE;
 103  003c 725f5259      	clr	21081
 104                     ; 79   TIM1->CCMR3 = TIM1_CCMR3_RESET_VALUE;
 106  0040 725f525a      	clr	21082
 107                     ; 80   TIM1->CCMR4 = TIM1_CCMR4_RESET_VALUE;
 109  0044 725f525b      	clr	21083
 110                     ; 81   TIM1->CNTRH = TIM1_CNTRH_RESET_VALUE;
 112  0048 725f525e      	clr	21086
 113                     ; 82   TIM1->CNTRL = TIM1_CNTRL_RESET_VALUE;
 115  004c 725f525f      	clr	21087
 116                     ; 83   TIM1->PSCRH = TIM1_PSCRH_RESET_VALUE;
 118  0050 725f5260      	clr	21088
 119                     ; 84   TIM1->PSCRL = TIM1_PSCRL_RESET_VALUE;
 121  0054 725f5261      	clr	21089
 122                     ; 85   TIM1->ARRH  = TIM1_ARRH_RESET_VALUE;
 124  0058 35ff5262      	mov	21090,#255
 125                     ; 86   TIM1->ARRL  = TIM1_ARRL_RESET_VALUE;
 127  005c 35ff5263      	mov	21091,#255
 128                     ; 87   TIM1->CCR1H = TIM1_CCR1H_RESET_VALUE;
 130  0060 725f5265      	clr	21093
 131                     ; 88   TIM1->CCR1L = TIM1_CCR1L_RESET_VALUE;
 133  0064 725f5266      	clr	21094
 134                     ; 89   TIM1->CCR2H = TIM1_CCR2H_RESET_VALUE;
 136  0068 725f5267      	clr	21095
 137                     ; 90   TIM1->CCR2L = TIM1_CCR2L_RESET_VALUE;
 139  006c 725f5268      	clr	21096
 140                     ; 91   TIM1->CCR3H = TIM1_CCR3H_RESET_VALUE;
 142  0070 725f5269      	clr	21097
 143                     ; 92   TIM1->CCR3L = TIM1_CCR3L_RESET_VALUE;
 145  0074 725f526a      	clr	21098
 146                     ; 93   TIM1->CCR4H = TIM1_CCR4H_RESET_VALUE;
 148  0078 725f526b      	clr	21099
 149                     ; 94   TIM1->CCR4L = TIM1_CCR4L_RESET_VALUE;
 151  007c 725f526c      	clr	21100
 152                     ; 95   TIM1->OISR  = TIM1_OISR_RESET_VALUE;
 154  0080 725f526f      	clr	21103
 155                     ; 96   TIM1->EGR   = 0x01; /* TIM1_EGR_UG */
 157  0084 35015257      	mov	21079,#1
 158                     ; 97   TIM1->DTR   = TIM1_DTR_RESET_VALUE;
 160  0088 725f526e      	clr	21102
 161                     ; 98   TIM1->BKR   = TIM1_BKR_RESET_VALUE;
 163  008c 725f526d      	clr	21101
 164                     ; 99   TIM1->RCR   = TIM1_RCR_RESET_VALUE;
 166  0090 725f5264      	clr	21092
 167                     ; 100   TIM1->SR1   = TIM1_SR1_RESET_VALUE;
 169  0094 725f5255      	clr	21077
 170                     ; 101 }
 173  0098 81            	ret	
 283                     ; 111 void TIM1_TimeBaseInit(uint16_t TIM1_Prescaler,
 283                     ; 112                        TIM1_CounterMode_TypeDef TIM1_CounterMode,
 283                     ; 113                        uint16_t TIM1_Period,
 283                     ; 114                        uint8_t TIM1_RepetitionCounter)
 283                     ; 115 {
 284                     .text:	section	.text,new
 285  0000               _TIM1_TimeBaseInit:
 287  0000 89            	pushw	x
 288       00000000      OFST:	set	0
 291                     ; 117   assert_param(IS_TIM1_COUNTER_MODE_OK(TIM1_CounterMode));
 293  0001 7b05          	ld	a,(OFST+5,sp)
 294  0003 271e          	jreq	L41
 295  0005 a110          	cp	a,#16
 296  0007 271a          	jreq	L41
 297  0009 a120          	cp	a,#32
 298  000b 2716          	jreq	L41
 299  000d a140          	cp	a,#64
 300  000f 2712          	jreq	L41
 301  0011 a160          	cp	a,#96
 302  0013 270e          	jreq	L41
 303  0015 ae0075        	ldw	x,#117
 304  0018 89            	pushw	x
 305  0019 5f            	clrw	x
 306  001a 89            	pushw	x
 307  001b ae0000        	ldw	x,#L101
 308  001e cd0000        	call	_assert_failed
 310  0021 5b04          	addw	sp,#4
 311  0023               L41:
 312                     ; 120   TIM1->ARRH = (uint8_t)(TIM1_Period >> 8);
 314  0023 7b06          	ld	a,(OFST+6,sp)
 315  0025 c75262        	ld	21090,a
 316                     ; 121   TIM1->ARRL = (uint8_t)(TIM1_Period);
 318  0028 7b07          	ld	a,(OFST+7,sp)
 319  002a c75263        	ld	21091,a
 320                     ; 124   TIM1->PSCRH = (uint8_t)(TIM1_Prescaler >> 8);
 322  002d 7b01          	ld	a,(OFST+1,sp)
 323  002f c75260        	ld	21088,a
 324                     ; 125   TIM1->PSCRL = (uint8_t)(TIM1_Prescaler);
 326  0032 7b02          	ld	a,(OFST+2,sp)
 327  0034 c75261        	ld	21089,a
 328                     ; 128   TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR)))
 328                     ; 129                         | (uint8_t)(TIM1_CounterMode));
 330  0037 c65250        	ld	a,21072
 331  003a a48f          	and	a,#143
 332  003c 1a05          	or	a,(OFST+5,sp)
 333  003e c75250        	ld	21072,a
 334                     ; 132   TIM1->RCR = TIM1_RepetitionCounter;
 336  0041 7b08          	ld	a,(OFST+8,sp)
 337  0043 c75264        	ld	21092,a
 338                     ; 133 }
 341  0046 85            	popw	x
 342  0047 81            	ret	
 628                     ; 154 void TIM1_OC1Init(TIM1_OCMode_TypeDef TIM1_OCMode,
 628                     ; 155                   TIM1_OutputState_TypeDef TIM1_OutputState,
 628                     ; 156                   TIM1_OutputNState_TypeDef TIM1_OutputNState,
 628                     ; 157                   uint16_t TIM1_Pulse,
 628                     ; 158                   TIM1_OCPolarity_TypeDef TIM1_OCPolarity,
 628                     ; 159                   TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity,
 628                     ; 160                   TIM1_OCIdleState_TypeDef TIM1_OCIdleState,
 628                     ; 161                   TIM1_OCNIdleState_TypeDef TIM1_OCNIdleState)
 628                     ; 162 {
 629                     .text:	section	.text,new
 630  0000               _TIM1_OC1Init:
 632  0000 89            	pushw	x
 633  0001 5203          	subw	sp,#3
 634       00000003      OFST:	set	3
 637                     ; 164   assert_param(IS_TIM1_OC_MODE_OK(TIM1_OCMode));
 639  0003 9e            	ld	a,xh
 640  0004 4d            	tnz	a
 641  0005 271f          	jreq	L62
 642  0007 9e            	ld	a,xh
 643  0008 a110          	cp	a,#16
 644  000a 271a          	jreq	L62
 645  000c 9e            	ld	a,xh
 646  000d a120          	cp	a,#32
 647  000f 2715          	jreq	L62
 648  0011 9e            	ld	a,xh
 649  0012 a130          	cp	a,#48
 650  0014 2710          	jreq	L62
 651  0016 9e            	ld	a,xh
 652  0017 a160          	cp	a,#96
 653  0019 270b          	jreq	L62
 654  001b 9e            	ld	a,xh
 655  001c a170          	cp	a,#112
 656  001e 2706          	jreq	L62
 657  0020 ae00a4        	ldw	x,#164
 658  0023 cd00d4        	call	LC001
 659  0026               L62:
 660                     ; 165   assert_param(IS_TIM1_OUTPUT_STATE_OK(TIM1_OutputState));
 662  0026 7b05          	ld	a,(OFST+2,sp)
 663  0028 270a          	jreq	L63
 664  002a a111          	cp	a,#17
 665  002c 2706          	jreq	L63
 666  002e ae00a5        	ldw	x,#165
 667  0031 cd00d4        	call	LC001
 668  0034               L63:
 669                     ; 166   assert_param(IS_TIM1_OUTPUTN_STATE_OK(TIM1_OutputNState));
 671  0034 7b08          	ld	a,(OFST+5,sp)
 672  0036 270a          	jreq	L64
 673  0038 a144          	cp	a,#68
 674  003a 2706          	jreq	L64
 675  003c ae00a6        	ldw	x,#166
 676  003f cd00d4        	call	LC001
 677  0042               L64:
 678                     ; 167   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
 680  0042 7b0b          	ld	a,(OFST+8,sp)
 681  0044 270a          	jreq	L65
 682  0046 a122          	cp	a,#34
 683  0048 2706          	jreq	L65
 684  004a ae00a7        	ldw	x,#167
 685  004d cd00d4        	call	LC001
 686  0050               L65:
 687                     ; 168   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
 689  0050 7b0c          	ld	a,(OFST+9,sp)
 690  0052 2709          	jreq	L66
 691  0054 a188          	cp	a,#136
 692  0056 2705          	jreq	L66
 693  0058 ae00a8        	ldw	x,#168
 694  005b ad77          	call	LC001
 695  005d               L66:
 696                     ; 169   assert_param(IS_TIM1_OCIDLE_STATE_OK(TIM1_OCIdleState));
 698  005d 7b0d          	ld	a,(OFST+10,sp)
 699  005f a155          	cp	a,#85
 700  0061 2708          	jreq	L67
 701  0063 4d            	tnz	a
 702  0064 2705          	jreq	L67
 703  0066 ae00a9        	ldw	x,#169
 704  0069 ad69          	call	LC001
 705  006b               L67:
 706                     ; 170   assert_param(IS_TIM1_OCNIDLE_STATE_OK(TIM1_OCNIdleState));
 708  006b 7b0e          	ld	a,(OFST+11,sp)
 709  006d a12a          	cp	a,#42
 710  006f 2708          	jreq	L601
 711  0071 4d            	tnz	a
 712  0072 2705          	jreq	L601
 713  0074 ae00aa        	ldw	x,#170
 714  0077 ad5b          	call	LC001
 715  0079               L601:
 716                     ; 174   TIM1->CCER1 &= (uint8_t)(~( TIM1_CCER1_CC1E | TIM1_CCER1_CC1NE 
 716                     ; 175                              | TIM1_CCER1_CC1P | TIM1_CCER1_CC1NP));
 718  0079 c6525c        	ld	a,21084
 719  007c a4f0          	and	a,#240
 720  007e c7525c        	ld	21084,a
 721                     ; 178   TIM1->CCER1 |= (uint8_t)((uint8_t)((uint8_t)(TIM1_OutputState & TIM1_CCER1_CC1E)
 721                     ; 179                                      | (uint8_t)(TIM1_OutputNState & TIM1_CCER1_CC1NE))
 721                     ; 180                            | (uint8_t)( (uint8_t)(TIM1_OCPolarity  & TIM1_CCER1_CC1P)
 721                     ; 181                                        | (uint8_t)(TIM1_OCNPolarity & TIM1_CCER1_CC1NP)));
 723  0081 7b0c          	ld	a,(OFST+9,sp)
 724  0083 a408          	and	a,#8
 725  0085 6b03          	ld	(OFST+0,sp),a
 727  0087 7b0b          	ld	a,(OFST+8,sp)
 728  0089 a402          	and	a,#2
 729  008b 1a03          	or	a,(OFST+0,sp)
 730  008d 6b02          	ld	(OFST-1,sp),a
 732  008f 7b08          	ld	a,(OFST+5,sp)
 733  0091 a404          	and	a,#4
 734  0093 6b01          	ld	(OFST-2,sp),a
 736  0095 7b05          	ld	a,(OFST+2,sp)
 737  0097 a401          	and	a,#1
 738  0099 1a01          	or	a,(OFST-2,sp)
 739  009b 1a02          	or	a,(OFST-1,sp)
 740  009d ca525c        	or	a,21084
 741  00a0 c7525c        	ld	21084,a
 742                     ; 184   TIM1->CCMR1 = (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_OCM)) | 
 742                     ; 185                           (uint8_t)TIM1_OCMode);
 744  00a3 c65258        	ld	a,21080
 745  00a6 a48f          	and	a,#143
 746  00a8 1a04          	or	a,(OFST+1,sp)
 747  00aa c75258        	ld	21080,a
 748                     ; 188   TIM1->OISR &= (uint8_t)(~(TIM1_OISR_OIS1 | TIM1_OISR_OIS1N));
 750  00ad c6526f        	ld	a,21103
 751  00b0 a4fc          	and	a,#252
 752  00b2 c7526f        	ld	21103,a
 753                     ; 190   TIM1->OISR |= (uint8_t)((uint8_t)( TIM1_OCIdleState & TIM1_OISR_OIS1 ) | 
 753                     ; 191                           (uint8_t)( TIM1_OCNIdleState & TIM1_OISR_OIS1N ));
 755  00b5 7b0e          	ld	a,(OFST+11,sp)
 756  00b7 a402          	and	a,#2
 757  00b9 6b03          	ld	(OFST+0,sp),a
 759  00bb 7b0d          	ld	a,(OFST+10,sp)
 760  00bd a401          	and	a,#1
 761  00bf 1a03          	or	a,(OFST+0,sp)
 762  00c1 ca526f        	or	a,21103
 763  00c4 c7526f        	ld	21103,a
 764                     ; 194   TIM1->CCR1H = (uint8_t)(TIM1_Pulse >> 8);
 766  00c7 7b09          	ld	a,(OFST+6,sp)
 767  00c9 c75265        	ld	21093,a
 768                     ; 195   TIM1->CCR1L = (uint8_t)(TIM1_Pulse);
 770  00cc 7b0a          	ld	a,(OFST+7,sp)
 771  00ce c75266        	ld	21094,a
 772                     ; 196 }
 775  00d1 5b05          	addw	sp,#5
 776  00d3 81            	ret	
 777  00d4               LC001:
 778  00d4 89            	pushw	x
 779  00d5 5f            	clrw	x
 780  00d6 89            	pushw	x
 781  00d7 ae0000        	ldw	x,#L101
 782  00da cd0000        	call	_assert_failed
 784  00dd 5b04          	addw	sp,#4
 785  00df 81            	ret	
 890                     ; 217 void TIM1_OC2Init(TIM1_OCMode_TypeDef TIM1_OCMode,
 890                     ; 218                   TIM1_OutputState_TypeDef TIM1_OutputState,
 890                     ; 219                   TIM1_OutputNState_TypeDef TIM1_OutputNState,
 890                     ; 220                   uint16_t TIM1_Pulse,
 890                     ; 221                   TIM1_OCPolarity_TypeDef TIM1_OCPolarity,
 890                     ; 222                   TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity,
 890                     ; 223                   TIM1_OCIdleState_TypeDef TIM1_OCIdleState,
 890                     ; 224                   TIM1_OCNIdleState_TypeDef TIM1_OCNIdleState)
 890                     ; 225 {
 891                     .text:	section	.text,new
 892  0000               _TIM1_OC2Init:
 894  0000 89            	pushw	x
 895  0001 5203          	subw	sp,#3
 896       00000003      OFST:	set	3
 899                     ; 227   assert_param(IS_TIM1_OC_MODE_OK(TIM1_OCMode));
 901  0003 9e            	ld	a,xh
 902  0004 4d            	tnz	a
 903  0005 271f          	jreq	L021
 904  0007 9e            	ld	a,xh
 905  0008 a110          	cp	a,#16
 906  000a 271a          	jreq	L021
 907  000c 9e            	ld	a,xh
 908  000d a120          	cp	a,#32
 909  000f 2715          	jreq	L021
 910  0011 9e            	ld	a,xh
 911  0012 a130          	cp	a,#48
 912  0014 2710          	jreq	L021
 913  0016 9e            	ld	a,xh
 914  0017 a160          	cp	a,#96
 915  0019 270b          	jreq	L021
 916  001b 9e            	ld	a,xh
 917  001c a170          	cp	a,#112
 918  001e 2706          	jreq	L021
 919  0020 ae00e3        	ldw	x,#227
 920  0023 cd00d4        	call	LC002
 921  0026               L021:
 922                     ; 228   assert_param(IS_TIM1_OUTPUT_STATE_OK(TIM1_OutputState));
 924  0026 7b05          	ld	a,(OFST+2,sp)
 925  0028 270a          	jreq	L031
 926  002a a111          	cp	a,#17
 927  002c 2706          	jreq	L031
 928  002e ae00e4        	ldw	x,#228
 929  0031 cd00d4        	call	LC002
 930  0034               L031:
 931                     ; 229   assert_param(IS_TIM1_OUTPUTN_STATE_OK(TIM1_OutputNState));
 933  0034 7b08          	ld	a,(OFST+5,sp)
 934  0036 270a          	jreq	L041
 935  0038 a144          	cp	a,#68
 936  003a 2706          	jreq	L041
 937  003c ae00e5        	ldw	x,#229
 938  003f cd00d4        	call	LC002
 939  0042               L041:
 940                     ; 230   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
 942  0042 7b0b          	ld	a,(OFST+8,sp)
 943  0044 270a          	jreq	L051
 944  0046 a122          	cp	a,#34
 945  0048 2706          	jreq	L051
 946  004a ae00e6        	ldw	x,#230
 947  004d cd00d4        	call	LC002
 948  0050               L051:
 949                     ; 231   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
 951  0050 7b0c          	ld	a,(OFST+9,sp)
 952  0052 2709          	jreq	L061
 953  0054 a188          	cp	a,#136
 954  0056 2705          	jreq	L061
 955  0058 ae00e7        	ldw	x,#231
 956  005b ad77          	call	LC002
 957  005d               L061:
 958                     ; 232   assert_param(IS_TIM1_OCIDLE_STATE_OK(TIM1_OCIdleState));
 960  005d 7b0d          	ld	a,(OFST+10,sp)
 961  005f a155          	cp	a,#85
 962  0061 2708          	jreq	L071
 963  0063 4d            	tnz	a
 964  0064 2705          	jreq	L071
 965  0066 ae00e8        	ldw	x,#232
 966  0069 ad69          	call	LC002
 967  006b               L071:
 968                     ; 233   assert_param(IS_TIM1_OCNIDLE_STATE_OK(TIM1_OCNIdleState));
 970  006b 7b0e          	ld	a,(OFST+11,sp)
 971  006d a12a          	cp	a,#42
 972  006f 2708          	jreq	L002
 973  0071 4d            	tnz	a
 974  0072 2705          	jreq	L002
 975  0074 ae00e9        	ldw	x,#233
 976  0077 ad5b          	call	LC002
 977  0079               L002:
 978                     ; 237   TIM1->CCER1 &= (uint8_t)(~( TIM1_CCER1_CC2E | TIM1_CCER1_CC2NE | 
 978                     ; 238                              TIM1_CCER1_CC2P | TIM1_CCER1_CC2NP));
 980  0079 c6525c        	ld	a,21084
 981  007c a40f          	and	a,#15
 982  007e c7525c        	ld	21084,a
 983                     ; 242   TIM1->CCER1 |= (uint8_t)((uint8_t)((uint8_t)(TIM1_OutputState & TIM1_CCER1_CC2E  ) | 
 983                     ; 243                                      (uint8_t)(TIM1_OutputNState & TIM1_CCER1_CC2NE )) | 
 983                     ; 244                            (uint8_t)((uint8_t)(TIM1_OCPolarity  & TIM1_CCER1_CC2P  ) | 
 983                     ; 245                                      (uint8_t)(TIM1_OCNPolarity & TIM1_CCER1_CC2NP )));
 985  0081 7b0c          	ld	a,(OFST+9,sp)
 986  0083 a480          	and	a,#128
 987  0085 6b03          	ld	(OFST+0,sp),a
 989  0087 7b0b          	ld	a,(OFST+8,sp)
 990  0089 a420          	and	a,#32
 991  008b 1a03          	or	a,(OFST+0,sp)
 992  008d 6b02          	ld	(OFST-1,sp),a
 994  008f 7b08          	ld	a,(OFST+5,sp)
 995  0091 a440          	and	a,#64
 996  0093 6b01          	ld	(OFST-2,sp),a
 998  0095 7b05          	ld	a,(OFST+2,sp)
 999  0097 a410          	and	a,#16
1000  0099 1a01          	or	a,(OFST-2,sp)
1001  009b 1a02          	or	a,(OFST-1,sp)
1002  009d ca525c        	or	a,21084
1003  00a0 c7525c        	ld	21084,a
1004                     ; 248   TIM1->CCMR2 = (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_OCM)) | 
1004                     ; 249                           (uint8_t)TIM1_OCMode);
1006  00a3 c65259        	ld	a,21081
1007  00a6 a48f          	and	a,#143
1008  00a8 1a04          	or	a,(OFST+1,sp)
1009  00aa c75259        	ld	21081,a
1010                     ; 252   TIM1->OISR &= (uint8_t)(~(TIM1_OISR_OIS2 | TIM1_OISR_OIS2N));
1012  00ad c6526f        	ld	a,21103
1013  00b0 a4f3          	and	a,#243
1014  00b2 c7526f        	ld	21103,a
1015                     ; 254   TIM1->OISR |= (uint8_t)((uint8_t)(TIM1_OISR_OIS2 & TIM1_OCIdleState) | 
1015                     ; 255                           (uint8_t)(TIM1_OISR_OIS2N & TIM1_OCNIdleState));
1017  00b5 7b0e          	ld	a,(OFST+11,sp)
1018  00b7 a408          	and	a,#8
1019  00b9 6b03          	ld	(OFST+0,sp),a
1021  00bb 7b0d          	ld	a,(OFST+10,sp)
1022  00bd a404          	and	a,#4
1023  00bf 1a03          	or	a,(OFST+0,sp)
1024  00c1 ca526f        	or	a,21103
1025  00c4 c7526f        	ld	21103,a
1026                     ; 258   TIM1->CCR2H = (uint8_t)(TIM1_Pulse >> 8);
1028  00c7 7b09          	ld	a,(OFST+6,sp)
1029  00c9 c75267        	ld	21095,a
1030                     ; 259   TIM1->CCR2L = (uint8_t)(TIM1_Pulse);
1032  00cc 7b0a          	ld	a,(OFST+7,sp)
1033  00ce c75268        	ld	21096,a
1034                     ; 260 }
1037  00d1 5b05          	addw	sp,#5
1038  00d3 81            	ret	
1039  00d4               LC002:
1040  00d4 89            	pushw	x
1041  00d5 5f            	clrw	x
1042  00d6 89            	pushw	x
1043  00d7 ae0000        	ldw	x,#L101
1044  00da cd0000        	call	_assert_failed
1046  00dd 5b04          	addw	sp,#4
1047  00df 81            	ret	
1152                     ; 281 void TIM1_OC3Init(TIM1_OCMode_TypeDef TIM1_OCMode,
1152                     ; 282                   TIM1_OutputState_TypeDef TIM1_OutputState,
1152                     ; 283                   TIM1_OutputNState_TypeDef TIM1_OutputNState,
1152                     ; 284                   uint16_t TIM1_Pulse,
1152                     ; 285                   TIM1_OCPolarity_TypeDef TIM1_OCPolarity,
1152                     ; 286                   TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity,
1152                     ; 287                   TIM1_OCIdleState_TypeDef TIM1_OCIdleState,
1152                     ; 288                   TIM1_OCNIdleState_TypeDef TIM1_OCNIdleState)
1152                     ; 289 {
1153                     .text:	section	.text,new
1154  0000               _TIM1_OC3Init:
1156  0000 89            	pushw	x
1157  0001 5203          	subw	sp,#3
1158       00000003      OFST:	set	3
1161                     ; 291   assert_param(IS_TIM1_OC_MODE_OK(TIM1_OCMode));
1163  0003 9e            	ld	a,xh
1164  0004 4d            	tnz	a
1165  0005 271f          	jreq	L212
1166  0007 9e            	ld	a,xh
1167  0008 a110          	cp	a,#16
1168  000a 271a          	jreq	L212
1169  000c 9e            	ld	a,xh
1170  000d a120          	cp	a,#32
1171  000f 2715          	jreq	L212
1172  0011 9e            	ld	a,xh
1173  0012 a130          	cp	a,#48
1174  0014 2710          	jreq	L212
1175  0016 9e            	ld	a,xh
1176  0017 a160          	cp	a,#96
1177  0019 270b          	jreq	L212
1178  001b 9e            	ld	a,xh
1179  001c a170          	cp	a,#112
1180  001e 2706          	jreq	L212
1181  0020 ae0123        	ldw	x,#291
1182  0023 cd00d4        	call	LC003
1183  0026               L212:
1184                     ; 292   assert_param(IS_TIM1_OUTPUT_STATE_OK(TIM1_OutputState));
1186  0026 7b05          	ld	a,(OFST+2,sp)
1187  0028 270a          	jreq	L222
1188  002a a111          	cp	a,#17
1189  002c 2706          	jreq	L222
1190  002e ae0124        	ldw	x,#292
1191  0031 cd00d4        	call	LC003
1192  0034               L222:
1193                     ; 293   assert_param(IS_TIM1_OUTPUTN_STATE_OK(TIM1_OutputNState));
1195  0034 7b08          	ld	a,(OFST+5,sp)
1196  0036 270a          	jreq	L232
1197  0038 a144          	cp	a,#68
1198  003a 2706          	jreq	L232
1199  003c ae0125        	ldw	x,#293
1200  003f cd00d4        	call	LC003
1201  0042               L232:
1202                     ; 294   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
1204  0042 7b0b          	ld	a,(OFST+8,sp)
1205  0044 270a          	jreq	L242
1206  0046 a122          	cp	a,#34
1207  0048 2706          	jreq	L242
1208  004a ae0126        	ldw	x,#294
1209  004d cd00d4        	call	LC003
1210  0050               L242:
1211                     ; 295   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
1213  0050 7b0c          	ld	a,(OFST+9,sp)
1214  0052 2709          	jreq	L252
1215  0054 a188          	cp	a,#136
1216  0056 2705          	jreq	L252
1217  0058 ae0127        	ldw	x,#295
1218  005b ad77          	call	LC003
1219  005d               L252:
1220                     ; 296   assert_param(IS_TIM1_OCIDLE_STATE_OK(TIM1_OCIdleState));
1222  005d 7b0d          	ld	a,(OFST+10,sp)
1223  005f a155          	cp	a,#85
1224  0061 2708          	jreq	L262
1225  0063 4d            	tnz	a
1226  0064 2705          	jreq	L262
1227  0066 ae0128        	ldw	x,#296
1228  0069 ad69          	call	LC003
1229  006b               L262:
1230                     ; 297   assert_param(IS_TIM1_OCNIDLE_STATE_OK(TIM1_OCNIdleState));
1232  006b 7b0e          	ld	a,(OFST+11,sp)
1233  006d a12a          	cp	a,#42
1234  006f 2708          	jreq	L272
1235  0071 4d            	tnz	a
1236  0072 2705          	jreq	L272
1237  0074 ae0129        	ldw	x,#297
1238  0077 ad5b          	call	LC003
1239  0079               L272:
1240                     ; 301   TIM1->CCER2 &= (uint8_t)(~( TIM1_CCER2_CC3E | TIM1_CCER2_CC3NE | 
1240                     ; 302                              TIM1_CCER2_CC3P | TIM1_CCER2_CC3NP));
1242  0079 c6525d        	ld	a,21085
1243  007c a4f0          	and	a,#240
1244  007e c7525d        	ld	21085,a
1245                     ; 305   TIM1->CCER2 |= (uint8_t)((uint8_t)((uint8_t)(TIM1_OutputState  & TIM1_CCER2_CC3E   ) |
1245                     ; 306                                      (uint8_t)(TIM1_OutputNState & TIM1_CCER2_CC3NE  )) | 
1245                     ; 307                            (uint8_t)((uint8_t)(TIM1_OCPolarity   & TIM1_CCER2_CC3P   ) | 
1245                     ; 308                                      (uint8_t)(TIM1_OCNPolarity  & TIM1_CCER2_CC3NP  )));
1247  0081 7b0c          	ld	a,(OFST+9,sp)
1248  0083 a408          	and	a,#8
1249  0085 6b03          	ld	(OFST+0,sp),a
1251  0087 7b0b          	ld	a,(OFST+8,sp)
1252  0089 a402          	and	a,#2
1253  008b 1a03          	or	a,(OFST+0,sp)
1254  008d 6b02          	ld	(OFST-1,sp),a
1256  008f 7b08          	ld	a,(OFST+5,sp)
1257  0091 a404          	and	a,#4
1258  0093 6b01          	ld	(OFST-2,sp),a
1260  0095 7b05          	ld	a,(OFST+2,sp)
1261  0097 a401          	and	a,#1
1262  0099 1a01          	or	a,(OFST-2,sp)
1263  009b 1a02          	or	a,(OFST-1,sp)
1264  009d ca525d        	or	a,21085
1265  00a0 c7525d        	ld	21085,a
1266                     ; 311   TIM1->CCMR3 = (uint8_t)((uint8_t)(TIM1->CCMR3 & (uint8_t)(~TIM1_CCMR_OCM)) | 
1266                     ; 312                           (uint8_t)TIM1_OCMode);
1268  00a3 c6525a        	ld	a,21082
1269  00a6 a48f          	and	a,#143
1270  00a8 1a04          	or	a,(OFST+1,sp)
1271  00aa c7525a        	ld	21082,a
1272                     ; 315   TIM1->OISR &= (uint8_t)(~(TIM1_OISR_OIS3 | TIM1_OISR_OIS3N));
1274  00ad c6526f        	ld	a,21103
1275  00b0 a4cf          	and	a,#207
1276  00b2 c7526f        	ld	21103,a
1277                     ; 317   TIM1->OISR |= (uint8_t)((uint8_t)(TIM1_OISR_OIS3 & TIM1_OCIdleState) | 
1277                     ; 318                           (uint8_t)(TIM1_OISR_OIS3N & TIM1_OCNIdleState));
1279  00b5 7b0e          	ld	a,(OFST+11,sp)
1280  00b7 a420          	and	a,#32
1281  00b9 6b03          	ld	(OFST+0,sp),a
1283  00bb 7b0d          	ld	a,(OFST+10,sp)
1284  00bd a410          	and	a,#16
1285  00bf 1a03          	or	a,(OFST+0,sp)
1286  00c1 ca526f        	or	a,21103
1287  00c4 c7526f        	ld	21103,a
1288                     ; 321   TIM1->CCR3H = (uint8_t)(TIM1_Pulse >> 8);
1290  00c7 7b09          	ld	a,(OFST+6,sp)
1291  00c9 c75269        	ld	21097,a
1292                     ; 322   TIM1->CCR3L = (uint8_t)(TIM1_Pulse);
1294  00cc 7b0a          	ld	a,(OFST+7,sp)
1295  00ce c7526a        	ld	21098,a
1296                     ; 323 }
1299  00d1 5b05          	addw	sp,#5
1300  00d3 81            	ret	
1301  00d4               LC003:
1302  00d4 89            	pushw	x
1303  00d5 5f            	clrw	x
1304  00d6 89            	pushw	x
1305  00d7 ae0000        	ldw	x,#L101
1306  00da cd0000        	call	_assert_failed
1308  00dd 5b04          	addw	sp,#4
1309  00df 81            	ret	
1384                     ; 338 void TIM1_OC4Init(TIM1_OCMode_TypeDef TIM1_OCMode,
1384                     ; 339                   TIM1_OutputState_TypeDef TIM1_OutputState,
1384                     ; 340                   uint16_t TIM1_Pulse,
1384                     ; 341                   TIM1_OCPolarity_TypeDef TIM1_OCPolarity,
1384                     ; 342                   TIM1_OCIdleState_TypeDef TIM1_OCIdleState)
1384                     ; 343 {
1385                     .text:	section	.text,new
1386  0000               _TIM1_OC4Init:
1388  0000 89            	pushw	x
1389  0001 88            	push	a
1390       00000001      OFST:	set	1
1393                     ; 345   assert_param(IS_TIM1_OC_MODE_OK(TIM1_OCMode));
1395  0002 9e            	ld	a,xh
1396  0003 4d            	tnz	a
1397  0004 271e          	jreq	L403
1398  0006 9e            	ld	a,xh
1399  0007 a110          	cp	a,#16
1400  0009 2719          	jreq	L403
1401  000b 9e            	ld	a,xh
1402  000c a120          	cp	a,#32
1403  000e 2714          	jreq	L403
1404  0010 9e            	ld	a,xh
1405  0011 a130          	cp	a,#48
1406  0013 270f          	jreq	L403
1407  0015 9e            	ld	a,xh
1408  0016 a160          	cp	a,#96
1409  0018 270a          	jreq	L403
1410  001a 9e            	ld	a,xh
1411  001b a170          	cp	a,#112
1412  001d 2705          	jreq	L403
1413  001f ae0159        	ldw	x,#345
1414  0022 ad6b          	call	LC004
1415  0024               L403:
1416                     ; 346   assert_param(IS_TIM1_OUTPUT_STATE_OK(TIM1_OutputState));
1418  0024 7b03          	ld	a,(OFST+2,sp)
1419  0026 2709          	jreq	L413
1420  0028 a111          	cp	a,#17
1421  002a 2705          	jreq	L413
1422  002c ae015a        	ldw	x,#346
1423  002f ad5e          	call	LC004
1424  0031               L413:
1425                     ; 347   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
1427  0031 7b08          	ld	a,(OFST+7,sp)
1428  0033 2709          	jreq	L423
1429  0035 a122          	cp	a,#34
1430  0037 2705          	jreq	L423
1431  0039 ae015b        	ldw	x,#347
1432  003c ad51          	call	LC004
1433  003e               L423:
1434                     ; 348   assert_param(IS_TIM1_OCIDLE_STATE_OK(TIM1_OCIdleState));
1436  003e 7b09          	ld	a,(OFST+8,sp)
1437  0040 a155          	cp	a,#85
1438  0042 2708          	jreq	L433
1439  0044 4d            	tnz	a
1440  0045 2705          	jreq	L433
1441  0047 ae015c        	ldw	x,#348
1442  004a ad43          	call	LC004
1443  004c               L433:
1444                     ; 351   TIM1->CCER2 &= (uint8_t)(~(TIM1_CCER2_CC4E | TIM1_CCER2_CC4P));
1446  004c c6525d        	ld	a,21085
1447  004f a4cf          	and	a,#207
1448  0051 c7525d        	ld	21085,a
1449                     ; 353   TIM1->CCER2 |= (uint8_t)((uint8_t)(TIM1_OutputState & TIM1_CCER2_CC4E ) |  
1449                     ; 354                            (uint8_t)(TIM1_OCPolarity  & TIM1_CCER2_CC4P ));
1451  0054 7b08          	ld	a,(OFST+7,sp)
1452  0056 a420          	and	a,#32
1453  0058 6b01          	ld	(OFST+0,sp),a
1455  005a 7b03          	ld	a,(OFST+2,sp)
1456  005c a410          	and	a,#16
1457  005e 1a01          	or	a,(OFST+0,sp)
1458  0060 ca525d        	or	a,21085
1459  0063 c7525d        	ld	21085,a
1460                     ; 357   TIM1->CCMR4 = (uint8_t)((uint8_t)(TIM1->CCMR4 & (uint8_t)(~TIM1_CCMR_OCM)) | 
1460                     ; 358                           TIM1_OCMode);
1462  0066 c6525b        	ld	a,21083
1463  0069 a48f          	and	a,#143
1464  006b 1a02          	or	a,(OFST+1,sp)
1465  006d c7525b        	ld	21083,a
1466                     ; 361   if (TIM1_OCIdleState != TIM1_OCIDLESTATE_RESET)
1468  0070 7b09          	ld	a,(OFST+8,sp)
1469  0072 270a          	jreq	L734
1470                     ; 363     TIM1->OISR |= (uint8_t)(~TIM1_CCER2_CC4P);
1472  0074 c6526f        	ld	a,21103
1473  0077 aadf          	or	a,#223
1474  0079 c7526f        	ld	21103,a
1476  007c 2004          	jra	L144
1477  007e               L734:
1478                     ; 367     TIM1->OISR &= (uint8_t)(~TIM1_OISR_OIS4);
1480  007e 721d526f      	bres	21103,#6
1481  0082               L144:
1482                     ; 371   TIM1->CCR4H = (uint8_t)(TIM1_Pulse >> 8);
1484  0082 7b06          	ld	a,(OFST+5,sp)
1485  0084 c7526b        	ld	21099,a
1486                     ; 372   TIM1->CCR4L = (uint8_t)(TIM1_Pulse);
1488  0087 7b07          	ld	a,(OFST+6,sp)
1489  0089 c7526c        	ld	21100,a
1490                     ; 373 }
1493  008c 5b03          	addw	sp,#3
1494  008e 81            	ret	
1495  008f               LC004:
1496  008f 89            	pushw	x
1497  0090 5f            	clrw	x
1498  0091 89            	pushw	x
1499  0092 ae0000        	ldw	x,#L101
1500  0095 cd0000        	call	_assert_failed
1502  0098 5b04          	addw	sp,#4
1503  009a 81            	ret	
1709                     ; 388 void TIM1_BDTRConfig(TIM1_OSSIState_TypeDef TIM1_OSSIState,
1709                     ; 389                      TIM1_LockLevel_TypeDef TIM1_LockLevel,
1709                     ; 390                      uint8_t TIM1_DeadTime,
1709                     ; 391                      TIM1_BreakState_TypeDef TIM1_Break,
1709                     ; 392                      TIM1_BreakPolarity_TypeDef TIM1_BreakPolarity,
1709                     ; 393                      TIM1_AutomaticOutput_TypeDef TIM1_AutomaticOutput)
1709                     ; 394 {
1710                     .text:	section	.text,new
1711  0000               _TIM1_BDTRConfig:
1713  0000 89            	pushw	x
1714  0001 88            	push	a
1715       00000001      OFST:	set	1
1718                     ; 396   assert_param(IS_TIM1_OSSI_STATE_OK(TIM1_OSSIState));
1720  0002 9e            	ld	a,xh
1721  0003 a104          	cp	a,#4
1722  0005 2709          	jreq	L643
1723  0007 9e            	ld	a,xh
1724  0008 4d            	tnz	a
1725  0009 2705          	jreq	L643
1726  000b ae018c        	ldw	x,#396
1727  000e ad57          	call	LC005
1728  0010               L643:
1729                     ; 397   assert_param(IS_TIM1_LOCK_LEVEL_OK(TIM1_LockLevel));
1731  0010 7b03          	ld	a,(OFST+2,sp)
1732  0012 2711          	jreq	L653
1733  0014 a101          	cp	a,#1
1734  0016 270d          	jreq	L653
1735  0018 a102          	cp	a,#2
1736  001a 2709          	jreq	L653
1737  001c a103          	cp	a,#3
1738  001e 2705          	jreq	L653
1739  0020 ae018d        	ldw	x,#397
1740  0023 ad42          	call	LC005
1741  0025               L653:
1742                     ; 398   assert_param(IS_TIM1_BREAK_STATE_OK(TIM1_Break));
1744  0025 7b07          	ld	a,(OFST+6,sp)
1745  0027 a110          	cp	a,#16
1746  0029 2708          	jreq	L663
1747  002b 4d            	tnz	a
1748  002c 2705          	jreq	L663
1749  002e ae018e        	ldw	x,#398
1750  0031 ad34          	call	LC005
1751  0033               L663:
1752                     ; 399   assert_param(IS_TIM1_BREAK_POLARITY_OK(TIM1_BreakPolarity));
1754  0033 7b08          	ld	a,(OFST+7,sp)
1755  0035 2709          	jreq	L673
1756  0037 a120          	cp	a,#32
1757  0039 2705          	jreq	L673
1758  003b ae018f        	ldw	x,#399
1759  003e ad27          	call	LC005
1760  0040               L673:
1761                     ; 400   assert_param(IS_TIM1_AUTOMATIC_OUTPUT_STATE_OK(TIM1_AutomaticOutput));
1763  0040 7b09          	ld	a,(OFST+8,sp)
1764  0042 a140          	cp	a,#64
1765  0044 2708          	jreq	L604
1766  0046 4d            	tnz	a
1767  0047 2705          	jreq	L604
1768  0049 ae0190        	ldw	x,#400
1769  004c ad19          	call	LC005
1770  004e               L604:
1771                     ; 402   TIM1->DTR = (uint8_t)(TIM1_DeadTime);
1773  004e 7b06          	ld	a,(OFST+5,sp)
1774  0050 c7526e        	ld	21102,a
1775                     ; 406   TIM1->BKR  =  (uint8_t)((uint8_t)(TIM1_OSSIState | (uint8_t)TIM1_LockLevel)  | 
1775                     ; 407                           (uint8_t)((uint8_t)(TIM1_Break | (uint8_t)TIM1_BreakPolarity)  | 
1775                     ; 408                           (uint8_t)TIM1_AutomaticOutput));
1777  0053 7b07          	ld	a,(OFST+6,sp)
1778  0055 1a08          	or	a,(OFST+7,sp)
1779  0057 1a09          	or	a,(OFST+8,sp)
1780  0059 6b01          	ld	(OFST+0,sp),a
1782  005b 7b02          	ld	a,(OFST+1,sp)
1783  005d 1a03          	or	a,(OFST+2,sp)
1784  005f 1a01          	or	a,(OFST+0,sp)
1785  0061 c7526d        	ld	21101,a
1786                     ; 409 }
1789  0064 5b03          	addw	sp,#3
1790  0066 81            	ret	
1791  0067               LC005:
1792  0067 89            	pushw	x
1793  0068 5f            	clrw	x
1794  0069 89            	pushw	x
1795  006a ae0000        	ldw	x,#L101
1796  006d cd0000        	call	_assert_failed
1798  0070 5b04          	addw	sp,#4
1799  0072 81            	ret	
2002                     ; 423 void TIM1_ICInit(TIM1_Channel_TypeDef TIM1_Channel,
2002                     ; 424                  TIM1_ICPolarity_TypeDef TIM1_ICPolarity,
2002                     ; 425                  TIM1_ICSelection_TypeDef TIM1_ICSelection,
2002                     ; 426                  TIM1_ICPSC_TypeDef TIM1_ICPrescaler,
2002                     ; 427                  uint8_t TIM1_ICFilter)
2002                     ; 428 {
2003                     .text:	section	.text,new
2004  0000               _TIM1_ICInit:
2006  0000 89            	pushw	x
2007       00000000      OFST:	set	0
2010                     ; 430   assert_param(IS_TIM1_CHANNEL_OK(TIM1_Channel));
2012  0001 9e            	ld	a,xh
2013  0002 4d            	tnz	a
2014  0003 2714          	jreq	L024
2015  0005 9e            	ld	a,xh
2016  0006 4a            	dec	a
2017  0007 2710          	jreq	L024
2018  0009 9e            	ld	a,xh
2019  000a a102          	cp	a,#2
2020  000c 270b          	jreq	L024
2021  000e 9e            	ld	a,xh
2022  000f a103          	cp	a,#3
2023  0011 2706          	jreq	L024
2024  0013 ae01ae        	ldw	x,#430
2025  0016 cd00b5        	call	LC006
2026  0019               L024:
2027                     ; 431   assert_param(IS_TIM1_IC_POLARITY_OK(TIM1_ICPolarity));
2029  0019 7b02          	ld	a,(OFST+2,sp)
2030  001b 2709          	jreq	L034
2031  001d 4a            	dec	a
2032  001e 2706          	jreq	L034
2033  0020 ae01af        	ldw	x,#431
2034  0023 cd00b5        	call	LC006
2035  0026               L034:
2036                     ; 432   assert_param(IS_TIM1_IC_SELECTION_OK(TIM1_ICSelection));
2038  0026 7b05          	ld	a,(OFST+5,sp)
2039  0028 a101          	cp	a,#1
2040  002a 270d          	jreq	L044
2041  002c a102          	cp	a,#2
2042  002e 2709          	jreq	L044
2043  0030 a103          	cp	a,#3
2044  0032 2705          	jreq	L044
2045  0034 ae01b0        	ldw	x,#432
2046  0037 ad7c          	call	LC006
2047  0039               L044:
2048                     ; 433   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_ICPrescaler));
2050  0039 7b06          	ld	a,(OFST+6,sp)
2051  003b 2711          	jreq	L054
2052  003d a104          	cp	a,#4
2053  003f 270d          	jreq	L054
2054  0041 a108          	cp	a,#8
2055  0043 2709          	jreq	L054
2056  0045 a10c          	cp	a,#12
2057  0047 2705          	jreq	L054
2058  0049 ae01b1        	ldw	x,#433
2059  004c ad67          	call	LC006
2060  004e               L054:
2061                     ; 434   assert_param(IS_TIM1_IC_FILTER_OK(TIM1_ICFilter));
2063  004e 7b07          	ld	a,(OFST+7,sp)
2064  0050 a110          	cp	a,#16
2065  0052 2505          	jrult	L654
2066  0054 ae01b2        	ldw	x,#434
2067  0057 ad5c          	call	LC006
2068  0059               L654:
2069                     ; 436   if (TIM1_Channel == TIM1_CHANNEL_1)
2071  0059 7b01          	ld	a,(OFST+1,sp)
2072  005b 2614          	jrne	L176
2073                     ; 439     TI1_Config((uint8_t)TIM1_ICPolarity,
2073                     ; 440                (uint8_t)TIM1_ICSelection,
2073                     ; 441                (uint8_t)TIM1_ICFilter);
2075  005d 7b07          	ld	a,(OFST+7,sp)
2076  005f 88            	push	a
2077  0060 7b06          	ld	a,(OFST+6,sp)
2078  0062 97            	ld	xl,a
2079  0063 7b03          	ld	a,(OFST+3,sp)
2080  0065 95            	ld	xh,a
2081  0066 cd0000        	call	L3_TI1_Config
2083  0069 84            	pop	a
2084                     ; 443     TIM1_SetIC1Prescaler(TIM1_ICPrescaler);
2086  006a 7b06          	ld	a,(OFST+6,sp)
2087  006c cd0000        	call	_TIM1_SetIC1Prescaler
2090  006f 2042          	jra	L376
2091  0071               L176:
2092                     ; 445   else if (TIM1_Channel == TIM1_CHANNEL_2)
2094  0071 a101          	cp	a,#1
2095  0073 2614          	jrne	L576
2096                     ; 448     TI2_Config((uint8_t)TIM1_ICPolarity,
2096                     ; 449                (uint8_t)TIM1_ICSelection,
2096                     ; 450                (uint8_t)TIM1_ICFilter);
2098  0075 7b07          	ld	a,(OFST+7,sp)
2099  0077 88            	push	a
2100  0078 7b06          	ld	a,(OFST+6,sp)
2101  007a 97            	ld	xl,a
2102  007b 7b03          	ld	a,(OFST+3,sp)
2103  007d 95            	ld	xh,a
2104  007e cd0000        	call	L5_TI2_Config
2106  0081 84            	pop	a
2107                     ; 452     TIM1_SetIC2Prescaler(TIM1_ICPrescaler);
2109  0082 7b06          	ld	a,(OFST+6,sp)
2110  0084 cd0000        	call	_TIM1_SetIC2Prescaler
2113  0087 202a          	jra	L376
2114  0089               L576:
2115                     ; 454   else if (TIM1_Channel == TIM1_CHANNEL_3)
2117  0089 a102          	cp	a,#2
2118  008b 2614          	jrne	L107
2119                     ; 457     TI3_Config((uint8_t)TIM1_ICPolarity,
2119                     ; 458                (uint8_t)TIM1_ICSelection,
2119                     ; 459                (uint8_t)TIM1_ICFilter);
2121  008d 7b07          	ld	a,(OFST+7,sp)
2122  008f 88            	push	a
2123  0090 7b06          	ld	a,(OFST+6,sp)
2124  0092 97            	ld	xl,a
2125  0093 7b03          	ld	a,(OFST+3,sp)
2126  0095 95            	ld	xh,a
2127  0096 cd0000        	call	L7_TI3_Config
2129  0099 84            	pop	a
2130                     ; 461     TIM1_SetIC3Prescaler(TIM1_ICPrescaler);
2132  009a 7b06          	ld	a,(OFST+6,sp)
2133  009c cd0000        	call	_TIM1_SetIC3Prescaler
2136  009f 2012          	jra	L376
2137  00a1               L107:
2138                     ; 466     TI4_Config((uint8_t)TIM1_ICPolarity,
2138                     ; 467                (uint8_t)TIM1_ICSelection,
2138                     ; 468                (uint8_t)TIM1_ICFilter);
2140  00a1 7b07          	ld	a,(OFST+7,sp)
2141  00a3 88            	push	a
2142  00a4 7b06          	ld	a,(OFST+6,sp)
2143  00a6 97            	ld	xl,a
2144  00a7 7b03          	ld	a,(OFST+3,sp)
2145  00a9 95            	ld	xh,a
2146  00aa cd0000        	call	L11_TI4_Config
2148  00ad 84            	pop	a
2149                     ; 470     TIM1_SetIC4Prescaler(TIM1_ICPrescaler);
2151  00ae 7b06          	ld	a,(OFST+6,sp)
2152  00b0 cd0000        	call	_TIM1_SetIC4Prescaler
2154  00b3               L376:
2155                     ; 472 }
2158  00b3 85            	popw	x
2159  00b4 81            	ret	
2160  00b5               LC006:
2161  00b5 89            	pushw	x
2162  00b6 5f            	clrw	x
2163  00b7 89            	pushw	x
2164  00b8 ae0000        	ldw	x,#L101
2165  00bb cd0000        	call	_assert_failed
2167  00be 5b04          	addw	sp,#4
2168  00c0 81            	ret	
2265                     ; 488 void TIM1_PWMIConfig(TIM1_Channel_TypeDef TIM1_Channel,
2265                     ; 489                      TIM1_ICPolarity_TypeDef TIM1_ICPolarity,
2265                     ; 490                      TIM1_ICSelection_TypeDef TIM1_ICSelection,
2265                     ; 491                      TIM1_ICPSC_TypeDef TIM1_ICPrescaler,
2265                     ; 492                      uint8_t TIM1_ICFilter)
2265                     ; 493 {
2266                     .text:	section	.text,new
2267  0000               _TIM1_PWMIConfig:
2269  0000 89            	pushw	x
2270  0001 89            	pushw	x
2271       00000002      OFST:	set	2
2274                     ; 494   uint8_t icpolarity = TIM1_ICPOLARITY_RISING;
2276                     ; 495   uint8_t icselection = TIM1_ICSELECTION_DIRECTTI;
2278                     ; 498   assert_param(IS_TIM1_PWMI_CHANNEL_OK(TIM1_Channel));
2280  0002 9e            	ld	a,xh
2281  0003 4d            	tnz	a
2282  0004 270a          	jreq	L015
2283  0006 9e            	ld	a,xh
2284  0007 4a            	dec	a
2285  0008 2706          	jreq	L015
2286  000a ae01f2        	ldw	x,#498
2287  000d cd00ac        	call	LC007
2288  0010               L015:
2289                     ; 499   assert_param(IS_TIM1_IC_POLARITY_OK(TIM1_ICPolarity));
2291  0010 7b04          	ld	a,(OFST+2,sp)
2292  0012 2709          	jreq	L025
2293  0014 4a            	dec	a
2294  0015 2706          	jreq	L025
2295  0017 ae01f3        	ldw	x,#499
2296  001a cd00ac        	call	LC007
2297  001d               L025:
2298                     ; 500   assert_param(IS_TIM1_IC_SELECTION_OK(TIM1_ICSelection));
2300  001d 7b07          	ld	a,(OFST+5,sp)
2301  001f a101          	cp	a,#1
2302  0021 270d          	jreq	L035
2303  0023 a102          	cp	a,#2
2304  0025 2709          	jreq	L035
2305  0027 a103          	cp	a,#3
2306  0029 2705          	jreq	L035
2307  002b ae01f4        	ldw	x,#500
2308  002e ad7c          	call	LC007
2309  0030               L035:
2310                     ; 501   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_ICPrescaler));
2312  0030 7b08          	ld	a,(OFST+6,sp)
2313  0032 2711          	jreq	L045
2314  0034 a104          	cp	a,#4
2315  0036 270d          	jreq	L045
2316  0038 a108          	cp	a,#8
2317  003a 2709          	jreq	L045
2318  003c a10c          	cp	a,#12
2319  003e 2705          	jreq	L045
2320  0040 ae01f5        	ldw	x,#501
2321  0043 ad67          	call	LC007
2322  0045               L045:
2323                     ; 504   if (TIM1_ICPolarity != TIM1_ICPOLARITY_FALLING)
2325  0045 7b04          	ld	a,(OFST+2,sp)
2326  0047 4a            	dec	a
2327  0048 2702          	jreq	L357
2328                     ; 506     icpolarity = TIM1_ICPOLARITY_FALLING;
2330  004a a601          	ld	a,#1
2332  004c               L357:
2333                     ; 510     icpolarity = TIM1_ICPOLARITY_RISING;
2335  004c 6b01          	ld	(OFST-1,sp),a
2337                     ; 514   if (TIM1_ICSelection == TIM1_ICSELECTION_DIRECTTI)
2339  004e 7b07          	ld	a,(OFST+5,sp)
2340  0050 4a            	dec	a
2341  0051 2604          	jrne	L757
2342                     ; 516     icselection = TIM1_ICSELECTION_INDIRECTTI;
2344  0053 a602          	ld	a,#2
2346  0055 2002          	jra	L167
2347  0057               L757:
2348                     ; 520     icselection = TIM1_ICSELECTION_DIRECTTI;
2350  0057 a601          	ld	a,#1
2351  0059               L167:
2352  0059 6b02          	ld	(OFST+0,sp),a
2354                     ; 523   if (TIM1_Channel == TIM1_CHANNEL_1)
2356  005b 7b03          	ld	a,(OFST+1,sp)
2357  005d 2626          	jrne	L367
2358                     ; 526     TI1_Config((uint8_t)TIM1_ICPolarity, (uint8_t)TIM1_ICSelection,
2358                     ; 527                (uint8_t)TIM1_ICFilter);
2360  005f 7b09          	ld	a,(OFST+7,sp)
2361  0061 88            	push	a
2362  0062 7b08          	ld	a,(OFST+6,sp)
2363  0064 97            	ld	xl,a
2364  0065 7b05          	ld	a,(OFST+3,sp)
2365  0067 95            	ld	xh,a
2366  0068 cd0000        	call	L3_TI1_Config
2368  006b 84            	pop	a
2369                     ; 530     TIM1_SetIC1Prescaler(TIM1_ICPrescaler);
2371  006c 7b08          	ld	a,(OFST+6,sp)
2372  006e cd0000        	call	_TIM1_SetIC1Prescaler
2374                     ; 533     TI2_Config(icpolarity, icselection, TIM1_ICFilter);
2376  0071 7b09          	ld	a,(OFST+7,sp)
2377  0073 88            	push	a
2378  0074 7b03          	ld	a,(OFST+1,sp)
2379  0076 97            	ld	xl,a
2380  0077 7b02          	ld	a,(OFST+0,sp)
2381  0079 95            	ld	xh,a
2382  007a cd0000        	call	L5_TI2_Config
2384  007d 84            	pop	a
2385                     ; 536     TIM1_SetIC2Prescaler(TIM1_ICPrescaler);
2387  007e 7b08          	ld	a,(OFST+6,sp)
2388  0080 cd0000        	call	_TIM1_SetIC2Prescaler
2391  0083 2024          	jra	L567
2392  0085               L367:
2393                     ; 541     TI2_Config((uint8_t)TIM1_ICPolarity, (uint8_t)TIM1_ICSelection,
2393                     ; 542                (uint8_t)TIM1_ICFilter);
2395  0085 7b09          	ld	a,(OFST+7,sp)
2396  0087 88            	push	a
2397  0088 7b08          	ld	a,(OFST+6,sp)
2398  008a 97            	ld	xl,a
2399  008b 7b05          	ld	a,(OFST+3,sp)
2400  008d 95            	ld	xh,a
2401  008e cd0000        	call	L5_TI2_Config
2403  0091 84            	pop	a
2404                     ; 545     TIM1_SetIC2Prescaler(TIM1_ICPrescaler);
2406  0092 7b08          	ld	a,(OFST+6,sp)
2407  0094 cd0000        	call	_TIM1_SetIC2Prescaler
2409                     ; 548     TI1_Config(icpolarity, icselection, TIM1_ICFilter);
2411  0097 7b09          	ld	a,(OFST+7,sp)
2412  0099 88            	push	a
2413  009a 7b03          	ld	a,(OFST+1,sp)
2414  009c 97            	ld	xl,a
2415  009d 7b02          	ld	a,(OFST+0,sp)
2416  009f 95            	ld	xh,a
2417  00a0 cd0000        	call	L3_TI1_Config
2419  00a3 84            	pop	a
2420                     ; 551     TIM1_SetIC1Prescaler(TIM1_ICPrescaler);
2422  00a4 7b08          	ld	a,(OFST+6,sp)
2423  00a6 cd0000        	call	_TIM1_SetIC1Prescaler
2425  00a9               L567:
2426                     ; 553 }
2429  00a9 5b04          	addw	sp,#4
2430  00ab 81            	ret	
2431  00ac               LC007:
2432  00ac 89            	pushw	x
2433  00ad 5f            	clrw	x
2434  00ae 89            	pushw	x
2435  00af ae0000        	ldw	x,#L101
2436  00b2 cd0000        	call	_assert_failed
2438  00b5 5b04          	addw	sp,#4
2439  00b7 81            	ret	
2495                     ; 561 void TIM1_Cmd(FunctionalState NewState)
2495                     ; 562 {
2496                     .text:	section	.text,new
2497  0000               _TIM1_Cmd:
2499  0000 88            	push	a
2500       00000000      OFST:	set	0
2503                     ; 564   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2505  0001 4d            	tnz	a
2506  0002 2711          	jreq	L275
2507  0004 4a            	dec	a
2508  0005 270e          	jreq	L275
2509  0007 ae0234        	ldw	x,#564
2510  000a 89            	pushw	x
2511  000b 5f            	clrw	x
2512  000c 89            	pushw	x
2513  000d ae0000        	ldw	x,#L101
2514  0010 cd0000        	call	_assert_failed
2516  0013 5b04          	addw	sp,#4
2517  0015               L275:
2518                     ; 567   if (NewState != DISABLE)
2520  0015 7b01          	ld	a,(OFST+1,sp)
2521  0017 2706          	jreq	L5101
2522                     ; 569     TIM1->CR1 |= TIM1_CR1_CEN;
2524  0019 72105250      	bset	21072,#0
2526  001d 2004          	jra	L7101
2527  001f               L5101:
2528                     ; 573     TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN);
2530  001f 72115250      	bres	21072,#0
2531  0023               L7101:
2532                     ; 575 }
2535  0023 84            	pop	a
2536  0024 81            	ret	
2573                     ; 583 void TIM1_CtrlPWMOutputs(FunctionalState NewState)
2573                     ; 584 {
2574                     .text:	section	.text,new
2575  0000               _TIM1_CtrlPWMOutputs:
2577  0000 88            	push	a
2578       00000000      OFST:	set	0
2581                     ; 586   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2583  0001 4d            	tnz	a
2584  0002 2711          	jreq	L406
2585  0004 4a            	dec	a
2586  0005 270e          	jreq	L406
2587  0007 ae024a        	ldw	x,#586
2588  000a 89            	pushw	x
2589  000b 5f            	clrw	x
2590  000c 89            	pushw	x
2591  000d ae0000        	ldw	x,#L101
2592  0010 cd0000        	call	_assert_failed
2594  0013 5b04          	addw	sp,#4
2595  0015               L406:
2596                     ; 590   if (NewState != DISABLE)
2598  0015 7b01          	ld	a,(OFST+1,sp)
2599  0017 2706          	jreq	L7301
2600                     ; 592     TIM1->BKR |= TIM1_BKR_MOE;
2602  0019 721e526d      	bset	21101,#7
2604  001d 2004          	jra	L1401
2605  001f               L7301:
2606                     ; 596     TIM1->BKR &= (uint8_t)(~TIM1_BKR_MOE);
2608  001f 721f526d      	bres	21101,#7
2609  0023               L1401:
2610                     ; 598 }
2613  0023 84            	pop	a
2614  0024 81            	ret	
2722                     ; 617 void TIM1_ITConfig(TIM1_IT_TypeDef  TIM1_IT, FunctionalState NewState)
2722                     ; 618 {
2723                     .text:	section	.text,new
2724  0000               _TIM1_ITConfig:
2726  0000 89            	pushw	x
2727       00000000      OFST:	set	0
2730                     ; 620   assert_param(IS_TIM1_IT_OK(TIM1_IT));
2732  0001 9e            	ld	a,xh
2733  0002 4d            	tnz	a
2734  0003 2605          	jrne	L416
2735  0005 ae026c        	ldw	x,#620
2736  0008 ad22          	call	LC008
2737  000a               L416:
2738                     ; 621   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
2740  000a 7b02          	ld	a,(OFST+2,sp)
2741  000c 2708          	jreq	L426
2742  000e 4a            	dec	a
2743  000f 2705          	jreq	L426
2744  0011 ae026d        	ldw	x,#621
2745  0014 ad16          	call	LC008
2746  0016               L426:
2747                     ; 623   if (NewState != DISABLE)
2749  0016 7b02          	ld	a,(OFST+2,sp)
2750  0018 2707          	jreq	L1111
2751                     ; 626     TIM1->IER |= (uint8_t)TIM1_IT;
2753  001a c65254        	ld	a,21076
2754  001d 1a01          	or	a,(OFST+1,sp)
2756  001f 2006          	jra	L3111
2757  0021               L1111:
2758                     ; 631     TIM1->IER &= (uint8_t)(~(uint8_t)TIM1_IT);
2760  0021 7b01          	ld	a,(OFST+1,sp)
2761  0023 43            	cpl	a
2762  0024 c45254        	and	a,21076
2763  0027               L3111:
2764  0027 c75254        	ld	21076,a
2765                     ; 633 }
2768  002a 85            	popw	x
2769  002b 81            	ret	
2770  002c               LC008:
2771  002c 89            	pushw	x
2772  002d 5f            	clrw	x
2773  002e 89            	pushw	x
2774  002f ae0000        	ldw	x,#L101
2775  0032 cd0000        	call	_assert_failed
2777  0035 5b04          	addw	sp,#4
2778  0037 81            	ret	
2802                     ; 640 void TIM1_InternalClockConfig(void)
2802                     ; 641 {
2803                     .text:	section	.text,new
2804  0000               _TIM1_InternalClockConfig:
2808                     ; 643   TIM1->SMCR &= (uint8_t)(~TIM1_SMCR_SMS);
2810  0000 c65252        	ld	a,21074
2811  0003 a4f8          	and	a,#248
2812  0005 c75252        	ld	21074,a
2813                     ; 644 }
2816  0008 81            	ret	
2934                     ; 662 void TIM1_ETRClockMode1Config(TIM1_ExtTRGPSC_TypeDef TIM1_ExtTRGPrescaler,
2934                     ; 663                               TIM1_ExtTRGPolarity_TypeDef TIM1_ExtTRGPolarity,
2934                     ; 664                               uint8_t ExtTRGFilter)
2934                     ; 665 {
2935                     .text:	section	.text,new
2936  0000               _TIM1_ETRClockMode1Config:
2938  0000 89            	pushw	x
2939       00000000      OFST:	set	0
2942                     ; 667   assert_param(IS_TIM1_EXT_PRESCALER_OK(TIM1_ExtTRGPrescaler));
2944  0001 9e            	ld	a,xh
2945  0002 4d            	tnz	a
2946  0003 2714          	jreq	L046
2947  0005 9e            	ld	a,xh
2948  0006 a110          	cp	a,#16
2949  0008 270f          	jreq	L046
2950  000a 9e            	ld	a,xh
2951  000b a120          	cp	a,#32
2952  000d 270a          	jreq	L046
2953  000f 9e            	ld	a,xh
2954  0010 a130          	cp	a,#48
2955  0012 2705          	jreq	L046
2956  0014 ae029b        	ldw	x,#667
2957  0017 ad25          	call	LC009
2958  0019               L046:
2959                     ; 668   assert_param(IS_TIM1_EXT_POLARITY_OK(TIM1_ExtTRGPolarity));
2961  0019 7b02          	ld	a,(OFST+2,sp)
2962  001b a180          	cp	a,#128
2963  001d 2708          	jreq	L056
2964  001f 4d            	tnz	a
2965  0020 2705          	jreq	L056
2966  0022 ae029c        	ldw	x,#668
2967  0025 ad17          	call	LC009
2968  0027               L056:
2969                     ; 671   TIM1_ETRConfig(TIM1_ExtTRGPrescaler, TIM1_ExtTRGPolarity, ExtTRGFilter);
2971  0027 7b05          	ld	a,(OFST+5,sp)
2972  0029 88            	push	a
2973  002a 7b03          	ld	a,(OFST+3,sp)
2974  002c 97            	ld	xl,a
2975  002d 7b02          	ld	a,(OFST+2,sp)
2976  002f 95            	ld	xh,a
2977  0030 cd0000        	call	_TIM1_ETRConfig
2979  0033 84            	pop	a
2980                     ; 674   TIM1->SMCR = (uint8_t)((uint8_t)(TIM1->SMCR & (uint8_t)(~(uint8_t)(TIM1_SMCR_SMS | TIM1_SMCR_TS )))
2980                     ; 675                          | (uint8_t)((uint8_t)TIM1_SLAVEMODE_EXTERNAL1 | TIM1_TS_ETRF ));
2982  0034 c65252        	ld	a,21074
2983  0037 aa77          	or	a,#119
2984  0039 c75252        	ld	21074,a
2985                     ; 676 }
2988  003c 85            	popw	x
2989  003d 81            	ret	
2990  003e               LC009:
2991  003e 89            	pushw	x
2992  003f 5f            	clrw	x
2993  0040 89            	pushw	x
2994  0041 ae0000        	ldw	x,#L101
2995  0044 cd0000        	call	_assert_failed
2997  0047 5b04          	addw	sp,#4
2998  0049 81            	ret	
3057                     ; 694 void TIM1_ETRClockMode2Config(TIM1_ExtTRGPSC_TypeDef TIM1_ExtTRGPrescaler,
3057                     ; 695                               TIM1_ExtTRGPolarity_TypeDef TIM1_ExtTRGPolarity,
3057                     ; 696                               uint8_t ExtTRGFilter)
3057                     ; 697 {
3058                     .text:	section	.text,new
3059  0000               _TIM1_ETRClockMode2Config:
3061  0000 89            	pushw	x
3062       00000000      OFST:	set	0
3065                     ; 699   assert_param(IS_TIM1_EXT_PRESCALER_OK(TIM1_ExtTRGPrescaler));
3067  0001 9e            	ld	a,xh
3068  0002 4d            	tnz	a
3069  0003 2714          	jreq	L466
3070  0005 9e            	ld	a,xh
3071  0006 a110          	cp	a,#16
3072  0008 270f          	jreq	L466
3073  000a 9e            	ld	a,xh
3074  000b a120          	cp	a,#32
3075  000d 270a          	jreq	L466
3076  000f 9e            	ld	a,xh
3077  0010 a130          	cp	a,#48
3078  0012 2705          	jreq	L466
3079  0014 ae02bb        	ldw	x,#699
3080  0017 ad21          	call	LC010
3081  0019               L466:
3082                     ; 700   assert_param(IS_TIM1_EXT_POLARITY_OK(TIM1_ExtTRGPolarity));
3084  0019 7b02          	ld	a,(OFST+2,sp)
3085  001b a180          	cp	a,#128
3086  001d 2708          	jreq	L476
3087  001f 4d            	tnz	a
3088  0020 2705          	jreq	L476
3089  0022 ae02bc        	ldw	x,#700
3090  0025 ad13          	call	LC010
3091  0027               L476:
3092                     ; 703   TIM1_ETRConfig(TIM1_ExtTRGPrescaler, TIM1_ExtTRGPolarity, ExtTRGFilter);
3094  0027 7b05          	ld	a,(OFST+5,sp)
3095  0029 88            	push	a
3096  002a 7b03          	ld	a,(OFST+3,sp)
3097  002c 97            	ld	xl,a
3098  002d 7b02          	ld	a,(OFST+2,sp)
3099  002f 95            	ld	xh,a
3100  0030 cd0000        	call	_TIM1_ETRConfig
3102  0033 721c5253      	bset	21075,#6
3103                     ; 706   TIM1->ETR |= TIM1_ETR_ECE;
3105                     ; 707 }
3108  0037 5b03          	addw	sp,#3
3109  0039 81            	ret	
3110  003a               LC010:
3111  003a 89            	pushw	x
3112  003b 5f            	clrw	x
3113  003c 89            	pushw	x
3114  003d ae0000        	ldw	x,#L101
3115  0040 cd0000        	call	_assert_failed
3117  0043 5b04          	addw	sp,#4
3118  0045 81            	ret	
3175                     ; 725 void TIM1_ETRConfig(TIM1_ExtTRGPSC_TypeDef TIM1_ExtTRGPrescaler,
3175                     ; 726                     TIM1_ExtTRGPolarity_TypeDef TIM1_ExtTRGPolarity,
3175                     ; 727                     uint8_t ExtTRGFilter)
3175                     ; 728 {
3176                     .text:	section	.text,new
3177  0000               _TIM1_ETRConfig:
3179  0000 89            	pushw	x
3180       00000000      OFST:	set	0
3183                     ; 730   assert_param(IS_TIM1_EXT_TRG_FILTER_OK(ExtTRGFilter));
3185  0001 7b05          	ld	a,(OFST+5,sp)
3186  0003 a110          	cp	a,#16
3187  0005 250e          	jrult	L607
3188  0007 ae02da        	ldw	x,#730
3189  000a 89            	pushw	x
3190  000b 5f            	clrw	x
3191  000c 89            	pushw	x
3192  000d ae0000        	ldw	x,#L101
3193  0010 cd0000        	call	_assert_failed
3195  0013 5b04          	addw	sp,#4
3196  0015               L607:
3197                     ; 732   TIM1->ETR |= (uint8_t)((uint8_t)(TIM1_ExtTRGPrescaler | (uint8_t)TIM1_ExtTRGPolarity )|
3197                     ; 733                          (uint8_t)ExtTRGFilter );
3199  0015 7b01          	ld	a,(OFST+1,sp)
3200  0017 1a02          	or	a,(OFST+2,sp)
3201  0019 1a05          	or	a,(OFST+5,sp)
3202  001b ca5253        	or	a,21075
3203  001e c75253        	ld	21075,a
3204                     ; 734 }
3207  0021 85            	popw	x
3208  0022 81            	ret	
3298                     ; 751 void TIM1_TIxExternalClockConfig(TIM1_TIxExternalCLK1Source_TypeDef TIM1_TIxExternalCLKSource,
3298                     ; 752                                  TIM1_ICPolarity_TypeDef TIM1_ICPolarity,
3298                     ; 753                                  uint8_t ICFilter)
3298                     ; 754 {
3299                     .text:	section	.text,new
3300  0000               _TIM1_TIxExternalClockConfig:
3302  0000 89            	pushw	x
3303       00000000      OFST:	set	0
3306                     ; 756   assert_param(IS_TIM1_TIXCLK_SOURCE_OK(TIM1_TIxExternalCLKSource));
3308  0001 9e            	ld	a,xh
3309  0002 a140          	cp	a,#64
3310  0004 270f          	jreq	L027
3311  0006 9e            	ld	a,xh
3312  0007 a160          	cp	a,#96
3313  0009 270a          	jreq	L027
3314  000b 9e            	ld	a,xh
3315  000c a150          	cp	a,#80
3316  000e 2705          	jreq	L027
3317  0010 ae02f4        	ldw	x,#756
3318  0013 ad47          	call	LC011
3319  0015               L027:
3320                     ; 757   assert_param(IS_TIM1_IC_POLARITY_OK(TIM1_ICPolarity));
3322  0015 7b02          	ld	a,(OFST+2,sp)
3323  0017 2708          	jreq	L037
3324  0019 4a            	dec	a
3325  001a 2705          	jreq	L037
3326  001c ae02f5        	ldw	x,#757
3327  001f ad3b          	call	LC011
3328  0021               L037:
3329                     ; 758   assert_param(IS_TIM1_IC_FILTER_OK(ICFilter));
3331  0021 7b05          	ld	a,(OFST+5,sp)
3332  0023 a110          	cp	a,#16
3333  0025 2505          	jrult	L637
3334  0027 ae02f6        	ldw	x,#758
3335  002a ad30          	call	LC011
3336  002c               L637:
3337                     ; 761   if (TIM1_TIxExternalCLKSource == TIM1_TIXEXTERNALCLK1SOURCE_TI2)
3339  002c 7b01          	ld	a,(OFST+1,sp)
3340  002e a160          	cp	a,#96
3341  0030 260e          	jrne	L3131
3342                     ; 763     TI2_Config((uint8_t)TIM1_ICPolarity, (uint8_t)TIM1_ICSELECTION_DIRECTTI, (uint8_t)ICFilter);
3344  0032 7b05          	ld	a,(OFST+5,sp)
3345  0034 88            	push	a
3346  0035 7b03          	ld	a,(OFST+3,sp)
3347  0037 ae0001        	ldw	x,#1
3348  003a 95            	ld	xh,a
3349  003b cd0000        	call	L5_TI2_Config
3352  003e 200c          	jra	L5131
3353  0040               L3131:
3354                     ; 767     TI1_Config((uint8_t)TIM1_ICPolarity, (uint8_t)TIM1_ICSELECTION_DIRECTTI, (uint8_t)ICFilter);
3356  0040 7b05          	ld	a,(OFST+5,sp)
3357  0042 88            	push	a
3358  0043 7b03          	ld	a,(OFST+3,sp)
3359  0045 ae0001        	ldw	x,#1
3360  0048 95            	ld	xh,a
3361  0049 cd0000        	call	L3_TI1_Config
3363  004c               L5131:
3364  004c 84            	pop	a
3365                     ; 771   TIM1_SelectInputTrigger((TIM1_TS_TypeDef)TIM1_TIxExternalCLKSource);
3367  004d 7b01          	ld	a,(OFST+1,sp)
3368  004f cd0000        	call	_TIM1_SelectInputTrigger
3370                     ; 774   TIM1->SMCR |= (uint8_t)(TIM1_SLAVEMODE_EXTERNAL1);
3372  0052 c65252        	ld	a,21074
3373  0055 aa07          	or	a,#7
3374  0057 c75252        	ld	21074,a
3375                     ; 775 }
3378  005a 85            	popw	x
3379  005b 81            	ret	
3380  005c               LC011:
3381  005c 89            	pushw	x
3382  005d 5f            	clrw	x
3383  005e 89            	pushw	x
3384  005f ae0000        	ldw	x,#L101
3385  0062 cd0000        	call	_assert_failed
3387  0065 5b04          	addw	sp,#4
3388  0067 81            	ret	
3474                     ; 787 void TIM1_SelectInputTrigger(TIM1_TS_TypeDef TIM1_InputTriggerSource)
3474                     ; 788 {
3475                     .text:	section	.text,new
3476  0000               _TIM1_SelectInputTrigger:
3478  0000 88            	push	a
3479       00000000      OFST:	set	0
3482                     ; 790   assert_param(IS_TIM1_TRIGGER_SELECTION_OK(TIM1_InputTriggerSource));
3484  0001 a140          	cp	a,#64
3485  0003 2721          	jreq	L657
3486  0005 a150          	cp	a,#80
3487  0007 271d          	jreq	L657
3488  0009 a160          	cp	a,#96
3489  000b 2719          	jreq	L657
3490  000d a170          	cp	a,#112
3491  000f 2715          	jreq	L657
3492  0011 a130          	cp	a,#48
3493  0013 2711          	jreq	L657
3494  0015 4d            	tnz	a
3495  0016 270e          	jreq	L657
3496  0018 ae0316        	ldw	x,#790
3497  001b 89            	pushw	x
3498  001c 5f            	clrw	x
3499  001d 89            	pushw	x
3500  001e ae0000        	ldw	x,#L101
3501  0021 cd0000        	call	_assert_failed
3503  0024 5b04          	addw	sp,#4
3504  0026               L657:
3505                     ; 793   TIM1->SMCR = (uint8_t)((uint8_t)(TIM1->SMCR & (uint8_t)(~TIM1_SMCR_TS)) | (uint8_t)TIM1_InputTriggerSource);
3507  0026 c65252        	ld	a,21074
3508  0029 a48f          	and	a,#143
3509  002b 1a01          	or	a,(OFST+1,sp)
3510  002d c75252        	ld	21074,a
3511                     ; 794 }
3514  0030 84            	pop	a
3515  0031 81            	ret	
3552                     ; 803 void TIM1_UpdateDisableConfig(FunctionalState NewState)
3552                     ; 804 {
3553                     .text:	section	.text,new
3554  0000               _TIM1_UpdateDisableConfig:
3556  0000 88            	push	a
3557       00000000      OFST:	set	0
3560                     ; 806   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
3562  0001 4d            	tnz	a
3563  0002 2711          	jreq	L077
3564  0004 4a            	dec	a
3565  0005 270e          	jreq	L077
3566  0007 ae0326        	ldw	x,#806
3567  000a 89            	pushw	x
3568  000b 5f            	clrw	x
3569  000c 89            	pushw	x
3570  000d ae0000        	ldw	x,#L101
3571  0010 cd0000        	call	_assert_failed
3573  0013 5b04          	addw	sp,#4
3574  0015               L077:
3575                     ; 809   if (NewState != DISABLE)
3577  0015 7b01          	ld	a,(OFST+1,sp)
3578  0017 2706          	jreq	L3731
3579                     ; 811     TIM1->CR1 |= TIM1_CR1_UDIS;
3581  0019 72125250      	bset	21072,#1
3583  001d 2004          	jra	L5731
3584  001f               L3731:
3585                     ; 815     TIM1->CR1 &= (uint8_t)(~TIM1_CR1_UDIS);
3587  001f 72135250      	bres	21072,#1
3588  0023               L5731:
3589                     ; 817 }
3592  0023 84            	pop	a
3593  0024 81            	ret	
3652                     ; 827 void TIM1_UpdateRequestConfig(TIM1_UpdateSource_TypeDef TIM1_UpdateSource)
3652                     ; 828 {
3653                     .text:	section	.text,new
3654  0000               _TIM1_UpdateRequestConfig:
3656  0000 88            	push	a
3657       00000000      OFST:	set	0
3660                     ; 830   assert_param(IS_TIM1_UPDATE_SOURCE_OK(TIM1_UpdateSource));
3662  0001 4d            	tnz	a
3663  0002 2711          	jreq	L2001
3664  0004 4a            	dec	a
3665  0005 270e          	jreq	L2001
3666  0007 ae033e        	ldw	x,#830
3667  000a 89            	pushw	x
3668  000b 5f            	clrw	x
3669  000c 89            	pushw	x
3670  000d ae0000        	ldw	x,#L101
3671  0010 cd0000        	call	_assert_failed
3673  0013 5b04          	addw	sp,#4
3674  0015               L2001:
3675                     ; 833   if (TIM1_UpdateSource != TIM1_UPDATESOURCE_GLOBAL)
3677  0015 7b01          	ld	a,(OFST+1,sp)
3678  0017 2706          	jreq	L5241
3679                     ; 835     TIM1->CR1 |= TIM1_CR1_URS;
3681  0019 72145250      	bset	21072,#2
3683  001d 2004          	jra	L7241
3684  001f               L5241:
3685                     ; 839     TIM1->CR1 &= (uint8_t)(~TIM1_CR1_URS);
3687  001f 72155250      	bres	21072,#2
3688  0023               L7241:
3689                     ; 841 }
3692  0023 84            	pop	a
3693  0024 81            	ret	
3730                     ; 849 void TIM1_SelectHallSensor(FunctionalState NewState)
3730                     ; 850 {
3731                     .text:	section	.text,new
3732  0000               _TIM1_SelectHallSensor:
3734  0000 88            	push	a
3735       00000000      OFST:	set	0
3738                     ; 852   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
3740  0001 4d            	tnz	a
3741  0002 2711          	jreq	L4101
3742  0004 4a            	dec	a
3743  0005 270e          	jreq	L4101
3744  0007 ae0354        	ldw	x,#852
3745  000a 89            	pushw	x
3746  000b 5f            	clrw	x
3747  000c 89            	pushw	x
3748  000d ae0000        	ldw	x,#L101
3749  0010 cd0000        	call	_assert_failed
3751  0013 5b04          	addw	sp,#4
3752  0015               L4101:
3753                     ; 855   if (NewState != DISABLE)
3755  0015 7b01          	ld	a,(OFST+1,sp)
3756  0017 2706          	jreq	L7441
3757                     ; 857     TIM1->CR2 |= TIM1_CR2_TI1S;
3759  0019 721e5251      	bset	21073,#7
3761  001d 2004          	jra	L1541
3762  001f               L7441:
3763                     ; 861     TIM1->CR2 &= (uint8_t)(~TIM1_CR2_TI1S);
3765  001f 721f5251      	bres	21073,#7
3766  0023               L1541:
3767                     ; 863 }
3770  0023 84            	pop	a
3771  0024 81            	ret	
3829                     ; 873 void TIM1_SelectOnePulseMode(TIM1_OPMode_TypeDef TIM1_OPMode)
3829                     ; 874 {
3830                     .text:	section	.text,new
3831  0000               _TIM1_SelectOnePulseMode:
3833  0000 88            	push	a
3834       00000000      OFST:	set	0
3837                     ; 876   assert_param(IS_TIM1_OPM_MODE_OK(TIM1_OPMode));
3839  0001 a101          	cp	a,#1
3840  0003 2711          	jreq	L6201
3841  0005 4d            	tnz	a
3842  0006 270e          	jreq	L6201
3843  0008 ae036c        	ldw	x,#876
3844  000b 89            	pushw	x
3845  000c 5f            	clrw	x
3846  000d 89            	pushw	x
3847  000e ae0000        	ldw	x,#L101
3848  0011 cd0000        	call	_assert_failed
3850  0014 5b04          	addw	sp,#4
3851  0016               L6201:
3852                     ; 879   if (TIM1_OPMode != TIM1_OPMODE_REPETITIVE)
3854  0016 7b01          	ld	a,(OFST+1,sp)
3855  0018 2706          	jreq	L1051
3856                     ; 881     TIM1->CR1 |= TIM1_CR1_OPM;
3858  001a 72165250      	bset	21072,#3
3860  001e 2004          	jra	L3051
3861  0020               L1051:
3862                     ; 885     TIM1->CR1 &= (uint8_t)(~TIM1_CR1_OPM);
3864  0020 72175250      	bres	21072,#3
3865  0024               L3051:
3866                     ; 888 }
3869  0024 84            	pop	a
3870  0025 81            	ret	
3969                     ; 903 void TIM1_SelectOutputTrigger(TIM1_TRGOSource_TypeDef TIM1_TRGOSource)
3969                     ; 904 {
3970                     .text:	section	.text,new
3971  0000               _TIM1_SelectOutputTrigger:
3973  0000 88            	push	a
3974       00000000      OFST:	set	0
3977                     ; 906   assert_param(IS_TIM1_TRGO_SOURCE_OK(TIM1_TRGOSource));
3979  0001 4d            	tnz	a
3980  0002 2726          	jreq	L0401
3981  0004 a110          	cp	a,#16
3982  0006 2722          	jreq	L0401
3983  0008 a120          	cp	a,#32
3984  000a 271e          	jreq	L0401
3985  000c a130          	cp	a,#48
3986  000e 271a          	jreq	L0401
3987  0010 a140          	cp	a,#64
3988  0012 2716          	jreq	L0401
3989  0014 a150          	cp	a,#80
3990  0016 2712          	jreq	L0401
3991  0018 a160          	cp	a,#96
3992  001a 270e          	jreq	L0401
3993  001c ae038a        	ldw	x,#906
3994  001f 89            	pushw	x
3995  0020 5f            	clrw	x
3996  0021 89            	pushw	x
3997  0022 ae0000        	ldw	x,#L101
3998  0025 cd0000        	call	_assert_failed
4000  0028 5b04          	addw	sp,#4
4001  002a               L0401:
4002                     ; 909   TIM1->CR2 = (uint8_t)((uint8_t)(TIM1->CR2 & (uint8_t)(~TIM1_CR2_MMS)) | 
4002                     ; 910                         (uint8_t) TIM1_TRGOSource);
4004  002a c65251        	ld	a,21073
4005  002d a48f          	and	a,#143
4006  002f 1a01          	or	a,(OFST+1,sp)
4007  0031 c75251        	ld	21073,a
4008                     ; 911 }
4011  0034 84            	pop	a
4012  0035 81            	ret	
4087                     ; 923 void TIM1_SelectSlaveMode(TIM1_SlaveMode_TypeDef TIM1_SlaveMode)
4087                     ; 924 {
4088                     .text:	section	.text,new
4089  0000               _TIM1_SelectSlaveMode:
4091  0000 88            	push	a
4092       00000000      OFST:	set	0
4095                     ; 926   assert_param(IS_TIM1_SLAVE_MODE_OK(TIM1_SlaveMode));
4097  0001 a104          	cp	a,#4
4098  0003 271a          	jreq	L2501
4099  0005 a105          	cp	a,#5
4100  0007 2716          	jreq	L2501
4101  0009 a106          	cp	a,#6
4102  000b 2712          	jreq	L2501
4103  000d a107          	cp	a,#7
4104  000f 270e          	jreq	L2501
4105  0011 ae039e        	ldw	x,#926
4106  0014 89            	pushw	x
4107  0015 5f            	clrw	x
4108  0016 89            	pushw	x
4109  0017 ae0000        	ldw	x,#L101
4110  001a cd0000        	call	_assert_failed
4112  001d 5b04          	addw	sp,#4
4113  001f               L2501:
4114                     ; 929   TIM1->SMCR = (uint8_t)((uint8_t)(TIM1->SMCR & (uint8_t)(~TIM1_SMCR_SMS)) |
4114                     ; 930                          (uint8_t)TIM1_SlaveMode);
4116  001f c65252        	ld	a,21074
4117  0022 a4f8          	and	a,#248
4118  0024 1a01          	or	a,(OFST+1,sp)
4119  0026 c75252        	ld	21074,a
4120                     ; 931 }
4123  0029 84            	pop	a
4124  002a 81            	ret	
4161                     ; 939 void TIM1_SelectMasterSlaveMode(FunctionalState NewState)
4161                     ; 940 {
4162                     .text:	section	.text,new
4163  0000               _TIM1_SelectMasterSlaveMode:
4165  0000 88            	push	a
4166       00000000      OFST:	set	0
4169                     ; 942   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
4171  0001 4d            	tnz	a
4172  0002 2711          	jreq	L4601
4173  0004 4a            	dec	a
4174  0005 270e          	jreq	L4601
4175  0007 ae03ae        	ldw	x,#942
4176  000a 89            	pushw	x
4177  000b 5f            	clrw	x
4178  000c 89            	pushw	x
4179  000d ae0000        	ldw	x,#L101
4180  0010 cd0000        	call	_assert_failed
4182  0013 5b04          	addw	sp,#4
4183  0015               L4601:
4184                     ; 945   if (NewState != DISABLE)
4186  0015 7b01          	ld	a,(OFST+1,sp)
4187  0017 2706          	jreq	L5161
4188                     ; 947     TIM1->SMCR |= TIM1_SMCR_MSM;
4190  0019 721e5252      	bset	21074,#7
4192  001d 2004          	jra	L7161
4193  001f               L5161:
4194                     ; 951     TIM1->SMCR &= (uint8_t)(~TIM1_SMCR_MSM);
4196  001f 721f5252      	bres	21074,#7
4197  0023               L7161:
4198                     ; 953 }
4201  0023 84            	pop	a
4202  0024 81            	ret	
4289                     ; 975 void TIM1_EncoderInterfaceConfig(TIM1_EncoderMode_TypeDef TIM1_EncoderMode,
4289                     ; 976                                  TIM1_ICPolarity_TypeDef TIM1_IC1Polarity,
4289                     ; 977                                  TIM1_ICPolarity_TypeDef TIM1_IC2Polarity)
4289                     ; 978 {
4290                     .text:	section	.text,new
4291  0000               _TIM1_EncoderInterfaceConfig:
4293  0000 89            	pushw	x
4294       00000000      OFST:	set	0
4297                     ; 980   assert_param(IS_TIM1_ENCODER_MODE_OK(TIM1_EncoderMode));
4299  0001 9e            	ld	a,xh
4300  0002 4a            	dec	a
4301  0003 270f          	jreq	L6701
4302  0005 9e            	ld	a,xh
4303  0006 a102          	cp	a,#2
4304  0008 270a          	jreq	L6701
4305  000a 9e            	ld	a,xh
4306  000b a103          	cp	a,#3
4307  000d 2705          	jreq	L6701
4308  000f ae03d4        	ldw	x,#980
4309  0012 ad54          	call	LC012
4310  0014               L6701:
4311                     ; 981   assert_param(IS_TIM1_IC_POLARITY_OK(TIM1_IC1Polarity));
4313  0014 7b02          	ld	a,(OFST+2,sp)
4314  0016 2708          	jreq	L6011
4315  0018 4a            	dec	a
4316  0019 2705          	jreq	L6011
4317  001b ae03d5        	ldw	x,#981
4318  001e ad48          	call	LC012
4319  0020               L6011:
4320                     ; 982   assert_param(IS_TIM1_IC_POLARITY_OK(TIM1_IC2Polarity));
4322  0020 7b05          	ld	a,(OFST+5,sp)
4323  0022 2708          	jreq	L6111
4324  0024 4a            	dec	a
4325  0025 2705          	jreq	L6111
4326  0027 ae03d6        	ldw	x,#982
4327  002a ad3c          	call	LC012
4328  002c               L6111:
4329                     ; 985   if (TIM1_IC1Polarity != TIM1_ICPOLARITY_RISING)
4331  002c 7b02          	ld	a,(OFST+2,sp)
4332  002e 2706          	jreq	L1661
4333                     ; 987     TIM1->CCER1 |= TIM1_CCER1_CC1P;
4335  0030 7212525c      	bset	21084,#1
4337  0034 2004          	jra	L3661
4338  0036               L1661:
4339                     ; 991     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1P);
4341  0036 7213525c      	bres	21084,#1
4342  003a               L3661:
4343                     ; 994   if (TIM1_IC2Polarity != TIM1_ICPOLARITY_RISING)
4345  003a 7b05          	ld	a,(OFST+5,sp)
4346  003c 2706          	jreq	L5661
4347                     ; 996     TIM1->CCER1 |= TIM1_CCER1_CC2P;
4349  003e 721a525c      	bset	21084,#5
4351  0042 2004          	jra	L7661
4352  0044               L5661:
4353                     ; 1000     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2P);
4355  0044 721b525c      	bres	21084,#5
4356  0048               L7661:
4357                     ; 1003   TIM1->SMCR = (uint8_t)((uint8_t)(TIM1->SMCR & (uint8_t)(TIM1_SMCR_MSM | TIM1_SMCR_TS))
4357                     ; 1004                          | (uint8_t) TIM1_EncoderMode);
4359  0048 c65252        	ld	a,21074
4360  004b a4f0          	and	a,#240
4361  004d 1a01          	or	a,(OFST+1,sp)
4362  004f c75252        	ld	21074,a
4363                     ; 1007   TIM1->CCMR1 = (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_CCxS)) 
4363                     ; 1008                           | (uint8_t) CCMR_TIxDirect_Set);
4365  0052 c65258        	ld	a,21080
4366  0055 a4fc          	and	a,#252
4367  0057 aa01          	or	a,#1
4368  0059 c75258        	ld	21080,a
4369                     ; 1009   TIM1->CCMR2 = (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_CCxS))
4369                     ; 1010                           | (uint8_t) CCMR_TIxDirect_Set);
4371  005c c65259        	ld	a,21081
4372  005f a4fc          	and	a,#252
4373  0061 aa01          	or	a,#1
4374  0063 c75259        	ld	21081,a
4375                     ; 1011 }
4378  0066 85            	popw	x
4379  0067 81            	ret	
4380  0068               LC012:
4381  0068 89            	pushw	x
4382  0069 5f            	clrw	x
4383  006a 89            	pushw	x
4384  006b ae0000        	ldw	x,#L101
4385  006e cd0000        	call	_assert_failed
4387  0071 5b04          	addw	sp,#4
4388  0073 81            	ret	
4456                     ; 1023 void TIM1_PrescalerConfig(uint16_t Prescaler,
4456                     ; 1024                           TIM1_PSCReloadMode_TypeDef TIM1_PSCReloadMode)
4456                     ; 1025 {
4457                     .text:	section	.text,new
4458  0000               _TIM1_PrescalerConfig:
4460  0000 89            	pushw	x
4461       00000000      OFST:	set	0
4464                     ; 1027   assert_param(IS_TIM1_PRESCALER_RELOAD_OK(TIM1_PSCReloadMode));
4466  0001 7b05          	ld	a,(OFST+5,sp)
4467  0003 2711          	jreq	L0311
4468  0005 4a            	dec	a
4469  0006 270e          	jreq	L0311
4470  0008 ae0403        	ldw	x,#1027
4471  000b 89            	pushw	x
4472  000c 5f            	clrw	x
4473  000d 89            	pushw	x
4474  000e ae0000        	ldw	x,#L101
4475  0011 cd0000        	call	_assert_failed
4477  0014 5b04          	addw	sp,#4
4478  0016               L0311:
4479                     ; 1030   TIM1->PSCRH = (uint8_t)(Prescaler >> 8);
4481  0016 7b01          	ld	a,(OFST+1,sp)
4482  0018 c75260        	ld	21088,a
4483                     ; 1031   TIM1->PSCRL = (uint8_t)(Prescaler);
4485  001b 7b02          	ld	a,(OFST+2,sp)
4486  001d c75261        	ld	21089,a
4487                     ; 1034   TIM1->EGR = (uint8_t)TIM1_PSCReloadMode;
4489  0020 7b05          	ld	a,(OFST+5,sp)
4490  0022 c75257        	ld	21079,a
4491                     ; 1035 }
4494  0025 85            	popw	x
4495  0026 81            	ret	
4532                     ; 1048 void TIM1_CounterModeConfig(TIM1_CounterMode_TypeDef TIM1_CounterMode)
4532                     ; 1049 {
4533                     .text:	section	.text,new
4534  0000               _TIM1_CounterModeConfig:
4536  0000 88            	push	a
4537       00000000      OFST:	set	0
4540                     ; 1051   assert_param(IS_TIM1_COUNTER_MODE_OK(TIM1_CounterMode));
4542  0001 4d            	tnz	a
4543  0002 271e          	jreq	L2411
4544  0004 a110          	cp	a,#16
4545  0006 271a          	jreq	L2411
4546  0008 a120          	cp	a,#32
4547  000a 2716          	jreq	L2411
4548  000c a140          	cp	a,#64
4549  000e 2712          	jreq	L2411
4550  0010 a160          	cp	a,#96
4551  0012 270e          	jreq	L2411
4552  0014 ae041b        	ldw	x,#1051
4553  0017 89            	pushw	x
4554  0018 5f            	clrw	x
4555  0019 89            	pushw	x
4556  001a ae0000        	ldw	x,#L101
4557  001d cd0000        	call	_assert_failed
4559  0020 5b04          	addw	sp,#4
4560  0022               L2411:
4561                     ; 1055   TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)((uint8_t)(~TIM1_CR1_CMS) & (uint8_t)(~TIM1_CR1_DIR)))
4561                     ; 1056                         | (uint8_t)TIM1_CounterMode);
4563  0022 c65250        	ld	a,21072
4564  0025 a48f          	and	a,#143
4565  0027 1a01          	or	a,(OFST+1,sp)
4566  0029 c75250        	ld	21072,a
4567                     ; 1057 }
4570  002c 84            	pop	a
4571  002d 81            	ret	
4630                     ; 1067 void TIM1_ForcedOC1Config(TIM1_ForcedAction_TypeDef TIM1_ForcedAction)
4630                     ; 1068 {
4631                     .text:	section	.text,new
4632  0000               _TIM1_ForcedOC1Config:
4634  0000 88            	push	a
4635       00000000      OFST:	set	0
4638                     ; 1070   assert_param(IS_TIM1_FORCED_ACTION_OK(TIM1_ForcedAction));
4640  0001 a150          	cp	a,#80
4641  0003 2712          	jreq	L4511
4642  0005 a140          	cp	a,#64
4643  0007 270e          	jreq	L4511
4644  0009 ae042e        	ldw	x,#1070
4645  000c 89            	pushw	x
4646  000d 5f            	clrw	x
4647  000e 89            	pushw	x
4648  000f ae0000        	ldw	x,#L101
4649  0012 cd0000        	call	_assert_failed
4651  0015 5b04          	addw	sp,#4
4652  0017               L4511:
4653                     ; 1073   TIM1->CCMR1 =  (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_OCM))|
4653                     ; 1074                            (uint8_t)TIM1_ForcedAction);
4655  0017 c65258        	ld	a,21080
4656  001a a48f          	and	a,#143
4657  001c 1a01          	or	a,(OFST+1,sp)
4658  001e c75258        	ld	21080,a
4659                     ; 1075 }
4662  0021 84            	pop	a
4663  0022 81            	ret	
4700                     ; 1085 void TIM1_ForcedOC2Config(TIM1_ForcedAction_TypeDef TIM1_ForcedAction)
4700                     ; 1086 {
4701                     .text:	section	.text,new
4702  0000               _TIM1_ForcedOC2Config:
4704  0000 88            	push	a
4705       00000000      OFST:	set	0
4708                     ; 1088   assert_param(IS_TIM1_FORCED_ACTION_OK(TIM1_ForcedAction));
4710  0001 a150          	cp	a,#80
4711  0003 2712          	jreq	L6611
4712  0005 a140          	cp	a,#64
4713  0007 270e          	jreq	L6611
4714  0009 ae0440        	ldw	x,#1088
4715  000c 89            	pushw	x
4716  000d 5f            	clrw	x
4717  000e 89            	pushw	x
4718  000f ae0000        	ldw	x,#L101
4719  0012 cd0000        	call	_assert_failed
4721  0015 5b04          	addw	sp,#4
4722  0017               L6611:
4723                     ; 1091   TIM1->CCMR2  =  (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_OCM))
4723                     ; 1092                             | (uint8_t)TIM1_ForcedAction);
4725  0017 c65259        	ld	a,21081
4726  001a a48f          	and	a,#143
4727  001c 1a01          	or	a,(OFST+1,sp)
4728  001e c75259        	ld	21081,a
4729                     ; 1093 }
4732  0021 84            	pop	a
4733  0022 81            	ret	
4770                     ; 1104 void TIM1_ForcedOC3Config(TIM1_ForcedAction_TypeDef TIM1_ForcedAction)
4770                     ; 1105 {
4771                     .text:	section	.text,new
4772  0000               _TIM1_ForcedOC3Config:
4774  0000 88            	push	a
4775       00000000      OFST:	set	0
4778                     ; 1107   assert_param(IS_TIM1_FORCED_ACTION_OK(TIM1_ForcedAction));
4780  0001 a150          	cp	a,#80
4781  0003 2712          	jreq	L0021
4782  0005 a140          	cp	a,#64
4783  0007 270e          	jreq	L0021
4784  0009 ae0453        	ldw	x,#1107
4785  000c 89            	pushw	x
4786  000d 5f            	clrw	x
4787  000e 89            	pushw	x
4788  000f ae0000        	ldw	x,#L101
4789  0012 cd0000        	call	_assert_failed
4791  0015 5b04          	addw	sp,#4
4792  0017               L0021:
4793                     ; 1110   TIM1->CCMR3  =  (uint8_t)((uint8_t)(TIM1->CCMR3 & (uint8_t)(~TIM1_CCMR_OCM))  
4793                     ; 1111                             | (uint8_t)TIM1_ForcedAction);
4795  0017 c6525a        	ld	a,21082
4796  001a a48f          	and	a,#143
4797  001c 1a01          	or	a,(OFST+1,sp)
4798  001e c7525a        	ld	21082,a
4799                     ; 1112 }
4802  0021 84            	pop	a
4803  0022 81            	ret	
4840                     ; 1123 void TIM1_ForcedOC4Config(TIM1_ForcedAction_TypeDef TIM1_ForcedAction)
4840                     ; 1124 {
4841                     .text:	section	.text,new
4842  0000               _TIM1_ForcedOC4Config:
4844  0000 88            	push	a
4845       00000000      OFST:	set	0
4848                     ; 1126   assert_param(IS_TIM1_FORCED_ACTION_OK(TIM1_ForcedAction));
4850  0001 a150          	cp	a,#80
4851  0003 2712          	jreq	L2121
4852  0005 a140          	cp	a,#64
4853  0007 270e          	jreq	L2121
4854  0009 ae0466        	ldw	x,#1126
4855  000c 89            	pushw	x
4856  000d 5f            	clrw	x
4857  000e 89            	pushw	x
4858  000f ae0000        	ldw	x,#L101
4859  0012 cd0000        	call	_assert_failed
4861  0015 5b04          	addw	sp,#4
4862  0017               L2121:
4863                     ; 1129   TIM1->CCMR4  =  (uint8_t)((uint8_t)(TIM1->CCMR4 & (uint8_t)(~TIM1_CCMR_OCM)) 
4863                     ; 1130                             | (uint8_t)TIM1_ForcedAction);
4865  0017 c6525b        	ld	a,21083
4866  001a a48f          	and	a,#143
4867  001c 1a01          	or	a,(OFST+1,sp)
4868  001e c7525b        	ld	21083,a
4869                     ; 1131 }
4872  0021 84            	pop	a
4873  0022 81            	ret	
4910                     ; 1139 void TIM1_ARRPreloadConfig(FunctionalState NewState)
4910                     ; 1140 {
4911                     .text:	section	.text,new
4912  0000               _TIM1_ARRPreloadConfig:
4914  0000 88            	push	a
4915       00000000      OFST:	set	0
4918                     ; 1142   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
4920  0001 4d            	tnz	a
4921  0002 2711          	jreq	L4221
4922  0004 4a            	dec	a
4923  0005 270e          	jreq	L4221
4924  0007 ae0476        	ldw	x,#1142
4925  000a 89            	pushw	x
4926  000b 5f            	clrw	x
4927  000c 89            	pushw	x
4928  000d ae0000        	ldw	x,#L101
4929  0010 cd0000        	call	_assert_failed
4931  0013 5b04          	addw	sp,#4
4932  0015               L4221:
4933                     ; 1145   if (NewState != DISABLE)
4935  0015 7b01          	ld	a,(OFST+1,sp)
4936  0017 2706          	jreq	L7502
4937                     ; 1147     TIM1->CR1 |= TIM1_CR1_ARPE;
4939  0019 721e5250      	bset	21072,#7
4941  001d 2004          	jra	L1602
4942  001f               L7502:
4943                     ; 1151     TIM1->CR1 &= (uint8_t)(~TIM1_CR1_ARPE);
4945  001f 721f5250      	bres	21072,#7
4946  0023               L1602:
4947                     ; 1153 }
4950  0023 84            	pop	a
4951  0024 81            	ret	
4987                     ; 1161 void TIM1_SelectCOM(FunctionalState NewState)
4987                     ; 1162 {
4988                     .text:	section	.text,new
4989  0000               _TIM1_SelectCOM:
4991  0000 88            	push	a
4992       00000000      OFST:	set	0
4995                     ; 1164   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
4997  0001 4d            	tnz	a
4998  0002 2711          	jreq	L6321
4999  0004 4a            	dec	a
5000  0005 270e          	jreq	L6321
5001  0007 ae048c        	ldw	x,#1164
5002  000a 89            	pushw	x
5003  000b 5f            	clrw	x
5004  000c 89            	pushw	x
5005  000d ae0000        	ldw	x,#L101
5006  0010 cd0000        	call	_assert_failed
5008  0013 5b04          	addw	sp,#4
5009  0015               L6321:
5010                     ; 1167   if (NewState != DISABLE)
5012  0015 7b01          	ld	a,(OFST+1,sp)
5013  0017 2706          	jreq	L1012
5014                     ; 1169     TIM1->CR2 |= TIM1_CR2_COMS;
5016  0019 72145251      	bset	21073,#2
5018  001d 2004          	jra	L3012
5019  001f               L1012:
5020                     ; 1173     TIM1->CR2 &= (uint8_t)(~TIM1_CR2_COMS);
5022  001f 72155251      	bres	21073,#2
5023  0023               L3012:
5024                     ; 1175 }
5027  0023 84            	pop	a
5028  0024 81            	ret	
5065                     ; 1183 void TIM1_CCPreloadControl(FunctionalState NewState)
5065                     ; 1184 {
5066                     .text:	section	.text,new
5067  0000               _TIM1_CCPreloadControl:
5069  0000 88            	push	a
5070       00000000      OFST:	set	0
5073                     ; 1186   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5075  0001 4d            	tnz	a
5076  0002 2711          	jreq	L0521
5077  0004 4a            	dec	a
5078  0005 270e          	jreq	L0521
5079  0007 ae04a2        	ldw	x,#1186
5080  000a 89            	pushw	x
5081  000b 5f            	clrw	x
5082  000c 89            	pushw	x
5083  000d ae0000        	ldw	x,#L101
5084  0010 cd0000        	call	_assert_failed
5086  0013 5b04          	addw	sp,#4
5087  0015               L0521:
5088                     ; 1189   if (NewState != DISABLE)
5090  0015 7b01          	ld	a,(OFST+1,sp)
5091  0017 2706          	jreq	L3212
5092                     ; 1191     TIM1->CR2 |= TIM1_CR2_CCPC;
5094  0019 72105251      	bset	21073,#0
5096  001d 2004          	jra	L5212
5097  001f               L3212:
5098                     ; 1195     TIM1->CR2 &= (uint8_t)(~TIM1_CR2_CCPC);
5100  001f 72115251      	bres	21073,#0
5101  0023               L5212:
5102                     ; 1197 }
5105  0023 84            	pop	a
5106  0024 81            	ret	
5143                     ; 1205 void TIM1_OC1PreloadConfig(FunctionalState NewState)
5143                     ; 1206 {
5144                     .text:	section	.text,new
5145  0000               _TIM1_OC1PreloadConfig:
5147  0000 88            	push	a
5148       00000000      OFST:	set	0
5151                     ; 1208   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5153  0001 4d            	tnz	a
5154  0002 2711          	jreq	L2621
5155  0004 4a            	dec	a
5156  0005 270e          	jreq	L2621
5157  0007 ae04b8        	ldw	x,#1208
5158  000a 89            	pushw	x
5159  000b 5f            	clrw	x
5160  000c 89            	pushw	x
5161  000d ae0000        	ldw	x,#L101
5162  0010 cd0000        	call	_assert_failed
5164  0013 5b04          	addw	sp,#4
5165  0015               L2621:
5166                     ; 1211   if (NewState != DISABLE)
5168  0015 7b01          	ld	a,(OFST+1,sp)
5169  0017 2706          	jreq	L5412
5170                     ; 1213     TIM1->CCMR1 |= TIM1_CCMR_OCxPE;
5172  0019 72165258      	bset	21080,#3
5174  001d 2004          	jra	L7412
5175  001f               L5412:
5176                     ; 1217     TIM1->CCMR1 &= (uint8_t)(~TIM1_CCMR_OCxPE);
5178  001f 72175258      	bres	21080,#3
5179  0023               L7412:
5180                     ; 1219 }
5183  0023 84            	pop	a
5184  0024 81            	ret	
5221                     ; 1227 void TIM1_OC2PreloadConfig(FunctionalState NewState)
5221                     ; 1228 {
5222                     .text:	section	.text,new
5223  0000               _TIM1_OC2PreloadConfig:
5225  0000 88            	push	a
5226       00000000      OFST:	set	0
5229                     ; 1230   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5231  0001 4d            	tnz	a
5232  0002 2711          	jreq	L4721
5233  0004 4a            	dec	a
5234  0005 270e          	jreq	L4721
5235  0007 ae04ce        	ldw	x,#1230
5236  000a 89            	pushw	x
5237  000b 5f            	clrw	x
5238  000c 89            	pushw	x
5239  000d ae0000        	ldw	x,#L101
5240  0010 cd0000        	call	_assert_failed
5242  0013 5b04          	addw	sp,#4
5243  0015               L4721:
5244                     ; 1233   if (NewState != DISABLE)
5246  0015 7b01          	ld	a,(OFST+1,sp)
5247  0017 2706          	jreq	L7612
5248                     ; 1235     TIM1->CCMR2 |= TIM1_CCMR_OCxPE;
5250  0019 72165259      	bset	21081,#3
5252  001d 2004          	jra	L1712
5253  001f               L7612:
5254                     ; 1239     TIM1->CCMR2 &= (uint8_t)(~TIM1_CCMR_OCxPE);
5256  001f 72175259      	bres	21081,#3
5257  0023               L1712:
5258                     ; 1241 }
5261  0023 84            	pop	a
5262  0024 81            	ret	
5299                     ; 1249 void TIM1_OC3PreloadConfig(FunctionalState NewState)
5299                     ; 1250 {
5300                     .text:	section	.text,new
5301  0000               _TIM1_OC3PreloadConfig:
5303  0000 88            	push	a
5304       00000000      OFST:	set	0
5307                     ; 1252   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5309  0001 4d            	tnz	a
5310  0002 2711          	jreq	L6031
5311  0004 4a            	dec	a
5312  0005 270e          	jreq	L6031
5313  0007 ae04e4        	ldw	x,#1252
5314  000a 89            	pushw	x
5315  000b 5f            	clrw	x
5316  000c 89            	pushw	x
5317  000d ae0000        	ldw	x,#L101
5318  0010 cd0000        	call	_assert_failed
5320  0013 5b04          	addw	sp,#4
5321  0015               L6031:
5322                     ; 1255   if (NewState != DISABLE)
5324  0015 7b01          	ld	a,(OFST+1,sp)
5325  0017 2706          	jreq	L1122
5326                     ; 1257     TIM1->CCMR3 |= TIM1_CCMR_OCxPE;
5328  0019 7216525a      	bset	21082,#3
5330  001d 2004          	jra	L3122
5331  001f               L1122:
5332                     ; 1261     TIM1->CCMR3 &= (uint8_t)(~TIM1_CCMR_OCxPE);
5334  001f 7217525a      	bres	21082,#3
5335  0023               L3122:
5336                     ; 1263 }
5339  0023 84            	pop	a
5340  0024 81            	ret	
5377                     ; 1271 void TIM1_OC4PreloadConfig(FunctionalState NewState)
5377                     ; 1272 {
5378                     .text:	section	.text,new
5379  0000               _TIM1_OC4PreloadConfig:
5381  0000 88            	push	a
5382       00000000      OFST:	set	0
5385                     ; 1274   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5387  0001 4d            	tnz	a
5388  0002 2711          	jreq	L0231
5389  0004 4a            	dec	a
5390  0005 270e          	jreq	L0231
5391  0007 ae04fa        	ldw	x,#1274
5392  000a 89            	pushw	x
5393  000b 5f            	clrw	x
5394  000c 89            	pushw	x
5395  000d ae0000        	ldw	x,#L101
5396  0010 cd0000        	call	_assert_failed
5398  0013 5b04          	addw	sp,#4
5399  0015               L0231:
5400                     ; 1277   if (NewState != DISABLE)
5402  0015 7b01          	ld	a,(OFST+1,sp)
5403  0017 2706          	jreq	L3322
5404                     ; 1279     TIM1->CCMR4 |= TIM1_CCMR_OCxPE;
5406  0019 7216525b      	bset	21083,#3
5408  001d 2004          	jra	L5322
5409  001f               L3322:
5410                     ; 1283     TIM1->CCMR4 &= (uint8_t)(~TIM1_CCMR_OCxPE);
5412  001f 7217525b      	bres	21083,#3
5413  0023               L5322:
5414                     ; 1285 }
5417  0023 84            	pop	a
5418  0024 81            	ret	
5454                     ; 1293 void TIM1_OC1FastConfig(FunctionalState NewState)
5454                     ; 1294 {
5455                     .text:	section	.text,new
5456  0000               _TIM1_OC1FastConfig:
5458  0000 88            	push	a
5459       00000000      OFST:	set	0
5462                     ; 1296   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5464  0001 4d            	tnz	a
5465  0002 2711          	jreq	L2331
5466  0004 4a            	dec	a
5467  0005 270e          	jreq	L2331
5468  0007 ae0510        	ldw	x,#1296
5469  000a 89            	pushw	x
5470  000b 5f            	clrw	x
5471  000c 89            	pushw	x
5472  000d ae0000        	ldw	x,#L101
5473  0010 cd0000        	call	_assert_failed
5475  0013 5b04          	addw	sp,#4
5476  0015               L2331:
5477                     ; 1299   if (NewState != DISABLE)
5479  0015 7b01          	ld	a,(OFST+1,sp)
5480  0017 2706          	jreq	L5522
5481                     ; 1301     TIM1->CCMR1 |= TIM1_CCMR_OCxFE;
5483  0019 72145258      	bset	21080,#2
5485  001d 2004          	jra	L7522
5486  001f               L5522:
5487                     ; 1305     TIM1->CCMR1 &= (uint8_t)(~TIM1_CCMR_OCxFE);
5489  001f 72155258      	bres	21080,#2
5490  0023               L7522:
5491                     ; 1307 }
5494  0023 84            	pop	a
5495  0024 81            	ret	
5531                     ; 1315 void TIM1_OC2FastConfig(FunctionalState NewState)
5531                     ; 1316 {
5532                     .text:	section	.text,new
5533  0000               _TIM1_OC2FastConfig:
5535  0000 88            	push	a
5536       00000000      OFST:	set	0
5539                     ; 1318   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5541  0001 4d            	tnz	a
5542  0002 2711          	jreq	L4431
5543  0004 4a            	dec	a
5544  0005 270e          	jreq	L4431
5545  0007 ae0526        	ldw	x,#1318
5546  000a 89            	pushw	x
5547  000b 5f            	clrw	x
5548  000c 89            	pushw	x
5549  000d ae0000        	ldw	x,#L101
5550  0010 cd0000        	call	_assert_failed
5552  0013 5b04          	addw	sp,#4
5553  0015               L4431:
5554                     ; 1321   if (NewState != DISABLE)
5556  0015 7b01          	ld	a,(OFST+1,sp)
5557  0017 2706          	jreq	L7722
5558                     ; 1323     TIM1->CCMR2 |= TIM1_CCMR_OCxFE;
5560  0019 72145259      	bset	21081,#2
5562  001d 2004          	jra	L1032
5563  001f               L7722:
5564                     ; 1327     TIM1->CCMR2 &= (uint8_t)(~TIM1_CCMR_OCxFE);
5566  001f 72155259      	bres	21081,#2
5567  0023               L1032:
5568                     ; 1329 }
5571  0023 84            	pop	a
5572  0024 81            	ret	
5608                     ; 1337 void TIM1_OC3FastConfig(FunctionalState NewState)
5608                     ; 1338 {
5609                     .text:	section	.text,new
5610  0000               _TIM1_OC3FastConfig:
5612  0000 88            	push	a
5613       00000000      OFST:	set	0
5616                     ; 1340   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5618  0001 4d            	tnz	a
5619  0002 2711          	jreq	L6531
5620  0004 4a            	dec	a
5621  0005 270e          	jreq	L6531
5622  0007 ae053c        	ldw	x,#1340
5623  000a 89            	pushw	x
5624  000b 5f            	clrw	x
5625  000c 89            	pushw	x
5626  000d ae0000        	ldw	x,#L101
5627  0010 cd0000        	call	_assert_failed
5629  0013 5b04          	addw	sp,#4
5630  0015               L6531:
5631                     ; 1343   if (NewState != DISABLE)
5633  0015 7b01          	ld	a,(OFST+1,sp)
5634  0017 2706          	jreq	L1232
5635                     ; 1345     TIM1->CCMR3 |= TIM1_CCMR_OCxFE;
5637  0019 7214525a      	bset	21082,#2
5639  001d 2004          	jra	L3232
5640  001f               L1232:
5641                     ; 1349     TIM1->CCMR3 &= (uint8_t)(~TIM1_CCMR_OCxFE);
5643  001f 7215525a      	bres	21082,#2
5644  0023               L3232:
5645                     ; 1351 }
5648  0023 84            	pop	a
5649  0024 81            	ret	
5685                     ; 1359 void TIM1_OC4FastConfig(FunctionalState NewState)
5685                     ; 1360 {
5686                     .text:	section	.text,new
5687  0000               _TIM1_OC4FastConfig:
5689  0000 88            	push	a
5690       00000000      OFST:	set	0
5693                     ; 1362   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
5695  0001 4d            	tnz	a
5696  0002 2711          	jreq	L0731
5697  0004 4a            	dec	a
5698  0005 270e          	jreq	L0731
5699  0007 ae0552        	ldw	x,#1362
5700  000a 89            	pushw	x
5701  000b 5f            	clrw	x
5702  000c 89            	pushw	x
5703  000d ae0000        	ldw	x,#L101
5704  0010 cd0000        	call	_assert_failed
5706  0013 5b04          	addw	sp,#4
5707  0015               L0731:
5708                     ; 1365   if (NewState != DISABLE)
5710  0015 7b01          	ld	a,(OFST+1,sp)
5711  0017 2706          	jreq	L3432
5712                     ; 1367     TIM1->CCMR4 |= TIM1_CCMR_OCxFE;
5714  0019 7214525b      	bset	21083,#2
5716  001d 2004          	jra	L5432
5717  001f               L3432:
5718                     ; 1371     TIM1->CCMR4 &= (uint8_t)(~TIM1_CCMR_OCxFE);
5720  001f 7215525b      	bres	21083,#2
5721  0023               L5432:
5722                     ; 1373 }
5725  0023 84            	pop	a
5726  0024 81            	ret	
5832                     ; 1389 void TIM1_GenerateEvent(TIM1_EventSource_TypeDef TIM1_EventSource)
5832                     ; 1390 {
5833                     .text:	section	.text,new
5834  0000               _TIM1_GenerateEvent:
5836  0000 88            	push	a
5837       00000000      OFST:	set	0
5840                     ; 1392   assert_param(IS_TIM1_EVENT_SOURCE_OK(TIM1_EventSource));
5842  0001 4d            	tnz	a
5843  0002 260e          	jrne	L0041
5844  0004 ae0570        	ldw	x,#1392
5845  0007 89            	pushw	x
5846  0008 5f            	clrw	x
5847  0009 89            	pushw	x
5848  000a ae0000        	ldw	x,#L101
5849  000d cd0000        	call	_assert_failed
5851  0010 5b04          	addw	sp,#4
5852  0012               L0041:
5853                     ; 1395   TIM1->EGR = (uint8_t)TIM1_EventSource;
5855  0012 7b01          	ld	a,(OFST+1,sp)
5856  0014 c75257        	ld	21079,a
5857                     ; 1396 }
5860  0017 84            	pop	a
5861  0018 81            	ret	
5898                     ; 1406 void TIM1_OC1PolarityConfig(TIM1_OCPolarity_TypeDef TIM1_OCPolarity)
5898                     ; 1407 {
5899                     .text:	section	.text,new
5900  0000               _TIM1_OC1PolarityConfig:
5902  0000 88            	push	a
5903       00000000      OFST:	set	0
5906                     ; 1409   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
5908  0001 4d            	tnz	a
5909  0002 2712          	jreq	L2141
5910  0004 a122          	cp	a,#34
5911  0006 270e          	jreq	L2141
5912  0008 ae0581        	ldw	x,#1409
5913  000b 89            	pushw	x
5914  000c 5f            	clrw	x
5915  000d 89            	pushw	x
5916  000e ae0000        	ldw	x,#L101
5917  0011 cd0000        	call	_assert_failed
5919  0014 5b04          	addw	sp,#4
5920  0016               L2141:
5921                     ; 1412   if (TIM1_OCPolarity != TIM1_OCPOLARITY_HIGH)
5923  0016 7b01          	ld	a,(OFST+1,sp)
5924  0018 2706          	jreq	L7242
5925                     ; 1414     TIM1->CCER1 |= TIM1_CCER1_CC1P;
5927  001a 7212525c      	bset	21084,#1
5929  001e 2004          	jra	L1342
5930  0020               L7242:
5931                     ; 1418     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1P);
5933  0020 7213525c      	bres	21084,#1
5934  0024               L1342:
5935                     ; 1420 }
5938  0024 84            	pop	a
5939  0025 81            	ret	
5976                     ; 1430 void TIM1_OC1NPolarityConfig(TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity)
5976                     ; 1431 {
5977                     .text:	section	.text,new
5978  0000               _TIM1_OC1NPolarityConfig:
5980  0000 88            	push	a
5981       00000000      OFST:	set	0
5984                     ; 1433   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
5986  0001 4d            	tnz	a
5987  0002 2712          	jreq	L4241
5988  0004 a188          	cp	a,#136
5989  0006 270e          	jreq	L4241
5990  0008 ae0599        	ldw	x,#1433
5991  000b 89            	pushw	x
5992  000c 5f            	clrw	x
5993  000d 89            	pushw	x
5994  000e ae0000        	ldw	x,#L101
5995  0011 cd0000        	call	_assert_failed
5997  0014 5b04          	addw	sp,#4
5998  0016               L4241:
5999                     ; 1436   if (TIM1_OCNPolarity != TIM1_OCNPOLARITY_HIGH)
6001  0016 7b01          	ld	a,(OFST+1,sp)
6002  0018 2706          	jreq	L1542
6003                     ; 1438     TIM1->CCER1 |= TIM1_CCER1_CC1NP;
6005  001a 7216525c      	bset	21084,#3
6007  001e 2004          	jra	L3542
6008  0020               L1542:
6009                     ; 1442     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1NP);
6011  0020 7217525c      	bres	21084,#3
6012  0024               L3542:
6013                     ; 1444 }
6016  0024 84            	pop	a
6017  0025 81            	ret	
6054                     ; 1454 void TIM1_OC2PolarityConfig(TIM1_OCPolarity_TypeDef TIM1_OCPolarity)
6054                     ; 1455 {
6055                     .text:	section	.text,new
6056  0000               _TIM1_OC2PolarityConfig:
6058  0000 88            	push	a
6059       00000000      OFST:	set	0
6062                     ; 1457   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
6064  0001 4d            	tnz	a
6065  0002 2712          	jreq	L6341
6066  0004 a122          	cp	a,#34
6067  0006 270e          	jreq	L6341
6068  0008 ae05b1        	ldw	x,#1457
6069  000b 89            	pushw	x
6070  000c 5f            	clrw	x
6071  000d 89            	pushw	x
6072  000e ae0000        	ldw	x,#L101
6073  0011 cd0000        	call	_assert_failed
6075  0014 5b04          	addw	sp,#4
6076  0016               L6341:
6077                     ; 1460   if (TIM1_OCPolarity != TIM1_OCPOLARITY_HIGH)
6079  0016 7b01          	ld	a,(OFST+1,sp)
6080  0018 2706          	jreq	L3742
6081                     ; 1462     TIM1->CCER1 |= TIM1_CCER1_CC2P;
6083  001a 721a525c      	bset	21084,#5
6085  001e 2004          	jra	L5742
6086  0020               L3742:
6087                     ; 1466     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2P);
6089  0020 721b525c      	bres	21084,#5
6090  0024               L5742:
6091                     ; 1468 }
6094  0024 84            	pop	a
6095  0025 81            	ret	
6132                     ; 1478 void TIM1_OC2NPolarityConfig(TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity)
6132                     ; 1479 {
6133                     .text:	section	.text,new
6134  0000               _TIM1_OC2NPolarityConfig:
6136  0000 88            	push	a
6137       00000000      OFST:	set	0
6140                     ; 1481   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
6142  0001 4d            	tnz	a
6143  0002 2712          	jreq	L0541
6144  0004 a188          	cp	a,#136
6145  0006 270e          	jreq	L0541
6146  0008 ae05c9        	ldw	x,#1481
6147  000b 89            	pushw	x
6148  000c 5f            	clrw	x
6149  000d 89            	pushw	x
6150  000e ae0000        	ldw	x,#L101
6151  0011 cd0000        	call	_assert_failed
6153  0014 5b04          	addw	sp,#4
6154  0016               L0541:
6155                     ; 1484   if (TIM1_OCNPolarity != TIM1_OCNPOLARITY_HIGH)
6157  0016 7b01          	ld	a,(OFST+1,sp)
6158  0018 2706          	jreq	L5152
6159                     ; 1486     TIM1->CCER1 |= TIM1_CCER1_CC2NP;
6161  001a 721e525c      	bset	21084,#7
6163  001e 2004          	jra	L7152
6164  0020               L5152:
6165                     ; 1490     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2NP);
6167  0020 721f525c      	bres	21084,#7
6168  0024               L7152:
6169                     ; 1492 }
6172  0024 84            	pop	a
6173  0025 81            	ret	
6210                     ; 1502 void TIM1_OC3PolarityConfig(TIM1_OCPolarity_TypeDef TIM1_OCPolarity)
6210                     ; 1503 {
6211                     .text:	section	.text,new
6212  0000               _TIM1_OC3PolarityConfig:
6214  0000 88            	push	a
6215       00000000      OFST:	set	0
6218                     ; 1505   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
6220  0001 4d            	tnz	a
6221  0002 2712          	jreq	L2641
6222  0004 a122          	cp	a,#34
6223  0006 270e          	jreq	L2641
6224  0008 ae05e1        	ldw	x,#1505
6225  000b 89            	pushw	x
6226  000c 5f            	clrw	x
6227  000d 89            	pushw	x
6228  000e ae0000        	ldw	x,#L101
6229  0011 cd0000        	call	_assert_failed
6231  0014 5b04          	addw	sp,#4
6232  0016               L2641:
6233                     ; 1508   if (TIM1_OCPolarity != TIM1_OCPOLARITY_HIGH)
6235  0016 7b01          	ld	a,(OFST+1,sp)
6236  0018 2706          	jreq	L7352
6237                     ; 1510     TIM1->CCER2 |= TIM1_CCER2_CC3P;
6239  001a 7212525d      	bset	21085,#1
6241  001e 2004          	jra	L1452
6242  0020               L7352:
6243                     ; 1514     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3P);
6245  0020 7213525d      	bres	21085,#1
6246  0024               L1452:
6247                     ; 1516 }
6250  0024 84            	pop	a
6251  0025 81            	ret	
6288                     ; 1527 void TIM1_OC3NPolarityConfig(TIM1_OCNPolarity_TypeDef TIM1_OCNPolarity)
6288                     ; 1528 {
6289                     .text:	section	.text,new
6290  0000               _TIM1_OC3NPolarityConfig:
6292  0000 88            	push	a
6293       00000000      OFST:	set	0
6296                     ; 1530   assert_param(IS_TIM1_OCN_POLARITY_OK(TIM1_OCNPolarity));
6298  0001 4d            	tnz	a
6299  0002 2712          	jreq	L4741
6300  0004 a188          	cp	a,#136
6301  0006 270e          	jreq	L4741
6302  0008 ae05fa        	ldw	x,#1530
6303  000b 89            	pushw	x
6304  000c 5f            	clrw	x
6305  000d 89            	pushw	x
6306  000e ae0000        	ldw	x,#L101
6307  0011 cd0000        	call	_assert_failed
6309  0014 5b04          	addw	sp,#4
6310  0016               L4741:
6311                     ; 1533   if (TIM1_OCNPolarity != TIM1_OCNPOLARITY_HIGH)
6313  0016 7b01          	ld	a,(OFST+1,sp)
6314  0018 2706          	jreq	L1652
6315                     ; 1535     TIM1->CCER2 |= TIM1_CCER2_CC3NP;
6317  001a 7216525d      	bset	21085,#3
6319  001e 2004          	jra	L3652
6320  0020               L1652:
6321                     ; 1539     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3NP);
6323  0020 7217525d      	bres	21085,#3
6324  0024               L3652:
6325                     ; 1541 }
6328  0024 84            	pop	a
6329  0025 81            	ret	
6366                     ; 1551 void TIM1_OC4PolarityConfig(TIM1_OCPolarity_TypeDef TIM1_OCPolarity)
6366                     ; 1552 {
6367                     .text:	section	.text,new
6368  0000               _TIM1_OC4PolarityConfig:
6370  0000 88            	push	a
6371       00000000      OFST:	set	0
6374                     ; 1554   assert_param(IS_TIM1_OC_POLARITY_OK(TIM1_OCPolarity));
6376  0001 4d            	tnz	a
6377  0002 2712          	jreq	L6051
6378  0004 a122          	cp	a,#34
6379  0006 270e          	jreq	L6051
6380  0008 ae0612        	ldw	x,#1554
6381  000b 89            	pushw	x
6382  000c 5f            	clrw	x
6383  000d 89            	pushw	x
6384  000e ae0000        	ldw	x,#L101
6385  0011 cd0000        	call	_assert_failed
6387  0014 5b04          	addw	sp,#4
6388  0016               L6051:
6389                     ; 1557   if (TIM1_OCPolarity != TIM1_OCPOLARITY_HIGH)
6391  0016 7b01          	ld	a,(OFST+1,sp)
6392  0018 2706          	jreq	L3062
6393                     ; 1559     TIM1->CCER2 |= TIM1_CCER2_CC4P;
6395  001a 721a525d      	bset	21085,#5
6397  001e 2004          	jra	L5062
6398  0020               L3062:
6399                     ; 1563     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC4P);
6401  0020 721b525d      	bres	21085,#5
6402  0024               L5062:
6403                     ; 1565 }
6406  0024 84            	pop	a
6407  0025 81            	ret	
6453                     ; 1579 void TIM1_CCxCmd(TIM1_Channel_TypeDef TIM1_Channel, FunctionalState NewState)
6453                     ; 1580 {
6454                     .text:	section	.text,new
6455  0000               _TIM1_CCxCmd:
6457  0000 89            	pushw	x
6458       00000000      OFST:	set	0
6461                     ; 1582   assert_param(IS_TIM1_CHANNEL_OK(TIM1_Channel));
6463  0001 9e            	ld	a,xh
6464  0002 4d            	tnz	a
6465  0003 2713          	jreq	L0251
6466  0005 9e            	ld	a,xh
6467  0006 4a            	dec	a
6468  0007 270f          	jreq	L0251
6469  0009 9e            	ld	a,xh
6470  000a a102          	cp	a,#2
6471  000c 270a          	jreq	L0251
6472  000e 9e            	ld	a,xh
6473  000f a103          	cp	a,#3
6474  0011 2705          	jreq	L0251
6475  0013 ae062e        	ldw	x,#1582
6476  0016 ad58          	call	LC013
6477  0018               L0251:
6478                     ; 1583   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
6480  0018 7b02          	ld	a,(OFST+2,sp)
6481  001a 2708          	jreq	L0351
6482  001c 4a            	dec	a
6483  001d 2705          	jreq	L0351
6484  001f ae062f        	ldw	x,#1583
6485  0022 ad4c          	call	LC013
6486  0024               L0351:
6487                     ; 1585   if (TIM1_Channel == TIM1_CHANNEL_1)
6489  0024 7b01          	ld	a,(OFST+1,sp)
6490  0026 2610          	jrne	L1362
6491                     ; 1588     if (NewState != DISABLE)
6493  0028 7b02          	ld	a,(OFST+2,sp)
6494  002a 2706          	jreq	L3362
6495                     ; 1590       TIM1->CCER1 |= TIM1_CCER1_CC1E;
6497  002c 7210525c      	bset	21084,#0
6499  0030 203c          	jra	L7362
6500  0032               L3362:
6501                     ; 1594       TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1E);
6503  0032 7211525c      	bres	21084,#0
6504  0036 2036          	jra	L7362
6505  0038               L1362:
6506                     ; 1598   else if (TIM1_Channel == TIM1_CHANNEL_2)
6508  0038 a101          	cp	a,#1
6509  003a 2610          	jrne	L1462
6510                     ; 1601     if (NewState != DISABLE)
6512  003c 7b02          	ld	a,(OFST+2,sp)
6513  003e 2706          	jreq	L3462
6514                     ; 1603       TIM1->CCER1 |= TIM1_CCER1_CC2E;
6516  0040 7218525c      	bset	21084,#4
6518  0044 2028          	jra	L7362
6519  0046               L3462:
6520                     ; 1607       TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2E);
6522  0046 7219525c      	bres	21084,#4
6523  004a 2022          	jra	L7362
6524  004c               L1462:
6525                     ; 1610   else if (TIM1_Channel == TIM1_CHANNEL_3)
6527  004c a102          	cp	a,#2
6528  004e 2610          	jrne	L1562
6529                     ; 1613     if (NewState != DISABLE)
6531  0050 7b02          	ld	a,(OFST+2,sp)
6532  0052 2706          	jreq	L3562
6533                     ; 1615       TIM1->CCER2 |= TIM1_CCER2_CC3E;
6535  0054 7210525d      	bset	21085,#0
6537  0058 2014          	jra	L7362
6538  005a               L3562:
6539                     ; 1619       TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3E);
6541  005a 7211525d      	bres	21085,#0
6542  005e 200e          	jra	L7362
6543  0060               L1562:
6544                     ; 1625     if (NewState != DISABLE)
6546  0060 7b02          	ld	a,(OFST+2,sp)
6547  0062 2706          	jreq	L1662
6548                     ; 1627       TIM1->CCER2 |= TIM1_CCER2_CC4E;
6550  0064 7218525d      	bset	21085,#4
6552  0068 2004          	jra	L7362
6553  006a               L1662:
6554                     ; 1631       TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC4E);
6556  006a 7219525d      	bres	21085,#4
6557  006e               L7362:
6558                     ; 1634 }
6561  006e 85            	popw	x
6562  006f 81            	ret	
6563  0070               LC013:
6564  0070 89            	pushw	x
6565  0071 5f            	clrw	x
6566  0072 89            	pushw	x
6567  0073 ae0000        	ldw	x,#L101
6568  0076 cd0000        	call	_assert_failed
6570  0079 5b04          	addw	sp,#4
6571  007b 81            	ret	
6617                     ; 1647 void TIM1_CCxNCmd(TIM1_Channel_TypeDef TIM1_Channel, FunctionalState NewState)
6617                     ; 1648 {
6618                     .text:	section	.text,new
6619  0000               _TIM1_CCxNCmd:
6621  0000 89            	pushw	x
6622       00000000      OFST:	set	0
6625                     ; 1650   assert_param(IS_TIM1_COMPLEMENTARY_CHANNEL_OK(TIM1_Channel));
6627  0001 9e            	ld	a,xh
6628  0002 4d            	tnz	a
6629  0003 270e          	jreq	L2451
6630  0005 9e            	ld	a,xh
6631  0006 4a            	dec	a
6632  0007 270a          	jreq	L2451
6633  0009 9e            	ld	a,xh
6634  000a a102          	cp	a,#2
6635  000c 2705          	jreq	L2451
6636  000e ae0672        	ldw	x,#1650
6637  0011 ad43          	call	LC014
6638  0013               L2451:
6639                     ; 1651   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
6641  0013 7b02          	ld	a,(OFST+2,sp)
6642  0015 2708          	jreq	L2551
6643  0017 4a            	dec	a
6644  0018 2705          	jreq	L2551
6645  001a ae0673        	ldw	x,#1651
6646  001d ad37          	call	LC014
6647  001f               L2551:
6648                     ; 1653   if (TIM1_Channel == TIM1_CHANNEL_1)
6650  001f 7b01          	ld	a,(OFST+1,sp)
6651  0021 2610          	jrne	L7072
6652                     ; 1656     if (NewState != DISABLE)
6654  0023 7b02          	ld	a,(OFST+2,sp)
6655  0025 2706          	jreq	L1172
6656                     ; 1658       TIM1->CCER1 |= TIM1_CCER1_CC1NE;
6658  0027 7214525c      	bset	21084,#2
6660  002b 2027          	jra	L5172
6661  002d               L1172:
6662                     ; 1662       TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1NE);
6664  002d 7215525c      	bres	21084,#2
6665  0031 2021          	jra	L5172
6666  0033               L7072:
6667                     ; 1665   else if (TIM1_Channel == TIM1_CHANNEL_2)
6669  0033 4a            	dec	a
6670  0034 2610          	jrne	L7172
6671                     ; 1668     if (NewState != DISABLE)
6673  0036 7b02          	ld	a,(OFST+2,sp)
6674  0038 2706          	jreq	L1272
6675                     ; 1670       TIM1->CCER1 |= TIM1_CCER1_CC2NE;
6677  003a 721c525c      	bset	21084,#6
6679  003e 2014          	jra	L5172
6680  0040               L1272:
6681                     ; 1674       TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2NE);
6683  0040 721d525c      	bres	21084,#6
6684  0044 200e          	jra	L5172
6685  0046               L7172:
6686                     ; 1680     if (NewState != DISABLE)
6688  0046 7b02          	ld	a,(OFST+2,sp)
6689  0048 2706          	jreq	L7272
6690                     ; 1682       TIM1->CCER2 |= TIM1_CCER2_CC3NE;
6692  004a 7214525d      	bset	21085,#2
6694  004e 2004          	jra	L5172
6695  0050               L7272:
6696                     ; 1686       TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3NE);
6698  0050 7215525d      	bres	21085,#2
6699  0054               L5172:
6700                     ; 1689 }
6703  0054 85            	popw	x
6704  0055 81            	ret	
6705  0056               LC014:
6706  0056 89            	pushw	x
6707  0057 5f            	clrw	x
6708  0058 89            	pushw	x
6709  0059 ae0000        	ldw	x,#L101
6710  005c cd0000        	call	_assert_failed
6712  005f 5b04          	addw	sp,#4
6713  0061 81            	ret	
6759                     ; 1712 void TIM1_SelectOCxM(TIM1_Channel_TypeDef TIM1_Channel, TIM1_OCMode_TypeDef TIM1_OCMode)
6759                     ; 1713 {
6760                     .text:	section	.text,new
6761  0000               _TIM1_SelectOCxM:
6763  0000 89            	pushw	x
6764       00000000      OFST:	set	0
6767                     ; 1715   assert_param(IS_TIM1_CHANNEL_OK(TIM1_Channel));
6769  0001 9e            	ld	a,xh
6770  0002 4d            	tnz	a
6771  0003 2713          	jreq	L4651
6772  0005 9e            	ld	a,xh
6773  0006 4a            	dec	a
6774  0007 270f          	jreq	L4651
6775  0009 9e            	ld	a,xh
6776  000a a102          	cp	a,#2
6777  000c 270a          	jreq	L4651
6778  000e 9e            	ld	a,xh
6779  000f a103          	cp	a,#3
6780  0011 2705          	jreq	L4651
6781  0013 ae06b3        	ldw	x,#1715
6782  0016 ad71          	call	LC015
6783  0018               L4651:
6784                     ; 1716   assert_param(IS_TIM1_OCM_OK(TIM1_OCMode));
6786  0018 7b02          	ld	a,(OFST+2,sp)
6787  001a 2721          	jreq	L4751
6788  001c a110          	cp	a,#16
6789  001e 271d          	jreq	L4751
6790  0020 a120          	cp	a,#32
6791  0022 2719          	jreq	L4751
6792  0024 a130          	cp	a,#48
6793  0026 2715          	jreq	L4751
6794  0028 a160          	cp	a,#96
6795  002a 2711          	jreq	L4751
6796  002c a170          	cp	a,#112
6797  002e 270d          	jreq	L4751
6798  0030 a150          	cp	a,#80
6799  0032 2709          	jreq	L4751
6800  0034 a140          	cp	a,#64
6801  0036 2705          	jreq	L4751
6802  0038 ae06b4        	ldw	x,#1716
6803  003b ad4c          	call	LC015
6804  003d               L4751:
6805                     ; 1718   if (TIM1_Channel == TIM1_CHANNEL_1)
6807  003d 7b01          	ld	a,(OFST+1,sp)
6808  003f 2610          	jrne	L5572
6809                     ; 1721     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1E);
6811  0041 7211525c      	bres	21084,#0
6812                     ; 1724     TIM1->CCMR1 = (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_OCM)) 
6812                     ; 1725                             | (uint8_t)TIM1_OCMode);
6814  0045 c65258        	ld	a,21080
6815  0048 a48f          	and	a,#143
6816  004a 1a02          	or	a,(OFST+2,sp)
6817  004c c75258        	ld	21080,a
6819  004f 2036          	jra	L7572
6820  0051               L5572:
6821                     ; 1727   else if (TIM1_Channel == TIM1_CHANNEL_2)
6823  0051 a101          	cp	a,#1
6824  0053 2610          	jrne	L1672
6825                     ; 1730     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2E);
6827  0055 7219525c      	bres	21084,#4
6828                     ; 1733     TIM1->CCMR2 = (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_OCM))
6828                     ; 1734                             | (uint8_t)TIM1_OCMode);
6830  0059 c65259        	ld	a,21081
6831  005c a48f          	and	a,#143
6832  005e 1a02          	or	a,(OFST+2,sp)
6833  0060 c75259        	ld	21081,a
6835  0063 2022          	jra	L7572
6836  0065               L1672:
6837                     ; 1736   else if (TIM1_Channel == TIM1_CHANNEL_3)
6839  0065 a102          	cp	a,#2
6840  0067 2610          	jrne	L5672
6841                     ; 1739     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3E);
6843  0069 7211525d      	bres	21085,#0
6844                     ; 1742     TIM1->CCMR3 = (uint8_t)((uint8_t)(TIM1->CCMR3 & (uint8_t)(~TIM1_CCMR_OCM)) 
6844                     ; 1743                             | (uint8_t)TIM1_OCMode);
6846  006d c6525a        	ld	a,21082
6847  0070 a48f          	and	a,#143
6848  0072 1a02          	or	a,(OFST+2,sp)
6849  0074 c7525a        	ld	21082,a
6851  0077 200e          	jra	L7572
6852  0079               L5672:
6853                     ; 1748     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC4E);
6855  0079 7219525d      	bres	21085,#4
6856                     ; 1751     TIM1->CCMR4 = (uint8_t)((uint8_t)(TIM1->CCMR4 & (uint8_t)(~TIM1_CCMR_OCM)) 
6856                     ; 1752                             | (uint8_t)TIM1_OCMode);
6858  007d c6525b        	ld	a,21083
6859  0080 a48f          	and	a,#143
6860  0082 1a02          	or	a,(OFST+2,sp)
6861  0084 c7525b        	ld	21083,a
6862  0087               L7572:
6863                     ; 1754 }
6866  0087 85            	popw	x
6867  0088 81            	ret	
6868  0089               LC015:
6869  0089 89            	pushw	x
6870  008a 5f            	clrw	x
6871  008b 89            	pushw	x
6872  008c ae0000        	ldw	x,#L101
6873  008f cd0000        	call	_assert_failed
6875  0092 5b04          	addw	sp,#4
6876  0094 81            	ret	
6910                     ; 1762 void TIM1_SetCounter(uint16_t Counter)
6910                     ; 1763 {
6911                     .text:	section	.text,new
6912  0000               _TIM1_SetCounter:
6916                     ; 1765   TIM1->CNTRH = (uint8_t)(Counter >> 8);
6918  0000 9e            	ld	a,xh
6919  0001 c7525e        	ld	21086,a
6920                     ; 1766   TIM1->CNTRL = (uint8_t)(Counter);
6922  0004 9f            	ld	a,xl
6923  0005 c7525f        	ld	21087,a
6924                     ; 1767 }
6927  0008 81            	ret	
6961                     ; 1775 void TIM1_SetAutoreload(uint16_t Autoreload)
6961                     ; 1776 {
6962                     .text:	section	.text,new
6963  0000               _TIM1_SetAutoreload:
6967                     ; 1778   TIM1->ARRH = (uint8_t)(Autoreload >> 8);
6969  0000 9e            	ld	a,xh
6970  0001 c75262        	ld	21090,a
6971                     ; 1779   TIM1->ARRL = (uint8_t)(Autoreload);
6973  0004 9f            	ld	a,xl
6974  0005 c75263        	ld	21091,a
6975                     ; 1780  }
6978  0008 81            	ret	
7012                     ; 1788 void TIM1_SetCompare1(uint16_t Compare1)
7012                     ; 1789 {
7013                     .text:	section	.text,new
7014  0000               _TIM1_SetCompare1:
7018                     ; 1791   TIM1->CCR1H = (uint8_t)(Compare1 >> 8);
7020  0000 9e            	ld	a,xh
7021  0001 c75265        	ld	21093,a
7022                     ; 1792   TIM1->CCR1L = (uint8_t)(Compare1);
7024  0004 9f            	ld	a,xl
7025  0005 c75266        	ld	21094,a
7026                     ; 1793 }
7029  0008 81            	ret	
7063                     ; 1801 void TIM1_SetCompare2(uint16_t Compare2)
7063                     ; 1802 {
7064                     .text:	section	.text,new
7065  0000               _TIM1_SetCompare2:
7069                     ; 1804   TIM1->CCR2H = (uint8_t)(Compare2 >> 8);
7071  0000 9e            	ld	a,xh
7072  0001 c75267        	ld	21095,a
7073                     ; 1805   TIM1->CCR2L = (uint8_t)(Compare2);
7075  0004 9f            	ld	a,xl
7076  0005 c75268        	ld	21096,a
7077                     ; 1806 }
7080  0008 81            	ret	
7114                     ; 1814 void TIM1_SetCompare3(uint16_t Compare3)
7114                     ; 1815 {
7115                     .text:	section	.text,new
7116  0000               _TIM1_SetCompare3:
7120                     ; 1817   TIM1->CCR3H = (uint8_t)(Compare3 >> 8);
7122  0000 9e            	ld	a,xh
7123  0001 c75269        	ld	21097,a
7124                     ; 1818   TIM1->CCR3L = (uint8_t)(Compare3);
7126  0004 9f            	ld	a,xl
7127  0005 c7526a        	ld	21098,a
7128                     ; 1819 }
7131  0008 81            	ret	
7165                     ; 1827 void TIM1_SetCompare4(uint16_t Compare4)
7165                     ; 1828 {
7166                     .text:	section	.text,new
7167  0000               _TIM1_SetCompare4:
7171                     ; 1830   TIM1->CCR4H = (uint8_t)(Compare4 >> 8);
7173  0000 9e            	ld	a,xh
7174  0001 c7526b        	ld	21099,a
7175                     ; 1831   TIM1->CCR4L = (uint8_t)(Compare4);
7177  0004 9f            	ld	a,xl
7178  0005 c7526c        	ld	21100,a
7179                     ; 1832 }
7182  0008 81            	ret	
7219                     ; 1844 void TIM1_SetIC1Prescaler(TIM1_ICPSC_TypeDef TIM1_IC1Prescaler)
7219                     ; 1845 {
7220                     .text:	section	.text,new
7221  0000               _TIM1_SetIC1Prescaler:
7223  0000 88            	push	a
7224       00000000      OFST:	set	0
7227                     ; 1847   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_IC1Prescaler));
7229  0001 4d            	tnz	a
7230  0002 271a          	jreq	L2261
7231  0004 a104          	cp	a,#4
7232  0006 2716          	jreq	L2261
7233  0008 a108          	cp	a,#8
7234  000a 2712          	jreq	L2261
7235  000c a10c          	cp	a,#12
7236  000e 270e          	jreq	L2261
7237  0010 ae0737        	ldw	x,#1847
7238  0013 89            	pushw	x
7239  0014 5f            	clrw	x
7240  0015 89            	pushw	x
7241  0016 ae0000        	ldw	x,#L101
7242  0019 cd0000        	call	_assert_failed
7244  001c 5b04          	addw	sp,#4
7245  001e               L2261:
7246                     ; 1850   TIM1->CCMR1 = (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~TIM1_CCMR_ICxPSC)) 
7246                     ; 1851                           | (uint8_t)TIM1_IC1Prescaler);
7248  001e c65258        	ld	a,21080
7249  0021 a4f3          	and	a,#243
7250  0023 1a01          	or	a,(OFST+1,sp)
7251  0025 c75258        	ld	21080,a
7252                     ; 1852 }
7255  0028 84            	pop	a
7256  0029 81            	ret	
7293                     ; 1864 void TIM1_SetIC2Prescaler(TIM1_ICPSC_TypeDef TIM1_IC2Prescaler)
7293                     ; 1865 {
7294                     .text:	section	.text,new
7295  0000               _TIM1_SetIC2Prescaler:
7297  0000 88            	push	a
7298       00000000      OFST:	set	0
7301                     ; 1868   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_IC2Prescaler));
7303  0001 4d            	tnz	a
7304  0002 271a          	jreq	L4361
7305  0004 a104          	cp	a,#4
7306  0006 2716          	jreq	L4361
7307  0008 a108          	cp	a,#8
7308  000a 2712          	jreq	L4361
7309  000c a10c          	cp	a,#12
7310  000e 270e          	jreq	L4361
7311  0010 ae074c        	ldw	x,#1868
7312  0013 89            	pushw	x
7313  0014 5f            	clrw	x
7314  0015 89            	pushw	x
7315  0016 ae0000        	ldw	x,#L101
7316  0019 cd0000        	call	_assert_failed
7318  001c 5b04          	addw	sp,#4
7319  001e               L4361:
7320                     ; 1871   TIM1->CCMR2 = (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~TIM1_CCMR_ICxPSC))
7320                     ; 1872                           | (uint8_t)TIM1_IC2Prescaler);
7322  001e c65259        	ld	a,21081
7323  0021 a4f3          	and	a,#243
7324  0023 1a01          	or	a,(OFST+1,sp)
7325  0025 c75259        	ld	21081,a
7326                     ; 1873 }
7329  0028 84            	pop	a
7330  0029 81            	ret	
7367                     ; 1885 void TIM1_SetIC3Prescaler(TIM1_ICPSC_TypeDef TIM1_IC3Prescaler)
7367                     ; 1886 {
7368                     .text:	section	.text,new
7369  0000               _TIM1_SetIC3Prescaler:
7371  0000 88            	push	a
7372       00000000      OFST:	set	0
7375                     ; 1889   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_IC3Prescaler));
7377  0001 4d            	tnz	a
7378  0002 271a          	jreq	L6461
7379  0004 a104          	cp	a,#4
7380  0006 2716          	jreq	L6461
7381  0008 a108          	cp	a,#8
7382  000a 2712          	jreq	L6461
7383  000c a10c          	cp	a,#12
7384  000e 270e          	jreq	L6461
7385  0010 ae0761        	ldw	x,#1889
7386  0013 89            	pushw	x
7387  0014 5f            	clrw	x
7388  0015 89            	pushw	x
7389  0016 ae0000        	ldw	x,#L101
7390  0019 cd0000        	call	_assert_failed
7392  001c 5b04          	addw	sp,#4
7393  001e               L6461:
7394                     ; 1892   TIM1->CCMR3 = (uint8_t)((uint8_t)(TIM1->CCMR3 & (uint8_t)(~TIM1_CCMR_ICxPSC)) | 
7394                     ; 1893                           (uint8_t)TIM1_IC3Prescaler);
7396  001e c6525a        	ld	a,21082
7397  0021 a4f3          	and	a,#243
7398  0023 1a01          	or	a,(OFST+1,sp)
7399  0025 c7525a        	ld	21082,a
7400                     ; 1894 }
7403  0028 84            	pop	a
7404  0029 81            	ret	
7441                     ; 1906 void TIM1_SetIC4Prescaler(TIM1_ICPSC_TypeDef TIM1_IC4Prescaler)
7441                     ; 1907 {
7442                     .text:	section	.text,new
7443  0000               _TIM1_SetIC4Prescaler:
7445  0000 88            	push	a
7446       00000000      OFST:	set	0
7449                     ; 1910   assert_param(IS_TIM1_IC_PRESCALER_OK(TIM1_IC4Prescaler));
7451  0001 4d            	tnz	a
7452  0002 271a          	jreq	L0661
7453  0004 a104          	cp	a,#4
7454  0006 2716          	jreq	L0661
7455  0008 a108          	cp	a,#8
7456  000a 2712          	jreq	L0661
7457  000c a10c          	cp	a,#12
7458  000e 270e          	jreq	L0661
7459  0010 ae0776        	ldw	x,#1910
7460  0013 89            	pushw	x
7461  0014 5f            	clrw	x
7462  0015 89            	pushw	x
7463  0016 ae0000        	ldw	x,#L101
7464  0019 cd0000        	call	_assert_failed
7466  001c 5b04          	addw	sp,#4
7467  001e               L0661:
7468                     ; 1913   TIM1->CCMR4 = (uint8_t)((uint8_t)(TIM1->CCMR4 & (uint8_t)(~TIM1_CCMR_ICxPSC)) |
7468                     ; 1914                           (uint8_t)TIM1_IC4Prescaler);
7470  001e c6525b        	ld	a,21083
7471  0021 a4f3          	and	a,#243
7472  0023 1a01          	or	a,(OFST+1,sp)
7473  0025 c7525b        	ld	21083,a
7474                     ; 1915 }
7477  0028 84            	pop	a
7478  0029 81            	ret	
7530                     ; 1922 uint16_t TIM1_GetCapture1(void)
7530                     ; 1923 {
7531                     .text:	section	.text,new
7532  0000               _TIM1_GetCapture1:
7534  0000 5204          	subw	sp,#4
7535       00000004      OFST:	set	4
7538                     ; 1926   uint16_t tmpccr1 = 0;
7540                     ; 1927   uint8_t tmpccr1l=0, tmpccr1h=0;
7544                     ; 1929   tmpccr1h = TIM1->CCR1H;
7546  0002 c65265        	ld	a,21093
7547  0005 6b02          	ld	(OFST-2,sp),a
7549                     ; 1930   tmpccr1l = TIM1->CCR1L;
7551  0007 c65266        	ld	a,21094
7552  000a 6b01          	ld	(OFST-3,sp),a
7554                     ; 1932   tmpccr1 = (uint16_t)(tmpccr1l);
7556  000c 5f            	clrw	x
7557  000d 97            	ld	xl,a
7558  000e 1f03          	ldw	(OFST-1,sp),x
7560                     ; 1933   tmpccr1 |= (uint16_t)((uint16_t)tmpccr1h << 8);
7562  0010 5f            	clrw	x
7563  0011 7b02          	ld	a,(OFST-2,sp)
7564  0013 97            	ld	xl,a
7565  0014 7b04          	ld	a,(OFST+0,sp)
7566  0016 01            	rrwa	x,a
7567  0017 1a03          	or	a,(OFST-1,sp)
7568  0019 01            	rrwa	x,a
7570                     ; 1935   return (uint16_t)tmpccr1;
7574  001a 5b04          	addw	sp,#4
7575  001c 81            	ret	
7627                     ; 1943 uint16_t TIM1_GetCapture2(void)
7627                     ; 1944 {
7628                     .text:	section	.text,new
7629  0000               _TIM1_GetCapture2:
7631  0000 5204          	subw	sp,#4
7632       00000004      OFST:	set	4
7635                     ; 1947   uint16_t tmpccr2 = 0;
7637                     ; 1948   uint8_t tmpccr2l=0, tmpccr2h=0;
7641                     ; 1950   tmpccr2h = TIM1->CCR2H;
7643  0002 c65267        	ld	a,21095
7644  0005 6b02          	ld	(OFST-2,sp),a
7646                     ; 1951   tmpccr2l = TIM1->CCR2L;
7648  0007 c65268        	ld	a,21096
7649  000a 6b01          	ld	(OFST-3,sp),a
7651                     ; 1953   tmpccr2 = (uint16_t)(tmpccr2l);
7653  000c 5f            	clrw	x
7654  000d 97            	ld	xl,a
7655  000e 1f03          	ldw	(OFST-1,sp),x
7657                     ; 1954   tmpccr2 |= (uint16_t)((uint16_t)tmpccr2h << 8);
7659  0010 5f            	clrw	x
7660  0011 7b02          	ld	a,(OFST-2,sp)
7661  0013 97            	ld	xl,a
7662  0014 7b04          	ld	a,(OFST+0,sp)
7663  0016 01            	rrwa	x,a
7664  0017 1a03          	or	a,(OFST-1,sp)
7665  0019 01            	rrwa	x,a
7667                     ; 1956   return (uint16_t)tmpccr2;
7671  001a 5b04          	addw	sp,#4
7672  001c 81            	ret	
7724                     ; 1964 uint16_t TIM1_GetCapture3(void)
7724                     ; 1965 {
7725                     .text:	section	.text,new
7726  0000               _TIM1_GetCapture3:
7728  0000 5204          	subw	sp,#4
7729       00000004      OFST:	set	4
7732                     ; 1967   uint16_t tmpccr3 = 0;
7734                     ; 1968   uint8_t tmpccr3l=0, tmpccr3h=0;
7738                     ; 1970   tmpccr3h = TIM1->CCR3H;
7740  0002 c65269        	ld	a,21097
7741  0005 6b02          	ld	(OFST-2,sp),a
7743                     ; 1971   tmpccr3l = TIM1->CCR3L;
7745  0007 c6526a        	ld	a,21098
7746  000a 6b01          	ld	(OFST-3,sp),a
7748                     ; 1973   tmpccr3 = (uint16_t)(tmpccr3l);
7750  000c 5f            	clrw	x
7751  000d 97            	ld	xl,a
7752  000e 1f03          	ldw	(OFST-1,sp),x
7754                     ; 1974   tmpccr3 |= (uint16_t)((uint16_t)tmpccr3h << 8);
7756  0010 5f            	clrw	x
7757  0011 7b02          	ld	a,(OFST-2,sp)
7758  0013 97            	ld	xl,a
7759  0014 7b04          	ld	a,(OFST+0,sp)
7760  0016 01            	rrwa	x,a
7761  0017 1a03          	or	a,(OFST-1,sp)
7762  0019 01            	rrwa	x,a
7764                     ; 1976   return (uint16_t)tmpccr3;
7768  001a 5b04          	addw	sp,#4
7769  001c 81            	ret	
7821                     ; 1984 uint16_t TIM1_GetCapture4(void)
7821                     ; 1985 {
7822                     .text:	section	.text,new
7823  0000               _TIM1_GetCapture4:
7825  0000 5204          	subw	sp,#4
7826       00000004      OFST:	set	4
7829                     ; 1987   uint16_t tmpccr4 = 0;
7831                     ; 1988   uint8_t tmpccr4l=0, tmpccr4h=0;
7835                     ; 1990   tmpccr4h = TIM1->CCR4H;
7837  0002 c6526b        	ld	a,21099
7838  0005 6b02          	ld	(OFST-2,sp),a
7840                     ; 1991   tmpccr4l = TIM1->CCR4L;
7842  0007 c6526c        	ld	a,21100
7843  000a 6b01          	ld	(OFST-3,sp),a
7845                     ; 1993   tmpccr4 = (uint16_t)(tmpccr4l);
7847  000c 5f            	clrw	x
7848  000d 97            	ld	xl,a
7849  000e 1f03          	ldw	(OFST-1,sp),x
7851                     ; 1994   tmpccr4 |= (uint16_t)((uint16_t)tmpccr4h << 8);
7853  0010 5f            	clrw	x
7854  0011 7b02          	ld	a,(OFST-2,sp)
7855  0013 97            	ld	xl,a
7856  0014 7b04          	ld	a,(OFST+0,sp)
7857  0016 01            	rrwa	x,a
7858  0017 1a03          	or	a,(OFST-1,sp)
7859  0019 01            	rrwa	x,a
7861                     ; 1996   return (uint16_t)tmpccr4;
7865  001a 5b04          	addw	sp,#4
7866  001c 81            	ret	
7900                     ; 2004 uint16_t TIM1_GetCounter(void)
7900                     ; 2005 {
7901                     .text:	section	.text,new
7902  0000               _TIM1_GetCounter:
7904  0000 89            	pushw	x
7905       00000002      OFST:	set	2
7908                     ; 2006   uint16_t tmpcntr = 0;
7910                     ; 2008   tmpcntr = ((uint16_t)TIM1->CNTRH << 8);
7912  0001 c6525e        	ld	a,21086
7913  0004 97            	ld	xl,a
7914  0005 4f            	clr	a
7915  0006 02            	rlwa	x,a
7916  0007 1f01          	ldw	(OFST-1,sp),x
7918                     ; 2011   return (uint16_t)(tmpcntr | (uint16_t)(TIM1->CNTRL));
7920  0009 c6525f        	ld	a,21087
7921  000c 5f            	clrw	x
7922  000d 97            	ld	xl,a
7923  000e 01            	rrwa	x,a
7924  000f 1a02          	or	a,(OFST+0,sp)
7925  0011 01            	rrwa	x,a
7926  0012 1a01          	or	a,(OFST-1,sp)
7927  0014 01            	rrwa	x,a
7930  0015 5b02          	addw	sp,#2
7931  0017 81            	ret	
7965                     ; 2019 uint16_t TIM1_GetPrescaler(void)
7965                     ; 2020 {
7966                     .text:	section	.text,new
7967  0000               _TIM1_GetPrescaler:
7969  0000 89            	pushw	x
7970       00000002      OFST:	set	2
7973                     ; 2021   uint16_t temp = 0;
7975                     ; 2023   temp = ((uint16_t)TIM1->PSCRH << 8);
7977  0001 c65260        	ld	a,21088
7978  0004 97            	ld	xl,a
7979  0005 4f            	clr	a
7980  0006 02            	rlwa	x,a
7981  0007 1f01          	ldw	(OFST-1,sp),x
7983                     ; 2026   return (uint16_t)( temp | (uint16_t)(TIM1->PSCRL));
7985  0009 c65261        	ld	a,21089
7986  000c 5f            	clrw	x
7987  000d 97            	ld	xl,a
7988  000e 01            	rrwa	x,a
7989  000f 1a02          	or	a,(OFST+0,sp)
7990  0011 01            	rrwa	x,a
7991  0012 1a01          	or	a,(OFST-1,sp)
7992  0014 01            	rrwa	x,a
7995  0015 5b02          	addw	sp,#2
7996  0017 81            	ret	
8171                     ; 2047 FlagStatus TIM1_GetFlagStatus(TIM1_FLAG_TypeDef TIM1_FLAG)
8171                     ; 2048 {
8172                     .text:	section	.text,new
8173  0000               _TIM1_GetFlagStatus:
8175  0000 89            	pushw	x
8176  0001 89            	pushw	x
8177       00000002      OFST:	set	2
8180                     ; 2049   FlagStatus bitstatus = RESET;
8182                     ; 2050   uint8_t tim1_flag_l = 0, tim1_flag_h = 0;
8186                     ; 2053   assert_param(IS_TIM1_GET_FLAG_OK(TIM1_FLAG));
8188  0002 a30001        	cpw	x,#1
8189  0005 2745          	jreq	L6071
8190  0007 a30002        	cpw	x,#2
8191  000a 2740          	jreq	L6071
8192  000c a30004        	cpw	x,#4
8193  000f 273b          	jreq	L6071
8194  0011 a30008        	cpw	x,#8
8195  0014 2736          	jreq	L6071
8196  0016 a30010        	cpw	x,#16
8197  0019 2731          	jreq	L6071
8198  001b a30020        	cpw	x,#32
8199  001e 272c          	jreq	L6071
8200  0020 a30040        	cpw	x,#64
8201  0023 2727          	jreq	L6071
8202  0025 a30080        	cpw	x,#128
8203  0028 2722          	jreq	L6071
8204  002a a30200        	cpw	x,#512
8205  002d 271d          	jreq	L6071
8206  002f a30400        	cpw	x,#1024
8207  0032 2718          	jreq	L6071
8208  0034 a30800        	cpw	x,#2048
8209  0037 2713          	jreq	L6071
8210  0039 a31000        	cpw	x,#4096
8211  003c 270e          	jreq	L6071
8212  003e ae0805        	ldw	x,#2053
8213  0041 89            	pushw	x
8214  0042 5f            	clrw	x
8215  0043 89            	pushw	x
8216  0044 ae0000        	ldw	x,#L101
8217  0047 cd0000        	call	_assert_failed
8219  004a 5b04          	addw	sp,#4
8220  004c               L6071:
8221                     ; 2055   tim1_flag_l = (uint8_t)(TIM1->SR1 & (uint8_t)TIM1_FLAG);
8223  004c c65255        	ld	a,21077
8224  004f 1404          	and	a,(OFST+2,sp)
8225  0051 6b01          	ld	(OFST-1,sp),a
8227                     ; 2056   tim1_flag_h = (uint8_t)((uint16_t)TIM1_FLAG >> 8);
8229  0053 7b03          	ld	a,(OFST+1,sp)
8230  0055 6b02          	ld	(OFST+0,sp),a
8232                     ; 2058   if ((tim1_flag_l | (uint8_t)(TIM1->SR2 & tim1_flag_h)) != 0)
8234  0057 c45256        	and	a,21078
8235  005a 1a01          	or	a,(OFST-1,sp)
8236  005c 2702          	jreq	L7643
8237                     ; 2060     bitstatus = SET;
8239  005e a601          	ld	a,#1
8242  0060               L7643:
8243                     ; 2064     bitstatus = RESET;
8246                     ; 2066   return (FlagStatus)(bitstatus);
8250  0060 5b04          	addw	sp,#4
8251  0062 81            	ret	
8287                     ; 2087 void TIM1_ClearFlag(TIM1_FLAG_TypeDef TIM1_FLAG)
8287                     ; 2088 {
8288                     .text:	section	.text,new
8289  0000               _TIM1_ClearFlag:
8291  0000 89            	pushw	x
8292       00000000      OFST:	set	0
8295                     ; 2090   assert_param(IS_TIM1_CLEAR_FLAG_OK(TIM1_FLAG));
8297  0001 01            	rrwa	x,a
8298  0002 9f            	ld	a,xl
8299  0003 a4e1          	and	a,#225
8300  0005 97            	ld	xl,a
8301  0006 4f            	clr	a
8302  0007 02            	rlwa	x,a
8303  0008 5d            	tnzw	x
8304  0009 2604          	jrne	L4171
8305  000b 1e01          	ldw	x,(OFST+1,sp)
8306  000d 260e          	jrne	L6171
8307  000f               L4171:
8308  000f ae082a        	ldw	x,#2090
8309  0012 89            	pushw	x
8310  0013 5f            	clrw	x
8311  0014 89            	pushw	x
8312  0015 ae0000        	ldw	x,#L101
8313  0018 cd0000        	call	_assert_failed
8315  001b 5b04          	addw	sp,#4
8316  001d               L6171:
8317                     ; 2093   TIM1->SR1 = (uint8_t)(~(uint8_t)(TIM1_FLAG));
8319  001d 7b02          	ld	a,(OFST+2,sp)
8320  001f 43            	cpl	a
8321  0020 c75255        	ld	21077,a
8322                     ; 2094   TIM1->SR2 = (uint8_t)((uint8_t)(~((uint8_t)((uint16_t)TIM1_FLAG >> 8))) & 
8322                     ; 2095                         (uint8_t)0x1E);
8324  0023 7b01          	ld	a,(OFST+1,sp)
8325  0025 43            	cpl	a
8326  0026 a41e          	and	a,#30
8327  0028 c75256        	ld	21078,a
8328                     ; 2096 }
8331  002b 85            	popw	x
8332  002c 81            	ret	
8397                     ; 2112 ITStatus TIM1_GetITStatus(TIM1_IT_TypeDef TIM1_IT)
8397                     ; 2113 {
8398                     .text:	section	.text,new
8399  0000               _TIM1_GetITStatus:
8401  0000 88            	push	a
8402  0001 89            	pushw	x
8403       00000002      OFST:	set	2
8406                     ; 2114   ITStatus bitstatus = RESET;
8408                     ; 2115   uint8_t TIM1_itStatus = 0, TIM1_itEnable = 0;
8412                     ; 2118   assert_param(IS_TIM1_GET_IT_OK(TIM1_IT));
8414  0002 a101          	cp	a,#1
8415  0004 272a          	jreq	L0371
8416  0006 a102          	cp	a,#2
8417  0008 2726          	jreq	L0371
8418  000a a104          	cp	a,#4
8419  000c 2722          	jreq	L0371
8420  000e a108          	cp	a,#8
8421  0010 271e          	jreq	L0371
8422  0012 a110          	cp	a,#16
8423  0014 271a          	jreq	L0371
8424  0016 a120          	cp	a,#32
8425  0018 2716          	jreq	L0371
8426  001a a140          	cp	a,#64
8427  001c 2712          	jreq	L0371
8428  001e a180          	cp	a,#128
8429  0020 270e          	jreq	L0371
8430  0022 ae0846        	ldw	x,#2118
8431  0025 89            	pushw	x
8432  0026 5f            	clrw	x
8433  0027 89            	pushw	x
8434  0028 ae0000        	ldw	x,#L101
8435  002b cd0000        	call	_assert_failed
8437  002e 5b04          	addw	sp,#4
8438  0030               L0371:
8439                     ; 2120   TIM1_itStatus = (uint8_t)(TIM1->SR1 & (uint8_t)TIM1_IT);
8441  0030 c65255        	ld	a,21077
8442  0033 1403          	and	a,(OFST+1,sp)
8443  0035 6b01          	ld	(OFST-1,sp),a
8445                     ; 2122   TIM1_itEnable = (uint8_t)(TIM1->IER & (uint8_t)TIM1_IT);
8447  0037 c65254        	ld	a,21076
8448  003a 1403          	and	a,(OFST+1,sp)
8449  003c 6b02          	ld	(OFST+0,sp),a
8451                     ; 2124   if ((TIM1_itStatus != (uint8_t)RESET ) && (TIM1_itEnable != (uint8_t)RESET ))
8453  003e 7b01          	ld	a,(OFST-1,sp)
8454  0040 2708          	jreq	L3453
8456  0042 7b02          	ld	a,(OFST+0,sp)
8457  0044 2704          	jreq	L3453
8458                     ; 2126     bitstatus = SET;
8460  0046 a601          	ld	a,#1
8463  0048 2001          	jra	L5453
8464  004a               L3453:
8465                     ; 2130     bitstatus = RESET;
8467  004a 4f            	clr	a
8469  004b               L5453:
8470                     ; 2132   return (ITStatus)(bitstatus);
8474  004b 5b03          	addw	sp,#3
8475  004d 81            	ret	
8512                     ; 2149 void TIM1_ClearITPendingBit(TIM1_IT_TypeDef TIM1_IT)
8512                     ; 2150 {
8513                     .text:	section	.text,new
8514  0000               _TIM1_ClearITPendingBit:
8516  0000 88            	push	a
8517       00000000      OFST:	set	0
8520                     ; 2152   assert_param(IS_TIM1_IT_OK(TIM1_IT));
8522  0001 4d            	tnz	a
8523  0002 260e          	jrne	L0471
8524  0004 ae0868        	ldw	x,#2152
8525  0007 89            	pushw	x
8526  0008 5f            	clrw	x
8527  0009 89            	pushw	x
8528  000a ae0000        	ldw	x,#L101
8529  000d cd0000        	call	_assert_failed
8531  0010 5b04          	addw	sp,#4
8532  0012               L0471:
8533                     ; 2155   TIM1->SR1 = (uint8_t)(~(uint8_t)TIM1_IT);
8535  0012 7b01          	ld	a,(OFST+1,sp)
8536  0014 43            	cpl	a
8537  0015 c75255        	ld	21077,a
8538                     ; 2156 }
8541  0018 84            	pop	a
8542  0019 81            	ret	
8594                     ; 2174 static void TI1_Config(uint8_t TIM1_ICPolarity,
8594                     ; 2175                        uint8_t TIM1_ICSelection,
8594                     ; 2176                        uint8_t TIM1_ICFilter)
8594                     ; 2177 {
8595                     .text:	section	.text,new
8596  0000               L3_TI1_Config:
8598  0000 89            	pushw	x
8599  0001 88            	push	a
8600       00000001      OFST:	set	1
8603                     ; 2179   TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1E);
8605  0002 7211525c      	bres	21084,#0
8606                     ; 2182   TIM1->CCMR1 = (uint8_t)((uint8_t)(TIM1->CCMR1 & (uint8_t)(~(uint8_t)( TIM1_CCMR_CCxS | TIM1_CCMR_ICxF ))) | 
8606                     ; 2183                           (uint8_t)(( (TIM1_ICSelection)) | ((uint8_t)( TIM1_ICFilter << 4))));
8608  0006 7b06          	ld	a,(OFST+5,sp)
8609  0008 97            	ld	xl,a
8610  0009 a610          	ld	a,#16
8611  000b 42            	mul	x,a
8612  000c 9f            	ld	a,xl
8613  000d 1a03          	or	a,(OFST+2,sp)
8614  000f 6b01          	ld	(OFST+0,sp),a
8616  0011 c65258        	ld	a,21080
8617  0014 a40c          	and	a,#12
8618  0016 1a01          	or	a,(OFST+0,sp)
8619  0018 c75258        	ld	21080,a
8620                     ; 2186   if (TIM1_ICPolarity != TIM1_ICPOLARITY_RISING)
8622  001b 7b02          	ld	a,(OFST+1,sp)
8623  001d 2706          	jreq	L3163
8624                     ; 2188     TIM1->CCER1 |= TIM1_CCER1_CC1P;
8626  001f 7212525c      	bset	21084,#1
8628  0023 2004          	jra	L5163
8629  0025               L3163:
8630                     ; 2192     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1P);
8632  0025 7213525c      	bres	21084,#1
8633  0029               L5163:
8634                     ; 2196   TIM1->CCER1 |=  TIM1_CCER1_CC1E;
8636  0029 7210525c      	bset	21084,#0
8637                     ; 2197 }
8640  002d 5b03          	addw	sp,#3
8641  002f 81            	ret	
8693                     ; 2215 static void TI2_Config(uint8_t TIM1_ICPolarity,
8693                     ; 2216                        uint8_t TIM1_ICSelection,
8693                     ; 2217                        uint8_t TIM1_ICFilter)
8693                     ; 2218 {
8694                     .text:	section	.text,new
8695  0000               L5_TI2_Config:
8697  0000 89            	pushw	x
8698  0001 88            	push	a
8699       00000001      OFST:	set	1
8702                     ; 2220   TIM1->CCER1 &=  (uint8_t)(~TIM1_CCER1_CC2E);
8704  0002 7219525c      	bres	21084,#4
8705                     ; 2223   TIM1->CCMR2  = (uint8_t)((uint8_t)(TIM1->CCMR2 & (uint8_t)(~(uint8_t)( TIM1_CCMR_CCxS | TIM1_CCMR_ICxF ))) 
8705                     ; 2224                            | (uint8_t)(( (TIM1_ICSelection)) | ((uint8_t)( TIM1_ICFilter << 4))));
8707  0006 7b06          	ld	a,(OFST+5,sp)
8708  0008 97            	ld	xl,a
8709  0009 a610          	ld	a,#16
8710  000b 42            	mul	x,a
8711  000c 9f            	ld	a,xl
8712  000d 1a03          	or	a,(OFST+2,sp)
8713  000f 6b01          	ld	(OFST+0,sp),a
8715  0011 c65259        	ld	a,21081
8716  0014 a40c          	and	a,#12
8717  0016 1a01          	or	a,(OFST+0,sp)
8718  0018 c75259        	ld	21081,a
8719                     ; 2226   if (TIM1_ICPolarity != TIM1_ICPOLARITY_RISING)
8721  001b 7b02          	ld	a,(OFST+1,sp)
8722  001d 2706          	jreq	L5463
8723                     ; 2228     TIM1->CCER1 |= TIM1_CCER1_CC2P;
8725  001f 721a525c      	bset	21084,#5
8727  0023 2004          	jra	L7463
8728  0025               L5463:
8729                     ; 2232     TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC2P);
8731  0025 721b525c      	bres	21084,#5
8732  0029               L7463:
8733                     ; 2235   TIM1->CCER1 |=  TIM1_CCER1_CC2E;
8735  0029 7218525c      	bset	21084,#4
8736                     ; 2236 }
8739  002d 5b03          	addw	sp,#3
8740  002f 81            	ret	
8792                     ; 2254 static void TI3_Config(uint8_t TIM1_ICPolarity,
8792                     ; 2255                        uint8_t TIM1_ICSelection,
8792                     ; 2256                        uint8_t TIM1_ICFilter)
8792                     ; 2257 {
8793                     .text:	section	.text,new
8794  0000               L7_TI3_Config:
8796  0000 89            	pushw	x
8797  0001 88            	push	a
8798       00000001      OFST:	set	1
8801                     ; 2259   TIM1->CCER2 &=  (uint8_t)(~TIM1_CCER2_CC3E);
8803  0002 7211525d      	bres	21085,#0
8804                     ; 2262   TIM1->CCMR3 = (uint8_t)((uint8_t)(TIM1->CCMR3 & (uint8_t)(~(uint8_t)( TIM1_CCMR_CCxS | TIM1_CCMR_ICxF))) 
8804                     ; 2263                           | (uint8_t)(( (TIM1_ICSelection)) | ((uint8_t)( TIM1_ICFilter << 4))));
8806  0006 7b06          	ld	a,(OFST+5,sp)
8807  0008 97            	ld	xl,a
8808  0009 a610          	ld	a,#16
8809  000b 42            	mul	x,a
8810  000c 9f            	ld	a,xl
8811  000d 1a03          	or	a,(OFST+2,sp)
8812  000f 6b01          	ld	(OFST+0,sp),a
8814  0011 c6525a        	ld	a,21082
8815  0014 a40c          	and	a,#12
8816  0016 1a01          	or	a,(OFST+0,sp)
8817  0018 c7525a        	ld	21082,a
8818                     ; 2266   if (TIM1_ICPolarity != TIM1_ICPOLARITY_RISING)
8820  001b 7b02          	ld	a,(OFST+1,sp)
8821  001d 2706          	jreq	L7763
8822                     ; 2268     TIM1->CCER2 |= TIM1_CCER2_CC3P;
8824  001f 7212525d      	bset	21085,#1
8826  0023 2004          	jra	L1073
8827  0025               L7763:
8828                     ; 2272     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC3P);
8830  0025 7213525d      	bres	21085,#1
8831  0029               L1073:
8832                     ; 2275   TIM1->CCER2 |=  TIM1_CCER2_CC3E;
8834  0029 7210525d      	bset	21085,#0
8835                     ; 2276 }
8838  002d 5b03          	addw	sp,#3
8839  002f 81            	ret	
8891                     ; 2294 static void TI4_Config(uint8_t TIM1_ICPolarity,
8891                     ; 2295                        uint8_t TIM1_ICSelection,
8891                     ; 2296                        uint8_t TIM1_ICFilter)
8891                     ; 2297 {
8892                     .text:	section	.text,new
8893  0000               L11_TI4_Config:
8895  0000 89            	pushw	x
8896  0001 88            	push	a
8897       00000001      OFST:	set	1
8900                     ; 2299   TIM1->CCER2 &=  (uint8_t)(~TIM1_CCER2_CC4E);
8902  0002 7219525d      	bres	21085,#4
8903                     ; 2302   TIM1->CCMR4 = (uint8_t)((uint8_t)(TIM1->CCMR4 & (uint8_t)(~(uint8_t)( TIM1_CCMR_CCxS | TIM1_CCMR_ICxF )))
8903                     ; 2303                           | (uint8_t)(( (TIM1_ICSelection)) | ((uint8_t)( TIM1_ICFilter << 4))));
8905  0006 7b06          	ld	a,(OFST+5,sp)
8906  0008 97            	ld	xl,a
8907  0009 a610          	ld	a,#16
8908  000b 42            	mul	x,a
8909  000c 9f            	ld	a,xl
8910  000d 1a03          	or	a,(OFST+2,sp)
8911  000f 6b01          	ld	(OFST+0,sp),a
8913  0011 c6525b        	ld	a,21083
8914  0014 a40c          	and	a,#12
8915  0016 1a01          	or	a,(OFST+0,sp)
8916  0018 c7525b        	ld	21083,a
8917                     ; 2306   if (TIM1_ICPolarity != TIM1_ICPOLARITY_RISING)
8919  001b 7b02          	ld	a,(OFST+1,sp)
8920  001d 2706          	jreq	L1373
8921                     ; 2308     TIM1->CCER2 |= TIM1_CCER2_CC4P;
8923  001f 721a525d      	bset	21085,#5
8925  0023 2004          	jra	L3373
8926  0025               L1373:
8927                     ; 2312     TIM1->CCER2 &= (uint8_t)(~TIM1_CCER2_CC4P);
8929  0025 721b525d      	bres	21085,#5
8930  0029               L3373:
8931                     ; 2316   TIM1->CCER2 |=  TIM1_CCER2_CC4E;
8933  0029 7218525d      	bset	21085,#4
8934                     ; 2317 }
8937  002d 5b03          	addw	sp,#3
8938  002f 81            	ret	
8951                     	xdef	_TIM1_ClearITPendingBit
8952                     	xdef	_TIM1_GetITStatus
8953                     	xdef	_TIM1_ClearFlag
8954                     	xdef	_TIM1_GetFlagStatus
8955                     	xdef	_TIM1_GetPrescaler
8956                     	xdef	_TIM1_GetCounter
8957                     	xdef	_TIM1_GetCapture4
8958                     	xdef	_TIM1_GetCapture3
8959                     	xdef	_TIM1_GetCapture2
8960                     	xdef	_TIM1_GetCapture1
8961                     	xdef	_TIM1_SetIC4Prescaler
8962                     	xdef	_TIM1_SetIC3Prescaler
8963                     	xdef	_TIM1_SetIC2Prescaler
8964                     	xdef	_TIM1_SetIC1Prescaler
8965                     	xdef	_TIM1_SetCompare4
8966                     	xdef	_TIM1_SetCompare3
8967                     	xdef	_TIM1_SetCompare2
8968                     	xdef	_TIM1_SetCompare1
8969                     	xdef	_TIM1_SetAutoreload
8970                     	xdef	_TIM1_SetCounter
8971                     	xdef	_TIM1_SelectOCxM
8972                     	xdef	_TIM1_CCxNCmd
8973                     	xdef	_TIM1_CCxCmd
8974                     	xdef	_TIM1_OC4PolarityConfig
8975                     	xdef	_TIM1_OC3NPolarityConfig
8976                     	xdef	_TIM1_OC3PolarityConfig
8977                     	xdef	_TIM1_OC2NPolarityConfig
8978                     	xdef	_TIM1_OC2PolarityConfig
8979                     	xdef	_TIM1_OC1NPolarityConfig
8980                     	xdef	_TIM1_OC1PolarityConfig
8981                     	xdef	_TIM1_GenerateEvent
8982                     	xdef	_TIM1_OC4FastConfig
8983                     	xdef	_TIM1_OC3FastConfig
8984                     	xdef	_TIM1_OC2FastConfig
8985                     	xdef	_TIM1_OC1FastConfig
8986                     	xdef	_TIM1_OC4PreloadConfig
8987                     	xdef	_TIM1_OC3PreloadConfig
8988                     	xdef	_TIM1_OC2PreloadConfig
8989                     	xdef	_TIM1_OC1PreloadConfig
8990                     	xdef	_TIM1_CCPreloadControl
8991                     	xdef	_TIM1_SelectCOM
8992                     	xdef	_TIM1_ARRPreloadConfig
8993                     	xdef	_TIM1_ForcedOC4Config
8994                     	xdef	_TIM1_ForcedOC3Config
8995                     	xdef	_TIM1_ForcedOC2Config
8996                     	xdef	_TIM1_ForcedOC1Config
8997                     	xdef	_TIM1_CounterModeConfig
8998                     	xdef	_TIM1_PrescalerConfig
8999                     	xdef	_TIM1_EncoderInterfaceConfig
9000                     	xdef	_TIM1_SelectMasterSlaveMode
9001                     	xdef	_TIM1_SelectSlaveMode
9002                     	xdef	_TIM1_SelectOutputTrigger
9003                     	xdef	_TIM1_SelectOnePulseMode
9004                     	xdef	_TIM1_SelectHallSensor
9005                     	xdef	_TIM1_UpdateRequestConfig
9006                     	xdef	_TIM1_UpdateDisableConfig
9007                     	xdef	_TIM1_SelectInputTrigger
9008                     	xdef	_TIM1_TIxExternalClockConfig
9009                     	xdef	_TIM1_ETRConfig
9010                     	xdef	_TIM1_ETRClockMode2Config
9011                     	xdef	_TIM1_ETRClockMode1Config
9012                     	xdef	_TIM1_InternalClockConfig
9013                     	xdef	_TIM1_ITConfig
9014                     	xdef	_TIM1_CtrlPWMOutputs
9015                     	xdef	_TIM1_Cmd
9016                     	xdef	_TIM1_PWMIConfig
9017                     	xdef	_TIM1_ICInit
9018                     	xdef	_TIM1_BDTRConfig
9019                     	xdef	_TIM1_OC4Init
9020                     	xdef	_TIM1_OC3Init
9021                     	xdef	_TIM1_OC2Init
9022                     	xdef	_TIM1_OC1Init
9023                     	xdef	_TIM1_TimeBaseInit
9024                     	xdef	_TIM1_DeInit
9025                     	xref	_assert_failed
9026                     .const:	section	.text
9027  0000               L101:
9028  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
9029  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
9030  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
9031  0036 5f74696d312e  	dc.b	"_tim1.c",0
9051                     	end
