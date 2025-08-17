#ifndef __FONTS_H
#define __FONTS_H

#include <stdint.h>


// Font structure definition
typedef struct _pFont
{    
	const uint8_t 		*pTable;  		//	Font bitmap data
	uint16_t 			Width; 		 	//	Single character bitmap width
	uint16_t 			Height; 			//	Single character bitmap height
	uint16_t 			Sizes;	 		//	Single character bitmap data size
	uint16_t				Table_Rows;		// This font only has Chinese characters, used to display two-dimensional array size
} pFONT;


/*------------------------------------ Chinese Fonts ---------------------------------------------*/

extern	pFONT	CH_Font12 ;		//	12x12 Chinese
extern	pFONT	CH_Font16 ;    //	16x16 Chinese
extern	pFONT	CH_Font20 ;    //	20x20 Chinese
extern	pFONT	CH_Font24 ;    //	24x24 Chinese
extern	pFONT	CH_Font32 ;    //	32x32 Chinese


/*------------------------------------ ASCII Fonts ---------------------------------------------*/

extern pFONT ASCII_Font32;		// 32x16 ASCII
extern pFONT ASCII_Font24;		// 24x12 ASCII
extern pFONT ASCII_Font20; 	// 20x10 ASCII
extern pFONT ASCII_Font16; 	// 16x8 ASCII
extern pFONT ASCII_Font12; 	// 12x6 ASCII

#endif 