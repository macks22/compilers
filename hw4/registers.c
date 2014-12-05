// registers.c
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "registers.h"

const char *REG_NAMES[NUM_REGISTERS] = {
    "%eax",
    "%edx",
    "%ecx",
    "%ebx",
    "%esi",
    "%edi"
};

/**
 * Initialize the register tracker.
 */
RegisterTracker *
rt_create()
{
    int i;
    RegisterTracker *rt = calloc(1, sizeof(RegisterTracker));
    assert(rt != NULL);
    for (i = 0; i < NUM_REGISTERS; i++) {
        rt->in_use[i] = 0;
    }
    rt->in_use[0] = 1;  // %eax is reserved
    rt->used = 1;
    return rt;
}

/**
 * Free register tracker memory.
 */
void *
rt_destroy(RegisterTracker *rt)
{
    free(rt);
}

/**
 * Return the name of the next available register.
 * If none are available, return a void pointer.
 * If this happens, it means one of two things. Either
 * (1) register allocation is being done poorly, or
 * (2) registers are not being freed as often as they should be.
 */
char *
get_register(RegisterTracker *rt)
{
    assert(rt != NULL);
    int i;
    for (i = 1; i < NUM_REGISTERS; i++) {
        if (!rt->in_use[i]) {
            rt->used++;
            return (char *)REG_NAMES[i];
        }
    }
}

/**
 * Free the given register. This simply marks the register as free.
 * The actual contents of the register will be overwritten when the
 * register is used again.
 */
void *
free_register(RegisterTracker *rt, char *reg)
{
    assert(rt != NULL);
    int i;
    for (i = 1; i < NUM_REGISTERS; i++) {
        if (strcmp(REG_NAMES[i], reg) == 0) {
            rt->in_use[i] = 0;
            rt->used--;
        }
    }
}

/**
 * Returns the number of registers currently being used.
 * This will be a value between 0 and `NUM_REGISTERS`.
 */
int
num_registers_in_use(RegisterTracker *rt)
{
    assert(rt != NULL);
    return rt->used;
}
