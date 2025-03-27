   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.13.2 - 04 Jun 2024
   3                     ; Generator (Limited) V4.6.4 - 15 Jan 2025
   4                     ; Optimizer V4.6.4 - 15 Jan 2025
  49                     ; 52 void ADC1_DeInit(void)
  49                     ; 53 {
  51                     .text:	section	.text,new
  52  0000               _ADC1_DeInit:
  56                     ; 54   ADC1->CSR  = ADC1_CSR_RESET_VALUE;
  58  0000 725f5400      	clr	21504
  59                     ; 55   ADC1->CR1  = ADC1_CR1_RESET_VALUE;
  61  0004 725f5401      	clr	21505
  62                     ; 56   ADC1->CR2  = ADC1_CR2_RESET_VALUE;
  64  0008 725f5402      	clr	21506
  65                     ; 57   ADC1->CR3  = ADC1_CR3_RESET_VALUE;
  67  000c 725f5403      	clr	21507
  68                     ; 58   ADC1->TDRH = ADC1_TDRH_RESET_VALUE;
  70  0010 725f5406      	clr	21510
  71                     ; 59   ADC1->TDRL = ADC1_TDRL_RESET_VALUE;
  73  0014 725f5407      	clr	21511
  74                     ; 60   ADC1->HTRH = ADC1_HTRH_RESET_VALUE;
  76  0018 35ff5408      	mov	21512,#255
  77                     ; 61   ADC1->HTRL = ADC1_HTRL_RESET_VALUE;
  79  001c 35035409      	mov	21513,#3
  80                     ; 62   ADC1->LTRH = ADC1_LTRH_RESET_VALUE;
  82  0020 725f540a      	clr	21514
  83                     ; 63   ADC1->LTRL = ADC1_LTRL_RESET_VALUE;
  85  0024 725f540b      	clr	21515
  86                     ; 64   ADC1->AWCRH = ADC1_AWCRH_RESET_VALUE;
  88  0028 725f540e      	clr	21518
  89                     ; 65   ADC1->AWCRL = ADC1_AWCRL_RESET_VALUE;
  91  002c 725f540f      	clr	21519
  92                     ; 66 }
  95  0030 81            	ret	
 547                     ; 88 void ADC1_Init(ADC1_ConvMode_TypeDef ADC1_ConversionMode, ADC1_Channel_TypeDef ADC1_Channel, ADC1_PresSel_TypeDef ADC1_PrescalerSelection, ADC1_ExtTrig_TypeDef ADC1_ExtTrigger, FunctionalState ADC1_ExtTriggerState, ADC1_Align_TypeDef ADC1_Align, ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel, FunctionalState ADC1_SchmittTriggerState)
 547                     ; 89 {
 548                     .text:	section	.text,new
 549  0000               _ADC1_Init:
 551  0000 89            	pushw	x
 552       00000000      OFST:	set	0
 555                     ; 91   assert_param(IS_ADC1_CONVERSIONMODE_OK(ADC1_ConversionMode));
 557  0001 9e            	ld	a,xh
 558  0002 4d            	tnz	a
 559  0003 270a          	jreq	L41
 560  0005 9e            	ld	a,xh
 561  0006 4a            	dec	a
 562  0007 2706          	jreq	L41
 563  0009 ae005b        	ldw	x,#91
 564  000c cd00f9        	call	LC001
 565  000f               L41:
 566                     ; 92   assert_param(IS_ADC1_CHANNEL_OK(ADC1_Channel));
 568  000f 7b02          	ld	a,(OFST+2,sp)
 569  0011 272e          	jreq	L42
 570  0013 a101          	cp	a,#1
 571  0015 272a          	jreq	L42
 572  0017 a102          	cp	a,#2
 573  0019 2726          	jreq	L42
 574  001b a103          	cp	a,#3
 575  001d 2722          	jreq	L42
 576  001f a104          	cp	a,#4
 577  0021 271e          	jreq	L42
 578  0023 a105          	cp	a,#5
 579  0025 271a          	jreq	L42
 580  0027 a106          	cp	a,#6
 581  0029 2716          	jreq	L42
 582  002b a107          	cp	a,#7
 583  002d 2712          	jreq	L42
 584  002f a108          	cp	a,#8
 585  0031 270e          	jreq	L42
 586  0033 a10c          	cp	a,#12
 587  0035 270a          	jreq	L42
 588  0037 a109          	cp	a,#9
 589  0039 2706          	jreq	L42
 590  003b ae005c        	ldw	x,#92
 591  003e cd00f9        	call	LC001
 592  0041               L42:
 593                     ; 93   assert_param(IS_ADC1_PRESSEL_OK(ADC1_PrescalerSelection));
 595  0041 7b05          	ld	a,(OFST+5,sp)
 596  0043 2722          	jreq	L43
 597  0045 a110          	cp	a,#16
 598  0047 271e          	jreq	L43
 599  0049 a120          	cp	a,#32
 600  004b 271a          	jreq	L43
 601  004d a130          	cp	a,#48
 602  004f 2716          	jreq	L43
 603  0051 a140          	cp	a,#64
 604  0053 2712          	jreq	L43
 605  0055 a150          	cp	a,#80
 606  0057 270e          	jreq	L43
 607  0059 a160          	cp	a,#96
 608  005b 270a          	jreq	L43
 609  005d a170          	cp	a,#112
 610  005f 2706          	jreq	L43
 611  0061 ae005d        	ldw	x,#93
 612  0064 cd00f9        	call	LC001
 613  0067               L43:
 614                     ; 94   assert_param(IS_ADC1_EXTTRIG_OK(ADC1_ExtTrigger));
 616  0067 7b06          	ld	a,(OFST+6,sp)
 617  0069 270a          	jreq	L44
 618  006b a110          	cp	a,#16
 619  006d 2706          	jreq	L44
 620  006f ae005e        	ldw	x,#94
 621  0072 cd00f9        	call	LC001
 622  0075               L44:
 623                     ; 95   assert_param(IS_FUNCTIONALSTATE_OK(((ADC1_ExtTriggerState))));
 625  0075 7b07          	ld	a,(OFST+7,sp)
 626  0077 2708          	jreq	L45
 627  0079 4a            	dec	a
 628  007a 2705          	jreq	L45
 629  007c ae005f        	ldw	x,#95
 630  007f ad78          	call	LC001
 631  0081               L45:
 632                     ; 96   assert_param(IS_ADC1_ALIGN_OK(ADC1_Align));
 634  0081 7b08          	ld	a,(OFST+8,sp)
 635  0083 2709          	jreq	L46
 636  0085 a108          	cp	a,#8
 637  0087 2705          	jreq	L46
 638  0089 ae0060        	ldw	x,#96
 639  008c ad6b          	call	LC001
 640  008e               L46:
 641                     ; 97   assert_param(IS_ADC1_SCHMITTTRIG_OK(ADC1_SchmittTriggerChannel));
 643  008e 7b09          	ld	a,(OFST+9,sp)
 644  0090 2731          	jreq	L47
 645  0092 a101          	cp	a,#1
 646  0094 272d          	jreq	L47
 647  0096 a102          	cp	a,#2
 648  0098 2729          	jreq	L47
 649  009a a103          	cp	a,#3
 650  009c 2725          	jreq	L47
 651  009e a104          	cp	a,#4
 652  00a0 2721          	jreq	L47
 653  00a2 a105          	cp	a,#5
 654  00a4 271d          	jreq	L47
 655  00a6 a106          	cp	a,#6
 656  00a8 2719          	jreq	L47
 657  00aa a107          	cp	a,#7
 658  00ac 2715          	jreq	L47
 659  00ae a108          	cp	a,#8
 660  00b0 2711          	jreq	L47
 661  00b2 a10c          	cp	a,#12
 662  00b4 270d          	jreq	L47
 663  00b6 a1ff          	cp	a,#255
 664  00b8 2709          	jreq	L47
 665  00ba a109          	cp	a,#9
 666  00bc 2705          	jreq	L47
 667  00be ae0061        	ldw	x,#97
 668  00c1 ad36          	call	LC001
 669  00c3               L47:
 670                     ; 98   assert_param(IS_FUNCTIONALSTATE_OK(ADC1_SchmittTriggerState));
 672  00c3 7b0a          	ld	a,(OFST+10,sp)
 673  00c5 2708          	jreq	L401
 674  00c7 4a            	dec	a
 675  00c8 2705          	jreq	L401
 676  00ca ae0062        	ldw	x,#98
 677  00cd ad2a          	call	LC001
 678  00cf               L401:
 679                     ; 103   ADC1_ConversionConfig(ADC1_ConversionMode, ADC1_Channel, ADC1_Align);
 681  00cf 7b08          	ld	a,(OFST+8,sp)
 682  00d1 88            	push	a
 683  00d2 7b03          	ld	a,(OFST+3,sp)
 684  00d4 97            	ld	xl,a
 685  00d5 7b02          	ld	a,(OFST+2,sp)
 686  00d7 95            	ld	xh,a
 687  00d8 cd0000        	call	_ADC1_ConversionConfig
 689  00db 84            	pop	a
 690                     ; 105   ADC1_PrescalerConfig(ADC1_PrescalerSelection);
 692  00dc 7b05          	ld	a,(OFST+5,sp)
 693  00de cd0000        	call	_ADC1_PrescalerConfig
 695                     ; 110   ADC1_ExternalTriggerConfig(ADC1_ExtTrigger, ADC1_ExtTriggerState);
 697  00e1 7b07          	ld	a,(OFST+7,sp)
 698  00e3 97            	ld	xl,a
 699  00e4 7b06          	ld	a,(OFST+6,sp)
 700  00e6 95            	ld	xh,a
 701  00e7 cd0000        	call	_ADC1_ExternalTriggerConfig
 703                     ; 115   ADC1_SchmittTriggerConfig(ADC1_SchmittTriggerChannel, ADC1_SchmittTriggerState);
 705  00ea 7b0a          	ld	a,(OFST+10,sp)
 706  00ec 97            	ld	xl,a
 707  00ed 7b09          	ld	a,(OFST+9,sp)
 708  00ef 95            	ld	xh,a
 709  00f0 cd0000        	call	_ADC1_SchmittTriggerConfig
 711                     ; 118   ADC1->CR1 |= ADC1_CR1_ADON;
 713  00f3 72105401      	bset	21505,#0
 714                     ; 119 }
 717  00f7 85            	popw	x
 718  00f8 81            	ret	
 719  00f9               LC001:
 720  00f9 89            	pushw	x
 721  00fa 5f            	clrw	x
 722  00fb 89            	pushw	x
 723  00fc ae0000        	ldw	x,#L542
 724  00ff cd0000        	call	_assert_failed
 726  0102 5b04          	addw	sp,#4
 727  0104 81            	ret	
 763                     ; 126 void ADC1_Cmd(FunctionalState NewState)
 763                     ; 127 {
 764                     .text:	section	.text,new
 765  0000               _ADC1_Cmd:
 767  0000 88            	push	a
 768       00000000      OFST:	set	0
 771                     ; 129   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 773  0001 4d            	tnz	a
 774  0002 2711          	jreq	L621
 775  0004 4a            	dec	a
 776  0005 270e          	jreq	L621
 777  0007 ae0081        	ldw	x,#129
 778  000a 89            	pushw	x
 779  000b 5f            	clrw	x
 780  000c 89            	pushw	x
 781  000d ae0000        	ldw	x,#L542
 782  0010 cd0000        	call	_assert_failed
 784  0013 5b04          	addw	sp,#4
 785  0015               L621:
 786                     ; 131   if (NewState != DISABLE)
 788  0015 7b01          	ld	a,(OFST+1,sp)
 789  0017 2706          	jreq	L562
 790                     ; 133     ADC1->CR1 |= ADC1_CR1_ADON;
 792  0019 72105401      	bset	21505,#0
 794  001d 2004          	jra	L762
 795  001f               L562:
 796                     ; 137     ADC1->CR1 &= (uint8_t)(~ADC1_CR1_ADON);
 798  001f 72115401      	bres	21505,#0
 799  0023               L762:
 800                     ; 139 }
 803  0023 84            	pop	a
 804  0024 81            	ret	
 840                     ; 146 void ADC1_ScanModeCmd(FunctionalState NewState)
 840                     ; 147 {
 841                     .text:	section	.text,new
 842  0000               _ADC1_ScanModeCmd:
 844  0000 88            	push	a
 845       00000000      OFST:	set	0
 848                     ; 149   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 850  0001 4d            	tnz	a
 851  0002 2711          	jreq	L041
 852  0004 4a            	dec	a
 853  0005 270e          	jreq	L041
 854  0007 ae0095        	ldw	x,#149
 855  000a 89            	pushw	x
 856  000b 5f            	clrw	x
 857  000c 89            	pushw	x
 858  000d ae0000        	ldw	x,#L542
 859  0010 cd0000        	call	_assert_failed
 861  0013 5b04          	addw	sp,#4
 862  0015               L041:
 863                     ; 151   if (NewState != DISABLE)
 865  0015 7b01          	ld	a,(OFST+1,sp)
 866  0017 2706          	jreq	L703
 867                     ; 153     ADC1->CR2 |= ADC1_CR2_SCAN;
 869  0019 72125402      	bset	21506,#1
 871  001d 2004          	jra	L113
 872  001f               L703:
 873                     ; 157     ADC1->CR2 &= (uint8_t)(~ADC1_CR2_SCAN);
 875  001f 72135402      	bres	21506,#1
 876  0023               L113:
 877                     ; 159 }
 880  0023 84            	pop	a
 881  0024 81            	ret	
 917                     ; 166 void ADC1_DataBufferCmd(FunctionalState NewState)
 917                     ; 167 {
 918                     .text:	section	.text,new
 919  0000               _ADC1_DataBufferCmd:
 921  0000 88            	push	a
 922       00000000      OFST:	set	0
 925                     ; 169   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 927  0001 4d            	tnz	a
 928  0002 2711          	jreq	L251
 929  0004 4a            	dec	a
 930  0005 270e          	jreq	L251
 931  0007 ae00a9        	ldw	x,#169
 932  000a 89            	pushw	x
 933  000b 5f            	clrw	x
 934  000c 89            	pushw	x
 935  000d ae0000        	ldw	x,#L542
 936  0010 cd0000        	call	_assert_failed
 938  0013 5b04          	addw	sp,#4
 939  0015               L251:
 940                     ; 171   if (NewState != DISABLE)
 942  0015 7b01          	ld	a,(OFST+1,sp)
 943  0017 2706          	jreq	L133
 944                     ; 173     ADC1->CR3 |= ADC1_CR3_DBUF;
 946  0019 721e5403      	bset	21507,#7
 948  001d 2004          	jra	L333
 949  001f               L133:
 950                     ; 177     ADC1->CR3 &= (uint8_t)(~ADC1_CR3_DBUF);
 952  001f 721f5403      	bres	21507,#7
 953  0023               L333:
 954                     ; 179 }
 957  0023 84            	pop	a
 958  0024 81            	ret	
1115                     ; 190 void ADC1_ITConfig(ADC1_IT_TypeDef ADC1_IT, FunctionalState NewState)
1115                     ; 191 {
1116                     .text:	section	.text,new
1117  0000               _ADC1_ITConfig:
1119  0000 89            	pushw	x
1120       00000000      OFST:	set	0
1123                     ; 193   assert_param(IS_ADC1_IT_OK(ADC1_IT));
1125  0001 a30020        	cpw	x,#32
1126  0004 270a          	jreq	L461
1127  0006 a30010        	cpw	x,#16
1128  0009 2705          	jreq	L461
1129  000b ae00c1        	ldw	x,#193
1130  000e ad22          	call	LC002
1131  0010               L461:
1132                     ; 194   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1134  0010 7b05          	ld	a,(OFST+5,sp)
1135  0012 2708          	jreq	L471
1136  0014 4a            	dec	a
1137  0015 2705          	jreq	L471
1138  0017 ae00c2        	ldw	x,#194
1139  001a ad16          	call	LC002
1140  001c               L471:
1141                     ; 196   if (NewState != DISABLE)
1143  001c 7b05          	ld	a,(OFST+5,sp)
1144  001e 2707          	jreq	L124
1145                     ; 199     ADC1->CSR |= (uint8_t)ADC1_IT;
1147  0020 c65400        	ld	a,21504
1148  0023 1a02          	or	a,(OFST+2,sp)
1150  0025 2006          	jra	L324
1151  0027               L124:
1152                     ; 204     ADC1->CSR &= (uint8_t)((uint16_t)~(uint16_t)ADC1_IT);
1154  0027 7b02          	ld	a,(OFST+2,sp)
1155  0029 43            	cpl	a
1156  002a c45400        	and	a,21504
1157  002d               L324:
1158  002d c75400        	ld	21504,a
1159                     ; 206 }
1162  0030 85            	popw	x
1163  0031 81            	ret	
1164  0032               LC002:
1165  0032 89            	pushw	x
1166  0033 5f            	clrw	x
1167  0034 89            	pushw	x
1168  0035 ae0000        	ldw	x,#L542
1169  0038 cd0000        	call	_assert_failed
1171  003b 5b04          	addw	sp,#4
1172  003d 81            	ret	
1209                     ; 214 void ADC1_PrescalerConfig(ADC1_PresSel_TypeDef ADC1_Prescaler)
1209                     ; 215 {
1210                     .text:	section	.text,new
1211  0000               _ADC1_PrescalerConfig:
1213  0000 88            	push	a
1214       00000000      OFST:	set	0
1217                     ; 217   assert_param(IS_ADC1_PRESSEL_OK(ADC1_Prescaler));
1219  0001 4d            	tnz	a
1220  0002 272a          	jreq	L602
1221  0004 a110          	cp	a,#16
1222  0006 2726          	jreq	L602
1223  0008 a120          	cp	a,#32
1224  000a 2722          	jreq	L602
1225  000c a130          	cp	a,#48
1226  000e 271e          	jreq	L602
1227  0010 a140          	cp	a,#64
1228  0012 271a          	jreq	L602
1229  0014 a150          	cp	a,#80
1230  0016 2716          	jreq	L602
1231  0018 a160          	cp	a,#96
1232  001a 2712          	jreq	L602
1233  001c a170          	cp	a,#112
1234  001e 270e          	jreq	L602
1235  0020 ae00d9        	ldw	x,#217
1236  0023 89            	pushw	x
1237  0024 5f            	clrw	x
1238  0025 89            	pushw	x
1239  0026 ae0000        	ldw	x,#L542
1240  0029 cd0000        	call	_assert_failed
1242  002c 5b04          	addw	sp,#4
1243  002e               L602:
1244                     ; 220   ADC1->CR1 &= (uint8_t)(~ADC1_CR1_SPSEL);
1246  002e c65401        	ld	a,21505
1247  0031 a48f          	and	a,#143
1248  0033 c75401        	ld	21505,a
1249                     ; 222   ADC1->CR1 |= (uint8_t)(ADC1_Prescaler);
1251  0036 c65401        	ld	a,21505
1252  0039 1a01          	or	a,(OFST+1,sp)
1253  003b c75401        	ld	21505,a
1254                     ; 223 }
1257  003e 84            	pop	a
1258  003f 81            	ret	
1306                     ; 233 void ADC1_SchmittTriggerConfig(ADC1_SchmittTrigg_TypeDef ADC1_SchmittTriggerChannel, FunctionalState NewState)
1306                     ; 234 {
1307                     .text:	section	.text,new
1308  0000               _ADC1_SchmittTriggerConfig:
1310  0000 89            	pushw	x
1311       00000000      OFST:	set	0
1314                     ; 236   assert_param(IS_ADC1_SCHMITTTRIG_OK(ADC1_SchmittTriggerChannel));
1316  0001 9e            	ld	a,xh
1317  0002 4d            	tnz	a
1318  0003 273b          	jreq	L022
1319  0005 9e            	ld	a,xh
1320  0006 4a            	dec	a
1321  0007 2737          	jreq	L022
1322  0009 9e            	ld	a,xh
1323  000a a102          	cp	a,#2
1324  000c 2732          	jreq	L022
1325  000e 9e            	ld	a,xh
1326  000f a103          	cp	a,#3
1327  0011 272d          	jreq	L022
1328  0013 9e            	ld	a,xh
1329  0014 a104          	cp	a,#4
1330  0016 2728          	jreq	L022
1331  0018 9e            	ld	a,xh
1332  0019 a105          	cp	a,#5
1333  001b 2723          	jreq	L022
1334  001d 9e            	ld	a,xh
1335  001e a106          	cp	a,#6
1336  0020 271e          	jreq	L022
1337  0022 9e            	ld	a,xh
1338  0023 a107          	cp	a,#7
1339  0025 2719          	jreq	L022
1340  0027 9e            	ld	a,xh
1341  0028 a108          	cp	a,#8
1342  002a 2714          	jreq	L022
1343  002c 9e            	ld	a,xh
1344  002d a10c          	cp	a,#12
1345  002f 270f          	jreq	L022
1346  0031 9e            	ld	a,xh
1347  0032 4c            	inc	a
1348  0033 270b          	jreq	L022
1349  0035 9e            	ld	a,xh
1350  0036 a109          	cp	a,#9
1351  0038 2706          	jreq	L022
1352  003a ae00ec        	ldw	x,#236
1353  003d cd00bf        	call	LC006
1354  0040               L022:
1355                     ; 237   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1357  0040 7b02          	ld	a,(OFST+2,sp)
1358  0042 2708          	jreq	L032
1359  0044 4a            	dec	a
1360  0045 2705          	jreq	L032
1361  0047 ae00ed        	ldw	x,#237
1362  004a ad73          	call	LC006
1363  004c               L032:
1364                     ; 239   if (ADC1_SchmittTriggerChannel == ADC1_SCHMITTTRIG_ALL)
1366  004c 7b01          	ld	a,(OFST+1,sp)
1367  004e a1ff          	cp	a,#255
1368  0050 261d          	jrne	L564
1369                     ; 241     if (NewState != DISABLE)
1371  0052 7b02          	ld	a,(OFST+2,sp)
1372  0054 270a          	jreq	L764
1373                     ; 243       ADC1->TDRL &= (uint8_t)0x0;
1375  0056 725f5407      	clr	21511
1376                     ; 244       ADC1->TDRH &= (uint8_t)0x0;
1378  005a 725f5406      	clr	21510
1380  005e 2057          	jra	L374
1381  0060               L764:
1382                     ; 248       ADC1->TDRL |= (uint8_t)0xFF;
1384  0060 c65407        	ld	a,21511
1385  0063 aaff          	or	a,#255
1386  0065 c75407        	ld	21511,a
1387                     ; 249       ADC1->TDRH |= (uint8_t)0xFF;
1389  0068 c65406        	ld	a,21510
1390  006b aaff          	or	a,#255
1391  006d 2045          	jp	LC003
1392  006f               L564:
1393                     ; 252   else if (ADC1_SchmittTriggerChannel < ADC1_SCHMITTTRIG_CHANNEL8)
1395  006f a108          	cp	a,#8
1396  0071 0d02          	tnz	(OFST+2,sp)
1397  0073 2420          	jruge	L574
1398                     ; 254     if (NewState != DISABLE)
1400  0075 2711          	jreq	L774
1401                     ; 256       ADC1->TDRL &= (uint8_t)(~(uint8_t)((uint8_t)0x01 << (uint8_t)ADC1_SchmittTriggerChannel));
1403  0077 ad40          	call	LC005
1404  0079 2704          	jreq	L432
1405  007b               L632:
1406  007b 48            	sll	a
1407  007c 5a            	decw	x
1408  007d 26fc          	jrne	L632
1409  007f               L432:
1410  007f 43            	cpl	a
1411  0080 c45407        	and	a,21511
1412  0083               LC004:
1413  0083 c75407        	ld	21511,a
1415  0086 202f          	jra	L374
1416  0088               L774:
1417                     ; 260       ADC1->TDRL |= (uint8_t)((uint8_t)0x01 << (uint8_t)ADC1_SchmittTriggerChannel);
1419  0088 ad2f          	call	LC005
1420  008a 2704          	jreq	L042
1421  008c               L242:
1422  008c 48            	sll	a
1423  008d 5a            	decw	x
1424  008e 26fc          	jrne	L242
1425  0090               L042:
1426  0090 ca5407        	or	a,21511
1427  0093 20ee          	jp	LC004
1428  0095               L574:
1429                     ; 265     if (NewState != DISABLE)
1431  0095 2710          	jreq	L505
1432                     ; 267       ADC1->TDRH &= (uint8_t)(~(uint8_t)((uint8_t)0x01 << ((uint8_t)ADC1_SchmittTriggerChannel - (uint8_t)8)));
1434  0097 a008          	sub	a,#8
1435  0099 ad1e          	call	LC005
1436  009b 2704          	jreq	L442
1437  009d               L642:
1438  009d 48            	sll	a
1439  009e 5a            	decw	x
1440  009f 26fc          	jrne	L642
1441  00a1               L442:
1442  00a1 43            	cpl	a
1443  00a2 c45406        	and	a,21510
1445  00a5 200d          	jp	LC003
1446  00a7               L505:
1447                     ; 271       ADC1->TDRH |= (uint8_t)((uint8_t)0x01 << ((uint8_t)ADC1_SchmittTriggerChannel - (uint8_t)8));
1449  00a7 a008          	sub	a,#8
1450  00a9 ad0e          	call	LC005
1451  00ab 2704          	jreq	L052
1452  00ad               L252:
1453  00ad 48            	sll	a
1454  00ae 5a            	decw	x
1455  00af 26fc          	jrne	L252
1456  00b1               L052:
1457  00b1 ca5406        	or	a,21510
1458  00b4               LC003:
1459  00b4 c75406        	ld	21510,a
1460  00b7               L374:
1461                     ; 274 }
1464  00b7 85            	popw	x
1465  00b8 81            	ret	
1466  00b9               LC005:
1467  00b9 5f            	clrw	x
1468  00ba 97            	ld	xl,a
1469  00bb a601          	ld	a,#1
1470  00bd 5d            	tnzw	x
1471  00be 81            	ret	
1472  00bf               LC006:
1473  00bf 89            	pushw	x
1474  00c0 5f            	clrw	x
1475  00c1 89            	pushw	x
1476  00c2 ae0000        	ldw	x,#L542
1477  00c5 cd0000        	call	_assert_failed
1479  00c8 5b04          	addw	sp,#4
1480  00ca 81            	ret	
1538                     ; 286 void ADC1_ConversionConfig(ADC1_ConvMode_TypeDef ADC1_ConversionMode, ADC1_Channel_TypeDef ADC1_Channel, ADC1_Align_TypeDef ADC1_Align)
1538                     ; 287 {
1539                     .text:	section	.text,new
1540  0000               _ADC1_ConversionConfig:
1542  0000 89            	pushw	x
1543       00000000      OFST:	set	0
1546                     ; 289   assert_param(IS_ADC1_CONVERSIONMODE_OK(ADC1_ConversionMode));
1548  0001 9e            	ld	a,xh
1549  0002 4d            	tnz	a
1550  0003 2709          	jreq	L262
1551  0005 9e            	ld	a,xh
1552  0006 4a            	dec	a
1553  0007 2705          	jreq	L262
1554  0009 ae0121        	ldw	x,#289
1555  000c ad6b          	call	LC007
1556  000e               L262:
1557                     ; 290   assert_param(IS_ADC1_CHANNEL_OK(ADC1_Channel));
1559  000e 7b02          	ld	a,(OFST+2,sp)
1560  0010 272d          	jreq	L272
1561  0012 a101          	cp	a,#1
1562  0014 2729          	jreq	L272
1563  0016 a102          	cp	a,#2
1564  0018 2725          	jreq	L272
1565  001a a103          	cp	a,#3
1566  001c 2721          	jreq	L272
1567  001e a104          	cp	a,#4
1568  0020 271d          	jreq	L272
1569  0022 a105          	cp	a,#5
1570  0024 2719          	jreq	L272
1571  0026 a106          	cp	a,#6
1572  0028 2715          	jreq	L272
1573  002a a107          	cp	a,#7
1574  002c 2711          	jreq	L272
1575  002e a108          	cp	a,#8
1576  0030 270d          	jreq	L272
1577  0032 a10c          	cp	a,#12
1578  0034 2709          	jreq	L272
1579  0036 a109          	cp	a,#9
1580  0038 2705          	jreq	L272
1581  003a ae0122        	ldw	x,#290
1582  003d ad3a          	call	LC007
1583  003f               L272:
1584                     ; 291   assert_param(IS_ADC1_ALIGN_OK(ADC1_Align));
1586  003f 7b05          	ld	a,(OFST+5,sp)
1587  0041 2709          	jreq	L203
1588  0043 a108          	cp	a,#8
1589  0045 2705          	jreq	L203
1590  0047 ae0123        	ldw	x,#291
1591  004a ad2d          	call	LC007
1592  004c               L203:
1593                     ; 294   ADC1->CR2 &= (uint8_t)(~ADC1_CR2_ALIGN);
1595  004c 72175402      	bres	21506,#3
1596                     ; 296   ADC1->CR2 |= (uint8_t)(ADC1_Align);
1598  0050 c65402        	ld	a,21506
1599  0053 1a05          	or	a,(OFST+5,sp)
1600  0055 c75402        	ld	21506,a
1601                     ; 298   if (ADC1_ConversionMode == ADC1_CONVERSIONMODE_CONTINUOUS)
1603  0058 7b01          	ld	a,(OFST+1,sp)
1604  005a 4a            	dec	a
1605  005b 2606          	jrne	L735
1606                     ; 301     ADC1->CR1 |= ADC1_CR1_CONT;
1608  005d 72125401      	bset	21505,#1
1610  0061 2004          	jra	L145
1611  0063               L735:
1612                     ; 306     ADC1->CR1 &= (uint8_t)(~ADC1_CR1_CONT);
1614  0063 72135401      	bres	21505,#1
1615  0067               L145:
1616                     ; 310   ADC1->CSR &= (uint8_t)(~ADC1_CSR_CH);
1618  0067 c65400        	ld	a,21504
1619  006a a4f0          	and	a,#240
1620  006c c75400        	ld	21504,a
1621                     ; 312   ADC1->CSR |= (uint8_t)(ADC1_Channel);
1623  006f c65400        	ld	a,21504
1624  0072 1a02          	or	a,(OFST+2,sp)
1625  0074 c75400        	ld	21504,a
1626                     ; 313 }
1629  0077 85            	popw	x
1630  0078 81            	ret	
1631  0079               LC007:
1632  0079 89            	pushw	x
1633  007a 5f            	clrw	x
1634  007b 89            	pushw	x
1635  007c ae0000        	ldw	x,#L542
1636  007f cd0000        	call	_assert_failed
1638  0082 5b04          	addw	sp,#4
1639  0084 81            	ret	
1686                     ; 325 void ADC1_ExternalTriggerConfig(ADC1_ExtTrig_TypeDef ADC1_ExtTrigger, FunctionalState NewState)
1686                     ; 326 {
1687                     .text:	section	.text,new
1688  0000               _ADC1_ExternalTriggerConfig:
1690  0000 89            	pushw	x
1691       00000000      OFST:	set	0
1694                     ; 328   assert_param(IS_ADC1_EXTTRIG_OK(ADC1_ExtTrigger));
1696  0001 9e            	ld	a,xh
1697  0002 4d            	tnz	a
1698  0003 270a          	jreq	L413
1699  0005 9e            	ld	a,xh
1700  0006 a110          	cp	a,#16
1701  0008 2705          	jreq	L413
1702  000a ae0148        	ldw	x,#328
1703  000d ad2c          	call	LC008
1704  000f               L413:
1705                     ; 329   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1707  000f 7b02          	ld	a,(OFST+2,sp)
1708  0011 2708          	jreq	L423
1709  0013 4a            	dec	a
1710  0014 2705          	jreq	L423
1711  0016 ae0149        	ldw	x,#329
1712  0019 ad20          	call	LC008
1713  001b               L423:
1714                     ; 332   ADC1->CR2 &= (uint8_t)(~ADC1_CR2_EXTSEL);
1716  001b c65402        	ld	a,21506
1717  001e a4cf          	and	a,#207
1718  0020 c75402        	ld	21506,a
1719                     ; 334   if (NewState != DISABLE)
1721  0023 7b02          	ld	a,(OFST+2,sp)
1722  0025 2706          	jreq	L565
1723                     ; 337     ADC1->CR2 |= (uint8_t)(ADC1_CR2_EXTTRIG);
1725  0027 721c5402      	bset	21506,#6
1727  002b 2004          	jra	L765
1728  002d               L565:
1729                     ; 342     ADC1->CR2 &= (uint8_t)(~ADC1_CR2_EXTTRIG);
1731  002d 721d5402      	bres	21506,#6
1732  0031               L765:
1733                     ; 346   ADC1->CR2 |= (uint8_t)(ADC1_ExtTrigger);
1735  0031 c65402        	ld	a,21506
1736  0034 1a01          	or	a,(OFST+1,sp)
1737  0036 c75402        	ld	21506,a
1738                     ; 347 }
1741  0039 85            	popw	x
1742  003a 81            	ret	
1743  003b               LC008:
1744  003b 89            	pushw	x
1745  003c 5f            	clrw	x
1746  003d 89            	pushw	x
1747  003e ae0000        	ldw	x,#L542
1748  0041 cd0000        	call	_assert_failed
1750  0044 5b04          	addw	sp,#4
1751  0046 81            	ret	
1775                     ; 358 void ADC1_StartConversion(void)
1775                     ; 359 {
1776                     .text:	section	.text,new
1777  0000               _ADC1_StartConversion:
1781                     ; 360   ADC1->CR1 |= ADC1_CR1_ADON;
1783  0000 72105401      	bset	21505,#0
1784                     ; 361 }
1787  0004 81            	ret	
1831                     ; 370 uint16_t ADC1_GetConversionValue(void)
1831                     ; 371 {
1832                     .text:	section	.text,new
1833  0000               _ADC1_GetConversionValue:
1835  0000 5205          	subw	sp,#5
1836       00000005      OFST:	set	5
1839                     ; 372   uint16_t temph = 0;
1841                     ; 373   uint8_t templ = 0;
1843                     ; 375   if ((ADC1->CR2 & ADC1_CR2_ALIGN) != 0) /* Right alignment */
1845  0002 720754020e    	btjf	21506,#3,L326
1846                     ; 378     templ = ADC1->DRL;
1848  0007 c65405        	ld	a,21509
1849  000a 6b03          	ld	(OFST-2,sp),a
1851                     ; 380     temph = ADC1->DRH;
1853  000c c65404        	ld	a,21508
1854  000f 97            	ld	xl,a
1856                     ; 382     temph = (uint16_t)(templ | (uint16_t)(temph << (uint8_t)8));
1858  0010 7b03          	ld	a,(OFST-2,sp)
1859  0012 02            	rlwa	x,a
1862  0013 201a          	jra	L526
1863  0015               L326:
1864                     ; 387     temph = ADC1->DRH;
1866  0015 c65404        	ld	a,21508
1867  0018 97            	ld	xl,a
1869                     ; 389     templ = ADC1->DRL;
1871  0019 c65405        	ld	a,21509
1872  001c 6b03          	ld	(OFST-2,sp),a
1874                     ; 391     temph = (uint16_t)((uint16_t)((uint16_t)templ << 6) | (uint16_t)((uint16_t)temph << 8));
1876  001e 4f            	clr	a
1877  001f 02            	rlwa	x,a
1878  0020 1f01          	ldw	(OFST-4,sp),x
1880  0022 7b03          	ld	a,(OFST-2,sp)
1881  0024 97            	ld	xl,a
1882  0025 a640          	ld	a,#64
1883  0027 42            	mul	x,a
1884  0028 01            	rrwa	x,a
1885  0029 1a02          	or	a,(OFST-3,sp)
1886  002b 01            	rrwa	x,a
1887  002c 1a01          	or	a,(OFST-4,sp)
1888  002e 01            	rrwa	x,a
1890  002f               L526:
1891                     ; 394   return ((uint16_t)temph);
1895  002f 5b05          	addw	sp,#5
1896  0031 81            	ret	
1943                     ; 405 void ADC1_AWDChannelConfig(ADC1_Channel_TypeDef Channel, FunctionalState NewState)
1943                     ; 406 {
1944                     .text:	section	.text,new
1945  0000               _ADC1_AWDChannelConfig:
1947  0000 89            	pushw	x
1948       00000000      OFST:	set	0
1951                     ; 408   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1953  0001 9f            	ld	a,xl
1954  0002 4d            	tnz	a
1955  0003 270a          	jreq	L243
1956  0005 9f            	ld	a,xl
1957  0006 4a            	dec	a
1958  0007 2706          	jreq	L243
1959  0009 ae0198        	ldw	x,#408
1960  000c cd0092        	call	LC012
1961  000f               L243:
1962                     ; 409   assert_param(IS_ADC1_CHANNEL_OK(Channel));
1964  000f 7b01          	ld	a,(OFST+1,sp)
1965  0011 272f          	jreq	L253
1966  0013 a101          	cp	a,#1
1967  0015 272b          	jreq	L253
1968  0017 a102          	cp	a,#2
1969  0019 2727          	jreq	L253
1970  001b a103          	cp	a,#3
1971  001d 2723          	jreq	L253
1972  001f a104          	cp	a,#4
1973  0021 271f          	jreq	L253
1974  0023 a105          	cp	a,#5
1975  0025 271b          	jreq	L253
1976  0027 a106          	cp	a,#6
1977  0029 2717          	jreq	L253
1978  002b a107          	cp	a,#7
1979  002d 2713          	jreq	L253
1980  002f a108          	cp	a,#8
1981  0031 270f          	jreq	L253
1982  0033 a10c          	cp	a,#12
1983  0035 270b          	jreq	L253
1984  0037 a109          	cp	a,#9
1985  0039 2707          	jreq	L253
1986  003b ae0199        	ldw	x,#409
1987  003e ad52          	call	LC012
1988  0040 7b01          	ld	a,(OFST+1,sp)
1989  0042               L253:
1990                     ; 411   if (Channel < (uint8_t)8)
1992  0042 a108          	cp	a,#8
1993  0044 0d02          	tnz	(OFST+2,sp)
1994  0046 2420          	jruge	L156
1995                     ; 413     if (NewState != DISABLE)
1997  0048 270d          	jreq	L356
1998                     ; 415       ADC1->AWCRL |= (uint8_t)((uint8_t)1 << Channel);
2000  004a ad40          	call	LC011
2001  004c 2704          	jreq	L653
2002  004e               L063:
2003  004e 48            	sll	a
2004  004f 5a            	decw	x
2005  0050 26fc          	jrne	L063
2006  0052               L653:
2007  0052 ca540f        	or	a,21519
2009  0055 200c          	jp	LC010
2010  0057               L356:
2011                     ; 419       ADC1->AWCRL &= (uint8_t)~(uint8_t)((uint8_t)1 << Channel);
2013  0057 ad33          	call	LC011
2014  0059 2704          	jreq	L263
2015  005b               L463:
2016  005b 48            	sll	a
2017  005c 5a            	decw	x
2018  005d 26fc          	jrne	L463
2019  005f               L263:
2020  005f 43            	cpl	a
2021  0060 c4540f        	and	a,21519
2022  0063               LC010:
2023  0063 c7540f        	ld	21519,a
2024  0066 2022          	jra	L756
2025  0068               L156:
2026                     ; 424     if (NewState != DISABLE)
2028  0068 270f          	jreq	L166
2029                     ; 426       ADC1->AWCRH |= (uint8_t)((uint8_t)1 << (Channel - (uint8_t)8));
2031  006a a008          	sub	a,#8
2032  006c ad1e          	call	LC011
2033  006e 2704          	jreq	L663
2034  0070               L073:
2035  0070 48            	sll	a
2036  0071 5a            	decw	x
2037  0072 26fc          	jrne	L073
2038  0074               L663:
2039  0074 ca540e        	or	a,21518
2041  0077 200e          	jp	LC009
2042  0079               L166:
2043                     ; 430       ADC1->AWCRH &= (uint8_t)~(uint8_t)((uint8_t)1 << (uint8_t)(Channel - (uint8_t)8));
2045  0079 a008          	sub	a,#8
2046  007b ad0f          	call	LC011
2047  007d 2704          	jreq	L273
2048  007f               L473:
2049  007f 48            	sll	a
2050  0080 5a            	decw	x
2051  0081 26fc          	jrne	L473
2052  0083               L273:
2053  0083 43            	cpl	a
2054  0084 c4540e        	and	a,21518
2055  0087               LC009:
2056  0087 c7540e        	ld	21518,a
2057  008a               L756:
2058                     ; 433 }
2061  008a 85            	popw	x
2062  008b 81            	ret	
2063  008c               LC011:
2064  008c 5f            	clrw	x
2065  008d 97            	ld	xl,a
2066  008e a601          	ld	a,#1
2067  0090 5d            	tnzw	x
2068  0091 81            	ret	
2069  0092               LC012:
2070  0092 89            	pushw	x
2071  0093 5f            	clrw	x
2072  0094 89            	pushw	x
2073  0095 ae0000        	ldw	x,#L542
2074  0098 cd0000        	call	_assert_failed
2076  009b 5b04          	addw	sp,#4
2077  009d 81            	ret	
2112                     ; 441 void ADC1_SetHighThreshold(uint16_t Threshold)
2112                     ; 442 {
2113                     .text:	section	.text,new
2114  0000               _ADC1_SetHighThreshold:
2116  0000 89            	pushw	x
2117       00000000      OFST:	set	0
2120                     ; 443   ADC1->HTRH = (uint8_t)(Threshold >> (uint8_t)2);
2122  0001 54            	srlw	x
2123  0002 54            	srlw	x
2124  0003 9f            	ld	a,xl
2125  0004 c75408        	ld	21512,a
2126                     ; 444   ADC1->HTRL = (uint8_t)Threshold;
2128  0007 7b02          	ld	a,(OFST+2,sp)
2129  0009 c75409        	ld	21513,a
2130                     ; 445 }
2133  000c 85            	popw	x
2134  000d 81            	ret	
2169                     ; 453 void ADC1_SetLowThreshold(uint16_t Threshold)
2169                     ; 454 {
2170                     .text:	section	.text,new
2171  0000               _ADC1_SetLowThreshold:
2175                     ; 455   ADC1->LTRL = (uint8_t)Threshold;
2177  0000 9f            	ld	a,xl
2178  0001 c7540b        	ld	21515,a
2179                     ; 456   ADC1->LTRH = (uint8_t)(Threshold >> (uint8_t)2);
2181  0004 54            	srlw	x
2182  0005 54            	srlw	x
2183  0006 9f            	ld	a,xl
2184  0007 c7540a        	ld	21514,a
2185                     ; 457 }
2188  000a 81            	ret	
2242                     ; 466 uint16_t ADC1_GetBufferValue(uint8_t Buffer)
2242                     ; 467 {
2243                     .text:	section	.text,new
2244  0000               _ADC1_GetBufferValue:
2246  0000 88            	push	a
2247  0001 5205          	subw	sp,#5
2248       00000005      OFST:	set	5
2251                     ; 468   uint16_t temph = 0;
2253                     ; 469   uint8_t templ = 0;
2255                     ; 472   assert_param(IS_ADC1_BUFFER_OK(Buffer));
2257  0003 a10a          	cp	a,#10
2258  0005 250e          	jrult	L604
2259  0007 ae01d8        	ldw	x,#472
2260  000a 89            	pushw	x
2261  000b 5f            	clrw	x
2262  000c 89            	pushw	x
2263  000d ae0000        	ldw	x,#L542
2264  0010 cd0000        	call	_assert_failed
2266  0013 5b04          	addw	sp,#4
2267  0015               L604:
2268                     ; 474   if ((ADC1->CR2 & ADC1_CR2_ALIGN) != 0) /* Right alignment */
2270  0015 7b06          	ld	a,(OFST+1,sp)
2271  0017 48            	sll	a
2272  0018 5f            	clrw	x
2273  0019 97            	ld	xl,a
2274  001a 7207540213    	btjf	21506,#3,L747
2275                     ; 477     templ = *(uint8_t*)(uint16_t)((uint16_t)ADC1_BaseAddress + (uint8_t)(Buffer << 1) + 1);
2277  001f d653e1        	ld	a,(21473,x)
2278  0022 6b03          	ld	(OFST-2,sp),a
2280                     ; 479     temph = *(uint8_t*)(uint16_t)((uint16_t)ADC1_BaseAddress + (uint8_t)(Buffer << 1));
2282  0024 7b06          	ld	a,(OFST+1,sp)
2283  0026 48            	sll	a
2284  0027 5f            	clrw	x
2285  0028 97            	ld	xl,a
2286  0029 d653e0        	ld	a,(21472,x)
2287  002c 97            	ld	xl,a
2289                     ; 481     temph = (uint16_t)(templ | (uint16_t)(temph << (uint8_t)8));
2291  002d 7b03          	ld	a,(OFST-2,sp)
2292  002f 02            	rlwa	x,a
2295  0030 2024          	jra	L157
2296  0032               L747:
2297                     ; 486     temph = *(uint8_t*)(uint16_t)((uint16_t)ADC1_BaseAddress + (uint8_t)(Buffer << 1));
2299  0032 d653e0        	ld	a,(21472,x)
2300  0035 5f            	clrw	x
2301  0036 97            	ld	xl,a
2302  0037 1f04          	ldw	(OFST-1,sp),x
2304                     ; 488     templ = *(uint8_t*)(uint16_t)((uint16_t)ADC1_BaseAddress + (uint8_t)(Buffer << 1) + 1);
2306  0039 7b06          	ld	a,(OFST+1,sp)
2307  003b 48            	sll	a
2308  003c 5f            	clrw	x
2309  003d 97            	ld	xl,a
2310  003e d653e1        	ld	a,(21473,x)
2311  0041 6b03          	ld	(OFST-2,sp),a
2313                     ; 490     temph = (uint16_t)((uint16_t)((uint16_t)templ << 6) | (uint16_t)(temph << 8));
2315  0043 4f            	clr	a
2316  0044 1e04          	ldw	x,(OFST-1,sp)
2317  0046 02            	rlwa	x,a
2318  0047 1f01          	ldw	(OFST-4,sp),x
2320  0049 7b03          	ld	a,(OFST-2,sp)
2321  004b 97            	ld	xl,a
2322  004c a640          	ld	a,#64
2323  004e 42            	mul	x,a
2324  004f 01            	rrwa	x,a
2325  0050 1a02          	or	a,(OFST-3,sp)
2326  0052 01            	rrwa	x,a
2327  0053 1a01          	or	a,(OFST-4,sp)
2328  0055 01            	rrwa	x,a
2330  0056               L157:
2331                     ; 493   return ((uint16_t)temph);
2335  0056 5b06          	addw	sp,#6
2336  0058 81            	ret	
2403                     ; 502 FlagStatus ADC1_GetAWDChannelStatus(ADC1_Channel_TypeDef Channel)
2403                     ; 503 {
2404                     .text:	section	.text,new
2405  0000               _ADC1_GetAWDChannelStatus:
2407  0000 88            	push	a
2408  0001 88            	push	a
2409       00000001      OFST:	set	1
2412                     ; 504   uint8_t status = 0;
2414                     ; 507   assert_param(IS_ADC1_CHANNEL_OK(Channel));
2416  0002 4d            	tnz	a
2417  0003 2736          	jreq	L024
2418  0005 a101          	cp	a,#1
2419  0007 2732          	jreq	L024
2420  0009 a102          	cp	a,#2
2421  000b 272e          	jreq	L024
2422  000d a103          	cp	a,#3
2423  000f 272a          	jreq	L024
2424  0011 a104          	cp	a,#4
2425  0013 2726          	jreq	L024
2426  0015 a105          	cp	a,#5
2427  0017 2722          	jreq	L024
2428  0019 a106          	cp	a,#6
2429  001b 271e          	jreq	L024
2430  001d a107          	cp	a,#7
2431  001f 271a          	jreq	L024
2432  0021 a108          	cp	a,#8
2433  0023 2716          	jreq	L024
2434  0025 a10c          	cp	a,#12
2435  0027 2712          	jreq	L024
2436  0029 a109          	cp	a,#9
2437  002b 270e          	jreq	L024
2438  002d ae01fb        	ldw	x,#507
2439  0030 89            	pushw	x
2440  0031 5f            	clrw	x
2441  0032 89            	pushw	x
2442  0033 ae0000        	ldw	x,#L542
2443  0036 cd0000        	call	_assert_failed
2445  0039 5b04          	addw	sp,#4
2446  003b               L024:
2447                     ; 509   if (Channel < (uint8_t)8)
2449  003b 7b02          	ld	a,(OFST+1,sp)
2450  003d a108          	cp	a,#8
2451  003f 2410          	jruge	L5001
2452                     ; 511     status = (uint8_t)(ADC1->AWSRL & (uint8_t)((uint8_t)1 << Channel));
2454  0041 5f            	clrw	x
2455  0042 97            	ld	xl,a
2456  0043 a601          	ld	a,#1
2457  0045 5d            	tnzw	x
2458  0046 2704          	jreq	L424
2459  0048               L624:
2460  0048 48            	sll	a
2461  0049 5a            	decw	x
2462  004a 26fc          	jrne	L624
2463  004c               L424:
2464  004c c4540d        	and	a,21517
2467  004f 2010          	jra	L7001
2468  0051               L5001:
2469                     ; 515     status = (uint8_t)(ADC1->AWSRH & (uint8_t)((uint8_t)1 << (Channel - (uint8_t)8)));
2471  0051 a008          	sub	a,#8
2472  0053 5f            	clrw	x
2473  0054 97            	ld	xl,a
2474  0055 a601          	ld	a,#1
2475  0057 5d            	tnzw	x
2476  0058 2704          	jreq	L034
2477  005a               L234:
2478  005a 48            	sll	a
2479  005b 5a            	decw	x
2480  005c 26fc          	jrne	L234
2481  005e               L034:
2482  005e c4540c        	and	a,21516
2484  0061               L7001:
2485                     ; 518   return ((FlagStatus)status);
2489  0061 85            	popw	x
2490  0062 81            	ret	
2649                     ; 527 FlagStatus ADC1_GetFlagStatus(ADC1_Flag_TypeDef Flag)
2649                     ; 528 {
2650                     .text:	section	.text,new
2651  0000               _ADC1_GetFlagStatus:
2653  0000 88            	push	a
2654  0001 88            	push	a
2655       00000001      OFST:	set	1
2658                     ; 529   uint8_t flagstatus = 0;
2660                     ; 530   uint8_t temp = 0;
2662                     ; 533   assert_param(IS_ADC1_FLAG_OK(Flag));
2664  0002 a180          	cp	a,#128
2665  0004 273e          	jreq	L244
2666  0006 a141          	cp	a,#65
2667  0008 273a          	jreq	L244
2668  000a a140          	cp	a,#64
2669  000c 2736          	jreq	L244
2670  000e a110          	cp	a,#16
2671  0010 2732          	jreq	L244
2672  0012 a111          	cp	a,#17
2673  0014 272e          	jreq	L244
2674  0016 a112          	cp	a,#18
2675  0018 272a          	jreq	L244
2676  001a a113          	cp	a,#19
2677  001c 2726          	jreq	L244
2678  001e a114          	cp	a,#20
2679  0020 2722          	jreq	L244
2680  0022 a115          	cp	a,#21
2681  0024 271e          	jreq	L244
2682  0026 a116          	cp	a,#22
2683  0028 271a          	jreq	L244
2684  002a a117          	cp	a,#23
2685  002c 2716          	jreq	L244
2686  002e a118          	cp	a,#24
2687  0030 2712          	jreq	L244
2688  0032 a119          	cp	a,#25
2689  0034 270e          	jreq	L244
2690  0036 ae0215        	ldw	x,#533
2691  0039 89            	pushw	x
2692  003a 5f            	clrw	x
2693  003b 89            	pushw	x
2694  003c ae0000        	ldw	x,#L542
2695  003f cd0000        	call	_assert_failed
2697  0042 5b04          	addw	sp,#4
2698  0044               L244:
2699                     ; 535   if ((Flag & 0x0F) == 0x01)
2701  0044 7b02          	ld	a,(OFST+1,sp)
2702  0046 a40f          	and	a,#15
2703  0048 4a            	dec	a
2704  0049 2607          	jrne	L7701
2705                     ; 538     flagstatus = (uint8_t)(ADC1->CR3 & ADC1_CR3_OVR);
2707  004b c65403        	ld	a,21507
2708  004e a440          	and	a,#64
2711  0050 2039          	jra	L1011
2712  0052               L7701:
2713                     ; 540   else if ((Flag & 0xF0) == 0x10)
2715  0052 7b02          	ld	a,(OFST+1,sp)
2716  0054 a4f0          	and	a,#240
2717  0056 a110          	cp	a,#16
2718  0058 262c          	jrne	L3011
2719                     ; 543     temp = (uint8_t)(Flag & (uint8_t)0x0F);
2721  005a 7b02          	ld	a,(OFST+1,sp)
2722  005c a40f          	and	a,#15
2723  005e 6b01          	ld	(OFST+0,sp),a
2725                     ; 544     if (temp < 8)
2727  0060 a108          	cp	a,#8
2728  0062 2410          	jruge	L5011
2729                     ; 546       flagstatus = (uint8_t)(ADC1->AWSRL & (uint8_t)((uint8_t)1 << temp));
2731  0064 5f            	clrw	x
2732  0065 97            	ld	xl,a
2733  0066 a601          	ld	a,#1
2734  0068 5d            	tnzw	x
2735  0069 2704          	jreq	L644
2736  006b               L054:
2737  006b 48            	sll	a
2738  006c 5a            	decw	x
2739  006d 26fc          	jrne	L054
2740  006f               L644:
2741  006f c4540d        	and	a,21517
2744  0072 2017          	jra	L1011
2745  0074               L5011:
2746                     ; 550       flagstatus = (uint8_t)(ADC1->AWSRH & (uint8_t)((uint8_t)1 << (temp - 8)));
2748  0074 a008          	sub	a,#8
2749  0076 5f            	clrw	x
2750  0077 97            	ld	xl,a
2751  0078 a601          	ld	a,#1
2752  007a 5d            	tnzw	x
2753  007b 2704          	jreq	L254
2754  007d               L454:
2755  007d 48            	sll	a
2756  007e 5a            	decw	x
2757  007f 26fc          	jrne	L454
2758  0081               L254:
2759  0081 c4540c        	and	a,21516
2761  0084 2005          	jra	L1011
2762  0086               L3011:
2763                     ; 555     flagstatus = (uint8_t)(ADC1->CSR & Flag);
2765  0086 c65400        	ld	a,21504
2766  0089 1402          	and	a,(OFST+1,sp)
2768  008b               L1011:
2769                     ; 557   return ((FlagStatus)flagstatus);
2773  008b 85            	popw	x
2774  008c 81            	ret	
2819                     ; 567 void ADC1_ClearFlag(ADC1_Flag_TypeDef Flag)
2819                     ; 568 {
2820                     .text:	section	.text,new
2821  0000               _ADC1_ClearFlag:
2823  0000 88            	push	a
2824  0001 88            	push	a
2825       00000001      OFST:	set	1
2828                     ; 569   uint8_t temp = 0;
2830                     ; 572   assert_param(IS_ADC1_FLAG_OK(Flag));
2832  0002 a180          	cp	a,#128
2833  0004 273e          	jreq	L464
2834  0006 a141          	cp	a,#65
2835  0008 273a          	jreq	L464
2836  000a a140          	cp	a,#64
2837  000c 2736          	jreq	L464
2838  000e a110          	cp	a,#16
2839  0010 2732          	jreq	L464
2840  0012 a111          	cp	a,#17
2841  0014 272e          	jreq	L464
2842  0016 a112          	cp	a,#18
2843  0018 272a          	jreq	L464
2844  001a a113          	cp	a,#19
2845  001c 2726          	jreq	L464
2846  001e a114          	cp	a,#20
2847  0020 2722          	jreq	L464
2848  0022 a115          	cp	a,#21
2849  0024 271e          	jreq	L464
2850  0026 a116          	cp	a,#22
2851  0028 271a          	jreq	L464
2852  002a a117          	cp	a,#23
2853  002c 2716          	jreq	L464
2854  002e a118          	cp	a,#24
2855  0030 2712          	jreq	L464
2856  0032 a119          	cp	a,#25
2857  0034 270e          	jreq	L464
2858  0036 ae023c        	ldw	x,#572
2859  0039 89            	pushw	x
2860  003a 5f            	clrw	x
2861  003b 89            	pushw	x
2862  003c ae0000        	ldw	x,#L542
2863  003f cd0000        	call	_assert_failed
2865  0042 5b04          	addw	sp,#4
2866  0044               L464:
2867                     ; 574   if ((Flag & 0x0F) == 0x01)
2869  0044 7b02          	ld	a,(OFST+1,sp)
2870  0046 a40f          	and	a,#15
2871  0048 4a            	dec	a
2872  0049 2606          	jrne	L5311
2873                     ; 577     ADC1->CR3 &= (uint8_t)(~ADC1_CR3_OVR);
2875  004b 721d5403      	bres	21507,#6
2877  004f 2045          	jra	L7311
2878  0051               L5311:
2879                     ; 579   else if ((Flag & 0xF0) == 0x10)
2881  0051 7b02          	ld	a,(OFST+1,sp)
2882  0053 a4f0          	and	a,#240
2883  0055 a110          	cp	a,#16
2884  0057 2634          	jrne	L1411
2885                     ; 582     temp = (uint8_t)(Flag & (uint8_t)0x0F);
2887  0059 7b02          	ld	a,(OFST+1,sp)
2888  005b a40f          	and	a,#15
2889  005d 6b01          	ld	(OFST+0,sp),a
2891                     ; 583     if (temp < 8)
2893  005f a108          	cp	a,#8
2894  0061 2414          	jruge	L3411
2895                     ; 585       ADC1->AWSRL &= (uint8_t)~(uint8_t)((uint8_t)1 << temp);
2897  0063 5f            	clrw	x
2898  0064 97            	ld	xl,a
2899  0065 a601          	ld	a,#1
2900  0067 5d            	tnzw	x
2901  0068 2704          	jreq	L074
2902  006a               L274:
2903  006a 48            	sll	a
2904  006b 5a            	decw	x
2905  006c 26fc          	jrne	L274
2906  006e               L074:
2907  006e 43            	cpl	a
2908  006f c4540d        	and	a,21517
2909  0072 c7540d        	ld	21517,a
2911  0075 201f          	jra	L7311
2912  0077               L3411:
2913                     ; 589       ADC1->AWSRH &= (uint8_t)~(uint8_t)((uint8_t)1 << (temp - 8));
2915  0077 a008          	sub	a,#8
2916  0079 5f            	clrw	x
2917  007a 97            	ld	xl,a
2918  007b a601          	ld	a,#1
2919  007d 5d            	tnzw	x
2920  007e 2704          	jreq	L474
2921  0080               L674:
2922  0080 48            	sll	a
2923  0081 5a            	decw	x
2924  0082 26fc          	jrne	L674
2925  0084               L474:
2926  0084 43            	cpl	a
2927  0085 c4540c        	and	a,21516
2928  0088 c7540c        	ld	21516,a
2929  008b 2009          	jra	L7311
2930  008d               L1411:
2931                     ; 594     ADC1->CSR &= (uint8_t) (~Flag);
2933  008d 7b02          	ld	a,(OFST+1,sp)
2934  008f 43            	cpl	a
2935  0090 c45400        	and	a,21504
2936  0093 c75400        	ld	21504,a
2937  0096               L7311:
2938                     ; 596 }
2941  0096 85            	popw	x
2942  0097 81            	ret	
2998                     ; 616 ITStatus ADC1_GetITStatus(ADC1_IT_TypeDef ITPendingBit)
2998                     ; 617 {
2999                     .text:	section	.text,new
3000  0000               _ADC1_GetITStatus:
3002  0000 89            	pushw	x
3003  0001 88            	push	a
3004       00000001      OFST:	set	1
3007                     ; 618   ITStatus itstatus = RESET;
3009                     ; 619   uint8_t temp = 0;
3011                     ; 622   assert_param(IS_ADC1_ITPENDINGBIT_OK(ITPendingBit));
3013  0002 a30080        	cpw	x,#128
3014  0005 274a          	jreq	L605
3015  0007 a30140        	cpw	x,#320
3016  000a 2745          	jreq	L605
3017  000c a30110        	cpw	x,#272
3018  000f 2740          	jreq	L605
3019  0011 a30111        	cpw	x,#273
3020  0014 273b          	jreq	L605
3021  0016 a30112        	cpw	x,#274
3022  0019 2736          	jreq	L605
3023  001b a30113        	cpw	x,#275
3024  001e 2731          	jreq	L605
3025  0020 a30114        	cpw	x,#276
3026  0023 272c          	jreq	L605
3027  0025 a30115        	cpw	x,#277
3028  0028 2727          	jreq	L605
3029  002a a30116        	cpw	x,#278
3030  002d 2722          	jreq	L605
3031  002f a30117        	cpw	x,#279
3032  0032 271d          	jreq	L605
3033  0034 a30118        	cpw	x,#280
3034  0037 2718          	jreq	L605
3035  0039 a3011c        	cpw	x,#284
3036  003c 2713          	jreq	L605
3037  003e a30119        	cpw	x,#281
3038  0041 270e          	jreq	L605
3039  0043 ae026e        	ldw	x,#622
3040  0046 89            	pushw	x
3041  0047 5f            	clrw	x
3042  0048 89            	pushw	x
3043  0049 ae0000        	ldw	x,#L542
3044  004c cd0000        	call	_assert_failed
3046  004f 5b04          	addw	sp,#4
3047  0051               L605:
3048                     ; 624   if (((uint16_t)ITPendingBit & 0xF0) == 0x10)
3050  0051 7b03          	ld	a,(OFST+2,sp)
3051  0053 a4f0          	and	a,#240
3052  0055 5f            	clrw	x
3053  0056 02            	rlwa	x,a
3054  0057 a30010        	cpw	x,#16
3055  005a 262c          	jrne	L7711
3056                     ; 627     temp = (uint8_t)((uint16_t)ITPendingBit & 0x0F);
3058  005c 7b03          	ld	a,(OFST+2,sp)
3059  005e a40f          	and	a,#15
3060  0060 6b01          	ld	(OFST+0,sp),a
3062                     ; 628     if (temp < 8)
3064  0062 a108          	cp	a,#8
3065  0064 2410          	jruge	L1021
3066                     ; 630       itstatus = (ITStatus)(ADC1->AWSRL & (uint8_t)((uint8_t)1 << temp));
3068  0066 5f            	clrw	x
3069  0067 97            	ld	xl,a
3070  0068 a601          	ld	a,#1
3071  006a 5d            	tnzw	x
3072  006b 2704          	jreq	L215
3073  006d               L415:
3074  006d 48            	sll	a
3075  006e 5a            	decw	x
3076  006f 26fc          	jrne	L415
3077  0071               L215:
3078  0071 c4540d        	and	a,21517
3081  0074 2017          	jra	L5021
3082  0076               L1021:
3083                     ; 634       itstatus = (ITStatus)(ADC1->AWSRH & (uint8_t)((uint8_t)1 << (temp - 8)));
3085  0076 a008          	sub	a,#8
3086  0078 5f            	clrw	x
3087  0079 97            	ld	xl,a
3088  007a a601          	ld	a,#1
3089  007c 5d            	tnzw	x
3090  007d 2704          	jreq	L615
3091  007f               L025:
3092  007f 48            	sll	a
3093  0080 5a            	decw	x
3094  0081 26fc          	jrne	L025
3095  0083               L615:
3096  0083 c4540c        	and	a,21516
3098  0086 2005          	jra	L5021
3099  0088               L7711:
3100                     ; 639     itstatus = (ITStatus)(ADC1->CSR & (uint8_t)ITPendingBit);
3102  0088 c65400        	ld	a,21504
3103  008b 1403          	and	a,(OFST+2,sp)
3105  008d               L5021:
3106                     ; 641   return ((ITStatus)itstatus);
3110  008d 5b03          	addw	sp,#3
3111  008f 81            	ret	
3157                     ; 662 void ADC1_ClearITPendingBit(ADC1_IT_TypeDef ITPendingBit)
3157                     ; 663 {
3158                     .text:	section	.text,new
3159  0000               _ADC1_ClearITPendingBit:
3161  0000 89            	pushw	x
3162  0001 88            	push	a
3163       00000001      OFST:	set	1
3166                     ; 664   uint8_t temp = 0;
3168                     ; 667   assert_param(IS_ADC1_ITPENDINGBIT_OK(ITPendingBit));
3170  0002 a30080        	cpw	x,#128
3171  0005 274a          	jreq	L035
3172  0007 a30140        	cpw	x,#320
3173  000a 2745          	jreq	L035
3174  000c a30110        	cpw	x,#272
3175  000f 2740          	jreq	L035
3176  0011 a30111        	cpw	x,#273
3177  0014 273b          	jreq	L035
3178  0016 a30112        	cpw	x,#274
3179  0019 2736          	jreq	L035
3180  001b a30113        	cpw	x,#275
3181  001e 2731          	jreq	L035
3182  0020 a30114        	cpw	x,#276
3183  0023 272c          	jreq	L035
3184  0025 a30115        	cpw	x,#277
3185  0028 2727          	jreq	L035
3186  002a a30116        	cpw	x,#278
3187  002d 2722          	jreq	L035
3188  002f a30117        	cpw	x,#279
3189  0032 271d          	jreq	L035
3190  0034 a30118        	cpw	x,#280
3191  0037 2718          	jreq	L035
3192  0039 a3011c        	cpw	x,#284
3193  003c 2713          	jreq	L035
3194  003e a30119        	cpw	x,#281
3195  0041 270e          	jreq	L035
3196  0043 ae029b        	ldw	x,#667
3197  0046 89            	pushw	x
3198  0047 5f            	clrw	x
3199  0048 89            	pushw	x
3200  0049 ae0000        	ldw	x,#L542
3201  004c cd0000        	call	_assert_failed
3203  004f 5b04          	addw	sp,#4
3204  0051               L035:
3205                     ; 669   if (((uint16_t)ITPendingBit & 0xF0) == 0x10)
3207  0051 7b03          	ld	a,(OFST+2,sp)
3208  0053 a4f0          	and	a,#240
3209  0055 5f            	clrw	x
3210  0056 02            	rlwa	x,a
3211  0057 a30010        	cpw	x,#16
3212  005a 2634          	jrne	L1321
3213                     ; 672     temp = (uint8_t)((uint16_t)ITPendingBit & 0x0F);
3215  005c 7b03          	ld	a,(OFST+2,sp)
3216  005e a40f          	and	a,#15
3217  0060 6b01          	ld	(OFST+0,sp),a
3219                     ; 673     if (temp < 8)
3221  0062 a108          	cp	a,#8
3222  0064 2414          	jruge	L3321
3223                     ; 675       ADC1->AWSRL &= (uint8_t)~(uint8_t)((uint8_t)1 << temp);
3225  0066 5f            	clrw	x
3226  0067 97            	ld	xl,a
3227  0068 a601          	ld	a,#1
3228  006a 5d            	tnzw	x
3229  006b 2704          	jreq	L435
3230  006d               L635:
3231  006d 48            	sll	a
3232  006e 5a            	decw	x
3233  006f 26fc          	jrne	L635
3234  0071               L435:
3235  0071 43            	cpl	a
3236  0072 c4540d        	and	a,21517
3237  0075 c7540d        	ld	21517,a
3239  0078 201f          	jra	L7321
3240  007a               L3321:
3241                     ; 679       ADC1->AWSRH &= (uint8_t)~(uint8_t)((uint8_t)1 << (temp - 8));
3243  007a a008          	sub	a,#8
3244  007c 5f            	clrw	x
3245  007d 97            	ld	xl,a
3246  007e a601          	ld	a,#1
3247  0080 5d            	tnzw	x
3248  0081 2704          	jreq	L045
3249  0083               L245:
3250  0083 48            	sll	a
3251  0084 5a            	decw	x
3252  0085 26fc          	jrne	L245
3253  0087               L045:
3254  0087 43            	cpl	a
3255  0088 c4540c        	and	a,21516
3256  008b c7540c        	ld	21516,a
3257  008e 2009          	jra	L7321
3258  0090               L1321:
3259                     ; 684     ADC1->CSR &= (uint8_t)((uint16_t)~(uint16_t)ITPendingBit);
3261  0090 7b03          	ld	a,(OFST+2,sp)
3262  0092 43            	cpl	a
3263  0093 c45400        	and	a,21504
3264  0096 c75400        	ld	21504,a
3265  0099               L7321:
3266                     ; 686 }
3269  0099 5b03          	addw	sp,#3
3270  009b 81            	ret	
3283                     	xdef	_ADC1_ClearITPendingBit
3284                     	xdef	_ADC1_GetITStatus
3285                     	xdef	_ADC1_ClearFlag
3286                     	xdef	_ADC1_GetFlagStatus
3287                     	xdef	_ADC1_GetAWDChannelStatus
3288                     	xdef	_ADC1_GetBufferValue
3289                     	xdef	_ADC1_SetLowThreshold
3290                     	xdef	_ADC1_SetHighThreshold
3291                     	xdef	_ADC1_GetConversionValue
3292                     	xdef	_ADC1_StartConversion
3293                     	xdef	_ADC1_AWDChannelConfig
3294                     	xdef	_ADC1_ExternalTriggerConfig
3295                     	xdef	_ADC1_ConversionConfig
3296                     	xdef	_ADC1_SchmittTriggerConfig
3297                     	xdef	_ADC1_PrescalerConfig
3298                     	xdef	_ADC1_ITConfig
3299                     	xdef	_ADC1_DataBufferCmd
3300                     	xdef	_ADC1_ScanModeCmd
3301                     	xdef	_ADC1_Cmd
3302                     	xdef	_ADC1_Init
3303                     	xdef	_ADC1_DeInit
3304                     	xref	_assert_failed
3305                     .const:	section	.text
3306  0000               L542:
3307  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\stm8s_std"
3308  0012 706572697068  	dc.b	"periph_lib\librari"
3309  0024 65735c73746d  	dc.b	"es\stm8s_stdperiph"
3310  0036 5f6472697665  	dc.b	"_driver\src\stm8s_"
3311  0048 616463312e63  	dc.b	"adc1.c",0
3331                     	end
