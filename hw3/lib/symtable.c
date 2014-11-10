// symtable.c
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"


Symbol *
symbol_create_attribute(char *name, int type)
{   /* Create a new attribute symbol struct and return a pointer to it.
     */
    Symbol *symbol = calloc(1, sizeof(Symbol));
    if (symbol == NULL) {
        return NULL;
    }
    symbol->name = name;
    symbol->type = type;
    symbol->decl_type = ATTRIBUTE;
    symbol->argcount = 0;
    return symbol;
}

Symbol *
symbol_create_method(char *name, int type, int argcount)
{   /* Create a new method symbol struct and return a pointer to it.
     */
    Symbol *symbol = calloc(1, sizeof(Symbol));
    if (symbol == NULL) {
        return NULL;
    }
    symbol->name = name;
    symbol->type = type;
    symbol->argcount = argcount;
    symbol->decl_type = METHOD;
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
    int i;
    for (i = 0; i < symtable->size; i++) {
        symbol_destroy(symtable->symbols[i]);
    }
    free(symtable->symbols);
    free(symtable);
}

void
symtable_add_method(Symtable *symtable, char *name, int type, int argcount)
{   /* Create a new method symbol and add it to the symbol table.
     */
    assert(symtable != NULL);  // sanity check
    symtable_add_symbol(symtable, symbol_create_method(name, type, argcount));
}

void
symtable_add_attribute(Symtable *symtable, char *name, int type)
{   /* Create a new attribute symbol and add it to the symbol table.
     */
    assert(symtable != NULL);  // sanity check
    symtable_add_symbol(symtable, symbol_create_attribute(name, type));
}

void
symtable_add_symbol(Symtable *symtable, Symbol *symbol)
{   /* Add a new symbol to the symbol table.
     */
    symtable_double_cap_if_full(symtable);
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

Symbol *
symtable_lookup_attribute(Symtable *symtable, char *name)
{   /* Look up an attribute in the table.
     * Return NULL if not found.
     */
    return symtable_lookup(symtable, name, ATTRIBUTE);
}

Symbol *
symtable_lookup_method(Symtable *symtable, char *name)
{   /* Look up a method in the table.
     * Return NULL if not found.
     */
    return symtable_lookup(symtable, name, METHOD);
}

void
print_symtable(Symtable *symtable)
{   /* Print out the contents of the scope.
     */
    assert(symtable != NULL);  // sanity check
    int i;
    Symbol * sym;
    for (i = 0; i < symtable->size; i++) {
        sym = symtable->symbols[i];
        if (is_attribute(sym)) {
            printf("\t[attribute][%s]: %d\n", sym->name, sym->type);
        } else {  // method
            printf("\t[method][%s](%d): %d\n", sym->name, sym->argcount,
                   sym->type);
        }
    }
}

