// 13x32 7-segment digits font
static const uint8_t OLED_FONT[] = {
  0xFC, 0x7F, 0xFF, 0x1F, 0xF9, 0x3F, 0xFE, 0x4F, 0xF3, 0x1F, 0xFC, 0x67,
  0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70,
  0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70,
  0x07, 0x00, 0x00, 0x70, 0xF3, 0x1F, 0xFC, 0x67, 0xF9, 0x3F, 0xFE, 0x4F,
  0xFC, 0x7F, 0xFF, 0x1F, // 0
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0xFC, 0x07, 0xF8, 0x3F, 0xFE, 0x0F,
  0xFC, 0x7F, 0xFF, 0x1F, // 1
  0x00, 0x00, 0xFF, 0x1F, 0x01, 0x00, 0xFE, 0x4F, 0x03, 0x80, 0xFC, 0x67,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01 ,0x70, 0xF3, 0x9F, 0x00, 0x60, 0xF9, 0x3F, 0x00, 0x40,
  0xFC, 0x7F, 0x00, 0x00, // 2
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x03, 0x80, 0x00, 0x60,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0xF3, 0x9F, 0xFC, 0x67, 0xF9, 0x3F, 0xFE, 0x4F,
  0xFC, 0x7F, 0xFF, 0x1F, // 3
  0xFC, 0x7F, 0x00, 0x00, 0xF8, 0x3F, 0x00, 0x00, 0xF0, 0x9F, 0x00, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0xF0, 0x9F, 0xFC, 0x07, 0xF8, 0x3F, 0xFE, 0x0F,
  0xFC, 0x7F, 0xFF, 0x1F, // 4
  0xFC, 0x7F, 0x00, 0x00, 0xF9, 0x3F, 0x00, 0x40, 0xF3, 0x9F, 0x00, 0x60,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x03, 0x80, 0xFC, 0x67, 0x01, 0x00, 0xFE, 0x4F,
  0x00, 0x00, 0xFF, 0x1F, // 5
  0xFC, 0x7F, 0xFF, 0x1F, 0xF9, 0x3F, 0xFE, 0x4F, 0xF3, 0x9F, 0xFC, 0x67,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x03, 0x80, 0xFC, 0x67, 0x01, 0x00, 0xFE, 0x4F,
  0x00, 0x00, 0xFF, 0x1F, // 6
  0xFC, 0x7F, 0x00, 0x00, 0xF9, 0x3F, 0x00, 0x00, 0xF3, 0x1F, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0xF3, 0x1F, 0xFC, 0x07, 0xF9, 0x3F, 0xFE, 0x0F,
  0xFC, 0x7F, 0xFF, 0x1F, // 7
  0xFC, 0x7F, 0xFF, 0x1F, 0xF9, 0x3F, 0xFE, 0x4F, 0xF3, 0x9F, 0xFC, 0x67,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0xF3, 0x9F, 0xFC, 0x67, 0xF9, 0x3F, 0xFE, 0x4F,
  0xFC, 0x7F, 0xFF, 0x1F, // 8
  0xFC, 0x7F, 0x00, 0x00, 0xF9, 0x3F, 0x00, 0x40, 0xF3, 0x9F, 0x00, 0x60,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70, 0x07, 0xC0, 0x01, 0x70,
  0x07, 0xC0, 0x01, 0x70, 0xF3, 0x9F, 0xFC, 0x67, 0xF9, 0x3F, 0xFE, 0x4F,
  0xFC, 0x7F, 0xFF, 0x1F, // 9
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x7C, 0x00, 0x00, 0x1F, 0x7C, 0x00,
  0x00, 0x1F, 0x7C, 0x00, 0x00, 0x1F, 0x7C, 0x00, 0x00, 0x1F, 0x7C, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, // : (10)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x7C,
  0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x7C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, // . (11)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, // - (12)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xFC, 0x1F, 0x00,
  0x00, 0xFE, 0x3F, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, // + (13)
  0xFC, 0x7F, 0xFF, 0x1F, 0xF8, 0x3F, 0xFE, 0x4F, 0xF0, 0x9F, 0xFC, 0x67,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0x80, 0xFC, 0x67, 0x00, 0x00, 0xFE, 0x4F,
  0x00, 0x00, 0xFF, 0x1F, // b (14)
  0x00, 0x00, 0xFF, 0x1F, 0x00, 0x00, 0xFE, 0x4F, 0x00, 0x80, 0xFC, 0x67,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70, 0x00, 0xC0, 0x01, 0x70,
  0x00, 0xC0, 0x01, 0x70, 0xF0, 0x9F, 0xFC, 0x67, 0xF8, 0x3F, 0xFE, 0x4F,
  0xFC, 0x7F, 0xFF, 0x1F, // d (15)
  0xFC, 0x7F, 0xFF, 0x1F, 0xF9, 0x3F, 0xFE, 0x0F, 0xF3, 0x1F, 0xFC, 0x07,
  0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0xE7, 0x1F, 0x00, 0x00,
  0xF7, 0x3F, 0x00, 0x00, 0xE7, 0x1F, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0xF3, 0x1F, 0xFC, 0x07, 0xF9, 0x3F, 0xFE, 0x0F,
  0xFC, 0x7F, 0xFF, 0x1F, // M (16)
  0xFC, 0x7F, 0xFF, 0x1F, 0xF8, 0x3F, 0xFE, 0x0F, 0xF0, 0x9F, 0xFC, 0x07,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0xC0, 0x01, 0x00,
  0x00, 0xC0, 0x01, 0x00, 0xF0, 0x9F, 0xFC, 0x07, 0xF8, 0x3F, 0xFE, 0x0F,
  0xFC, 0x7F, 0xFF, 0x1F, // H (17)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x80, 0x00, 0x60,
  0x00, 0xC0, 0x01, 0x76, 0x00, 0xC0, 0x81, 0x77, 0x00, 0xC0, 0xE1, 0x73,
  0x00, 0xC0, 0xF9, 0x71, 0x00, 0xC0, 0x7D, 0x70, 0x00, 0xC0, 0x1D, 0x70,
  0x00, 0xC0, 0x01, 0x70, 0x00, 0x80, 0x00, 0x60, 0x00, 0x00, 0x00, 0x40,
  0x00, 0x00, 0x00, 0x00  // z (18)
};