
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symtable.h"


int
main()
{
    int flag, size;
    Symtable *symtable;
    Symbol *sym;

    sym = symbol_create_method("test", 0, 3);
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == METHOD);
    assert(sym->argcount == 3);
    symbol_destroy(sym);

    sym = symbol_create_attribute("test", 0);
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->decl_type == ATTRIBUTE);
    symbol_destroy(sym);

    symtable = symtable_create();
    assert(symtable->size == 0);
    assert(symtable->cap == SYMTABLE_INIT_CAP);

    size = symtable->size;
    symtable->size = symtable->cap;
    symtable_double_cap_if_full(symtable);
    assert(symtable->cap == SYMTABLE_INIT_CAP * 2);
    symtable->size = size;
    symtable_destroy(symtable);

    symtable = symtable_create();
    symtable_add_method(symtable, "test", 0, 3);
    assert(symtable->size == 1);

    // negative test
    assert(symtable_lookup(symtable, "nothing here", METHOD) == NULL);
    assert(symtable_lookup_method(symtable, "nothing here") == NULL);

    // positive test
    sym = symtable_lookup(symtable, "test", METHOD);
    assert(sym != NULL);  // returns NULL if not found
    assert(sym->name == "test");
    assert(sym->type == 0);
    assert(sym->argcount == 3);
    assert(sym->decl_type == METHOD);

    sym = symtable_lookup_method(symtable, "test");
    assert(sym != NULL);  // returns NULL if not found
    assert(strcmp(sym->name, "test") == 0);
    assert(sym->type == 0);
    assert(sym->argcount == 3);
    assert(sym->decl_type == METHOD);

    symtable_add_attribute(symtable, "term", 2);
    assert(symtable->size == 2);
    sym = symtable_lookup_attribute(symtable, "term");
    assert(sym != NULL);
    assert(strcmp(sym->name, "term") == 0);
    assert(sym->type == 2);
    assert(sym->decl_type == ATTRIBUTE);

    // negative test, should return 1
    flag = symtable_overwrite_symbol(symtable, "nothing here", 15, ATTRIBUTE);
    assert(flag == 1);

    // positive test, should return 0 and overwrite the type
    // note that previous type was 0
    flag = symtable_overwrite_symbol(symtable, "term", 15, ATTRIBUTE);
    assert(flag == 0);
    sym = symtable_lookup_attribute(symtable, "term");
    assert(sym->name == "term");
    assert(sym->type == 15);

    symtable_destroy(symtable);
    return 0;
}
