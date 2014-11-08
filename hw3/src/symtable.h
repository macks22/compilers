// symtabl.h
//

// A symbol is simply some identifier used in UnCool, with the associated type
// information and perhaps the token as well, just for good measure. Other stuff
// can be added as it comes along. We assume each type has an integer identifier
// which will be used throughout the program.

typedef enum {CLASS, METHOD, ATTRIBUTE} declaration_type;

typedef struct {
    char *name;                 // the symbol identifier
    int type;                   // the data type of the symbol
    declaration_type decl_type; // which type of declaration it is
} Symbol;

Symbol *symbol_create(char *name, int token, declaration_type type);

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

void symtable_add_symbol(Symtable *symtable, char *name, int type,
                         declaration_type decl_type);

void symtable_double_cap_if_full(Symtable *symtable);

Symbol *symtable_lookup(Symtable *symtable, char *name);
