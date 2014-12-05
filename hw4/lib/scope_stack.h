// scope_stack.h
//

#include "global.h"


#define INIT_SCOPE_STACK_CAP 100

typedef struct {
    int size;             // number of scopes on stack
    int cap;              // currently allocated slots
    GlobalScope *global;  // bottom of scope stack (global scope)
    Scope *local;         // top of scope stack (local scope)
    Scope **scopes;       // stack of scopes making up hierarchy of scope
} ScopeStack;


ScopeStack * scope_stack_create();
void scope_stack_destroy(ScopeStack *stack);

void scope_stack_push(ScopeStack *stack, Scope *scope);
void scope_stack_double_cap_if_full(ScopeStack *stack);
Scope * scope_stack_pop(ScopeStack *stack);

void enter_scope(ScopeStack *stack, scope_type type, char *name);
void exit_scope(ScopeStack *stack);

char *type_name(ScopeStack *stack, int token);
int create_type(ScopeStack *stack, int token, char *name);
