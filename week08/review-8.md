## Summary

* A Translation Lookaside Buffer (TLB) can be used to cache virtual
  memory mappings for speed increases.
  translations for different processes, avoiding the need to invalidate
  the entire cache.
* TLBs can be completely within hardware, or they can be
  software-controlled.
  * If software-controlled, the CPU will issue a trap/interrupt which
    the OS will handle by setting up the TLB correctly.
* The TLB also needs a copy of the protection bits for a particular page
  so it can avoid needing to hit the real page table for that
  information.
* Context switches with a TLB are interesting because the switched-in
  process might not have any mappings yet in the TLB, slowing things
  down at first.
  * If you had to clear the TLB every time there was a process switch,
    it would be prohibitive.
  * Some TLBs use ASIDs to tag entries as being associated with a
    particular process.
* Since most virtual address space is unused for a typical process, it
  makes no sense to reserve that space in a page table. Multi-level page
  tables solve this problem.
  * The complexity is higher and speed is lower, but the memory saving
    tradeoff is worth it.
* Although you can't _compact_ blocks in your `myalloc` system (because
  it would move pointers behind the users' backs), you can _coalesce_
  neighboring free blocks into a single, larger block.
  * This mitigates the problems arising from external fragmentation.
