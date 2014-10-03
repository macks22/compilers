#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "rdparser.h"
#include "tokens.h"

#define BUFSIZE 50

char *symtable[7] = {"EOF", "NT", "T", "GOES", "SEMI", "OR", "EOL"};
extern int lineno;
extern char *curtext;
int lookahead;
int verbose = 0;

Plist *plist;
char cur_nt;
char rhs[BUFSIZE];
int  rhs_flags[BUFSIZE];
int pos;

char in_grammar[26];
int  igpos = 0;

void
add_to_grammar(char nt)
{
    int i;
    for (i = 0; i < 26; i++) {
        if (in_grammar[i] == nt) return;
    }
    in_grammar[igpos++] = nt;
}

void
print_firsts(Plist *firsts)
{
    int i;
    LLnode *ntprods;
    for (i = 0; i < igpos; i++) {
        ntprods = get_nt_prods(firsts, in_grammar[i]);
        llist_print_set(ntprods);
    }
}

int
goes_to_epsilon(Plist *plist, char nt)
{
    LLnode *pnode;
    for_each_pnode(pnode, plist, nt) {
        if (strcmp(pnode->chars, "") == 0) return 1;
    }
    return 0;
}

void
add_to_firsts(Plist *firsts, char nt, char *c)
{
    if (strcmp(c, "") == 0) log_msg("[compute_first_set]: %c: epsilon\n", nt);
    else log_msg("[compute_first_set]: %c: %s\n", nt, c);
    plist_unique_add(firsts, nt, c);
}

void
firsts_rule3(Plist *firsts, Plist *plist, LLnode *pnode, char nt, int pos)
{
    LLnode *fnode;
    int flag;
    char other_nt, next_tok;

    // if the first char is a NT, and it goes to epsilon (has epsilon
    // in its linked list of productions), then add the first of the NEXT
    // thing (all its nodes), to FIRST(nt).
    if (pnode->flags[pos] == 0) return;  /* end of RHS indicator */
    other_nt = pnode->chars[pos];
    log_msg("[firsts_rule3]: checking token: %c... ", other_nt);

    if (pnode->flags[pos] == NT && goes_to_epsilon(plist, other_nt)) {
        log_msg("goes to epsilon.\n");
        flag = pnode->flags[pos+1];
        if (flag == 0) return;  /* no more valid tokens in RHS */

        next_tok = pnode->chars[pos+1];
        log_msg("[firsts_rule3]: next token: %c (flag %s)\n",
            next_tok, symtable[flag]);

        if (flag == T) {
            log_msg("[firsts_rule3]: adding %c to first set of %c\n",
                next_tok, nt);
            rhs[0] = next_tok; rhs[1] = '\0';
            add_to_firsts(firsts, nt, rhs);
        } else if (flag == NT) {
            log_msg("[firsts_rule3]: adding first set of %c to %c\n",
                next_tok, nt);
            for_each_pnode(fnode, firsts, next_tok) {
                add_to_firsts(firsts, nt, fnode->chars);
            }
        } else {  /* EOL = epsilon */
            log_msg("[firsts_rule3]: adding epsilon to first set of %c\n", nt);
            add_to_firsts(firsts, nt, "");
        }

        // recurse through remainder of RHS
        firsts_rule3(firsts, plist, pnode, nt, pos+1);

    } else {
        log_msg("does not go to epsilon.\n");
    }

}

Plist *
compute_first_set(Plist *plist, Plist *firsts, char nt)
{
    int pos = 0;
    LLnode *pnode, *fnode;
    for_each_pnode(pnode, plist, nt) {
        // if first element is a terminal (T), add the element to FIRST(nt)
        if (pnode->flags[0] == T) {
            rhs[0] = pnode->chars[0]; rhs[1] = '\0';
            add_to_firsts(firsts, nt, rhs);
        } else if (pnode->flags[0] == NT) {
            for_each_pnode(fnode, firsts, pnode->chars[0]) {
                if (strcmp(fnode->chars, "") != 0) {
                    add_to_firsts(firsts, nt, fnode->chars);
                }
            }
        }

        // if the node is empty (epsilon), add epsilon (empty) to FIRST(nt)
        if (strcmp(pnode->chars, "") == 0) {
            add_to_firsts(firsts, nt, "");
        }

        // if the first char is a NT, and it goes to epsilon (has epsilon
        // in its linked list of productions), then add the first of that
        // thing (all its nodes), to FIRST(nt).
        firsts_rule3(firsts, plist, pnode, nt, 0);
    }
}

Plist *
compute_first_sets(Plist *plist)
{   /* Given an array of production lists, compute the first sets for each
     * non-empty NT (each one in the CFG processed).
     */
    int i, nt, num_prods;
    Plist *firsts = plist_init();
    num_prods = -1;
    while (num_prods < firsts->num_prods) {
        num_prods = firsts->num_prods;
        for (i = 0; i < NUM_NT; i++) {
            nt = i + 65;
            compute_first_set(plist, firsts, nt);
        }
        log_msg("[compute_first_set]: Iteration complete. %d new.\n",
            firsts->num_prods - num_prods);
        if (verbose) {
            printf("\n");
            print_firsts(firsts);
            printf("\n");
        }
    }
    return firsts;
}

void
update_plist()
{   /* finished parsing a rule; now we need to update plist.
     */
    rhs[pos] = '\0';
    rhs_flags[pos] = 0;
    plist_addf(plist, cur_nt, rhs, rhs_flags);
    pos = 0;
}

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
    int i;
    char c;
    Plist *firsts;
    plist = plist_init();
    pos = 0;

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

    firsts = compute_first_sets(plist);

    printf("\nPARSED GRAMMAR:\n");
    plist_display(plist);

    log_msg("\nGOES TO EPSILON?\n");
    for (i = 0; i < igpos; i++) {
        c = in_grammar[i];
        log_msg("%c: ", c);
        if (goes_to_epsilon(plist, c)) {
            log_msg("YES\n");
        } else log_msg("NO\n");
    }

    printf("\n---------\n\n");
    printf("FIRST SETS:\n");
    print_firsts(firsts);

    plist_free(plist);
    plist_free(firsts);
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
        cur_nt = curtext[0];
        add_to_grammar(cur_nt);

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
        RULE();
        update_plist();
        PBODY_MORE();
    } else {
        error("PBODY");
    }
}

void
PBODY_MORE()
{   //  PBODY_MORE : OR RULE PBODY_MORE   {OR}
    //  PBODY_MORE : e                    {SEMI}

    log_msg("PBODY_MORE\n");
    if (lookahead == OR) {
        match(OR);
        RULE();
        update_plist();
        PBODY_MORE();
    } else if (lookahead == SEMI) return;  /* EOF */
    else error("PBODY_MORE");
}

void
RULE()
{   //  RULE : NT RULE   {NT}
    //  RULE : T RULE    {T}
    //  RULE : EOL       {EOL}

    log_msg("RULE\n");
    if (lookahead == NT) {
        rhs[pos] = curtext[0];
        rhs_flags[pos++] = NT;
        match(NT); RULE();
    } else if (lookahead == T) {
        rhs[pos] = curtext[0];
        rhs_flags[pos++] = T;
        match(T); RULE();
    } else if (lookahead == EOL) {
        rhs[pos] = '\0';
        rhs_flags[pos++] = EOL;
        match(EOL);
    } else error("RULE");
}
