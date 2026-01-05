#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

// Basic Unity configuration for STM32

#define UNITY_INT_WIDTH 32
#define UNITY_POINTER_WIDTH 32

// Output to serial (you can customize this)
#define UNITY_OUTPUT_CHAR(a) putchar(a)
#define UNITY_OUTPUT_FLUSH() fflush(stdout)
#define UNITY_OUTPUT_START() setvbuf(stdout, NULL, _IONBF, 0)
#define UNITY_OUTPUT_COMPLETE() fflush(stdout)

#endif // UNITY_CONFIG_H
