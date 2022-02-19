<!-- Exploration 8.2: Multi-Level Page Tables -->

## Improving Page Table Memory Size

If you have _n_ pages of memory (e.g. 4 million), and each page table
entry takes up a certain amount of size (e.g 4 bytes), that's a lot of
memory (eg 16 megabytes) used for a process's page table.

Multiple by a lot of processes running on your system (e.g. 200) noq
we're talking a _metric ton_ of space used just for page tables (e.g.
3.2 GB).

The real crime here is that _most of those entries in the page table are
unused_.

Even though a process has the entire virtual address space to itself,
that doesn't mean it's using it all. Only a few of those virtual address
pages are actually mapped to physical memory. The rest are unused.

So let's see how we might tackle some of this waste.

A couple quick suggestions are:

* Bigger (thus fewer) pages
* Combine paging with segments

But really what people use these days are multi-level page tables.

### Multi-level Page Tables

The idea with these is that we'll split our page table into page-sized
chunks.

Each chunk still performs the same function: map from a virtual address
to the corresponding physical address. And each chunk is responsible for
a partial range of the entire virtual address space.

The only question is, which chunks of the page table are in use, and
which ones aren't?

If an entire chunk of the page table isn't in use by the process
(because it has nothing in that particular part of virtual memory),
there's no need to even allocate that part of the page table.

In other words, the page table can be missing for giant sections of the
virtual address space, and there's no harm. We only need the parts of
the page table that correspond to actual in-use virtual memory space.

And that's some space savings.

But there has to also be a part of the system that tracks which parts of
the page table are where. Now that the page table is no longer a
continuous array, we need to keep pointers to the individual pages that
hold it.

The _page directory_ keeps track of which parts of the page table are
(at least partially) in-use. That is, which parts of the page table
actually exist.

The directory is a listing of all possible chunks of the page table, in
use or not. Each entry has a "valid" bit that indicates if any
particular chunk of the page table exists, and a physical address of
where that page table chunk is if it does exist.

Since each chunk of the page table can holds many virtual mappings, the
directory can be smaller by that same factor.

The trade-off is that now we have to do two memory lookups for each
address translation. But the space savings makes it worth it.

So worth it, in fact, that some systems have more than two levels
(like Intel's [5-level
paging](https://en.wikipedia.org/wiki/Intel_5-level_paging)),
realizing even more space savings at the expense of more memory accesses
per translation.

Even with those slowdowns, though, the TLB can make things fast enough
to be worth it.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Advanced Page Tables](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-smalltables.pdf)
  
## Reflect

* What are some advantages and disadvantages of multi-level page tables?

