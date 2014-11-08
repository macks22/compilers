// lib.h
//
// This module contains functions which abstract the underlying data structures
// behind a layer of language specific to handling the parsing of the UnCool
// language.

#include "scope_stack.h"


int in_class_scope(ScopeStack *stack);

int in_let_scope(ScopeStack *stack);

int in_global_scope(ScopeStack *stack);

int class_exists(ScopeStack *stack, char *name);

int method_exists(Scope *class, char *name);

int attribute_exists(ScopeStack *stack, char *name);

int declare_class(ScopeStack *stack, char *name);

int declare_method(ScopeStack *stack, char *name, int type);

int declare_attribute(ScopeStack *stack, char *name, int type);

Scope * lookup_class(ScopeStack *stack, char *name);

Symbol * lookup_method(ScopeStack *stack, char *class_name, char *method_name);

Symbol * lookup_attribute(ScopeStack *stack, char *name);
