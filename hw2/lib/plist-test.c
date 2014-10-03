// plist-test.c

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "plist.h"

int
main()
{
    int i;
    int *flags = calloc(3, sizeof(int));
    flags[0] = 0; flags[1] = 1; flags[2] = 2;
    Plist *plist;
    LLnode *pnode;

    plist = plist_init();
    assert(plist->num_prods == 0);
    assert(plist_count(plist, 'A') == 0);

    plist_add(plist, 'A', "aBC");
    assert(plist_count(plist, 'A') == 1);
    assert(plist->num_prods == 1);
    plist_add(plist, 'A', "");
    assert(plist_count(plist, 'A') == 2);
    assert(plist->num_prods == 2);
    plist_display(plist);
    plist_unique_add(plist, 'A', "aBC");
    assert(plist_count(plist, 'A') == 2);
    assert(plist->num_prods == 2);
    plist_display(plist);

    plist_addf(plist, 'A', "aCD", (char *)flags);

    for_each_pnode(pnode, plist, 'A') {
        printf("%s\n", pnode->chars);
    }

    free(flags);
}
