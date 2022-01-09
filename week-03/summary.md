## Summary

* The _scheduler_ is the part of the kernel that decides which process
  gets to run (use the CPU) next.
* There are a lot of different scheduling policies (AKA _disciplines_)
  that have different performance characteristics.
* Two common metrics that schedulers attempt to minimize to a certain
  degree are:
  * Response time: the time it takes from the requested start of a
    program until the process gets scheduled to run.
  * Turnaround time: the time it takes from the requested start of a
    process to its total completion.
* Some basic scheduling disciplines are:
  * First-In-First-Out (FIFO) / First-Come-First-Served (FCFS)
  * Shortest-Job-First (SJF)
  * Shortest-Time-to-Completion-First (STCF)
  * Round-Robin (RR)
* The scheduler can _preempts_ a process, giving the CPU to another
  process.
* When a process requests I/O, the scheduler runs other processes until
  the I/O completes. Once the I/O is done, the process that requested it
  is marked Ready-to-Run and will eventually be scheduled again.
* The Multi-Level-Feedback-Queue (MLFQ) is a more advanced scheduler
  that attempts to have good response time and good turnaround time.
* The core of a shell is a loop that reads commands, parses them, and
  (after `fork()`ing a new process), feeds them to `execvp()` in the
  child process. Then the parent process `wait()`s for the child to
  complete before looping again.