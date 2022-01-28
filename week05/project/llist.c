#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

void insert_head(struct node **head, struct node *n)
{
    n->next = *head;
    *head = n;
}

struct node *delete_head(struct node **head)
{
    if (*head == NULL)
        return NULL;

    struct node *old_head = *head;

    *head = (*head)->next;

    old_head->next = NULL;

    return old_head;
}

void insert_tail(struct node **head, struct node *n)
{
    if (*head == NULL) {
        n->next = *head;
        *head = n;

        return;
    }

    struct node *p = *head;

    while (p->next != NULL)
        p = p->next;

    p->next = n;
    n->next = NULL;
}

void print_list(struct node *head)
{
    if (head == NULL) {
        printf("[empty]\n");
        return;
    }

    while (head != NULL) {
        printf("%d", head->value);

        if (head->next != NULL)
            printf(" -> ");

        head = head->next;
    }

    putchar('\n');
}

struct node *alloc_node(int value)
{
    struct node *n;

    n = malloc(sizeof *n);
    n->value = value;
    n->next = NULL;

    return n;
}

void free_node(struct node *n)
{
    free(n);
}

void free_list(struct node **head)
{
    while (*head != NULL) {
        struct node *old_next = (*head)->next;

        free_node(*head);

        *head = old_next;
    }
}

int main(void)
{
    struct node *head = NULL;
    struct node *n, *p;

    print_list(head);

    for (int i = 0; i < 3; i++) {
        n = alloc_node(i);
        insert_head(&head, n);
        print_list(head);
    }

    for (int i = 1; i <= 3; i++) {
        n = alloc_node(i*11);
        insert_tail(&head, n);
        print_list(head);
    }

    while ((p = delete_head(&head)) != NULL) {
        printf("Deleted %d\n", p->value);
        free_node(p);
    }

    print_list(head);
}