// scope_stack.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "scope_stack.h"


ScopeStack *
scope_stack_create()
{   /* Create a new scope stack and return a pointer to it.
     * This involves creating a global scope and placing it at the bottom
     * of the stack.
     */
    ScopeStack *stack = calloc(1, sizeof(ScopeStack));
    if (stack == NULL) {
        return NULL;
    }

    stack->scopes = calloc(INIT_SCOPE_STACK_CAP, sizeof(Scope));
    if (stack->scopes == NULL) {
        return NULL;
    }
    stack->cap = INIT_SCOPE_STACK_CAP;
    stack->size = 0;

    // global will never change (not actually on stack)
    stack->global = global_scope_create();
    stack->local = NULL;   // initially the global scope is also local
    return stack;
}

void
scope_stack_destroy(ScopeStack *stack)
{   /* Free up all memory associated with scope stack.
     */
    assert(stack != NULL);  // sanity check

    // free up all scopes in stack
    int i;
    for (i = 0; i < stack->size; i++) {
        scope_destroy(stack->scopes[i]);
    }
    free(stack->scopes);
    global_scope_destroy(stack->global);
    free(stack);
}

void
scope_stack_push(ScopeStack *stack, Scope *scope)
{   /* Push a scope onto the top of the stack.
     */
    assert(stack != NULL);  // sanity check
    scope_stack_double_cap_if_full(stack);

    // double capacity if full
    stack->scopes[stack->size++] = scope;
    stack->local = scope;
}

void
scope_stack_double_cap_if_full(ScopeStack *stack)
{   /* If size equals capacity, next push will overflow, so double cap.
     * Otherwise do nothing.
     */
    if (stack->size == stack->cap) {
        stack->cap *= 2;
        stack->scopes = realloc(stack->scopes, stack->cap);
    }
}

Scope *
scope_stack_pop(ScopeStack *stack)
{   /* Pop the top scope from the stack and return a pointer to it.
     * Returns NULL if there is nothing to pop from the stack.
     */
    assert(stack != NULL);  // sanity check
    if (stack->size == 0) {  // nothing to pop
        return NULL;
    }

    stack->size--;
    Scope *top = stack->scopes[stack->size];

    if (stack->size == 0) {  // we've removed the last scope
        stack->local = NULL;
    }
    else {  // still at least one left, so update local scope
        stack->local = stack->scopes[stack->size - 1];
    }

    return top;
}

void
enter_scope(ScopeStack *stack, scope_type type, char *name)
{   /* Create a new scope of the given type and add it to the top
     * of the stack.
     */
    assert(stack != NULL);  // sanity check
    Scope *scope = scope_create(type, name);
    scope_stack_push(stack, scope);
}

void
exit_scope(ScopeStack *stack)
{   /* Pop the current scope off the stack. If it's a class scope,
     * also add it to the global scope.
     */
    assert(stack != NULL);  // sanity check
    Scope *scope = scope_stack_pop(stack);
    if (scope->type == CLASS_SCOPE) {  // add to global scope
        global_scope_add_class_scope(stack->global, scope);
    }
    else {  // free up memory -- we won't be coming back to this scope
        scope_destroy(scope);
    }
}
