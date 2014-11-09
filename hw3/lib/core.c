// lib.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "errors.h"
#include "core.h"


int
in_class_scope(ScopeStack *stack)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    if (in_global_scope(stack)) {
        return 0;
    }
    else if (stack->local->type == CLASS_SCOPE) {
        return 1;
    }
    return 0;
}

int
in_let_scope(ScopeStack *stack)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    if (in_global_scope(stack)) {
        return 0;
    }
    else if (stack->local->type == LET_SCOPE) {
        return 1;
    }
    return 0;
}

int
in_global_scope(ScopeStack *stack)
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

void
enter_let_scope(ScopeStack *stack)
{
    enter_scope(stack, LET_SCOPE, "LET");
}

int
class_exists(ScopeStack *stack, char *name)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    return (lookup_class(stack, name) == NULL) ? 0 : 1;
}

int
number_of_classes(ScopeStack *stack)
{   /* Returns the number of classes currently stored in the global scope.
     */
    assert(stack != NULL);  // sanity check
    return stack->global->size;
}

int
method_exists(Scope *class, char *name)
{   /* 1 if true, else 0. */
    assert(class != NULL);  // sanity check
    return (scope_lookup_symbol(class, name, METHOD) == NULL) ? 0 : 1;
}

int
method_exists_for_class(ScopeStack *stack, char *method_name, char *class_name)
{   /* First searches for class.
     * Returns NO_SUCH_CLASS flag if none is found.
     * Otherwise returns 1 if the method is found in the class scope,
     * and a 0 if not found.
     */
    assert(stack != NULL);  // sanity check
    int flag;
    Scope *class = lookup_class(stack, class_name);
    if (class == NULL) {
        return NO_SUCH_CLASS;
    }

    return method_exists(class, method_name);
}

int
attribute_exists(ScopeStack *stack, char *name)
{   /* 1 if true, else 0. */
    assert(stack != NULL);  // sanity check
    return (lookup_attribute(stack, name) == NULL) ? 0 : 1;
}

int
attribute_exists_locally(ScopeStack *stack, char *name)
{   /* 1 if true, else 0.
     * Only the local scope is searched.
     */
    if (in_global_scope(stack)) {
        return 0;  // no attributes in global scope
    }
    else if (scope_lookup_symbol(stack->local, name, ATTRIBUTE) == NULL) {
        return 0;  // not in local scope
    }
    else {
        return 1;  // attribute exists in local scope
    }
}

int
attribute_exists_for_class(ScopeStack *stack, char *attr_name, char *class_name)
{   /* First searches for class.
     * Returns NO_SUCH_CLASS flag if none is found.
     * Otherwise returns 1 if the attribute is found in the class scope,
     * and a 0 if not found.
     */
    assert(stack != NULL);  // sanity check
    int flag;
    Scope *class = lookup_class(stack, class_name);
    if (class == NULL) {
        return NO_SUCH_CLASS;
    }
    return (scope_lookup_symbol(class, attr_name, ATTRIBUTE) == NULL) ? 0 : 1;
}

int
begin_class_declaration(ScopeStack *stack, char *name)
{   /* Declare a new class (enter new class scope).
     */
    assert(stack != NULL);  // sanity check

    // first make sure we're not already in a class scope
    // since classes can't be declared inside other classes
    if (in_class_scope(stack)) {
        return CLASS_DECL_INSIDE_CLASS_DECL;
    }

    // first we need to ensure no class exists with this name
    if (class_exists(stack, name)) {
        return DUPLICATE_CLASS;
    }

    // at this point, we can simply enter the new class scope
    // the scope will be added to the global scope by enter_scope
    enter_scope(stack, CLASS_SCOPE, name);
    return 0;
}

void
end_class_declaration(ScopeStack *stack)
{   /* Simply exit the class scope.
     * This function has benefits over just calling exit_scope
     * because it sanity checks the operation in a variety of ways.
     */
    assert(stack != NULL);          // sanity check
    assert(in_class_scope(stack));  // sanity check
    char *class_name = stack->local->name;
    exit_scope(stack);
    assert(class_exists(stack, class_name));
}

int
declare_method(ScopeStack *stack, char *name, int type, int argcount)
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
    scope_add_method(stack->local, name, type, argcount);
    return 0;
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
    if (in_global_scope(stack)) {
        return ATTRIBUTE_DECL_IN_GLOBAL_SCOPE;
    }

    // next handle class and let scopes
    if (attribute_exists_locally(stack, name)) {
        // if in class scope, this is an error
        if (in_class_scope) {
            return DUPLICATE_ATTRIBUTE;
        }
        // otherwise, we're in a let scope, so overwrite
        flag = scope_overwrite_attribute(stack->local, name, type);
        if (flag) {  // overwrite failed, no idea why...
            printf("Overwrite failed for symbol: %s\n", name);
            exit(flag);
        } else {
            return 0;  // successful overwrite
        }
    }

    // if it doesn't exist, and we're not in global, simply create it
    scope_add_attribute(stack->local, name, type);
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

    if (in_global_scope(stack)) {
        return NULL;  // no attributes in global scope
    }

    // inspect local and outlying scopes
    int i;
    for (i = stack->size-1; i >= 0; i--) {
        sym = scope_lookup_symbol(stack->scopes[i], name, ATTRIBUTE);
        if (sym != NULL) {
            return sym;
        }
    }
    return NULL;  // identifier not found
}

