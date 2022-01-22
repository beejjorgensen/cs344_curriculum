<!-- Exploration 3.1: Scheduling -->

## Scheduling

The _scheduler_ is a basic part of the OS kernel that answers a simple
question:

* Out of all the processes that are ready to run, which one gets to run
  next?

Deciding how to answer that is a rather human problem, actually. Imagine
you have a group of 10 children who all want to ride on a single swing.
How do you choose whp goes next?

You might think, well, we'll go around taking turns in order,
repeatedly. This way the child who has used the swing least recently
will always go next.

This scheduling scheme is called _round robin_, and it's a legitimate
way of scheduling processes.

But like you'll find in the reading, it's not without its drawbacks.

A scheduler has to try, for a given pattern of CPU and I/O usage to get
maximum runtime to the maximum number of processes. An additional goal
might be that the system has to be responsive to user input even under
heavy load. Multiple factors can come into play when deciding which
process to schedule next.

For instance, I/O is glacially slow compared to the CPU, so if a program
needs to get something from your disk, does it make sense to have all
the other programs wait until the disk has retrieved the information?

Maybe it's better to put the I/O program to sleep ("blocked") until the
disk has the data ready, and in the meantime schedule other processes to
run.

We'll look at different scheduling disciplines and compare how that work
under different circumstances.

## Some helpful functions

These might come in useful for this week's project.

### `fgets()` -- Read a Line

Using `scanf()` or the `read()` syscall to read a line of data from the
keyboard can be problematic for various reasons.

* The input is probably line buffered at the terminal, leading to
  confusing results from `scanf()`.
* `read()` is too low-level--it only counts bytes, not newlines.

But there's a library function called `fgets()` that will read from an
open file until either the specified number of bytes is reached, or a
newline is found, whichever is first.

Note that the newline is returned as part of the string that is read.

Demo:

```
#include <stdio.h>

int main(void)
{
    char s[2048];

    printf("Enter something: ");

    fflush(stdout);  // Make sure the prompt is displayed

    fgets(s, sizeof s, stdin);  // Read a line from stdin

    printf("s is \"%s\"\n", s);
}
```

Note: since there's no newiine on the prompt, above, we might not see it
on the output because C is buffering it to minimize the number of
syscalls to `write()` it has to make. Calling `fflush()` forces the
output to be sent.

Output:

```
Enter something: vim is better
s is "vim is better
"
```

Note: see how the newline is captured as part of the string, which is
why the second quote is on the next line down.

Also note: Vim is better.

### `strtok()` -- Tokensize (split) a line

It can sometimes be useful to split lines into chunks based on a
separator. Modern languages tend to have a function called `split()` or
something similar. C has `strtok()`.

Its usage is a little funky. The first time you call it, you pass in the
string to tokenize as well as the field separators (the things to split
on). That gives you back the first token.

To get subsequent tokens, you call it again but pass `NULL` as the
string to keep processing. That's `strtok()`'s hint that it should keep
processing subsequent tokens, not start fresh on a new string.

`strtok()` can split on any of a number of characters, so when splitting
on whitespace it's common to include all whitespace variants:

```
strtok(s, " \t\n\r");  // split on space, tab, newline, return
```

Leading and trailing split characters will be effectively stripped.

This is really useful in conjunction with `fgets()` for getting rid of
the trailing newline; just add `\n` to your delimiter string.

`strtok()` returns `NULL` if there are no more tokens.

Here's a contrived demo. Notice that on the first call we pass the
string to tokenize, and on subsequent calls we pass `NULL`:

```
#include <stdio.h>
#include <string.h>  // for strtok()

int main(void)
{
    char s[] = "  This  is a   test!   ";
    char *token;

    token = strtok(s, " ");    // First
    printf("%s\n", token);

    token = strtok(NULL, " "); // Subsequent
    printf("%s\n", token);

    token = strtok(NULL, " "); // Subsequent
    printf("%s\n", token);
}
```

Output:

```
This
is
a
```

Since you have to call it with `NULL` as the first parameter to get
subsequent tokens, a common usage pattern to get all tokens has been
generally settled upon as idiomatic: an `if` statement for the first
call followed by `do`-`while` for subsequent calls.

```
#include <stdio.h>
#include <string.h>  // for strtok()

int main(void)
{
    char s[2048];

    printf("Enter something: ");
    fflush(stdout);
    fgets(s, sizeof s, stdin);

    char *token;

    if ((token = strtok(s, " \t\n\r")) != NULL) {
        do {
            printf("Token: \"%s\"\n", token);
        } while ((token = strtok(NULL, " \t\n\r")) != NULL);
    }
}
```

Those nested expressions in the `if` and `while` are weird. The
assignment to `token` happens first (because it's in parens) and then
the result of that assignment (i.e. whatever is stored in `token`) is
compared to `NULL`.

Output:

```
Enter something:    this     is  the best     time
Token: "this"
Token: "is"
Token: "the"
Token: "best"
Token: "time"
```

### `execvp()`

This syscall executes a program based on an array of arguments. To use
it, you build an array of strings that terminates with a `NULL` pointer,
then pass that into `execvp()`.

```
#include <stdio.h>
#include <unistd.h>  // for execvp()

int main(void)
{
    char *args[] = {  // ls -a -l
        "ls",
        "-a",
        "-l",
        NULL   // Command arguments must end with NULL
    };

    execvp(args[0], args);

    // If we get here, exec failed
    perror("exec");

    return 1;
}
```

Running that, you should get a long directory listing.

Remember that `exec()` replaces the currently running process's program
with the new program. So if we ever see `exec()` return, it means it
failed.

If you want to see `exec()` fail, replace `"ls"` with something
non-existent, like `"ls_nonexistent"`. You'll get output like this from
the `perror()` call:

```
exec: No such file or directory
```

## Reading

In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [CPU Scheduling](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched.pdf)
  
Here is a link to the interactive demo from that chapter,
[scheduler.py](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched).

## Reflect

* What is the main goal of the scheduler?
* What factors have to be considered when designing or selecting a
  scheduler?
* What kind of wrench does I/O throw in the works for a scheduler?
* Why don't we have to error check the return value from the `exec()`
  call? Why can we just assume it was an error if it returned?
* Why not use `read()` to read a line from the keyboard?
* If you did use `read()` to read a line from the keyboard, how might
  you do that? What problems might you encounter?
* Why does `strtok()` require you to pass `NULL` as the first parameter
  to get tokens after the first?