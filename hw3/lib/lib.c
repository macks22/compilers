// lib.c
//

#include <stdlib.h>
#include <assert.h>
#include "lib.h"


Scope *
lookup_class(ScopeStack *stack, char *name)
{   /* Search for a declared class scope in the global scope.
     * Note: this assumes a class is not used in it's own declaration body.
     */
    assert(stack != NULL);  // sanity check
    return global_class_lookup(stack->global, name);
}

Symbol *
lookup_method(ScopeStack *stack, char *class_name, char *method_name)
{   /* Look up a method in the scope stack.
     */
    assert(stack != NULL);  // sanity check

    // first try to find the class the method belongs to
    Scope *class = global_class_lookup(stack->global, class_name);
    if (class == NULL) {
        return NULL;
    }

    // now search for the method in the class scope
    return scope_lookup_symbol(class, method_name, METHOD);
}

Symbol *
lookup_attribute(ScopeStack *stack, char *name)
{   /* Look up an identifier in the scope stack.
     * The symbol for the identifier is returned if found.
     * Otherwise, NULL is returned.
     * This should not be used to lookup class declarations.
     */
    assert(stack != NULL);  // sanity check
    Symbol *sym;

    // inspect local and outlying scopes
    int i;
    for (i = stack->size-1; i >= 0; i++) {
        sym = scope_lookup_symbol(stack->scopes[i], name, ATTRIBUTE);
        if (sym != NULL) {
            return sym;
        }
    }
    return NULL;  // identifier not found
}

int
declare_method(ScopeStack *stack, char *name, int type)
{   /* Declare a new method in the current scope.
     * If the current scope is not a class scope, return 0.
     * Otherwsie return 1.
     */
    assert(stack != NULL);  // sanity check
    if (stack->local->type != CLASS_SCOPE) {
        return 0;
    }
    scope_add_symbol(stack->local, name, type, METHOD);
}

int
declare_attribute(ScopeStack *stack, char *name, int type)
{   /* Declare a new attribute in the current scope.
     */
    assert(stack != NULL);  // sanity check
}
