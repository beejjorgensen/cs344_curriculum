<!-- Exploration 10.1: VAX/VMS Virtual Memory -->

## Virtual Memory on the VAX

The VAX is a venerable old platform now woefully obsolete, a pioneer in
the space of virtual memory, however.

If your instructor is old enough, they might have used one of these
machines in the late 1980s-early 1990s.

### Overview

* Virtual address space: 32 bits, addresses 0x00000000-0xfffffffff.
* Page size: 512 bytes.

To represent offsets in a 512-byte page requires 9 bits (encoding values
0-511).

Above that, we find 23 bits of virtual page number (VPN). The upper 2
bits of the VPN encoded the segment--a segmented/paged hybrid.

Bit layout of a VAX virtual address:

```
  3         2         1
 10987654321098765432109876543210
+--------------------------------+
|aaAAAAAAAAAAAAAAAAAAAAAOOOOOOOOO|
+--------------------------------+

a: segment bits
A: virtual address bits
O: offset bits
```

The virtual address space was split in half.

* Low half: per process virtual pages
  * Stack, heap, program instructions, etc.
* High half: shared OS code and data

When a context switch occurs, the OS data pages don't change; all
processes are looking at the same OS data.

Having the OS in the same virtual memory space as the user programs also
gives it access to user data on a system call (e.g. if a user passes a
pointer to some data in a syscall).

The CPU supports protection levels in the page tables that keep user
processes from directly accessing the OS pages.

### Page Table Size Mitigation

If we have 0x100000000/2 addresses and 512-byte pages, the gives us
4,194,304 pages, and that many entries in each page table. This is
unreasonably large, even though we only have to do it for the
per-process lower half of virtual memory.

To fix, the per process virtual space was split into 2 segments:

* Low segment grows upward (code and heap)
* High segment grows downward (stack)

No page table entries were necessary between the two segments, saving
that space.

Additionally, the page tables themselves were stored high in OS virtual
memory, keeping that area free in the per-process address space.

A drawback of doing so is that the OS has to keep an additional table to
keep track of all the page tables, adding an additional memory access
and level of indirection for virtual address translations.

One of those common trade-offs: space for speed, or vice versa.

To mitigate the drawbacks of _that_ mitigation, the VAX also has a
hardware TLB to speed things up.

### Swapping

Each process had a limit on the number of pages it could use. A FIFO
scheme was used per-process to evict pages.

To overcome the performance limitations of FIFO, two "second-chance"
queues were added so that the OS would be even more sure it was good
decision to evict a page. (That is, it wouldn't be immediately needed
right after swapping it out.)

### Demand Zeroing, Copy on Write

When you get a page from the OS, it would be nice for it to be full of
zeros, and not full of some other process's old data.

But it takes time to zero a page, and the OS can be a bit more
performant if it does this in a _lazy_ manner.

There's no point in zeroing a page before a process tries to read from
it, so the OS doesn't do that. It sets the permissions so the process
can't read from that page.

When a process tries, the OS traps, _then_ it zeros the page and sets
permissions to allow the process to read it.

A similar optimization is _copy on write_. The VAX and every modern OS
uses this technique.

Recall that in Unix when you `fork()` a process, it makes a copy of the
page table, but doesn't actually copy any of the underlying physical
pages. The child process's virtual pages map to the exact same physical
pages as the parent process's do.

But does this mean that if the child writes to the page, the parent will
see those changes? No.

After the `fork()`, the OS marks the page for the parent and child as
read-only.

So they can both read from it, no problem.

But if the parent or child tries to write, it doesn't have permission,
and the OS traps. And _then_ the OS makes a copy of the page for the
writing process to use.

This is why `fork()` is relatively cheap even though it effectively
makes a "copy" of the parent process's data. No copy is made until a
process attempts to write to memory.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Complete VM Systems § 23.2-23.3](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-complete.pdf)

## Reflect

* What would happen on a `fork()` without copy-on-write?
* What advantage does VMS gain by having the top two virtual address
  bits be segment identifiers?
* The page table entries in VMS didn't have a reference bit--which is
  normally the way you'd tell if a page was in use. How did VMS get
  around this limitation?

