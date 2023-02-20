# General

There's some inconsistent indenting--try to make it look good!

Separate logical sections with blank lines to make it easier to read.

Consider breaking out logical blocks into functions so you don't have one big main().

Usually build products (e.g. the executable) are not checked into git, since they can be easily recreated.

Hitting enter on a blank line causes a crash--this should be made more user-friendly!

Hitting CTRL-D (EOF) causes strange things to happen. Typically this would cause the shell to exit (though not a requirement for this). You can detect this condition with the `feof()` function.

Though not a requirement, it would be nice to give an error when the user enters an unknown command (i.e. when `exec()` fails). `perror()` would be useful there.

The proper main signature is `int main(void)`, indicating no parameters.

On error, `exit(1)` (or some small positive number) is typically used to indicate an error condition caused the exit. (As opposed to `0` which is typically interpreted as "successful, normal, intended exit".)

To be most correct, you'd error check `fork()` to see if it returned `-1` for some reason.

You can do `int main(void)` to avoid the unused variable warnings.

You can add "\n" to the `strtok()` delimiter string and that'll make it automatically eat up the newline at the end.

If `exec()` ever returns, the status code will **always** be `-1`. (Remember that if it succeeds, it does not return.) So it's one of those weird functions where you don't need an `if` to decide if you're going to print an error. It returned, therefore an error must have occurred.

`ls` with no arguments shows the files in the current directory by default, so there's no need to add the current working directory on as an argument.

# Prints Prompt, reads input

-2 Doesn't print prompt

-5 No exit after failed `exec()`, which allows the child to keep running.

# Handles cd

-10 cd just exited when I tried to use it. This was because it tried to `execvp()`, but it shouldn't because `cd` is an internal command. Additionally, there needed to be a `continue` after handling `cd` to prevent it from executing the main `exec()` after that.

-3 You need a `continue` after the `cd` logic so that it doesn't try to `exec()` a `cd`.
