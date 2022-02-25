## Summary

* When the OS runs out of physical memory, it can swap pages out to
  disk.
* There are a number of swap policies that the OS can use to decide what
  to swap and when.
  * E.g. FIFO, LRU, approximate LRU.
  * These different policies have different benefits and drawbacks.
  * Swapping out the page that will be used furthest in the future is
    optimal, but it's virtually impossible to predict this.
* When a process accesses a virtual page for which the backing physical
  memory has been swapped out, a page fault occurs.
* The OS handles page faults and brings the swapped-out page back into
  RAM so the owning process can continue running.
* The OS can be proactive about moving pages in and out of swap to
  improve performance.
* Thrashing occurs when physical memory is heavily overcommitted; that
  is, when the total number of pages needed by all ready-to-run
  processes greatly exceeds the total number of pages in physical
  memory.

