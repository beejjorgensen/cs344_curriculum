<!-- Exploration 7.2: Paging: The Modern Era -->

## Paging: The Modern Era

We've looked at some earlier attempts at setting up virtual memory, and
now we'll check out the one commonly used today: paging.
 
With paging, we offload some of the complexity of virtual addressing
onto the (now more capable) CPU, thus lessening the complexity of what
needs to be done from the OS's perspective.

The idea is that we'll have memory split up into fixed-sized pages (for
example, 4096 bytes) that the OS can map to a virtual address space. The
physical pages don't have to be contiguous with one another in any way.
And they are fungible.

* **Page Table**: A per-process data structure that maps the process's
  virtual page addresses to physical ones. Each entry in the table will
  contain an address mapping and several flags that describe the state
  of the mapped RAM.

* **Page Frame**: A page of physical memory.

The virtual address itself is split into two pieces:

* **Virtual Page Number**: these bits indicate which which virtual page
  we're on.

* **Offset**: the offset within the page we're interested in.

The virtual page number is used by the page table to figure out which
physical frame number is at this address.

The offset is fed through as-is from the virtual address to the physical
one.

There are some problems with the simple page table algorithm that this
chapter uses--subsequent chapters will attempt to address these
problems.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Introduction to Paging](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-paging.pdf)
  
## Reflect

* What is the benefit of fixed-sized pages in regards to fragmentation?

* What are some of the advantages that base/bounds has over paging (as
  described in this chapter)?

* What are some of the advantages that paging (as described in this
  chapter) has over base/bounds?

* What are some of the flags that are kept per-entry in the page table?
