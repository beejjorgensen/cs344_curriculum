<!-- How the OS Runs Programs -->
When you tell the shell to run a command, it asks the OS to do it.
(After all, the OS is the gatekeeper and so the shell has to beg
permission to do it. This happens through the `exec()` family of system
calls.)

So you type in `./filename` to run the program, and the shell says to
the OS, “Please run filename.”

The first thing the OS does is check to see if filename is executable by
you. If not, the OS returns “Permission denied” and that’s that.

But assuming it’s executable (because you set it as such with `chmod +x
filename`), then the OS goes to the next phase: divining what kind of
executable file this is. Often many types (Links to an external site.)
are supported by an OS.

To do that, it looks at the first few bytes of the file for some kind of
[_magic number_](https://en.wikipedia.org/wiki/Magic_number) that
identifies the executable type. For example, the common ELF binary
format (as you might get from building a C program) begins with the
bytes `0x7F`, `'E'`, `'L'`, `'F'`. And if the OS sees that, it loads it
into memory and runs it like a regular binary file.

> Binary file formats like ELF or Mach-O contain some metadata, but also
> the raw machine code that will eventually be run. When the program
> loads, the OS allocates memory for that machine code and copies it
> from disk into that memory. Then when the corresponding process is
> run, it jumps to that machine code and executes.

But if the first two bytes are `#!`, then the OS does something else. It
looks at the rest of the first line for a full path to an interpreter
program and passes the file off, wholesale, to that interpreter.

For example, if you have this:

```
#!/bin/bash

echo "Hello, world!"
```

and set that file to executable (with `chmod +x`), and then run it with
`./foo`, the OS will see the first two bytes are `#!` and then read the
rest of that line (`/bin/bash`) and then run `/bin/bash` and tell it to
execute this file.

You could also:

```
#!/usr/bin/python

print("Hello, world!")
```

for the same effect. (Though it’s far more common to `#!/usr/bin/env
python` because that will find Python in the `PATH`. But with shells
like `/bin/bash` it’s OK because they’ll always be found in `/bin`.)

And, finally, note that `#` is the comment symbol in most shells and
Python, so the `#!` line is ignored by those interpreters.

Fun fact: since the 1950s, typesetters have referred to the exclamation
point as “bang”, perhaps due to its appearance in comic books, and this
carried over into Unix hackerdom. And `#` is a hash mark. Putting them
together gets you “hash bang”, which has been contracted to “shebang”,
the name given to that first line of the script.