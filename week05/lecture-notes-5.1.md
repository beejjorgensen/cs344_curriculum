# Lecture Notes 5.1

## Today

* Review
* Virtual memory
* Process memory space
* Memory allocation using the C library
* Stack Frames

## Review Story So Far

Halfway through!

* OS kernel responsible for managing resources
  * Hardware access
  * Users

* OS utilities and UI sit on top of it

* Programs make syscalls to ask the kernel to do things for them.

* Shell scripts, pipes, regexes

* The file syscalls: open, close, read, write
* File descriptors are what the kernel uses to identify open files
* stdin, stdout, stderr
* fork/exec used to launch new processes
* Processes become zombies when they die
  * Until parent `wait()`s.l

* Scheduler
  * Scheduling disciplines
  * I/O makes a process block
  * Timer interrupt can preempt a running process
* The shell REPL loop

* When you fork
  * Each process gets a copy of the data
  * Open files are shared between parent and child
  * Data can be passed between processes with a pipe
  * File descriptors can be duplicated with dup
    * Use this to hook up I/O for a pipe or redirection

* Memory cache
  * On-CPU, speeds things up
  * Difficulties with multicore

## Memory Map

* Heap
* Stack

## `malloc()`

Exercises with class:

* How do you `malloc()` 10 bytes?
* How do you `malloc()` enough space for a string?
  * Unicode characters might make it messy
* How do you `malloc()` space for an int?
* How do you `malloc()` space for 10 ints?

* Demo `sizeof(int)` vs `sizeof *p`

## `void *`

* `malloc()` returns a `void*`.
* You can't dereference.
* You can assign to another pointer.
* Cast is unnecessary for return value from `malloc()`.

## Stack Frames

* Demonstrate stack frames with recursive calls
* Every time you call a function a stack frame is created
* Every time you return from a function, a stack frame is destroyed
* Stack frame holds locals, parameters, and return address
