## Introduction

This week we're going to continue learning about scheduling. We'll take
a look at a real life scheduler: Linux's Completely Fair Scheduler (CFS).
see how that works. And we'll also a high level overview of how
schedulers work when multiple processors or cores are involved.

Also, we'll dig into `fork()` a little more and see some of the details
about what is and is not shared between processes.

We'll also take a look at _pipes_ in Unix, a simple interprocess
communication mechanism, and how we can write system software to take
advantage of that.

## Goals

* Understand how Linux's Completely Fair Scheduler (CFS) works
* Learn some of the issues around scheduling for multiple processors
* Learn about how variables and file descriptors are shared between
  parent and child processes
* Write software utilizing Unix pipes.
  
## Module Learning Outcomes
  
After the successful completion of this module, you will be able to:

* Describe how Linux's CFS works.
* Summarize some of the issues with multicore scheduling, including
  cache issues.
* Utilize pipes to redirect I/O between processes.

## Explorations

* [Exploration 4.1]()
* [Exploration 4.2]()

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Lottery Scheduling/Proportional Share](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf) sections 9.7-9.8
  * [Multi-CPU Scheduling](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-multi.pdf) sections 10.1-10.3
* Complete [Quiz 4]()
* Complete [Project 4]()

