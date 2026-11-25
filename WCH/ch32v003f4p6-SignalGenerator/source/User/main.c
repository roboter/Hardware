#include "main.h"
#include <ch32v00x_gpio.h>
#include <ch32v00x_i2c.h>
#include <ch32v00x_rcc.h>
#include <debug.h>
#include <si5351.h>
#include <ssd1306.h>
#include <ssd1306_font.h>

#define SI5351_MIN_FREQ 10000UL
#define SI5351_MAX_USER_FREQ 225000000UL
#define LONG_PRESS_TICKS 50 /* 50 * 10ms = 500 ms */

typedef enum {
  TAB_CLK0 = 0,
  TAB_CLK1,
  TAB_CLK2,
  TAB_SYS
} ui_tab_t;

typedef enum {
  FOCUS_TABS = 0,
  FOCUS_DIAL,
  FOCUS_CONFIG
} ui_focus_t;

static const uint32_t step_table[9] = {
    100000000UL, 10000000UL, 1000000UL, 100000UL, 10000UL,
    1000UL,      100UL,      10UL,      1UL};

static const char *const step_labels[9] = {
    "100M", "10M", "1M", "100k", "10k", "1k", "100", "10", "1"};

static const uint32_t if_offsets[3] = {0UL, 455000UL, 10700000UL};
static const char *const if_labels[3] = {"0", "455k", "10.7M"};

/* Per-channel state */
static uint32_t ch_freq[3] = {145000000UL, 10700000UL, 7100000UL};
static uint8_t ch_enabled[3] = {1, 0, 0};
static uint8_t ch_digit[3] = {4, 4, 4}; /* Default: 10 kHz step */

/* UI & Config state */
static ui_tab_t active_tab = TAB_CLK0;
static ui_focus_t active_focus = FOCUS_DIAL;
static uint8_t dial_curved = 1;
static uint8_t if_mode = 0;   /* 0:VFO, 1:+455k, 2:+10.7M */
static uint8_t cfg_idx = 0;   /* 0:DIAL, 1:IF */

static void apply_channel_hw(uint8_t ch) {
  if (ch >= 3)
    return;
  uint32_t out_freq = ch_freq[ch] + if_offsets[if_mode];
  if (out_freq > SI5351_MAX_USER_FREQ)
    out_freq = SI5351_MAX_USER_FREQ;
  SI5351_set_freq(out_freq, (si5351_clock_t)ch, SI5351_PLL_A);
  SI5351_output_enable((si5351_clock_t)ch, ch_enabled[ch] ? true : false);
}

static void tune_channel(uint8_t ch, int8_t dir) {
  if (ch >= 3)
    return;
  uint32_t step = step_table[ch_digit[ch]];
  uint32_t f = ch_freq[ch];

  if (dir > 0) {
    if (f + step <= SI5351_MAX_USER_FREQ && f + step >= f) {
      f += step;
    } else {
      f = SI5351_MAX_USER_FREQ;
    }
  } else {
    if (f >= SI5351_MIN_FREQ + step) {
      f -= step;
    } else {
      f = SI5351_MIN_FREQ;
    }
  }

  ch_freq[ch] = f;
  apply_channel_hw(ch);
}

static void format_freq_str(uint32_t f, char *buf) {
  /* Format as XXX.XXX.XXX (11 chars + NUL) without sprintf bloat */
  uint8_t d[9];
  for (int8_t i = 8; i >= 0; i--) {
    d[i] = (uint8_t)(f % 10);
    f /= 10;
  }
  buf[0] = '0' + d[0];
  buf[1] = '0' + d[1];
  buf[2] = '0' + d[2];
  buf[3] = '.';
  buf[4] = '0' + d[3];
  buf[5] = '0' + d[4];
  buf[6] = '0' + d[5];
  buf[7] = '.';
  buf[8] = '0' + d[6];
  buf[9] = '0' + d[7];
  buf[10] = '0' + d[8];
  buf[11] = '\0';
}

static uint8_t format_scale_label(uint32_t f, uint32_t step_hz, char *buf) {
  /* Compact 5-char label for drum scale: MHz.tenths or kHz.tenths */
  uint32_t whole, frac;
  if (step_hz >= 10000UL) {
    whole = f / 1000000UL;
    frac = (f % 1000000UL) / 100000UL;
  } else if (step_hz >= 10UL) {
    whole = (f / 1000UL) % 1000UL;
    frac = (f % 1000UL) / 100UL;
  } else {
    whole = f % 1000UL;
    frac = 0;
  }

  uint8_t pos = 0;
  if (whole >= 100) {
    buf[pos++] = '0' + (uint8_t)((whole / 100) % 10);
    buf[pos++] = '0' + (uint8_t)((whole / 10) % 10);
  } else if (whole >= 10) {
    buf[pos++] = '0' + (uint8_t)(whole / 10);
  }
  buf[pos++] = '0' + (uint8_t)(whole % 10);
  if (step_hz >= 10UL) {
    buf[pos++] = '.';
    buf[pos++] = '0' + (uint8_t)frac;
  }
  buf[pos] = '\0';
  return pos;
}

static void draw_clipped_str(int16_t x, uint8_t y, const char *s) {
  while (*s) {
    if (x >= 0 && x <= 122) {
      OLED_drawChar((uint8_t)x, y, *s, White, 1);
    }
    x += 6;
    s++;
  }
}

/* Zero-RAM column renderer for Retro Drum Dial (Pages 5..6, Y=40..55) */
static uint16_t render_dial_column(uint8_t x, int32_t center_pos,
                                   int32_t min_pos, int32_t max_pos) {
  if (x == 64)
    return 0xFFFF; /* Fixed center hairline */

  uint8_t droop = 0;
  if (dial_curved) {
    uint16_t dx = (x < 64) ? (uint16_t)(64 - x) : (uint16_t)(x - 64);
    droop = (uint8_t)((dx * dx) >> 9);
  }

  int32_t tick_pos = center_pos + ((int32_t)x - 64);
  if (tick_pos < min_pos || tick_pos > max_pos)
    return 0x0000;

  uint16_t col_bits = 0x0000;
  int32_t mod40 = ((tick_pos % 40) + 40) % 40;

  if (tick_pos == min_pos || tick_pos == max_pos) {
    col_bits = 0x03FF; /* Limit stop bar */
  } else if (mod40 == 0) {
    col_bits = 0x00FF; /* Major tick (8 px tall) */
  } else if (mod40 == 20) {
    col_bits = 0x003E; /* Half-way tick (5 px tall) */
  } else if ((mod40 & 0x03) == 0) {
    col_bits = 0x000E; /* Minor vernier tick (3 px tall) */
  }

  return (uint16_t)(col_bits << droop);
}

static void draw_top_bar(uint8_t active_ch) {
  static const char *const tab_names[4] = {"CLK0", "CLK1", "CLK2", "SYS"};
  static const uint8_t tab_x[4] = {1, 27, 53, 79};
  static const uint8_t tab_w[4] = {24, 24, 24, 18};

  OLED_setTextSize(1);
  for (uint8_t i = 0; i < 4; i++) {
    if (i == (uint8_t)active_tab) {
      OLED_fillRect(tab_x[i] - 1, 1, tab_w[i] + 2, 10, White);
      OLED_setTextColor(Inverse);
      OLED_setCursor(tab_x[i], 2);
      OLED_print(tab_names[i]);
      OLED_setTextColor(White);
    } else {
      OLED_setCursor(tab_x[i], 2);
      OLED_print(tab_names[i]);
    }
    if (i == (uint8_t)active_tab && active_focus == FOCUS_TABS) {
      OLED_drawFastHLine(tab_x[i] - 1, 13, tab_w[i] + 2, White);
    }
  }

  /* Divider and Output Status */
  OLED_drawFastVLine(100, 1, 11, White);
  if (ch_enabled[active_ch]) {
    OLED_fillRect(103, 1, 24, 10, White);
    OLED_setTextColor(Inverse);
    OLED_setCursor(109, 2);
    OLED_print("ON");
    OLED_setTextColor(White);
  } else {
    OLED_drawRect(103, 1, 24, 10, White);
    OLED_setCursor(106, 2);
    OLED_print("OFF");
  }
  OLED_drawFastHLine(0, 15, 128, White);
}

static void draw_retro_dial(uint8_t ch) {
  uint32_t f = ch_freq[ch];
  uint32_t step_hz = step_table[ch_digit[ch]];
  char buf[16];

  /* Blue Zone 1 (Y=16..29): Digital Readout + Active Digit Underline */
  format_freq_str(f, buf);
  OLED_setTextSize(1);
  OLED_setCursor(2, 17);
  OLED_print(buf);

  /* Underline / caret under active digit */
  uint8_t d = ch_digit[ch];
  uint8_t char_idx = d + (d >= 3 ? 1 : 0) + (d >= 6 ? 1 : 0);
  uint8_t ux = 2 + char_idx * 6;
  if (active_focus == FOCUS_DIAL) {
    OLED_drawFastHLine(ux, 26, 5, White);
    OLED_drawPixel(ux + 2, 27, White);
  } else {
    OLED_drawFastHLine(ux, 26, 5, White);
  }

  /* Step size on right */
  OLED_setCursor(76, 17);
  OLED_print("STP:");
  OLED_print(step_labels[ch_digit[ch]]);

  if (active_focus == FOCUS_CONFIG) {
    /* Bottom Config Strip (Y=32..63) */
    OLED_drawFastHLine(0, 31, 128, White);
    OLED_setCursor(2, 37);
    OLED_print(cfg_idx == 0 ? ">DIAL: " : " DIAL: ");
    OLED_print(dial_curved ? "CURVED" : "FLAT");

    OLED_setCursor(2, 49);
    OLED_print(cfg_idx == 1 ? ">IF  : " : " IF  : ");
    OLED_print(if_labels[if_mode]);
    return;
  }

  uint8_t *fb = OLED_getBuffer();

  /* Full-range min..max limit gauge bar (Y=28..30 in Page 3) */
  uint8_t pos_x = (uint8_t)(f / 1800000UL);
  if (pos_x > 125)
    pos_x = 125;
  uint8_t *p3 = fb + 3 * 128;
  p3[0] |= 0x70;
  p3[127] |= 0x70;
  p3[pos_x] |= 0x20;
  p3[pos_x + 1] |= 0x20;

  /* Blue Zone 2 (Y=31..39): Sliding Major Scale Numbers */
  uint32_t center_steps = f / step_hz;
  uint32_t center_major = center_steps - (center_steps % 10);
  int16_t x_major = 64 - (int16_t)((center_steps % 10) * 4);

  for (int8_t k = -2; k <= 2; k++) {
    int32_t m_steps = (int32_t)center_major + (int32_t)k * 10;
    if (m_steps < 0)
      continue;
    uint32_t m_freq = (uint32_t)m_steps * step_hz;
    if (m_freq < SI5351_MIN_FREQ || m_freq > SI5351_MAX_USER_FREQ)
      continue;
    int16_t tx = x_major + (int16_t)k * 40;
    if (tx < -15 || tx > 142)
      continue;
    uint8_t len = format_scale_label(m_freq, step_hz, buf);
    draw_clipped_str(tx - (int16_t)(len * 3), 31, buf);
  }

  /* Blue Zone 2/3 (Pages 5..6, Y=40..55): Zero-RAM Drum Dial Columns */
  int32_t center_pos = (int32_t)(center_steps * 4);
  int32_t min_pos = (int32_t)((SI5351_MIN_FREQ / step_hz) * 4);
  int32_t max_pos = (int32_t)((SI5351_MAX_USER_FREQ / step_hz) * 4);
  for (uint8_t col = 0; col < 128; col++) {
    uint16_t bits = render_dial_column(col, center_pos, min_pos, max_pos);
    fb[5 * 128 + col] |= (uint8_t)(bits & 0xFF);
    fb[6 * 128 + col] |= (uint8_t)((bits >> 8) & 0xFF);
  }

  /* Blue Zone 3 (Y=56..63): Center Fiducial Pointer (solid=ON, hollow=OFF) */
  if (ch_enabled[ch]) {
    OLED_fillTriangle(61, 63, 67, 63, 64, 57, White);
  } else {
    OLED_drawTriangle(61, 63, 67, 63, 64, 57, White);
  }

  /* Subtle mode & IF indicators on bottom corners */
  OLED_setCursor(2, 56);
  OLED_print(if_mode ? "LO" : "VFO");
  OLED_setCursor(104, 56);
  OLED_print(dial_curved ? "CRV" : "FLT");
}

static void draw_sys_view(void) {
  char buf[16];
  OLED_setTextSize(1);
  for (uint8_t i = 0; i < 3; i++) {
    uint8_t y = 18 + i * 11;
    OLED_setCursor(2, y);
    buf[0] = 'C';
    buf[1] = '0' + i;
    buf[2] = ':';
    buf[3] = '\0';
    OLED_print(buf);
    format_freq_str(ch_freq[i], buf);
    OLED_print(buf);
    OLED_setCursor(104, y);
    OLED_print(ch_enabled[i] ? "[ON]" : "[--]");
  }
  OLED_drawFastHLine(0, 52, 128, White);
  OLED_setCursor(2, 55);
  OLED_print("IF:");
  OLED_print(if_labels[if_mode]);
}

void layout_ui(void) {
  uint8_t active_ch = (active_tab <= TAB_CLK2) ? (uint8_t)active_tab : 0;
  OLED_clear();
  OLED_setTextColor(White);

  draw_top_bar(active_ch);
  if (active_tab == TAB_SYS) {
    draw_sys_view();
  } else {
    draw_retro_dial(active_ch);
  }

  OLED_display();
}

void GPIO_Buttons_INIT(void) {
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = ENTER | UP | DOWN | RIGHT | LEFT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(BUTTONPORT, &GPIO_InitStructure);
}

i2c_err_t I2C_HAL_Init(i2c_device_t *dev) {
  if (dev->regb == 0)
    dev->regb = 1;
  if (dev->regb > 4)
    dev->regb = 4;

  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB2PeriphClockCmd(I2C_PORT_RCC | RCC_APB2Periph_AFIO, ENABLE);

  AFIO->PCFR1 &= ~(0x04400002);
  AFIO->PCFR1 |= I2C_AFIO_REG;

  GPIO_InitTypeDef GPIO_InitStructure = {0};
  GPIO_InitStructure.GPIO_Pin = (1 << I2C_PIN_SDA) | (1 << I2C_PIN_SCL);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(I2C_PORT, &GPIO_InitStructure);

  I2C1->CTLR2 &= ~I2C_CTLR2_FREQ;
  I2C1->CTLR2 |= (SystemCoreClock / 1000000) & I2C_CTLR2_FREQ;

  if (dev->clkr <= 100000) {
    I2C1->CKCFGR = (SystemCoreClock / (2 * dev->clkr)) & I2C_CKCFGR_CCR;
  } else {
    I2C1->CKCFGR =
        ((SystemCoreClock / (3 * dev->clkr)) & I2C_CKCFGR_CCR) | I2C_CKCFGR_FS;
  }

  I2C_Cmd(I2C1, ENABLE);
  return I2C_OK;
}

static void handle_short_nav(uint8_t up, uint8_t down, uint8_t left,
                           uint8_t right) {
  uint8_t ch = (active_tab <= TAB_CLK2) ? (uint8_t)active_tab : 0;

  if (active_focus == FOCUS_TABS) {
    if (right) {
      active_tab = (ui_tab_t)((active_tab + 1) & 0x03);
    } else if (left) {
      active_tab = (ui_tab_t)((active_tab + 3) & 0x03);
    } else if (up || down) {
      ch_enabled[ch] = !ch_enabled[ch];
      apply_channel_hw(ch);
    }
  } else if (active_focus == FOCUS_DIAL) {
    if (active_tab == TAB_SYS)
      return;
    if (up) {
      tune_channel(ch, 1);
    } else if (down) {
      tune_channel(ch, -1);
    } else if (right) {
      if (ch_digit[ch] < 8)
        ch_digit[ch]++;
    } else if (left) {
      if (ch_digit[ch] > 0)
        ch_digit[ch]--;
    }
  } else { /* FOCUS_CONFIG */
    if (up || down) {
      if (cfg_idx == 0) {
        dial_curved = !dial_curved;
      } else {
        if_mode = (uint8_t)((if_mode + (up ? 1 : 2)) % 3);
        for (uint8_t i = 0; i < 3; i++)
          apply_channel_hw(i);
      }
    } else if (left || right) {
      cfg_idx = !cfg_idx;
    }
  }
}

int main(void) {
  Delay_Init();
  GPIO_Buttons_INIT();
  USART_Printf_Init(115200);

  i2c_device_t dev = {
      .clkr = I2C_CLK_400KHZ,
      .type = I2C_ADDR_7BIT,
      .addr = 0x68,
      .regb = 1,
      .tout = 2000,
  };

  I2C_HAL_Init(&dev);

  OLED_init();
  OLED_clear();
  Delay_Ms(200);

  if (SI5351_begin() != I2C_OK) {
    OLED_setCursor(10, 24);
    OLED_print("SI5351 Error!");
    OLED_update();
    Delay_Ms(1000);
  } else {
    for (uint8_t i = 0; i < 3; i++) {
      apply_channel_hw(i);
    }
  }

  layout_ui();

  uint8_t last_state = 0;
  uint32_t press_ticks = 0;
  uint32_t repeat_ticks = 0;
  uint8_t repeat_count = 0;
  uint8_t enter_long_handled = 0;

  while (1) {
    uint8_t up = GPIO_ReadInputDataBit(BUTTONPORT, UP);
    uint8_t down = GPIO_ReadInputDataBit(BUTTONPORT, DOWN);
    uint8_t left = GPIO_ReadInputDataBit(BUTTONPORT, LEFT);
    uint8_t right = GPIO_ReadInputDataBit(BUTTONPORT, RIGHT);
    uint8_t enter = GPIO_ReadInputDataBit(BUTTONPORT, ENTER);

    uint8_t state =
        (up << 0) | (down << 1) | (left << 2) | (right << 3) | (enter << 4);

    if (state != last_state) {
      /* Detect ENTER short press on release if long press didn't fire */
      if ((last_state & (1 << 4)) && !enter && !enter_long_handled) {
        if (active_tab == TAB_SYS) {
          active_focus = (active_focus == FOCUS_TABS) ? FOCUS_CONFIG : FOCUS_TABS;
        } else {
          active_focus = (ui_focus_t)((active_focus + 1) % 3);
        }
        layout_ui();
      }

      last_state = state;
      press_ticks = 0;
      repeat_ticks = 0;
      repeat_count = 0;
      enter_long_handled = 0;

      if (up || down || left || right) {
        handle_short_nav(up, down, left, right);
        layout_ui();
      }
    } else if (state != 0) {
      press_ticks++;

      /* ENTER long press (500 ms): toggle active channel output ON/OFF */
      if (enter && !enter_long_handled && press_ticks >= LONG_PRESS_TICKS) {
        uint8_t ch = (active_tab <= TAB_CLK2) ? (uint8_t)active_tab : 0;
        ch_enabled[ch] = !ch_enabled[ch];
        apply_channel_hw(ch);
        enter_long_handled = 1;
        layout_ui();
      }

      /* Smooth 15-20 Hz auto-repeat for UP/DOWN tuning in Dial mode */
      if ((up || down) && active_focus == FOCUS_DIAL && active_tab <= TAB_CLK2 &&
          press_ticks > 25) {
        repeat_ticks++;
        uint8_t delay_ticks = (repeat_count < 10) ? 7 : 5; /* ~14-20 Hz */
        if (repeat_ticks >= delay_ticks) {
          repeat_ticks = 0;
          repeat_count++;
          tune_channel((uint8_t)active_tab, up ? 1 : -1);
          layout_ui();
        }
      }
    }

    Delay_Ms(10);
  }
}
