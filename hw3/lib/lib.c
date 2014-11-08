// lib.c
//

#include <stdlib.h>
#include <assert.h>
#include "errors.h"
#include "lib.h"


int
in_class_scope(stack)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    if (stack->local->type == CLASS_SCOPE) {
        return 1;
    }
    return 0;
}

int
in_let_scope(stack)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    if (stack->local->type == LET_SCOPE) {
        return 1;
    }
    return 0;
}

int
in_global_scope(stack)
{   /* 1 if true, else 0.
     * In the global scope only if the scope stack is empty.
     * The stack->local pointer is NULL in this case.
     */
    assert(stack != NULL);  // sanity check
    if (stack->local == NULL) {
        return 1;
    }
    return 0;
}

int
class_exists(stack, name)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    return (lookup_class(stack, name) == NULL) ? 0 : 1;
}

int
method_exists(class, name)
{   /* 1 if true, else 0. */
    assert(class != NULL);  // sanity check
    return (scope_lookup_symbol(class, name, METHOD) == NULL) ? 0 : 1;
}

int
attribute_exists(stack, name)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    return (lookup_attribute(stack, name) == NULL) ? 0 : 1;
}

int
attribute_exists_locally(stack, name)
{   /* 1 if true, else 0.
     * Only the local scope is searched.
     */
    if (in_global_scope) {
        return 0;  // no attributes in global scope
    }
    else if (scope_lookup_symbol(stack->local, name) == NULL) {
        return 0;  // not in local scope
    }
    else {
        return 1;  // attribute exists in local scope
    }
}

int
declare_class(ScopeStack *stack, char *name)
{   /* Declare a new class (enter new class scope).
     */
    assert(stack != NULL);  // sanity check

    // first we need to ensure no class exists with this name
    if (lookup_class(stack, name) != NULL) {
        return DUPLICATE_CLASS;
    }

    // at this point, we can simply enter the new class scope
    // the scope will be added to the global scope by the exit_scope
    // function of the scope_stack
    enter_scope(stack, name, CLASS_SCOPE);
    return 0;
}

int
declare_method(ScopeStack *stack, char *name, int type)
{   /* Declare a new method in the current scope.
     * If the current scope is not a class scope, return 0.
     * Otherwsie return 1.
     */
    assert(stack != NULL);  // sanity check
    if (!in_class_scope(stack)) {
        return METHOD_DECL_OUTSIDE_CLASS_SCOPE;
    }

    // at this point, we know we're in a class scope
    // however, we must still ensure the method doesn't already exist
    if (method_exists(stack->local, name)) {
        return DUPLICATE_METHOD;
    }

    // Houston, we have lift off
    scope_add_symbol(stack->local, name, type, METHOD);
}

int
declare_attribute(ScopeStack *stack, char *name, int type)
{   /* Declare a new attribute in the current scope.
     * Check for global scope; invalid declaration.
     * If in a let scope, existing symbols can be ovewritten.
     * Otherwise, we're in a class scope and duplicates are errors.
     * Returns 0 if all goes well, otherwise
     */
    assert(stack != NULL);  // sanity check
    Symbol *attribute;
    int flag;

    // first check for global scope
    if (in_global_scope) {
        return ATTRIBUTE_DECL_IN_GLOBAL_SCOPE
    }

    // next handle class and let scopes
    if (attribute_exists_locally(stack, name)) {
        // if in class scope, this is an error
        if (in_class_scope) {
            return DUPLICATE_ATTRIBUTE;
        }
        // otherwise, we're in a let scope, so overwrite
        flag = scope_overwrite_symbol(stack->local, name, type, ATTRIBUTE);
        if (flag) {  // overwrite failed, no idea why...
            printf("Overwrite failed for symbol: %s\n", name);
            exit(flag);
        } else {
            return 0;  // successful overwrite
        }
    }

    // if it doesn't exist, and we're not in global, simply create it
    scope_add_symbol(stack->local, name, type, ATTRIBUTE);
    return 0;
}

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

