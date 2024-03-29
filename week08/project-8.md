<!-- Project 7: Coalescing Free Memory -->

## Introduction

This week we want to wrap up our `malloc()` replacement.

The big thing that is missing is _coalescing_ free spaces into a single
free space.

For example, if we have these allocations:

![Before Free]()

and the user calls `myfree()` on the second block, leaving us with this:

![After Free]()

we have two free regions right next to each other. We want to merge
those into a single, larger free region, like this:

![Consolidating Two Blocks]()

(The result size is 64 bytes since we're adding together 16 bytes of
free region, plus (presumably) 16 bytes for the `struct block`, plus 32
bytes of previously-used memory.)

Somewhat more complicatedly, if we free a region that has free space on
both sides, we want to merge all three of them.

So if we had this:

![Before Middle Free]()

and we freed the used block, it would merge all three of those initial
blocks like this:

![After Middle Free]()

We have multiple options for how to make this happen. Choose one of
them!

### Approach Option 1

This one is likely the simpler of the two.

Since we have a singly-linked list, there's no easy way to look at which
block is _before_ the one we just freed. It would be easy to look at
`->next` to see if the next one is also free and needs to be merged, but
we can't look back.

With Option 1, we'll walk the entire list after `myfree()` marks the
block not `in_use` and merge any free blocks we come to,

Algorithm:


```
start cur at head

while cur->next isn't NULL:
    if cur is not in_use and next node not in use:
        add the next node's region's size to cur's
        make cur's next pointer skip the next node
    else
        move cur to next node
```

Note that when you add the next node's size to this node's, you have to
add the next node's size PLUS the padded size of the `struct block` that
goes with it. The whole region (the `struct` and the user data) is
going to be added to the existing free node.

> You might notice that we're not zeroing the memory of the freed
> nodes, not even the memory that contains the old `struct block`. This
> is OK; in general in C, uninitialized space is assumed to contain
> "garbage".


The time complexity of this approach is _O(n)_ over the number of nodes
in the list.

### Approach Option 2

Since the problem with Option 1 was that we couldn't look backward in
the singly-linked list, we could fix this by converting to a
doubly-linked list.

We know that all mergers of free blocks must be immediately adjacent to
the recently `myfree()`d block. (If it were farther away, it would have
been merged earlier.

So all we have to do is check the previous and next nodes to see if
they're not in use and merge them if they aren't.

Algorithm `mergeblocks` merges two adjacent free blocks:

```
mergeblocks(cur):
    if cur is not NULL and
       cur is not in_use and
       cur's next is not NULL and
       the next node is not in_use:

        add the next node's size to cur
        rewire the list so cur's next skips over its old next node
```

Note that when you add the next node's size to this node's, you have to
add the next node's size PLUS the padded size of the `struct block` that
goes with it. The whole region (the `struct` and the user data) is
going to be added to the existing free node.

Algorithm:

```
let cur be the block just freed

mergeblocks(cur)
mergeblocks(cur's prev)
```

The time complexity of this approach is _O(1)_ over the number of nodes
in the list, a vast improvement over Option 1. Like with many things,
getting a jump in time complexity involves a corresponding increase in
code complexity.

### Example Output

**Example 1:**

```
void *p;

p = myalloc(10); print_data();

myfree(p); print_data();
```

Output:

```
[16,used] -> [976,free]
[1008,free]
```

**Example 2:**

```
void *p, *q;

p = myalloc(10); print_data();
q = myalloc(20); print_data();

myfree(p); print_data();
myfree(q); print_data();
```

Output:

```
[16,used] -> [976,free]
[16,used] -> [32,used] -> [928,free]
[16,free] -> [32,used] -> [928,free]
[1008,free]  
```

**Example 3:**

```
void *p, *q;

p = myalloc(10); print_data();
q = myalloc(20); print_data();

myfree(q); print_data();
myfree(p); print_data();
```

Output:

```
[16,used] -> [976,free]
[16,used] -> [32,used] -> [928,free]
[16,used] -> [976,free]
[1008,free]
```

**Example 4:**

```
void *p, *q, *r, *s;

p = myalloc(10); print_data();
q = myalloc(20); print_data();
r = myalloc(30); print_data();
s = myalloc(40); print_data();

myfree(q); print_data();
myfree(p); print_data();
myfree(s); print_data();
myfree(r); print_data();
```

Output:

```
[16,used] -> [976,free]
[16,used] -> [32,used] -> [928,free]
[16,used] -> [32,used] -> [32,used] -> [880,free]
[16,used] -> [32,used] -> [32,used] -> [48,used] -> [816,free]
[16,used] -> [32,free] -> [32,used] -> [48,used] -> [816,free]
[64,free] -> [32,used] -> [48,used] -> [816,free]
[64,free] -> [32,used] -> [880,free]
[1008,free]  
```

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **90 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

* A real allocation system would, upon finding out there wasn't enough
  memory for a user's request, call `mmap()` again to make enough free
  space, thus increasing the heap size as needed.

<!-- Rubric

15
If the next block is free, it and the newly freed block are merged

15
If the previous block is free, it and the newly freed block are merged

15
If the freed block is surrounded by free blocks, they are all merged into a single block

10
If the existing free block is at the head of the list, it is merged successfully

10
If the existing free block is at the tail of the list, it is merged successfully

10
If the newly freed block is at the head of the list, it is merged successfully

10
If the newly freed block is at the tail of the list, it is merged successfully

5
If the newly freed block has no free neighbors, nothing is merged

-->

