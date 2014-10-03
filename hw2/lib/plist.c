// plist.c

#include <stdlib.h>
#include <string.h>
#include "plist.h"


Plist *
plist_init()
{   /* Initialize a new Plist and return a pointer to it.
     */
    int i;
    char val[2];

    Plist *plist = calloc(1, sizeof(Plist));
    plist->nodes = calloc(NUM_NT, sizeof(LLnode *));
    for (i = 0; i < NUM_NT; i++) {
        val[0] = i + 65; val[1] = '\0';
        plist->nodes[i] = llist_node_init(val);
    }
    plist->num_prods = 0;
    return plist;
}

void
plist_add(Plist *plist, char nt, char *rhs)
{   /* Add a new production to the production list for the given nonterminal.
     */
    LLnode *ntprods = get_nt_prods(plist, nt);
    llist_append(ntprods, llist_node_init(rhs));
    plist->num_prods++;
}

void
plist_unique_add(Plist *plist, char nt, char *rhs)
{   /* Ensure no other nodes with an equivalent char array as `rhs` exist
     * before adding a new node.
     */
    LLnode *pnode;
    for_each_pnode(pnode, plist, nt) {
        if (strcmp(pnode->chars, rhs) == 0) return;
    }
    plist_add(plist, nt, rhs);
}

void
plist_addf(Plist *plist, char nt, char *rhs, int *flags)
{   /* Add a new production to the production list for the given nonterminal.
     */
    int i;
    LLnode *ntprods = get_nt_prods(plist, nt);
    LLnode *new = llist_node_init(rhs);
    for (i = 0; i < strlen(rhs); i++) {
        new->flags[i] = flags[i];
    }
    llist_append(ntprods, new);
    plist->num_prods++;
}

void
plist_unique_addf(Plist *plist, char nt, char *rhs, int *flags)
{   /* Ensure no other nodes with an equivalent char array as `rhs` exist
     * before adding a new node.
     */
    LLnode *pnode;
    for_each_pnode(pnode, plist, nt) {
        if (strcmp(pnode->chars, rhs) == 0) return;
    }
    plist_addf(plist, nt, rhs, flags);
}

int
plist_count(Plist *plist, char nt)
{   /* Return the number of productions in the Plist for the given nonterminal.
     */
    LLnode *ntprods = get_nt_prods(plist, nt);
    return (llist_length(ntprods) - 1);
}

void
plist_display(Plist *plist)
{   /* Print out the whole production list.
     */
    int i;
    for (i = 0; i < NUM_NT; i++) {
        if (plist_count(plist, (i + 65)) > 0) {
            llist_print(plist->nodes[i]);
        }
    }
}

// TODO: seems to be leaking memory still (also in llist_free)
void
plist_free(Plist *plist)
{
    int i;
    for (i = 0; i < NUM_NT; i++) {
        llist_free(plist->nodes[i]);
    }
    free(plist->nodes);
    free(plist);
}

void
plist_display_sets(Plist *plist)
{
    int i;
    for (i = 0; i < NUM_NT; i++) {
        if (plist_count(plist, (i + 65)) > 0) {
            llist_print_set(plist->nodes[i]);
        }
    }
}
