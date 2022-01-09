<!-- Exploration 3.2: Multi-Level Feedback Queue -->

## Multi-Level Feedback Queue

The MLFQ is a scheduler that attempts to solve two problems:

* Have the shortest-running-time programs run first.
* Be responsive to the user.

As the book points out, the first goal isn't easy, since the OS has no
idea how long a program intends to run for.

The MLFQ solves these problems in an interesting way.

If it's been a minute since you've used a queue, maybe do a quick
refresher with [Wikipedia's Queue
entry](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) or your
other website of choice.

### Timeslice Review

Before continuing, it's important to be clear on the concept of a
_timeslice_, that is, how long a process is allowed to hog the CPU
before a timer interrupt gives control back to the OS.

CPU-hungry processes (e.g. "compute pi to 100 billion decimal places")
are going to use their entire timeslice.

I/O-hungry processes (e.g. "search all these files on disk for a
particular string") are likely to hand control back to the OS before
they use their timeslice. Remember that all I/O has to go through the
OS, and every time you make an I/O syscall, you're giving up the
remainder of your timeslice.

The MLFQ looks favorably on processes that willingly give up the
remainder of their timeslice. It looks less favorably on processes that
do not.

### A Bunch of Queues

As its name suggests, the MLFQ is a number of queues, each queue
representing a _priority_.  Imagine, for instance, there are 8 queues.
Queue #8 is the high priority queue, Queue #7 is lower priority, all the
way down to Queue #1, the lowest priority.

A process exists in only one queue at a time, though the MLFQ scheduler
will move it from one queue to another according to certain rules.

When a process is in the highest priority queue with other processes
that are highest priority, the MLFQ scheduler will run it in round-robin
fashion with the other highest-priority processes.

Processes that are in lower-priority queues don't run at all...

... until the MLFQ moves them up into the higher priority queues.

It's the movement of processes between the queues that gives the MLFQ
scheduler its power.

### MLFQ Rules

In the rules, below, A and B are processes. The Priority() function
simply refers to relative priorities of the queues that contain A and B.

* **Rule 1**: If Priority(A) > Priority(B), A runs (B doesn’t).
* **Rule 2**: If Priority(A) = Priority(B), A & B run in round-robin
  fashion using the time slice (quantum length) of the given queue.
* **Rule 3**: When a job enters the system, it is placed at the highest
  priority (the topmost queue).
* **Rule 4**: Once a job uses up its time allotment at a given level
  (regardless of how many times it has given up the CPU), its priority
  is reduced (i.e., it moves down one queue).
* **Rule 5**: After some time period S, move all the jobs in the system
  to the topmost queue.

(Rules copied from the book.)

## Reading

In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Multi-level Feedback](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf)
  
Here is a link to the interactive demo from that chapter,
[mlfq.py](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched-mlfq)

## Reflect

* What is the advantage of the MLFQ over vanilla Round-Robin scheduling?
* What are the ways that the MLFQ prevents _gaming_ of the scheduler?
* Why is it dangerous to have a scheduler that can be gamed?
* What problem is solved by Rule 4, above?
* What problem is solved by Rule 5, above?
* Search online--what is the name of the scheduler that Linux uses? That
  OS X uses?