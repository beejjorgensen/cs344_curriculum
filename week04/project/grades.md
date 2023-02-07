# lswc

-3 The last argument to `execlp()` must be NULL, and it's not in the case of the user specifies a directory. This is causing it to malfunction in my case.

# Redirout

-1 Two arguments is the minimum.

-1 Incorrect computation of start of arguments in argv

# Misc

Fix your unused parameter warning with `(void)argc;`

Make sure your code indentation is consistent and good.

Add blank lines between logical sections of code to make it more readable.

Specify a file permission on the open() call: `open(filename, O_WRONLY|O_CREATE|O_TRUNC, 0644)` or weird things can happen with the permissions.

Don't check build products into git--add them to your .gitignore.

The type returned from `fork()` is `pid_t`.

Use `NULL` instead of `(char*)0`. They're the same thing, effectively.




So... with the `redirout`, there's actually a much easier way to make it work. And, embarrassingly, I can't recall for the life of me why I had you all implement it with a pipe. For this reason I'm being very lenient with coding errors related to the pipe on redirout.

Does anyone see it? As a hint, the solution doesn't use `pipe()` or `fork()`, necessarily.
