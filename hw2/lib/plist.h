// plist.h
//
// For CFGs, we always have a list of productions. For this assignment, those
// productions always start with a nonterminal, which is a single [A-Z] char.
// In order to hold these, we'll construct an array of length 26, where each
// slot holds the pointer to the head node of a linked list. In this way, the
// nonterminals can be used to directly index into the data structure by
// subtracting 65 from their ASCII ordinals.
//
// The data structure will also maintain a count of how many productions have
// been entered so far. For each linked list (each nonterminal), the first node
// will contain the nonterminal itself, and each subsequent node corresponds to
// a single production, where the node's char array will hold the RHS of the
// production. A node whose char array is empty (strlen(node->chars) == 1)
// corresponds to epsilon in the CFG.


#include "llist.h"

#define NUM_NT 26

#define GET_INDEX(NT) (NT - 65)

#define get_nt_prods(plist, NT) (plist->nodes[GET_INDEX(NT)])

// assign prod to each node after the first
#define for_each_pnode(pnode, plist, NT) \
    for (pnode = get_nt_prods(plist, NT)->next; \
         pnode != '\0'; \
         pnode = pnode->next)

typedef struct {
    LLnode **nodes;
    int num_prods;
} Plist;

Plist * plist_init();

void plist_add(Plist *plist, char nt, char *rhs);

void plist_unique_add(Plist *plist, char nt, char *rhs);

void plist_addf(Plist *plist, char nt, char *rhs, int *flags);

void plist_unique_addf(Plist *plist, char nt, char *rhs, int *flags);

int plist_count(Plist *plist, char nt);

void plist_display(Plist *plist);

void plist_free(Plist *plist);

void plist_display_sets(Plist *plist);
