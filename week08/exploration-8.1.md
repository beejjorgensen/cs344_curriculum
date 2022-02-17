<!-- Exploration 8.1: Translation Lookaside Buffers -->

## Translation Lookaside Buffers

With paged virtual memory, each virtual address must be mapped to the
corresponding physical memory address.

This happens by consulting the _page table_, which has the mapping from
each virtual memory page to its corresponding physical memory page.

But since there are a _lot_ of pages (my computer has 4,194,304 of
them), the page tables have to be stored somewhere in memory (not in
registers).

This means in order to do a conversion from a virtual to physical
address, a memory access must happen to look up the mapping in the
page table _before_ we can look up the data in the address we were
interested in.

That's two memory accesses for the price of one! This, unfortunately,
isn't a good thing; each access costs us time.

> In reality, there could be many more accesses to find the mapping, as
> with Intel's [5-level
> paging](https://en.wikipedia.org/wiki/Intel_5-level_paging).

But assuming we're frequently doing a lot of accesses near one another,
one thing we could do is _cache_ those commonly-used mappings from the
page table where they're quicker to look up.

Enter the Translation Lookaside Buffer (TLB). It's a cache that does
exactly that.

When a process accesses a virtual address, first the TLB is checked to
see if the mapping is there. If it is, the math is done to get the
physical address and the lookup and proceed.

If the mapping isn't in the TLB, then the hard work has to be done. The
page table will be consulted and then that value is loaded into the TLB
for use.

### Hardware versus Software-Supported TLBs

Often the hardware is capable of doing the TLB management itself without
any software support at all. This has the advantage of being transparent
to software; if there's a TLB miss, the software won't even know except
that things were a bit slower.

However, this doesn't leave the option of using a variety of different
data structures to store the page table--it must match what the hardware
is expecting.

To be more flexible and to reduce the complexity (and cost) of the CPU,
some chips rely on software to do the translation. In this case, the CPU
issues a trap when a TLB miss occurs. The OS handles it, performs the
translation in whatever way it sees fit, loads the translated address
into the TLB, and returns control to the process. The process can then
do the virtual memory access without issue because the mapping is now in
the TLB.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Translation Lookaside Buffer](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-tlbs.pdf)
  
## Reflect

* What is the purpose of the protection bits on the TLB?
* Since the mappings in the page table for one process are different
  from those for another, what happens to the TLB during a context
  switch? What are some options?
* Why would two different virtual page numbers (VPNs) in two different
  processes point to the same physical frame number (PFN)?
* What happens when the TLB is full and we have to put still more things
  in it?
* The book poses the question of what happens when you have more than
  256 processes running at a time on a MIPS R4000 processor (i.e. every
  possible ASID is used and you need more). What options might the OS
  have to handle this?
