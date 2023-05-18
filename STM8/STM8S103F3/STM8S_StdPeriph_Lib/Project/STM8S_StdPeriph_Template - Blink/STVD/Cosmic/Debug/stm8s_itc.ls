   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 50 uint8_t ITC_GetCPUCC(void)
  49                     ; 51 {
  51                     .text:	section	.text,new
  52  0000               _ITC_GetCPUCC:
  56                     ; 53   _asm("push cc");
  59  0000 8a            	push	cc
  61                     ; 54   _asm("pop a");
  64  0001 84            	pop	a
  66                     ; 55   return; /* Ignore compiler warning, the returned value is in A register */
  69  0002 81            	ret	
  92                     ; 80 void ITC_DeInit(void)
  92                     ; 81 {
  93                     .text:	section	.text,new
  94  0000               _ITC_DeInit:
  98                     ; 82   ITC->ISPR1 = ITC_SPRX_RESET_VALUE;
 100  0000 35ff7f70      	mov	32624,#255
 101                     ; 83   ITC->ISPR2 = ITC_SPRX_RESET_VALUE;
 103  0004 35ff7f71      	mov	32625,#255
 104                     ; 84   ITC->ISPR3 = ITC_SPRX_RESET_VALUE;
 106  0008 35ff7f72      	mov	32626,#255
 107                     ; 85   ITC->ISPR4 = ITC_SPRX_RESET_VALUE;
 109  000c 35ff7f73      	mov	32627,#255
 110                     ; 86   ITC->ISPR5 = ITC_SPRX_RESET_VALUE;
 112  0010 35ff7f74      	mov	32628,#255
 113                     ; 87   ITC->ISPR6 = ITC_SPRX_RESET_VALUE;
 115  0014 35ff7f75      	mov	32629,#255
 116                     ; 88   ITC->ISPR7 = ITC_SPRX_RESET_VALUE;
 118  0018 35ff7f76      	mov	32630,#255
 119                     ; 89   ITC->ISPR8 = ITC_SPRX_RESET_VALUE;
 121  001c 35ff7f77      	mov	32631,#255
 122                     ; 90 }
 125  0020 81            	ret	
 150                     ; 97 uint8_t ITC_GetSoftIntStatus(void)
 150                     ; 98 {
 151                     .text:	section	.text,new
 152  0000               _ITC_GetSoftIntStatus:
 156                     ; 99   return (uint8_t)(ITC_GetCPUCC() & CPU_CC_I1I0);
 158  0000 cd0000        	call	_ITC_GetCPUCC
 160  0003 a428          	and	a,#40
 163  0005 81            	ret	
 413                     .const:	section	.text
 414  0000               L23:
 415  0000 0035          	dc.w	L14
 416  0002 0035          	dc.w	L14
 417  0004 0035          	dc.w	L14
 418  0006 0035          	dc.w	L14
 419  0008 003a          	dc.w	L34
 420  000a 003a          	dc.w	L34
 421  000c 003a          	dc.w	L34
 422  000e 003a          	dc.w	L34
 423  0010 005a          	dc.w	L502
 424  0012 005a          	dc.w	L502
 425  0014 003f          	dc.w	L54
 426  0016 003f          	dc.w	L54
 427  0018 0044          	dc.w	L74
 428  001a 0044          	dc.w	L74
 429  001c 0044          	dc.w	L74
 430  001e 0044          	dc.w	L74
 431  0020 0049          	dc.w	L15
 432  0022 0049          	dc.w	L15
 433  0024 0049          	dc.w	L15
 434  0026 0049          	dc.w	L15
 435  0028 005a          	dc.w	L502
 436  002a 005a          	dc.w	L502
 437  002c 004e          	dc.w	L35
 438  002e 004e          	dc.w	L35
 439  0030 0053          	dc.w	L55
 440                     ; 107 ITC_PriorityLevel_TypeDef ITC_GetSoftwarePriority(ITC_Irq_TypeDef IrqNum)
 440                     ; 108 {
 441                     .text:	section	.text,new
 442  0000               _ITC_GetSoftwarePriority:
 444  0000 88            	push	a
 445  0001 89            	pushw	x
 446       00000002      OFST:	set	2
 449                     ; 109   uint8_t Value = 0;
 451  0002 0f02          	clr	(OFST+0,sp)
 453                     ; 110   uint8_t Mask = 0;
 455                     ; 113   assert_param(IS_ITC_IRQ_OK((uint8_t)IrqNum));
 457  0004 a119          	cp	a,#25
 458  0006 250e          	jrult	L02
 459  0008 ae0071        	ldw	x,#113
 460  000b 89            	pushw	x
 461  000c 5f            	clrw	x
 462  000d 89            	pushw	x
 463  000e ae0064        	ldw	x,#L102
 464  0011 cd0000        	call	_assert_failed
 466  0014 5b04          	addw	sp,#4
 467  0016               L02:
 468                     ; 116   Mask = (uint8_t)(0x03U << (((uint8_t)IrqNum % 4U) * 2U));
 470  0016 7b03          	ld	a,(OFST+1,sp)
 471  0018 a403          	and	a,#3
 472  001a 48            	sll	a
 473  001b 5f            	clrw	x
 474  001c 97            	ld	xl,a
 475  001d a603          	ld	a,#3
 476  001f 5d            	tnzw	x
 477  0020 2704          	jreq	L42
 478  0022               L62:
 479  0022 48            	sll	a
 480  0023 5a            	decw	x
 481  0024 26fc          	jrne	L62
 482  0026               L42:
 483  0026 6b01          	ld	(OFST-1,sp),a
 485                     ; 118   switch (IrqNum)
 487  0028 7b03          	ld	a,(OFST+1,sp)
 489                     ; 198   default:
 489                     ; 199     break;
 490  002a a119          	cp	a,#25
 491  002c 242c          	jruge	L502
 492  002e 5f            	clrw	x
 493  002f 97            	ld	xl,a
 494  0030 58            	sllw	x
 495  0031 de0000        	ldw	x,(L23,x)
 496  0034 fc            	jp	(x)
 497  0035               L14:
 498                     ; 120   case ITC_IRQ_TLI: /* TLI software priority can be read but has no meaning */
 498                     ; 121   case ITC_IRQ_AWU:
 498                     ; 122   case ITC_IRQ_CLK:
 498                     ; 123   case ITC_IRQ_PORTA:
 498                     ; 124     Value = (uint8_t)(ITC->ISPR1 & Mask); /* Read software priority */
 500  0035 c67f70        	ld	a,32624
 501                     ; 125     break;
 503  0038 201c          	jp	LC001
 504  003a               L34:
 505                     ; 127   case ITC_IRQ_PORTB:
 505                     ; 128   case ITC_IRQ_PORTC:
 505                     ; 129   case ITC_IRQ_PORTD:
 505                     ; 130   case ITC_IRQ_PORTE:
 505                     ; 131     Value = (uint8_t)(ITC->ISPR2 & Mask); /* Read software priority */
 507  003a c67f71        	ld	a,32625
 508                     ; 132     break;
 510  003d 2017          	jp	LC001
 511  003f               L54:
 512                     ; 141   case ITC_IRQ_SPI:
 512                     ; 142   case ITC_IRQ_TIM1_OVF:
 512                     ; 143     Value = (uint8_t)(ITC->ISPR3 & Mask); /* Read software priority */
 514  003f c67f72        	ld	a,32626
 515                     ; 144     break;
 517  0042 2012          	jp	LC001
 518  0044               L74:
 519                     ; 146   case ITC_IRQ_TIM1_CAPCOM:
 519                     ; 147 #if defined (STM8S903) || defined (STM8AF622x)
 519                     ; 148   case ITC_IRQ_TIM5_OVFTRI:
 519                     ; 149   case ITC_IRQ_TIM5_CAPCOM:
 519                     ; 150 #else
 519                     ; 151   case ITC_IRQ_TIM2_OVF:
 519                     ; 152   case ITC_IRQ_TIM2_CAPCOM:
 519                     ; 153 #endif /* STM8S903 or STM8AF622x*/
 519                     ; 154   case ITC_IRQ_TIM3_OVF:
 519                     ; 155     Value = (uint8_t)(ITC->ISPR4 & Mask); /* Read software priority */
 521  0044 c67f73        	ld	a,32627
 522                     ; 156     break;
 524  0047 200d          	jp	LC001
 525  0049               L15:
 526                     ; 158   case ITC_IRQ_TIM3_CAPCOM:
 526                     ; 159 #if defined(STM8S208) ||defined(STM8S207) || defined (STM8S007) || defined(STM8S103) || \
 526                     ; 160     defined(STM8S003) ||defined(STM8S001) || defined (STM8S903) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
 526                     ; 161   case ITC_IRQ_UART1_TX:
 526                     ; 162   case ITC_IRQ_UART1_RX:
 526                     ; 163 #endif /*STM8S208 or STM8S207 or STM8S007 or STM8S103 or STM8S003 or STM8S001 or STM8S903 or STM8AF52Ax or STM8AF62Ax */ 
 526                     ; 164 #if defined(STM8AF622x)
 526                     ; 165   case ITC_IRQ_UART4_TX:
 526                     ; 166   case ITC_IRQ_UART4_RX:
 526                     ; 167 #endif /*STM8AF622x */
 526                     ; 168   case ITC_IRQ_I2C:
 526                     ; 169     Value = (uint8_t)(ITC->ISPR5 & Mask); /* Read software priority */
 528  0049 c67f74        	ld	a,32628
 529                     ; 170     break;
 531  004c 2008          	jp	LC001
 532  004e               L35:
 533                     ; 184   case ITC_IRQ_ADC1:
 533                     ; 185 #endif /*STM8S105, STM8S005, STM8S103 or STM8S003 or STM8S001 or STM8S903 or STM8AF626x or STM8AF622x */
 533                     ; 186 #if defined (STM8S903) || defined (STM8AF622x)
 533                     ; 187   case ITC_IRQ_TIM6_OVFTRI:
 533                     ; 188 #else
 533                     ; 189   case ITC_IRQ_TIM4_OVF:
 533                     ; 190 #endif /*STM8S903 or STM8AF622x */
 533                     ; 191     Value = (uint8_t)(ITC->ISPR6 & Mask); /* Read software priority */
 535  004e c67f75        	ld	a,32629
 536                     ; 192     break;
 538  0051 2003          	jp	LC001
 539  0053               L55:
 540                     ; 194   case ITC_IRQ_EEPROM_EEC:
 540                     ; 195     Value = (uint8_t)(ITC->ISPR7 & Mask); /* Read software priority */
 542  0053 c67f76        	ld	a,32630
 543  0056               LC001:
 544  0056 1401          	and	a,(OFST-1,sp)
 545  0058 6b02          	ld	(OFST+0,sp),a
 547                     ; 196     break;
 549                     ; 198   default:
 549                     ; 199     break;
 551  005a               L502:
 552                     ; 202   Value >>= (uint8_t)(((uint8_t)IrqNum % 4u) * 2u);
 554  005a 7b03          	ld	a,(OFST+1,sp)
 555  005c a403          	and	a,#3
 556  005e 48            	sll	a
 557  005f 5f            	clrw	x
 558  0060 97            	ld	xl,a
 559  0061 7b02          	ld	a,(OFST+0,sp)
 560  0063 5d            	tnzw	x
 561  0064 2704          	jreq	L43
 562  0066               L63:
 563  0066 44            	srl	a
 564  0067 5a            	decw	x
 565  0068 26fc          	jrne	L63
 566  006a               L43:
 568                     ; 204   return((ITC_PriorityLevel_TypeDef)Value);
 572  006a 5b03          	addw	sp,#3
 573  006c 81            	ret	
 639                     	switch	.const
 640  0032               L201:
 641  0032 0066          	dc.w	L702
 642  0034 0066          	dc.w	L702
 643  0036 0066          	dc.w	L702
 644  0038 0066          	dc.w	L702
 645  003a 0078          	dc.w	L112
 646  003c 0078          	dc.w	L112
 647  003e 0078          	dc.w	L112
 648  0040 0078          	dc.w	L112
 649  0042 00e2          	dc.w	L362
 650  0044 00e2          	dc.w	L362
 651  0046 008a          	dc.w	L312
 652  0048 008a          	dc.w	L312
 653  004a 009c          	dc.w	L512
 654  004c 009c          	dc.w	L512
 655  004e 009c          	dc.w	L512
 656  0050 009c          	dc.w	L512
 657  0052 00ae          	dc.w	L712
 658  0054 00ae          	dc.w	L712
 659  0056 00ae          	dc.w	L712
 660  0058 00ae          	dc.w	L712
 661  005a 00e2          	dc.w	L362
 662  005c 00e2          	dc.w	L362
 663  005e 00c0          	dc.w	L122
 664  0060 00c0          	dc.w	L122
 665  0062 00d2          	dc.w	L322
 666                     ; 220 void ITC_SetSoftwarePriority(ITC_Irq_TypeDef IrqNum, ITC_PriorityLevel_TypeDef PriorityValue)
 666                     ; 221 {
 667                     .text:	section	.text,new
 668  0000               _ITC_SetSoftwarePriority:
 670  0000 89            	pushw	x
 671  0001 89            	pushw	x
 672       00000002      OFST:	set	2
 675                     ; 222   uint8_t Mask = 0;
 677                     ; 223   uint8_t NewPriority = 0;
 679                     ; 226   assert_param(IS_ITC_IRQ_OK((uint8_t)IrqNum));
 681  0002 9e            	ld	a,xh
 682  0003 a119          	cp	a,#25
 683  0005 2506          	jrult	L44
 684  0007 ae00e2        	ldw	x,#226
 685  000a cd00e5        	call	LC002
 686  000d               L44:
 687                     ; 227   assert_param(IS_ITC_PRIORITY_OK(PriorityValue));
 689  000d 7b04          	ld	a,(OFST+2,sp)
 690  000f a102          	cp	a,#2
 691  0011 2711          	jreq	L45
 692  0013 a101          	cp	a,#1
 693  0015 270d          	jreq	L45
 694  0017 4d            	tnz	a
 695  0018 270a          	jreq	L45
 696  001a a103          	cp	a,#3
 697  001c 2706          	jreq	L45
 698  001e ae00e3        	ldw	x,#227
 699  0021 cd00e5        	call	LC002
 700  0024               L45:
 701                     ; 230   assert_param(IS_ITC_INTERRUPTS_DISABLED);
 703  0024 cd0000        	call	_ITC_GetSoftIntStatus
 705  0027 a128          	cp	a,#40
 706  0029 2706          	jreq	L46
 707  002b ae00e6        	ldw	x,#230
 708  002e cd00e5        	call	LC002
 709  0031               L46:
 710                     ; 234   Mask = (uint8_t)(~(uint8_t)(0x03U << (((uint8_t)IrqNum % 4U) * 2U)));
 712  0031 7b03          	ld	a,(OFST+1,sp)
 713  0033 a403          	and	a,#3
 714  0035 48            	sll	a
 715  0036 5f            	clrw	x
 716  0037 97            	ld	xl,a
 717  0038 a603          	ld	a,#3
 718  003a 5d            	tnzw	x
 719  003b 2704          	jreq	L07
 720  003d               L27:
 721  003d 48            	sll	a
 722  003e 5a            	decw	x
 723  003f 26fc          	jrne	L27
 724  0041               L07:
 725  0041 43            	cpl	a
 726  0042 6b01          	ld	(OFST-1,sp),a
 728                     ; 237   NewPriority = (uint8_t)((uint8_t)(PriorityValue) << (((uint8_t)IrqNum % 4U) * 2U));
 730  0044 7b03          	ld	a,(OFST+1,sp)
 731  0046 a403          	and	a,#3
 732  0048 48            	sll	a
 733  0049 5f            	clrw	x
 734  004a 97            	ld	xl,a
 735  004b 7b04          	ld	a,(OFST+2,sp)
 736  004d 5d            	tnzw	x
 737  004e 2704          	jreq	L47
 738  0050               L67:
 739  0050 48            	sll	a
 740  0051 5a            	decw	x
 741  0052 26fc          	jrne	L67
 742  0054               L47:
 743  0054 6b02          	ld	(OFST+0,sp),a
 745                     ; 239   switch (IrqNum)
 747  0056 7b03          	ld	a,(OFST+1,sp)
 749                     ; 329   default:
 749                     ; 330     break;
 750  0058 a119          	cp	a,#25
 751  005a 2503cc00e2    	jruge	L362
 752  005f 5f            	clrw	x
 753  0060 97            	ld	xl,a
 754  0061 58            	sllw	x
 755  0062 de0032        	ldw	x,(L201,x)
 756  0065 fc            	jp	(x)
 757  0066               L702:
 758                     ; 241   case ITC_IRQ_TLI: /* TLI software priority can be written but has no meaning */
 758                     ; 242   case ITC_IRQ_AWU:
 758                     ; 243   case ITC_IRQ_CLK:
 758                     ; 244   case ITC_IRQ_PORTA:
 758                     ; 245     ITC->ISPR1 &= Mask;
 760  0066 c67f70        	ld	a,32624
 761  0069 1401          	and	a,(OFST-1,sp)
 762  006b c77f70        	ld	32624,a
 763                     ; 246     ITC->ISPR1 |= NewPriority;
 765  006e c67f70        	ld	a,32624
 766  0071 1a02          	or	a,(OFST+0,sp)
 767  0073 c77f70        	ld	32624,a
 768                     ; 247     break;
 770  0076 206a          	jra	L362
 771  0078               L112:
 772                     ; 249   case ITC_IRQ_PORTB:
 772                     ; 250   case ITC_IRQ_PORTC:
 772                     ; 251   case ITC_IRQ_PORTD:
 772                     ; 252   case ITC_IRQ_PORTE:
 772                     ; 253     ITC->ISPR2 &= Mask;
 774  0078 c67f71        	ld	a,32625
 775  007b 1401          	and	a,(OFST-1,sp)
 776  007d c77f71        	ld	32625,a
 777                     ; 254     ITC->ISPR2 |= NewPriority;
 779  0080 c67f71        	ld	a,32625
 780  0083 1a02          	or	a,(OFST+0,sp)
 781  0085 c77f71        	ld	32625,a
 782                     ; 255     break;
 784  0088 2058          	jra	L362
 785  008a               L312:
 786                     ; 264   case ITC_IRQ_SPI:
 786                     ; 265   case ITC_IRQ_TIM1_OVF:
 786                     ; 266     ITC->ISPR3 &= Mask;
 788  008a c67f72        	ld	a,32626
 789  008d 1401          	and	a,(OFST-1,sp)
 790  008f c77f72        	ld	32626,a
 791                     ; 267     ITC->ISPR3 |= NewPriority;
 793  0092 c67f72        	ld	a,32626
 794  0095 1a02          	or	a,(OFST+0,sp)
 795  0097 c77f72        	ld	32626,a
 796                     ; 268     break;
 798  009a 2046          	jra	L362
 799  009c               L512:
 800                     ; 270   case ITC_IRQ_TIM1_CAPCOM:
 800                     ; 271 #if defined(STM8S903) || defined(STM8AF622x) 
 800                     ; 272   case ITC_IRQ_TIM5_OVFTRI:
 800                     ; 273   case ITC_IRQ_TIM5_CAPCOM:
 800                     ; 274 #else
 800                     ; 275   case ITC_IRQ_TIM2_OVF:
 800                     ; 276   case ITC_IRQ_TIM2_CAPCOM:
 800                     ; 277 #endif /*STM8S903 or STM8AF622x */
 800                     ; 278   case ITC_IRQ_TIM3_OVF:
 800                     ; 279     ITC->ISPR4 &= Mask;
 802  009c c67f73        	ld	a,32627
 803  009f 1401          	and	a,(OFST-1,sp)
 804  00a1 c77f73        	ld	32627,a
 805                     ; 280     ITC->ISPR4 |= NewPriority;
 807  00a4 c67f73        	ld	a,32627
 808  00a7 1a02          	or	a,(OFST+0,sp)
 809  00a9 c77f73        	ld	32627,a
 810                     ; 281     break;
 812  00ac 2034          	jra	L362
 813  00ae               L712:
 814                     ; 283   case ITC_IRQ_TIM3_CAPCOM:
 814                     ; 284 #if defined(STM8S208) ||defined(STM8S207) || defined (STM8S007) || defined(STM8S103) || \
 814                     ; 285     defined(STM8S001) ||defined(STM8S003) ||defined(STM8S903) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
 814                     ; 286   case ITC_IRQ_UART1_TX:
 814                     ; 287   case ITC_IRQ_UART1_RX:
 814                     ; 288 #endif /*STM8S208 or STM8S207 or STM8S007 or STM8S103 or STM8S003 or STM8S001 or STM8S903 or STM8AF52Ax or STM8AF62Ax */ 
 814                     ; 289 #if defined(STM8AF622x)
 814                     ; 290   case ITC_IRQ_UART4_TX:
 814                     ; 291   case ITC_IRQ_UART4_RX:
 814                     ; 292 #endif /*STM8AF622x */
 814                     ; 293   case ITC_IRQ_I2C:
 814                     ; 294     ITC->ISPR5 &= Mask;
 816  00ae c67f74        	ld	a,32628
 817  00b1 1401          	and	a,(OFST-1,sp)
 818  00b3 c77f74        	ld	32628,a
 819                     ; 295     ITC->ISPR5 |= NewPriority;
 821  00b6 c67f74        	ld	a,32628
 822  00b9 1a02          	or	a,(OFST+0,sp)
 823  00bb c77f74        	ld	32628,a
 824                     ; 296     break;
 826  00be 2022          	jra	L362
 827  00c0               L122:
 828                     ; 312   case ITC_IRQ_ADC1:
 828                     ; 313 #endif /*STM8S105, STM8S005, STM8S103 or STM8S003 or STM8S001 or STM8S903 or STM8AF626x or STM8AF622x */
 828                     ; 314     
 828                     ; 315 #if defined (STM8S903) || defined (STM8AF622x)
 828                     ; 316   case ITC_IRQ_TIM6_OVFTRI:
 828                     ; 317 #else
 828                     ; 318   case ITC_IRQ_TIM4_OVF:
 828                     ; 319 #endif /* STM8S903 or STM8AF622x */
 828                     ; 320     ITC->ISPR6 &= Mask;
 830  00c0 c67f75        	ld	a,32629
 831  00c3 1401          	and	a,(OFST-1,sp)
 832  00c5 c77f75        	ld	32629,a
 833                     ; 321     ITC->ISPR6 |= NewPriority;
 835  00c8 c67f75        	ld	a,32629
 836  00cb 1a02          	or	a,(OFST+0,sp)
 837  00cd c77f75        	ld	32629,a
 838                     ; 322     break;
 840  00d0 2010          	jra	L362
 841  00d2               L322:
 842                     ; 324   case ITC_IRQ_EEPROM_EEC:
 842                     ; 325     ITC->ISPR7 &= Mask;
 844  00d2 c67f76        	ld	a,32630
 845  00d5 1401          	and	a,(OFST-1,sp)
 846  00d7 c77f76        	ld	32630,a
 847                     ; 326     ITC->ISPR7 |= NewPriority;
 849  00da c67f76        	ld	a,32630
 850  00dd 1a02          	or	a,(OFST+0,sp)
 851  00df c77f76        	ld	32630,a
 852                     ; 327     break;
 854                     ; 329   default:
 854                     ; 330     break;
 856  00e2               L362:
 857                     ; 332 }
 860  00e2 5b04          	addw	sp,#4
 861  00e4 81            	ret	
 862  00e5               LC002:
 863  00e5 89            	pushw	x
 864  00e6 5f            	clrw	x
 865  00e7 89            	pushw	x
 866  00e8 ae0064        	ldw	x,#L102
 867  00eb cd0000        	call	_assert_failed
 869  00ee 5b04          	addw	sp,#4
 870  00f0 81            	ret	
 883                     	xdef	_ITC_GetSoftwarePriority
 884                     	xdef	_ITC_SetSoftwarePriority
 885                     	xdef	_ITC_GetSoftIntStatus
 886                     	xdef	_ITC_DeInit
 887                     	xdef	_ITC_GetCPUCC
 888                     	xref	_assert_failed
 889                     	switch	.const
 890  0064               L102:
 891  0064 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 892  0076 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 893  0088 685f64726976  	dc.b	"h_driver\src\stm8s"
 894  009a 5f6974632e63  	dc.b	"_itc.c",0
 914                     	end
