<!-- Overview: Page Tables, Allocation Part 3 -->

## Introduction

We looked at page tables before as a way to handle virtual memory, but
it wasn't without its drawbacks. We'll look at a couple ways of
improving them:

* More speed with a _translation lookaside buffer_ (TLB)
* Less space with _multi-level page tables_

Recall that the page table holds mappings from virtual addresses to
physical addresses.

The TLB is a cache of those mappings.

Even though the page table only maps page to page, and each page is a
significant number of bytes, there are still a _lot_ of pages, maybe
millions.

And since each process has its own page table, that can add up to a lot
of space just for page tables alone.

But we can see that most processes barely use any of their virtual
memory space. They just don't need it. So if there were a good way to
just have the parts of the page table that we need, and not use memory
for the parts of the page table that correspond to unused virtual memory
space, we'd save memory.

Multi-level page tables do exactly that.

## Goals

* See how TLBs are more speed efficient
* See how multi-level page tables are more memory efficient
* Modify your memory manager to coalesce adjacent free memory regions
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Describe the benefits and drawbacks of TLBs
* Describe the benefits and drawbacks of multi-level page tables
* Write the part of the memory management system that consolidates free
  memory regions, reducing external fragmentation.
 
## Explorations

* [Exploration 8.1](https://canvas.oregonstate.edu/courses/1849663/assignments/8790498)
* [Exploration 8.2](https://canvas.oregonstate.edu/courses/1849663/assignments/8790499)

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Translation Lookaside Buffer](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf)
  * [Advanced Page Tables](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf)
* Complete [Quiz 8](https://canvas.oregonstate.edu/courses/1849663/assignments/8790501)
* Complete [Project 8](https://canvas.oregonstate.edu/courses/1849663/assignments/8790500)
