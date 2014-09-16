%{
#include <stdarg.h>
#include "lib/vector.h"

int i; // used in for loops
int ruleno; // track which production is being processed
int reject; // set when string rejection is determined before EOL
int verbose;    // if set, output will be verbose
char start;    // track the start state (non-terminal = capital char)
char curstate; // track the current state during string testing
char *final_states;  // if curstate is in this list at end of string, accept
Vector *left, *mid, *right;  // used to store the DFA.

void log_msg(char *fmt, ...);
void printf_cfg();
void add_final_state(char state);
int parse_token(char token);
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
/* used to identify empty lines/whitespace at beginning */
%s DFA_S

term        [a-z]
nonterm     [A-Z][a-zA-Z0-9]*
prod        "-->"
ws          [ \t]+

%%

<INITIAL>{nonterm}          {start = yytext[0];
                             vector_append(left, yytext[0]);
                             BEGIN CFG_NT; }

<CFG_NT>{prod}              {BEGIN RIGHT; }

<RIGHT>{term}               {vector_append(mid, yytext[0]);
                             BEGIN RIGHT_T; }
<RIGHT>[\n]                 {vector_append(mid, '\0');
                             vector_append(right, '\0');
                             add_final_state(left->data[ruleno]);
                             ruleno++;
                             BEGIN CFG; }

<RIGHT_T>{nonterm}          {vector_append(right, yytext[0]);
                             BEGIN RIGHT_NT; }

<RIGHT_NT>[\n]              {ruleno++; BEGIN CFG; }

<CFG>{nonterm}              {vector_append(left, yytext[0]);
                             BEGIN CFG_NT; }
<CFG>{term}                 {curstate = start;
                             parse_token(yytext[0]);
                             BEGIN DFA; }

<DFA>{term}                 {if (!parse_token(yytext[0])) { reject = 1; } }
<DFA>[\n]                   {if (valid_string()) { printf("String accepted\n"); }
                             else { printf("String rejected\n"); }
                             curstate = start;  /* start over for new string */
                             BEGIN DFA_S; }

<DFA_S>{term}               {parse_token(yytext[0]);
                             BEGIN DFA;}
<DFA_S>[\n]                 ;

{ws}                        ;
[\n]                        ;
.                           ;

%%

int
valid_string()
{   /* First check the value of the reject flag. This flag is used to indicate
     * rejection of a string at a token before the final token in the string. If
     * it is set, then immediately reject the string. Otherwise, if current
     * state is in the set of final states, return 1, else 0.
     */
    if (reject) {
        return 0;
    }
    for (i = 0; i <= strlen(final_states); i++) {
        if (final_states[i] == curstate) {
            return 1;
        }
    }
    return 0;
}

int
parse_token(char token)
{   /* For each token, try to find a production that moves from the current
     * state to another state using this token. If none can be found, then
     * reset the current state to the start state and return 0. Otherwise
     * process the production, changing the state, then return 1.
     */
    int action_taken = 0;
    log_msg("processing token:    %c\n", token);
    for (i=0; i < left->size; i++) {
        if (left->data[i] == curstate && mid->data[i] == token) {
            /* if mid is not null, this won't be either */
            log_msg("using rule: ");
            log_msg("%c --> %c %c\n", left->data[i], mid->data[i], right->data[i]);
            log_msg("to change state FROM: %c\n", curstate);
            curstate = right->data[i];
            log_msg("to new state:         %c\n", curstate);
            action_taken = 1;
            break;
        }
    }
    log_msg("current state: %c\n\n", curstate);
    return action_taken;
}

void
add_final_state(char state)
{   /* Add a state to the array of final states.
     * Does not check for overlap, but adding the same state multiple times
     * will have no noticeable effect on subsequent parsing.
     */
    int len = strlen(final_states);
    final_states[len++] = state;
    final_states[len] = '\0';
}

void
print_cfg()
{   /* Print the Context-Free Grammar parsed from the productions. */
    for (i=0; i < left->size; i++) {
        printf("%c --> %c %c\n", left->data[i], mid->data[i], right->data[i]);
    }
}

void log_msg(char *fmt, ...)
{   /* Wrap printf in order to log based on a flag. */
    va_list args;
    if (verbose) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

int
main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-v") == 0) {
        // set logging
        verbose = 1;
    }

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

    yylex();  // kick off the lexer.
    return 0;
}
