#ifndef LLIST_H
#define LLIST_H

struct node {
    int value;
    struct node *next;
};

void llist_insert_head(struct node **head, struct node *n);
struct node *llist_delete_head(struct node **head);
void llist_insert_tail(struct node **head, struct node *n);
void llist_print(struct node *head);
void llist_free(struct node **head);

struct node *node_alloc(int value);
void node_free(struct node *n);

#endif