// scope.h
//

#include "symtable.h"

// there are 2 different kinds of scopes:
// 1.  METHOD: can only contain attributes
// 2.  CLASS: can contain methods and attributes
// 3.  LET: can only contain attributes

typedef enum {CLASS_SCOPE, LET_SCOPE, METHOD_SCOPE} scope_type;

typedef struct {
    char *name;          // used to hold class names or GLOBAL/LET
    scope_type type;     // identify what type of scope this is
    Symtable *symtable;  // the holding cell for symbols
    int typetoken;       // used for classes
} Scope;

#define is_class_scope(scope) (scope->type == CLASS_SCOPE)
#define is_let_scope(scope) (scope->type == LET_SCOPE)
#define is_method_scope(scope) (scope->type == METHOD_SCOPE)

Scope * scope_create(scope_type type, char *name);

void scope_destroy(Scope *scope);

void scope_add_symbol(Scope *scope, char *name, int type,
                      declaration_type decl_type);

void scope_add_method(Scope *scope, char *name, int type, int argcount);

void scope_add_attribute(Scope *scope, char *name, int type);

int scope_overwrite_symbol(Scope *scope, char *name, int type,
                           declaration_type decl_type);

int scope_overwrite_attribute(Scope *scope, char *name, int type);

Symbol * scope_lookup_symbol(Scope *scope, char *name,
                             declaration_type decl_type);

Symbol * scope_lookup_attribute(Scope *scope, char *name);

Symbol * scope_lookup_method(Scope *scope, char *name);
