   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
2202                     ; 17 void CLK_Init()
2202                     ; 18 {
2204                     .text:	section	.text,new
2205  0000               _CLK_Init:
2209                     ; 19 	CLK_CKDIVR = 0x00; // Set Clock 16MHz
2211  0000 725f50c6      	clr	_CLK_CKDIVR
2212                     ; 20 	CLK_PCKENR1 = 0xFF; // Enable peripherals
2214  0004 35ff50c7      	mov	_CLK_PCKENR1,#255
2215                     ; 21 }
2218  0008 81            	ret
2245                     ; 23 void UART_Init()
2245                     ; 24 {	
2246                     .text:	section	.text,new
2247  0000               _UART_Init:
2251                     ; 28 	UART1_CR3 &= ~((1<<4)| (1<<4)); //1 stop bit
2253  0000 72195236      	bres	_UART1_CR3,#4
2254                     ; 31 	UART1_BRR1 = 0x68;
2256  0004 35685232      	mov	_UART1_BRR1,#104
2257                     ; 33 	UART1_BRR2 = 0x03;
2259  0008 35035233      	mov	_UART1_BRR2,#3
2260                     ; 35 	UART1_CR2 |= (1<<2) | (1 << 3); // Enable RX and TX
2262  000c c65235        	ld	a,_UART1_CR2
2263  000f aa0c          	or	a,#12
2264  0011 c75235        	ld	_UART1_CR2,a
2265                     ; 38 }
2268  0014 81            	ret
2304                     ; 40 void UART_TX(unsigned char send)
2304                     ; 41 {
2305                     .text:	section	.text,new
2306  0000               _UART_TX:
2310                     ; 42 	UART1_DR = send;
2312  0000 c75231        	ld	_UART1_DR,a
2314  0003               L3741:
2315                     ; 43 	while(!(UART1_SR & (1<<6)));
2317  0003 c65230        	ld	a,_UART1_SR
2318  0006 a540          	bcp	a,#64
2319  0008 27f9          	jreq	L3741
2320                     ; 44 }
2323  000a 81            	ret
2348                     ; 46 unsigned char UART_RX(void)
2348                     ; 47 {
2349                     .text:	section	.text,new
2350  0000               _UART_RX:
2354  0000               L1151:
2355                     ; 48 		while(!(UART1_SR & (1<<5)));
2357  0000 c65230        	ld	a,_UART1_SR
2358  0003 a520          	bcp	a,#32
2359  0005 27f9          	jreq	L1151
2360                     ; 49 		return UART1_DR;
2362  0007 c65231        	ld	a,_UART1_DR
2365  000a 81            	ret
2405                     ; 52 void main()
2405                     ; 53 {
2406                     .text:	section	.text,new
2407  0000               _main:
2409  0000 88            	push	a
2410       00000001      OFST:	set	1
2413                     ; 54 	CLK_Init();
2415  0001 cd0000        	call	_CLK_Init
2417                     ; 55 	UART_Init();
2419  0004 cd0000        	call	_UART_Init
2421                     ; 56 	delay (100);
2423  0007 ae0064        	ldw	x,#100
2424  000a cd0000        	call	_delay
2426  000d               L3351:
2427                     ; 58 		unsigned char inChar = 0;
2429                     ; 59 		if(UART1_SR & (1<<5))
2431  000d c65230        	ld	a,_UART1_SR
2432  0010 a520          	bcp	a,#32
2433  0012 27f9          	jreq	L3351
2434                     ; 61 			inChar = UART_RX();
2436  0014 cd0000        	call	_UART_RX
2438  0017 6b01          	ld	(OFST+0,sp),a
2440                     ; 63 			UART_TX(inChar);
2442  0019 7b01          	ld	a,(OFST+0,sp)
2443  001b cd0000        	call	_UART_TX
2445  001e 20ed          	jra	L3351
2498                     ; 68 void delay (int ms) //create delay function
2498                     ; 69 {
2499                     .text:	section	.text,new
2500  0000               _delay:
2502  0000 89            	pushw	x
2503  0001 5204          	subw	sp,#4
2504       00000004      OFST:	set	4
2507                     ; 70 	int i = 0;
2509                     ; 71 	int j = 0;
2511                     ; 72 	for (i=0; i<=ms; i++)
2513  0003 5f            	clrw	x
2514  0004 1f01          	ldw	(OFST-3,sp),x
2517  0006 201a          	jra	L3751
2518  0008               L7651:
2519                     ; 74 		for (j=0; j<120; j++) // Nop = Fosc/4
2521  0008 5f            	clrw	x
2522  0009 1f03          	ldw	(OFST-1,sp),x
2524  000b               L7751:
2525                     ; 75 			_asm("nop"); //Perform no operation //assembly code <span style="white-space:pre"> </span>
2528  000b 9d            nop
2530                     ; 74 		for (j=0; j<120; j++) // Nop = Fosc/4
2532  000c 1e03          	ldw	x,(OFST-1,sp)
2533  000e 1c0001        	addw	x,#1
2534  0011 1f03          	ldw	(OFST-1,sp),x
2538  0013 9c            	rvf
2539  0014 1e03          	ldw	x,(OFST-1,sp)
2540  0016 a30078        	cpw	x,#120
2541  0019 2ff0          	jrslt	L7751
2542                     ; 72 	for (i=0; i<=ms; i++)
2544  001b 1e01          	ldw	x,(OFST-3,sp)
2545  001d 1c0001        	addw	x,#1
2546  0020 1f01          	ldw	(OFST-3,sp),x
2548  0022               L3751:
2551  0022 9c            	rvf
2552  0023 1e01          	ldw	x,(OFST-3,sp)
2553  0025 1305          	cpw	x,(OFST+1,sp)
2554  0027 2ddf          	jrsle	L7651
2555                     ; 77 }
2558  0029 5b06          	addw	sp,#6
2559  002b 81            	ret
2572                     	xdef	_main
2573                     	xdef	_UART_RX
2574                     	xdef	_UART_TX
2575                     	xdef	_delay
2576                     	xdef	_UART_Init
2577                     	xdef	_CLK_Init
2596                     	end
