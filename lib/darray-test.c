// darray-usage.c

#include <stdio.h>
#include "darray.h"

int main() {
    int i;

    // declare and initialize a new darray
    Darray darray;
    darray_init(&darray);

    // fill it up with 150 arbitrary values
    // this should expand capacity up to 200
    for (i=0; i <= 127; i++) {
        darray_append(&darray, (char)i);
    }

    // print out all values in the darray
    darray_print(&darray);

    // set a value at an arbitrary index
    // this will expand and zero-fill the darray to fit
    darray_set(&darray, 200, 'a');

    // we're all done playing with our darray, 
    // so free its underlying data array
    darray_free(&darray);
}
