<!-- Exploration 7.1: Memory Management -->

## Memory Management

In this exploration we'll take a look at some of the issues that came
come up with memory management both in user space (like with `malloc()`)
and in kernel space (like with virtual memory).

This chapter of the book describes a system that's similar to the
`myalloc()` you're implementing in the project. (There's no "one true
way" to implement such an allocator--there are benefits are drawbacks to
the different approaches.)

In addition, it covers the following concepts:

* **External Fragmentation**: When all the free blocks are small and you
  can't perform larger allocations, even though collectively you have
  enough free space to do so.

* **Internal Fragmentation**: When you waste allocated space inside a
  specific allocation by allocating more than was asked for, making it
  impossible to allocate that space later.

* **Splitting**: Taking part of a large free block and making it used,
  while adding a new free block to represent the remainder of the free
  space.

* **Compaction**: The act of consolidating many small, disjoint free
  regions into a single large one, regardless of their relative
  positions. The allocated and free blocks are rearranged in memory to
  create the larger block. (If you're old-school, think of how disk
  [defragging](https://en.wikipedia.org/wiki/Defragmentation) worked.)

* **Coalescing**: Consolidating neighboring free spaces without doing
  any rearrangement of blocks in memory.

* **Magic Number**: A marker that you can add to the block header to use
  as a sanity check to make sure the pointer the user passes to your
  `free()` function is a valid one. In general, a [magic
  number](https://en.wikipedia.org/wiki/Magic_number_(programming)) is a
  number that has some additional meaning beyond its purely numeric
  value.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Free Space Management](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf)
  
## Reflect

* Why can't we use compaction/fragmentation with `malloc()` to
  consolidate smaller free spaces and avoid external fragmentation?

* What would the algorithm look like for detecting a bad free with a
  magic number? How would you compute the location of the magic number
  from the pointer the user passed in?

* What is coalescing OK with a `malloc()`-like system, but compaction
  isn't?

* Why does the free list have to be "embedded", as the book puts it?
