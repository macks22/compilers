
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "symtable.h"


int
main()
{
    int flag;
    Symtable *symtable;
    Symbol *sym;

    sym = symbol_create("test", 0, METHOD);
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == METHOD);
    symbol_destroy(sym);

    symtable = symtable_create();
    assert(symtable->size == 0);
    assert(symtable->cap == SYMTABLE_INIT_CAP);
    symtable->size = symtable->cap;
    symtable_double_cap_if_full(symtable);
    assert(symtable->cap == SYMTABLE_INIT_CAP * 2);
    symtable_destroy(symtable);

    symtable = symtable_create();
    symtable_add_symbol(symtable, "test", 0, METHOD);
    assert(symtable->size == 1);

    // negative test
    assert(symtable_lookup(symtable, "nothing here", METHOD) == NULL);

    // positive test
    sym = symtable_lookup(symtable, "test", METHOD);
    assert(sym != NULL);  // returns NULL if not found
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == METHOD);

    // negative test, should return 0
    flag = symtable_overwrite_symbol(symtable, "nothing here", 15, METHOD);
    assert(flag == 1);

    // positive test, should return 0 and overwrite the type
    // note that previous type was 0
    flag = symtable_overwrite_symbol(symtable, "test", 15, METHOD);
    assert(flag == 0);
    sym = symtable_lookup(symtable, "test", METHOD);
    assert(sym->name == "test");
    assert(sym->type == 15);

    symbol_destroy(sym);
    symtable_destroy(symtable);
    return 0;
}
