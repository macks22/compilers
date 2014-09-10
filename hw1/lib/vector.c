// vector.c

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


void vector_init(Vector *vector) {
    // first allocate space for struct
    // vector = (Vector *)malloc(sizeof(Vector));

    // initialize size and capacity
    vector->size = 0;
    vector->capacity = VECTOR_INITIAL_CAPACITY;

    // allocate memory for vector data
    vector->data = malloc(sizeof(char) * vector->capacity);
}

void vector_append(Vector *vector, char value) {
    // ensure adequate room for expansion
    vector_double_capacity_if_full(vector);

    // append the value and increment vector size
    vector->data[vector->size++] = value;
}

char vector_get(Vector *vector, int index) {
    if (index >= vector->size || index < 0) {
        printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
        exit(1);
    }
    return vector->data[index];
}

void vector_set(Vector *vector, int index, char value) {
    // zero fill vector up to the desired index
    while (index >= vector->size) {
        vector_append(vector, (char)0);
    }

    // set value at desired index
    vector->data[index] = value;
}

void vector_double_capacity_if_full(Vector *vector) {
    if (vector->size >= vector->capacity) {
        // double capacity counter and realloc appropriate memory amount
        vector->capacity *= 2;
        vector->data = realloc(vector->data, sizeof(int) * vector->capacity);
    }
}

void vector_print(Vector *vector) {
    int i;
    for (i=0; i < vector->size; i++) {
        printf("%c", vector_get(vector, i));
    }
    printf("\n");
}

void vector_free(Vector *vector) {
    free(vector->data);
}
