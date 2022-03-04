[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

In the project, how many memory accesses does it take to map a virtual address to a physical one?

Two. One to get the page table page number, and one to get the physical page from the page table.

One. Just need to get the page table number.

One. Just need to get the physical page number from the page table.

Three. One to get the virtual page number, one to get the page table page number, and one to get the physical page number.

---

In the project, a process that requests two data pages will use in total:

Three physical pages

One physical pages

Two physical pages

Four physical pages

---

Why did VAX/VMS use a hybrid segmented/paged virtual memory system?

The segmentation was used to save on page table size.

The paging was used to save on segment size.

The hybrid is faster than a flat page table.

To avoid buffer overrun attacks.

---

How does the OS handle NULL pointer accesses?

Page zero is invalid, so the OS traps and produces a segfault.

The OS checks each memory access to see if the pointer is NULL.

The program is put on page zero, so overwriting address 0 causes it to crash.

It doesn't. The program might crash, or it might not.

---

Why did VMS implement the two second-chance FIFO queues?

A single FIFO is not performant; this gives pages more time before being evicted.

Three total queues spread the page load out over the number of processes.

More queues were needed to represent all physical pages on the VAX.

More queues were needed to represent all cirtual pages on the VAX.

---

When a Unix system forks a new process:

The page table is copied, but memory pages aren't copied until they're written to by the child.

The page table is copied, along with all memory pages.

The page table isn't copied, and neither are the memory pages, until they're written to by the child.

The page table isn't copied until written by the child, but the memory pages are.

---

In a modern Linux system, for a user process, practically speaking:

Stack overflow can never occur since there's not enough pages of physical RAM to bridge the gap between the stack and heap.

Stack overflow can occur with large pages.

Stack overflow can sometimes occur, if the system is running low on virtual memory.

Stack overflow can never occur since the stack and heap grow away from each other.

---

One of the problems with larger pages is:

Internal fragmentation

External fragmentation

Slow access

Large page table sizes

---

The main job of the page cache is:

To keep pages of data from secondary storage ready in memory for quick access.

To hold instructions close to the CPU for faster execution.

To hold mapped physical addresses so that the CPU doesn't have to consult the page table again.

To hold web pages so your browser doesn't have to get them over the network again.

---

The No-Execute bit set on a page is used to:

Prevent buffer overrun attacks.

Prevent return-oriented programming attacks.

Prevent Spectre attacks.

Prevent Meltdown attacks.


