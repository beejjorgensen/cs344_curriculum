<!-- Exploration 1.1: OS and Virtualization -->

## The Operating System

The Operating System (OS) is a collection of software that solves a
number of problems:

* How do users interact with the system?
* How do many programs simultaneously access shared resources?
* How are users and programs restricted to access only the resources
  they are allowed to?

When people refer to the OS, they can be talking about a number of
things.

* The
  [kernel](https://en.wikipedia.org/wiki/Kernel_(operating_system))--the
  core of the OS
* The user interface, whether text based or GUI
* The supporting programs and utilities

## The Kernel

The kernel runs the show deep down, working at:

* Managing Physical Hardware Resources
  * Disks
  * Network interfaces
  * Graphics cards
* Managing Logical Resources
  * Files
  * Users
  * Permissions
  * Processes
* Providing an API to access these resources. These functions are known
  as _system calls_, sometimes shortened to "syscalls".

## The UI

The user interface(s) are how users interact with the OS in every day
usage.

* We're used to GUIs, whether it's Windows, OS X, or the X Window System
* But as developers we're also used to "terminal" windows where we run
  commands through the shell
* These user interfaces ask the kernel to do work on their behalf

## Utility Programs

Operating Systems also tend to be bundled with a variety of utilities to
get work done.

* In a Unix-like OS, these would be things like `ls`, `grep`, `sort`,
  `cat`, etc.
* These also ask the kernel to do work on their behalf

## Virtualization

You know how you can run multiple programs at once on your computer? And
they all use your memory and disks and graphics cards, and mice, and
keyboards, and network, and everything?

How is this possible without everything going haywire?

Two big mechanisms:

* The kernel manages it all.
* Each program thinks it has the machine to itself.

That second bullet is the magic. Each program can use the disks, network
interfaces, graphics cards, and other hardware as if they were the only
thing on the system. Not only that, but each program thinks it has all
of the RAM to use for itself! The only requirement is they use system
calls to ask the OS to do what they need.

That's virtualization: the OS takes shared resources and presents them,
through the syscall interface, as virtual resources for any program to
use.

Note that it's not quite the same as a virtual machine where you run a
different OS on top of another--just similar terminology.

## Reading

* In the Intro section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [_Dialogue_](https://pages.cs.wisc.edu/~remzi/OSTEP/dialogue-threeeasy.pdf)
  * [_Intro_](https://pages.cs.wisc.edu/~remzi/OSTEP/intro.pdf)

## Reflect

* What is the kernel?
* How is it different than the UI and utility programs?
* What are the main functions of the kernel?
* What is virtualization?
* How would life be different without virtualization?