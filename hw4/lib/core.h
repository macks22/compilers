// core.h
//
// This module contains functions which abstract the underlying data structures
// behind a layer of language specific to handling the parsing of the UnCool
// language.

#ifndef _CORE_H
#define _CORE_H

#include "scope_stack.h"

#define INVALID_TYPE -32


int in_class_scope(ScopeStack *stack);
int in_method_scope(ScopeStack *stack);
int in_let_scope(ScopeStack *stack);
int in_global_scope(ScopeStack *stack);

void enter_let_scope(ScopeStack *stack);

char * current_class_name(ScopeStack *stack);
int class_exists(ScopeStack *stack, char *name);
int number_of_classes(ScopeStack *stack);
int method_exists(Scope *class, char *name);
int method_exists_for_class(ScopeStack *stack, char *method_name,
                            char *class_name);

int attribute_exists(ScopeStack *stack, char *name);
int attribute_exists_locally(ScopeStack *stack, char *name);
int attribute_exists_for_class(ScopeStack *stack, char *attr_name,
                               char *class_name);

int begin_class_declaration(ScopeStack *stack, char *name);
void end_class_declaration(ScopeStack *stack);

int begin_method_declaration(ScopeStack *stack, char *name, int type, int argcount);
void end_method_declaration(ScopeStack *stack);

int declare_method(ScopeStack *stack, char *name, int type, int argcount);
int declare_attribute(ScopeStack *stack, char *name, int type);
int attribute_type(ScopeStack *stack);

Scope * containing_class(ScopeStack *stack);
Scope * lookup_class(ScopeStack *stack, char *name);
Symbol * lookup_method(ScopeStack *stack, char *class_name, char *method_name);
Symbol * lookup_attribute(ScopeStack *stack, char *name);

void print_let_scope(GlobalScope *global, Scope *scope);
void print_scope_stack(ScopeStack *stack);
void print_type_map(ScopeStack *stack);

#endif /* _CORE_H */
