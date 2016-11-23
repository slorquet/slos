#include "config.h"

#include <stdint.h>

#define NR_INTERRUPTS 0 /* number of int vectors, not important yet*/

void _startup(void); /*system entry point*/
void _except(void); /*exception entry point, in other file*/
void main(void); /*user entry point*/

/*symbols defined in linker script*/
extern uint32_t _stack_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _data_init_start;
extern uint32_t _data_start;
extern uint32_t _data_end;

uint32_t _vectors[] __attribute__((section(".armvectors"))) = {
    (uint32_t)&_stack_end, /*initial value for SP, defined in linkerscript*/
    (uint32_t)&arch_start, /*initial PC*/
    [2 ... 15 + NR_INTERRUPTS ] = (uint32_t)_except /* the easy gcc way */
};

/*fist code executed by the CPU!*/
void __attribute__((noreturn)) arch_start(void)
{
    uint32_t *addr;
    uint32_t *src;

    /* clear bss segment */
    for(addr = &_bss_start; addr < &_bss_end; addr++) {
        *addr = 0;
    }

    /* copy initialized data */
    src = &_data_init_start;
    for(addr = &_data_start; addr < &_data_end; addr++) {
        *addr = *src++;
    }

    /* call user code */
    chip_start();
}
