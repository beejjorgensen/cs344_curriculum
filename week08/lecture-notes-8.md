# Day 1

* Project

* Review Page tables
  * Note one page table per process

* Translation Lookaside Buffers
  * Jump to first image and use it as an example
  * Run examples, hit, hit, hit, hit, miss

* Hardware TLB handler x86
* Software TLB handler RISCy
  * Have an interrupt occur
  * OS can use whatever structure it wants for the TLB

* What about context switches?
  * TLB is only good for a single address space mapping
  * What to do?
    * Flush it?
    * Tag with a "address space ID"

# Day 2

Multi-level Page Tables

