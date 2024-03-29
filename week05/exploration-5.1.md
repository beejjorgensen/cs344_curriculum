<!-- Exploration 5.1 Memory Virtualization, Stack and Heap -->

<!-- This page has images that must be linked -->

## Memory Virtualization and Address Spaces

As you learned in Architecture, memory is like a big "array" of bytes
that is numbered by _address_ (where the address is the index into that
big array).

But we also need to consider a couple types of memory:

* _Physical Memory_: the memory chips/sticks/cards hardware that you buy
* _Virtual Memory_: the memory a process thinks it has

On 64-bit machines, the virtual address space is _vast_. There are
18,446,744,073,709,551,616 addresses. This is the world that every
process sees from its perspective.

But if you have 8 GB physical memory, that's only 8,589,934,592
addresses.

The magic of _virtual memory_ is that the kernel juggles _pages_ (small
chunks) of physical RAM and maps them into the gigantic virtual spaces
of the various processes on an as-needed basis.

![Virtual Memory]()

(Image from Wikipedia.)

This is transparent to the processes themselves; as far they're
concerned, their entire world is the virtual memory space that is
presented to them by the kernel.

And that's is how memory is virtualized by the OS.

## The Stack and the Heap

Allocated memory for a given process is broadly partitioned into two
types:

* Stack
* Heap

These are typically positioned at opposite ends of memory, with the heap
growing upward toward the stack, and the stack growing downward toward
the heap.

If they meet, it's [drum roll] _stack overflow_.

But in modern systems, they never meet because of the virtualized memory
space. The stack and heap are so far apart that you don't have enough
physical RAM to fill the distance between them.

## Memory Allocation in C

It's important to know that C is limited when it comes to automatic
memory management.

Here's what it can do automatically:

* If you declare a local variable to a block (e.g. in a function body),
  that variable is freed when the block ends.

That's it.

> In fact, variables of this type are called _automatic variables_ in
> the C documentation.

These types of data are stored on the stack.

Anything else you want to allocate must be allocated, managed, and
freed explicitly by the programmer.

And those types of data are stored on the heap.

There's no built-in automatic reference counting or garbage collection.

If you allocate some memory and don't free it, that's a _memory leak_
and that memory will be unavailable to any programs on the system.

> When a program exits, all memory it has allocated is freed, so it's
> not like the leak is permanent. But if the the program runs for a long
> time (hours, days, months, years), the leaks can add up and use all
> memory.

The C standard library includes a number of functions for memory
allocation and freeing.

The big ones are:

* `malloc()` -- allocate a certain number of bytes of memory
* `free()` -- free previously-allocated memory

Some lesser-used ones are:

* `realloc()` -- resize a previously-allocated memory region
* `calloc()` -- allocate a certain number of bytes and set them all to
  zero
* `aligned_alloc()` -- allocate memory
  [aligned](https://en.wikipedia.org/wiki/Data_structure_alignment)
  aligned a certain way

The memory allocation functions return pointers to the new memory.

`malloc()` is commonly used with `sizeof`, since `sizeof` gives you the
size in bytes of a particular type of data.

Example: allocating 12 integers:

``` c
int *a;

// Allocate 12 ints
a = malloc(12 * sizeof(int));

// Same thing, since the type of `*a` is `int`
a = malloc(12 * sizeof *a);
```

After that, `a` is effectively an array of 12 `int`s.

Example of allocating space for a structure:

``` c
struct node {
    int data;
    struct node *next;
};

struct node *n;

n = malloc(sizeof(struct node));
//n = malloc(sizeof *n);  // Or this
```

Note that using data after it has been `free()`d is undefined behavior.
Insidiously, it might seem to work fine, but then crash when you're
giving a demo.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [12. _Dialog_](https://pages.cs.wisc.edu/~remzi/OSTEP/dialogue-vm.pdf)
  * [Address Spaces](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf)
  
## Reflect

* What's the difference between physical and virtual memory?
* Will you always have more virtual memory than physical memory? Or will
  it be the other way around?
* What's the difference between the stack and the heap? What is stored
  in each?
* What's an automatic variable in C? Do they go on the stack or heap?
* What kind of data goes on the heap?
