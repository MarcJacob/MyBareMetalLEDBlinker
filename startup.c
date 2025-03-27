/* startup.c: Program start on board reset / startup & Interrupt Vector Table & Interrupt Handlers */

#include <stdint.h>

#define SRAM_START_ADDR (0x20000000)
#define SRAM_SIZE       (768U * 1024U)
#define SRAM_END_ADDR   (SRAM_START_ADDR + SRAM_SIZE)

#define STACK_POINTER_INIT_ADDR (SRAM_END_ADDR) // Set Stack Pointer to start at the very end of Data section.

#define INTERRUPT_VECTOR_TABLE_SIZE 140 // As found in the STM32U585 reference manual.

#define NULL 0U

// Interrupt Handlers Declaration

// Default "stub" handler.
void HANDLER_DEFAULT();

void HANDLER_reset();
/* TODO(Marc): Add further handler declarations */

#define TO_IMPLEMENT (uint32_t)&HANDLER_DEFAULT

// Interrupt Vector Table definition
uint32_t isr_vector[INTERRUPT_VECTOR_TABLE_SIZE] __attribute__((section(".isr_vector"))) = 
{
    // Only implement the initial stack pointer and the Reset routine for bare minimum functionality.
    // Also put in the layout for implementing the rest of the "core" routines of the Cortex-M33 MPU.
    STACK_POINTER_INIT_ADDR,
    (uint32_t)&HANDLER_reset,
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    NULL, // Reserved.
    NULL, // Reserved.
    NULL, // Reserved.
    TO_IMPLEMENT,
    TO_IMPLEMENT,
    NULL, // Reserved.
    TO_IMPLEMENT,
    TO_IMPLEMENT
};

// HANDLER DEFINITIONS
void HANDLER_DEFAULT()
{
    // Do nothing.
}

extern uint32_t _etext, _sdata, _edata, _sbss, _ebss;

// Reset Handler: Copy initialized data from Flash to RAM, zero out .bss region of RAM and call main function.
void main();
void HANDLER_reset()
{
    // Copy data from flash to RAM
    uint32_t data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t* flash_data = (uint8_t*) &_etext; // Points to end of .text and beginning of .rodata
    uint8_t* sram_data = (uint8_t*) &_sdata; // Points to beginning of .data

    for(int i = 0; i < data_size; i++)
    {
        sram_data[i] = flash_data[i];
    }

    // Zero out .bss
    uint32_t bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    uint8_t* bss_data = (uint8_t*)&_sbss; // Points to beginning of .bss

    for (int i = 0; i < bss_size; i++)
    {
        bss_data[i] = 0;
    }

    // Call main function
    main();
}