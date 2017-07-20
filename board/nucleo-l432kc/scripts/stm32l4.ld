/*linker script for STM32*/
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256k
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 32k
}

/* Definition de la fonction a executer au demarrage */
ENTRY(_arch_start)

/* definir la taille de la pile systeme */
STACK_SIZE = 4096;
SECTIONS
{
    .armvectors : {
        *(.armvectors)      /* ARM interrupt vectors */
    } > FLASH

    .text ALIGN(4) : {
        *(.text .text.*)        /* main code */
        *(.glue_7)              /* required by linker */
        *(.glue_7t)             /* required by linker */
        *(.rodata .rodata.*)    /* read only data */
    } > FLASH

    /* The initizlized data is always stored after the text section */

    _data_init_start = .; /* start of init data */
    _data_init_end = _data_init_start + _data_end - _data_start;
    . = _data_init_end;
    . = ALIGN(2048);
    _userflash_start = .; /* This symbol is the beginning of the next sector after the code */


    . = 0x20000000;

    .stack ALIGN(4) : {
        /* stack is reserved at begininning of RAM, addresses are descending so stack overflow will explode instead of overwriting data */
        . += STACK_SIZE;
        _stack_end = .;
    } > RAM

    /* compile-time RAM contents */
    .data ALIGN(4) : {
        _data_start = .;
        *(.data .data.*)    /* initialized data */
        *(.igot.plt)
        _data_end = .;
    } > RAM AT > FLASH      /* where to store the initialized contents! */

    .bss ALIGN(4) : {
        _bss_start = .;
        *(.bss)             /* uninitialized data */
        *(COMMON)
        _bss_end = .;
    } > RAM

	/* useful for gdb, not loaded in device memory */
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }
	.debug_loc 0 : { *(.debug_loc) }
	.debug_str 0 : { *(.debug_str) }
	.debug_frame 0 : { *(.debug_frame) }
}
