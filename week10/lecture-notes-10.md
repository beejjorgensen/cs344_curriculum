# Day 1

VAX/VMS

# Day 2

Linux

Virtual address space

Kernel (logical) mapped 1:1 to physical
* Contiguous physical memory useful for certain hw ops, DMA
* 1 GB total

Kernel (virtual) typical page mapping
* Enables more memory to be used since it can be mapped anywhere
  * Not just in the 1 GB stretch of logical

4-level page table
* 281,474,976,710,656
* 256 TB RAM supported

Large page support
* Fewer page table entries
* Better TLB usage for large programs
* Internal fragmentation -- unused portions

Page Cache, buffer cache
* Keep pages in memory from disk for quick access
* 2Q LRU-ish

Buffer overrun
* Return attacks
* ASLR


