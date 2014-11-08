// lib.h
//
// This module contains functions which abstract the underlying data structures
// behind a layer of language specific to handling the parsing of the UnCool
// language.

#include "scope_stack.h"


Scope * lookup_class(ScopeStack *stack, char *name);

Symbol * lookup_method(ScopeStack *stack, char *class_name, char *method_name);

Symbol * lookup_attribute(ScopeStack *stack, char *name);

int declare_method(ScopeStack *stack, char *name, int type);

int declare_attribute(ScopeStack *stack, char *name, int type);
