<!-- Exploration 4.1: CFS, File Descriptors, Pipes -->

## The Completely Fair Scheduler (CFS)

This is one of the schedulers available for Linux, and is one of the
most popular. Let's take a look at this real-world piece of software.

Highlights:

* CFS takes a repeating time interval and splits it up evenly amongst
  all the processes that wish to run at that time. Each process gets an
  equal portion of that time interval to run.
* The equal portion can be made greater or smaller by setting the _nice_
  level for the process.
* Each process's total CPU time is tracked by the OS.
* When scheduling, the ready-to-run process with the least amount of CPU
  time is chosen to run.
* A [red-black tree](https://en.wikipedia.org/wiki/Red_black_tree) is
  used to quickly (`O(log n)`) track the process with the smallest
  runtime.
* When waking from sleep (moving from "blocked" to "ready-to-run") the
  process's total CPU time is set to the smallest value among all the
  other ready-to-run/running processes.

## Unix `fork()` and Shared Data

When you `fork()`, a new process is created with effectively a copy of
the data in the parent. Variables will have the same values, etc.

But those variables are independent. If a child manipulates a variable
(global or local), the parent does _not_ see those changes, and vice
versa. By default, data is not shared between processes.

> For comparison, data _is_ shared between _threads_. In Unix, you can
> use the `pthreads` library.

There are various mechanisms for sharing data between processes,
including but not limited to:

* Shared memory segments
* Mutexes and Semaphores
* FIFOs
* File locks
* Unix domain sockets
* pipes

We'll talk about the last of these: pipes.

## Unix `fork()` and Shared Files

Recall that every open file in a process is represented by a _file
descriptor_, which is a non-negative integer number.

Like regular variables, the child process gets a copy of the variables
that hold the file descriptors open in the parent.

So if the parent opens file descriptor `4` and stores it in variable
`f`, the child will get a `4` in its `f` variable, as well.

**The magic**: _both those file descriptors point to the same open file.
Either process can write to that same file through that file
descriptor._

If the parent opens a file, both the parent and child can access that
file through the same file descriptor.

## Unix Pipes

In Unix, a _pipe_ is a one-directional communication conduit.

It is created at runtime with the `pipe()` system call.

Bytes written to the "write" or "input" end of the pipe can be read from
then "read" or "output" end of the pipe in the order they were put in.

**The magic:** _If the parent creates the pipe, both the parent and
child processes have access to both the read and write ends of the
pipe._

So the parent can create the pipe, then `fork()` a child process. And
the parent could write into the pipe, and the child can read from it!

Interprocess communication!

Now, since the pipe is unidirectional, it's very, very common to decide
that one of the processes only reads from the pipe, and the other
process only writes from the pipe.

This keeps things sane.

And, related to that, it's really common that the process will call
`close()` on the end of the pipe they're not going to be using.

For example, if the parent is going to only write into the pipe on
`pfd[1]`, it'll close `pfd[0]`. And the child will only read on `pfd[0]`
and it closes `pfd[1]`.

It's important because a process won't get an end-of-file indication on
the read end of the pipe unless _all_ the process that had access to the
write end have closed it.

All this "file"-y stuff. Pipes sure sound like files, right? You
`read()`, `write()`, and `close()` them, just like files. There's an old
proverb: _everything in Unix is a file_. This is true of pipes, as well.

## The `pipe()` Syscall

A pipe is created like this:

```
int pfd[2];   // Pipe file descriptors, write and read

pipe(pfd);    // Create a pipe
```

After the call:

* `pfd[0]` is the read/input end of the pipe.
* `pfd[1]` is the write/output end of the pipe.

> A mnemonic for remembering which end is which is to recall that:
>
> * File descriptor `0` is standard input
> * File descriptor `1` is standard output

## Duplicating File Descriptors

This is brain-bending, so read slowly.

We need to tie this into how shell pipes work, because `pipe()` is what
the shell uses under the hood for it's pipe operator, `|`.

What if we want to run a utility program and pipe something into it?

For example, what if we wanted to send the string `"hello"` to the
program `wc`?

It seems problematic, because `wc` **only** reads from either a file, or
from `stdin` (AKA file descriptor `0`).

But I don't want to save it to a file, so the first option is out.

And I can't change `wc` to read from anything other than `stdin`
otherwise. It's been hardcoded to do that.

So what to do?

We know we can write things into the write end of the pipe. How do we
get `wc` to read out of the read end of the pipe instead of from `stdin`
(AKA file descriptor `0`)?

What we're going to do is this: we'll rewire the file descriptors fromp
`wc`'s perspective so that file descriptor `0` **is** the read end of
the pipe.

`wc` will continue to read from file descriptor `0`, oblivious to the
fact that it's now the read end of a pipe, and not the keyboard as
usual. It simply doesn't care where the bytes are ultimate coming from.
It's reading from file descriptor `0`, and that's the whole story from
its perspective.

We can do this with the `dup2()` syscall, like this:

```
// Make file descriptor 0 the same as pfd[0]
// so that reads from 0 are the same as reads
// from pfd[0]

dup2(pfd[0], 0);
```

Internally, `dup2()` will close file descriptor `0` from whatever file
it was attached to before (presumably the one representing the keyboard)
then effectively reopen it as a copy of `pfd[0]`, representing the same
file.

At that point, the process can read from either of those descriptors to
get information out of the pipe, since `0` is now a duplicate of
`pfd[0]`.

And this is great for getting `wc` to read from the pipe, because it's
going to read from file descriptor `0`.

Note: if a process `dup2()`s some file descriptors, that just affects
the file descriptors in that process, alone. The file descriptors in the
parent or other processes are unaffected.

## Putting it Together

A parent process can pipe things to a child process with the proper
setup ahead of time.

An example run where the parent passes data through a pipe to a child
process that calls `exec()`.

* Parent calls `pipe()` to create it. This will be visible to parent and
  children.
* Parent `fork()`s a child. Child can access the pipe through its copy
  of the pipe's file descriptors.
* Child calls `dup2()` to hook the read end of the pipe up to its
  standard input, file descriptor `0`.
* Child calls `exec()` to launch a new program
* Parent calls `write()` to send data into the write end of the pipe.
* Child calls `read()` on standard input (file descriptor `0`) to read
  from the read end of the pipe.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Lottery Scheduling/Proportional Share](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-lottery.pdf) sections 9.7-9.8
  
Here is a link to the interactive demo from that chapter,
[lottery.py](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched-lottery).

## Reflect

* What does the CFS use the `vruntime` variable for?
* In CFS, what are the effects of changing the `sched_latency` tuning
  value?
* In CFS, what are the effects of changing the `min_granularity` tuning
  value?
* How does using a red-black tree help make CFS more performant?
* With CFS, what wrench is thrown in the works by I/O?
* If a parent creates a pipe, how does the child access that pipe?
* Why is it a good practice for a process to close the ends of the pipe
  it isn't using?
* After you `dup2()` an open file descriptor into another, what is the
  difference between the two in terms of usage?
