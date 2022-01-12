<!-- Exploration 2.2: Unix Process API -->

## Limited Direct Execution

_Direct Execution_ is the idea that processes run directly on the CPU,
i.e. the OS gives them complete control of the CPU so they can run as
fast as possible.

We're going to use the words _trap_ and _interrupt_ interchangeably.
There are plenty of conflicting definitions of how they differ (i.e. "An
interrupt is a signal from hardware, but a trap is an interrupt from
software") so we'll just make them the same for this discussion.

But the idea is the same: something has happened that interrupted the
running process and transferred control back to the OS. 

And the process keeps control until one of the following things happens:

* The process makes a system call.
* A timer interrupt occurs--this is how the OS preempts a process when
  its timeslice if up.
* An I/O or other interrupt occurs.

All of those things transfer control back from the running process to
the OS.

The _Limited_ part refers to the fact that the process, even though it
has control of the CPU, still doesn't have permission to interface
directly with the hardware or other system resources. Those still have
to be requested through syscalls.

To make this happen, the CPU can be running in _user mode_ (limited), or
_kernel mode_ (when running in the OS kernel).

If you're running in user mode, a syscall or interrupt gets you to
kernel mode.

If you're running in kernel mode, the kernel deciding to schedule your
process is what gets you back to user mode.

When the kernel decides to run another process, it does a _context
switch_. It takes all the saved state from the new process (e.g. what
all its registers held, etc.) and sets everything up so that when it
returns from the trap/interrupt, the new process starts running.

## Process API

Recall that the kernel exposes an API for us to create processes,
destroy processes, and wait for processes to complete.

In Unix, we use the following calls to do these tasks:

* `fork()` -- create a process
* `exec()` -- replace the currently running process with another one
* `kill()` -- destroy a process
* `wait()` -- wait for a process to complete

When you run a program from the shell, the shell does the following
steps:

1. Show a prompt.
1. Parse user input for the command name.
1. `fork()` a new child process. This is running the shell code, as
   well, somewhat confusingly. More on that in a minute.
1. `exec()` to replace the shell the child process is running with the
   program the user requested
1. `wait()` for the child process to complete.
1. Repeat from step 1

## What happens when you `fork()`?

> **WARNING**: _if you repeatedly run `fork()` in a loop, you're going
> to get in trouble fast. This is called a [fork
> bomb](https://en.wikipedia.org/wiki/Fork_bomb), and you could
> [DOS](https://en.wikipedia.org/wiki/Denial-of-service_attack) yourself
> out of your machine right quick depending on how it's configured. No
> one likes a hard reboot when your work isn't saved. Any time you're
> running `fork()` in a loop, make sure it's not going to run
> exponentially out of control._

Imagine that your process is executing your program, having a great
time. As you imagine this, imagine the program counter (or instruction
pointer) keeping track of the location of the currently-executing
instruction, one instruction to the next.

Then--bam! You call `fork()`. This effectively makes _another process
running the exact same code from that point on_. Each process has its
own copy of variables, so changing variables in one process doesn't
affect the other.

Sounds weird, right? Let's look at a sample.

```
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    puts("Before fork()");

    fork();

    puts("After fork()");
}
```

What will happen when you run this?

It starts as one process, which prints "Before fork()"... but then a new
child process is created when `fork()` is called. And this child process
returns and keeps running from the point of the `fork()`, just like the
parent. So both the parent and the child print "After fork()".

```
Before fork()
After fork()
After fork()
```

One of those last lines was the parent, and one was the child.

But how can we tell them apart?

Here's the magic: `fork()` returns a non-zero integer to the parent
process, but it returns `0` to the child! It returns a different thing
depending on what process it is!

The value returned is actually of type `pid_t`, a signed integer type.
This number uniquely identifies a process on the system. They might be
reused after some time, but no two processes will simultaneously share a
PID. In the case of the child, the `0` returned is not its PID, but is a
sentinel value indicating that it's the child. (The child can always get
its own PID with `getpid()`.)

So check this out--we can decide to do different things based on what it
returns, i.e. have the child do a different thing than the parent, even
though both processes are running the same program.

```
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    puts("Before fork()");

    pid_t pid = fork();

    switch(pid) {
        case -1:
            perror("fork");  // Handle errors
            break;

        case 0:
            puts("I'm the child process!");
            break;

        default:
            puts("I'm the parent process!");
            break;
    }
}
```

For this output:

```
Before fork()
I'm the parent process!
I'm the child process!
```

## Running a new program with `exec()`

Just running the same program after a `fork()` doesn't seem super useful
for running new programs. So let's join forces with the `exec()` family
of syscalls to run a completely different program.

What `exec()` does is it replaces, wholesale, the program a process is
running with another program. And the process runs that other program
instead. After the `exec()`, the old program is gone entirely from the
perspective of the process. And the new program is running from scratch
in it's place.

`exec()` says, "Forget about the program you were running, and start
over running this other one instead."

Think about what this means: _`exec()` never returns_! (Assuming no
error--it'll return `-1` if there's an error.)

Do you see how to use this with `fork()` to launch a new program?

Here's the game plan:

1. Parent `fork()`s a child process
1. Child `exec()`s a new program
1. Parent `wait()`s for the child process to complete

Let's try it:

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    puts("Parent: about to fork()");

    pid_t pid = fork();

    if (pid == 0) {
        puts("Child : execing the date command");
        execlp("date", "date", NULL);
        // If we get here, it must be an error
        perror("exec");
        exit(1);  // Child dies here

    } else {
        puts("Parent: waiting for child to complete");
        wait(NULL);
        puts("Parent: child has exited");
    }
}
```

For this output:

```
Parent: about to fork()
Parent: waiting for child to complete
Child : execing the date command
Tue Dec 28 17:57:15 PST 2021
Parent: child has exited
```

Note that we called this line from the child:

```
execlp("date", "date", NULL);
```

That's a little weird, but breaking it down:

* With `execlp()`, the `l` means "list of command arguments" and `p`
  means "search the PATH for the program".
  * By "list of command arguments", we mean that the arguments are
    included as extra strings in the call, as below.
  * The last argument must be `NULL` so `execlp()` knows when to stop.
* It's weird that `"date"` is duplicated. Just take it for granted for
  now that the first two arguments are the name of the program to run.

Let's say you wanted the date in RFC 2822 format UTC, with the `-R` and
`-u` flags. You could run that like so:

```
execlp("date", "date", "-R". "-u", NULL);
```

Lastly, the `wait()` call puts the calling process to sleep until one of
its child exits. There are variants of wait() that offer more control.
And the argument passed could be used to retrieve the exit status of the
child, but in this case we uncaringly pass `NULL`.

## Zombie Processes and `init`

As soon as a process exits in Unix, it becomes a zombie. The process is
done, and all its resources are freed, but its exit status still
persists waiting to be collected by another process. This normally
happens when a parent process wait()s for the child zombie. This gets
the exit status, and the zombie is gone.

If the parent process dies before the child, the child is adopted by a
process called `init` which always has PID 1. `init` is the first
process created upon system boot, and is the ultimate ancestor of all
processes. It never dies while the system is running. `init`
automatically reaps zombies of its children, adopted or otherwise.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Direct
    Execution](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-mechanisms.pdf)

## Reflect

* Which Unix syscalls map to process creation, termination, and waiting?
* What is the common relationship between `fork()` and `exec()`?
* What is a fork bomb?
* What is a zombie process? How is it created and destroyed?
* What is the `init` process? What does it do?

## Additional

If you're enjoying system-level programming in Unix, you might like the
book _Advanced Programming in the UNIX Environment_ by W. Richard
Stevens (not required for this class).