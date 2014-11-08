
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "scope_stack.h"


int
main()
{
    int size;
    ScopeStack *stack;
    Scope *scope, *tmp_scope;
    Symbol *sym;

    stack = scope_stack_create();
    assert(stack != NULL);
    assert(stack->cap == INIT_SCOPE_STACK_CAP);
    assert(stack->size == 0);
    assert(stack->local == NULL);
    assert(stack->global != NULL);

    scope = scope_create(LET_SCOPE, "LET");
    scope_stack_push(stack, scope);
    assert(stack->size == 1);
    assert(stack->local == stack->scopes[0]);
    assert(stack->local == scope);

    tmp_scope = scope_stack_pop(stack);
    assert(tmp_scope == scope);
    assert(stack->size == 0);
    assert(stack->local == NULL);
    scope_destroy(tmp_scope);

    enter_scope(stack, LET_SCOPE, "LET");
    assert(stack->size == 1);
    assert(stack->local == stack->scopes[0]);

    exit_scope(stack);
    assert(stack->size == 0);
    assert(stack->local == NULL);

    enter_scope(stack, CLASS_SCOPE, "TEST");
    assert(stack->size == 1);
    assert(stack->local == stack->scopes[0]);

    exit_scope(stack);
    assert(stack->size == 0);
    assert(stack->global->size == 1);

    size = stack->size;
    stack->size = stack->cap;
    scope_stack_double_cap_if_full(stack);
    assert(stack->cap == INIT_SCOPE_STACK_CAP * 2);
    stack->size = size;

    scope_stack_destroy(stack);
    return 0;
}
