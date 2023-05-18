   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 50 void SPI_DeInit(void)
  49                     ; 51 {
  51                     .text:	section	.text,new
  52  0000               _SPI_DeInit:
  56                     ; 52   SPI->CR1    = SPI_CR1_RESET_VALUE;
  58  0000 725f5200      	clr	20992
  59                     ; 53   SPI->CR2    = SPI_CR2_RESET_VALUE;
  61  0004 725f5201      	clr	20993
  62                     ; 54   SPI->ICR    = SPI_ICR_RESET_VALUE;
  64  0008 725f5202      	clr	20994
  65                     ; 55   SPI->SR     = SPI_SR_RESET_VALUE;
  67  000c 35025203      	mov	20995,#2
  68                     ; 56   SPI->CRCPR  = SPI_CRCPR_RESET_VALUE;
  70  0010 35075205      	mov	20997,#7
  71                     ; 57 }
  74  0014 81            	ret	
 391                     ; 78 void SPI_Init(SPI_FirstBit_TypeDef FirstBit, SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, SPI_Mode_TypeDef Mode, SPI_ClockPolarity_TypeDef ClockPolarity, SPI_ClockPhase_TypeDef ClockPhase, SPI_DataDirection_TypeDef Data_Direction, SPI_NSS_TypeDef Slave_Management, uint8_t CRCPolynomial)
 391                     ; 79 {
 392                     .text:	section	.text,new
 393  0000               _SPI_Init:
 395  0000 89            	pushw	x
 396  0001 88            	push	a
 397       00000001      OFST:	set	1
 400                     ; 81   assert_param(IS_SPI_FIRSTBIT_OK(FirstBit));
 402  0002 9e            	ld	a,xh
 403  0003 4d            	tnz	a
 404  0004 270b          	jreq	L41
 405  0006 9e            	ld	a,xh
 406  0007 a180          	cp	a,#128
 407  0009 2706          	jreq	L41
 408  000b ae0051        	ldw	x,#81
 409  000e cd00c0        	call	LC001
 410  0011               L41:
 411                     ; 82   assert_param(IS_SPI_BAUDRATE_PRESCALER_OK(BaudRatePrescaler));
 413  0011 7b03          	ld	a,(OFST+2,sp)
 414  0013 2722          	jreq	L42
 415  0015 a108          	cp	a,#8
 416  0017 271e          	jreq	L42
 417  0019 a110          	cp	a,#16
 418  001b 271a          	jreq	L42
 419  001d a118          	cp	a,#24
 420  001f 2716          	jreq	L42
 421  0021 a120          	cp	a,#32
 422  0023 2712          	jreq	L42
 423  0025 a128          	cp	a,#40
 424  0027 270e          	jreq	L42
 425  0029 a130          	cp	a,#48
 426  002b 270a          	jreq	L42
 427  002d a138          	cp	a,#56
 428  002f 2706          	jreq	L42
 429  0031 ae0052        	ldw	x,#82
 430  0034 cd00c0        	call	LC001
 431  0037               L42:
 432                     ; 83   assert_param(IS_SPI_MODE_OK(Mode));
 434  0037 7b06          	ld	a,(OFST+5,sp)
 435  0039 a104          	cp	a,#4
 436  003b 2708          	jreq	L43
 437  003d 4d            	tnz	a
 438  003e 2705          	jreq	L43
 439  0040 ae0053        	ldw	x,#83
 440  0043 ad7b          	call	LC001
 441  0045               L43:
 442                     ; 84   assert_param(IS_SPI_POLARITY_OK(ClockPolarity));
 444  0045 7b07          	ld	a,(OFST+6,sp)
 445  0047 2709          	jreq	L44
 446  0049 a102          	cp	a,#2
 447  004b 2705          	jreq	L44
 448  004d ae0054        	ldw	x,#84
 449  0050 ad6e          	call	LC001
 450  0052               L44:
 451                     ; 85   assert_param(IS_SPI_PHASE_OK(ClockPhase));
 453  0052 7b08          	ld	a,(OFST+7,sp)
 454  0054 2708          	jreq	L45
 455  0056 4a            	dec	a
 456  0057 2705          	jreq	L45
 457  0059 ae0055        	ldw	x,#85
 458  005c ad62          	call	LC001
 459  005e               L45:
 460                     ; 86   assert_param(IS_SPI_DATA_DIRECTION_OK(Data_Direction));
 462  005e 7b09          	ld	a,(OFST+8,sp)
 463  0060 2711          	jreq	L46
 464  0062 a104          	cp	a,#4
 465  0064 270d          	jreq	L46
 466  0066 a180          	cp	a,#128
 467  0068 2709          	jreq	L46
 468  006a a1c0          	cp	a,#192
 469  006c 2705          	jreq	L46
 470  006e ae0056        	ldw	x,#86
 471  0071 ad4d          	call	LC001
 472  0073               L46:
 473                     ; 87   assert_param(IS_SPI_SLAVEMANAGEMENT_OK(Slave_Management));
 475  0073 7b0a          	ld	a,(OFST+9,sp)
 476  0075 a102          	cp	a,#2
 477  0077 2708          	jreq	L47
 478  0079 4d            	tnz	a
 479  007a 2705          	jreq	L47
 480  007c ae0057        	ldw	x,#87
 481  007f ad3f          	call	LC001
 482  0081               L47:
 483                     ; 88   assert_param(IS_SPI_CRC_POLYNOMIAL_OK(CRCPolynomial));
 485  0081 7b0b          	ld	a,(OFST+10,sp)
 486  0083 2605          	jrne	L201
 487  0085 ae0058        	ldw	x,#88
 488  0088 ad36          	call	LC001
 489  008a               L201:
 490                     ; 91   SPI->CR1 = (uint8_t)((uint8_t)((uint8_t)FirstBit | BaudRatePrescaler) |
 490                     ; 92                        (uint8_t)((uint8_t)ClockPolarity | ClockPhase));
 492  008a 7b07          	ld	a,(OFST+6,sp)
 493  008c 1a08          	or	a,(OFST+7,sp)
 494  008e 6b01          	ld	(OFST+0,sp),a
 496  0090 7b02          	ld	a,(OFST+1,sp)
 497  0092 1a03          	or	a,(OFST+2,sp)
 498  0094 1a01          	or	a,(OFST+0,sp)
 499  0096 c75200        	ld	20992,a
 500                     ; 95   SPI->CR2 = (uint8_t)((uint8_t)(Data_Direction) | (uint8_t)(Slave_Management));
 502  0099 7b09          	ld	a,(OFST+8,sp)
 503  009b 1a0a          	or	a,(OFST+9,sp)
 504  009d c75201        	ld	20993,a
 505                     ; 97   if (Mode == SPI_MODE_MASTER)
 507  00a0 7b06          	ld	a,(OFST+5,sp)
 508  00a2 a104          	cp	a,#4
 509  00a4 2606          	jrne	L502
 510                     ; 99     SPI->CR2 |= (uint8_t)SPI_CR2_SSI;
 512  00a6 72105201      	bset	20993,#0
 514  00aa 2004          	jra	L702
 515  00ac               L502:
 516                     ; 103     SPI->CR2 &= (uint8_t)~(SPI_CR2_SSI);
 518  00ac 72115201      	bres	20993,#0
 519  00b0               L702:
 520                     ; 107   SPI->CR1 |= (uint8_t)(Mode);
 522  00b0 c65200        	ld	a,20992
 523  00b3 1a06          	or	a,(OFST+5,sp)
 524  00b5 c75200        	ld	20992,a
 525                     ; 110   SPI->CRCPR = (uint8_t)CRCPolynomial;
 527  00b8 7b0b          	ld	a,(OFST+10,sp)
 528  00ba c75205        	ld	20997,a
 529                     ; 111 }
 532  00bd 5b03          	addw	sp,#3
 533  00bf 81            	ret	
 534  00c0               LC001:
 535  00c0 89            	pushw	x
 536  00c1 5f            	clrw	x
 537  00c2 89            	pushw	x
 538  00c3 ae0000        	ldw	x,#L302
 539  00c6 cd0000        	call	_assert_failed
 541  00c9 5b04          	addw	sp,#4
 542  00cb 81            	ret	
 598                     ; 119 void SPI_Cmd(FunctionalState NewState)
 598                     ; 120 {
 599                     .text:	section	.text,new
 600  0000               _SPI_Cmd:
 602  0000 88            	push	a
 603       00000000      OFST:	set	0
 606                     ; 122   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 608  0001 4d            	tnz	a
 609  0002 2711          	jreq	L411
 610  0004 4a            	dec	a
 611  0005 270e          	jreq	L411
 612  0007 ae007a        	ldw	x,#122
 613  000a 89            	pushw	x
 614  000b 5f            	clrw	x
 615  000c 89            	pushw	x
 616  000d ae0000        	ldw	x,#L302
 617  0010 cd0000        	call	_assert_failed
 619  0013 5b04          	addw	sp,#4
 620  0015               L411:
 621                     ; 124   if (NewState != DISABLE)
 623  0015 7b01          	ld	a,(OFST+1,sp)
 624  0017 2706          	jreq	L732
 625                     ; 126     SPI->CR1 |= SPI_CR1_SPE; /* Enable the SPI peripheral*/
 627  0019 721c5200      	bset	20992,#6
 629  001d 2004          	jra	L142
 630  001f               L732:
 631                     ; 130     SPI->CR1 &= (uint8_t)(~SPI_CR1_SPE); /* Disable the SPI peripheral*/
 633  001f 721d5200      	bres	20992,#6
 634  0023               L142:
 635                     ; 132 }
 638  0023 84            	pop	a
 639  0024 81            	ret	
 749                     ; 141 void SPI_ITConfig(SPI_IT_TypeDef SPI_IT, FunctionalState NewState)
 749                     ; 142 {
 750                     .text:	section	.text,new
 751  0000               _SPI_ITConfig:
 753  0000 89            	pushw	x
 754  0001 88            	push	a
 755       00000001      OFST:	set	1
 758                     ; 143   uint8_t itpos = 0;
 760                     ; 145   assert_param(IS_SPI_CONFIG_IT_OK(SPI_IT));
 762  0002 9e            	ld	a,xh
 763  0003 a117          	cp	a,#23
 764  0005 2714          	jreq	L621
 765  0007 9e            	ld	a,xh
 766  0008 a106          	cp	a,#6
 767  000a 270f          	jreq	L621
 768  000c 9e            	ld	a,xh
 769  000d a105          	cp	a,#5
 770  000f 270a          	jreq	L621
 771  0011 9e            	ld	a,xh
 772  0012 a134          	cp	a,#52
 773  0014 2705          	jreq	L621
 774  0016 ae0091        	ldw	x,#145
 775  0019 ad32          	call	LC002
 776  001b               L621:
 777                     ; 146   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 779  001b 7b03          	ld	a,(OFST+2,sp)
 780  001d 2708          	jreq	L631
 781  001f 4a            	dec	a
 782  0020 2705          	jreq	L631
 783  0022 ae0092        	ldw	x,#146
 784  0025 ad26          	call	LC002
 785  0027               L631:
 786                     ; 149   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)SPI_IT & (uint8_t)0x0F));
 788  0027 7b02          	ld	a,(OFST+1,sp)
 789  0029 a40f          	and	a,#15
 790  002b 5f            	clrw	x
 791  002c 97            	ld	xl,a
 792  002d a601          	ld	a,#1
 793  002f 5d            	tnzw	x
 794  0030 2704          	jreq	L241
 795  0032               L441:
 796  0032 48            	sll	a
 797  0033 5a            	decw	x
 798  0034 26fc          	jrne	L441
 799  0036               L241:
 800  0036 6b01          	ld	(OFST+0,sp),a
 802                     ; 151   if (NewState != DISABLE)
 804  0038 0d03          	tnz	(OFST+2,sp)
 805  003a 2707          	jreq	L313
 806                     ; 153     SPI->ICR |= itpos; /* Enable interrupt*/
 808  003c c65202        	ld	a,20994
 809  003f 1a01          	or	a,(OFST+0,sp)
 811  0041 2004          	jra	L513
 812  0043               L313:
 813                     ; 157     SPI->ICR &= (uint8_t)(~itpos); /* Disable interrupt*/
 815  0043 43            	cpl	a
 816  0044 c45202        	and	a,20994
 817  0047               L513:
 818  0047 c75202        	ld	20994,a
 819                     ; 159 }
 822  004a 5b03          	addw	sp,#3
 823  004c 81            	ret	
 824  004d               LC002:
 825  004d 89            	pushw	x
 826  004e 5f            	clrw	x
 827  004f 89            	pushw	x
 828  0050 ae0000        	ldw	x,#L302
 829  0053 cd0000        	call	_assert_failed
 831  0056 5b04          	addw	sp,#4
 832  0058 81            	ret	
 866                     ; 166 void SPI_SendData(uint8_t Data)
 866                     ; 167 {
 867                     .text:	section	.text,new
 868  0000               _SPI_SendData:
 872                     ; 168   SPI->DR = Data; /* Write in the DR register the data to be sent*/
 874  0000 c75204        	ld	20996,a
 875                     ; 169 }
 878  0003 81            	ret	
 901                     ; 176 uint8_t SPI_ReceiveData(void)
 901                     ; 177 {
 902                     .text:	section	.text,new
 903  0000               _SPI_ReceiveData:
 907                     ; 178   return ((uint8_t)SPI->DR); /* Return the data in the DR register*/
 909  0000 c65204        	ld	a,20996
 912  0003 81            	ret	
 949                     ; 187 void SPI_NSSInternalSoftwareCmd(FunctionalState NewState)
 949                     ; 188 {
 950                     .text:	section	.text,new
 951  0000               _SPI_NSSInternalSoftwareCmd:
 953  0000 88            	push	a
 954       00000000      OFST:	set	0
 957                     ; 190   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 959  0001 4d            	tnz	a
 960  0002 2711          	jreq	L061
 961  0004 4a            	dec	a
 962  0005 270e          	jreq	L061
 963  0007 ae00be        	ldw	x,#190
 964  000a 89            	pushw	x
 965  000b 5f            	clrw	x
 966  000c 89            	pushw	x
 967  000d ae0000        	ldw	x,#L302
 968  0010 cd0000        	call	_assert_failed
 970  0013 5b04          	addw	sp,#4
 971  0015               L061:
 972                     ; 192   if (NewState != DISABLE)
 974  0015 7b01          	ld	a,(OFST+1,sp)
 975  0017 2706          	jreq	L363
 976                     ; 194     SPI->CR2 |= SPI_CR2_SSI; /* Set NSS pin internally by software*/
 978  0019 72105201      	bset	20993,#0
 980  001d 2004          	jra	L563
 981  001f               L363:
 982                     ; 198     SPI->CR2 &= (uint8_t)(~SPI_CR2_SSI); /* Reset NSS pin internally by software*/
 984  001f 72115201      	bres	20993,#0
 985  0023               L563:
 986                     ; 200 }
 989  0023 84            	pop	a
 990  0024 81            	ret	
1013                     ; 207 void SPI_TransmitCRC(void)
1013                     ; 208 {
1014                     .text:	section	.text,new
1015  0000               _SPI_TransmitCRC:
1019                     ; 209   SPI->CR2 |= SPI_CR2_CRCNEXT; /* Enable the CRC transmission*/
1021  0000 72185201      	bset	20993,#4
1022                     ; 210 }
1025  0004 81            	ret	
1062                     ; 218 void SPI_CalculateCRCCmd(FunctionalState NewState)
1062                     ; 219 {
1063                     .text:	section	.text,new
1064  0000               _SPI_CalculateCRCCmd:
1066  0000 88            	push	a
1067       00000000      OFST:	set	0
1070                     ; 221   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1072  0001 4d            	tnz	a
1073  0002 2711          	jreq	L471
1074  0004 4a            	dec	a
1075  0005 270e          	jreq	L471
1076  0007 ae00dd        	ldw	x,#221
1077  000a 89            	pushw	x
1078  000b 5f            	clrw	x
1079  000c 89            	pushw	x
1080  000d ae0000        	ldw	x,#L302
1081  0010 cd0000        	call	_assert_failed
1083  0013 5b04          	addw	sp,#4
1084  0015               L471:
1085                     ; 223   if (NewState != DISABLE)
1087  0015 7b01          	ld	a,(OFST+1,sp)
1088  0017 2706          	jreq	L514
1089                     ; 225     SPI->CR2 |= SPI_CR2_CRCEN; /* Enable the CRC calculation*/
1091  0019 721a5201      	bset	20993,#5
1093  001d 2004          	jra	L714
1094  001f               L514:
1095                     ; 229     SPI->CR2 &= (uint8_t)(~SPI_CR2_CRCEN); /* Disable the CRC calculation*/
1097  001f 721b5201      	bres	20993,#5
1098  0023               L714:
1099                     ; 231 }
1102  0023 84            	pop	a
1103  0024 81            	ret	
1168                     ; 238 uint8_t SPI_GetCRC(SPI_CRC_TypeDef SPI_CRC)
1168                     ; 239 {
1169                     .text:	section	.text,new
1170  0000               _SPI_GetCRC:
1172  0000 88            	push	a
1173  0001 88            	push	a
1174       00000001      OFST:	set	1
1177                     ; 240   uint8_t crcreg = 0;
1179                     ; 243   assert_param(IS_SPI_CRC_OK(SPI_CRC));
1181  0002 a101          	cp	a,#1
1182  0004 2711          	jreq	L602
1183  0006 4d            	tnz	a
1184  0007 270e          	jreq	L602
1185  0009 ae00f3        	ldw	x,#243
1186  000c 89            	pushw	x
1187  000d 5f            	clrw	x
1188  000e 89            	pushw	x
1189  000f ae0000        	ldw	x,#L302
1190  0012 cd0000        	call	_assert_failed
1192  0015 5b04          	addw	sp,#4
1193  0017               L602:
1194                     ; 245   if (SPI_CRC != SPI_CRC_RX)
1196  0017 7b02          	ld	a,(OFST+1,sp)
1197  0019 2705          	jreq	L354
1198                     ; 247     crcreg = SPI->TXCRCR;  /* Get the Tx CRC register*/
1200  001b c65207        	ld	a,20999
1203  001e 2003          	jra	L554
1204  0020               L354:
1205                     ; 251     crcreg = SPI->RXCRCR; /* Get the Rx CRC register*/
1207  0020 c65206        	ld	a,20998
1209  0023               L554:
1210                     ; 255   return crcreg;
1214  0023 85            	popw	x
1215  0024 81            	ret	
1240                     ; 263 void SPI_ResetCRC(void)
1240                     ; 264 {
1241                     .text:	section	.text,new
1242  0000               _SPI_ResetCRC:
1246                     ; 267   SPI_CalculateCRCCmd(ENABLE);
1248  0000 a601          	ld	a,#1
1249  0002 cd0000        	call	_SPI_CalculateCRCCmd
1251                     ; 270   SPI_Cmd(ENABLE);
1253  0005 a601          	ld	a,#1
1255                     ; 271 }
1258  0007 cc0000        	jp	_SPI_Cmd
1282                     ; 278 uint8_t SPI_GetCRCPolynomial(void)
1282                     ; 279 {
1283                     .text:	section	.text,new
1284  0000               _SPI_GetCRCPolynomial:
1288                     ; 280   return SPI->CRCPR; /* Return the CRC polynomial register */
1290  0000 c65205        	ld	a,20997
1293  0003 81            	ret	
1350                     ; 288 void SPI_BiDirectionalLineConfig(SPI_Direction_TypeDef SPI_Direction)
1350                     ; 289 {
1351                     .text:	section	.text,new
1352  0000               _SPI_BiDirectionalLineConfig:
1354  0000 88            	push	a
1355       00000000      OFST:	set	0
1358                     ; 291   assert_param(IS_SPI_DIRECTION_OK(SPI_Direction));
1360  0001 4d            	tnz	a
1361  0002 2711          	jreq	L032
1362  0004 4a            	dec	a
1363  0005 270e          	jreq	L032
1364  0007 ae0123        	ldw	x,#291
1365  000a 89            	pushw	x
1366  000b 5f            	clrw	x
1367  000c 89            	pushw	x
1368  000d ae0000        	ldw	x,#L302
1369  0010 cd0000        	call	_assert_failed
1371  0013 5b04          	addw	sp,#4
1372  0015               L032:
1373                     ; 293   if (SPI_Direction != SPI_DIRECTION_RX)
1375  0015 7b01          	ld	a,(OFST+1,sp)
1376  0017 2706          	jreq	L525
1377                     ; 295     SPI->CR2 |= SPI_CR2_BDOE; /* Set the Tx only mode*/
1379  0019 721c5201      	bset	20993,#6
1381  001d 2004          	jra	L725
1382  001f               L525:
1383                     ; 299     SPI->CR2 &= (uint8_t)(~SPI_CR2_BDOE); /* Set the Rx only mode*/
1385  001f 721d5201      	bres	20993,#6
1386  0023               L725:
1387                     ; 301 }
1390  0023 84            	pop	a
1391  0024 81            	ret	
1513                     ; 311 FlagStatus SPI_GetFlagStatus(SPI_Flag_TypeDef SPI_FLAG)
1513                     ; 312 {
1514                     .text:	section	.text,new
1515  0000               _SPI_GetFlagStatus:
1517  0000 88            	push	a
1518  0001 88            	push	a
1519       00000001      OFST:	set	1
1522                     ; 313   FlagStatus status = RESET;
1524                     ; 315   assert_param(IS_SPI_FLAGS_OK(SPI_FLAG));
1526  0002 a140          	cp	a,#64
1527  0004 2726          	jreq	L242
1528  0006 a120          	cp	a,#32
1529  0008 2722          	jreq	L242
1530  000a a110          	cp	a,#16
1531  000c 271e          	jreq	L242
1532  000e a108          	cp	a,#8
1533  0010 271a          	jreq	L242
1534  0012 a102          	cp	a,#2
1535  0014 2716          	jreq	L242
1536  0016 a101          	cp	a,#1
1537  0018 2712          	jreq	L242
1538  001a a180          	cp	a,#128
1539  001c 270e          	jreq	L242
1540  001e ae013b        	ldw	x,#315
1541  0021 89            	pushw	x
1542  0022 5f            	clrw	x
1543  0023 89            	pushw	x
1544  0024 ae0000        	ldw	x,#L302
1545  0027 cd0000        	call	_assert_failed
1547  002a 5b04          	addw	sp,#4
1548  002c               L242:
1549                     ; 318   if ((SPI->SR & (uint8_t)SPI_FLAG) != (uint8_t)RESET)
1551  002c c65203        	ld	a,20995
1552  002f 1502          	bcp	a,(OFST+1,sp)
1553  0031 2704          	jreq	L506
1554                     ; 320     status = SET; /* SPI_FLAG is set */
1556  0033 a601          	ld	a,#1
1559  0035 2001          	jra	L706
1560  0037               L506:
1561                     ; 324     status = RESET; /* SPI_FLAG is reset*/
1563  0037 4f            	clr	a
1565  0038               L706:
1566                     ; 328   return status;
1570  0038 85            	popw	x
1571  0039 81            	ret	
1607                     ; 346 void SPI_ClearFlag(SPI_Flag_TypeDef SPI_FLAG)
1607                     ; 347 {
1608                     .text:	section	.text,new
1609  0000               _SPI_ClearFlag:
1611  0000 88            	push	a
1612       00000000      OFST:	set	0
1615                     ; 348   assert_param(IS_SPI_CLEAR_FLAGS_OK(SPI_FLAG));
1617  0001 a110          	cp	a,#16
1618  0003 2712          	jreq	L452
1619  0005 a108          	cp	a,#8
1620  0007 270e          	jreq	L452
1621  0009 ae015c        	ldw	x,#348
1622  000c 89            	pushw	x
1623  000d 5f            	clrw	x
1624  000e 89            	pushw	x
1625  000f ae0000        	ldw	x,#L302
1626  0012 cd0000        	call	_assert_failed
1628  0015 5b04          	addw	sp,#4
1629  0017               L452:
1630                     ; 350   SPI->SR = (uint8_t)(~SPI_FLAG);
1632  0017 7b01          	ld	a,(OFST+1,sp)
1633  0019 43            	cpl	a
1634  001a c75203        	ld	20995,a
1635                     ; 351 }
1638  001d 84            	pop	a
1639  001e 81            	ret	
1722                     ; 366 ITStatus SPI_GetITStatus(SPI_IT_TypeDef SPI_IT)
1722                     ; 367 {
1723                     .text:	section	.text,new
1724  0000               _SPI_GetITStatus:
1726  0000 88            	push	a
1727  0001 89            	pushw	x
1728       00000002      OFST:	set	2
1731                     ; 368   ITStatus pendingbitstatus = RESET;
1733                     ; 369   uint8_t itpos = 0;
1735                     ; 370   uint8_t itmask1 = 0;
1737                     ; 371   uint8_t itmask2 = 0;
1739                     ; 372   uint8_t enablestatus = 0;
1741                     ; 373   assert_param(IS_SPI_GET_IT_OK(SPI_IT));
1743  0002 a165          	cp	a,#101
1744  0004 2722          	jreq	L662
1745  0006 a155          	cp	a,#85
1746  0008 271e          	jreq	L662
1747  000a a145          	cp	a,#69
1748  000c 271a          	jreq	L662
1749  000e a134          	cp	a,#52
1750  0010 2716          	jreq	L662
1751  0012 a117          	cp	a,#23
1752  0014 2712          	jreq	L662
1753  0016 a106          	cp	a,#6
1754  0018 270e          	jreq	L662
1755  001a ae0175        	ldw	x,#373
1756  001d 89            	pushw	x
1757  001e 5f            	clrw	x
1758  001f 89            	pushw	x
1759  0020 ae0000        	ldw	x,#L302
1760  0023 cd0000        	call	_assert_failed
1762  0026 5b04          	addw	sp,#4
1763  0028               L662:
1764                     ; 375   itpos = (uint8_t)((uint8_t)1 << ((uint8_t)SPI_IT & (uint8_t)0x0F));
1766  0028 7b03          	ld	a,(OFST+1,sp)
1767  002a a40f          	and	a,#15
1768  002c 5f            	clrw	x
1769  002d 97            	ld	xl,a
1770  002e a601          	ld	a,#1
1771  0030 5d            	tnzw	x
1772  0031 2704          	jreq	L272
1773  0033               L472:
1774  0033 48            	sll	a
1775  0034 5a            	decw	x
1776  0035 26fc          	jrne	L472
1777  0037               L272:
1778  0037 6b01          	ld	(OFST-1,sp),a
1780                     ; 378   itmask1 = (uint8_t)((uint8_t)SPI_IT >> (uint8_t)4);
1782  0039 7b03          	ld	a,(OFST+1,sp)
1783  003b 4e            	swap	a
1784  003c a40f          	and	a,#15
1785  003e 6b02          	ld	(OFST+0,sp),a
1787                     ; 380   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
1789  0040 5f            	clrw	x
1790  0041 97            	ld	xl,a
1791  0042 a601          	ld	a,#1
1792  0044 5d            	tnzw	x
1793  0045 2704          	jreq	L672
1794  0047               L003:
1795  0047 48            	sll	a
1796  0048 5a            	decw	x
1797  0049 26fc          	jrne	L003
1798  004b               L672:
1800                     ; 382   enablestatus = (uint8_t)((uint8_t)SPI->SR & itmask2);
1802  004b c45203        	and	a,20995
1803  004e 6b02          	ld	(OFST+0,sp),a
1805                     ; 384   if (((SPI->ICR & itpos) != RESET) && enablestatus)
1807  0050 c65202        	ld	a,20994
1808  0053 1501          	bcp	a,(OFST-1,sp)
1809  0055 2708          	jreq	L176
1811  0057 7b02          	ld	a,(OFST+0,sp)
1812  0059 2704          	jreq	L176
1813                     ; 387     pendingbitstatus = SET;
1815  005b a601          	ld	a,#1
1818  005d 2001          	jra	L376
1819  005f               L176:
1820                     ; 392     pendingbitstatus = RESET;
1822  005f 4f            	clr	a
1824  0060               L376:
1825                     ; 395   return  pendingbitstatus;
1829  0060 5b03          	addw	sp,#3
1830  0062 81            	ret	
1876                     ; 412 void SPI_ClearITPendingBit(SPI_IT_TypeDef SPI_IT)
1876                     ; 413 {
1877                     .text:	section	.text,new
1878  0000               _SPI_ClearITPendingBit:
1880  0000 88            	push	a
1881  0001 88            	push	a
1882       00000001      OFST:	set	1
1885                     ; 414   uint8_t itpos = 0;
1887                     ; 415   assert_param(IS_SPI_CLEAR_IT_OK(SPI_IT));
1889  0002 a145          	cp	a,#69
1890  0004 2712          	jreq	L013
1891  0006 a134          	cp	a,#52
1892  0008 270e          	jreq	L013
1893  000a ae019f        	ldw	x,#415
1894  000d 89            	pushw	x
1895  000e 5f            	clrw	x
1896  000f 89            	pushw	x
1897  0010 ae0000        	ldw	x,#L302
1898  0013 cd0000        	call	_assert_failed
1900  0016 5b04          	addw	sp,#4
1901  0018               L013:
1902                     ; 420   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)(SPI_IT & (uint8_t)0xF0) >> 4));
1904  0018 7b02          	ld	a,(OFST+1,sp)
1905  001a 4e            	swap	a
1906  001b a40f          	and	a,#15
1907  001d 5f            	clrw	x
1908  001e 97            	ld	xl,a
1909  001f a601          	ld	a,#1
1910  0021 5d            	tnzw	x
1911  0022 2704          	jreq	L413
1912  0024               L613:
1913  0024 48            	sll	a
1914  0025 5a            	decw	x
1915  0026 26fc          	jrne	L613
1916  0028               L413:
1918                     ; 422   SPI->SR = (uint8_t)(~itpos);
1920  0028 43            	cpl	a
1921  0029 c75203        	ld	20995,a
1922                     ; 424 }
1925  002c 85            	popw	x
1926  002d 81            	ret	
1939                     	xdef	_SPI_ClearITPendingBit
1940                     	xdef	_SPI_GetITStatus
1941                     	xdef	_SPI_ClearFlag
1942                     	xdef	_SPI_GetFlagStatus
1943                     	xdef	_SPI_BiDirectionalLineConfig
1944                     	xdef	_SPI_GetCRCPolynomial
1945                     	xdef	_SPI_ResetCRC
1946                     	xdef	_SPI_GetCRC
1947                     	xdef	_SPI_CalculateCRCCmd
1948                     	xdef	_SPI_TransmitCRC
1949                     	xdef	_SPI_NSSInternalSoftwareCmd
1950                     	xdef	_SPI_ReceiveData
1951                     	xdef	_SPI_SendData
1952                     	xdef	_SPI_ITConfig
1953                     	xdef	_SPI_Cmd
1954                     	xdef	_SPI_Init
1955                     	xdef	_SPI_DeInit
1956                     	xref	_assert_failed
1957                     .const:	section	.text
1958  0000               L302:
1959  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
1960  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
1961  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
1962  0036 5f7370692e63  	dc.b	"_spi.c",0
1982                     	end
