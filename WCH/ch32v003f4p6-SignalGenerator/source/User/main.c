#include "main.h"
#include <ch32v00x_gpio.h>
#include <ch32v00x_i2c.h>
#include <ch32v00x_rcc.h>
#include <debug.h>
#include <si5351.h>
#include <ssd1306.h>
#include <ssd1306_font.h>
#include <string.h>

#define IF                                                                     \
  455 // Enter your IF frequency, ex: 455 = 455kHz, 10700 = 10.7MHz,  0 = to
      // direct convert receiver or RF generator, + will
// VFO Parameters
static uint32_t freq = 127100000; // 7.1 MHz default
static uint32_t interfreq = 0;    // IF frequency
static uint8_t stp = 3;           // Step index
static uint8_t sts = 0;           // RX/TX status
static uint8_t s_meter = 5;       // S-meter value (0-9)
static const uint8_t total_digits = 8;

static uint8_t select_digit = 0;
uint8_t count, x, xo;

// Band definitions
typedef struct {
  const char *name;
  uint32_t start;
  uint32_t end;
} Band;

const Band bands[] = {
    {"160m", 1800000, 2000000},  {"80m", 3500000, 4000000},
    {"40m", 7000000, 7300000},   {"30m", 10100000, 10150000},
    {"20m", 14000000, 14350000}, {"17m", 18068000, 18168000},
    {"15m", 21000000, 21450000}, {"12m", 24890000, 24990000},
    {"10m", 28000000, 29700000},
};

// Function prototypes
void update_frequency(int32_t change);
void change_step(void);
const char *get_current_band(void);

long pow10(int n) {
  if (n <= 0)
    return 1; // 10^0 = 1, guard negative
  long result = 1;
  for (int i = 0; i < n; i++) {
    result *= 10;
    // optional: could check overflow here
  }
  return result;
}

void decrement_freq() {
  // use total_digits-1 - select_digit to get correct place value
  int exp = (int)total_digits - (int)select_digit;
  if (exp < 0)
    exp = 0;
  int64_t delta = pow10(exp);
  if ((int64_t)freq >= delta) {
    freq -= (uint32_t)delta;
  } else {
    freq = 0; // prevent underflow
  }
}

void increment_freq() {
  int exp = (int)total_digits - (int)select_digit;
  if (exp < 0)
    exp = 0;
  int64_t delta = pow10(exp);
  if ((int64_t)freq + delta <= (int64_t)SI5351_MAX_FREQ) {
    freq += (uint32_t)delta;
  } else {
    freq = SI5351_MAX_FREQ; // prevent overflow
  }
}

// Get step size based on stp index
uint32_t get_step_size(void) {
  switch (stp) {
  case 0:
    return 1;
  case 1:
    return 10;
  case 2:
    return 100;
  case 3:
    return 1000; // 1kHz default
  case 4:
    return 10000; // 10kHz
  case 5:
    return 100000; // 100kHz
  case 6:
    return 1000000; // 1MHz
  default:
    return 1000;
  }
}

// Get current band name
const char *get_current_band(void) {
  for (uint8_t i = 0; i < sizeof(bands) / sizeof(Band); i++) {
    if (freq >= bands[i].start && freq <= bands[i].end) {
      return bands[i].name;
    }
  }
  return "GEN";
}

// Update frequency with bounds checking
void update_frequency(int32_t change) {
  int64_t new_freq = (int64_t)freq + change;

  // Bounds: 10kHz to 225MHz (SI5351 range)
  if (new_freq < 10000)
    new_freq = 10000;
  if (new_freq > 225000000)
    new_freq = 225000000;

  freq = (uint32_t)new_freq;

  // Update SI5351 (you'll need to implement this)
  SI5351_set_freq(freq, 0, SI5351_PLL_A_FREQ);
}

// Change step size
void change_step(void) {
  stp++;
  if (stp > 6)
    stp = 0;
}

void bandlist() {
  const char *band_names[] = {"GEN", "MW",  "160m", "80m", "60m", "49m", "40m",
                              "31m", "25m", "22m",  "20m", "19m", "16m", "13m",
                              "11m", "10m", "6m",   "WFM", "AIR", "2m",  "1m"};

  OLED_setTextSize(2);

  if (count >= 1 &&
      count <= (int)(sizeof(band_names) / sizeof(band_names[0]))) {
    OLED_setCursor(0, 25);
    OLED_print(band_names[count - 1]);
  }

  if (count == 1) {
    interfreq = 0;
  } else if (!sts) {
    interfreq = IF;
  }
}

void layout_ui(void) {
  OLED_clear();
  OLED_setTextColor(White);

  char freq_str[16];
  uint32_t mhz = freq / 1000000;
  uint32_t khz = (freq % 1000000) / 1000;
  uint32_t hz = freq % 1000;

  // ensure correct types for printf-like formatting
  sprintf(freq_str, "%03lu%03lu%03lu", (unsigned long)mhz, (unsigned long)khz,
          (unsigned long)hz);

  // Draw frequency with large text
  OLED_setTextSize(2);
  OLED_drawSymbol(select_digit * 12, 14, CHAR_UP_S, White);
  OLED_drawSymbol(select_digit * 12, 14 * 3 - 5, CHAR_DOWN_S, White);

  OLED_drawSymbol(40, 0, CHAR_CURSOR, White);

  // OLED_setCursor(0, 20);
  OLED_setpos(0, 4);
  OLED_print(freq_str);

  OLED_setTextSize(1);

  OLED_drawSymbol(60, 0, CHAR_CURSOR, White);
  OLED_drawSymbol(61, 8, CHAR_CURSOR, White);

  // Unit (MHz/kHz)
  //    OLED_setTextSize(1);
  //    OLED_setCursor(108, 32);
  //    if(freq < 1000000)
  //        OLED_print("kHz");
  //    else
  //        OLED_print("MHz");

  // RX/TX indicator
  //    OLED_setTextSize(1);
  //    if(!sts) {
  //        OLED_fillRect(0, 0, 20, 12, White);
  //        OLED_setTextColor(Black);
  //        OLED_setCursor(2, 2);
  //        OLED_print("RX");
  //        OLED_setTextColor(White);
  //    } else {
  //        OLED_drawRect(0, 0, 20, 12, White);
  //        OLED_setCursor(2, 2);
  //        OLED_print("TX");
  //    }
  //
  //    // Band indicator
  //    OLED_setCursor(23, 2);
  //    OLED_print(get_current_band());
  //
  //    // VFO/LO mode
  //    OLED_setCursor(55, 2);
  //    if(interfreq == 0)
  //        OLED_print("VFO");
  //    else
  //        OLED_print("LO");
  //
  //    // Draw step size box
  //    OLED_drawRect(88, 0, 40, 12, White);
  //    OLED_setCursor(90, 2);
  //    OLED_print("STEP");
  //
  //    OLED_setCursor(90, 8);
  //    uint32_t step = get_step_size();
  //    if(step >= 1000000) {
  //        OLED_printf("%luM", step / 1000000);
  //    } else if(step >= 1000) {
  //        OLED_printf("%luk", step / 1000);
  //    } else {
  //        OLED_printf("%luHz", step);
  //    }
  //
  //    // IF frequency if applicable
  //    if(interfreq > 0) {
  //        OLED_setCursor(0, 48);
  //        OLED_print("IF:");
  //        OLED_printf("%lukHz", interfreq / 1000);
  //    }
  //
  //    // S-meter
  //    OLED_setCursor(0, 56);
  //    OLED_print("S:");
  //    OLED_drawBargraph(12, 56, 60, 6, 9, s_meter);
  //
  //    if(s_meter >= 9) {
  //        OLED_setCursor(75, 56);
  //        OLED_print("+20");
  //    }

  OLED_display();
}

// Keep your existing functions
void GPIO_Buttons_INIT(void) {
  GPIO_InitTypeDef GPIO_InitStructure = {0};
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = ENTER | UP | DOWN | RIGHT | LEFT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
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

int main(void) {
  Delay_Init();
  GPIO_Buttons_INIT();
  USART_Printf_Init(115200);
  printf("SystemClk:%lu\r\n", (unsigned long)SystemCoreClock);
  printf("VFO/RF Generator v2.0\r\n");

  // Initialize I2C
  i2c_device_t dev = {
      .clkr = I2C_CLK_400KHZ,
      .type = I2C_ADDR_7BIT,
      .addr = 0x68,
      .regb = 1,
      .tout = 2000,
  };

  if (I2C_HAL_Init(&dev) != I2C_OK) {
    printf("Failed to init I2C Bus\n");
  }

  // Initialize OLED
  OLED_init();
  OLED_clear();

  // Splash screen
  //    OLED_setTextSize(2);
  //    OLED_setCursor(10, 10);
  //    OLED_print("VFO/RF");
  //    OLED_setTextSize(1);
  //    OLED_setCursor(15, 30);
  //    OLED_print("Generator v2.0");
  //    OLED_drawRect(0, 0, 128, 64, White);
  //    OLED_update();
  Delay_Ms(2000);
  //    OLED_clear();

  // Initialize SI5351
  i2c_err_t err = SI5351_begin();
  if (err != I2C_OK) {
    OLED_clear();
    OLED_setCursor(10, 20);
    OLED_print("SI5351 Error!");
    OLED_update();
    printf("Error initializing SI5351: %d\n", err);
    Delay_Ms(2000);
  }

  // Main UI
  layout_ui();

  // Button state tracking
  static uint8_t last_button_state = 0;
  static uint32_t button_press_time = 0;
  static uint32_t repeat_timer = 0;
  static uint8_t repeat_count = 0;

  while (1) {
    // Read buttons
    uint8_t up = GPIO_ReadInputDataBit(BUTTONPORT, UP);
    uint8_t right = GPIO_ReadInputDataBit(BUTTONPORT, RIGHT);
    uint8_t left = GPIO_ReadInputDataBit(BUTTONPORT, LEFT);
    uint8_t down = GPIO_ReadInputDataBit(BUTTONPORT, DOWN);
    uint8_t enter = GPIO_ReadInputDataBit(BUTTONPORT, ENTER);

    uint8_t current_state =
        (up << 0) | (down << 1) | (left << 2) | (right << 3) | (enter << 4);

    // Check for button press (low to high transition)
    if (current_state != last_button_state) {
      last_button_state = current_state;
      button_press_time = 0;
      repeat_count = 0;

      // Handle button actions
      if (up) {
        printf("UP - Increase Frequency\n");
        increment_freq();
        layout_ui();

      } else if (down) {
        printf("DOWN - Decrease Frequency\n");
        decrement_freq();
        layout_ui();

      } else if (right) {
        printf("RIGHT - Increase Step\n");
        // allow select_digit in range 0..(total_digits-1)
        if (select_digit < total_digits)
          select_digit++;
        layout_ui();

      } else if (left) {
        printf("LEFT - Decrease Step\n");
        if (select_digit > 0)
          select_digit--;
        layout_ui();

      } else if (enter) {
        printf("ENTER - Toggle RX/TX\n");
        sts = !sts;
        if (sts) {
          interfreq = 0; // TX mode, no IF
        } else {
          interfreq = IF; // RX mode, use IF frequency
        }
        layout_ui();
      }
    }

    // Button repeat logic (for fast frequency changes)
    if (current_state != 0) {
      button_press_time++;

      // Initial delay before repeat
      if (button_press_time > 30) {
        repeat_timer++;

        // Repeat rate increases with time
        uint32_t repeat_delay = (repeat_count < 10) ? 10 : 5;

        if (repeat_timer >= repeat_delay) {
          repeat_timer = 0;
          repeat_count++;

          if (up) {
            increment_freq();
            //    update_frequency(get_step_size());
            layout_ui();
          } else if (down) {
            decrement_freq();
            //      update_frequency(-get_step_size());
            layout_ui();
          }
        }
      }
    }

    // Simulate S-meter update (in real use, read from ADC)
    static uint32_t s_meter_counter = 0;
    if (++s_meter_counter > 50) {
      s_meter_counter = 0;
      // Random S-meter for demo (replace with actual signal strength)
      s_meter = (s_meter + 1) % 10;
      layout_ui();
    }

    Delay_Ms(10); // Faster polling for better responsiveness
  }
}
