
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "scope.h"


int
main()
{
    Scope *scope, *tmp_scope;
    Symbol *sym;

    scope = scope_create(CLASS_SCOPE, "Person");
    scope_add_symbol(scope, "test", 0, CLASS);

    // negative test
    sym = scope_lookup_symbol(scope, "nothing here");
    assert(sym == NULL);

    // positive test
    sym = scope_lookup_symbol(scope, "test");
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == CLASS);

    scope_destroy(scope);
    free(sym);
    return 0;
}
