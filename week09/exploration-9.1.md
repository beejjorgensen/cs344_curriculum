<!-- Exploration 9.1: TODO -->

## Swapping

If you've set up a Unix system at any point, you might have been given
the option of setting up a swap partition or swap file. We'll talk here
about what that is and why we need it.

Let's say you have 8 GB of physical RAM, and you're running 200
processes. Each process requires an average of 100 MB (0.1 GB).

This means the total memory required for all processes is 20 GB. And the
system keeps running just fine.

But you only have 8 GB of physical RAM! How do you put 20 GB of stuff in
8 GB RAM?

Answer: you don't. When physical memory fills up, you _swap_
uncommonly-used pages by writing them out to disk.

This is very slow, of course, so it typically happens with sleeping
processes.

When the sleeping process wakes up, maybe it tries to use a page of
memory that was swapped out to disk. This is called a _page fault_. The
OS handles the page fault by going out to disk and loading the page into
physical RAM.

It then sets the _present_ bit for that page in the process's page table
and set it ready-to-run. The present bit indicates whether or not a
particular page of memory is _actually_ in RAM, or if it's not present
in RAM, i.e. swapped out to disk.

On a Unix-like, running `free -h` will show you the amount of RAM and
swap you have and is free:

```
       total     used     free   shared  buff/cache   available
Mem:    15Gi    5.8Gi    1.2Gi    1.7Gi       8.4Gi       7.5Gi
Swap:  2.0Gi     32Mi    2.0Gi
```

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Swapping Mechanisms](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys.pdf)

## Reflect

* TODO
