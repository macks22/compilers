// vector-usage.c

#include <stdio.h>
#include "vector.h"

int main() {
    int i;

    // declare and initialize a new vector
    Vector vector;
    vector_init(&vector);

    // fill it up with 150 arbitrary values
    // this should expand capacity up to 200
    for (i=0; i <= 127; i++) {
        vector_append(&vector, (char)i);
    }

    // print out all values in the vector
    vector_print(&vector);

    // set a value at an arbitrary index
    // this will expand and zero-fill the vector to fit
    vector_set(&vector, 200, 'a');

    // we're all done playing with our vector, 
    // so free its underlying data array
    vector_free(&vector);
}
