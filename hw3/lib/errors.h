// errors.h
//
// This module contains error codes for all type and scope errors which arise
// when parsing UnCool code.

#define DUPLICATE_CLASS -1
#define DUPLICATE_ATTRIBUTE -2
#define DUPLICATE_METHOD -3
#define NO_MAIN_CLASS -4
#define NO_MAIN_METHOD -5
#define METHOD_DECL_OUTSIDE_CLASS_SCOPE -6
#define ATTRIBUTE_DECL_IN_GLOBAL_SCOPE -7
#define CLASS_DECL_INSIDE_CLASS_DECL -8
#define NO_SUCH_CLASS -9

#define NO_SUCH_ATTRIBUTE -10
#define NO_SUCH_METHOD -11
#define CONFLICTING_TYPE -12
