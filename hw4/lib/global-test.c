
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "errors.h"


int
main()
{
    int size, flag;
    GlobalScope *global;
    Scope *scope;

    global = global_scope_create();
    assert(global != NULL);
    assert(global->size == 0);
    assert(global->cap == INIT_GLOBAL_SCOPE_CAP);

    global_scope_create_class_scope(global, "test");
    assert(global->size == 1);
    assert(global->classes[0]->name == "test");
    assert(global->classes[0]->typetoken == 128);
    assert(strcmp(global_type_name(global, 128), "test") == 0);

    scope = global_class_lookup(global, "test");
    assert(scope != NULL);
    assert(scope->name == "test");
    assert(scope->typetoken == 128);
    assert(global->classes[0] == scope);

    global_scope_create_class_scope(global, "test2");
    assert(global->size == 2);
    assert(strcmp(global->classes[1]->name, "test2") == 0);
    assert(global->classes[1]->typetoken == 129);
    assert(strcmp(global_type_name(global, 129), "test2") == 0);

    flag = global_create_type(global, 156, "newtype");
    assert(flag == 0);
    assert(strcmp(global_type_name(global, 156), "newtype") == 0);
    flag = global_create_type(global, 156, "clobber");
    assert(flag == CLOBBERING_TYPE);
    assert(strcmp(global_type_name(global, 156), "newtype") == 0);

    size = global->size;
    global->size = global->cap;
    global_scope_double_cap_if_full(global);
    assert(global->cap == INIT_GLOBAL_SCOPE_CAP * 2);
    global->size = size;

    global_scope_destroy(global);
    return 0;
}
