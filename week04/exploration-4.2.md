<!-- Exploration 4.1: Caches, Multi-Core -->

## Caches

The cache is fast, expensive (in currency), small memory that sits close
to (or on) the CPU. This is useful for performance, because going all
the way across the motherboard to regular slow, cheap, large RAM to get
data takes a while.

The cache works on the assumption that if you asked for a particular
byte in memory, you're likely to ask for subsequent bytes after that. So
the cache might as well just make one request out to RAM to get a bunch
of bytes and keep those on-hand for those presumed subsequent reads.

Caches usually have a hierarchy of "levels", but for our purposes, we
can just assume the cache is a small, fast copy of a subportion of RAM.

## Multi-Core

Some older systems had multiple CPUs on the motherboard, with varying
degrees of shared hardware resources.

Today, we have _multi-core_ processors. This will be a CPU package that
has multiple CPU "cores" in it. It's like having a CPU that's made up of
2 or 4 or 8 or more CPUs.

And each of those cores can run a program at the same time the others
are running programs.

This is great for performance. If you can run eight things at once,
that's way better than just being able to run one thing at once.

Each of the cores has its own registers. And, typically, its own cache.

## Multi-Core and Caches

If the cache holds a copy of some RAM, and each core has its own cache,
what are some of the problems that can arise?

If one core writes to a cache, when does it appear in RAM? When does it
appear in the other caches?

Could a program on one core write to its cache and then another program
on another core reads from the same location in _its_ cache... and have
the second program get "stale" results? (That is, it reads the old value
instead of the new one that was just written.)

This is the issue of _cache coherence_. And we'll get more into that at
a later time.

As programmers, we can use a concept called _synchronization_ to deal
with this, guaranteeing that writes made on one core will be visible to
reads from another core.

And more on that later, as well.

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

fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
```

There are a couple things going on there.

```
O_WRONLY | O_CREAT | O_TRUNC
```

Flags passed to `open()` can be a bitwise-OR of a number of values. In
this case, we OR the following flags together:

* **`O_WRONLY`**: open only for writing
* **`O_CREAT`**: create this file if it doesn't exist
* **`O_TRUNC`**: if the file did exist, truncate it to zero bytes long

You could leave off any of the modifier flags if it were appropriate for
your use case. But most people are accustomed to the `O_CREAT|O_TRUNC`
behavior when they open a file for writing.

Lastly, what's that `0644`?

That's the file permissions. It's an octal number--that's what the
leading `0` tells the C compiler.

Here are the four most common numbers to see there:

* **`0644`**: user has read/write, group and other just have read
* **`0600`**: user has read/write, group and other have nothing
* **`0755`**: user has read/write/execute, group and other just have
  read/execute
* **`0700`**: user has read/write/execute, group and other have nothing

More details are in the next section.

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
    6   4   4     decimal/octal
  110 100 100     binary
- rw- r-- r--
```

If we cram those together in an octal number, we get `644`. But C wants
us to put a `0` on the front of all octal numbers, so it becomes `0644`.

What's the octal permission for this?

```
-r-xrw---x
```

Answer at the bottom of this page.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Multi-CPU Scheduling](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-multi.pdf) sections 10.1-10.3
  
Here is a link to the interactive demo from that chapter,
[multi.py](https://github.com/remzi-arpacidusseau/ostep-homework/tree/master/cpu-sched-multi).

## Reflect

* Questions?

Answer to the permissions question: `0561`.