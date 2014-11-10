// global.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "global.h"
#include "errors.h"


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
    global->typetracker = INIT_TYPE_NUMBER;
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

int
global_create_type(GlobalScope *global, int token, char *name)
{   /* Create a new mapping in the type table.
     */
    assert(global != NULL);  // sanity check
    char *check = global_type_name(global, token);
    if (check != NULL) {
        return CLOBBERING_TYPE;
    }
    global->typetable[token % MAX_NUMBER_OF_TYPES] = name;
    return 0;
}

char *
global_type_name(GlobalScope *global, int token)
{   /* Look up the name of the type by its token.
     * Returns NULL if the token is not found.
     */
    assert(global != NULL);  // sanity check
    return global->typetable[token % MAX_NUMBER_OF_TYPES];
}

void
global_scope_create_class_scope(GlobalScope *global, char *name)
{   /* Add a new class scope to the global scope.
     */
    assert(global != NULL);  // sanity check
    global_scope_double_cap_if_full(global);
    Scope *class = scope_create(CLASS_SCOPE, name);
    int new_token = global->typetracker++;
    class->typetoken = new_token;
    global_create_type(global, new_token, name);
    global->classes[global->size++] = class;
}

void
global_scope_add_class_scope(GlobalScope *global, Scope *class)
{   /* Add the class scope to the global scope's list of scopes.
     */
    assert(global != NULL);  // sanity check
    assert(class != NULL);   // sanity check
    global_scope_double_cap_if_full(global);
    int new_token = global->typetracker++;
    class->typetoken = new_token;
    global_create_type(global, new_token, class->name);
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

void
print_scope_contents(GlobalScope *global, Scope *scope)
{
    assert(scope != NULL);  // sanity check
    int i;
    Symbol *sym;
    for (i = 0; i < scope->symtable->size; i++) {
        sym = scope->symtable->symbols[i];
        if (is_attribute(sym)) {
            printf("\t[attribute][%s]: %s\n", sym->name,
                   global_type_name(global, sym->type));
        } else {  // method
            printf("\t[method][%s](%d): %s\n", sym->name, sym->argcount,
                   global_type_name(global, sym->type));
        }
    }
}

void
print_class(GlobalScope *global, Scope *class)
{   /* Print out the class name and its contents.
     */
    assert(class != NULL);  // sanity check
    printf("[CLASS SCOPE] %s:\n", global_type_name(global, class->typetoken));
    print_scope_contents(global, class);
}

void
print_all_classes(GlobalScope *global)
{
    assert(global != NULL);  // sanity check
    Scope *class;
    int i;
    for (i = 0; i < global->size; i++) {
        class = global->classes[i];
        print_class(global, class);
        printf("\n");
    }
}


void
global_print_type_map(GlobalScope *global)
{   /* Print out all types with their tokens.
     */
    assert(global != NULL);  // sanity check
    int i;
    for (i = 0; i < MAX_NUMBER_OF_TYPES; i++) {
        if (global->typetable[i] != NULL) {
            printf("%s: %d\n", global->typetable[i], i);
        }
    }
}
