
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"


int
main()
{
    int size;
    GlobalScope *global;
    Scope *scope;

    global = global_scope_create();
    assert(global != NULL);
    assert(global->size == 0);
    assert(global->cap == INIT_GLOBAL_SCOPE_CAP);

    global_scope_create_class_scope(global, "test");
    assert(global->size == 1);
    assert(global->classes[0]->name == "test");

    scope = global_class_lookup(global, "test");
    assert(scope != NULL);
    assert(scope->name == "test");
    assert(global->classes[0] == scope);

    size = global->size;
    global->size = global->cap;
    global_scope_double_cap_if_full(global);
    assert(global->cap == INIT_GLOBAL_SCOPE_CAP * 2);
    global->size = size;

    global_scope_destroy(global);
    return 0;
}
