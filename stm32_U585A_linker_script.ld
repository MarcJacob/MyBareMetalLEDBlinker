/* Linker Script for STM32-U585Axx board. */

ENTRY(HANDLER_reset)

MEMORY
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 2000K
    SRAM (rwx): ORIGIN = 0x20000000, LENGTH = 768K /* Let's not include SRAM4 or BACKUP for now. */
}

SECTIONS
{
    .irs_vector :
    {
        KEEP(*(.isr_vector))
    }> FLASH

    .text :  
    {
        . = ALIGN(4); /* Align to 32bit lines */

        *(.text)
        _etext = .;
        *(.rodata)
        . = ALIGN(4);
        
    }> FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .;

        *(.data)

        . = ALIGN(4);
        _edata = .;
    }> SRAM AT> FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;

        *(.bss)

        . = ALIGN(4);
        _ebss = .;
    }> SRAM
}