## Summary

* The Completely Fair Scheduler (CFS) is a common Linux scheduler.
* CFS evenly divides a time segment up among all the ready-to-run
  processes.
  * Except some of the process get a modified timeslice based on their
    "nice" value.
* CFS uses a red-black tree to get `O(log n)` performance when deciding
  which process to run next.
* Data are copied to a child process when the parent process calls
  `fork()`.
* Open files are shared between parent and child.
* If you want to communicate between processes, you'll have to use some
  kind of interprocess communication API.
  * Pipes are one of these API mechanism.
* A pipe is a unidirectional data conduit.
  * It has a write end and a read end. 
  * Data is read in the order it was written.
* `dup2()` can be used to duplicate a file descriptor.
  * This is how you hook up `stdin` and `stdout` to a pipe().
* Each core in a CPU can run a program independently of the other cores.
* Each core typically has its own cache.
* The cache is small, fast memory close to the CPU that holds a subset
  of RAM for quick access.
* Keeping caches synchronized (cache coherency) is one of the trickier
  parts of having one cache per core.
* Processes that are running _multi-threaded_ have to be aware of how to
  synchronize their reads and writes in a multicore system.
* One of the few places the octal numbering system is still in use today
  is with Unix file permissions, as passed to the `open()` and `chmod()`
  syscalls, and to the `chmod` command line utility.