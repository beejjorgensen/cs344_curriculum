<!-- Project 4: Use Pipes for Interprocess Communication -->

## Introduction

For this project, you're going to write two programs:

* One will pipe its output into the input of another program.
* The other will save the output of a command in a file.

Under the hood, these will work in the same way that pipes work in the
shell (the `|` shell operator) and how output redirection works (the `>`
shell operator). Except we're going to code them from scratch with
syscalls!

## What to Do

**NOTE**: For these programs, you may not invoke the shell to do the
work. (i.e no calling `system()` or `exec()`ing `bash` or `zsh`.) You
**must** use syscalls from C to get the work done.

### Part 1: Pipe from One Command to Another

We're going to write a program that runs `ls` for a given directory and
`wc` (word count) at the same time, and pipes the output from `ls` into
`wc`.

Example run:

```
% lswc /usr/bin
5685
```

We're going to do this without calling on the shell to do it; we're
going to use `fork()`, `exec()`, `pipe()`, and `dup2()` syscalls to get
it done.

When you're in your shell, you can figure out how many files there are
in the current directory like this:

```
% ls -1a | wc -l
```

That's "minus one A" in that we're giving to `ls`--the `1` it tells it
to have a single column of output, one file per line.

Then we pipe it into `wc -l` (word count, lines) which will tell us how
many lines of output there are. And, therefore, how many files were in
that directory.

We want to write a program called `lswc` that runs `ls -1a` (on a
specified directory) and also runs `wc -l`. And we want it to pipe the
output of `ls` into the input of `wc`.

If the user specifies a directory name on the command line, you should
run the command for that directory (e.g. `ls -1a /usr/bin | wc -l`).

If the user doesn't specify a directory on the command line, use the
current directory.

If your code is working, you'll get the same output as the command as
run from the shell:

```
% ./lswc
8
% ls -1a | wc -l
8

% ./lswc /usr/bin
5685
% ls -1a /usr/bin | wc -l
5685
```

You'll probably need these headers:

* `<stdio.h>` for `printf()`, `perror()`
* `<stdlib.h>` for `exit()`
* `<unistd.h>` for `fork()`, `execlp()`, `close()`

The exact header files may vary by system. Look up the `man` pages for a
particular call to be sure.

Rough gameplan:

0. Parse the command line
1. Make a `pipe()` in the parent
2. `fork()`.
3. The child will run `wc`:
   * `dup2()` the read end of the pipe into `stdin`
   * `close()` the write end of the pipe
   * `execlp()` the `wc` command
4. The parent will run `ls`:
   * `dup2()` the write end of the pipe into `stdout`
   * `close()` the read end of the pipe
   * `execlp()` the `ls` command

It actually doesn't matter which process runs which command. The parent
can be the one that runs `wc`, if you wish. All that matters is one
process runs `ls` and the other runs `wc`.

You also don't have to use `execlp()`--you can use one of the other
`exec()` variants if that's easier. (I found `execlp()` to be easier.)

> **Sidenote**: This has been an exercise in using pipes. If you want to
> know how many files there are in a directory from a C program in Unix,
> there are much quicker ways than this.

### Part 2

Write a program `redirout` that redirects output into a file.

This program will run a child process/program, and save that child's
output in a specified file.

Example run:

```
% redirout foo.txt ls -l -a
% cat foo.txt
total 64
drwxr-xr-x 2 beej beej  4096 Jan 14 14:09 .
drwxr-xr-x 3 beej beej  4096 Jan 14 13:42 ..
-rw-r--r-- 1 beej beej     0 Jan 14 14:09 foo.txt
-rw-r--r-- 1 beej beej    13 Jan 14 13:00 .gitignore
-rwxr-xr-x 1 beej beej 16472 Jan 14 11:47 lswc
-rw-r--r-- 1 beej beej  1216 Jan 14 11:47 lswc.c
-rw-r--r-- 1 beej beej   185 Jan 13 12:48 Makefile
-rwxr-xr-x 1 beej beej 16664 Jan 14 12:09 redirout
-rw-r--r-- 1 beej beej  1169 Jan 14 12:09 redirout.c
```

Notice there's no console output from `redirout`--all the output goes
into the file specified.

You can also see the command line is broken up like this:

```
redirout  outfilename  command opt1 opt2 ...
```

The first command line argument will always be the filename to output
to.

The remainder of the command line is the command to run and all its
options.

You'll probably need these headers:

* `<stdio.h>` for `printf()`, `perror()`
* `<stdlib.h>` for `exit()`
* `<unistd.h>` for `fork()`, `execlp()`, `close()`
* `<fcntl.h>` for `open()`

Gameplan:

1. Parse the command line to make sure the user has entered the minimum
   amount of information.
2. `open()` the output file.
3. Create a `pipe()`.
4. `fork()` a child process to run the command.
5. In the child:
   * `dup2()` the output end of the pipe into `stdout`.
   * `close()` the input end of the pipe.
   * `execvp()` the command.
6. In the parent:
   * `close()` the output end of the pipe.
   * Repeatedly `read()` from the input end into a buffer.
     * `write()` the buffer into the output file you opened earlier.
     * `read()` will return zero bytes read on end-of-file (EOF).
   * `close()` the input end of the pipe.
   * `close()` the output file.

It might seem intimidating how to get the command in from your `argv[]`
into `execvp()`, but there's actually a shortcut that makes it pretty
trivial; you don't even need to parse `argv` to make it happen.

Hints:

* The command starts with `argv[2]` (since index `0` is `redirout` and
  index `1` is the output file name).
* In a plain array of `char`s, you can use pointer arithmetic to get a
  pointer to the 3rd `char` in the array like this:

  ```
  char *s = "abcdef"; // s points to letter "a"
  char *p = s + 2;    // p points to letter "c"
  ```
  
  `argv` is an array of `char*`s. How we get a pointer to the 3rd
  `char*`?

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **95 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

If you want more challenges:

* Write a program the redirects input from a file into a command, the
  opposite of what we did for part 2, above.

* Write a program that runs three programs in a pipeline, i.e. `x | y |
  z`.

* Write a program that runs an arbitrary number of programs in a
  pipeline.

* Add pipes to your `mush` shell.

<!--
Rubric:

5
lswc creates a pipe

10
lswc forks/execs a child process

15
lswc properly connects pipes with dup2

5
lswc all unused ends of the pipe properly closed

5
lswc works on the directory specified on the command line

5
rediroutput prints out a friendly help message if the user doesn't enter the minimum number of arguments

5
rediroutput creates a pipe

10
rediroutput creates the output file, truncating it to 0 length if it exists

10
rediroutput forks/execs a child process

15
rediroutput properly connects pipes with dup2

5
rediroutput all unused ends of the pipe properly closed

5
rediroutput reads input from the pipe in a loop, handling input of any size
-->
