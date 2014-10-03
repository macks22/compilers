#include <string.h>
#include <assert.h>
#include "llist.h"
#include "log.h"

int verbose = 0;

int
main(int argc, char *argv[])
{
    LLnode *head;
    int i;

    if (argc == 2 && strcmp(argv[1], "-v") == 0) {
        verbose = 1;  // turn on logging
    }

    ///////////////////////////////////////////////////////////////////////////
    // int llist_length(LLnode *head)
    //
    // Tested throughout.

    ///////////////////////////////////////////////////////////////////////////
    // LLnode * llist_node_init();
    //
    head = llist_node_init("one");
    assert(head != NULL);
    assert(head->next == NULL);
    head->chars = "00000000000000000000000000000000000000000000000000";
    head->chars = "one";
    assert(llist_length(head) == 1);

    ///////////////////////////////////////////////////////////////////////////
    // llist_next(LLnode *head)
    // llist_append(LLnode *head, LLnode *node)
    //
    assert(llist_next(head) == NULL);
    LLnode *new = llist_node_init("two");
    llist_append(head, new);
    assert(llist_next(head) == new);
    assert(llist_next(new) == NULL);
    assert(llist_length(head) == 2);

    ///////////////////////////////////////////////////////////////////////////
    // LLnode * llist_pop(LLnode *head);
    //
    LLnode *ref = llist_pop(head);
    assert(ref == new);
    assert(strcmp(ref->chars, new->chars) == 0);
    assert(llist_length(head) == 1);
    llist_append(head, new);
    assert(llist_length(head) == 2);

    ///////////////////////////////////////////////////////////////////////////
    // void llist_insert(LLnode *head, LLnode *node, int pos);
    //
    LLnode *new2 = llist_node_init("three");
    llist_print(head);
    llist_insert(head, new2, 1);
    assert(llist_next(head) == new2);
    assert(llist_next(new2) == new);
    assert(llist_length(head) == 3);
    llist_print(head);

    LLnode *new3 = llist_node_init("four");
    llist_insert(head, new3, 3);
    assert(llist_length(head) == 4);
    llist_print(head);

    llist_free(head);
    return 0;
}
