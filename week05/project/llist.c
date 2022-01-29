#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

enum cmd {
    CMD_UNKNOWN,
    CMD_INSERT_HEAD,
    CMD_INSERT_TAIL,
    CMD_DELETE_HEAD,
    CMD_PRINT
};

void llist_insert_head(struct node **head, struct node *n)
{
    n->next = *head;
    *head = n;
}

struct node *llist_delete_head(struct node **head)
{
    if (*head == NULL)
        return NULL;

    struct node *old_head = *head;

    *head = (*head)->next;

    old_head->next = NULL;

    return old_head;
}

void llist_insert_tail(struct node **head, struct node *n)
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

void llist_print(struct node *head)
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

struct node *node_alloc(int value)
{
    struct node *n;

    n = malloc(sizeof *n);
    n->value = value;
    n->next = NULL;

    return n;
}

void node_free(struct node *n)
{
    free(n);
}

void llist_free(struct node **head)
{
    while (*head != NULL) {
        struct node *old_next = (*head)->next;

        node_free(*head);

        *head = old_next;
    }
}

enum cmd tokenize(char *s)
{
    if (strcmp(s, "ih") == 0)
        return CMD_INSERT_HEAD;
    else if (strcmp(s, "it") == 0)
        return CMD_INSERT_TAIL;
    else if (strcmp(s, "dh") == 0)
        return CMD_DELETE_HEAD;
    else if (strcmp(s, "p") == 0)
        return CMD_PRINT;

    return CMD_UNKNOWN;
}

int main(int argc, char **argv)
{
    struct node *head = NULL;

    if (argc == 1) {
        fprintf(stderr, "usage: llist command [command ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        char *strc = argv[i];
        enum cmd c = tokenize(argv[i]);
        int cmd_arg;
        struct node *n;

        if (c == CMD_INSERT_HEAD || c == CMD_INSERT_TAIL)
            cmd_arg = atoi(argv[++i]);

        switch (c) {
            case CMD_INSERT_HEAD:
                n = node_alloc(cmd_arg);
                llist_insert_head(&head, n);
                break;

            case CMD_INSERT_TAIL:
                n = node_alloc(cmd_arg);
                llist_insert_tail(&head, n);
                break;

            case CMD_DELETE_HEAD:
                n = llist_delete_head(&head);
                node_free(n);
                break;

            case CMD_PRINT:
                llist_print(head);
                break;

            default:
                fprintf(stderr, "llist: unknown command \"%s\"\n", strc);
                break;
        }
    }
}