<!-- Exploration 10.2: Linux Virtual Memory -->

## Linux Virtual Memory

You'll probably recognize some similarities between the old VMS systems
and modern Linux systems in terms of memory layout.

One interesting aspect is the permanently-mapped logical kernel memory.

* Holds kernel data structures, page tables, etc.
* Can't be swapped out.
* Maps to contiguous physical memory.
  * Makes it easier to work with larger chunks of memory that span
    pages, since you know the physical pages are contiguous.

By contrast, kernel virtual memory is mapped to discontinuous physical
pages, just like per-process virtual memory.

### Page Tables

The book (2018) notes that a 4-level page table is used that doesn't pay
attention to the high 16 bits of the virtual address (effectively making
that virtual address space unusable.

But that's not too bad, since a 48-bit address space is still 262,144
GB.

### Large Pages

x86 supports 4 KB, 2 MB, and 1 GB pages, even supporting different page
sizes at the same time.

The kernel can intelligently choose the page size.

### The Page Cache

Data from disk is cached in RAM by Unix-like systems. And usually a lot
of it. Most of your otherwise-would-be-free memory ends up as part of
the page cache.

If you read a byte from a file, a page of data from the file will be
stored in the page cache. Subsequent file accesses won't go to the
disk--they'll just use the cached data page.

Of course, that's a bummer when the power fails and you just have your
changes written to RAM and they haven't been flushed out to disk yet.

There's a syscall (`sync()`) that forces the data to be saved; a
background process called `pdflush` does this periodically.

If you start running low on memory, the kernel will start flushing the
cache out to use the memory for other more important things.

### Security

As you know from the many crashes you've experienced with C, there's not
really a lot preventing you from accessing data outside the bounds of an
array.

Malicious hackers have figured out ways to use this to gain entry into
your systems by adding executable code to their input and overrunning
buffers in very specific ways.

One mitigation is that modern CPUs allow you to mark data pages as
non-executable, so if this attack is tried, the OS traps and stops it.

So if the malicious hackers can't load instructions into the data space,
they have to use the existing instruction space, which is read-only. So
they hunt for bits of code that do their bidding followed by RET
instructions. They _can_ write to the stack, so they set the return
address to the next piece of code they want to run, chaining them
together.

To do that, they need to know the exact address to return to. And if the
program always runs in the exact same part of virtual memory, they just
figure out those addresses and code them into their exploit.

To mitigate, Linux uses _address space layout randomization_. This makes
the stack appear in different places in virtual memory from run to run,
so the attacker can't hardcode return addresses to stick on the stack.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Complete VM Systems § 23.1](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-complete.pdf)

## Reflect

* Why is Linux's kernel virtual memory less useful with 64-bit systems
  than it is with 32-bit?
* What are some drawbacks of using 4 KB pages?
* What are some drawbacks of using large pages?
* How cool is the Spectre attack?

