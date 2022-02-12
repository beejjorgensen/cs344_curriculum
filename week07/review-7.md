## Summary

* Memory managers suffer from internal and external fragmentation.
* External fragmentation and compaction can be mitigated by using
  allocations that are the same size.
* You can coalesce adjacent free chunks of memory in a `malloc()`-style
  allocator to mitigate external fragmentation to an extent.
* Paging offers more flexibility than other virtual memory systems, at
  the expense of additional memory usage.
* The page table is a data structure that allows the CPU to perform the
  mapping between virtual addresses and physical addresses.
* Although compaction does a great job of handling external
  fragmentation, we can't use it with `malloc()` because the user isn't
  expecting their allocated memory regions to move.
* When mapping from a virtual address to a physical page, the virtual
  address is split into two parts:
  * The high bits are the virtual page number. The looking up this index
    in the paging table gives you the physical frame number that it maps
    to.
  * The low bits are the offset in the page. This offset is the same in
    the virtual page as in the physical page.
* There are different strategies for a `malloc()`-style system to
  choose the next free block, with trade-offs for each.
  * First-fit
  * Next-fit
  * Best-fit
  * Worst-fit
* As with all virtualization aspects of the OS, all processes are
  unaware of their location in physical memory. All they see is their
  own big virtual address space.
