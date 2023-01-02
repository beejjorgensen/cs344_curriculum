## Introduction

This week we're going to take a closer look at memory virtualization,
the way processes think they have the system memory to themselves and
don't overwrite the data for other processes.

We'll check out a few potential methods for implementation:

* Base/bound
* Coarse-grained Segmentation
* Fine-grained Segmentation

We'll also look at how C library memory management routines such as
`malloc()` work.

## Goals

* Investigate techniques for supporting virtual memory on the CPU.
* Explore how the OS can use these techniques to make it look to the
  process like it has a large, contiguous chunk of memory.
* Use the `mmap()` syscall to get some memory allocated from the OS.
* Implement part of a `malloc()` replacement.
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Describe how `malloc()` gets memory from the OS
* Implement a partial linked-list version of a `malloc()`-style
  allocator
* Describe different forms of memory virtualization and their relative
  strengths and weaknesses

## Explorations

* [Exploration 6.1](https://canvas.oregonstate.edu/courses/1849663/assignments/8782818)
* [Exploration 6.2](https://canvas.oregonstate.edu/courses/1849663/assignments/8782819)

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Address Translation](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-mechanism.pdf)
  * [Segmentation](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-segmentation.pdf)
* Complete [Quiz 6](https://canvas.oregonstate.edu/courses/1849663/assignments/8782816)
* Complete [Project 6](https://canvas.oregonstate.edu/courses/1849663/assignments/8781483)
