%{
#include "lib/vector.h"
int i, len, ruleno;
char start;
char curstate;
char *final_states;
Vector *left, *mid, *right;

void printf_cfg();
void add_final_state(char state);
void parse_token(char token);
int valid_string();
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
nonterm     [A-Z][a-zA-Z0-9]*
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
                             add_final_state(left->data[ruleno]);
                             ruleno++;
                             BEGIN CFG; }

<RIGHT_T>{nonterm}          {printf("nonterm: %s\n", yytext);
                             vector_append(right, yytext[0]);
                             BEGIN RIGHT_NT; }

<RIGHT_NT>[\n]              {printf("NEWLINE\n"); ruleno++; BEGIN CFG; }

<CFG>{nonterm}              {printf("nonterm  (left):  %s\n", yytext);
                             vector_append(left, yytext[0]);
                             BEGIN CFG_NT; }
<CFG>{term}                 {printf("Done with CFG parsing (found terminal "
                                    "on left side of production)\n");
                             printf("char: %c\n", yytext[0]);
                             curstate = start;
                             parse_token(yytext[0]);
                             BEGIN DFA; }

<DFA>{term}                 {printf("char: %c\n", yytext[0]);
                             parse_token(yytext[0]); }
<DFA>[\n]                   {if (valid_string()) { printf("String accepted\n"); }
                             else { printf("String rejected\n"); }
                            }

{ws}                        ;
[\n]                        ;
.                           ;

%%

int
valid_string()
{
    for (i = 0; i <= strlen(final_states); i++) {
        if (final_states[i] == curstate) {
            return 1;
        }
    }
    return 0;
}

void
parse_token(char token)
{
    printf("processing token:    %c\n", token);
    for (i=0; i < left->size; i++) {
        if (left->data[i] == curstate && mid->data[i] == token) {
            /* if mid is not null, this won't be either */
            printf("using rule: ");
            printf("%c --> %c %c\n", left->data[i], mid->data[i], right->data[i]);
            printf("to change state FROM: %c\n", curstate);
            printf("to new state          %c\n\n", curstate);
            curstate = right->data[i];
            break;
        }
    }
}

void
add_final_state(char state)
{
    len = strlen(final_states);
    final_states[len++] = state;
    final_states[len] = '\0';
}

void
print_cfg()
{
    for (i=0; i < left->size; i++) {
        printf("%c --> %c %c\n", left->data[i], mid->data[i], right->data[i]);
    }
}

int
main()
{
    // set the ruleno to 0; used to track which rule is being processed
    ruleno = 0;

    // initialize the table vectors
    left = (Vector *)malloc(sizeof(Vector));
    vector_init(left);
    mid = (Vector *)malloc(sizeof(Vector));
    vector_init(mid);
    right = (Vector *)malloc(sizeof(right));
    vector_init(right);

    // make space for the array of possible final states
    final_states = (char *)malloc(sizeof(char) * 26);

    yylex();

    print_cfg();
    printf("\nfinal states: %s\n", final_states);
    return 0;
}
