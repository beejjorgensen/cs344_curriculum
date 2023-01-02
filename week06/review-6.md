## Summary

* There are multiple approaches to virtualizing memory, each with their
  own benefits and drawbacks.
  * Base/bound: entire program is contained in a contiguous stretch of
    physical memory, remapped to virtual address space.
  * Segmented: Segments of the program (instructions, heap, etc.) are
    in independent contiguous sections of physical memory.
  * Fine-grained segmented: small sections of physical memory are
    remapped to virtual address space. Maximum complexity, maximum
    flexibility.
* Memory fragmentation occurs when large sections of free memory are
  frequently interrupted by in-use memory, making it difficult or
  impossible to allocate additional large chunks.
* Alignment: memory accesses often must occur starting on addresses that
  are multiples of a certain number.
  * This is architecture-dependent.
  * Misaligned reads might, depending on the architecture:
    * Cause exceptions
    * Run slower
    * Produce bad data
    * Work just fine
* `malloc` implementations in the C standard library commonly allocate
  space on the heap with the `mmap()` system call, then manage that
  space at the request of the process using it.
