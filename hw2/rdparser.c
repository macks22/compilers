#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "rdparser.h"
#include "tokens.h"

char *symtable[7] = {"EOF", "NT", "T", "GOES", "SEMI", "OR", "EOL"};
extern int lineno;
int lookahead;
int verbose = 0;

void
log_msg(char *fmt, ...)
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
        verbose = 1;  // turn on logging
    }

    lookahead = yylex();
    PLIST();
    if (lookahead == 0) {  /* no more input */
        printf("ACCEPTED\n");
    } else {
        printf("REJECTED\n");
    }
    return 0;
}

void
match(int token)
{   /* Determine if the current lookahead matches the expected token.
     * Consume it and update the lookahead if it does,
     * otherwise indicate a syntax error.
     */

    if (token == lookahead) {
        log_msg("%s ", symtable[token]);
        lookahead = yylex();
    } else error("match");
}

void
error(char *where)
{   /* Indicate that a syntax error has occured;
     * this is meant to be called with the name of the function where the
     * error occurred. The lineno will be included in the output.
     */

    printf("Syntax error line %d: %s\n", lineno, where);
    if (lookahead != OTHER) {
        printf("Token seen: %s\n", symtable[lookahead]);
    } else {
        printf("Token seen: undefined in langauge\n");
    }
    exit(42);
}

void
PLIST()
{   //  PLIST : PROD PLIST_MORE   {NT}

    log_msg("PLIST\n");
    if (lookahead == NT) { PROD(); PLIST_MORE(); }
    else error("PLIST");
}

void
PLIST_MORE()
{   //  PLIST_MORE : PROD PLIST_MORE  {NT}
    //  PLIST_MORE : e                {$}

    log_msg("PLIST_MORE\n\n");
    if (lookahead == NT) { PROD(); PLIST_MORE(); }
    else if (lookahead == 0) return;  /* EOF */
    else error("PLIST_MORE");
}

void
PROD()
{   //  PROD : NT GOES PBODY SEMI EOL  {NT}

    log_msg("PROD\n");
    if (lookahead == NT) {
        match(NT); match(GOES);
        PBODY();
        match(SEMI); match(EOL);
    } else {
        error("PROD");
    }
}

void
PBODY()
{   //  PBODY : RULE PBODY_MORE  {NT,T,EOL}
    log_msg("PBODY\n");
    if ((lookahead == NT) || (lookahead == T) || (lookahead == EOL)) {
        RULE(); PBODY_MORE();
    } else {
        error("PBODY");
    }
}

void
PBODY_MORE()
{   //  PBODY_MORE : OR RULE PBODY_MORE   {OR}
    //  PBODY_MORE : e                    {SEMI}

    log_msg("PBODY_MORE\n");
    if (lookahead == OR) { match(OR); RULE(); PBODY_MORE(); }
    else if (lookahead == SEMI) { return; }  /* EOF */
    else error("PBODY_MORE");
}

void
RULE()
{   //  RULE : NT RULE   {NT}
    //  RULE : T RULE    {T}
    //  RULE : EOL       {EOL}

    log_msg("RULE\n");
    if (lookahead == NT) { match(NT); RULE(); }
    else if (lookahead == T) { match(T); RULE(); }
    else if (lookahead == EOL) { match(EOL); }
    else error("RULE");
}
