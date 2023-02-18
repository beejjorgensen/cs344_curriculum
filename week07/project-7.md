<!-- Project 6: Memory Allocation Part 2 -->

## Introduction

**This is a multi part project, each part taking one week. This is part
2.**

This week we're going to modify our `myalloc()` call to split a large
existing space into a new allocated space and a new free space.

That is, if there's a block of free space that looks like this:

![Before split]()

and the user calls

```
void *p = myalloc(117);
```

we should end up with space that looks like this:

![After split]()

In addition, we'll implement the first version of `myfree()`.

## What to Do

### Splitting Blocks

This will be added as part of the previous "find space" algorithm
implemented last week:

```
Find_Space(bytes):

    bytes = bytes + GET_PADDING(bytes)

    walk the linked list looking for a space at least "bytes" big

        if current space big enough:

            # vvv splitting code vvv

            if the space is big enough to split:
                Split_Space(current, size) into current and new

            # ^^^ splitting code ^^^

            Mark current space in use
            Return pointer to current space
        
    return NULL since we're out of memory
```

The `Split_Space` algorithm looks like this:

```
Split_Space(current_node, requested_size):
    If current_node big enough to split:
        Add a new struct block with the remaining unused space
        Wire it into the linked list
```

How do we know if the current node is big enough to split?

Well, we know its size, and we know after a split we want to be able to
hold three things in it:

1. The data space requested by the user
2. A new `struct block` (padded)
3. The remaining space referred to by the new `struct block` (padded)

If the user is requesting all or virtually all of the space, there won't
be enough room left for the new block or data, so there's no point to
splitting the block up.

So we can make the decision of whether or not we split like so:

```
required_space = padded_requested_space +
                 padded_struct_block_size +
                 16
                 
if available_space >= required_space:
    do the split
```

The minimum free space in the new block we've specified as 16 bytes,
above, since any smaller amount would have to be padded to 16 bytes.

Remember that all `struct block`s need to be padded to multiples of 16
bytes, as do all data regions.

### Freeing a Node

In order to free a node, the user will pass the pointer they got from
`myalloc()` into `myfree()`, and your code will mark that block as
unused.

```
void *p = myalloc(10);

myfree(p);
```

You can assume that the user will only pass in pointers that they got
from `myalloc()`.

> This is how the standard C library works with `malloc()` and `free()`,
> as well. If you pass a pointer to `free()` other than one you got from
> `malloc()`, the behavior is undefined.

In this initial pass of the algorithm, you just need to mark the block
as not `in_use` in the corresponding `struct node`.

You can compute the location of the `struct node` from the pointer the
user passes to `myfree()` with pointer subtraction.

### Sample Runs

**Example 1**: if `main()` has this:

```
    void *p;

    p = myalloc(512);
    print_data();

    myfree(p);
    print_data();
```

The output should be:

```
[512,used] -> [480,free]
[512,free] -> [480,free]
```

(Next week we'll add code to merge those free regions.)

**Example 2**:

```
    myalloc(10); print_data();
    myalloc(20); print_data();
    myalloc(30); print_data();
    myalloc(40); print_data();
    myalloc(50); print_data();
```

Output:

```
[16,used] -> [976,free]
[16,used] -> [32,used] -> [928,free]
[16,used] -> [32,used] -> [32,used] -> [880,free]
[16,used] -> [32,used] -> [32,used] -> [48,used] -> [816,free]
[16,used] -> [32,used] -> [32,used] -> [48,used] -> [64,used] -> [736,free]
```

**Example 3**:

```
    void *p;

    myalloc(10);     print_data();
    p = myalloc(20); print_data();
    myalloc(30);     print_data();
    myfree(p);       print_data();
    myalloc(40);     print_data();
    myalloc(10);     print_data();
```

Output:

```
[16,used] -> [976,free]
[16,used] -> [32,used] -> [928,free]
[16,used] -> [32,used] -> [32,used] -> [880,free]
[16,used] -> [32,free] -> [32,used] -> [880,free]
[16,used] -> [32,free] -> [32,used] -> [48,used] -> [816,free]
[16,used] -> [32,used] -> [32,used] -> [48,used] -> [816,free]
```

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **95 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

* Next week, we want to merge neighboring free blocks so that we don't
  end up with excessive fragmentation. There are two approaches we could
  use for this:

  * Make a pass through the singly-linked list after `myfree()` marks
    the block as not `in_use`, merging free areas as you go.

  * Convert to a doubly-linked list and then try to merge with the
    previous and next areas to the recently free'd block.

<!-- Rubric

15
Split only splits if there's the proper amount of room

15
Split creates the new free node

10
Split's new node is hooked into the linked list properly

10
Split's new node has the right size

5
Split's new node is marked not in use

15
Free computes (or locates) the proper struct block location

5
Free marks the block as free

10
When allocating, the first block that fits is used

10
When allocating, if no blocks are available, `myalloc()` returns NULL

-->
