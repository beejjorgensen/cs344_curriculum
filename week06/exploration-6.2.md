<!-- Exploration 6.2: Segmented Virtual Memory, Fragmentation -->

## Segmented Virtualized Memory

Taking a step up from base/bound, this scheme has a different base/bound
for each _segment_ in a process, where segments are:

* Program code
* Heap
* Stack
* Maybe others

This means that every memory access needs to also include a few bits to
indicate to the CPU which segment we're talking about.

If we're going to support segment growth (which we should), it's
important to note the direction of growth. Notably, the heap grows
upward while the stack grows downward. When the OS is setting up the
virtual memory system, it could flag these directions to the CPU.

### Shared Memory

If a segment is going to be shared, the CPU also has to support some
kind of permissions on that segment. Namely whether or not the data is
executable, readable, and/or writable.

### Fine-Grained Segmentation

On some systems, instead of just using the big Code/Heap/Stack segments
in their entirety, the memory space was cut up into a pile of shorter
segments. A _segment table_ could be set up in memory that described
what segments were available to whom and for what.

### Fragmentation

The OS maps physical memory to segments, but problems can arise if a lot
of small segments are mapped in a way that doesn't allow room for larger
contiguous ones to exist. The memory is too _fragmented_.

Defragging/compacting it is problematically expensive and makes it hard
for compacted segments to grow.

There's no best solution to this.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Segmentation](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-segmentation.pdf)
  
## Reflect

* How did instructions on the VAX specify the segment?
* What advantages does the segmented memory scheme have over vanilla
  base/bound?
* What kinds of problems does fragmentation cause?
