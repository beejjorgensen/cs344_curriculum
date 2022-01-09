## Introduction

We're going to write some utilities.

You know how we used `grep`, `sort`, etc. with pipes? We're going to
write our own in C.

And we'll use syscalls to make it happen.

## What to Do

Put all these in the same directory in the GitHub repo that you submit.

### 1. Shake the rust off

Make sure your compiler is working from the command line by verifying
this says something other than "command not found":

```
gcc --version
```

Write a program `hello.c` that defines three variables:

* `x`, an `int` with value `12`
* `y`, a `float` with value `3.14`
* `s`, a string (`char*` or `char[]`) pointing to `"Hello, world!"`

then prints those values, followed by multiples of 5 printed with a
loop, like so:

```
x is 12, y is 3.140000
Hello, world!
0 x 5 = 0
1 x 5 = 5
2 x 5 = 10
3 x 5 = 15
4 x 5 = 20
```

### 2. Add a `Makefile`

If you're not familiar with Makefiles, [here's
one](https://canvas.oregonstate.edu/courses/1849663/files/91203382?wrap=1).
Drop this in the directory with your source and call it `Makefile` with
a capital `M`.

**IMPORTANT: _The indented lines below are indented with a single TAB
character, not spaces! If you use spaces, it won't work. Best to
download from the link, above._**

```
CC=gcc
CCOPTS=-Wall -Wextra
LIBS=

SRCS=$(wildcard *.c)
TARGETS=$(SRCS:.c=)

.PHONY: all clean

all: $(TARGETS)

clean:
    rm -f $(TARGETS)

%: %.c
    $(CC) $(CCOPTS) -o $@ $< $(LIBS)
```

Once you've done that, you can just type `make` to build all the C
sources you have in that directory.

### 3. Access Command Line Arguments

Write a program called `printcl.c` that prints out all the command line
arguments passed to it like so:

```
% ./printcl aaa bb c
0: ./printcl
1: aaa
2: bb
3: c
```

### 4. Read a file

Make a program `readfile.c` that reads the file specified on the command
line.

Let's assume the file is fewer than 2048 bytes so that you can capture
it all in a single read() call.

If you need a sample, the `readfile.c` source should be well less than
2048 bytes. Run it on its own source!

Don't use `printf()` or any of the other standard library output reading
or writing routines. (You may use `perror()` for printing error
messages.) Use `open()`, `read()`, `write()`, and `close()`.

Gameplan:

* Get the file to read from `argv[1]`.
* `open()` that file, getting a file descriptor.
* `read()` from the file descriptor, getting up to 2048 bytes in a 2048
  byte `char` array.
* Using the number of bytes returned from `read()`, `write()` that many
  bytes from the buffer to file descriptor `1` (standard output).
* `close()` the file descriptor when done.

Example output:

```
% ./readfile input.txt
Are you going to let the obstacles in
your life be stumbling blocks or
stepping stones? Choose the positive.
You are the master of your attitude.

       --Bruce Lee
```

### 5. Write a clone of the `cat` Unix utility.

Call this one `mycat.c`.

Don't use `printf()` or any of the other standard library output reading
or writing routines. (You may use `perror()` for printing error messages.)
Use `open()`, `read()`, `write()`, and `close()`.

This program reads from standard input (file descriptor `0`) or from the
files specified on the command line in order. It outputs whatever it
reads in.

Gameplan:

* Check how many files the user specified on the command line (check
  `argc`).
* If none, the input file descriptor is `0` (stdin). Use it.
* If some, loop through the files
  * For each, call `open()`, get the file descriptor, use it, then
    `close()` it

When I say "use it", what do I mean?

For each open file descriptor to process, you should repeatedly call
`read()` with it to get some data and `write()` on file descriptor `1`
(`stdout`) with that data. Until you reach the end of the input.

Quit your loop when `read()` returns `0` (end of file) or `-1` (error).

You can do this by reading one byte at a time, but that's inefficient.
Each syscall incurs overhead. It's better to read in, say, 2048 bytes at
once, then write however many you got. Check the return value from
`read()` to see how many bytes were actually read--unless your input is
a multiple of 2048 bytes, you'll get a short read at the end of the
file.

Output: if you run:

```
% ./mycat mycat.c hello.c
```

you should see the contents of those two files concatenated on the
screen.

If you run:

```
% ./mycat
```

you should see each line you type echoed until you hit `CTRL-D` (which
is how you send EOF from the keyboard in Unix).

### 6. Write a Utility that Turns Everything to UPPERCASE

**Copy** your `mycat.c` file into `yell.c`. These two utilities are
almost identical.

If you `#include <ctype.h>`, you'll get access to a function called
`toupper()` that returns the uppercase version of a single character.

Gameplan:

* Just like `mycat`, except after you read from the input, loop through
  the buffer converting every character to uppercase.
* Then write the uppercased buffer out, just like before.

Example output, piping `ls` output into `yell`:

```
% ls | ./yell
MAKEFILE
HELLO.C
INPUT.TXT
MYCAT
MYCAT.C
NODIGITS.C
PRINTCL.C
READFILE.C
YELL
YELL.C
```

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **56 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your submission.

## Extensions

Copy `mycat.c` into `nodigits.c`.

Write a `nodigits` program that strips any digits from the input when it
prints the output.

Hints:

* if you're using a buffer larger than 1 character (which you should be
  doing), try building another output buffer from the input buffer by
  ignoring digits. If there are digits, the output buffer will clearly
  have fewer bytes in it, something to consider when you're calling
  `write()`.

* In `<ctype.h>`, the `isdigit()` function returns true if the character
  is a digit.

Example output, piping `ls -l` into `nodigits` to strip all digits:

```
% ls -l | ./nodigits
total
-rw-r--r--   beej  staff     Dec  : Makefile
-rw-r--r--   beej  staff     Dec  : hello.c
-rw-r--r--   beej  staff     Dec  : input.txt
-rw-r--r--   beej  staff     Dec  : mycat.c
-rwxr-xr-x   beej  staff   Dec  : nodigits
-rw-r--r--   beej  staff    Dec  : nodigits.c
-rw-r--r--   beej  staff     Dec  : printcl.c
-rw-r--r--   beej  staff     Dec  : readfile.c
-rw-r--r--   beej  staff     Dec  : yell.c
```


