#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

// Bit manipulation macros for common operations

// Set a specific bit in the register
// Usage: BIT_SET(PORTA, 5); // Sets bit 5 in PORTA
#define BIT_SET(reg, bit)     ((reg) |= (1U << (bit)))

// Clear a specific bit in the register
// Usage: BIT_CLEAR(PORTA, 5); // Clears bit 5 in PORTA
#define BIT_CLEAR(reg, bit)   ((reg) &= ~(1U << (bit)))

// Toggle a specific bit in the register
// Usage: BIT_TOGGLE(PORTA, 5); // Toggles bit 5 in PORTA
#define BIT_TOGGLE(reg, bit)  ((reg) ^= (1U << (bit)))

// Check if a specific bit is set
// Usage: if (BIT_IS_SET(PORTA, 5)) { ... } // Checks if bit 5 is set in PORTA
#define BIT_IS_SET(reg, bit)  (((reg) & (1U << (bit))) != 0)

// Check if a specific bit is clear
// Usage: if (BIT_IS_CLEAR(PORTA, 5)) { ... } // Checks if bit 5 is clear in PORTA
#define BIT_IS_CLEAR(reg, bit) (((reg) & (1U << (bit))) == 0)

// Mask-based operations

// Set bits specified by the mask
// Usage: BITS_SET(PORTA, 0x0F); // Sets bits 0-3 in PORTA
#define BITS_SET(reg, mask)   ((reg) |= (mask))

// Clear bits specified by the mask
// Usage: BITS_CLEAR(PORTA, 0x0F); // Clears bits 0-3 in PORTA
#define BITS_CLEAR(reg, mask) ((reg) &= ~(mask))

// Toggle bits specified by the mask
// Usage: BITS_TOGGLE(PORTA, 0x0F); // Toggles bits 0-3 in PORTA
#define BITS_TOGGLE(reg, mask) ((reg) ^= (mask))

// Set multiple specific bits
// Usage: BIT_SET_2(PORTA, 0, 1); // Sets bits 0 and 1 in PORTA
#define BIT_SET_2(reg, bit1, bit2) ((reg) |= ((1U << (bit1)) | (1U << (bit2))))

// Usage: BIT_SET_3(PORTA, 0, 1, 2); // Sets bits 0, 1, and 2 in PORTA
#define BIT_SET_3(reg, bit1, bit2, bit3) ((reg) |= ((1U << (bit1)) | (1U << (bit2)) | (1U << (bit3))))

// Usage: BIT_SET_4(PORTA, 0, 1, 2, 3); // Sets bits 0, 1, 2, and 3 in PORTA
#define BIT_SET_4(reg, bit1, bit2, bit3, bit4) ((reg) |= ((1U << (bit1)) | (1U << (bit2)) | (1U << (bit3)) | (1U << (bit4))))

#endif // BIT_MANIPULATION_H