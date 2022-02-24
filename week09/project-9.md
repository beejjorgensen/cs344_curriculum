<!-- Project 9: TODO -->

## Introduction

**This is part 1 of a multipart project.**

We're going to simulate a page table on a simple computer.

Recall that the page table is effectively a big array that you use to
map virtual page numbers to physical page numbers.

This simulation will allow us to start new (fake) processes that need a
certain number of pages of physical memory, store and load data from
virtual addresses per process, and so on.

### The Fake Computer

This is a machine with 14-bit addressing, supporting physical addresses
from 0-16385 (16 KB), and per process virtual addresses in the same
range.

We're going to simulate this physical memory with a big global array of
`unsigned char`s:

```
#define MEM_SIZE 16384

unsigned char mem[MEM_SIZE];
```

(In C, a `unsigned char` type is just a byte--on your system, it's
certainly 8-bits. It can hold charaters, or small numbers between 0 and 255.
In this case, we'll use them to hold small numbers.

The memory is logically split up into 64 pages of 256 bytes each.  (`64
x 256 = 16384`, the total memory size.)

Page 0 goes from addresses 0 to 255.

Page 1 goes from addresses 256 to 511, and so on.

### Addressing

Confusingly, there are two ways to refer to the same address:

1. The address number from 0-16383.
2. The page number and the offset within that page.

Remember that we've logically split the 16384-byte area up into 64
contiguous pages of 256 bytes each. So if I give you a page number and
an offset within that page, you should be able to compute the address:

```
address = page_num * 256 + offset;
```

So page 3, offset 12 is:

```
#define PAGE_SIZE 256

address = 3 * PAGE_SIZE + 12 = 780
```

In our fake computer, we can write physical memory with an address
directly like this:

```
mem[addr] = 12;
```

or with a page and offset like this:

```
mem[page * PAGE_SIZE + offset] = 12;
```

### Zero Page

This is the zeroth page of physical memory, from address 0-255. It has
special uses in this fake computer.

Bytes 0-63 (effectively addresses 0-63) form a free page map (which lets
you know which pages are in use and which aren't).

Bytes 64-127 hold page table pointers for up to 64 processes.

Process 0's page table page number is at address 64.

Process 1's page table page number is at address 65, and so on.

The page table page number is the number of the page in physical memory
that holds the page table for the given process.

You might need to reread that sentence a number of times to get it.

### Per Process Page Table

Each process has its own page table. Confusingly, each page table also
resides in memory, and each one takes a single page.

So we have zero page, which is reserved for the system stuff, above. And
then each process also has a page table allocated from the pool of free
physical pages.

The page table entry for the given process points to the page that holds
the its page table.

### Process Page Allocation Examples

If we started a `Process 1` that needed two pages of data, we'd have the
following physical memory layout:

```
Page 0: Zero Page, reserved
Page 1: Process 1's page table
Page 2: Process 1's data page 0
Page 3: Process 1's data page 1
Page 4: Unused
Page 5: Unused
Page 6: Unused
Page 7: ... and so on ...
```

If we then started another `Process 2` that needed just one page of
data, we'd then have:

```
Page 0: Zero Page, reserved
Page 1: Process 1's page table
Page 2: Process 1's data page 0
Page 3: Process 1's data page 1
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Unused
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

If we then killed `Process 1`, all its physical pages would be freed:

```
Page 0: Zero Page, reserved
Page 1: Unused
Page 2: Unused
Page 3: Unused
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Unused
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

and those blocks become available for reuse.

So let's start a new `Process 3` that needs three pages of memory. We'd
see this happen:

```
Page 0: Zero Page, reserved
Page 1: Process 3's page table
Page 2: Process 3's data page 0
Page 3: Process 3's data page 1
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Process 3's data page 2
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

See how `Process 3`'s pages are disjoint and spread out over `Process
2`s?

This is not a problem, because the page tables tell you how to map from
a process's continuous virtual pages to the system's physical pages,
even if those physical pages are scattered about.

### Example Output

TODO

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **TODO points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

* TODO

<!-- Rubric

TODO

-->
