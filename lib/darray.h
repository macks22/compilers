// darray.h
//
// Dynamic array data structure.

#define DARRAY_INITIAL_CAPACITY 50

// Define a darray type
typedef struct {
    int size;       // slots used so far
    int capacity;   // total available slots
    char *data;     // array of integers we're storing
} Darray;

void darray_init(Darray *darray);

void darray_append(Darray *darray, char value);

char darray_get(Darray *darray, int index);

void darray_set(Darray *darray, int index, char value);

void darray_double_capacity_if_full(Darray *darray);

void darray_print(Darray *darray);

void darray_free(Darray *darray);

void darray_reinit(Darray *darray);
