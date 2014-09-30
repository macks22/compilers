%{
#include <stdarg.h>
#include "lib/vector.h"
#include "lib/hash.h"

int i; // used in for loops
int ruleno; // track which production is being processed
int reject; // set when string rejection is determined before EOL
int verbose;   // if set, output will be verbose
char start;    // track the start state (non-terminal = capital char)
char curstate; // track the current state during string testing
char *final_states;  // if curstate is in this list at end of string, accept
Vector *left, *mid, *right;  // used to store the DFA.
Vector *string;              // used to hold current string being parsed

void log_msg(char *fmt, ...);
void log_rule(int index);
void print_cfg();
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
/* %s DFA_S */

term        [a-z0-9]
nonterm     [A-Z][a-zA-Z0-9]*
prod        "-->"
ws          [ \t]+

%%

<INITIAL>{nonterm}          {start = adler32(yytext, yyleng);
                             vector_append(left, adler32(yytext, yyleng));
                             BEGIN CFG_NT; }

<CFG_NT>{prod}              {BEGIN RIGHT; }

<RIGHT>{term}               {vector_append(mid, yytext[0]);
                             BEGIN RIGHT_T; }
<RIGHT>[\n]                 {vector_append(mid, '\0');
                             vector_append(right, '\0');
                             add_final_state(left->data[ruleno++]);
                             BEGIN CFG; }

<RIGHT_T>{nonterm}          {vector_append(right, adler32(yytext, yyleng));
                             BEGIN RIGHT_NT; }

<RIGHT_NT>[\n]              {ruleno++; BEGIN CFG; }

<CFG>{nonterm}              {vector_append(left, adler32(yytext, yyleng));
                             BEGIN CFG_NT; }
<CFG>{term}                 {print_cfg();
                             curstate = start;
                             parse_token(yytext[0]);
                             BEGIN DFA; }

<DFA>{term}                 {parse_token(yytext[0]); }
<DFA>[\n]                   {if (valid_string()) printf("String accepted");
                             else printf("String rejected");
                             if (verbose) {
                                 printf(" (");
                                 vector_print(string);
                                 printf(")\n\n");
                             } else {
                                 printf("\n");
                             }
                             vector_reinit(string);  /* clear buf for next */
                             curstate = start;  /* start over for new string */
                             reject = 0;  /* ditto */
                            }

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
    vector_append(string, '\0');  // null terminate string: prep to log
    if (reject) {
        log_msg("early reject recognized\n");
        return 0;
    }
    for (i = 0; i < strlen(final_states); i++) {
        log_msg("%i == %i?\n", curstate, final_states[i]);
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
    vector_append(string, token);
    log_msg("processing token:     %c\n", token);
    for (i=0; i < left->size; i++) {
        if (left->data[i] == curstate && mid->data[i] == token) {
            /* if mid is not null, this won't be either */
            log_msg("using rule:           ");
            log_rule(i);
            log_msg("to change state FROM: %i\n", curstate);
            curstate = right->data[i];
            log_msg("to new state:         %i\n\n", curstate);
            action_taken = 1;
            break;
        }
    }
    if (!action_taken) { /* must take an action in order to be in language. */
        reject = 1;
        log_msg("no action taken\n");
        log_msg("current state:        %i\n\n", curstate);
        log_msg("REJECTED; PROCESSING TILL END.\n");
    }
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
        log_rule(i);
    }
    log_msg("\nSTART STATE IS: %i\n", start);
    log_msg("%i FINAL STATES: ", (int)strlen(final_states), final_states);
    for (i=0; i < strlen(final_states); i++) {
        log_msg("%i", final_states[i]);
    }
    log_msg("\n\n");
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

void
log_rule(int index)
{   /* Print ruleno. `index` from DFA vectors. */
    if (right->data[i] == '\0') {
        log_msg("%i --> %c %c\n",
            left->data[i], mid->data[i], right->data[i]);
    } else {
        log_msg("%i --> %c %i\n",
            left->data[i], mid->data[i], right->data[i]);
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
    right = (Vector *)malloc(sizeof(Vector));
    vector_init(right);
    string = (Vector *)malloc(sizeof(Vector));
    vector_init(string);

    // make space for the array of possible final states
    final_states = (char *)malloc(sizeof(char) * 26);

    yylex();  // kick off the lexer.
    return 0;
}
