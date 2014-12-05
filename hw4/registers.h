// registers.h
//

#ifndef _REG_H
#define _REG_H

// Allocate codes to each register available; these will be used to
// index into the members of the RegisterTracker.
#define EAX 0
#define EDX 1
#define ECX 2
#define EBX 3
#define ESI 4
#define EDI 5

#define NUM_REGISTERS 6
extern const char *REG_NAMES[NUM_REGISTERS];


// The RegisterTracker will track which registers are avilable and
// provide functions for getting and freeing registers.
typedef struct {
    int in_use[NUM_REGISTERS];
    int used;
} RegisterTracker;

/**
 * Initialize the register tracker.
 */
RegisterTracker * rt_create();

/**
 * Free register tracker memory.
 */
void * rt_destroy(RegisterTracker *rt);

/**
 * Return the name of the next available register.
 * If none are available, return a void pointer.
 * If this happens, it means one of two things. Either
 * (1) register allocation is being done poorly, or
 * (2) registers are not being freed as often as they should be.
 */
char * get_register(RegisterTracker *rt);

/**
 * Free the given register. This simply marks the register as free.
 * The actual contents of the register will be overwritten when the
 * register is used again.
 */
void * free_register(RegisterTracker *rt, char *reg);

/**
 * Returns the number of registers currently being used.
 * This will be a value between 0 and `NUM_REGISTERS`.
 */
int num_registers_in_use(RegisterTracker *rt);


#endif /* _REG_H */
