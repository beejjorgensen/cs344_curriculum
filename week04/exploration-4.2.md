<!-- Exploration 4.1: Caches, Multi-Core -->

## Caches

## Multi-Core

## Opening Files in Unix

We've already used `open()` to read files, like this:

```
int fd;

fd = open(filename, O_RDONLY);
```

and of course it makes sense that you can open files for writing, and
also create them if they don't exist.

If you do create a file with `open()`, you're going to also have to tell
it what the permissions on that new file are.

Let's look at an example where we open a file for writing, creating it
if it doesn't exist, and setting the file permissions if it is just
created.

```
int fd;

fd = open(filename, O_WRONLY | O_CREAT, 0644);
```

There are a couple things going on there.

```
O_WRONLY | O_CREAT
```

Flags passed to `open()` can be a bitwise-OR of a number of values. In
this case, we OR `O_WRONLY`  (meaning open only for reading) with
`O_CREAT` (meaning "create this file if it doesn't exist").

Lastly, what's that `0644`?

That's the file permissions. It's an octal number--that's what the
leading `0` tells the C compiler.

Here are the four most common numbers to see there:

* **`0644`**: user has read/write, group and other just have read
* **`0600`**: user has read/write, group and other have nothing
* **`0755`**: user has read/write/execute, group and other just have
  read/execute
* **`0700`**: user has read/write/execute, group and other have nothing

## Unit File Permissions and Octal

If you `ls -l` a file, you'll see something on the left that looks like:

```
-rw-r--r--
```

This shows permissions for User, Group, and Other (everyone else).

The letters stand for:

* `r`ead
* `w`rite
* e`x`ecute

If we draw it more fully, it looks like this:

```
-rwxrwxrwx
```

That's a triplet of `rwx`s. (The `-` on the left would be a `d` if this
file were a directory.)

Let's split them up:

```
user   group   other

rwx     rwx     rwx
```

Any place you see the letters means that user or group of users has that
particular permission. If you see a `-`, it means you don't. So:

```
r--
```

means you have read permission and that's all.

```
r-x
```

means you have read and execute permission, but no write permission.

Let's assume that "permission" is represented by a `1`, and "no
permission" is represented by `0`.

Here's a permission from `ls -l` with the `1`s and `0`s above, and
spaces added to break apart the three groups:

```
  110 100 100    binary
- rw- r-- r--
```

Recall that octal (base-8) is made of the digits 0-7. And 0-7 can be
represented by 3 bits, coincidentally.

So if we convert those binary values to decimal, we get:

```
    6   4   4     decimal
  110 100 100     binary
- rw- r-- r--
```

If we cram those together in an octal number, we get `644`. But C wants
us to put a `0` on the front of all octal numbers, so it becomes `0644`.

What's the octal permission for this?

```
-r-xrw---x
```

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Multi-CPU Scheduling](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-multi.pdf) sections 10.1-10.3
  
Here is a link to the interactive demo from that chapter,
[multi.py](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched-multi).

## Reflect

* Questions?
