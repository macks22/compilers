// scope.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "scope.h"


Scope *
scope_create(scope_type type, char *name)
{   /* Create a new scope with the given type and return a pointer to it.
     */
    Scope *scope = calloc(1, sizeof(Scope));
    if (scope == NULL) {
        return NULL;
    }

    scope->symtable = symtable_create();
    if (scope->symtable == NULL) {
        return NULL;
    }

    scope->type = type;
    scope->name = name;
    return scope;
}

void
scope_destroy(Scope *scope)
{   /* Free up all memory associated with the scope.
     */
    assert(scope != NULL);  // sanity check
    symtable_destroy(scope->symtable);
    free(scope);
}

void
scope_add_symbol(Scope *scope, char *name, int type, declaration_type decl_type)
{   /* Add a symbol to the scope.
     */
    assert(scope != NULL);  // sanity check
    symtable_add_symbol(scope->symtable, name, type, decl_type);
}

Symbol *
scope_lookup_symbol(Scope *scope, char *name)
{   /* Look up a symbol in the scope.
     */
    assert(scope != NULL);  // sanity check
    return symtable_lookup(scope->symtable, name);
}