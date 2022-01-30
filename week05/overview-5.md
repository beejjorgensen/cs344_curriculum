## Introduction

A modern OS virtualizes memory so that when a program is loaded it
thinks it has the entire memory region to itself, and that there are no
other programs running.

This virtual memory space is mapped to pages of physical memory that are
present on your motherboard.

Once a program is running, it can request additional memory from the OS
to hold data.

## Goals

* Learn how the CPU virtualizes RAM
* Understand the memory layout of a program
* Understand how C Programs allocate memory
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Allocate and free memory from a running program with the C library
* Describe the process of how the OS virtualizes memory
* Use Unix system calls to allocate more memory

## Explorations

* [Exploration 5.1](https://canvas.oregonstate.edu/courses/1849663/assignments/8774395)
* [Exploration 5.2](https://canvas.oregonstate.edu/courses/1849663/assignments/8774396)

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [12. _Dialog_](https://pages.cs.wisc.edu/~remzi/OSTEP/dialogue-vm.pdf)
  * [Address Spaces](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-intro.pdf)
  * [Memory API](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf)
* Complete [Quiz 5](https://canvas.oregonstate.edu/courses/1849663/quizzes/2758076)
* Complete [Project 5](https://canvas.oregonstate.edu/courses/1849663/assignments/8774397)
