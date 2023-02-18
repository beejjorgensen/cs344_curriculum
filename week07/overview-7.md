<!-- Overview: Memory Management, Allocation Part 2 -->

## Introduction

This week we're going to take a more in-depth look at memory management,
both from a user-space programmer standpoint and from an OS standpoint.

As a programmer, we're used to using functions like `malloc()` (and our
`myalloc()` function that we wrote) to allocate memory. We'll look at
some of the issues that can arise with that, and some strategies for
allocation.

And the OS is interested in managing virtual memory. We'll look at
_paging_, which is a modern technique for managing large amounts of
virtual memory between large numbers of processes.

## Goals

* Learn about how `malloc()` manages memory it gets from the OS.
* Learn about how the OS manages virtual memory with paging.
* Modify our allocator to split off a block of new free space after the
  user has allocated some of an existing space.
* Learn about 
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Better juggle free and used blocks in a memory allocator.
* Describe the difference between internal and external fragmentation.
* Understand the difference between compaction and coalescing.
* Describe the limitations of a `malloc()` style system.
* Show the steps required to map between a virtual address and a
  physical address using page tables.

## Explorations

* [Exploration 7.1]()
* [Exploration 7.2]()

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Free Space Management](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-freespace.pdf)
  * [Introduction to Paging](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-paging.pdf)
* Complete [Quiz 7]()
* Complete [Project 7]()

