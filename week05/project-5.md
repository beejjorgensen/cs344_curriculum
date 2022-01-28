<!-- Project 5: Linked Lists-->

## Introduction

We're going to implement a linked list.

The goals here are multifold:

* Get used to the user side of memory management
* Refresh on linked lists as a concept
* Get more pointer practice

Subsequent projects may make use of this.

This will be a linked list with no dummy node or metadata node; the head
pointer will point directly to a linked list node, or will be `NULL`
indicating the list is empty.

The program itself will accept commands given on the command line.

The commands are:

* `ih`: insert the next number on the command line at the head of the
  list.
* `it`: insert the next number on the command line at the tail of the
  list.
* `dh`: delete the node from the head of the list
* `p`: print the list to standard output

Example run:

```
$ ./llist ih 12 ih 13 it 14 p dh p
13 -> 12 -> 14
12 -> 14
```

## What to Do

You're going to be implementing the functions in the following header
file, `llist.h`. Don't modify this file, and `#include` it from your
`llist.c` source.

```
// llist.h

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
```

### Function Breakdown

And example usage, given `struct node *head`:

* `llist_insert_head(&head, n)`: insert node `n` at the head of the
  list. The node should have been previously allocated with
  `node_alloc()`.

* `list_delete_head(&head)`: remove a node from the head of the list and
  return a pointer to it. Return `NULL` if the list is empty. This
  function does **not** free the node; it merely uncouples it from the
  list.

* `llist_insert_tail(&head, *n)`: insert node `n` at the tail of the
  list. The node should have been previously allocated with
  `node_alloc()`.

* `llist_print(head)`: print a list to standard output in this form:

   ```
   1 -> 12 -> 3490 -> 7
   ```

   with no trailing or leading spaces on the line. If the list is empty,
   the string `[empty]` (including square brackets) should be printed.

   ```
   [empty]
   ```

* `llist_free(&head)`: call `node_free()` for every node in the list.
  `head` will be set to `NULL`.

### Suggested Approach

* Write the command line parser first. Make sure you're getting the
  right numbers with the right commands. You can either parse the whole
  command into some structure first, or you can just run list commands
  as you process `argv`.
* Write `node_alloc()` to allocate a node with a given value.
* Write `node_free()` to free the node.
* Get `llist_print()` in place. Maybe test it by allocating a
  quick node to your `head` pointer and passing it in.
* Write `llist_insert_head()` and get it working.
* Followed by the other ones.

## What's That `struct node **` and Should I Be Nervous?


## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **TODO points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

If you want more challenges:
