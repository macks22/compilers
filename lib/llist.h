// llist.h
//
// Basic singly linked list implementation.

#define LLIST_NUM_CHARS 50

typedef struct LLnode {
    char *chars;
    struct LLnode *next;
} LLnode;

LLnode * llist_node_init(char * chars);

LLnode * llist_next(LLnode *head);

void llist_append(LLnode *head, LLnode *node);

LLnode * llist_pop(LLnode *head);

void llist_insert(LLnode *head, LLnode *node, int pos);

int llist_length(LLnode *head);

void llist_print(LLnode *head);

void llist_free(LLnode *head);
