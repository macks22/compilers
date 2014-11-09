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
scope_add_method(Scope *scope, char *name, int type, int argcount)
{   /* Add a new method to the scope.
     */
    assert(scope != NULL);  // sanity check
    symtable_add_method(scope->symtable, name, type, argcount);
}

void
scope_add_attribute(Scope *scope, char *name, int type)
{   /* Add a new attribute to the scope.
     */
    assert(scope != NULL);  // sanity check
    symtable_add_attribute(scope->symtable, name, type);
}

int
scope_overwrite_symbol(Scope *scope, char *name, int type,
                       declaration_type decl_type)
{   /* Look up the symbol by name and declaration type.
     * If not found, return 0.
     * Otherwise, replace the type of the existing symbol with the new type.
     * Return 1 if successful.
     */
    assert(scope != NULL);  // sanity check
    return symtable_overwrite_symbol(scope->symtable, name, type, decl_type);
}

int
scope_overwrite_attribute(Scope *scope, char *name, int type)
{   /* Look up attribute by name.
     * If not found, return 0.
     * Otherwise, replace the type of the existing attribute and return 1.
     */
    return scope_overwrite_symbol(scope, name, type, ATTRIBUTE);
}

Symbol *
scope_lookup_symbol(Scope *scope, char *name, declaration_type decl_type)
{   /* Look up a symbol in the scope.
     */
    assert(scope != NULL);  // sanity check
    return symtable_lookup(scope->symtable, name, decl_type);
}

Symbol *
scope_lookup_attribute(Scope *scope, char *name)
{   /* Return the symbol or NULL if not found.
     */
    return scope_lookup_symbol(scope, name, ATTRIBUTE);
}

Symbol *
scope_lookup_method(Scope *scope, char *name)
{   /* Return the symbol or NULL if not found.
     */
    return scope_lookup_symbol(scope, name, METHOD);
}
