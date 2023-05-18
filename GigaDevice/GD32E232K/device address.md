To read a memory address on an ARM controller using C language, you can use a pointer variable to access the address and read its contents. Here's an example code snippet:

```c
// declare a pointer variable of the appropriate data type
volatile uint32_t* memory_address;

// set the pointer to the desired memory address
memory_address = (uint32_t*) 0x1FFF F7B0;

// read the contents of the memory address
uint32_t data = *memory_address;
```

In this example, we're declaring a volatile pointer variable `memory_address` of type `uint32_t*`, which is a pointer to a 32-bit unsigned integer. We then set the pointer to the desired memory address `0x1FFF F7B0`. Finally, we read the contents of the memory address by dereferencing the pointer using the `*` operator and storing the data in a variable `data`.

Note that it's important to use the `volatile` keyword in the pointer declaration when accessing memory-mapped registers or other memory locations that can change unexpectedly, as it informs the compiler that the value can change at any time and should not be optimized away. Also, the exact syntax may vary depending on the specific ARM controller and the C compiler being used.