// global.h
//

#include "scope.h"

// The global scope is basically a symbol table of symbol tables. No other
// scopes can contain class definitions, so we don't have that problem with any
// others. But the Global scope is unique and wonderful -- hence it requires
// it's very own fantastical data structure. This is not strictly necessary, but
// I'm trying to avoid generics here.

#define INIT_GLOBAL_SCOPE_CAP 100
#define INIT_TYPE_NUMBER 128
#define MAX_NUMBER_OF_TYPES 256

typedef struct {
    int size;         // total number of classes
    int cap;          // capacity
    int typetracker;  // used to assign ascending type tokens to new classes
    char *typetable[MAX_NUMBER_OF_TYPES];  // maps each type to a token
    Scope **classes;  // dynamic array of classes
} GlobalScope;

GlobalScope * global_scope_create();

void global_scope_destroy(GlobalScope *global);

int global_create_type(GlobalScope *global, int token, char *name);

char * global_type_name(GlobalScope *global, int token);

void global_scope_create_class_scope(GlobalScope *global, char *name);

void global_scope_add_class_scope(GlobalScope *global, Scope *class);

void global_scope_double_cap_if_full(GlobalScope *global);

Scope * global_class_lookup(GlobalScope *global, char *name);

void print_class(Scope *class);

void print_all_classes(GlobalScope *global);
