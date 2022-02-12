<!--
Week 1
Allocate the first part
Alignment

Week 2
Split nodes
Free node

Week 3
Consolidate nodes
Handle free from command line
-->
<!-- Project 6: Memory Allocation Part 1 -->
## Introduction

**This is a multi part project, each part taking one week. This is part
1.**

**Hint: before you type a line of code, you should understand this
problem well enough to teach it to someone to the degree they could work
an example with pen and paper. It will be _much_ harder to implement if
you do not understand it well enough.** This advice is always true, but
I want to really drive it home for this project where it is especially
true.

We're going to write a `malloc()`/`free()` implementation from scratch!

**You may NOT use `malloc()` or any of its relatives (e.g. `calloc()`),
`free()`, or `mmap()` for this project. Solutions that use these
functions will not be accepted.**

When you request more data segment space from the OS with `sbrk()`, it
increases the size of the continuous chunk of memory used for the heap,
the part that's right after the program code.

There are no holes in this memory--it's one big piece.

What `malloc()` does is to micromanage this big space, making it look to
a process like it's split into a bunch of little ones.

## What to Do

We're going to write an allocator with the following function:

* `myalloc()` -- allocate a certain number of bytes, and return a
  pointer to it.

We'll do our `myfree()` code later.

Remember--no using the built-in `malloc()` for this! We're writing it!

This is the overview for `myalloc()` for this week. Note that this is an
incomplete implementation, but we'll be working more on it in the
following weeks.

* If this is the first call, `sbrk()` to get some space.
  * At the same time, build a linked-list node inside the new space
    indicating its size and "in-use" status.
* Walk the linked list in a loop and look for the first node that is:
  * Not in-use
  * Big enough to hold the requested amount (plus padding)
* If the block is found:
  * Mark it in-use.
  * Return a pointer to the user data just after the linked list node
    (plus padding)).
* If no such block is found:
  * Return `NULL`

Details on these steps follow.

### Usage

The user of your code is going to write something like this:

```
int *p = myalloc(sizeof(int) * 5);  // Allocate space for 5 ints
```

We need it implement it.

### What We're Allocating

We'll use `sbrk()` to allocate a chunk of data space ahead of time.
Think of this as a big array of bytes. We're going to drop various data
structures in there in specific places.

> Note on `sbrk()`: this function is deprecated on OS X. It'll still
> work, though. Feel free to turn off the warning by adding this option
> to your `Makefile` or command line:
>
> ```
> -Wno-deprecated-declarations
> ```
>
> We suppose allocators under OS X would do something more complicated,
> possibly with `mmap()`, to get around this issue. But we'll just use
> `sbrk()`.

What we'll do is make a linked-list of nodes _inside_ this data space,
and those list nodes will share the space with the allocated space they
represent. (Remember: you can't call `malloc()`!)

Each node will have three pieces of information:

* Whether or not this memory region is in-use.
* The size of the allocated memory region.
* A pointer to the next memory region.

It's a little weird because the nodes in this linked list will be
separated in memory by the chunks of data they represent.

We're going to juggle that by hand, as we'll see.

### Initial Allocation

On the very first call to `myalloc()`, we won't have any heap space.
Allocate 1024 bytes of heap with:

```
void *heap = sbrk(1024);
```

We're going to use part of this space to hold the head of our linked
list.

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

It stores the number of bytes that the block is, whether or not it's in
use, and a pointer to the next block.

We're going to partition the big chunk of bytes we got back from
`sbrk()` into several sections. Each section will consist of a header
(which is the `struct block`), followed by some amount of empty space.
Repeating.

Each header is a linked list node that will point to the next
header/data section.

So we'll have a list of blocks, some in use and some not (numbers are
the number of bytes of each data area, free or in-use):

<!-- freelist.svg 640px wide -->
![Overall Architecture](https://canvas.oregonstate.edu/courses/1849663/files/91896069/preview)

Notice how the data is interspersed between the block metadata. Note
that this is one contiguous region of memory we're looking at (that we
got from `sbrk()`); we've just partitioned it up by putting `struct
block` data in the proper locations.

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

There's some math there to figure out the size of the free data. Some of
it gets used up by the `struct block` metadata. The amount used is the
padded size of that `struct`.

More on padding when we talk about alignment, below.

It's weird, though, that we asked for 1024 bytes and just used it as a
`struct block`, which is way smaller than that, right?

Well, the OS doesn't care if you under-use the space. Only if you
overuse it. If the memory weren't aligned, maybe using it as the
`struct` might cause trouble, but it's aligned, so no problem.

But this was just the one-off initialization. We still have to set up
the block the user asked for.

> In a _real_ implementation, `sbrk()` would be called as needed, not
> just one time. If the first block of heap got used up, `malloc()`
> would call `sbrk()` again to grow it. But we're trying to keep things
> simple here.

### Allocating a Block

This is going to be a three-phase process.

1. Find a free block that's big enough for what the caller requested.
2. Mark it as used.
3. [Next week: possibly split the block into a new unused portion.]

We're going to just do (1) and (2) this week. (3) will come later.
Though this will limit our implementation this week, we'll code it in
such a way that it'll be ready for the next steps later.

We're going to use a strategy called "first-fit" to find a block to use.
That is, we'll walk the linked list and the first unused block we find
that is big enough, we'll use that.

Algorithm:

```
Walk the list looking for a free node
    let n = the free node
    If n's data big enough for user request

        Mark n as used

        Return address of n's data

If we get here, there was no room
return NULL
```

In our case, I promise the user will ask for a small amount of data,
like 60 bytes or so, so we can be assured it'll fit in the 1024-bytes
that we allocated with `sbrk()`.

So after the user does that, we'll have something that looks like this:

<!-- afteralloc.svg 480px wide -->
![Data Allocated](https://canvas.oregonstate.edu/courses/1849663/files/91896378/preview)

Why is the data size only 1008 bytes when we grabbed 1024 bytes with
`sbrk()`? It's because in this example, 16 bytes are used up by the
`struct block` at the front.

> Now you're probably thinking, what good is this? We just allocated the
> entire space for one block of 60 bytes. If we call `myalloc()` again,
> it will fail because there's no free space left.
>
> That's going to be dealt with later when we add another node to our
> linked list to represent the remainder of the free space. _Then_ we'll
> be able to `myalloc()` repeatedly. But this week, we're just getting
> to this point.

But of course it's not this straightforward. We have to deal with
alignment.

### Alignment

This is a substantial wrench in the works. We want every allocation to
begin on an address that is evenly divisible by 16.

> This is called _alignment_ and has to do with how the CPU accesses
> data. The x86 is pretty happy to work with data that starts on any
> address, albeit a little slower if it's not correctly aligned. Other
> CPUs might crash on misaligned data accesses.

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
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
```

As an example:

```
printf("%d\n", PADDED_SIZE(15));  // Prints 16
printf("%d\n", PADDED_SIZE(16));  // Prints 16

printf("%d\n", PADDED_SIZE(17));  // Prints 32
printf("%d\n", PADDED_SIZE(18));  // Prints 32
printf("%d\n", PADDED_SIZE(32));  // Prints 32

printf("%d\n", PADDED_SIZE(33));  // Prints 48
printf("%d\n", PADDED_SIZE(37));  // Prints 48
```

In short:

```
actual_size = PADDED_SIZE(user_requested_size)
```

And when storing the size of the data in your `struct block`, it makes
things easier to store the size of the padded data, not the size
requested by the user. Really, `myalloc()` will be promising that "we'll
give you at _least_ as many bytes as you asked for".

### Alignment II: Revenge of Alignment

And that's not all! We have to make sure our `struct block` linked list
node is also padded to the alignment.

On my system, the `struct` was exactly 16 bytes already so I needed zero
bytes of padding, but that was just luck. On another system it might be
more or less.

So we need to make sure it's padded out, too.

Basically, we'll have something like this for each region in memory:

<!-- header.svg 480px wide -->
![Full Padding](https://canvas.oregonstate.edu/courses/1849663/files/91896375/preview)

where the padding is between 0 and 15 bytes--just enough to make the
region a multiple of 16 bytes.

```
padded_struct_block_size = PADDED_SIZE(sizeof(struct block));
```

The padding in both cases ensures that both the `struct` and the data
will be on an alignment boundary, and that the entire glob of data is
also going to be so-aligned. Alignment all around.

### What We're Returning

`myalloc()` will return a pointer to the data, not a pointer to the
`struct block`. We know where the data starts, though: `n` bytes past
the `struct`, where `n` is `PADDED_SIZE(sizeof(struct block))`.

How do we compute that? Read on...

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

So in `myalloc()`, when we return the data to the user, we'll have code
like this:

```
struct block *cur;

// ... All the machinations to allocate go here ...

padded_block_size = PADDED_SIZE(sizeof(struct block));

return PTR_OFFSET(cur, padded_block_size);
```

### Printing the List

Printing the list of blocks should be accomplished with this code. It
assumes `head` is the name of the start of the list, and is global.

You should copy this into your code. If your `head` isn't global, just
add it as a parameter.

```
void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}
```

## Example Run

If you have this in `main()`:

```
void *p;

print_data();
p = myalloc(64);
print_data();
```

We'd expect the output (assuming your padding `struct block` size is 16 bytes):

```
[empty]
[1008,used]
```

Even though the user only asked for 64 bytes, we looked for the first
available block that was at least that big, marked it in use, and
returned the data to them.

We'll fix that next week.

If you have this in your `main()`:

```
    void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
```

This should be your output:

```
[empty]
[1008,used]
0x0
```

The second `myalloc()` returned `NULL` because all the space was given
to the first allocation and there is none left over.

As noted, we'll fix that next week.

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **95 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

If you want to get a jump on it, next week we're going to introduce
splitting, where we split a free space into a newly used space and the
remainder of the free space.

That is, if you have a free block with 1008 bytes in it, and you
`myalloc()` 32 bytes, you should end up with two entries in your linked
list. One of them is the newly allocated block, and the other is the
unused remainder of the previous free space.

In this example, assuming the `struct block` linked list node is 16
bytes, we'd go from:

* Block 1, size: 1008, in-use: false

to:

* Block 1, size: 32, in-use: true
* Block 2, size: 960, in-use: false

After that works, you can call `myalloc()` repeatedly until the space
fills up.

Of course, we should only split the block this way if the remaining
space was at least big enough for the a new `struct block` plus at least
16 bytes of usable space, besides.

<!-- Rubric

Linked list nodes padded to proper alignment (15)

Data padded to proper alignment (15)

First call to `myalloc()` calls `sbrk()` to allocate space (10)

`myalloc()` returns `NULL` if no more space is available. (10)

All calls to `myalloc()` traverse the linked list searching for a free node with enough space to hold the requested amount. (Even though at this point, there is just one node, there should still be a loop that is capable of traversing 1 or more nodes in this search. (15)

`struct block` `size` field computed correctly (size is padded to 16 byte alignment, doesn't count the `struct block` size itself) (10)

Blocks' in-use flags set correctly.  (10)

Print list prints `[empty]` when list empty (5)

Print list prints the list properly when not empty (5)

-->
