
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "core.h"
#include "errors.h"

#define INT 10
#define BOOL 11
#define STRING 12
#define INT_ARR 13


int main()
{
    int flag;
    ScopeStack *stack;
    Symbol *sym;
    Scope *tmp_scope, *class;

    // Test enter/exit scope for all scope types
    // ====================================================
    stack = scope_stack_create();
    assert(in_global_scope(stack));
    enter_scope(stack, LET_SCOPE, "LET");
    assert(in_let_scope(stack));
    assert(number_of_classes(stack) == 0);
    enter_scope(stack, CLASS_SCOPE, "CLASS");
    assert(in_class_scope(stack));
    assert(number_of_classes(stack) == 1);
    assert(class_exists(stack, "CLASS"));

    exit_scope(stack);
    assert(class_exists(stack, "CLASS"));
    assert(in_let_scope(stack));
    assert(number_of_classes(stack) == 1);
    exit_scope(stack);

    assert(in_global_scope(stack));
    enter_scope(stack, LET_SCOPE, "LET");
    assert(in_let_scope(stack));
    enter_scope(stack, CLASS_SCOPE, "CLASS");
    assert(in_class_scope(stack));
    enter_scope(stack, METHOD_SCOPE, "METHOD");
    assert(in_method_scope(stack));
    exit_scope(stack);
    assert(in_class_scope(stack));
    exit_scope(stack);
    assert(in_let_scope(stack));
    exit_scope(stack);
    assert(in_global_scope(stack));

    scope_stack_destroy(stack);

    // Test declaration & existence functions
    // ====================================================
    stack = scope_stack_create(stack);

    flag = method_exists_for_class(stack, "say_hello", "Person");
    assert(flag == NO_SUCH_CLASS);
    assert(!attribute_exists(stack, "hello"));

    flag = begin_class_declaration(stack, "Person");
    assert(flag == 0);
    assert(in_class_scope(stack));
    assert(number_of_classes(stack) == 1);
    flag = begin_class_declaration(stack, "Employee");
    assert(flag == CLASS_DECL_INSIDE_CLASS_DECL);
    assert(number_of_classes(stack) == 1);

    assert(!attribute_exists(stack, "name"));
    assert(!attribute_exists_locally(stack, "name"));
    flag = declare_attribute(stack, "name", STRING);
    assert(flag == 0);
    assert(attribute_exists(stack, "name"));
    assert(attribute_exists_locally(stack, "name"));
    assert(attribute_exists_for_class(stack, "name", "Person"));
    flag = declare_attribute(stack, "name", STRING);
    assert(flag == DUPLICATE_ATTRIBUTE);

    flag = begin_method_declaration(stack, "say_hello", STRING, 2);
    assert(flag == 0);
    flag = begin_method_declaration(stack, "say_hello", STRING, 2);
    assert(flag == METHOD_DECL_INSIDE_METHOD_DECL);
    end_method_declaration(stack);
    flag = begin_method_declaration(stack, "say_hello", STRING, 2);
    assert(flag == DUPLICATE_METHOD);

    end_class_declaration(stack);
    assert(!attribute_exists_locally(stack, "name"));
    assert(attribute_exists_for_class(stack, "name", "Person"));
    assert(class_exists(stack, "Person"));
    assert(method_exists_for_class(stack, "say_hello", "Person"));
    assert(!method_exists_for_class(stack, "no_method", "Person"));

    flag = begin_class_declaration(stack, "Person");
    assert(flag == DUPLICATE_CLASS);
    assert(in_global_scope(stack));
    flag = declare_attribute(stack, "buggy", INT);
    assert(flag == ATTRIBUTE_DECL_IN_GLOBAL_SCOPE);
    flag = begin_method_declaration(stack, "still_buggy", INT_ARR, 3);
    assert(flag == METHOD_DECL_OUTSIDE_CLASS_SCOPE);

    enter_let_scope(stack);
    assert(in_let_scope(stack));
    declare_attribute(stack, "i", STRING);

    // should be able to find "i", because it's in local scope
    sym = lookup_attribute(stack, "i");
    assert(sym->type == STRING);
    assert(strcmp(sym->name, "i") == 0);
    enter_let_scope(stack);

    // should be able to find "i", in scope above current
    assert(lookup_attribute(stack, "a") == NULL);
    sym = lookup_attribute(stack, "i");
    assert(sym->type == STRING);
    assert(strcmp(sym->name, "i") == 0);
    exit_scope(stack);

    assert(method_exists_for_class(stack, "say_hello", "Person"));
    assert(!method_exists_for_class(stack, "no_method", "Person"));
    scope_stack_destroy(stack);

    // printing tests
    // ====================================================
    stack = scope_stack_create();
    begin_class_declaration(stack, "Person");
    begin_method_declaration(stack, "say_hello", INT, 1);
    end_method_declaration(stack);
    declare_attribute(stack, "name", STRING);
    begin_method_declaration(stack, "say_goodbye", INT, 0);
    end_method_declaration(stack);
    end_class_declaration(stack);
    class = lookup_class(stack, "Person");
    print_class(stack->global, class);

    enter_let_scope(stack);
    declare_attribute(stack, "x", INT);
    declare_attribute(stack, "y", INT);
    declare_attribute(stack, "test", STRING);
    declare_attribute(stack, "nums", INT_ARR);
    print_scope_stack(stack);
    exit_scope(stack);

    scope_stack_destroy(stack);
    return 0;
}
