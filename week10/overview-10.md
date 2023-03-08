<!-- Overview: Virtual Memory, Page Tables Part 2 -->

## Introduction

This week we look at a couple real-life virtual memory systems to see
how this works in actual implementation.

We'e also going to be adding our to our paged virtual memory simulator.
After this implementation, it will have the ability to kill processes
(freeing their memory) and the ability to read and write virtual
addresses for various processes.

## Goals

* Learn about real-life virtual memory systems, including Linux.
* Learn about some of the pitfalls and workarounds on those systems.
* Learn about copy-on-write.
* Learn about page caches.
* Implement virtual memory addressing and process killing on your
  simulator.
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Describe how virtual memory works under VMS and Linux
* Describe some security isses with virtual memory and their
  mitigations.
* Describe how copy-on-write functions and how it is beneficial.
* Map a virtual address to a physical address in a paged virtual memory
  system.
 
## Explorations

* [Exploration 10.1]()
* [Exploration 10.2]()

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Complete VM Systems § 23.1](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-complete.pdf)
  * [Complete VM Systems § 23.2-23.3](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-complete.pdf)
* Complete [Quiz 10]()
* Complete [Project 10]()

