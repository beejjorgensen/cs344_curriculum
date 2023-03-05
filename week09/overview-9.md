<!-- Overview: Swapping, Page Tables Part 1 -->

## Introduction

This week we're going to look at _swapping_, which is when the OS runs
out of physical RAM and has to move some pages of memory out to disk to
handle that.

We'll look at some of the techniques and policies that are commonly used
when doing so.

We're also going to implement a simulation of a paged memory management
system. This will be similar in nature to what the OS does under the
hood, but simplified for easier implementation and demonstration.

## Goals

* Understand how swapping works.
* Know what policies can be used to implement swapping.
* Learn what can go wrong with swapping.
* Get a better understanding of how a paged memory manager works under
  the hood.
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Implement a simple simulation of a paged virtual memory manager.
* Describe what swapping is and how it works on modern operating
  systems.
* Describe the relative strengths and weaknesses of various swapping
  policies.
 
## Explorations

* [Exploration 9.1]()
* [Exploration 9.2]()

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Swapping Mechanisms](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys.pdf)
  * [Swapping Policies](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys-policy.pdf)
* Complete [Quiz 9]()
* Complete [Project 9]()
