
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "core.h"


int main()
{
    ScopeStack *stack;
    Scope *tmp_scope;

    stack = scope_stack_create();

    // TEST ALL FUNCTIONS OF LIB.H

    scope_stack_destroy(stack);
    return 0;
}
