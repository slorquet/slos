/*linker script for STM32*/
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256k
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 32k
}

/* Definition de la fonction a executer au demarrage */
ENTRY(_startup)

/* definir la taille de la pile systeme */
STACK_SIZE = 4096;
SECTIONS
{
    .armvectors : {
        *(.armvectors)      /* ARM interrupt vectors /
    } > FLASH

    .text ALIGN(4) : {
        *(.text .text.*)    /* main code */
        *(.rodata)          /* read only data */
        *(.glue_7)          /* required by linker */
        *(.glue_7t)         /* required by linker */
    } > FLASH

    _data_init_start = .; /* start of init data */

    . = 0x20000000;

    .stack ALIGN(4) : {
        /* stack is reserved at begininning of RAM */
        . += STACK_SIZE;
        _stack_end = .;
    } > RAM

    /* definir le contenu de la RAM */
    .data ALIGN(4) : {
        _data_start = .;
        *(.data .data.*)    /* initialized data */
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
