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
