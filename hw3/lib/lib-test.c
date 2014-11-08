
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lib.h"


int main()
{
    ScopeStack *stack;
    Scope *tmp_scope;

    stack = scope_stack_create();

    tmp_scope = lookup_class(stack, "TEST");
    assert(tmp_scope != NULL);
    assert(tmp_scope->name == "TEST");
    free(tmp_scope);

    scope_stack_destroy(stack);
    return 0;
}
