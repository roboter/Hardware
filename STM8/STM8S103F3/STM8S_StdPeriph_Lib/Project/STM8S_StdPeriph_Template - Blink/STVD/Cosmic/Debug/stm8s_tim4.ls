   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 49 void TIM4_DeInit(void)
  49                     ; 50 {
  51                     .text:	section	.text,new
  52  0000               _TIM4_DeInit:
  56                     ; 51   TIM4->CR1 = TIM4_CR1_RESET_VALUE;
  58  0000 725f5340      	clr	21312
  59                     ; 52   TIM4->IER = TIM4_IER_RESET_VALUE;
  61  0004 725f5343      	clr	21315
  62                     ; 53   TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
  64  0008 725f5346      	clr	21318
  65                     ; 54   TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
  67  000c 725f5347      	clr	21319
  68                     ; 55   TIM4->ARR = TIM4_ARR_RESET_VALUE;
  70  0010 35ff5348      	mov	21320,#255
  71                     ; 56   TIM4->SR1 = TIM4_SR1_RESET_VALUE;
  73  0014 725f5344      	clr	21316
  74                     ; 57 }
  77  0018 81            	ret	
 184                     ; 65 void TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period)
 184                     ; 66 {
 185                     .text:	section	.text,new
 186  0000               _TIM4_TimeBaseInit:
 188  0000 89            	pushw	x
 189       00000000      OFST:	set	0
 192                     ; 68   assert_param(IS_TIM4_PRESCALER_OK(TIM4_Prescaler));
 194  0001 9e            	ld	a,xh
 195  0002 4d            	tnz	a
 196  0003 2730          	jreq	L41
 197  0005 9e            	ld	a,xh
 198  0006 4a            	dec	a
 199  0007 272c          	jreq	L41
 200  0009 9e            	ld	a,xh
 201  000a a102          	cp	a,#2
 202  000c 2727          	jreq	L41
 203  000e 9e            	ld	a,xh
 204  000f a103          	cp	a,#3
 205  0011 2722          	jreq	L41
 206  0013 9e            	ld	a,xh
 207  0014 a104          	cp	a,#4
 208  0016 271d          	jreq	L41
 209  0018 9e            	ld	a,xh
 210  0019 a105          	cp	a,#5
 211  001b 2718          	jreq	L41
 212  001d 9e            	ld	a,xh
 213  001e a106          	cp	a,#6
 214  0020 2713          	jreq	L41
 215  0022 9e            	ld	a,xh
 216  0023 a107          	cp	a,#7
 217  0025 270e          	jreq	L41
 218  0027 ae0044        	ldw	x,#68
 219  002a 89            	pushw	x
 220  002b 5f            	clrw	x
 221  002c 89            	pushw	x
 222  002d ae0000        	ldw	x,#L76
 223  0030 cd0000        	call	_assert_failed
 225  0033 5b04          	addw	sp,#4
 226  0035               L41:
 227                     ; 70   TIM4->PSCR = (uint8_t)(TIM4_Prescaler);
 229  0035 7b01          	ld	a,(OFST+1,sp)
 230  0037 c75347        	ld	21319,a
 231                     ; 72   TIM4->ARR = (uint8_t)(TIM4_Period);
 233  003a 7b02          	ld	a,(OFST+2,sp)
 234  003c c75348        	ld	21320,a
 235                     ; 73 }
 238  003f 85            	popw	x
 239  0040 81            	ret	
 295                     ; 81 void TIM4_Cmd(FunctionalState NewState)
 295                     ; 82 {
 296                     .text:	section	.text,new
 297  0000               _TIM4_Cmd:
 299  0000 88            	push	a
 300       00000000      OFST:	set	0
 303                     ; 84   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 305  0001 4d            	tnz	a
 306  0002 2711          	jreq	L62
 307  0004 4a            	dec	a
 308  0005 270e          	jreq	L62
 309  0007 ae0054        	ldw	x,#84
 310  000a 89            	pushw	x
 311  000b 5f            	clrw	x
 312  000c 89            	pushw	x
 313  000d ae0000        	ldw	x,#L76
 314  0010 cd0000        	call	_assert_failed
 316  0013 5b04          	addw	sp,#4
 317  0015               L62:
 318                     ; 87   if (NewState != DISABLE)
 320  0015 7b01          	ld	a,(OFST+1,sp)
 321  0017 2706          	jreq	L711
 322                     ; 89     TIM4->CR1 |= TIM4_CR1_CEN;
 324  0019 72105340      	bset	21312,#0
 326  001d 2004          	jra	L121
 327  001f               L711:
 328                     ; 93     TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
 330  001f 72115340      	bres	21312,#0
 331  0023               L121:
 332                     ; 95 }
 335  0023 84            	pop	a
 336  0024 81            	ret	
 395                     ; 107 void TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState)
 395                     ; 108 {
 396                     .text:	section	.text,new
 397  0000               _TIM4_ITConfig:
 399  0000 89            	pushw	x
 400       00000000      OFST:	set	0
 403                     ; 110   assert_param(IS_TIM4_IT_OK(TIM4_IT));
 405  0001 9e            	ld	a,xh
 406  0002 4a            	dec	a
 407  0003 2705          	jreq	L63
 408  0005 ae006e        	ldw	x,#110
 409  0008 ad22          	call	LC001
 410  000a               L63:
 411                     ; 111   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 413  000a 7b02          	ld	a,(OFST+2,sp)
 414  000c 2708          	jreq	L64
 415  000e 4a            	dec	a
 416  000f 2705          	jreq	L64
 417  0011 ae006f        	ldw	x,#111
 418  0014 ad16          	call	LC001
 419  0016               L64:
 420                     ; 113   if (NewState != DISABLE)
 422  0016 7b02          	ld	a,(OFST+2,sp)
 423  0018 2707          	jreq	L351
 424                     ; 116     TIM4->IER |= (uint8_t)TIM4_IT;
 426  001a c65343        	ld	a,21315
 427  001d 1a01          	or	a,(OFST+1,sp)
 429  001f 2006          	jra	L551
 430  0021               L351:
 431                     ; 121     TIM4->IER &= (uint8_t)(~TIM4_IT);
 433  0021 7b01          	ld	a,(OFST+1,sp)
 434  0023 43            	cpl	a
 435  0024 c45343        	and	a,21315
 436  0027               L551:
 437  0027 c75343        	ld	21315,a
 438                     ; 123 }
 441  002a 85            	popw	x
 442  002b 81            	ret	
 443  002c               LC001:
 444  002c 89            	pushw	x
 445  002d 5f            	clrw	x
 446  002e 89            	pushw	x
 447  002f ae0000        	ldw	x,#L76
 448  0032 cd0000        	call	_assert_failed
 450  0035 5b04          	addw	sp,#4
 451  0037 81            	ret	
 488                     ; 131 void TIM4_UpdateDisableConfig(FunctionalState NewState)
 488                     ; 132 {
 489                     .text:	section	.text,new
 490  0000               _TIM4_UpdateDisableConfig:
 492  0000 88            	push	a
 493       00000000      OFST:	set	0
 496                     ; 134   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 498  0001 4d            	tnz	a
 499  0002 2711          	jreq	L06
 500  0004 4a            	dec	a
 501  0005 270e          	jreq	L06
 502  0007 ae0086        	ldw	x,#134
 503  000a 89            	pushw	x
 504  000b 5f            	clrw	x
 505  000c 89            	pushw	x
 506  000d ae0000        	ldw	x,#L76
 507  0010 cd0000        	call	_assert_failed
 509  0013 5b04          	addw	sp,#4
 510  0015               L06:
 511                     ; 137   if (NewState != DISABLE)
 513  0015 7b01          	ld	a,(OFST+1,sp)
 514  0017 2706          	jreq	L571
 515                     ; 139     TIM4->CR1 |= TIM4_CR1_UDIS;
 517  0019 72125340      	bset	21312,#1
 519  001d 2004          	jra	L771
 520  001f               L571:
 521                     ; 143     TIM4->CR1 &= (uint8_t)(~TIM4_CR1_UDIS);
 523  001f 72135340      	bres	21312,#1
 524  0023               L771:
 525                     ; 145 }
 528  0023 84            	pop	a
 529  0024 81            	ret	
 588                     ; 155 void TIM4_UpdateRequestConfig(TIM4_UpdateSource_TypeDef TIM4_UpdateSource)
 588                     ; 156 {
 589                     .text:	section	.text,new
 590  0000               _TIM4_UpdateRequestConfig:
 592  0000 88            	push	a
 593       00000000      OFST:	set	0
 596                     ; 158   assert_param(IS_TIM4_UPDATE_SOURCE_OK(TIM4_UpdateSource));
 598  0001 4d            	tnz	a
 599  0002 2711          	jreq	L27
 600  0004 4a            	dec	a
 601  0005 270e          	jreq	L27
 602  0007 ae009e        	ldw	x,#158
 603  000a 89            	pushw	x
 604  000b 5f            	clrw	x
 605  000c 89            	pushw	x
 606  000d ae0000        	ldw	x,#L76
 607  0010 cd0000        	call	_assert_failed
 609  0013 5b04          	addw	sp,#4
 610  0015               L27:
 611                     ; 161   if (TIM4_UpdateSource != TIM4_UPDATESOURCE_GLOBAL)
 613  0015 7b01          	ld	a,(OFST+1,sp)
 614  0017 2706          	jreq	L722
 615                     ; 163     TIM4->CR1 |= TIM4_CR1_URS;
 617  0019 72145340      	bset	21312,#2
 619  001d 2004          	jra	L132
 620  001f               L722:
 621                     ; 167     TIM4->CR1 &= (uint8_t)(~TIM4_CR1_URS);
 623  001f 72155340      	bres	21312,#2
 624  0023               L132:
 625                     ; 169 }
 628  0023 84            	pop	a
 629  0024 81            	ret	
 687                     ; 179 void TIM4_SelectOnePulseMode(TIM4_OPMode_TypeDef TIM4_OPMode)
 687                     ; 180 {
 688                     .text:	section	.text,new
 689  0000               _TIM4_SelectOnePulseMode:
 691  0000 88            	push	a
 692       00000000      OFST:	set	0
 695                     ; 182   assert_param(IS_TIM4_OPM_MODE_OK(TIM4_OPMode));
 697  0001 a101          	cp	a,#1
 698  0003 2711          	jreq	L401
 699  0005 4d            	tnz	a
 700  0006 270e          	jreq	L401
 701  0008 ae00b6        	ldw	x,#182
 702  000b 89            	pushw	x
 703  000c 5f            	clrw	x
 704  000d 89            	pushw	x
 705  000e ae0000        	ldw	x,#L76
 706  0011 cd0000        	call	_assert_failed
 708  0014 5b04          	addw	sp,#4
 709  0016               L401:
 710                     ; 185   if (TIM4_OPMode != TIM4_OPMODE_REPETITIVE)
 712  0016 7b01          	ld	a,(OFST+1,sp)
 713  0018 2706          	jreq	L162
 714                     ; 187     TIM4->CR1 |= TIM4_CR1_OPM;
 716  001a 72165340      	bset	21312,#3
 718  001e 2004          	jra	L362
 719  0020               L162:
 720                     ; 191     TIM4->CR1 &= (uint8_t)(~TIM4_CR1_OPM);
 722  0020 72175340      	bres	21312,#3
 723  0024               L362:
 724                     ; 193 }
 727  0024 84            	pop	a
 728  0025 81            	ret	
 797                     ; 215 void TIM4_PrescalerConfig(TIM4_Prescaler_TypeDef Prescaler, TIM4_PSCReloadMode_TypeDef TIM4_PSCReloadMode)
 797                     ; 216 {
 798                     .text:	section	.text,new
 799  0000               _TIM4_PrescalerConfig:
 801  0000 89            	pushw	x
 802       00000000      OFST:	set	0
 805                     ; 218   assert_param(IS_TIM4_PRESCALER_RELOAD_OK(TIM4_PSCReloadMode));
 807  0001 9f            	ld	a,xl
 808  0002 4d            	tnz	a
 809  0003 2709          	jreq	L611
 810  0005 9f            	ld	a,xl
 811  0006 4a            	dec	a
 812  0007 2705          	jreq	L611
 813  0009 ae00da        	ldw	x,#218
 814  000c ad31          	call	LC002
 815  000e               L611:
 816                     ; 219   assert_param(IS_TIM4_PRESCALER_OK(Prescaler));
 818  000e 7b01          	ld	a,(OFST+1,sp)
 819  0010 2723          	jreq	L621
 820  0012 a101          	cp	a,#1
 821  0014 271f          	jreq	L621
 822  0016 a102          	cp	a,#2
 823  0018 271b          	jreq	L621
 824  001a a103          	cp	a,#3
 825  001c 2717          	jreq	L621
 826  001e a104          	cp	a,#4
 827  0020 2713          	jreq	L621
 828  0022 a105          	cp	a,#5
 829  0024 270f          	jreq	L621
 830  0026 a106          	cp	a,#6
 831  0028 270b          	jreq	L621
 832  002a a107          	cp	a,#7
 833  002c 2707          	jreq	L621
 834  002e ae00db        	ldw	x,#219
 835  0031 ad0c          	call	LC002
 836  0033 7b01          	ld	a,(OFST+1,sp)
 837  0035               L621:
 838                     ; 222   TIM4->PSCR = (uint8_t)Prescaler;
 840  0035 c75347        	ld	21319,a
 841                     ; 225   TIM4->EGR = (uint8_t)TIM4_PSCReloadMode;
 843  0038 7b02          	ld	a,(OFST+2,sp)
 844  003a c75345        	ld	21317,a
 845                     ; 226 }
 848  003d 85            	popw	x
 849  003e 81            	ret	
 850  003f               LC002:
 851  003f 89            	pushw	x
 852  0040 5f            	clrw	x
 853  0041 89            	pushw	x
 854  0042 ae0000        	ldw	x,#L76
 855  0045 cd0000        	call	_assert_failed
 857  0048 5b04          	addw	sp,#4
 858  004a 81            	ret	
 895                     ; 234 void TIM4_ARRPreloadConfig(FunctionalState NewState)
 895                     ; 235 {
 896                     .text:	section	.text,new
 897  0000               _TIM4_ARRPreloadConfig:
 899  0000 88            	push	a
 900       00000000      OFST:	set	0
 903                     ; 237   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 905  0001 4d            	tnz	a
 906  0002 2711          	jreq	L041
 907  0004 4a            	dec	a
 908  0005 270e          	jreq	L041
 909  0007 ae00ed        	ldw	x,#237
 910  000a 89            	pushw	x
 911  000b 5f            	clrw	x
 912  000c 89            	pushw	x
 913  000d ae0000        	ldw	x,#L76
 914  0010 cd0000        	call	_assert_failed
 916  0013 5b04          	addw	sp,#4
 917  0015               L041:
 918                     ; 240   if (NewState != DISABLE)
 920  0015 7b01          	ld	a,(OFST+1,sp)
 921  0017 2706          	jreq	L533
 922                     ; 242     TIM4->CR1 |= TIM4_CR1_ARPE;
 924  0019 721e5340      	bset	21312,#7
 926  001d 2004          	jra	L733
 927  001f               L533:
 928                     ; 246     TIM4->CR1 &= (uint8_t)(~TIM4_CR1_ARPE);
 930  001f 721f5340      	bres	21312,#7
 931  0023               L733:
 932                     ; 248 }
 935  0023 84            	pop	a
 936  0024 81            	ret	
 986                     ; 257 void TIM4_GenerateEvent(TIM4_EventSource_TypeDef TIM4_EventSource)
 986                     ; 258 {
 987                     .text:	section	.text,new
 988  0000               _TIM4_GenerateEvent:
 990  0000 88            	push	a
 991       00000000      OFST:	set	0
 994                     ; 260   assert_param(IS_TIM4_EVENT_SOURCE_OK(TIM4_EventSource));
 996  0001 4a            	dec	a
 997  0002 270e          	jreq	L051
 998  0004 ae0104        	ldw	x,#260
 999  0007 89            	pushw	x
1000  0008 5f            	clrw	x
1001  0009 89            	pushw	x
1002  000a ae0000        	ldw	x,#L76
1003  000d cd0000        	call	_assert_failed
1005  0010 5b04          	addw	sp,#4
1006  0012               L051:
1007                     ; 263   TIM4->EGR = (uint8_t)(TIM4_EventSource);
1009  0012 7b01          	ld	a,(OFST+1,sp)
1010  0014 c75345        	ld	21317,a
1011                     ; 264 }
1014  0017 84            	pop	a
1015  0018 81            	ret	
1049                     ; 272 void TIM4_SetCounter(uint8_t Counter)
1049                     ; 273 {
1050                     .text:	section	.text,new
1051  0000               _TIM4_SetCounter:
1055                     ; 275   TIM4->CNTR = (uint8_t)(Counter);
1057  0000 c75346        	ld	21318,a
1058                     ; 276 }
1061  0003 81            	ret	
1095                     ; 284 void TIM4_SetAutoreload(uint8_t Autoreload)
1095                     ; 285 {
1096                     .text:	section	.text,new
1097  0000               _TIM4_SetAutoreload:
1101                     ; 287   TIM4->ARR = (uint8_t)(Autoreload);
1103  0000 c75348        	ld	21320,a
1104                     ; 288 }
1107  0003 81            	ret	
1130                     ; 295 uint8_t TIM4_GetCounter(void)
1130                     ; 296 {
1131                     .text:	section	.text,new
1132  0000               _TIM4_GetCounter:
1136                     ; 298   return (uint8_t)(TIM4->CNTR);
1138  0000 c65346        	ld	a,21318
1141  0003 81            	ret	
1165                     ; 306 TIM4_Prescaler_TypeDef TIM4_GetPrescaler(void)
1165                     ; 307 {
1166                     .text:	section	.text,new
1167  0000               _TIM4_GetPrescaler:
1171                     ; 309   return (TIM4_Prescaler_TypeDef)(TIM4->PSCR);
1173  0000 c65347        	ld	a,21319
1176  0003 81            	ret	
1256                     ; 319 FlagStatus TIM4_GetFlagStatus(TIM4_FLAG_TypeDef TIM4_FLAG)
1256                     ; 320 {
1257                     .text:	section	.text,new
1258  0000               _TIM4_GetFlagStatus:
1260  0000 88            	push	a
1261  0001 88            	push	a
1262       00000001      OFST:	set	1
1265                     ; 321   FlagStatus bitstatus = RESET;
1267                     ; 324   assert_param(IS_TIM4_GET_FLAG_OK(TIM4_FLAG));
1269  0002 4a            	dec	a
1270  0003 270e          	jreq	L071
1271  0005 ae0144        	ldw	x,#324
1272  0008 89            	pushw	x
1273  0009 5f            	clrw	x
1274  000a 89            	pushw	x
1275  000b ae0000        	ldw	x,#L76
1276  000e cd0000        	call	_assert_failed
1278  0011 5b04          	addw	sp,#4
1279  0013               L071:
1280                     ; 326   if ((TIM4->SR1 & (uint8_t)TIM4_FLAG)  != 0)
1282  0013 c65344        	ld	a,21316
1283  0016 1502          	bcp	a,(OFST+1,sp)
1284  0018 2704          	jreq	L105
1285                     ; 328     bitstatus = SET;
1287  001a a601          	ld	a,#1
1290  001c 2001          	jra	L305
1291  001e               L105:
1292                     ; 332     bitstatus = RESET;
1294  001e 4f            	clr	a
1296  001f               L305:
1297                     ; 334   return ((FlagStatus)bitstatus);
1301  001f 85            	popw	x
1302  0020 81            	ret	
1338                     ; 344 void TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG)
1338                     ; 345 {
1339                     .text:	section	.text,new
1340  0000               _TIM4_ClearFlag:
1342  0000 88            	push	a
1343       00000000      OFST:	set	0
1346                     ; 347   assert_param(IS_TIM4_GET_FLAG_OK(TIM4_FLAG));
1348  0001 4a            	dec	a
1349  0002 270e          	jreq	L002
1350  0004 ae015b        	ldw	x,#347
1351  0007 89            	pushw	x
1352  0008 5f            	clrw	x
1353  0009 89            	pushw	x
1354  000a ae0000        	ldw	x,#L76
1355  000d cd0000        	call	_assert_failed
1357  0010 5b04          	addw	sp,#4
1358  0012               L002:
1359                     ; 350   TIM4->SR1 = (uint8_t)(~TIM4_FLAG);
1361  0012 7b01          	ld	a,(OFST+1,sp)
1362  0014 43            	cpl	a
1363  0015 c75344        	ld	21316,a
1364                     ; 351 }
1367  0018 84            	pop	a
1368  0019 81            	ret	
1433                     ; 360 ITStatus TIM4_GetITStatus(TIM4_IT_TypeDef TIM4_IT)
1433                     ; 361 {
1434                     .text:	section	.text,new
1435  0000               _TIM4_GetITStatus:
1437  0000 88            	push	a
1438  0001 89            	pushw	x
1439       00000002      OFST:	set	2
1442                     ; 362   ITStatus bitstatus = RESET;
1444                     ; 364   uint8_t itstatus = 0x0, itenable = 0x0;
1448                     ; 367   assert_param(IS_TIM4_IT_OK(TIM4_IT));
1450  0002 4a            	dec	a
1451  0003 270e          	jreq	L012
1452  0005 ae016f        	ldw	x,#367
1453  0008 89            	pushw	x
1454  0009 5f            	clrw	x
1455  000a 89            	pushw	x
1456  000b ae0000        	ldw	x,#L76
1457  000e cd0000        	call	_assert_failed
1459  0011 5b04          	addw	sp,#4
1460  0013               L012:
1461                     ; 369   itstatus = (uint8_t)(TIM4->SR1 & (uint8_t)TIM4_IT);
1463  0013 c65344        	ld	a,21316
1464  0016 1403          	and	a,(OFST+1,sp)
1465  0018 6b01          	ld	(OFST-1,sp),a
1467                     ; 371   itenable = (uint8_t)(TIM4->IER & (uint8_t)TIM4_IT);
1469  001a c65343        	ld	a,21315
1470  001d 1403          	and	a,(OFST+1,sp)
1471  001f 6b02          	ld	(OFST+0,sp),a
1473                     ; 373   if ((itstatus != (uint8_t)RESET ) && (itenable != (uint8_t)RESET ))
1475  0021 7b01          	ld	a,(OFST-1,sp)
1476  0023 2708          	jreq	L555
1478  0025 7b02          	ld	a,(OFST+0,sp)
1479  0027 2704          	jreq	L555
1480                     ; 375     bitstatus = (ITStatus)SET;
1482  0029 a601          	ld	a,#1
1485  002b 2001          	jra	L755
1486  002d               L555:
1487                     ; 379     bitstatus = (ITStatus)RESET;
1489  002d 4f            	clr	a
1491  002e               L755:
1492                     ; 381   return ((ITStatus)bitstatus);
1496  002e 5b03          	addw	sp,#3
1497  0030 81            	ret	
1534                     ; 391 void TIM4_ClearITPendingBit(TIM4_IT_TypeDef TIM4_IT)
1534                     ; 392 {
1535                     .text:	section	.text,new
1536  0000               _TIM4_ClearITPendingBit:
1538  0000 88            	push	a
1539       00000000      OFST:	set	0
1542                     ; 394   assert_param(IS_TIM4_IT_OK(TIM4_IT));
1544  0001 4a            	dec	a
1545  0002 270e          	jreq	L022
1546  0004 ae018a        	ldw	x,#394
1547  0007 89            	pushw	x
1548  0008 5f            	clrw	x
1549  0009 89            	pushw	x
1550  000a ae0000        	ldw	x,#L76
1551  000d cd0000        	call	_assert_failed
1553  0010 5b04          	addw	sp,#4
1554  0012               L022:
1555                     ; 397   TIM4->SR1 = (uint8_t)(~TIM4_IT);
1557  0012 7b01          	ld	a,(OFST+1,sp)
1558  0014 43            	cpl	a
1559  0015 c75344        	ld	21316,a
1560                     ; 398 }
1563  0018 84            	pop	a
1564  0019 81            	ret	
1577                     	xdef	_TIM4_ClearITPendingBit
1578                     	xdef	_TIM4_GetITStatus
1579                     	xdef	_TIM4_ClearFlag
1580                     	xdef	_TIM4_GetFlagStatus
1581                     	xdef	_TIM4_GetPrescaler
1582                     	xdef	_TIM4_GetCounter
1583                     	xdef	_TIM4_SetAutoreload
1584                     	xdef	_TIM4_SetCounter
1585                     	xdef	_TIM4_GenerateEvent
1586                     	xdef	_TIM4_ARRPreloadConfig
1587                     	xdef	_TIM4_PrescalerConfig
1588                     	xdef	_TIM4_SelectOnePulseMode
1589                     	xdef	_TIM4_UpdateRequestConfig
1590                     	xdef	_TIM4_UpdateDisableConfig
1591                     	xdef	_TIM4_ITConfig
1592                     	xdef	_TIM4_Cmd
1593                     	xdef	_TIM4_TimeBaseInit
1594                     	xdef	_TIM4_DeInit
1595                     	xref	_assert_failed
1596                     .const:	section	.text
1597  0000               L76:
1598  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
1599  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
1600  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
1601  0036 5f74696d342e  	dc.b	"_tim4.c",0
1621                     	end
