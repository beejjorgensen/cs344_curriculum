<!-- Project 3: Write a Shell in C -->

## Introduction

For this project, you're going to write a complete shell from scratch, a
competitor to `bash` and `zsh`!

OK, so not a _super_ competitor, but you will be putting together the
basis for a real shell from which you can run real commands.

## What to Do

We're going to write the _Mega Underwhelming Shell_, or `mush` for
short.

### Part 1

You'll probably need these headers:

* `<stdio.h>` for `printf()`, `fgets()`, `perror()`
* `<stdlib.h>` for `exit()`
* `<string.h>` for `strtok()`, `strcmp()`
* `<unistd.h>` for `fork()`, `execvp()`
* `<sys/wait.h>` for `wait()`

The exact header files may vary by system. Look up the `man` pages for a
particular call to be sure.

First, the basic shell:  

1. Begin with the main loop. For now, just have it go forever.
2. You should print a prompt, read a line (`fgets()`), and then parse it
   down to individual words (`strtok()`).
3. _I suggest you stop here and test everything to make sure it's
   working as expected_.
3. Put those words in an array of `char*`s. Be sure to terminate the
   array with a `NULL` so you can pass it easily to `execvp()`.
4. _I suggest you stop here as well, and make sure the array is built as
   you expected. It's easier to debug small bits at a time than the
   whole thing at once._
5. Call `execvp()` with your array. Pass the 0th element as the first
   argument to `execvp()`.

Some constraints:

* You can assume no one will enter a command line longer than 2048
  characters.
* You can assume that no command line will have more than 128 individual
  words.

At this point, if it's working, you should be able to launch your shell,
and then run a command like `ls -la`. And after it runs, you'll be back
at your **real** shell prompt, and `mush` will have exited.

Why? How did you get out of your main loop?

Remember that when you call `exec()` it replaces the currently running
program with the new `exec()`d program. Your `mash` shell was replaced
by `ls`. And then `ls` exited, and that was it.

So you need to `fork()` a new process to do the `exec()`. The parent
process will keep running the main loop, and the child process can be
replaced with the thing you wanted to run (e.g. `ls`). Let's do that
next.

### Part 2

It might be clearer to write a function that handles the running of a
command, just to keep your main loop from getting too crowded and hard
to read.

To run the command:

1. `fork()` a child process.
2. The child process should `execvp()` the command that you put in the
   array with `strtok()`. This will replace the child program with the
   requested program, but the parent process running the shell will
   remain unaffected.
3. The parent process should call `wait(NULL)` to wait for the child to
   complete.

Remember that if `execvp()` returns, it means something has gone wrong,
like permission denied, or file not found. Use `perror()` to print an
error message. If successful, `execvp()` will not return at all--it'll
be gone when this program is replaced by the new one.

**And this is important**: if `execvp()` fails, after you print the
error you must call `exit(1)` (from `<stdlib.h>`) to have the child
quit. If you don't, the child will happily reenter the main loop and
take over for the parent that's still `wait()`ing! It'll look like the
command didn't work and everything is fine, but it'll start behaving
poorly when you implement the `exit` command later.

To get out of the shell, you can hit `CTRL-C` for now.

### Part 3

You need to be able to change directories with `cd`. But `cd` is an
_internal command_ or _built-in_.

Since each process keeps track of it's current directory, you can't
launch an external process to change your directory. It would only
change the directory of the external process, leaving you where you
were.

So we need a special case. _You don't need to (and mustn't) call
`fork()` for this!_ You can just handle it from the main process.

If the first word of the command line is `cd`, then you need to make a
syscall to `chdir()` with the second word of the command line.

Check the return value of `chdir()`. If it's `-1`, something went wrong
and you should `perror()` to see what it was.

If it's working, you should be able to `cd` at will from the prompt.

### Part 4

Add exit support.

Typing `exit` in a shell will cause that shell to quit. We should add
this.

Again, we can't have an external `exit` command, because it would only
cause _that_ process to exit, not our shell.

So it has to also be a special case command.

Check the first word of the command. If it's `exit`, don't `fork()` a
child process. Just call `exit(0)` instead and exit the shell.

**ProHint**: if you have to type `exit` multiple times before it seems
to take effect, you should make sure you have an `exit()` call after the
`execvp()` call in the child process of `fork()`! You might just be
exiting child processes that have found themselves falling into the main
loop.

## What to Turn In

Submit the link to your GitHub repo.

## Extensions

Don't do pipes. We'll do those next week.

### Better errors

Add good error messages if the wrong number of arguments are passed to
`exit` or `cd`, if you haven't already.

For example:

```
if (arg_count != 2)
    fprintf(stderr, "usage: cd directory\n");
```

Make your `perror()` statements informative for `chdir()` as well, by
printing the attempted directory name if something went wrong.

```
mush$ cd nonexistent_dir
nonexistent_dir: No such file or directory
```

### More Capable `exit`

You can pass an exit status to the `exit()` call, and it would be nice
to get them from the command line.

For example, if I type:

```
mash$ exit 2
```

I'd like to see `exit(2)` called by the shell. If I just type `exit`
with no arguments, it should call `exit(0)`.

### Exit on End-of-File

`CTRL-D` is the Unix end-of-file key. You can test for EOF with
`feof()`.

The basic idea is to read a line, then test for EOF. And exit if it's
true.

```
fgets(line, sizeof line, stdin);

if (feof(stdin))
    exit(0);
```

Then you can exit the shell with EOF as well as the `exit` command.

<!--
Rubric:

5
Prints prompt, reads input

20
Runs single command

20
Runs single command and arguments

20
Handles cd command

10
Handles exit command

5
Loops around printing prompt and running program
-->
