   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  49                     ; 53 void EXTI_DeInit(void)
  49                     ; 54 {
  51                     .text:	section	.text,new
  52  0000               _EXTI_DeInit:
  56                     ; 55   EXTI->CR1 = EXTI_CR1_RESET_VALUE;
  58  0000 725f50a0      	clr	20640
  59                     ; 56   EXTI->CR2 = EXTI_CR2_RESET_VALUE;
  61  0004 725f50a1      	clr	20641
  62                     ; 57 }
  65  0008 81            	ret	
 191                     ; 70 void EXTI_SetExtIntSensitivity(EXTI_Port_TypeDef Port, EXTI_Sensitivity_TypeDef SensitivityValue)
 191                     ; 71 {
 192                     .text:	section	.text,new
 193  0000               _EXTI_SetExtIntSensitivity:
 195  0000 89            	pushw	x
 196       00000000      OFST:	set	0
 199                     ; 73   assert_param(IS_EXTI_PORT_OK(Port));
 201  0001 9e            	ld	a,xh
 202  0002 4d            	tnz	a
 203  0003 2718          	jreq	L41
 204  0005 9e            	ld	a,xh
 205  0006 4a            	dec	a
 206  0007 2714          	jreq	L41
 207  0009 9e            	ld	a,xh
 208  000a a102          	cp	a,#2
 209  000c 270f          	jreq	L41
 210  000e 9e            	ld	a,xh
 211  000f a103          	cp	a,#3
 212  0011 270a          	jreq	L41
 213  0013 9e            	ld	a,xh
 214  0014 a104          	cp	a,#4
 215  0016 2705          	jreq	L41
 216  0018 ae0049        	ldw	x,#73
 217  001b ad7c          	call	LC004
 218  001d               L41:
 219                     ; 74   assert_param(IS_EXTI_SENSITIVITY_OK(SensitivityValue));
 221  001d 7b02          	ld	a,(OFST+2,sp)
 222  001f 2711          	jreq	L42
 223  0021 a101          	cp	a,#1
 224  0023 270d          	jreq	L42
 225  0025 a102          	cp	a,#2
 226  0027 2709          	jreq	L42
 227  0029 a103          	cp	a,#3
 228  002b 2705          	jreq	L42
 229  002d ae004a        	ldw	x,#74
 230  0030 ad67          	call	LC004
 231  0032               L42:
 232                     ; 77   switch (Port)
 234  0032 7b01          	ld	a,(OFST+1,sp)
 236                     ; 99   default:
 236                     ; 100     break;
 237  0034 270e          	jreq	L12
 238  0036 4a            	dec	a
 239  0037 271a          	jreq	L32
 240  0039 4a            	dec	a
 241  003a 2725          	jreq	L52
 242  003c 4a            	dec	a
 243  003d 2731          	jreq	L72
 244  003f 4a            	dec	a
 245  0040 2745          	jreq	L13
 246  0042 2053          	jra	L511
 247  0044               L12:
 248                     ; 79   case EXTI_PORT_GPIOA:
 248                     ; 80     EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);
 250  0044 c650a0        	ld	a,20640
 251  0047 a4fc          	and	a,#252
 252  0049 c750a0        	ld	20640,a
 253                     ; 81     EXTI->CR1 |= (uint8_t)(SensitivityValue);
 255  004c c650a0        	ld	a,20640
 256  004f 1a02          	or	a,(OFST+2,sp)
 257                     ; 82     break;
 259  0051 202f          	jp	LC001
 260  0053               L32:
 261                     ; 83   case EXTI_PORT_GPIOB:
 261                     ; 84     EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PBIS);
 263  0053 c650a0        	ld	a,20640
 264  0056 a4f3          	and	a,#243
 265  0058 c750a0        	ld	20640,a
 266                     ; 85     EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 2);
 268  005b 7b02          	ld	a,(OFST+2,sp)
 269  005d 48            	sll	a
 270  005e 48            	sll	a
 271                     ; 86     break;
 273  005f 201e          	jp	LC002
 274  0061               L52:
 275                     ; 87   case EXTI_PORT_GPIOC:
 275                     ; 88     EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PCIS);
 277  0061 c650a0        	ld	a,20640
 278  0064 a4cf          	and	a,#207
 279  0066 c750a0        	ld	20640,a
 280                     ; 89     EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 4);
 282  0069 7b02          	ld	a,(OFST+2,sp)
 283  006b 97            	ld	xl,a
 284  006c a610          	ld	a,#16
 285                     ; 90     break;
 287  006e 200d          	jp	LC003
 288  0070               L72:
 289                     ; 91   case EXTI_PORT_GPIOD:
 289                     ; 92     EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PDIS);
 291  0070 c650a0        	ld	a,20640
 292  0073 a43f          	and	a,#63
 293  0075 c750a0        	ld	20640,a
 294                     ; 93     EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 6);
 296  0078 7b02          	ld	a,(OFST+2,sp)
 297  007a 97            	ld	xl,a
 298  007b a640          	ld	a,#64
 299  007d               LC003:
 300  007d 42            	mul	x,a
 301  007e 9f            	ld	a,xl
 302  007f               LC002:
 303  007f ca50a0        	or	a,20640
 304  0082               LC001:
 305  0082 c750a0        	ld	20640,a
 306                     ; 94     break;
 308  0085 2010          	jra	L511
 309  0087               L13:
 310                     ; 95   case EXTI_PORT_GPIOE:
 310                     ; 96     EXTI->CR2 &= (uint8_t)(~EXTI_CR2_PEIS);
 312  0087 c650a1        	ld	a,20641
 313  008a a4fc          	and	a,#252
 314  008c c750a1        	ld	20641,a
 315                     ; 97     EXTI->CR2 |= (uint8_t)(SensitivityValue);
 317  008f c650a1        	ld	a,20641
 318  0092 1a02          	or	a,(OFST+2,sp)
 319  0094 c750a1        	ld	20641,a
 320                     ; 98     break;
 322                     ; 99   default:
 322                     ; 100     break;
 324  0097               L511:
 325                     ; 102 }
 328  0097 85            	popw	x
 329  0098 81            	ret	
 330  0099               LC004:
 331  0099 89            	pushw	x
 332  009a 5f            	clrw	x
 333  009b 89            	pushw	x
 334  009c ae0000        	ldw	x,#L111
 335  009f cd0000        	call	_assert_failed
 337  00a2 5b04          	addw	sp,#4
 338  00a4 81            	ret	
 397                     ; 111 void EXTI_SetTLISensitivity(EXTI_TLISensitivity_TypeDef SensitivityValue)
 397                     ; 112 {
 398                     .text:	section	.text,new
 399  0000               _EXTI_SetTLISensitivity:
 401  0000 88            	push	a
 402       00000000      OFST:	set	0
 405                     ; 114   assert_param(IS_EXTI_TLISENSITIVITY_OK(SensitivityValue));
 407  0001 4d            	tnz	a
 408  0002 2712          	jreq	L63
 409  0004 a104          	cp	a,#4
 410  0006 270e          	jreq	L63
 411  0008 ae0072        	ldw	x,#114
 412  000b 89            	pushw	x
 413  000c 5f            	clrw	x
 414  000d 89            	pushw	x
 415  000e ae0000        	ldw	x,#L111
 416  0011 cd0000        	call	_assert_failed
 418  0014 5b04          	addw	sp,#4
 419  0016               L63:
 420                     ; 117   EXTI->CR2 &= (uint8_t)(~EXTI_CR2_TLIS);
 422  0016 721550a1      	bres	20641,#2
 423                     ; 118   EXTI->CR2 |= (uint8_t)(SensitivityValue);
 425  001a c650a1        	ld	a,20641
 426  001d 1a01          	or	a,(OFST+1,sp)
 427  001f c750a1        	ld	20641,a
 428                     ; 119 }
 431  0022 84            	pop	a
 432  0023 81            	ret	
 479                     ; 126 EXTI_Sensitivity_TypeDef EXTI_GetExtIntSensitivity(EXTI_Port_TypeDef Port)
 479                     ; 127 {
 480                     .text:	section	.text,new
 481  0000               _EXTI_GetExtIntSensitivity:
 483  0000 88            	push	a
 484  0001 88            	push	a
 485       00000001      OFST:	set	1
 488                     ; 128   uint8_t value = 0;
 490  0002 0f01          	clr	(OFST+0,sp)
 492                     ; 131   assert_param(IS_EXTI_PORT_OK(Port));
 494  0004 4d            	tnz	a
 495  0005 271e          	jreq	L05
 496  0007 a101          	cp	a,#1
 497  0009 271a          	jreq	L05
 498  000b a102          	cp	a,#2
 499  000d 2716          	jreq	L05
 500  000f a103          	cp	a,#3
 501  0011 2712          	jreq	L05
 502  0013 a104          	cp	a,#4
 503  0015 270e          	jreq	L05
 504  0017 ae0083        	ldw	x,#131
 505  001a 89            	pushw	x
 506  001b 5f            	clrw	x
 507  001c 89            	pushw	x
 508  001d ae0000        	ldw	x,#L111
 509  0020 cd0000        	call	_assert_failed
 511  0023 5b04          	addw	sp,#4
 512  0025               L05:
 513                     ; 133   switch (Port)
 515  0025 7b02          	ld	a,(OFST+1,sp)
 517                     ; 150   default:
 517                     ; 151     break;
 518  0027 2710          	jreq	L541
 519  0029 4a            	dec	a
 520  002a 2712          	jreq	L741
 521  002c 4a            	dec	a
 522  002d 2718          	jreq	L151
 523  002f 4a            	dec	a
 524  0030 271b          	jreq	L351
 525  0032 4a            	dec	a
 526  0033 2722          	jreq	L551
 527  0035 7b01          	ld	a,(OFST+0,sp)
 528  0037 2023          	jra	LC005
 529  0039               L541:
 530                     ; 135   case EXTI_PORT_GPIOA:
 530                     ; 136     value = (uint8_t)(EXTI->CR1 & EXTI_CR1_PAIS);
 532  0039 c650a0        	ld	a,20640
 533                     ; 137     break;
 535  003c 201c          	jp	LC006
 536  003e               L741:
 537                     ; 138   case EXTI_PORT_GPIOB:
 537                     ; 139     value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_PBIS) >> 2);
 539  003e c650a0        	ld	a,20640
 540  0041 a40c          	and	a,#12
 541  0043 44            	srl	a
 542  0044 44            	srl	a
 543                     ; 140     break;
 545  0045 2015          	jp	LC005
 546  0047               L151:
 547                     ; 141   case EXTI_PORT_GPIOC:
 547                     ; 142     value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_PCIS) >> 4);
 549  0047 c650a0        	ld	a,20640
 550  004a 4e            	swap	a
 551                     ; 143     break;
 553  004b 200d          	jp	LC006
 554  004d               L351:
 555                     ; 144   case EXTI_PORT_GPIOD:
 555                     ; 145     value = (uint8_t)((uint8_t)(EXTI->CR1 & EXTI_CR1_PDIS) >> 6);
 557  004d c650a0        	ld	a,20640
 558  0050 4e            	swap	a
 559  0051 a40c          	and	a,#12
 560  0053 44            	srl	a
 561  0054 44            	srl	a
 562                     ; 146     break;
 564  0055 2003          	jp	LC006
 565  0057               L551:
 566                     ; 147   case EXTI_PORT_GPIOE:
 566                     ; 148     value = (uint8_t)(EXTI->CR2 & EXTI_CR2_PEIS);
 568  0057 c650a1        	ld	a,20641
 569  005a               LC006:
 570  005a a403          	and	a,#3
 571  005c               LC005:
 573                     ; 149     break;
 575                     ; 150   default:
 575                     ; 151     break;
 577                     ; 154   return((EXTI_Sensitivity_TypeDef)value);
 581  005c 85            	popw	x
 582  005d 81            	ret	
 618                     ; 162 EXTI_TLISensitivity_TypeDef EXTI_GetTLISensitivity(void)
 618                     ; 163 {
 619                     .text:	section	.text,new
 620  0000               _EXTI_GetTLISensitivity:
 622       00000001      OFST:	set	1
 625                     ; 164   uint8_t value = 0;
 627                     ; 167   value = (uint8_t)(EXTI->CR2 & EXTI_CR2_TLIS);
 629  0000 c650a1        	ld	a,20641
 630  0003 a404          	and	a,#4
 632                     ; 169   return((EXTI_TLISensitivity_TypeDef)value);
 636  0005 81            	ret	
 649                     	xdef	_EXTI_GetTLISensitivity
 650                     	xdef	_EXTI_GetExtIntSensitivity
 651                     	xdef	_EXTI_SetTLISensitivity
 652                     	xdef	_EXTI_SetExtIntSensitivity
 653                     	xdef	_EXTI_DeInit
 654                     	xref	_assert_failed
 655                     .const:	section	.text
 656  0000               L111:
 657  0000 2e2e5c2e2e5c  	dc.b	"..\..\..\..\librar"
 658  0012 6965735c7374  	dc.b	"ies\stm8s_stdperip"
 659  0024 685f64726976  	dc.b	"h_driver\src\stm8s"
 660  0036 5f657874692e  	dc.b	"_exti.c",0
 680                     	end
