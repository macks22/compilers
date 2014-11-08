// symtable.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"


Symbol *
symbol_create(char *name, int type, declaration_type decl_type)
{   /* Create a new symbol struct and return a pointer to it.
     */
    Symbol *symbol = calloc(1, sizeof(Symbol));

    // set attributes
    symbol->name = name;
    symbol->type = type;
    symbol->decl_type = decl_type;
    return symbol;
}

void
symbol_destroy(Symbol* symbol)
{   /* Free up all memory for the symbol.
     */
    free(symbol);
}

Symtable *
symtable_create()
{   /* Create a new symbol table and return a pointer to it.
     */
    Symtable *symtable = calloc(1, sizeof(Symtable));
    if (symtable == NULL) {
        return NULL;
    }

    symtable->symbols = calloc(SYMTABLE_INIT_CAP, sizeof(Symbol));
    if (symtable->symbols == NULL) {
        return NULL;
    }

    symtable->cap = SYMTABLE_INIT_CAP;
    symtable->size = 0;
    return symtable;
}

void symtable_destroy(Symtable *symtable)
{   /* Free up all memory associated with the symbol table.
     */
    assert(symtable != NULL);  // sanity check
    free(symtable->symbols);
    free(symtable);
}

void
symtable_add_symbol(Symtable *symtable, char *name, int type,
                    declaration_type decl_type)
{   /* Add a new symbol to the symbol table.
     */
    assert(symtable != NULL);  // sanity check
    symtable_double_cap_if_full(symtable);

    Symbol *symbol = symbol_create(name, type, decl_type);
    symtable->symbols[symtable->size++] = symbol;
}

int
symtable_overwrite_symbol(Symtable *symtable, char *name, int type,
                          declaration_type decl_type)
{   /* Overwrite an existing symbol.
     * If the symbol is found, it's type will be replaced.
     * This is considered an ovewrite, and a 0 will be returned.
     * If the symbol is not found, no action is taken and a 1 is returned.
     */
    assert(symtable != NULL);  // sanity check

    int i;
    Symbol *sym;

    for (i = 0; i < symtable->size; i++) {
        sym = symtable->symbols[i];
        if (strcmp(sym->name, name) == 0 && sym->decl_type == decl_type) {
            symtable->symbols[i]->type = type;
            return 0;
        }
    }
    return 1;
}

void
symtable_double_cap_if_full(Symtable *symtable)
{   /* Check if cap is reached; if so, double # allocations and update cap.
     */
    if (symtable->size == symtable->cap) {
        symtable->cap *= 2;
        symtable->symbols = realloc(symtable->symbols, symtable->cap);
    }
}

Symbol *
symtable_lookup(Symtable *symtable, char *name, declaration_type decl_type)
{   /* Look up a symbol in the table.
     * Return NULL if it is not found.
     */
    assert(symtable != NULL);  // sanity check

    int i;
    Symbol *sym;

    for (i = 0; i < symtable->size; i++) {
        sym = symtable->symbols[i];
        if (strcmp(sym->name, name) == 0 && sym->decl_type == decl_type) {
            return sym;
        }
    }
    return NULL;
}
