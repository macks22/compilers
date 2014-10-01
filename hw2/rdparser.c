#include <stdio.h>
#include <stdlib.h>
#include "rdparser.h"
#include "tokens.h"

char *symtable[7] = {"EOF", "NT", "T", "GOES", "SEMI", "OR", "EOL"};
extern int lineno;
int lookahead;

int
main()
{
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
{
    if (token == lookahead) {
        printf("%s ", symtable[token]);
        lookahead = yylex();
    } else error("match");
}

void
error(char *where)
{
    printf("Syntax error line %d: %s\n", lineno, where);
    if (lookahead != OTHER) {
        printf("Token seen: %s\n", symtable[lookahead]);
    } else {
        printf("Token seen: undefined in langauge\n");
    }
    exit(42);
}

//  PLIST      :  PROD PLIST_MORE           {NT}
void
PLIST()
{
    printf("PLIST\n");
    if (lookahead == NT) { PROD(); PLIST_MORE(); }
    else error("PLIST");
}

//  PLIST_MORE :  PROD PLIST_MORE           {NT}
//  PLIST_MORE :  e                         {$}
void
PLIST_MORE()
{
    printf("PLIST_MORE\n\n");
    if (lookahead == NT) { PROD(); PLIST_MORE(); }
    else if (lookahead == 0) return;  /* EOF */
    else error("PLIST_MORE");
}

//  PROD       :  NT GOES PBODY SEMI EOL  {NT}
void
PROD()
{
    printf("PROD\n");
    if (lookahead == NT) {
        match(NT); match(GOES);
        PBODY();
        match(SEMI); match(EOL);
    } else {
        error("PROD");
    }
}

//  PBODY      :  RULE PBODY_MORE           {NT,T,EOL}
void
PBODY()
{
    printf("PBODY\n");
    if ((lookahead == NT) || (lookahead == T) || (lookahead == EOL)) {
        RULE(); PBODY_MORE();
    } else {
        error("PBODY");
    }
}

//  PBODY_MORE :  OR RULE PBODY_MORE        {OR}
//  PBODY_MORE :  e                         {SEMI}
void
PBODY_MORE()
{
    printf("PBODY_MORE\n");
    if (lookahead == OR) { match(OR); RULE(); PBODY_MORE(); }
    else if (lookahead == SEMI) { return; }  /* EOF */
    else error("PBODY_MORE");
}

//  RULE       :  NT RULE                   {NT}
//  RULE       :  T RULE                    {T}
//  RULE       :  EOL                       {EOL}
void
RULE()
{
    printf("RULE\n");
    if (lookahead == NT) { match(NT); RULE(); }
    else if (lookahead == T) { match(T); RULE(); }
    else if (lookahead == EOL) { match(EOL); }
    else error("RULE");
}
