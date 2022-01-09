## Introduction

This week we're going to take a closer look at how the OS virtualizes
and abstracts processes.

## Goals

* Understand how the OS seemingly runs many programs at the same time.
* Write some new utilities in C using syscalls to get used to the language.
* Have more fun!

## Module Learning Outcomes

After the successful completion of this module, you will be able to:

* Make syscalls in C and have your programs work with pipes on the command line.
* Know what file descriptors are and how to read and write from them.
* Summarize what the process abstraction encompasses and the data structures involved.
* List the functions of a process API and know the Unix syscall equivalents.
* Describe Limited Direct Execution and how the OS transfers control to
  other programs.

## Explorations

* [Exploration 2.1](https://canvas.oregonstate.edu/courses/1849663/pages/exploration-2-dot-1-processes-and-system-programming)
* [Exploration 2.2](https://canvas.oregonstate.edu/courses/1849663/pages/exploration-2-dot-2-unix-process-api)

## Task List

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [_Dialogue_](https://pages.cs.wisc.edu/~remzi/OSTEP/dialogue-virtualization.pdf)
  * [_Processess_](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf)
  * [_Process API_](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf) (just skim except for page 11, "Aside: Key Process API Terms"--you can come back and reference this chapter when we use it later)
  * [Direct Execution](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-mechanisms.pdf)
* Complete [Quiz 2](https://canvas.oregonstate.edu/courses/1849663/quizzes/2749195)
* Complete [Project 2](https://canvas.oregonstate.edu/courses/1849663/assignments/8732086)