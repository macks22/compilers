// global.h
//

#include "scope.h"

// The global scope is basically a symbol table of symbol tables. No other
// scopes can contain class definitions, so we don't have that problem with any
// others. But the Global scope is unique and wonderful -- hence it requires
// it's very own fantastical data structure. This is not strictly necessary, but
// I'm trying to avoid generics here.

#define INIT_GLOBAL_SCOPE_CAP 100

typedef struct {
    int size;         // total number of classes
    int cap;          // capacity
    Scope **classes;  // dynamic array of classes
} GlobalScope;

GlobalScope * global_scope_create();

void global_scope_destroy(GlobalScope *global);

void global_scope_create_class_scope(GlobalScope *global, char *name);

void global_scope_add_class_scope(GlobalScope *global, Scope *class);

void global_scope_double_cap_if_full(GlobalScope *global);

Scope * global_class_lookup(GlobalScope *global, char *name);
