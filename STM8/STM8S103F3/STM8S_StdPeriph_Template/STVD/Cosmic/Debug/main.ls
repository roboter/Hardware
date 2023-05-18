   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
   4                     ; Optimizer V4.5.4 - 16 Dec 2021
  67                     ; 39 void main(void)
  67                     ; 40 {
  69                     .text:	section	.text,new
  70  0000               _main:
  72  0000 88            	push	a
  73       00000001      OFST:	set	1
  76                     ; 41   uint8_t i = 0;
  78  0001 0f01          	clr	(OFST+0,sp)
  80                     ; 43   CLK_Config();
  82  0003 cd0000        	call	L3_CLK_Config
  84                     ; 45   BEEP_LSICalibrationConfig(LSIMeasurment());
  86  0006 cd0000        	call	_LSIMeasurment
  88  0009 be02          	ldw	x,c_lreg+2
  89  000b 89            	pushw	x
  90  000c be00          	ldw	x,c_lreg
  91  000e 89            	pushw	x
  92  000f cd0000        	call	_BEEP_LSICalibrationConfig
  94  0012 5b04          	addw	sp,#4
  95                     ; 47   enableInterrupts();
  98  0014 9a            	rim	
 100                     ; 49   BEEP_Cmd(DISABLE);
 103  0015 4f            	clr	a
 104  0016 cd0000        	call	_BEEP_Cmd
 106                     ; 50   Delay(100);
 108  0019 ae0064        	ldw	x,#100
 109  001c cd0000        	call	_Delay
 111                     ; 51   BEEP_Init(BEEP_FREQUENCY_1KHZ);
 113  001f 4f            	clr	a
 114  0020 cd0000        	call	_BEEP_Init
 116                     ; 53   BEEP_Cmd(ENABLE);
 118  0023 a601          	ld	a,#1
 119  0025 cd0000        	call	_BEEP_Cmd
 121                     ; 54   Delay(65535);
 123  0028 aeffff        	ldw	x,#65535
 124  002b               LC001:
 125  002b cd0000        	call	_Delay
 127  002e               L73:
 128                     ; 58     i++;
 130  002e 0c01          	inc	(OFST+0,sp)
 132                     ; 60     switch (i)
 134  0030 7b01          	ld	a,(OFST+0,sp)
 135  0032 a104          	cp	a,#4
 136  0034 26f8          	jrne	L73
 139                     ; 87     case 4:
 139                     ; 88       BEEP_Cmd(DISABLE);
 141  0036 4f            	clr	a
 142  0037 cd0000        	call	_BEEP_Cmd
 144                     ; 89        Delay(20000);
 146  003a ae4e20        	ldw	x,#20000
 148                     ; 90       break;
 150  003d 20ec          	jp	LC001
 151                     ; 91     case 5:
 151                     ; 92      // i=0;
 151                     ; 93       break;
 153                     ; 94     default:
 153                     ; 95 
 153                     ; 96       break;
 178                     ; 108 static void CLK_Config(void)
 178                     ; 109 {
 179                     .text:	section	.text,new
 180  0000               L3_CLK_Config:
 184                     ; 112   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
 186  0000 4f            	clr	a
 188                     ; 113 }
 191  0001 cc0000        	jp	_CLK_HSIPrescalerConfig
 225                     ; 119 void Delay(uint16_t nCount)
 225                     ; 120 {
 226                     .text:	section	.text,new
 227  0000               _Delay:
 229  0000 89            	pushw	x
 230       00000000      OFST:	set	0
 233  0001 2003          	jra	L77
 234  0003               L57:
 235                     ; 124     nCount--;
 237  0003 5a            	decw	x
 238  0004 1f01          	ldw	(OFST+1,sp),x
 239  0006               L77:
 240                     ; 122   while (nCount != 0)
 242  0006 1e01          	ldw	x,(OFST+1,sp)
 243  0008 26f9          	jrne	L57
 244                     ; 126 }
 247  000a 85            	popw	x
 248  000b 81            	ret	
 314                     ; 135 uint32_t LSIMeasurment(void)
 314                     ; 136 {
 315                     .text:	section	.text,new
 316  0000               _LSIMeasurment:
 318  0000 520c          	subw	sp,#12
 319       0000000c      OFST:	set	12
 322                     ; 138   uint32_t lsi_freq_hz = 0x0;
 324                     ; 139   uint32_t fmaster = 0x0;
 326                     ; 140   uint16_t ICValue1 = 0x0;
 328                     ; 141   uint16_t ICValue2 = 0x0;
 330                     ; 144   fmaster = CLK_GetClockFreq();
 332  0002 cd0000        	call	_CLK_GetClockFreq
 334  0005 96            	ldw	x,sp
 335  0006 1c0009        	addw	x,#OFST-3
 336  0009 cd0000        	call	c_rtol
 339                     ; 147   AWU->CSR |= AWU_CSR_MSR;
 341  000c 721050f0      	bset	20720,#0
 342                     ; 154   TIM1_ICInit(TIM1_CHANNEL_1, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV8, 0);
 344  0010 4b00          	push	#0
 345  0012 4b0c          	push	#12
 346  0014 4b01          	push	#1
 347  0016 5f            	clrw	x
 348  0017 cd0000        	call	_TIM1_ICInit
 350  001a 5b03          	addw	sp,#3
 351                     ; 157   TIM1_Cmd(ENABLE);
 353  001c a601          	ld	a,#1
 354  001e cd0000        	call	_TIM1_Cmd
 357  0021               L731:
 358                     ; 160   while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
 360  0021 72035255fb    	btjf	21077,#1,L731
 361                     ; 162   ICValue1 = TIM1_GetCapture1();
 363  0026 cd0000        	call	_TIM1_GetCapture1
 365  0029 1f05          	ldw	(OFST-7,sp),x
 367                     ; 163   TIM1_ClearFlag(TIM1_FLAG_CC1);
 369  002b ae0002        	ldw	x,#2
 370  002e cd0000        	call	_TIM1_ClearFlag
 373  0031               L541:
 374                     ; 166   while((TIM1->SR1 & TIM1_FLAG_CC1) != TIM1_FLAG_CC1);
 376  0031 72035255fb    	btjf	21077,#1,L541
 377                     ; 168   ICValue2 = TIM1_GetCapture1();
 379  0036 cd0000        	call	_TIM1_GetCapture1
 381  0039 1f07          	ldw	(OFST-5,sp),x
 383                     ; 169   TIM1_ClearFlag(TIM1_FLAG_CC1);
 385  003b ae0002        	ldw	x,#2
 386  003e cd0000        	call	_TIM1_ClearFlag
 388                     ; 172   TIM1->CCER1 &= (uint8_t)(~TIM1_CCER1_CC1E);
 390  0041 7211525c      	bres	21084,#0
 391                     ; 174   TIM1_Cmd(DISABLE);
 393  0045 4f            	clr	a
 394  0046 cd0000        	call	_TIM1_Cmd
 396                     ; 205   lsi_freq_hz = (8 * fmaster) / (ICValue2 - ICValue1);
 398  0049 1e07          	ldw	x,(OFST-5,sp)
 399  004b 72f005        	subw	x,(OFST-7,sp)
 400  004e cd0000        	call	c_uitolx
 402  0051 96            	ldw	x,sp
 403  0052 5c            	incw	x
 404  0053 cd0000        	call	c_rtol
 407  0056 96            	ldw	x,sp
 408  0057 1c0009        	addw	x,#OFST-3
 409  005a cd0000        	call	c_ltor
 411  005d a603          	ld	a,#3
 412  005f cd0000        	call	c_llsh
 414  0062 96            	ldw	x,sp
 415  0063 5c            	incw	x
 416  0064 cd0000        	call	c_ludv
 418  0067 96            	ldw	x,sp
 419  0068 1c0009        	addw	x,#OFST-3
 420  006b cd0000        	call	c_rtol
 423                     ; 208   AWU->CSR &= (uint8_t)(~AWU_CSR_MSR);
 425  006e 721150f0      	bres	20720,#0
 426                     ; 210   return (lsi_freq_hz);
 428  0072 96            	ldw	x,sp
 429  0073 1c0009        	addw	x,#OFST-3
 430  0076 cd0000        	call	c_ltor
 434  0079 5b0c          	addw	sp,#12
 435  007b 81            	ret	
 470                     ; 222 void assert_failed(u8* file, u32 line)
 470                     ; 223 { 
 471                     .text:	section	.text,new
 472  0000               _assert_failed:
 476  0000               L761:
 477  0000 20fe          	jra	L761
 490                     	xdef	_main
 491                     	xdef	_Delay
 492                     	xdef	_LSIMeasurment
 493                     	xdef	_assert_failed
 494                     	xref	_TIM1_ClearFlag
 495                     	xref	_TIM1_GetCapture1
 496                     	xref	_TIM1_Cmd
 497                     	xref	_TIM1_ICInit
 498                     	xref	_CLK_GetClockFreq
 499                     	xref	_CLK_HSIPrescalerConfig
 500                     	xref	_BEEP_LSICalibrationConfig
 501                     	xref	_BEEP_Cmd
 502                     	xref	_BEEP_Init
 503                     	xref.b	c_lreg
 504                     	xref.b	c_x
 523                     	xref	c_ludv
 524                     	xref	c_uitolx
 525                     	xref	c_llsh
 526                     	xref	c_ltor
 527                     	xref	c_rtol
 528                     	end
