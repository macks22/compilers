// darray.c

#include <stdio.h>
#include <stdlib.h>
#include "darray.h"


void darray_init(Darray *darray) {
    // first allocate space for struct
    // darray = (Darray *)malloc(sizeof(Darray));

    // initialize size and capacity
    darray->size = 0;
    darray->capacity = DARRAY_INITIAL_CAPACITY;

    // allocate memory for darray data
    darray->data = malloc(sizeof(char) * darray->capacity);
}

void darray_append(Darray *darray, char value) {
    // ensure adequate room for expansion
    darray_double_capacity_if_full(darray);

    // append the value and increment darray size
    darray->data[darray->size++] = value;
}

char darray_get(Darray *darray, int index) {
    if (index >= darray->size || index < 0) {
        printf("Index %d out of bounds for darray of size %d\n",
            index, darray->size);
        exit(1);
    }
    return darray->data[index];
}

void darray_set(Darray *darray, int index, char value) {
    // zero fill darray up to the desired index
    while (index >= darray->size) {
        darray_append(darray, (char)0);
    }

    // set value at desired index
    darray->data[index] = value;
}

void darray_double_capacity_if_full(Darray *darray) {
    if (darray->size >= darray->capacity) {
        // double capacity counter and realloc appropriate memory amount
        darray->capacity *= 2;
        darray->data = realloc(darray->data, sizeof(int) * darray->capacity);
    }
}

void darray_print(Darray *darray) {
    /* Print contents of darray, one char at a time.
     * This does not require the darray be null-terminated.
     */
    int i;
    for (i=0; i < darray->size; i++) {
        printf("%c", darray_get(darray, i));
    }
}

void darray_free(Darray *darray) {
    free(darray->data);
}

void darray_reinit(Darray *darray) {
    /* Free the contents of the darray and initialize it again.
     */
    darray_free(darray);
    darray_init(darray);
}
