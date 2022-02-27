[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

What's the main function of the page table?

Maps a process's virtual addresses to physical addresses.

Maps a process's physical addresses to virtual addresses.

Maps a process's physical addresses to other physical addresses.

Maps a process's virtual addresses to other virtual addresses.

---

The physical pages a process uses must be consecutive and in order. (5)

False

True

---

How many page tables on any particular system?

One per process.

Up to 64 maximum.

Depends on how much virtual memory there is.

Depends on how much free disk space there is.

---

How is an address space split into pages?

Each page is a fixed size and the page number is in the high bits of the address.

Each page is a fixed size and the page number is in the low bits of the address.

Each page is a variable size and the page number is in the high bits of the address.

Each page is a variable size and the page number is in the low bits of the address.

---

When mapping from a virtual address to a physical one, how is the offset within the page computed?

The offset in the virtual page is the same as the offset in the physical page.

You shift the address right to compute the physical offset.

You shift the address left to compute the physical offset.

You bitwise OR the page number with the virtual offset to compute the physical offset.

---

What happens when main memory is full and a new process needs to allocate more?

Some of the used memory is swapped out to disk.

Some swapped out memory is brought into main memory.

The out-of-memory killer kills the process.

The new process's page's dirty bits are set.

---

A page's "present" bit is used to indicate:

Whether or not a mapped virtual page is in memory or swapped out to disk.

Whether or not a particular virtual page is mapped to a physical page.

Whether or not a particular virtual page has been modified since it was swapped in from disk.

Whether or not a particular physical page exists.

---

In regards to FIFO swapping policy versus Least-Recently-Used (LRU):

FIFO has the advantage of simplicity of implementation.

FIFO generally has a better hit rate.

LRU has the advantage of simplicity of implementation.

FIFO and LRU offer comparable hit rates.

---

The main reason we'd use an approximate LRU policy over and LRU policy is:

LRU is computationally prohibitive and approximate LRU is not.

Approximate LRU gives a better hit rate than LRU.

LRU uses less disk space than approximate LRU.

Approximate LRU uses less disk space than LRU.

---

What are the high watermark and low watermark used for?

When the amount of free physical memory falls to the lower watermark level, pages are swapped out until it returns to the high watermark.

When the amount of free virtual memory falls to the lower watermark level, pages are swapped out until it returns to the high watermark.

The high watermark is the most physical RAM we're allowed to use; the low watermark is the least.

The high watermark is the most virtual RAM we're allowed to use; the low watermark is the least.
