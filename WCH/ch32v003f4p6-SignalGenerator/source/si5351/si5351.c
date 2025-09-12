#include "si5351.h"
#include "debug.h"
#include <stdio.h>

// Crystal frequency (25MHz for most SI5351 modules)
#define SI5351_XTAL_FREQ 25000000UL

// PLL frequencies
#define SI5351_PLL_A_FREQ 900000000UL  // 900MHz
#define SI5351_PLL_B_FREQ 900000000UL  // 900MHz

static uint32_t pll_a_freq = SI5351_PLL_A_FREQ;
static uint32_t pll_b_freq = SI5351_PLL_B_FREQ;

// Initialize SI5351
void SI5351_init(void) {
    // Basic initialization will be done in begin()
}

// Begin communication with SI5351
bool SI5351_begin(void) {
    // Reset SI5351
    SI5351_write(0xB7, 0xAC);  // Reset device
    Delay_Ms(10);
    
    // Disable all outputs
    SI5351_write(3, 0xFF);
    
    // Power down all output drivers
    for(uint8_t i = 16; i <= 23; i++) {
        SI5351_write(i, 0x80);
    }
    
    // Set crystal load capacitance (typically 6-10pF)
    SI5351_set_crystal_load(6);
    
    // Configure PLLs
    SI5351_setup_pll(SI5351_PLL_A, SI5351_PLL_A_FREQ);
    SI5351_setup_pll(SI5351_PLL_B, SI5351_PLL_B_FREQ);
    
    return true;
}

// Set frequency for a specific clock output
void SI5351_set_freq(uint32_t freq, si5351_clock_t clock, si5351_pll_t pll_source) {
    uint32_t pll_freq = (pll_source == SI5351_PLL_A) ? pll_a_freq : pll_b_freq;
    uint32_t divider = pll_freq / freq;
    
    if(divider % 2) divider--;  // Ensure even divider
    
    
    // Calculate multisynth parameters
    uint32_t a = divider / 4;
    uint32_t b = divider % 4;
    uint32_t c = 1;
    
    // Set multisynth parameters
    uint8_t params[8];
    params[0] = (a >> 8) & 0xFF;
    params[1] = a & 0xFF;
    params[2] = (b >> 8) & 0xFF;
    params[3] = b & 0xFF;
    params[4] = c & 0xFF;
    params[5] = 0x00;
    params[6] = 0x00;
    params[7] = 0x00;
    
    // Write to appropriate multisynth registers
    uint8_t base_reg = 0;
    switch(clock) {
        case SI5351_CLK0: base_reg = SI5351_MULTISYNTH0_0; break;
        case SI5351_CLK1: base_reg = SI5351_MULTISYNTH1_0; break;
        case SI5351_CLK2: base_reg = SI5351_MULTISYNTH2_0; break;
        default: return;
    }
    
    SI5351_bulk_write(base_reg, params, 8);
    
    // Configure clock control register
    uint8_t ctrl_reg = 0x0F;  // Basic settings
    ctrl_reg |= (pll_source << 5);  // PLL source
    ctrl_reg |= (SI5351_DRIVE_8MA << 0);  // Drive strength
    
    SI5351_write(SI5351_CLK0_CONTROL + clock, ctrl_reg);
}

// Setup PLL
void SI5351_setup_pll(si5351_pll_t pll, uint32_t freq) {
    uint32_t divider = freq / SI5351_XTAL_FREQ;
    uint32_t a = divider;
    uint32_t b = 0;
    uint32_t c = 1;
    
    uint8_t params[8];
    params[0] = (a >> 8) & 0xFF;
    params[1] = a & 0xFF;
    params[2] = (b >> 8) & 0xFF;
    params[3] = b & 0xFF;
    params[4] = c & 0xFF;
    params[5] = 0x00;
    params[6] = 0x00;
    params[7] = 0x00;
    
    uint8_t base_reg = (pll == SI5351_PLL_A) ? SI5351_SYNTH_MSNA_0 : SI5351_SYNTH_MSNB_0;
    SI5351_bulk_write(base_reg, params, 8);
}

// Enable/disable clock output
void SI5351_output_enable(si5351_clock_t clock, bool enable) {
    uint8_t reg_val = SI5351_read(3);
    if(enable) {
        reg_val &= ~(1 << clock);
    } else {
        reg_val |= (1 << clock);
    }
    SI5351_write(3, reg_val);
}

// Set crystal load capacitance
void SI5351_set_crystal_load(uint8_t load) {
    uint8_t reg_val = SI5351_read(SI5351_CRYSTAL_LOAD);
    reg_val &= 0xF0;
    reg_val |= (load & 0x0F);
    SI5351_write(SI5351_CRYSTAL_LOAD, reg_val);
}

// Write to SI5351 register
void SI5351_write(uint8_t reg, uint8_t data) {
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1, SI5351_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    I2C_SendData(I2C1, reg);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    
    I2C_SendData(I2C1, data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    I2C_GenerateSTOP(I2C1, ENABLE);
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

// Read from SI5351 register
uint8_t SI5351_read(uint8_t reg) {
    uint8_t data = 0;
    
    // Write register address
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1, SI5351_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    I2C_SendData(I2C1, reg);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    // Restart for read
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1, SI5351_ADDR, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    
    // Read data
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    data = I2C_ReceiveData(I2C1);
    
    I2C_GenerateSTOP(I2C1, ENABLE);
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
    
    return data;
}

// Bulk write to SI5351
void SI5351_bulk_write(uint8_t reg, uint8_t *data, uint8_t length) {
    I2C_GenerateSTART(I2C1, ENABLE);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
    
    I2C_Send7bitAddress(I2C1, SI5351_ADDR, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
    I2C_SendData(I2C1, reg);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    
    for(uint8_t i = 0; i < length; i++) {
        I2C_SendData(I2C1, data[i]);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
    }
    
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    I2C_GenerateSTOP(I2C1, ENABLE);
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}


// Test SI5351 connection
uint8_t SI5351_test_connection(void) {
    // Try to read from a known SI5351 register
    // Register 0 (Device Status) is a good candidate as it's always readable
    
    I2C_GenerateSTART(I2C1, ENABLE);
    uint32_t timeout = 100000;
    
    // Wait for START condition
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if(timeout-- == 0) {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 1; // START timeout
        }
    }
    
    // Send SI5351 address (7-bit address is 0x3C for write)
    I2C_Send7bitAddress(I2C1, SI5351_ADDR , I2C_Direction_Transmitter);
    timeout = 100000;
    
    // Wait for address acknowledgment
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        if(I2C_GetFlagStatus(I2C1, I2C_FLAG_AF)) {
            I2C_ClearFlag(I2C1, I2C_FLAG_AF);
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 2; // Address not acknowledged
        }
        if(timeout-- == 0) {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 3; // Address timeout
        }
    }
    
    // Send register address (0x00 - Device Status)
    I2C_SendData(I2C1, 0x00);
    timeout = 100000;
    
    // Wait for byte transmission
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        if(timeout-- == 0) {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 4; // Register write timeout
        }
    }
    
    // Generate repeated START for read
    I2C_GenerateSTART(I2C1, ENABLE);
    timeout = 100000;
    
    // Wait for repeated START
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) {
        if(timeout-- == 0) {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 5; // Repeated START timeout
        }
    }
    
    // Send SI5351 address for read
    I2C_Send7bitAddress(I2C1, SI5351_ADDR, I2C_Direction_Receiver);
    timeout = 100000;
    
    // Wait for address acknowledgment
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
        if(I2C_GetFlagStatus(I2C1, I2C_FLAG_AF)) {
            I2C_ClearFlag(I2C1, I2C_FLAG_AF);
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 6; // Read address not acknowledged
        }
        if(timeout-- == 0) {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 7; // Read address timeout
        }
    }
    
    // Read data with NACK (since we're only reading one byte)
    I2C_AcknowledgeConfig(I2C1, DISABLE);
    
    timeout = 100000;
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
        if(timeout-- == 0) {
            I2C_AcknowledgeConfig(I2C1, ENABLE);
            I2C_GenerateSTOP(I2C1, ENABLE);
            return 8; // Data read timeout
        }
    }
    
    uint8_t status = I2C_ReceiveData(I2C1);
    
    // Generate STOP condition
    I2C_GenerateSTOP(I2C1, ENABLE);
    timeout = 100000;
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF)) {
        if(timeout-- == 0) break;
    }
    
    I2C_AcknowledgeConfig(I2C1, ENABLE);
    
    // If we got here, the device responded
    // We can also check if the status register value makes sense
    // Bit 7 should be 0 (not busy), other bits might vary
    if(status & 0x80) {
        return 9; // Device is busy (not necessarily an error)
    }
    
    return 0; // Success
}
