   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  21                     .const:	section	.text
  22  0000               _HSIDivFactor:
  23  0000 01            	dc.b	1
  24  0001 02            	dc.b	2
  25  0002 04            	dc.b	4
  26  0003 08            	dc.b	8
  27  0004               _CLKPrescTable:
  28  0004 01            	dc.b	1
  29  0005 02            	dc.b	2
  30  0006 04            	dc.b	4
  31  0007 08            	dc.b	8
  32  0008 0a            	dc.b	10
  33  0009 10            	dc.b	16
  34  000a 14            	dc.b	20
  35  000b 28            	dc.b	40
  64                     ; 72 void CLK_DeInit(void)
  64                     ; 73 {
  66                     .text:	section	.text,new
  67  0000               _CLK_DeInit:
  71                     ; 74   CLK->ICKR = CLK_ICKR_RESET_VALUE;
  73  0000 350150c0      	mov	20672,#1
  74                     ; 75   CLK->ECKR = CLK_ECKR_RESET_VALUE;
  76  0004 725f50c1      	clr	20673
  77                     ; 76   CLK->SWR  = CLK_SWR_RESET_VALUE;
  79  0008 35e150c4      	mov	20676,#225
  80                     ; 77   CLK->SWCR = CLK_SWCR_RESET_VALUE;
  82  000c 725f50c5      	clr	20677
  83                     ; 78   CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE;
  85  0010 351850c6      	mov	20678,#24
  86                     ; 79   CLK->PCKENR1 = CLK_PCKENR1_RESET_VALUE;
  88  0014 35ff50c7      	mov	20679,#255
  89                     ; 80   CLK->PCKENR2 = CLK_PCKENR2_RESET_VALUE;
  91  0018 35ff50ca      	mov	20682,#255
  92                     ; 81   CLK->CSSR = CLK_CSSR_RESET_VALUE;
  94  001c 725f50c8      	clr	20680
  95                     ; 82   CLK->CCOR = CLK_CCOR_RESET_VALUE;
  97  0020 725f50c9      	clr	20681
  99  0024               L52:
 100                     ; 83   while ((CLK->CCOR & CLK_CCOR_CCOEN)!= 0)
 102  0024 720050c9fb    	btjt	20681,#0,L52
 103                     ; 85   CLK->CCOR = CLK_CCOR_RESET_VALUE;
 105  0029 725f50c9      	clr	20681
 106                     ; 86   CLK->HSITRIMR = CLK_HSITRIMR_RESET_VALUE;
 108  002d 725f50cc      	clr	20684
 109                     ; 87   CLK->SWIMCCR = CLK_SWIMCCR_RESET_VALUE;
 111  0031 725f50cd      	clr	20685
 112                     ; 88 }
 115  0035 81            	ret	
 172                     ; 99 void CLK_FastHaltWakeUpCmd(FunctionalState NewState)
 172                     ; 100 {
 173                     .text:	section	.text,new
 174  0000               _CLK_FastHaltWakeUpCmd:
 176  0000 88            	push	a
 177       00000000      OFST:	set	0
 180                     ; 102   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 182  0001 4d            	tnz	a
 183  0002 2711          	jreq	L41
 184  0004 4a            	dec	a
 185  0005 270e          	jreq	L41
 186  0007 ae0066        	ldw	x,#102
 187  000a 89            	pushw	x
 188  000b 5f            	clrw	x
 189  000c 89            	pushw	x
 190  000d ae000c        	ldw	x,#L75
 191  0010 cd0000        	call	_assert_failed
 193  0013 5b04          	addw	sp,#4
 194  0015               L41:
 195                     ; 104   if (NewState != DISABLE)
 197  0015 7b01          	ld	a,(OFST+1,sp)
 198  0017 2706          	jreq	L16
 199                     ; 107     CLK->ICKR |= CLK_ICKR_FHWU;
 201  0019 721450c0      	bset	20672,#2
 203  001d 2004          	jra	L36
 204  001f               L16:
 205                     ; 112     CLK->ICKR &= (uint8_t)(~CLK_ICKR_FHWU);
 207  001f 721550c0      	bres	20672,#2
 208  0023               L36:
 209                     ; 114 }
 212  0023 84            	pop	a
 213  0024 81            	ret	
 249                     ; 121 void CLK_HSECmd(FunctionalState NewState)
 249                     ; 122 {
 250                     .text:	section	.text,new
 251  0000               _CLK_HSECmd:
 253  0000 88            	push	a
 254       00000000      OFST:	set	0
 257                     ; 124   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 259  0001 4d            	tnz	a
 260  0002 2711          	jreq	L62
 261  0004 4a            	dec	a
 262  0005 270e          	jreq	L62
 263  0007 ae007c        	ldw	x,#124
 264  000a 89            	pushw	x
 265  000b 5f            	clrw	x
 266  000c 89            	pushw	x
 267  000d ae000c        	ldw	x,#L75
 268  0010 cd0000        	call	_assert_failed
 270  0013 5b04          	addw	sp,#4
 271  0015               L62:
 272                     ; 126   if (NewState != DISABLE)
 274  0015 7b01          	ld	a,(OFST+1,sp)
 275  0017 2706          	jreq	L301
 276                     ; 129     CLK->ECKR |= CLK_ECKR_HSEEN;
 278  0019 721050c1      	bset	20673,#0
 280  001d 2004          	jra	L501
 281  001f               L301:
 282                     ; 134     CLK->ECKR &= (uint8_t)(~CLK_ECKR_HSEEN);
 284  001f 721150c1      	bres	20673,#0
 285  0023               L501:
 286                     ; 136 }
 289  0023 84            	pop	a
 290  0024 81            	ret	
 326                     ; 143 void CLK_HSICmd(FunctionalState NewState)
 326                     ; 144 {
 327                     .text:	section	.text,new
 328  0000               _CLK_HSICmd:
 330  0000 88            	push	a
 331       00000000      OFST:	set	0
 334                     ; 146   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 336  0001 4d            	tnz	a
 337  0002 2711          	jreq	L04
 338  0004 4a            	dec	a
 339  0005 270e          	jreq	L04
 340  0007 ae0092        	ldw	x,#146
 341  000a 89            	pushw	x
 342  000b 5f            	clrw	x
 343  000c 89            	pushw	x
 344  000d ae000c        	ldw	x,#L75
 345  0010 cd0000        	call	_assert_failed
 347  0013 5b04          	addw	sp,#4
 348  0015               L04:
 349                     ; 148   if (NewState != DISABLE)
 351  0015 7b01          	ld	a,(OFST+1,sp)
 352  0017 2706          	jreq	L521
 353                     ; 151     CLK->ICKR |= CLK_ICKR_HSIEN;
 355  0019 721050c0      	bset	20672,#0
 357  001d 2004          	jra	L721
 358  001f               L521:
 359                     ; 156     CLK->ICKR &= (uint8_t)(~CLK_ICKR_HSIEN);
 361  001f 721150c0      	bres	20672,#0
 362  0023               L721:
 363                     ; 158 }
 366  0023 84            	pop	a
 367  0024 81            	ret	
 403                     ; 166 void CLK_LSICmd(FunctionalState NewState)
 403                     ; 167 {
 404                     .text:	section	.text,new
 405  0000               _CLK_LSICmd:
 407  0000 88            	push	a
 408       00000000      OFST:	set	0
 411                     ; 169   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 413  0001 4d            	tnz	a
 414  0002 2711          	jreq	L25
 415  0004 4a            	dec	a
 416  0005 270e          	jreq	L25
 417  0007 ae00a9        	ldw	x,#169
 418  000a 89            	pushw	x
 419  000b 5f            	clrw	x
 420  000c 89            	pushw	x
 421  000d ae000c        	ldw	x,#L75
 422  0010 cd0000        	call	_assert_failed
 424  0013 5b04          	addw	sp,#4
 425  0015               L25:
 426                     ; 171   if (NewState != DISABLE)
 428  0015 7b01          	ld	a,(OFST+1,sp)
 429  0017 2706          	jreq	L741
 430                     ; 174     CLK->ICKR |= CLK_ICKR_LSIEN;
 432  0019 721650c0      	bset	20672,#3
 434  001d 2004          	jra	L151
 435  001f               L741:
 436                     ; 179     CLK->ICKR &= (uint8_t)(~CLK_ICKR_LSIEN);
 438  001f 721750c0      	bres	20672,#3
 439  0023               L151:
 440                     ; 181 }
 443  0023 84            	pop	a
 444  0024 81            	ret	
 480                     ; 189 void CLK_CCOCmd(FunctionalState NewState)
 480                     ; 190 {
 481                     .text:	section	.text,new
 482  0000               _CLK_CCOCmd:
 484  0000 88            	push	a
 485       00000000      OFST:	set	0
 488                     ; 192   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 490  0001 4d            	tnz	a
 491  0002 2711          	jreq	L46
 492  0004 4a            	dec	a
 493  0005 270e          	jreq	L46
 494  0007 ae00c0        	ldw	x,#192
 495  000a 89            	pushw	x
 496  000b 5f            	clrw	x
 497  000c 89            	pushw	x
 498  000d ae000c        	ldw	x,#L75
 499  0010 cd0000        	call	_assert_failed
 501  0013 5b04          	addw	sp,#4
 502  0015               L46:
 503                     ; 194   if (NewState != DISABLE)
 505  0015 7b01          	ld	a,(OFST+1,sp)
 506  0017 2706          	jreq	L171
 507                     ; 197     CLK->CCOR |= CLK_CCOR_CCOEN;
 509  0019 721050c9      	bset	20681,#0
 511  001d 2004          	jra	L371
 512  001f               L171:
 513                     ; 202     CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOEN);
 515  001f 721150c9      	bres	20681,#0
 516  0023               L371:
 517                     ; 204 }
 520  0023 84            	pop	a
 521  0024 81            	ret	
 557                     ; 213 void CLK_ClockSwitchCmd(FunctionalState NewState)
 557                     ; 214 {
 558                     .text:	section	.text,new
 559  0000               _CLK_ClockSwitchCmd:
 561  0000 88            	push	a
 562       00000000      OFST:	set	0
 565                     ; 216   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 567  0001 4d            	tnz	a
 568  0002 2711          	jreq	L67
 569  0004 4a            	dec	a
 570  0005 270e          	jreq	L67
 571  0007 ae00d8        	ldw	x,#216
 572  000a 89            	pushw	x
 573  000b 5f            	clrw	x
 574  000c 89            	pushw	x
 575  000d ae000c        	ldw	x,#L75
 576  0010 cd0000        	call	_assert_failed
 578  0013 5b04          	addw	sp,#4
 579  0015               L67:
 580                     ; 218   if (NewState != DISABLE )
 582  0015 7b01          	ld	a,(OFST+1,sp)
 583  0017 2706          	jreq	L312
 584                     ; 221     CLK->SWCR |= CLK_SWCR_SWEN;
 586  0019 721250c5      	bset	20677,#1
 588  001d 2004          	jra	L512
 589  001f               L312:
 590                     ; 226     CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWEN);
 592  001f 721350c5      	bres	20677,#1
 593  0023               L512:
 594                     ; 228 }
 597  0023 84            	pop	a
 598  0024 81            	ret	
 635                     ; 238 void CLK_SlowActiveHaltWakeUpCmd(FunctionalState NewState)
 635                     ; 239 {
 636                     .text:	section	.text,new
 637  0000               _CLK_SlowActiveHaltWakeUpCmd:
 639  0000 88            	push	a
 640       00000000      OFST:	set	0
 643                     ; 241   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 645  0001 4d            	tnz	a
 646  0002 2711          	jreq	L011
 647  0004 4a            	dec	a
 648  0005 270e          	jreq	L011
 649  0007 ae00f1        	ldw	x,#241
 650  000a 89            	pushw	x
 651  000b 5f            	clrw	x
 652  000c 89            	pushw	x
 653  000d ae000c        	ldw	x,#L75
 654  0010 cd0000        	call	_assert_failed
 656  0013 5b04          	addw	sp,#4
 657  0015               L011:
 658                     ; 243   if (NewState != DISABLE)
 660  0015 7b01          	ld	a,(OFST+1,sp)
 661  0017 2706          	jreq	L532
 662                     ; 246     CLK->ICKR |= CLK_ICKR_SWUAH;
 664  0019 721a50c0      	bset	20672,#5
 666  001d 2004          	jra	L732
 667  001f               L532:
 668                     ; 251     CLK->ICKR &= (uint8_t)(~CLK_ICKR_SWUAH);
 670  001f 721b50c0      	bres	20672,#5
 671  0023               L732:
 672                     ; 253 }
 675  0023 84            	pop	a
 676  0024 81            	ret	
 836                     ; 263 void CLK_PeripheralClockConfig(CLK_Peripheral_TypeDef CLK_Peripheral, FunctionalState NewState)
 836                     ; 264 {
 837                     .text:	section	.text,new
 838  0000               _CLK_PeripheralClockConfig:
 840  0000 89            	pushw	x
 841       00000000      OFST:	set	0
 844                     ; 266   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 846  0001 9f            	ld	a,xl
 847  0002 4d            	tnz	a
 848  0003 270a          	jreq	L221
 849  0005 9f            	ld	a,xl
 850  0006 4a            	dec	a
 851  0007 2706          	jreq	L221
 852  0009 ae010a        	ldw	x,#266
 853  000c cd0092        	call	LC004
 854  000f               L221:
 855                     ; 267   assert_param(IS_CLK_PERIPHERAL_OK(CLK_Peripheral));
 857  000f 7b01          	ld	a,(OFST+1,sp)
 858  0011 272f          	jreq	L231
 859  0013 a101          	cp	a,#1
 860  0015 272b          	jreq	L231
 861  0017 a103          	cp	a,#3
 862  0019 2727          	jreq	L231
 863  001b a104          	cp	a,#4
 864  001d 2723          	jreq	L231
 865  001f a105          	cp	a,#5
 866  0021 271f          	jreq	L231
 867  0023 a104          	cp	a,#4
 868  0025 271b          	jreq	L231
 869  0027 a106          	cp	a,#6
 870  0029 2717          	jreq	L231
 871  002b a107          	cp	a,#7
 872  002d 2713          	jreq	L231
 873  002f a117          	cp	a,#23
 874  0031 270f          	jreq	L231
 875  0033 a113          	cp	a,#19
 876  0035 270b          	jreq	L231
 877  0037 a112          	cp	a,#18
 878  0039 2707          	jreq	L231
 879  003b ae010b        	ldw	x,#267
 880  003e ad52          	call	LC004
 881  0040 7b01          	ld	a,(OFST+1,sp)
 882  0042               L231:
 883                     ; 269   if (((uint8_t)CLK_Peripheral & (uint8_t)0x10) == 0x00)
 885  0042 a510          	bcp	a,#16
 886  0044 2622          	jrne	L323
 887                     ; 271     if (NewState != DISABLE)
 889  0046 0d02          	tnz	(OFST+2,sp)
 890  0048 270d          	jreq	L523
 891                     ; 274       CLK->PCKENR1 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
 893  004a ad3e          	call	LC003
 894  004c 2704          	jreq	L631
 895  004e               L041:
 896  004e 48            	sll	a
 897  004f 5a            	decw	x
 898  0050 26fc          	jrne	L041
 899  0052               L631:
 900  0052 ca50c7        	or	a,20679
 902  0055 200c          	jp	LC002
 903  0057               L523:
 904                     ; 279       CLK->PCKENR1 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
 906  0057 ad31          	call	LC003
 907  0059 2704          	jreq	L241
 908  005b               L441:
 909  005b 48            	sll	a
 910  005c 5a            	decw	x
 911  005d 26fc          	jrne	L441
 912  005f               L241:
 913  005f 43            	cpl	a
 914  0060 c450c7        	and	a,20679
 915  0063               LC002:
 916  0063 c750c7        	ld	20679,a
 917  0066 2020          	jra	L133
 918  0068               L323:
 919                     ; 284     if (NewState != DISABLE)
 921  0068 0d02          	tnz	(OFST+2,sp)
 922  006a 270d          	jreq	L333
 923                     ; 287       CLK->PCKENR2 |= (uint8_t)((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F));
 925  006c ad1c          	call	LC003
 926  006e 2704          	jreq	L641
 927  0070               L051:
 928  0070 48            	sll	a
 929  0071 5a            	decw	x
 930  0072 26fc          	jrne	L051
 931  0074               L641:
 932  0074 ca50ca        	or	a,20682
 934  0077 200c          	jp	LC001
 935  0079               L333:
 936                     ; 292       CLK->PCKENR2 &= (uint8_t)(~(uint8_t)(((uint8_t)1 << ((uint8_t)CLK_Peripheral & (uint8_t)0x0F))));
 938  0079 ad0f          	call	LC003
 939  007b 2704          	jreq	L251
 940  007d               L451:
 941  007d 48            	sll	a
 942  007e 5a            	decw	x
 943  007f 26fc          	jrne	L451
 944  0081               L251:
 945  0081 43            	cpl	a
 946  0082 c450ca        	and	a,20682
 947  0085               LC001:
 948  0085 c750ca        	ld	20682,a
 949  0088               L133:
 950                     ; 295 }
 953  0088 85            	popw	x
 954  0089 81            	ret	
 955  008a               LC003:
 956  008a a40f          	and	a,#15
 957  008c 5f            	clrw	x
 958  008d 97            	ld	xl,a
 959  008e a601          	ld	a,#1
 960  0090 5d            	tnzw	x
 961  0091 81            	ret	
 962  0092               LC004:
 963  0092 89            	pushw	x
 964  0093 5f            	clrw	x
 965  0094 89            	pushw	x
 966  0095 ae000c        	ldw	x,#L75
 967  0098 cd0000        	call	_assert_failed
 969  009b 5b04          	addw	sp,#4
 970  009d 81            	ret	
1159                     ; 309 ErrorStatus CLK_ClockSwitchConfig(CLK_SwitchMode_TypeDef CLK_SwitchMode, CLK_Source_TypeDef CLK_NewClock, FunctionalState ITState, CLK_CurrentClockState_TypeDef CLK_CurrentClockState)
1159                     ; 310 {
1160                     .text:	section	.text,new
1161  0000               _CLK_ClockSwitchConfig:
1163  0000 89            	pushw	x
1164  0001 5204          	subw	sp,#4
1165       00000004      OFST:	set	4
1168                     ; 312   uint16_t DownCounter = CLK_TIMEOUT;
1170  0003 aeffff        	ldw	x,#65535
1171  0006 1f03          	ldw	(OFST-1,sp),x
1173                     ; 313   ErrorStatus Swif = ERROR;
1175                     ; 316   assert_param(IS_CLK_SOURCE_OK(CLK_NewClock));
1177  0008 7b06          	ld	a,(OFST+2,sp)
1178  000a a1e1          	cp	a,#225
1179  000c 270e          	jreq	L461
1180  000e a1d2          	cp	a,#210
1181  0010 270a          	jreq	L461
1182  0012 a1b4          	cp	a,#180
1183  0014 2706          	jreq	L461
1184  0016 ae013c        	ldw	x,#316
1185  0019 cd00dc        	call	LC007
1186  001c               L461:
1187                     ; 317   assert_param(IS_CLK_SWITCHMODE_OK(CLK_SwitchMode));
1189  001c 7b05          	ld	a,(OFST+1,sp)
1190  001e 2709          	jreq	L471
1191  0020 4a            	dec	a
1192  0021 2706          	jreq	L471
1193  0023 ae013d        	ldw	x,#317
1194  0026 cd00dc        	call	LC007
1195  0029               L471:
1196                     ; 318   assert_param(IS_FUNCTIONALSTATE_OK(ITState));
1198  0029 7b09          	ld	a,(OFST+5,sp)
1199  002b 2709          	jreq	L402
1200  002d 4a            	dec	a
1201  002e 2706          	jreq	L402
1202  0030 ae013e        	ldw	x,#318
1203  0033 cd00dc        	call	LC007
1204  0036               L402:
1205                     ; 319   assert_param(IS_CLK_CURRENTCLOCKSTATE_OK(CLK_CurrentClockState));
1207  0036 7b0a          	ld	a,(OFST+6,sp)
1208  0038 2709          	jreq	L412
1209  003a 4a            	dec	a
1210  003b 2706          	jreq	L412
1211  003d ae013f        	ldw	x,#319
1212  0040 cd00dc        	call	LC007
1213  0043               L412:
1214                     ; 322   clock_master = (CLK_Source_TypeDef)CLK->CMSR;
1216  0043 c650c3        	ld	a,20675
1217  0046 6b01          	ld	(OFST-3,sp),a
1219                     ; 325   if (CLK_SwitchMode == CLK_SWITCHMODE_AUTO)
1221  0048 7b05          	ld	a,(OFST+1,sp)
1222  004a 4a            	dec	a
1223  004b 263d          	jrne	L744
1224                     ; 328     CLK->SWCR |= CLK_SWCR_SWEN;
1226  004d 721250c5      	bset	20677,#1
1227                     ; 331     if (ITState != DISABLE)
1229  0051 7b09          	ld	a,(OFST+5,sp)
1230  0053 2706          	jreq	L154
1231                     ; 333       CLK->SWCR |= CLK_SWCR_SWIEN;
1233  0055 721450c5      	bset	20677,#2
1235  0059 2004          	jra	L354
1236  005b               L154:
1237                     ; 337       CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWIEN);
1239  005b 721550c5      	bres	20677,#2
1240  005f               L354:
1241                     ; 341     CLK->SWR = (uint8_t)CLK_NewClock;
1243  005f 7b06          	ld	a,(OFST+2,sp)
1244  0061 c750c4        	ld	20676,a
1246  0064 2003          	jra	L164
1247  0066               L554:
1248                     ; 346       DownCounter--;
1250  0066 5a            	decw	x
1251  0067 1f03          	ldw	(OFST-1,sp),x
1253  0069               L164:
1254                     ; 344     while((((CLK->SWCR & CLK_SWCR_SWBSY) != 0 )&& (DownCounter != 0)))
1256  0069 720150c504    	btjf	20677,#0,L564
1258  006e 1e03          	ldw	x,(OFST-1,sp)
1259  0070 26f4          	jrne	L554
1260  0072               L564:
1261                     ; 349     if(DownCounter != 0)
1263  0072 1e03          	ldw	x,(OFST-1,sp)
1264                     ; 351       Swif = SUCCESS;
1266  0074 263d          	jrne	LC006
1267  0076               L764:
1268                     ; 355       Swif = ERROR;
1271  0076 0f02          	clr	(OFST-2,sp)
1273  0078               L374:
1274                     ; 390   if(Swif != ERROR)
1276  0078 275d          	jreq	L715
1277                     ; 393     if((CLK_CurrentClockState == CLK_CURRENTCLOCKSTATE_DISABLE) && ( clock_master == CLK_SOURCE_HSI))
1279  007a 7b0a          	ld	a,(OFST+6,sp)
1280  007c 263b          	jrne	L125
1282  007e 7b01          	ld	a,(OFST-3,sp)
1283  0080 a1e1          	cp	a,#225
1284  0082 2635          	jrne	L125
1285                     ; 395       CLK->ICKR &= (uint8_t)(~CLK_ICKR_HSIEN);
1287  0084 721150c0      	bres	20672,#0
1289  0088 204d          	jra	L715
1290  008a               L744:
1291                     ; 361     if (ITState != DISABLE)
1293  008a 7b09          	ld	a,(OFST+5,sp)
1294  008c 2706          	jreq	L574
1295                     ; 363       CLK->SWCR |= CLK_SWCR_SWIEN;
1297  008e 721450c5      	bset	20677,#2
1299  0092 2004          	jra	L774
1300  0094               L574:
1301                     ; 367       CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWIEN);
1303  0094 721550c5      	bres	20677,#2
1304  0098               L774:
1305                     ; 371     CLK->SWR = (uint8_t)CLK_NewClock;
1307  0098 7b06          	ld	a,(OFST+2,sp)
1308  009a c750c4        	ld	20676,a
1310  009d 2003          	jra	L505
1311  009f               L105:
1312                     ; 376       DownCounter--;
1314  009f 5a            	decw	x
1315  00a0 1f03          	ldw	(OFST-1,sp),x
1317  00a2               L505:
1318                     ; 374     while((((CLK->SWCR & CLK_SWCR_SWIF) != 0 ) && (DownCounter != 0)))
1320  00a2 720750c504    	btjf	20677,#3,L115
1322  00a7 1e03          	ldw	x,(OFST-1,sp)
1323  00a9 26f4          	jrne	L105
1324  00ab               L115:
1325                     ; 379     if(DownCounter != 0)
1327  00ab 1e03          	ldw	x,(OFST-1,sp)
1328  00ad 27c7          	jreq	L764
1329                     ; 382       CLK->SWCR |= CLK_SWCR_SWEN;
1331  00af 721250c5      	bset	20677,#1
1332                     ; 383       Swif = SUCCESS;
1334  00b3               LC006:
1336  00b3 a601          	ld	a,#1
1337  00b5 6b02          	ld	(OFST-2,sp),a
1340  00b7 20bf          	jra	L374
1341                     ; 387       Swif = ERROR;
1342  00b9               L125:
1343                     ; 397     else if((CLK_CurrentClockState == CLK_CURRENTCLOCKSTATE_DISABLE) && ( clock_master == CLK_SOURCE_LSI))
1345  00b9 7b0a          	ld	a,(OFST+6,sp)
1346  00bb 260c          	jrne	L525
1348  00bd 7b01          	ld	a,(OFST-3,sp)
1349  00bf a1d2          	cp	a,#210
1350  00c1 2606          	jrne	L525
1351                     ; 399       CLK->ICKR &= (uint8_t)(~CLK_ICKR_LSIEN);
1353  00c3 721750c0      	bres	20672,#3
1355  00c7 200e          	jra	L715
1356  00c9               L525:
1357                     ; 401     else if ((CLK_CurrentClockState == CLK_CURRENTCLOCKSTATE_DISABLE) && ( clock_master == CLK_SOURCE_HSE))
1359  00c9 7b0a          	ld	a,(OFST+6,sp)
1360  00cb 260a          	jrne	L715
1362  00cd 7b01          	ld	a,(OFST-3,sp)
1363  00cf a1b4          	cp	a,#180
1364  00d1 2604          	jrne	L715
1365                     ; 403       CLK->ECKR &= (uint8_t)(~CLK_ECKR_HSEEN);
1367  00d3 721150c1      	bres	20673,#0
1368  00d7               L715:
1369                     ; 406   return(Swif);
1371  00d7 7b02          	ld	a,(OFST-2,sp)
1374  00d9 5b06          	addw	sp,#6
1375  00db 81            	ret	
1376  00dc               LC007:
1377  00dc 89            	pushw	x
1378  00dd 5f            	clrw	x
1379  00de 89            	pushw	x
1380  00df ae000c        	ldw	x,#L75
1381  00e2 cd0000        	call	_assert_failed
1383  00e5 5b04          	addw	sp,#4
1384  00e7 81            	ret	
1523                     ; 415 void CLK_HSIPrescalerConfig(CLK_Prescaler_TypeDef HSIPrescaler)
1523                     ; 416 {
1524                     .text:	section	.text,new
1525  0000               _CLK_HSIPrescalerConfig:
1527  0000 88            	push	a
1528       00000000      OFST:	set	0
1531                     ; 418   assert_param(IS_CLK_HSIPRESCALER_OK(HSIPrescaler));
1533  0001 4d            	tnz	a
1534  0002 271a          	jreq	L622
1535  0004 a108          	cp	a,#8
1536  0006 2716          	jreq	L622
1537  0008 a110          	cp	a,#16
1538  000a 2712          	jreq	L622
1539  000c a118          	cp	a,#24
1540  000e 270e          	jreq	L622
1541  0010 ae01a2        	ldw	x,#418
1542  0013 89            	pushw	x
1543  0014 5f            	clrw	x
1544  0015 89            	pushw	x
1545  0016 ae000c        	ldw	x,#L75
1546  0019 cd0000        	call	_assert_failed
1548  001c 5b04          	addw	sp,#4
1549  001e               L622:
1550                     ; 421   CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
1552  001e c650c6        	ld	a,20678
1553  0021 a4e7          	and	a,#231
1554  0023 c750c6        	ld	20678,a
1555                     ; 424   CLK->CKDIVR |= (uint8_t)HSIPrescaler;
1557  0026 c650c6        	ld	a,20678
1558  0029 1a01          	or	a,(OFST+1,sp)
1559  002b c750c6        	ld	20678,a
1560                     ; 425 }
1563  002e 84            	pop	a
1564  002f 81            	ret	
1700                     ; 436 void CLK_CCOConfig(CLK_Output_TypeDef CLK_CCO)
1700                     ; 437 {
1701                     .text:	section	.text,new
1702  0000               _CLK_CCOConfig:
1704  0000 88            	push	a
1705       00000000      OFST:	set	0
1708                     ; 439   assert_param(IS_CLK_OUTPUT_OK(CLK_CCO));
1710  0001 4d            	tnz	a
1711  0002 273e          	jreq	L042
1712  0004 a104          	cp	a,#4
1713  0006 273a          	jreq	L042
1714  0008 a102          	cp	a,#2
1715  000a 2736          	jreq	L042
1716  000c a108          	cp	a,#8
1717  000e 2732          	jreq	L042
1718  0010 a10a          	cp	a,#10
1719  0012 272e          	jreq	L042
1720  0014 a10c          	cp	a,#12
1721  0016 272a          	jreq	L042
1722  0018 a10e          	cp	a,#14
1723  001a 2726          	jreq	L042
1724  001c a110          	cp	a,#16
1725  001e 2722          	jreq	L042
1726  0020 a112          	cp	a,#18
1727  0022 271e          	jreq	L042
1728  0024 a114          	cp	a,#20
1729  0026 271a          	jreq	L042
1730  0028 a116          	cp	a,#22
1731  002a 2716          	jreq	L042
1732  002c a118          	cp	a,#24
1733  002e 2712          	jreq	L042
1734  0030 a11a          	cp	a,#26
1735  0032 270e          	jreq	L042
1736  0034 ae01b7        	ldw	x,#439
1737  0037 89            	pushw	x
1738  0038 5f            	clrw	x
1739  0039 89            	pushw	x
1740  003a ae000c        	ldw	x,#L75
1741  003d cd0000        	call	_assert_failed
1743  0040 5b04          	addw	sp,#4
1744  0042               L042:
1745                     ; 442   CLK->CCOR &= (uint8_t)(~CLK_CCOR_CCOSEL);
1747  0042 c650c9        	ld	a,20681
1748  0045 a4e1          	and	a,#225
1749  0047 c750c9        	ld	20681,a
1750                     ; 445   CLK->CCOR |= (uint8_t)CLK_CCO;
1752  004a c650c9        	ld	a,20681
1753  004d 1a01          	or	a,(OFST+1,sp)
1754  004f c750c9        	ld	20681,a
1755                     ; 448   CLK->CCOR |= CLK_CCOR_CCOEN;
1757  0052 721050c9      	bset	20681,#0
1758                     ; 449 }
1761  0056 84            	pop	a
1762  0057 81            	ret	
1828                     ; 459 void CLK_ITConfig(CLK_IT_TypeDef CLK_IT, FunctionalState NewState)
1828                     ; 460 {
1829                     .text:	section	.text,new
1830  0000               _CLK_ITConfig:
1832  0000 89            	pushw	x
1833       00000000      OFST:	set	0
1836                     ; 462   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1838  0001 9f            	ld	a,xl
1839  0002 4d            	tnz	a
1840  0003 2709          	jreq	L252
1841  0005 9f            	ld	a,xl
1842  0006 4a            	dec	a
1843  0007 2705          	jreq	L252
1844  0009 ae01ce        	ldw	x,#462
1845  000c ad3f          	call	LC008
1846  000e               L252:
1847                     ; 463   assert_param(IS_CLK_IT_OK(CLK_IT));
1849  000e 7b01          	ld	a,(OFST+1,sp)
1850  0010 a10c          	cp	a,#12
1851  0012 2709          	jreq	L262
1852  0014 a11c          	cp	a,#28
1853  0016 2705          	jreq	L262
1854  0018 ae01cf        	ldw	x,#463
1855  001b ad30          	call	LC008
1856  001d               L262:
1857                     ; 465   if (NewState != DISABLE)
1859  001d 7b02          	ld	a,(OFST+2,sp)
1860  001f 2716          	jreq	L727
1861                     ; 467     switch (CLK_IT)
1863  0021 7b01          	ld	a,(OFST+1,sp)
1865                     ; 475     default:
1865                     ; 476       break;
1866  0023 a00c          	sub	a,#12
1867  0025 270a          	jreq	L366
1868  0027 a010          	sub	a,#16
1869  0029 2620          	jrne	L537
1870                     ; 469     case CLK_IT_SWIF: /* Enable the clock switch interrupt */
1870                     ; 470       CLK->SWCR |= CLK_SWCR_SWIEN;
1872  002b 721450c5      	bset	20677,#2
1873                     ; 471       break;
1875  002f 201a          	jra	L537
1876  0031               L366:
1877                     ; 472     case CLK_IT_CSSD: /* Enable the clock security system detection interrupt */
1877                     ; 473       CLK->CSSR |= CLK_CSSR_CSSDIE;
1879  0031 721450c8      	bset	20680,#2
1880                     ; 474       break;
1882  0035 2014          	jra	L537
1883                     ; 475     default:
1883                     ; 476       break;
1886  0037               L727:
1887                     ; 481     switch (CLK_IT)
1889  0037 7b01          	ld	a,(OFST+1,sp)
1891                     ; 489     default:
1891                     ; 490       break;
1892  0039 a00c          	sub	a,#12
1893  003b 270a          	jreq	L176
1894  003d a010          	sub	a,#16
1895  003f 260a          	jrne	L537
1896                     ; 483     case CLK_IT_SWIF: /* Disable the clock switch interrupt */
1896                     ; 484       CLK->SWCR  &= (uint8_t)(~CLK_SWCR_SWIEN);
1898  0041 721550c5      	bres	20677,#2
1899                     ; 485       break;
1901  0045 2004          	jra	L537
1902  0047               L176:
1903                     ; 486     case CLK_IT_CSSD: /* Disable the clock security system detection interrupt */
1903                     ; 487       CLK->CSSR &= (uint8_t)(~CLK_CSSR_CSSDIE);
1905  0047 721550c8      	bres	20680,#2
1906                     ; 488       break;
1907  004b               L537:
1908                     ; 493 }
1911  004b 85            	popw	x
1912  004c 81            	ret	
1913                     ; 489     default:
1913                     ; 490       break;
1915  004d               LC008:
1916  004d 89            	pushw	x
1917  004e 5f            	clrw	x
1918  004f 89            	pushw	x
1919  0050 ae000c        	ldw	x,#L75
1920  0053 cd0000        	call	_assert_failed
1922  0056 5b04          	addw	sp,#4
1923  0058 81            	ret	
1959                     ; 500 void CLK_SYSCLKConfig(CLK_Prescaler_TypeDef CLK_Prescaler)
1959                     ; 501 {
1960                     .text:	section	.text,new
1961  0000               _CLK_SYSCLKConfig:
1963  0000 88            	push	a
1964       00000000      OFST:	set	0
1967                     ; 503   assert_param(IS_CLK_PRESCALER_OK(CLK_Prescaler));
1969  0001 4d            	tnz	a
1970  0002 273a          	jreq	L472
1971  0004 a108          	cp	a,#8
1972  0006 2736          	jreq	L472
1973  0008 a110          	cp	a,#16
1974  000a 2732          	jreq	L472
1975  000c a118          	cp	a,#24
1976  000e 272e          	jreq	L472
1977  0010 a180          	cp	a,#128
1978  0012 272a          	jreq	L472
1979  0014 a181          	cp	a,#129
1980  0016 2726          	jreq	L472
1981  0018 a182          	cp	a,#130
1982  001a 2722          	jreq	L472
1983  001c a183          	cp	a,#131
1984  001e 271e          	jreq	L472
1985  0020 a184          	cp	a,#132
1986  0022 271a          	jreq	L472
1987  0024 a185          	cp	a,#133
1988  0026 2716          	jreq	L472
1989  0028 a186          	cp	a,#134
1990  002a 2712          	jreq	L472
1991  002c a187          	cp	a,#135
1992  002e 270e          	jreq	L472
1993  0030 ae01f7        	ldw	x,#503
1994  0033 89            	pushw	x
1995  0034 5f            	clrw	x
1996  0035 89            	pushw	x
1997  0036 ae000c        	ldw	x,#L75
1998  0039 cd0000        	call	_assert_failed
2000  003c 5b04          	addw	sp,#4
2001  003e               L472:
2002                     ; 505   if (((uint8_t)CLK_Prescaler & (uint8_t)0x80) == 0x00) /* Bit7 = 0 means HSI divider */
2004  003e 7b01          	ld	a,(OFST+1,sp)
2005  0040 2b0e          	jrmi	L167
2006                     ; 507     CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
2008  0042 c650c6        	ld	a,20678
2009  0045 a4e7          	and	a,#231
2010  0047 c750c6        	ld	20678,a
2011                     ; 508     CLK->CKDIVR |= (uint8_t)((uint8_t)CLK_Prescaler & (uint8_t)CLK_CKDIVR_HSIDIV);
2013  004a 7b01          	ld	a,(OFST+1,sp)
2014  004c a418          	and	a,#24
2016  004e 200c          	jra	L367
2017  0050               L167:
2018                     ; 512     CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_CPUDIV);
2020  0050 c650c6        	ld	a,20678
2021  0053 a4f8          	and	a,#248
2022  0055 c750c6        	ld	20678,a
2023                     ; 513     CLK->CKDIVR |= (uint8_t)((uint8_t)CLK_Prescaler & (uint8_t)CLK_CKDIVR_CPUDIV);
2025  0058 7b01          	ld	a,(OFST+1,sp)
2026  005a a407          	and	a,#7
2027  005c               L367:
2028  005c ca50c6        	or	a,20678
2029  005f c750c6        	ld	20678,a
2030                     ; 515 }
2033  0062 84            	pop	a
2034  0063 81            	ret	
2091                     ; 523 void CLK_SWIMConfig(CLK_SWIMDivider_TypeDef CLK_SWIMDivider)
2091                     ; 524 {
2092                     .text:	section	.text,new
2093  0000               _CLK_SWIMConfig:
2095  0000 88            	push	a
2096       00000000      OFST:	set	0
2099                     ; 526   assert_param(IS_CLK_SWIMDIVIDER_OK(CLK_SWIMDivider));
2101  0001 4d            	tnz	a
2102  0002 2711          	jreq	L603
2103  0004 4a            	dec	a
2104  0005 270e          	jreq	L603
2105  0007 ae020e        	ldw	x,#526
2106  000a 89            	pushw	x
2107  000b 5f            	clrw	x
2108  000c 89            	pushw	x
2109  000d ae000c        	ldw	x,#L75
2110  0010 cd0000        	call	_assert_failed
2112  0013 5b04          	addw	sp,#4
2113  0015               L603:
2114                     ; 528   if (CLK_SWIMDivider != CLK_SWIMDIVIDER_2)
2116  0015 7b01          	ld	a,(OFST+1,sp)
2117  0017 2706          	jreq	L3101
2118                     ; 531     CLK->SWIMCCR |= CLK_SWIMCCR_SWIMDIV;
2120  0019 721050cd      	bset	20685,#0
2122  001d 2004          	jra	L5101
2123  001f               L3101:
2124                     ; 536     CLK->SWIMCCR &= (uint8_t)(~CLK_SWIMCCR_SWIMDIV);
2126  001f 721150cd      	bres	20685,#0
2127  0023               L5101:
2128                     ; 538 }
2131  0023 84            	pop	a
2132  0024 81            	ret	
2156                     ; 547 void CLK_ClockSecuritySystemEnable(void)
2156                     ; 548 {
2157                     .text:	section	.text,new
2158  0000               _CLK_ClockSecuritySystemEnable:
2162                     ; 550   CLK->CSSR |= CLK_CSSR_CSSEN;
2164  0000 721050c8      	bset	20680,#0
2165                     ; 551 }
2168  0004 81            	ret	
2193                     ; 559 CLK_Source_TypeDef CLK_GetSYSCLKSource(void)
2193                     ; 560 {
2194                     .text:	section	.text,new
2195  0000               _CLK_GetSYSCLKSource:
2199                     ; 561   return((CLK_Source_TypeDef)CLK->CMSR);
2201  0000 c650c3        	ld	a,20675
2204  0003 81            	ret	
2267                     ; 569 uint32_t CLK_GetClockFreq(void)
2267                     ; 570 {
2268                     .text:	section	.text,new
2269  0000               _CLK_GetClockFreq:
2271  0000 5209          	subw	sp,#9
2272       00000009      OFST:	set	9
2275                     ; 571   uint32_t clockfrequency = 0;
2277                     ; 572   CLK_Source_TypeDef clocksource = CLK_SOURCE_HSI;
2279                     ; 573   uint8_t tmp = 0, presc = 0;
2283                     ; 576   clocksource = (CLK_Source_TypeDef)CLK->CMSR;
2285  0002 c650c3        	ld	a,20675
2286  0005 6b09          	ld	(OFST+0,sp),a
2288                     ; 578   if (clocksource == CLK_SOURCE_HSI)
2290  0007 a1e1          	cp	a,#225
2291  0009 2634          	jrne	L1701
2292                     ; 580     tmp = (uint8_t)(CLK->CKDIVR & CLK_CKDIVR_HSIDIV);
2294  000b c650c6        	ld	a,20678
2295  000e a418          	and	a,#24
2296  0010 44            	srl	a
2297  0011 44            	srl	a
2298  0012 44            	srl	a
2300                     ; 581     tmp = (uint8_t)(tmp >> 3);
2303                     ; 582     presc = HSIDivFactor[tmp];
2305  0013 5f            	clrw	x
2306  0014 97            	ld	xl,a
2307  0015 d60000        	ld	a,(_HSIDivFactor,x)
2308  0018 6b09          	ld	(OFST+0,sp),a
2310                     ; 583     clockfrequency = HSI_VALUE / presc;
2312  001a b703          	ld	c_lreg+3,a
2313  001c 3f02          	clr	c_lreg+2
2314  001e 3f01          	clr	c_lreg+1
2315  0020 3f00          	clr	c_lreg
2316  0022 96            	ldw	x,sp
2317  0023 5c            	incw	x
2318  0024 cd0000        	call	c_rtol
2321  0027 ae2400        	ldw	x,#9216
2322  002a bf02          	ldw	c_lreg+2,x
2323  002c ae00f4        	ldw	x,#244
2324  002f bf00          	ldw	c_lreg,x
2325  0031 96            	ldw	x,sp
2326  0032 5c            	incw	x
2327  0033 cd0000        	call	c_ludv
2329  0036 96            	ldw	x,sp
2330  0037 1c0005        	addw	x,#OFST-4
2331  003a cd0000        	call	c_rtol
2335  003d 2018          	jra	L3701
2336  003f               L1701:
2337                     ; 585   else if ( clocksource == CLK_SOURCE_LSI)
2339  003f a1d2          	cp	a,#210
2340  0041 260a          	jrne	L5701
2341                     ; 587     clockfrequency = LSI_VALUE;
2343  0043 aef400        	ldw	x,#62464
2344  0046 1f07          	ldw	(OFST-2,sp),x
2345  0048 ae0001        	ldw	x,#1
2347  004b 2008          	jp	LC009
2348  004d               L5701:
2349                     ; 591     clockfrequency = HSE_VALUE;
2351  004d ae2400        	ldw	x,#9216
2352  0050 1f07          	ldw	(OFST-2,sp),x
2353  0052 ae00f4        	ldw	x,#244
2354  0055               LC009:
2355  0055 1f05          	ldw	(OFST-4,sp),x
2357  0057               L3701:
2358                     ; 594   return((uint32_t)clockfrequency);
2360  0057 96            	ldw	x,sp
2361  0058 1c0005        	addw	x,#OFST-4
2362  005b cd0000        	call	c_ltor
2366  005e 5b09          	addw	sp,#9
2367  0060 81            	ret	
2467                     ; 604 void CLK_AdjustHSICalibrationValue(CLK_HSITrimValue_TypeDef CLK_HSICalibrationValue)
2467                     ; 605 {
2468                     .text:	section	.text,new
2469  0000               _CLK_AdjustHSICalibrationValue:
2471  0000 88            	push	a
2472       00000000      OFST:	set	0
2475                     ; 607   assert_param(IS_CLK_HSITRIMVALUE_OK(CLK_HSICalibrationValue));
2477  0001 4d            	tnz	a
2478  0002 272a          	jreq	L623
2479  0004 a101          	cp	a,#1
2480  0006 2726          	jreq	L623
2481  0008 a102          	cp	a,#2
2482  000a 2722          	jreq	L623
2483  000c a103          	cp	a,#3
2484  000e 271e          	jreq	L623
2485  0010 a104          	cp	a,#4
2486  0012 271a          	jreq	L623
2487  0014 a105          	cp	a,#5
2488  0016 2716          	jreq	L623
2489  0018 a106          	cp	a,#6
2490  001a 2712          	jreq	L623
2491  001c a107          	cp	a,#7
2492  001e 270e          	jreq	L623
2493  0020 ae025f        	ldw	x,#607
2494  0023 89            	pushw	x
2495  0024 5f            	clrw	x
2496  0025 89            	pushw	x
2497  0026 ae000c        	ldw	x,#L75
2498  0029 cd0000        	call	_assert_failed
2500  002c 5b04          	addw	sp,#4
2501  002e               L623:
2502                     ; 610   CLK->HSITRIMR = (uint8_t)( (uint8_t)(CLK->HSITRIMR & (uint8_t)(~CLK_HSITRIMR_HSITRIM))|((uint8_t)CLK_HSICalibrationValue));
2504  002e c650cc        	ld	a,20684
2505  0031 a4f8          	and	a,#248
2506  0033 1a01          	or	a,(OFST+1,sp)
2507  0035 c750cc        	ld	20684,a
2508                     ; 611 }
2511  0038 84            	pop	a
2512  0039 81            	ret	
2536                     ; 622 void CLK_SYSCLKEmergencyClear(void)
2536                     ; 623 {
2537                     .text:	section	.text,new
2538  0000               _CLK_SYSCLKEmergencyClear:
2542                     ; 624   CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWBSY);
2544  0000 721150c5      	bres	20677,#0
2545                     ; 625 }
2548  0004 81            	ret	
2702                     ; 634 FlagStatus CLK_GetFlagStatus(CLK_Flag_TypeDef CLK_FLAG)
2702                     ; 635 {
2703                     .text:	section	.text,new
2704  0000               _CLK_GetFlagStatus:
2706  0000 89            	pushw	x
2707  0001 5203          	subw	sp,#3
2708       00000003      OFST:	set	3
2711                     ; 636   uint16_t statusreg = 0;
2713                     ; 637   uint8_t tmpreg = 0;
2715                     ; 638   FlagStatus bitstatus = RESET;
2717                     ; 641   assert_param(IS_CLK_FLAG_OK(CLK_FLAG));
2719  0003 a30110        	cpw	x,#272
2720  0006 2736          	jreq	L243
2721  0008 a30102        	cpw	x,#258
2722  000b 2731          	jreq	L243
2723  000d a30202        	cpw	x,#514
2724  0010 272c          	jreq	L243
2725  0012 a30308        	cpw	x,#776
2726  0015 2727          	jreq	L243
2727  0017 a30301        	cpw	x,#769
2728  001a 2722          	jreq	L243
2729  001c a30408        	cpw	x,#1032
2730  001f 271d          	jreq	L243
2731  0021 a30402        	cpw	x,#1026
2732  0024 2718          	jreq	L243
2733  0026 a30504        	cpw	x,#1284
2734  0029 2713          	jreq	L243
2735  002b a30502        	cpw	x,#1282
2736  002e 270e          	jreq	L243
2737  0030 ae0281        	ldw	x,#641
2738  0033 89            	pushw	x
2739  0034 5f            	clrw	x
2740  0035 89            	pushw	x
2741  0036 ae000c        	ldw	x,#L75
2742  0039 cd0000        	call	_assert_failed
2744  003c 5b04          	addw	sp,#4
2745  003e               L243:
2746                     ; 644   statusreg = (uint16_t)((uint16_t)CLK_FLAG & (uint16_t)0xFF00);
2748  003e 7b04          	ld	a,(OFST+1,sp)
2749  0040 97            	ld	xl,a
2750  0041 4f            	clr	a
2751  0042 02            	rlwa	x,a
2752  0043 1f01          	ldw	(OFST-2,sp),x
2754                     ; 647   if (statusreg == 0x0100) /* The flag to check is in ICKRregister */
2756  0045 a30100        	cpw	x,#256
2757  0048 2605          	jrne	L3421
2758                     ; 649     tmpreg = CLK->ICKR;
2760  004a c650c0        	ld	a,20672
2762  004d 2021          	jra	L5421
2763  004f               L3421:
2764                     ; 651   else if (statusreg == 0x0200) /* The flag to check is in ECKRregister */
2766  004f a30200        	cpw	x,#512
2767  0052 2605          	jrne	L7421
2768                     ; 653     tmpreg = CLK->ECKR;
2770  0054 c650c1        	ld	a,20673
2772  0057 2017          	jra	L5421
2773  0059               L7421:
2774                     ; 655   else if (statusreg == 0x0300) /* The flag to check is in SWIC register */
2776  0059 a30300        	cpw	x,#768
2777  005c 2605          	jrne	L3521
2778                     ; 657     tmpreg = CLK->SWCR;
2780  005e c650c5        	ld	a,20677
2782  0061 200d          	jra	L5421
2783  0063               L3521:
2784                     ; 659   else if (statusreg == 0x0400) /* The flag to check is in CSS register */
2786  0063 a30400        	cpw	x,#1024
2787  0066 2605          	jrne	L7521
2788                     ; 661     tmpreg = CLK->CSSR;
2790  0068 c650c8        	ld	a,20680
2792  006b 2003          	jra	L5421
2793  006d               L7521:
2794                     ; 665     tmpreg = CLK->CCOR;
2796  006d c650c9        	ld	a,20681
2797  0070               L5421:
2798  0070 6b03          	ld	(OFST+0,sp),a
2800                     ; 668   if ((tmpreg & (uint8_t)CLK_FLAG) != (uint8_t)RESET)
2802  0072 7b05          	ld	a,(OFST+2,sp)
2803  0074 1503          	bcp	a,(OFST+0,sp)
2804  0076 2704          	jreq	L3621
2805                     ; 670     bitstatus = SET;
2807  0078 a601          	ld	a,#1
2810  007a 2001          	jra	L5621
2811  007c               L3621:
2812                     ; 674     bitstatus = RESET;
2814  007c 4f            	clr	a
2816  007d               L5621:
2817                     ; 678   return((FlagStatus)bitstatus);
2821  007d 5b05          	addw	sp,#5
2822  007f 81            	ret	
2869                     ; 687 ITStatus CLK_GetITStatus(CLK_IT_TypeDef CLK_IT)
2869                     ; 688 {
2870                     .text:	section	.text,new
2871  0000               _CLK_GetITStatus:
2873  0000 88            	push	a
2874  0001 88            	push	a
2875       00000001      OFST:	set	1
2878                     ; 689   ITStatus bitstatus = RESET;
2880                     ; 692   assert_param(IS_CLK_IT_OK(CLK_IT));
2882  0002 a10c          	cp	a,#12
2883  0004 2712          	jreq	L453
2884  0006 a11c          	cp	a,#28
2885  0008 270e          	jreq	L453
2886  000a ae02b4        	ldw	x,#692
2887  000d 89            	pushw	x
2888  000e 5f            	clrw	x
2889  000f 89            	pushw	x
2890  0010 ae000c        	ldw	x,#L75
2891  0013 cd0000        	call	_assert_failed
2893  0016 5b04          	addw	sp,#4
2894  0018               L453:
2895                     ; 694   if (CLK_IT == CLK_IT_SWIF)
2897  0018 7b02          	ld	a,(OFST+1,sp)
2898  001a a11c          	cp	a,#28
2899  001c 260b          	jrne	L1131
2900                     ; 697     if ((CLK->SWCR & (uint8_t)CLK_IT) == (uint8_t)0x0C)
2902  001e c650c5        	ld	a,20677
2903  0021 1402          	and	a,(OFST+1,sp)
2904  0023 a10c          	cp	a,#12
2905  0025 260f          	jrne	L1231
2906                     ; 699       bitstatus = SET;
2908  0027 2009          	jp	LC011
2909                     ; 703       bitstatus = RESET;
2910  0029               L1131:
2911                     ; 709     if ((CLK->CSSR & (uint8_t)CLK_IT) == (uint8_t)0x0C)
2913  0029 c650c8        	ld	a,20680
2914  002c 1402          	and	a,(OFST+1,sp)
2915  002e a10c          	cp	a,#12
2916  0030 2604          	jrne	L1231
2917                     ; 711       bitstatus = SET;
2919  0032               LC011:
2921  0032 a601          	ld	a,#1
2924  0034 2001          	jra	L7131
2925  0036               L1231:
2926                     ; 715       bitstatus = RESET;
2929  0036 4f            	clr	a
2931  0037               L7131:
2932                     ; 720   return bitstatus;
2936  0037 85            	popw	x
2937  0038 81            	ret	
2974                     ; 729 void CLK_ClearITPendingBit(CLK_IT_TypeDef CLK_IT)
2974                     ; 730 {
2975                     .text:	section	.text,new
2976  0000               _CLK_ClearITPendingBit:
2978  0000 88            	push	a
2979       00000000      OFST:	set	0
2982                     ; 732   assert_param(IS_CLK_IT_OK(CLK_IT));
2984  0001 a10c          	cp	a,#12
2985  0003 2712          	jreq	L663
2986  0005 a11c          	cp	a,#28
2987  0007 270e          	jreq	L663
2988  0009 ae02dc        	ldw	x,#732
2989  000c 89            	pushw	x
2990  000d 5f            	clrw	x
2991  000e 89            	pushw	x
2992  000f ae000c        	ldw	x,#L75
2993  0012 cd0000        	call	_assert_failed
2995  0015 5b04          	addw	sp,#4
2996  0017               L663:
2997                     ; 734   if (CLK_IT == (uint8_t)CLK_IT_CSSD)
2999  0017 7b01          	ld	a,(OFST+1,sp)
3000  0019 a10c          	cp	a,#12
3001  001b 2606          	jrne	L3431
3002                     ; 737     CLK->CSSR &= (uint8_t)(~CLK_CSSR_CSSD);
3004  001d 721750c8      	bres	20680,#3
3006  0021 2004          	jra	L5431
3007  0023               L3431:
3008                     ; 742     CLK->SWCR &= (uint8_t)(~CLK_SWCR_SWIF);
3010  0023 721750c5      	bres	20677,#3
3011  0027               L5431:
3012                     ; 745 }
3015  0027 84            	pop	a
3016  0028 81            	ret	
3051                     	xdef	_CLKPrescTable
3052                     	xdef	_HSIDivFactor
3053                     	xdef	_CLK_ClearITPendingBit
3054                     	xdef	_CLK_GetITStatus
3055                     	xdef	_CLK_GetFlagStatus
3056                     	xdef	_CLK_GetSYSCLKSource
3057                     	xdef	_CLK_GetClockFreq
3058                     	xdef	_CLK_AdjustHSICalibrationValue
3059                     	xdef	_CLK_SYSCLKEmergencyClear
3060                     	xdef	_CLK_ClockSecuritySystemEnable
3061                     	xdef	_CLK_SWIMConfig
3062                     	xdef	_CLK_SYSCLKConfig
3063                     	xdef	_CLK_ITConfig
3064                     	xdef	_CLK_CCOConfig
3065                     	xdef	_CLK_HSIPrescalerConfig
3066                     	xdef	_CLK_ClockSwitchConfig
3067                     	xdef	_CLK_PeripheralClockConfig
3068                     	xdef	_CLK_SlowActiveHaltWakeUpCmd
3069                     	xdef	_CLK_FastHaltWakeUpCmd
3070                     	xdef	_CLK_ClockSwitchCmd
3071                     	xdef	_CLK_CCOCmd
3072                     	xdef	_CLK_LSICmd
3073                     	xdef	_CLK_HSICmd
3074                     	xdef	_CLK_HSECmd
3075                     	xdef	_CLK_DeInit
3076                     	xref	_assert_failed
3077                     	switch	.const
3078  000c               L75:
3079  000c 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
3080  001e 6965735c7374  	dc.b	"ies\stm8s_stdperip"
3081  0030 685f64726976  	dc.b	"h_driver\src\stm8s"
3082  0042 5f636c6b2e63  	dc.b	"_clk.c",0
3083                     	xref.b	c_lreg
3084                     	xref.b	c_x
3104                     	xref	c_ltor
3105                     	xref	c_ludv
3106                     	xref	c_rtol
3107                     	end
