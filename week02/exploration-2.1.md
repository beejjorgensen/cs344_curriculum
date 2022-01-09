<!-- Processes and System Programming -->

## Processes

A process is a running program. Since there are many programs running at
the "same" time and only so many cores to run them on, the kernel has to
keep track of a number of things:

* The memory used by the process
* The process state:
  * Ready to run
  * Running
  * Blocked (by I/O or other reasons)

## Process API

The kernel allows programs to do at least the following three main
operations with processes:

* Create a process
* Destroy a process
* Wait for a process to complete

When a process creates a new process, the creator is said to be the
"parent" and the new process, "the child".

When you run a command from the shell, the shell creates the new process
you asked to run, then waits for it to finish before showing you another
shell prompt.

## C Programming and the OS

If you're rusty on C, check out the free [Beej's Guide to
C](https://beej.us/guide/bgc/) Good non-free books are _The C
Programming Language 2nd Edition_ by Kernighan and Ritchie, and _C
Programming: A Modern Approach_ by K. N. King.

We know that the OS exposes functionality through system calls
("syscalls"). [There are
many](https://linuxhint.com/list_of_linux_syscalls/). In C, these
manifest as regular functions that you can call, although under the hood
they're actually switching to privileged kernel mode to do the work. (A
regular function like `sqrt()` is going to stay in unprivileged user
mode to do the work.)

Let's take a look at doing some file I/O directly through the OS, as
opposed to through the C standard library.

To make this happen,  we can use the following syscalls:

* `open()` from `<fcntl.h>`
* `close()` from `<unistd.h>`
* `read()` from `<unistd.h>`
* `write()` from `<unistd.h>`

If you ever forget which header files to #include, you can look them up
in section 2 of the manual, for example:

```
% man 2 open
```

## File Descriptors

The above four functions keep track of which file they're talking about
though something called a _file descriptor_. The file descriptor is just
a non-negative integer representing an open file (or other resource from
which you can read and write).

A successful `open()` call returns a file descriptor that can be used in
subsequent `read()`, `write()`, and `close()` calls.

This way a process can have many files open at once, tracking them
through their unique per-process file descriptors.

As an example, here is a call opening a file for reading (read-only):

```
int fd = open("input.txt", O_RDONLY);
```

With most syscalls, if the returned value is `-1`, something went wrong.
You can print out a human-readable message about it with the `perror()`
function found in `<stdio.h>`.

```
int fd = open("input.txt", O_RDONLY);

if (fd == -1)
    perror("open")
```

If the file wasn't found, this would output the following (the word
"open" is from the argument to `perror()`):

```
open: No such file or directory
```

Once a file is open, you can read from it like so, using the file
descriptor from the `open()` call:

```
char buf[128];  // Buffer to hold the data
int count;

count = read(fd, buf, sizeof buf);  // fd, buffer, max bytes
```

Note that read() will not write more than can fit in `buf`, but it might
write less! Check the returned `count` to see how many bytes were
actually read.

You can write in much the same way:

```
count = write(fd2, "Hello!", 6);
```

That writes `6` bytes to `fd2`, presumably opened for writing. `count`
will hold the number of bytes actually written, which might be fewer
than you asked for. (But for this part of the class we don't need to
worry about that happening.)

## Built-in File Descriptors

In Unix, there are three file descriptors that are created automatically
for new processes, numbered `0`, `1`, and `2`.

* `0`, standard input or `stdin` -- usually the keyboard, but could be
  another program's output being piped in, or a file being redirected as
  input

* `1`, standard output or `stdout` -- usually the screen, but could be
  another program's input being piped into, or a file being redirected
  as output

* `2`, standard error or stderr -- usually the screen, but could be
  another program's input being piped into, or a file being redirected
  as output

Standard error and standard output seem pretty much the same. But by
convention, programs send error messages to `stderr` and regular output
to `stdout`. This enables the runners of the program to separate error
messages if they choose to do so.

For example, we can print a hello message to the screen (`stdout`, file
descriptor `1`) like this:

```
write(1, "Hello, world!\n", 14);  // Write these 14 bytes to fd 1
```

That bypasses all the C standard library functions (like `printf()` or
`puts()`) and calls directly into the kernel. Note that library calls
like `printf()` eventually call `write()` deep down to get their work
done--just with more functionality and features than the barebones
`write()` call allows.

## Command Line Arguments

We'll be processing a lot of command line arguments; you can [review how
to do that
here](https://beej.us/guide/bgc/html/split/the-outside-environment.html#command-line-arguments).

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [_Dialogue_](https://pages.cs.wisc.edu/~remzi/OSTEP/dialogue-virtualization.pdf)
  * [_Processess_](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-intro.pdf)
  * [_Process API_](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf)
    (just skim except for page 11, "Aside: Key Process API Terms"--you
    can come back and reference this chapter when we use it later)

## Reflect

* What is a process?
* What are some of the common functions in the kernel's process API?
* What does a file descriptor do?
* What's the difference between stderr and stdout?