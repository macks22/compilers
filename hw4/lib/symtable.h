// symtable.h
//

#ifndef _SYMTABLE_H
#define _SYMTABLE_H

// A symbol is simply some identifier used in UnCool, with the associated type
// information and perhaps the token as well, just for good measure. Other stuff
// can be added as it comes along. We assume each type has an integer identifier
// which will be used throughout the program.

// note that a class is actually defined as a scope, so it is not a valid
// declaration as far as symbols are concerned. They are however a valid
// declaration in the UnCool spec.
typedef enum {METHOD, ATTRIBUTE} declaration_type;

// assembly label char size.
#define LABEL_SIZE 128
#define NO_OFFSET -7

typedef struct {
    char *name;                 // the symbol identifier
    int type;                   // the data type of the symbol
    declaration_type decl_type; // which type of declaration it is
    int argcount;               // need this for methods
    char *label;                // assembly label for globals
    int offset;                 // offset for local variables
} Symbol;

#define is_method(sym) (sym->decl_type == METHOD)
#define is_attribute(sym) (sym->decl_type == ATTRIBUTE)
#define is_global(sym) (sym->offset == NO_OFFSET)

Symbol *symbol_create_attribute(char *name, int type);
Symbol *symbol_create_method(char *name, int type, int argcount);

void symbol_destroy(Symbol* symbol);

// Each scope has an underlying symbol table which actually holds the symbols
// stored in a particular scope. The symbol table simply needs to have
// functionality for adding symbols and their metadata and looking those symbols
// up later. Given the spec of UnCool, it doesn't seem like we even need a
// delete. In terms of how to do this... let's be stupid simple and make an
// arraylist (dynamic array of symbol structs.
//
// Therefore all we really need is dynamic array-like stuff, such as append and
// get, and a lookup function which actually does the finding.

#define SYMTABLE_INIT_CAP 100

typedef struct {
    int size;        // the number of symbols stored currently
    int cap;         // the capacity in terms of allocated symbol slots
    Symbol **symbols; // actual symbol data.
} Symtable;

Symtable *symtable_create();
void symtable_destroy(Symtable *symtable);

void symtable_add_method(Symtable *symtable, char *name, int type, int argcount);
void symtable_add_attribute(Symtable *symtable, char *name, int type);
void symtable_add_symbol(Symtable *symtable, Symbol *symbol);

void symtable_double_cap_if_full(Symtable *symtable);

Symbol *symtable_lookup_attribute(Symtable *symtable, char *name);
Symbol *symtable_lookup_method(Symtable *symtable, char *name);
Symbol *symtable_lookup(Symtable *symtable, char *name,
                        declaration_type decl_type);

int symtable_overwrite_symbol(Symtable *symtable, char *name, int type,
                              declaration_type decl_type);

void print_symtable(Symtable *symtable);

#endif /* _SYMTABLE_H */
