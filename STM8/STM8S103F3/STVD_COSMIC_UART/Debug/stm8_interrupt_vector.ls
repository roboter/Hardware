   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.12.6 - 16 Dec 2021
   3                     ; Generator (Limited) V4.5.4 - 16 Dec 2021
  46                     ; 12 @far @interrupt void NonHandledInterrupt (void)
  46                     ; 13 {
  47                     .text:	section	.text,new
  48  0000               f_NonHandledInterrupt:
  52                     ; 17 	return;
  55  0000 80            	iret
  57                     .const:	section	.text
  58  0000               __vectab:
  59  0000 82            	dc.b	130
  61  0001 00            	dc.b	page(__stext)
  62  0002 0000          	dc.w	__stext
  63  0004 82            	dc.b	130
  65  0005 00            	dc.b	page(f_NonHandledInterrupt)
  66  0006 0000          	dc.w	f_NonHandledInterrupt
  67  0008 82            	dc.b	130
  69  0009 00            	dc.b	page(f_NonHandledInterrupt)
  70  000a 0000          	dc.w	f_NonHandledInterrupt
  71  000c 82            	dc.b	130
  73  000d 00            	dc.b	page(f_NonHandledInterrupt)
  74  000e 0000          	dc.w	f_NonHandledInterrupt
  75  0010 82            	dc.b	130
  77  0011 00            	dc.b	page(f_NonHandledInterrupt)
  78  0012 0000          	dc.w	f_NonHandledInterrupt
  79  0014 82            	dc.b	130
  81  0015 00            	dc.b	page(f_NonHandledInterrupt)
  82  0016 0000          	dc.w	f_NonHandledInterrupt
  83  0018 82            	dc.b	130
  85  0019 00            	dc.b	page(f_NonHandledInterrupt)
  86  001a 0000          	dc.w	f_NonHandledInterrupt
  87  001c 82            	dc.b	130
  89  001d 00            	dc.b	page(f_NonHandledInterrupt)
  90  001e 0000          	dc.w	f_NonHandledInterrupt
  91  0020 82            	dc.b	130
  93  0021 00            	dc.b	page(f_NonHandledInterrupt)
  94  0022 0000          	dc.w	f_NonHandledInterrupt
  95  0024 82            	dc.b	130
  97  0025 00            	dc.b	page(f_NonHandledInterrupt)
  98  0026 0000          	dc.w	f_NonHandledInterrupt
  99  0028 82            	dc.b	130
 101  0029 00            	dc.b	page(f_NonHandledInterrupt)
 102  002a 0000          	dc.w	f_NonHandledInterrupt
 103  002c 82            	dc.b	130
 105  002d 00            	dc.b	page(f_NonHandledInterrupt)
 106  002e 0000          	dc.w	f_NonHandledInterrupt
 107  0030 82            	dc.b	130
 109  0031 00            	dc.b	page(f_NonHandledInterrupt)
 110  0032 0000          	dc.w	f_NonHandledInterrupt
 111  0034 82            	dc.b	130
 113  0035 00            	dc.b	page(f_NonHandledInterrupt)
 114  0036 0000          	dc.w	f_NonHandledInterrupt
 115  0038 82            	dc.b	130
 117  0039 00            	dc.b	page(f_NonHandledInterrupt)
 118  003a 0000          	dc.w	f_NonHandledInterrupt
 119  003c 82            	dc.b	130
 121  003d 00            	dc.b	page(f_NonHandledInterrupt)
 122  003e 0000          	dc.w	f_NonHandledInterrupt
 123  0040 82            	dc.b	130
 125  0041 00            	dc.b	page(f_NonHandledInterrupt)
 126  0042 0000          	dc.w	f_NonHandledInterrupt
 127  0044 82            	dc.b	130
 129  0045 00            	dc.b	page(f_NonHandledInterrupt)
 130  0046 0000          	dc.w	f_NonHandledInterrupt
 131  0048 82            	dc.b	130
 133  0049 00            	dc.b	page(f_NonHandledInterrupt)
 134  004a 0000          	dc.w	f_NonHandledInterrupt
 135  004c 82            	dc.b	130
 137  004d 00            	dc.b	page(f_NonHandledInterrupt)
 138  004e 0000          	dc.w	f_NonHandledInterrupt
 139  0050 82            	dc.b	130
 141  0051 00            	dc.b	page(f_NonHandledInterrupt)
 142  0052 0000          	dc.w	f_NonHandledInterrupt
 143  0054 82            	dc.b	130
 145  0055 00            	dc.b	page(f_NonHandledInterrupt)
 146  0056 0000          	dc.w	f_NonHandledInterrupt
 147  0058 82            	dc.b	130
 149  0059 00            	dc.b	page(f_NonHandledInterrupt)
 150  005a 0000          	dc.w	f_NonHandledInterrupt
 151  005c 82            	dc.b	130
 153  005d 00            	dc.b	page(f_NonHandledInterrupt)
 154  005e 0000          	dc.w	f_NonHandledInterrupt
 155  0060 82            	dc.b	130
 157  0061 00            	dc.b	page(f_NonHandledInterrupt)
 158  0062 0000          	dc.w	f_NonHandledInterrupt
 159  0064 82            	dc.b	130
 161  0065 00            	dc.b	page(f_NonHandledInterrupt)
 162  0066 0000          	dc.w	f_NonHandledInterrupt
 163  0068 82            	dc.b	130
 165  0069 00            	dc.b	page(f_NonHandledInterrupt)
 166  006a 0000          	dc.w	f_NonHandledInterrupt
 167  006c 82            	dc.b	130
 169  006d 00            	dc.b	page(f_NonHandledInterrupt)
 170  006e 0000          	dc.w	f_NonHandledInterrupt
 171  0070 82            	dc.b	130
 173  0071 00            	dc.b	page(f_NonHandledInterrupt)
 174  0072 0000          	dc.w	f_NonHandledInterrupt
 175  0074 82            	dc.b	130
 177  0075 00            	dc.b	page(f_NonHandledInterrupt)
 178  0076 0000          	dc.w	f_NonHandledInterrupt
 179  0078 82            	dc.b	130
 181  0079 00            	dc.b	page(f_NonHandledInterrupt)
 182  007a 0000          	dc.w	f_NonHandledInterrupt
 183  007c 82            	dc.b	130
 185  007d 00            	dc.b	page(f_NonHandledInterrupt)
 186  007e 0000          	dc.w	f_NonHandledInterrupt
 237                     	xdef	__vectab
 238                     	xref	__stext
 239                     	xdef	f_NonHandledInterrupt
 258                     	end
