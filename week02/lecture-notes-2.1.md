# Lecture 2.1

## A Little Bit of Processes

* [Bring up Exploration 2.1]
* Process Review, process states
  * Ready to run
  * Blocked
  * Running
  * How do we get from one state to another?

## Simulation

Process

* COVID: don't pair students; just lead from the front of the class.
* NON-COVID: Pair students to work on the problems.

What it is

* This is a simple simulation that shows how the CPU gets utililized
  when I/O is present.
* It runs jobs in the order given, no preemption.

Example

Program 1 runs first, 10 instructions, 50% of instructions are CPU
(non-I/O)

Program 2 runs next, 5 instructions, 100% of instructions are CPU
(non-I/O)

```
python process-run.py -l 10:50,5:100
```

This will show the world from each process's point of view, in
isolation.

Run with `-cp` to get a per-process breakdown and stats.

More details

* A process will run to completion
* Unless it has I/O, then it gives up the CPU for another process to run
* The only way a process gets to start running is if
  * It's next in line to run and
  * Another program completes or
  * Another program does some I/O

## Process API

* Quick refresher--the OS has an API for a process to:
  * Create a process
  * Destroy a process
  * Wait for another process to complete

## System Calls and C Programming

* Bring up gcc
* Code along

* printf hello world
  * Go over all the lines in detail
* write hello world
* wrote code that reads from a file
  * show man page lookup

## Extra material on C programming

Options, class directed:

* for loop syntax
* how strings work
* pointers
  * Home address on post-it note analogy?
