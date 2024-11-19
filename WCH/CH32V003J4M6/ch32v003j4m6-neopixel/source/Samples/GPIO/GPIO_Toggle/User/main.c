#include "debug.h"
#include "ch32v00x_conf.h"

/* Global define */
//#define LED_PIN GPIO_Pin_1
//#define LED_PORT GPIOC


#define LED_PIN GPIO_Pin_6
#define LED_PORT GPIOD
#define NUM_LEDS 1


void WS2812B_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // Enable the clock for GPIOD
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // Configure PD6 as push-pull output
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void delay_cycles(uint32_t cycles) {
    __asm__ volatile (
        "1: \n"            // Label for the loop start
        "addi %0, %0, -1 \n" // Decrement the cycle count
        "bnez %0, 1b \n"   // Branch to label 1 if the cycle count is not zero
        : "=r" (cycles)    // Output operand: cycles is modified in place
        : "0" (cycles)     // Input operand: initial value of cycles
    );
}

void WS2812B_SendBit(uint8_t bit) {
    if (bit) {
        // Bit "1": High for 0.66 µs, Low for 0.59 µs
        GPIOD->BSHR = LED_PIN;  // Set pin high
        __asm__ volatile (
            "li t0, 5 \n"        // Load the cycle count for high time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );

        GPIOD->BCR = LED_PIN;  // Set pin low
        __asm__ volatile (
            "li t0, 1 \n"        // Load the cycle count for low time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );
    } else {
        // Bit "0": High for 0.33 µs, Low for 0.92 µs
        GPIOD->BSHR = LED_PIN;  // Set pin high
        __asm__ volatile (
            "li t0, 4 \n"        // Load the cycle count for high time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );

        GPIOD->BCR = LED_PIN;  // Set pin low
        __asm__ volatile (
            "li t0, 1 \n"        // Load the cycle count for low time
            "1: \n"              // Label for the loop start
            "addi t0, t0, -1 \n" // Decrement the cycle count
            "bnez t0, 1b \n"     // Branch to label 1 if the cycle count is not zero
        );
    }
}

void WS2812B_SendByte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        WS2812B_SendBit((byte << i) & 0x80);
    }
}

void WS2812B_SendColor(uint8_t red, uint8_t green, uint8_t blue) {
    WS2812B_SendByte(green);
    WS2812B_SendByte(red);
    WS2812B_SendByte(blue);
}

void WS2812B_SendColors(uint8_t colors[][3], uint8_t num_leds) {
    for (uint8_t i = 0; i < num_leds; i++) {
        WS2812B_SendColor(colors[i][0], colors[i][1], colors[i][2]);
    }
}

void WS2812B_Rainbow(uint8_t num_leds) {
    uint8_t colors[7][3] = {
        {255, 0, 0},   // Red
        {255, 127, 0}, // Orange
        {255, 255, 0}, // Yellow
        {0, 255, 0},   // Green
        {0, 0, 255},   // Blue
        {75, 0, 130},  // Indigo
        {148, 0, 211}  // Violet
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < num_leds; j++) {
            WS2812B_SendColor(colors[i][0], colors[i][1], colors[i][2]);
        }
        Delay_Ms(10000); // Adjust delay as needed
    }
}

void WS2812B_FadeColors(uint8_t num_leds) {
    uint8_t red, green, blue;
    int step = 5; // Adjust step size for smoother transitions

    // Fade from Red to Blue
    for (red = 255, blue = 0; red > 0; red -= step, blue += step) {
        WS2812B_SendColor(red, 0, blue);
        Delay_Ms(50); // Adjust delay for speed
    }

    // Fade from Blue to Green
    for (blue = 255, green = 0; blue > 0; blue -= step, green += step) {
        WS2812B_SendColor(0, green, blue);
        Delay_Ms(50);
    }

    // Fade from Green to Red
    for (green = 255, red = 0; green > 0; green -= step, red += step) {
        WS2812B_SendColor(red, green, 0);
        Delay_Ms(50);
    }
}

int main(void) {
    SystemInit();
    WS2812B_Init();
		Delay_Init();

    while (1) {			
			 WS2812B_FadeColors(NUM_LEDS);
    }
}
