<!-- Project 6: Memory Allocation Part 1 -->

## Introduction

**This is a two part project, each part taking one week. This is part 1.**

We're going to write a `malloc()`/`free()` implementation from scratch!

**You may NOT use `malloc()` or any of its relatives, `free()`, or
`mmap()` for this project.**

When you request more data segment space from the OS with `sbrk()`, it
increases the size of the continuous chunk of memory used for the heap,
the part that's right after the program code.

There are no holes in this memory--it's one big piece.

What `malloc()` does is to micromanage this big space, making it look to
a process like it's split into a bunch of little ones.

## What to Do

We're going to write an allocator with the following function:

* `mymalloc()` -- allocate a certain number of bytes, and return a
  pointer to it.

We'll do our `myfree()` code next week.

Remember--no using the built-in `malloc()` for this! We're writing it!

### What We're Allocating

We'll use `sbrk()` to allocate a chunk of data space ahead of time.
Think of this as a big array of bytes. We're going to drop various data
structures in there in specific places.

What we'll do is make a linked-list of nodes. Each node will have three
pieces of information:

* Whether or not this memory region is in-use.
* The size of the allocated memory region.
* A pointer to the next memory region.

It's a little weird because the nodes in this linked list will be
separated in memory by the chunks of data they represent.

We're going to juggle that by hand, as we'll see.

### Initial Allocation

On the very first call to `mymalloc()`, we won't have any heap space.
Allocate 1024 bytes of heap with:

```
void *heap = sbrk(1024);
```

### Linked List Nodes

The node representing the metadata for a particular user allocation
looks like this:

```
struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
}
```

It stores the number of bytes bit the block is, whether or not it's in
use, and a pointer to the next block.

So we'll have a list of blocks, some in use and some not:

```
TODO diagram
|11 used|Data      |31 Free|         |20 Used|Data           |
       ------------>       ---------->       --||
```

Notice how the data is interspersed between the block metadata. Note
that this is one contiguous region of memory we're looking at (that we
got from `sbrk()`); we've just partitioned it up by putting `struct
block` data in the proper locations.

### Alignment

This is a substantial wrench in the works. We want every allocation to
begin on an address that is evenly divisible by 16.

> This is called _alignment_ and has to do with how the CPU accesses
> data. The x86 is pretty happy to work with data that starts on any
> address, albeit a little slower if it's not correctly aligned. Other
> CPUs might crash.

We can safely assume that `sbrk()` gives us back an address that meets
that requirement. So that's good.

But if someone asks for 37 bytes, that's going to throw us out of
alignment.

What we do, then, is round the size up to the next multiple of 16. They
asked for 37 bytes, but we're going to give them 48. We'll just not tell
them.

We call this extra space _padding_.

Here are some macros to help compute the padding required for any
particular number of bytes for a given alignment:

```
#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (x - 1) & (ALIGNMENT - 1))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
```

As an example:

```
printf("%d\n", PADDED_SIZE(15));  // Prints 16
printf("%d\n", PADDED_SIZE(16));  // Prints 16
printf("%d\n", PADDED_SIZE(17));  // Prints 32
printf("%d\n", PADDED_SIZE(37));  // Prints 48
```

In short:

```
actual_size = PADDED_SIZE(user_requested_size)
```

And when storing the size of the data in your `struct block`, it makes
things easier to store the size of the padded data, not the size
requested by the user.

```
TODO: diagram
|struct size|data|padding|
```

### Alignment II: Revenge of Alignment

And that's not all! We have to make sure our `struct block` linked list
node is also padded to the alignment.

On my system, the `struct` was exactly 16 bytes already so I needed zero
bytes of padding, but that was just luck. On another system it might be
more or less.

So we need to make sure it's padded out, too.

Basically, we'll have something like this for each region in memory:

```
TODO: diagram
|struct|padding|data|padding|
```

The padding in both cases ensures that both the `struct` and the data
will be on an alignment boundary, and that the entire glob of data is
also going to be so-aligned. Alignment all around.

### In The Beginning

Let's get some space for the list and see how we might use it.

```
struct block *head = NULL;  // Head of the list, empty
```

```
// in my_malloc()

if (head == NULL) {
    head = sbrk(1024);
    head->next = NULL;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
}
```

So if this is the first allocation, and the head of our list is `NULL`,
let's `sbrk()` to get some memory from the OS to use. And we know that's
going to be the only block in the list, and it's going to be marked
"free".

```
TODO diagram
|head|pad|      |
```

There's some math there to figure out the size of the free data. Some of
it gets used up by the `struct block` metadata. The amount used is the
padded size of that `struct`.

(We know that the size is still a multiple of 16 because the padded
`struct` is a multiple of 16 and 1024 is also a multiple of 16.)

It's weird, though, that we asked for 1024 bytes and just used it as a
`struct block`, which is way smaller than that, right?

Well, the OS doesn't care if you under-use the space. Only if you
overuse it. If the memory weren't aligned, maybe using it as the
`struct` might cause trouble, but it's aligned, so no problem.

### Allocating a Block

This is going to be a three-phase process.

1. Find a free block that's big enough for what the caller requested.
2. Mark it as used.
3. Possibly split the block into a new unused portion.

We're going to use a strategy called "first-fit". That is, we'll walk
the linked list and the first unused block we find that is big enough,
we'll use that.

Now, you might think it's good enough to mark it as used and return a
pointer to the user data. But what if the block is 1008 bytes big, and
you only need 48 bytes of it? We don't want to waste the rest.

So we _split_ it and add a new node into the list.

Before allocating 48 bytes:

```
TODO Diagram
|1008 free|               |
```

After allocating 48 bytes and a split:

```
TODO Diagram
|48 used|      |928 free|              |
```

Algorithm:

```
Walk the head looking for a free node
    If free node big enough
        If free node big enough to split
            Compute size and address of new node
            new node next -> free node next
            free node next -> new node
            Mark new node unused
            
        Mark free node as used

        Compute address of previously free node data
        Return that address

If we get here, there was no room
return NULL
```

How do we know if the free node is big enough to split?

Well, the free node used to consist of two chunks of data:

* `struct block`
* the free data bytes past it

We know we're still going to have the `struct block` there


### Adding Pointers

If you add a value to a pointer like this:

```
int x = 12;
int *a = &x;

a++;
```

The pointer will actually move 4 bytes up in memory, not just 1. This is
because it was an `int` pointer, and `int`s are 4 bytes (probably).
`a++` gets you to the next `int`, which is 4 bytes up.

But what if you just want to move ahead a fixed number of bytes, not a
fixed number of `int`s?

Here's a macro that can do that.

```
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))
```

> This macro simply casts the pointer to a `char*` so that every
> addition jumps `sizeof(char)` bytes ahead--and `sizeof(char)` is
> always `1`.

Example:

```
int x = 12;
int *a = &x;

int *b = PTR_OFFSET(a, 16);

// b now points 16 bytes ahead of a
```

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **TODO points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

<!-- Rubric
-->