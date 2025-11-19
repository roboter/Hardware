#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v00x_i2c.h"
#include <stdint.h>
#include <stdbool.h>
  #include "main.h"


// Crystal frequency (25MHz for most SI5351 modules)
#define SI5351_XTAL_FREQ 25000000UL

// PLL frequencies
#define SI5351_PLL_A_FREQ 900000000UL  // 900MHz
#define SI5351_PLL_B_FREQ 900000000UL  // 900MHz

static uint32_t pll_a_freq = SI5351_PLL_A_FREQ;
static uint32_t pll_b_freq = SI5351_PLL_B_FREQ;
// SI5351 I2C address
#define SI5351_ADDR 0x60  // 7-bit I2C address
//#define I2C_TIMEOUT 50000

// Register definitions
#define SI5351_DEVICE_STATUS      0
#define SI5351_INTERRUPT_STATUS   1
#define SI5351_INTERRUPT_MASK     2
#define SI5351_PLL_A_SOURCE       15
#define SI5351_PLL_B_SOURCE       16
#define SI5351_CLK0_CONTROL       16
#define SI5351_CLK1_CONTROL       17
#define SI5351_CLK2_CONTROL       18
#define SI5351_CLK3_CONTROL       19
#define SI5351_CLK4_CONTROL       20
#define SI5351_CLK5_CONTROL       21
#define SI5351_CLK6_CONTROL       22
#define SI5351_CLK7_CONTROL       23
#define SI5351_SYNTH_PLL_A        26
#define SI5351_SYNTH_PLL_B        34
#define SI5351_SYNTH_MSNA_0       42
#define SI5351_SYNTH_MSNA_1       43
#define SI5351_SYNTH_MSNA_2       44
#define SI5351_SYNTH_MSNA_3       45
#define SI5351_SYNTH_MSNA_4       46
#define SI5351_SYNTH_MSNA_5       47
#define SI5351_SYNTH_MSNA_6       48
#define SI5351_SYNTH_MSNA_7       49
#define SI5351_SYNTH_MSNB_0       50
#define SI5351_SYNTH_MSNB_1       51
#define SI5351_SYNTH_MSNB_2       52
#define SI5351_SYNTH_MSNB_3       53
#define SI5351_SYNTH_MSNB_4       54
#define SI5351_SYNTH_MSNB_5       55
#define SI5351_SYNTH_MSNB_6       56
#define SI5351_SYNTH_MSNB_7       57
#define SI5351_MULTISYNTH0_0      58
#define SI5351_MULTISYNTH0_1      59
#define SI5351_MULTISYNTH0_2      60
#define SI5351_MULTISYNTH0_3      61
#define SI5351_MULTISYNTH0_4      62
#define SI5351_MULTISYNTH0_5      63
#define SI5351_MULTISYNTH0_6      64
#define SI5351_MULTISYNTH0_7      65
#define SI5351_MULTISYNTH1_0      66
#define SI5351_MULTISYNTH1_1      67
#define SI5351_MULTISYNTH1_2      68
#define SI5351_MULTISYNTH1_3      69
#define SI5351_MULTISYNTH1_4      70
#define SI5351_MULTISYNTH1_5      71
#define SI5351_MULTISYNTH1_6      72
#define SI5351_MULTISYNTH1_7      73
#define SI5351_MULTISYNTH2_0      74
#define SI5351_MULTISYNTH2_1      75
#define SI5351_MULTISYNTH2_2      76
#define SI5351_MULTISYNTH2_3      77
#define SI5351_MULTISYNTH2_4      78
#define SI5351_MULTISYNTH2_5      79
#define SI5351_MULTISYNTH2_6      80
#define SI5351_MULTISYNTH2_7      81
#define SI5351_CLK0_PHOFF_0       90
#define SI5351_CLK0_PHOFF_1       91
#define SI5351_CLK0_PHOFF_2       92
#define SI5351_CLK0_PHOFF_3       93
#define SI5351_CLK1_PHOFF_0       94
#define SI5351_CLK1_PHOFF_1       95
#define SI5351_CLK1_PHOFF_2       96
#define SI5351_CLK1_PHOFF_3       97
#define SI5351_CLK2_PHOFF_0       98
#define SI5351_CLK2_PHOFF_1       99
#define SI5351_CLK2_PHOFF_2       100
#define SI5351_CLK2_PHOFF_3       101
#define SI5351_CRYSTAL_LOAD       183
#define SI5351_FANOUT_ENABLE      187
#define SI5351_MAX_FREQ      900000000UL
// Clock outputs
typedef enum {
    SI5351_CLK0 = 0,
    SI5351_CLK1 = 1,
    SI5351_CLK2 = 2,
    SI5351_CLK3 = 3,
    SI5351_CLK4 = 4,
    SI5351_CLK5 = 5,
    SI5351_CLK6 = 6,
    SI5351_CLK7 = 7
} si5351_clock_t;

// PLL sources
typedef enum {
    SI5351_PLL_A = 0,
    SI5351_PLL_B = 1
} si5351_pll_t;

// Drive strength options
typedef enum {
    SI5351_DRIVE_2MA = 0,
    SI5351_DRIVE_4MA = 1,
    SI5351_DRIVE_6MA = 2,
    SI5351_DRIVE_8MA = 3
} si5351_drive_t;

// Function prototypes
i2c_err_t SI5351_begin(void);
i2c_err_t SI5351_set_freq(uint32_t freq, si5351_clock_t clock, si5351_pll_t pll_source);
void SI5351_set_clock_enable(si5351_clock_t clock, bool enable);
void SI5351_set_clock_invert(si5351_clock_t clock, bool invert);
void SI5351_set_clock_drive(si5351_clock_t clock, si5351_drive_t drive);
i2c_err_t SI5351_output_enable(si5351_clock_t clock, bool enable);
i2c_err_t SI5351_set_crystal_load(uint8_t load);
void SI5351_set_pll_source(si5351_pll_t pll, uint8_t source);
i2c_err_t SI5351_write(uint8_t reg, uint8_t data);
i2c_err_t SI5351_read(uint8_t reg, uint8_t *data);
//void SI5351_bulk_write(uint8_t reg, uint8_t *data, uint8_t length);
i2c_err_t SI5351_bulk_write(uint8_t reg, uint8_t *data, uint8_t length);
i2c_err_t SI5351_setup_pll(si5351_pll_t pll, uint32_t freq) ;
uint8_t SI5351_test_connection(void);

#ifdef __cplusplus
}
#endif