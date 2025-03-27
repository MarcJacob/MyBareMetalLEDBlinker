#include <stdio.h>
#include <stdint.h>

// We seek to make a specific Red LED ("LD6") blink. I am using the B-U585l-IOT02A Discovery Kit.
// For that, we need to enable clock functionality on the GPIOH Port, located on the AHB2 bus as specified in the
// STM32U585 datasheet.
// That done, Pin 6 of GPIO Port H ("PH6") needs to have its mode set to Output. Only then can we finally set its associated data register
// to alternating 0 and 1 and make the associated LED blink.
// I can't believe how complex this is. Maybe I should have bought a simpler board to start with.

#define AHB2_BASE_ADDR (0x42020000)

#define RCC_BASE_ADDR (0x46020C00)
#define RCC_AHB2_PERIPHERAL_ENABLE_REG1_OFFSET (0x08C) // GPIOH ENABLE = BIT 7

#define GPIO_PORT_MODE_OFFSET (0x00) // For PH6: bits 13 & 12
#define GPIO_PORT_OUTPUT_DATA_OFFSET (0x14) // For PH6: bit 6

#define RCC_AHB2_PERIPHERAL_ENABLE_REG1 ((volatile uint32_t*)(RCC_BASE_ADDR + RCC_AHB2_PERIPHERAL_ENABLE_REG1_OFFSET))
#define GPIOH_BASE_ADDR (AHB2_BASE_ADDR + 0x1C00)
#define GPIOH_MODE_ADDR ((volatile uint32_t*)(GPIOH_BASE_ADDR + GPIO_PORT_MODE_OFFSET))
#define GPIOH_OUTPUT_DATA_ADDR ((volatile uint32_t*)(GPIOH_BASE_ADDR + GPIO_PORT_OUTPUT_DATA_OFFSET))

#define LED_PIN_NUMBER 6

int main()
{
    //printf("Hello World ! This is my own minimalistic from scratch program running !\nIt's been deployed by OpenOCD. Linker script & all code written by me !\n");
    
    // Enable Clock for GPIOH then run a few dummy reads to make sure it's actually enabled afterwards.
    *RCC_AHB2_PERIPHERAL_ENABLE_REG1 |= (1 << 7);

    volatile uint32_t dummyRead;
    dummyRead = *RCC_AHB2_PERIPHERAL_ENABLE_REG1;
    dummyRead = *RCC_AHB2_PERIPHERAL_ENABLE_REG1;

    // Set GPIOH6 Mode to Output (Set bit 13 to 0 and bit 12 to 1)
    *GPIOH_MODE_ADDR &= ~(1 << 13);
    *GPIOH_MODE_ADDR |= (1 << 12);

    // Now let's loop, setting the pin's value to high and low in alternance.
    while(1)
    {
        *GPIOH_OUTPUT_DATA_ADDR ^= (1 << LED_PIN_NUMBER);
        for (uint32_t i = 0; i < 1000000; i++);
    }

    return 0;
}