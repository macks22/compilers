// global.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "global.h"


GlobalScope *
global_scope_create()
{   /* Create a new global scope struct and return a pointer to it.
     */
    GlobalScope *global = calloc(1, sizeof(GlobalScope));
    if (global == NULL) {
        return NULL;
    }

    global->classes = calloc(1, INIT_GLOBAL_SCOPE_CAP);
    if (global->classes == NULL) {
        return NULL;
    }
    global->cap = INIT_GLOBAL_SCOPE_CAP;
    global->size = 0;
    return global;
}

void
global_scope_destroy(GlobalScope *global)
{   /* Free all memory associated with the global scope.
     */
    assert(global != NULL);  // sanity check
    int i;
    for (i = 0; i < global->size; i++) {
        scope_destroy(global->classes[i]);
    }
    free(global->classes);
    free(global);
}

void
global_scope_create_class_scope(GlobalScope *global, char *name)
{   /* Add a new class scope to the global scope.
     */
    assert(global != NULL);  // sanity check
    global_scope_double_cap_if_full(global);
    Scope *class = scope_create(CLASS_SCOPE, name);
    global->classes[global->size++] = class;
}

void
global_scope_add_class_scope(GlobalScope *global, Scope *class)
{   /* Add the class scope to the global scope's list of scopes.
     */
    assert(global != NULL);  // sanity check
    assert(class != NULL);   // sanity check
    global_scope_double_cap_if_full(global);
    global->classes[global->size++] = class;
}

void
global_scope_double_cap_if_full(GlobalScope *global)
{   /* Double capacity if size == cap.
     */
    assert(global != NULL);  // sanity check
    if (global->size == global->cap) {
        global->cap *= 2;
        global->classes = realloc(global->classes, global->cap);
    }
}

Scope *
global_class_lookup(GlobalScope *global, char *name)
{   /* Look up a class scope by name and return it if found.
     * Return NULL if not found.
     */
    assert(global != NULL);  // sanity check
    Scope *class;
    int i;
    for (i = 0; i < global->size; i++) {
        class = global->classes[i];
        if (strcmp(class->name, name) == 0) {
            return class;
        }
    }
    return NULL;
}
