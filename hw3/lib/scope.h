// scope.h
//

#include "symtable.h"

// there are 3 different kinds of scopes:
// 1.  GLOBAL: only contains class scopes
// 2.  CLASS: can contain methods and attributes
// 3.  LET: can only contain attributes

typedef enum {CLASS_SCOPE, GLOBAL_SCOPE, LET_SCOPE} scope_type;

typedef struct {
    char *name;          // used to hold class names or GLOBAL/LET
    scope_type type;     // identify what type of scope this is
    Symtable *symtable;  // the holding cell for symbols
} Scope;

Scope * scope_create(scope_type type, char *name);

void scope_destroy(Scope *scope);

void scope_add_symbol(Scope *scope, char *name, int data_type,
                      declaration_type decl_type);

Symbol * scope_lookup_symbol(Scope *scope, char *name);
