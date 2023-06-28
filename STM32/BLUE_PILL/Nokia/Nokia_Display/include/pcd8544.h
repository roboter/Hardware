#ifndef __PCD8544_H__
#define __PCD8544_H__
#include <stdint.h>
#include <stdbool.h>

/// alias
#define  pcd8544_clear() pcd8544_fill_fb(0x0)
#define lcd_print(x,y,z)   pcd8544_print_string(x,y,z)
#define  lcd_print_invert(s,x,y) pcd8544_print_string_invert_fb(s,x,y)
#define  lcd_print_big(s,x,y) pcd8544_send_char_size2_fb(s,x,y)
#define  lcd_print_hugo(s,x,y) pcd8544_send_char_size3_fb(s,x,y)

// functions
void pcd8544_init();
void pcd8544_fill_fb(uint8_t value);
void pcd8544_display_fb();
void pcd8544_off();
void pcd8544_print_string(char *str, uint8_t x, uint8_t y);
void pcd8544_print_string_invert_fb(char *str, uint8_t x, uint8_t y);
void pcd8544_send_char_size2_fb(uint8_t ch, uint8_t x, uint8_t y);
void pcd8544_send_char_size3_fb(uint8_t ch, uint8_t x, uint8_t y);
void pcd8544_print_uint8_at(uint8_t num, uint8_t size, uint8_t x, uint8_t y);
void pcd8544_send_char(uint8_t ch,bool inverse);
void pcd8544_mirror();

#endif      // __PCD8544_H__
