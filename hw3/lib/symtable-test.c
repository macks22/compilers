
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "symtable.h"


int
main()
{
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
    symtable_add_symbol(symtable, "test", 0, CLASS);
    assert(symtable->size == 1);

    // negative test
    assert(symtable_lookup(symtable, "nothing here") == NULL);

    // positive test
    sym = symtable_lookup(symtable, "test");
    assert(sym != NULL);  // returns NULL if not found
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == CLASS);

    symbol_destroy(sym);
    symtable_destroy(symtable);
    return 0;
}
