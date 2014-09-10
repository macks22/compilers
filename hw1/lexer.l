%{
#include "lib/vector.h"
char start;
Vector *left, *mid, *right;
%}

/* before the first non-terminal is parsed; used to find start state */
/* INITIAL */

/* CFG parsing has begun, on left side of production, before NT */
%s CFG
/* left side, just after NT parsed */
%s CFG_NT
/* just after production symbol parsed */
%s RIGHT
/* parsed terminal symbol on right side of production */
%s RIGHT_T
/* parsed non-terminal at end of production */
%s RIGHT_NT
/* finished parsing CFG input; DFA has been built and is being used */
%s DFA

term        [a-z]
nonterm     [A-Z]
prod        "-->"
ws          [ \t]+

%%

<INITIAL>{nonterm}          {printf("nonterm: %s (start)\n", yytext);
                             start = yytext[0];
                             vector_append(left, yytext[0]);
                             BEGIN CFG_NT; }

<CFG_NT>{prod}              {printf("prod: %s\n", yytext); BEGIN RIGHT; }

<RIGHT>{term}               {printf("term: %s\n", yytext);
                             vector_append(mid, yytext[0]);
                             BEGIN RIGHT_T; }
<RIGHT>[\n]                 {printf("NEWLINE\n");
                             vector_append(mid, '\0');
                             vector_append(right, '\0');
                             BEGIN CFG; }

<RIGHT_T>{nonterm}          {printf("nonterm: %s\n", yytext);
                             vector_append(right, yytext[0]);
                             BEGIN RIGHT_NT; }

<RIGHT_NT>[\n]              {printf("NEWLINE\n"); BEGIN CFG; }

<CFG>{nonterm}              {printf("nonterm  (left):  %s\n", yytext);
                             vector_append(left, yytext[0]);
                             BEGIN CFG_NT; }
<CFG>{term}                 {printf("Done with CFG parsing (found terminal "
                                    "on left side of production):  %s\n", yytext);
                             BEGIN DFA; }

{ws}                        ;
[\n]                        ;
.                           ;

%%

int main()
{
    int i;

    left = (Vector *)malloc(sizeof(Vector));
    vector_init(left);
    mid = (Vector *)malloc(sizeof(Vector));
    vector_init(mid);
    right = (Vector *)malloc(sizeof(right));
    vector_init(right);

    yylex();

    for (i=0; i < left->size; i++) {
        printf("%c --> %c %c\n", left->data[i], mid->data[i], right->data[i]);
    }
    return 0;
}
