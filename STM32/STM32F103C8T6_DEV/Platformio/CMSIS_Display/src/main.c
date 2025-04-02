#include <stm32f10x_conf.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_spi.h>
#include "font5x7.h"
#include <delay.h>
#include <st7735.h>
#include <garmin-digits.h>


uint8_t i;


int main(void)
{
	 // Initialize display
	 ST7789_BLK_On();
	 ST7789_Init();
	 ST7789_BLK_On();
	 ST7789_Fill_Color(BLUE); // Clear screen
	 ST7789_BLK_On();
	 // Display text strings
	//  ST7789_WriteString(0, 0, "Hello beautiful screen!", Font_7x10, RED, BLACK);
	//  ST7789_WriteString(0, 12, "This is 7x10 font", Font_7x10, GREEN, BLACK);
	//  ST7789_WriteString(0, 24, "Screen 240x240 pixels", Font_7x10, BLUE, BLACK);
	 
	 // Set display orientation (if needed)
	 // ST7789_SetRotation(0); // Normal orientation
	 
	 while(1) {
		 // Display big digits (simulated with filled rectangles)
		 // Digit 2
		//  ST7789_DrawFilledRectangle(0, 35, 15, 70, RGB565(212,246,190));
		//  ST7789_DrawFilledRectangle(0, 35, 15, 45, BLACK);
		//  ST7789_DrawFilledRectangle(0, 60, 15, 70, BLACK);
		 
		//  // Digit 3
		//  ST7789_DrawFilledRectangle(16, 35, 31, 70, RGB565(212,246,190));
		//  ST7789_DrawFilledRectangle(16, 35, 31, 45, BLACK);
		//  ST7789_DrawFilledRectangle(16, 60, 31, 70, BLACK);
		 
		//  // Colon
		 ST7789_DrawFilledRectangle(33, 42, 35, 44, RGB565(177,211,190));
	  ST7789_DrawFilledRectangle(33, 67, 35, 69, RGB565(177,211,190));
		 
		//  // Digit 4
		//  ST7789_DrawFilledRectangle(37, 35, 52, 70, RGB565(212,246,190));
		//  ST7789_DrawFilledRectangle(37, 35, 52, 45, BLACK);
		 
		//  // Digit 8
		//  ST7789_DrawFilledRectangle(53, 35, 68, 70, RGB565(212,246,190));
		 
		//  // Colon
		//  ST7789_DrawFilledRectangle(70, 42, 72, 44, RGB565(177,211,190));
		//  ST7789_DrawFilledRectangle(70, 67, 72, 69, RGB565(177,211,190));
		 
		//  // Digit 5
		//  ST7789_DrawFilledRectangle(75, 35, 90, 70, RGB565(212,246,190));
		//  ST7789_DrawFilledRectangle(75, 60, 90, 70, BLACK);
		 
		//  // Digit 6
		//  ST7789_DrawFilledRectangle(91, 35, 106, 70, RGB565(212,246,190));
		 
		//  // Time label
		//  ST7789_WriteString(0, 80, "Time:", Font_7x10, WHITE, BLACK);
		 
		 // Add delay to prevent flickering
		 DelayMs(100);
	 }

}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    /* User can add his own implementation to report the file name and line number */
    while (1) {}
}
#endif