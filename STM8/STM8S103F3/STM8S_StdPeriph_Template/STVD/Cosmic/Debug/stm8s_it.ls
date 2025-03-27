   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.13.2 - 04 Jun 2024
   3                     ; Generator (Limited) V4.6.4 - 15 Jan 2025
   4                     ; Optimizer V4.6.4 - 15 Jan 2025
  50                     ; 50 INTERRUPT_HANDLER(NonHandledInterrupt, 25)
  50                     ; 51 {
  51                     .text:	section	.text,new
  52  0000               f_NonHandledInterrupt:
  56                     ; 55 }
  59  0000 80            	iret	
  81                     ; 63 INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
  81                     ; 64 {
  82                     .text:	section	.text,new
  83  0000               f_TRAP_IRQHandler:
  87                     ; 68 }
  90  0000 80            	iret	
 112                     ; 74 INTERRUPT_HANDLER(TLI_IRQHandler, 0)
 112                     ; 75 {
 113                     .text:	section	.text,new
 114  0000               f_TLI_IRQHandler:
 118                     ; 79 }
 121  0000 80            	iret	
 143                     ; 86 INTERRUPT_HANDLER(AWU_IRQHandler, 1)
 143                     ; 87 {
 144                     .text:	section	.text,new
 145  0000               f_AWU_IRQHandler:
 149                     ; 91 }
 152  0000 80            	iret	
 174                     ; 98 INTERRUPT_HANDLER(CLK_IRQHandler, 2)
 174                     ; 99 {
 175                     .text:	section	.text,new
 176  0000               f_CLK_IRQHandler:
 180                     ; 103 }
 183  0000 80            	iret	
 206                     ; 110 INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
 206                     ; 111 {
 207                     .text:	section	.text,new
 208  0000               f_EXTI_PORTA_IRQHandler:
 212                     ; 115 }
 215  0000 80            	iret	
 238                     ; 122 INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
 238                     ; 123 {
 239                     .text:	section	.text,new
 240  0000               f_EXTI_PORTB_IRQHandler:
 244                     ; 127 }
 247  0000 80            	iret	
 270                     ; 134 INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
 270                     ; 135 {
 271                     .text:	section	.text,new
 272  0000               f_EXTI_PORTC_IRQHandler:
 276                     ; 136 }
 279  0000 80            	iret	
 302                     ; 143 INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
 302                     ; 144 {
 303                     .text:	section	.text,new
 304  0000               f_EXTI_PORTD_IRQHandler:
 308                     ; 148 }
 311  0000 80            	iret	
 334                     ; 155 INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
 334                     ; 156 {
 335                     .text:	section	.text,new
 336  0000               f_EXTI_PORTE_IRQHandler:
 340                     ; 160 }
 343  0000 80            	iret	
 365                     ; 206 INTERRUPT_HANDLER(SPI_IRQHandler, 10)
 365                     ; 207 {
 366                     .text:	section	.text,new
 367  0000               f_SPI_IRQHandler:
 371                     ; 211 }
 374  0000 80            	iret	
 397                     ; 218 INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
 397                     ; 219 {
 398                     .text:	section	.text,new
 399  0000               f_TIM1_UPD_OVF_TRG_BRK_IRQHandler:
 403                     ; 223 }
 406  0000 80            	iret	
 429                     ; 230 INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
 429                     ; 231 {
 430                     .text:	section	.text,new
 431  0000               f_TIM1_CAP_COM_IRQHandler:
 435                     ; 235 }
 438  0000 80            	iret	
 461                     ; 267  INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 461                     ; 268 {
 462                     .text:	section	.text,new
 463  0000               f_TIM2_UPD_OVF_BRK_IRQHandler:
 467                     ; 272 }
 470  0000 80            	iret	
 493                     ; 279  INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
 493                     ; 280 {
 494                     .text:	section	.text,new
 495  0000               f_TIM2_CAP_COM_IRQHandler:
 499                     ; 284 }
 502  0000 80            	iret	
 525                     ; 321  INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
 525                     ; 322 {
 526                     .text:	section	.text,new
 527  0000               f_UART1_TX_IRQHandler:
 531                     ; 326 }
 534  0000 80            	iret	
 557                     ; 333  INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 557                     ; 334 {
 558                     .text:	section	.text,new
 559  0000               f_UART1_RX_IRQHandler:
 563                     ; 338 }
 566  0000 80            	iret	
 588                     ; 346 INTERRUPT_HANDLER(I2C_IRQHandler, 19)
 588                     ; 347 {
 589                     .text:	section	.text,new
 590  0000               f_I2C_IRQHandler:
 594                     ; 351 }
 597  0000 80            	iret	
 619                     ; 426  INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
 619                     ; 427 {
 620                     .text:	section	.text,new
 621  0000               f_ADC1_IRQHandler:
 625                     ; 432     return;
 628  0000 80            	iret	
 651                     ; 455  INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
 651                     ; 456 {
 652                     .text:	section	.text,new
 653  0000               f_TIM4_UPD_OVF_IRQHandler:
 657                     ; 460 }
 660  0000 80            	iret	
 683                     ; 468 INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
 683                     ; 469 {
 684                     .text:	section	.text,new
 685  0000               f_EEPROM_EEC_IRQHandler:
 689                     ; 473 }
 692  0000 80            	iret	
 704                     	xdef	f_EEPROM_EEC_IRQHandler
 705                     	xdef	f_TIM4_UPD_OVF_IRQHandler
 706                     	xdef	f_ADC1_IRQHandler
 707                     	xdef	f_I2C_IRQHandler
 708                     	xdef	f_UART1_RX_IRQHandler
 709                     	xdef	f_UART1_TX_IRQHandler
 710                     	xdef	f_TIM2_CAP_COM_IRQHandler
 711                     	xdef	f_TIM2_UPD_OVF_BRK_IRQHandler
 712                     	xdef	f_TIM1_UPD_OVF_TRG_BRK_IRQHandler
 713                     	xdef	f_TIM1_CAP_COM_IRQHandler
 714                     	xdef	f_SPI_IRQHandler
 715                     	xdef	f_EXTI_PORTE_IRQHandler
 716                     	xdef	f_EXTI_PORTD_IRQHandler
 717                     	xdef	f_EXTI_PORTC_IRQHandler
 718                     	xdef	f_EXTI_PORTB_IRQHandler
 719                     	xdef	f_EXTI_PORTA_IRQHandler
 720                     	xdef	f_CLK_IRQHandler
 721                     	xdef	f_AWU_IRQHandler
 722                     	xdef	f_TLI_IRQHandler
 723                     	xdef	f_TRAP_IRQHandler
 724                     	xdef	f_NonHandledInterrupt
 743                     	end
