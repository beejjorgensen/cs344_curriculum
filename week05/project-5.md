<!-- Project 5: Linked Lists-->

## Introduction

We're going to implement a linked list.

The goals here are multifold:

* Get used to the user side of memory management
* Refresh on linked lists as a concept (since we'll be using these soon)
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
* `dh`: delete the node from the head of the list; does nothing if the
  list is empty
* `f`: free the entire list
* `p`: print the list to standard output

Example runs:

```
./llist it 1 it 2 it 3 p
1 -> 2 -> 3
```

```
$ ./llist ih 1 ih 2 ih 3 p
3 -> 2 -> 1
```

```
$ ./llist ih 12 ih 13 it 14 p dh p
13 -> 12 -> 14
12 -> 14
```

```
$ ./llist ih 20 ih 40 it 5 p dh p dh p dh p
40 -> 20 -> 5
20 -> 5
5
[empty]
```

```
$ ./llist ih 20 p dh dh dh dh dh dh dh p
20
[empty]
```

```
%  ./llist ih 1 ih 2 p f p ih 3 p
2 -> 1
[empty]
3
```

## What to Do

You can use any C standard library functions or syscalls for this
project.

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

* `node_alloc(3490)`: allocate a new `struct node` with `value` 3490 and
  a `next` of `NULL`.

* `node_free(n)`: free a node previously allocated with `node_alloc()`.

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

## Parsing the Command Line

The "ih" and "it" commands take an argument: an `int` value to insert in
the list at that point.

But all the values in `argv[]` are strings.

You'll have to convert the argument in question to an `int` with a
function like `atoi()`:

```c
char *s = "16";

int x = atoi(s);

printf("%d\n", x * 2);  // 32
```

## What's That `struct node **` and Should I Be Nervous?

Some of these functions will modify the head of the list. Because it
might need to be modified, we have to pass a pointer to the head to a
function.

This is just like if we want to modify an integer in a function, we have
to pass a pointer to that integer and modify the value via the pointer.

``` c
int add5(int *p)
{
    *p += 5;
}

int main(void)
{
    int x = 10;

    add5(&x);

    printf("%d\n", x);  // 15
}
```

So we have the head of the list, which is a pointer to a `struct node`:

``` c
struct node *head = NULL;  // head points to empty list
```

And if we want a function to be able to modify it, we have to pass a
pointer to it, a pointer to a `struct node *`.

In other words, a `struct node **`.

``` c
void llist_insert_head(struct node **head, struct node *n) {
    // TODO: code to insert at head
}

int main(void)
{
    struct node *head = NULL;

    struct node *n = node_alloc(10);
    llist_insert_head(&head, n);
}
```

One way to think of it is that address-of (`&`) adds another level of
pointer, and dereference (`*`) digs down a level.

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **115 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

If you want more challenges:

* Write a function to return the length of the list
* Write a function to delete from the middle of the list by index
* Write a function to delete from list by value
* Write a function to reverse the list by juggling pointers
  * If you wrote this function iteratively, rewrite it recursively. Or
    vice-versa.

<!--
Rubric:

llist_insert_head functions on empty list (10)
llist_insert_head functions on non-empty list (5)
llist_delete_head returns NULL on empty list (5)
llist_delete_head functions on non-empty list (10)
llist_insert_tail functions on empty list (10)
llist_insert_tail functions on non-empty list (10)
llist_free frees all nodes (10)
llist_free sets head to NULL (5)
llist_free works on empty list (5)
llist_print prints correctly (10)
node_alloc properly allocates and initializes a node (5)
node_free properly frees the node (5)
command line 'ih' command functions properly (5)
command line 'it' command functions properly (5)
command line 'dh' command functions properly (5)
command line 'f' command functions properly (5)
command line 'p' command functions properly (5)

-->