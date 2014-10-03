// llist.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

LLnode *
llist_node_init(char *chars)
{   /* Initialize a new linked list (simply make a new LLnode) and return a
     * pointer to it. The value of the char array is set using strcpy with the
     * input `chars`.
     */
    LLnode *head = (LLnode *)calloc(1, sizeof(LLnode));
    head->chars = (char *)calloc(LLIST_NUM_CHARS, sizeof(char));
    head->next = NULL;
    strcpy(head->chars, chars);
    return head;
}

LLnode *
llist_next(LLnode *head)
{   /* Return the next node in the linked list.
     */
    return head->next;
}

void
llist_append(LLnode *head, LLnode *node)
{   /* Append the given node to the end of the list which `head` resides in.
     */
    if (head->next == NULL) {
        head->next = node;
    } else {
        llist_append(head->next, node);
    }
}

void
llist_insert(LLnode *head, LLnode *node, int pos)
{   /* Insert a node at a particular position. If a position is passed that
     * is beyond the end of the list, this will likely segfault. Note that
     * an insert at 0 will place the node before the current head, which should
     * subsequently be updated to the node given.
     */
    if (pos == 0) {
        node->next = head;
    } else if (pos == 1) {
        llist_insert(head->next, node, pos-1);
        head->next = node;
    } else {
        llist_insert(head->next, node, pos-1);
    }
}

LLnode *
llist_pop(LLnode *head)
{   /* Remove the last node in the list and return it. The only tricky part of
     * this is that the node directly before must have its pointer set to NULL.
     * If only one node is in the list, it will be returned.
     */
    LLnode *next = head->next;
    if (next == NULL) return head;  /* only if 1 node in list */
    else if (next->next == NULL) {
        head->next = NULL;
        return next;
    }
    return llist_pop(head->next);
}

int
llist_length(LLnode *head)
{   /* Return the number of nodes in the linked list.
     */
    if (head->next == NULL) return 1;
    return 1 + llist_length(head->next);
}

void
llist_print(LLnode *head)
{   /* Print the contents of the linked list in a way that looks like a linked
     * list.
     */
    if (head->next == NULL) {
        printf("[%s] ->\n", head->chars);
        return;
    }
    printf("[%s] -> ", head->chars);
    llist_print(head->next);
}

void
llist_free(LLnode *head)
{
    if (head->next != NULL) {
        llist_free(head->next);
    }
    free(head->chars);
    free(head);
}
