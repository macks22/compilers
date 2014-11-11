
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scope.h"


int
main()
{
    Scope *scope, *tmp_scope;
    Symbol *sym;

    scope = scope_create(CLASS_SCOPE, "Person");
    scope_add_attribute(scope, "test", 0);

    // negative test
    sym = scope_lookup_symbol(scope, "nothing here", ATTRIBUTE);
    assert(sym == NULL);

    sym = scope_lookup_attribute(scope, "nothing here");
    assert(sym == NULL);

    // positive test
    sym = scope_lookup_symbol(scope, "test", ATTRIBUTE);
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == ATTRIBUTE);

    sym = scope_lookup_attribute(scope, "test");
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == ATTRIBUTE);

    scope_destroy(scope);
    scope = scope_create(LET_SCOPE, "Person");

    // negative test
    sym = scope_lookup_method(scope, "hello");
    assert(sym == NULL);

    // positive test
    scope_add_method(scope, "hello", 0, 2);
    sym = scope_lookup_method(scope, "hello");
    assert(sym != NULL);
    assert(strcmp(sym->name, "hello") == 0);
    assert(sym->type == 0);
    assert(sym->argcount == 2);
    assert(sym->decl_type == METHOD);

    scope_destroy(scope);
    return 0;
}
