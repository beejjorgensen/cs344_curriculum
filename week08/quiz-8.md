[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

Why is a translation lookaside buffer (TLB) useful with a paged virtual memory system?

Repeated memory lookups in the page table are slow; the TLB acts as a cache.

It saves space, replacing a flat page table with a tree-like structure.

It enables you to specify ranges of virtual memory addresses that are in-use.

It is responsible for mapping virtual addresses to physical addresses and back.

---

A hardware translation lookaside buffer (TLB):

Hides the details of the cache from the OS and user-space programs.

Partially relies on the OS to manage the cache.

Partially relies on userspace processes to manage the cache.

Is used in processors like the SPARC V9 and the MIPS R10000.

---

A software translation lookaside buffer (TLB):

Partially relies on the OS to manage the cache.

Hides the details of the cache from the OS and user-space programs.

Partially relies on userspace processes to manage the cache.

Is commonly used in Intel processors.

---

Context switches with translation lookaside buffers (TLBs) are problematic because:

The page mappings from one process are typically not those of another, and the cached mapping are invalid after the switch.

Lookups in the cache will run more slowly after a context switch.

Each context switch uses memory that would normally be used for page tables.

TLBs cannot be used with multi-level page tables and context switching.

---

An address space identifier (ASID) is used to:

Logically partition the TLB space among several processes.

Mark which page table this TLB belongs to.

Identify the type of memory used by this process.

Define which segments are associated with with which programs.

---

Protection bits are required in the translation lookaside buffer (TLB) because:

Virtual mappings from the TLB that bypass the page table still need to know the permissions on the pages.

Without permissions processes might be able to access other process's pages.

When a user logs in, permissions must be checked to access disk resources via the TLB.

If a page fault occurs, the permissions need to be checked to see if a mapping is allowed.


---

If two processes are both running the same program, what can a paged memory system do to save memory?

Different virtual pages in the two processes can point to the same physical page.

Different physical pages in the two processes can point to the same virtual page.

Hand the physical pages to the processes in a first-come-first-served manner.

Direct you to your nearest RAM dealer.

---

The main benefit of a multi-level page table is: (5)

Saves space.

Runs faster.

---

The main drawback of a multi-level page table is: (5)

Runs slower.

Uses more space.

---

If we didn't coalesce free space with our memory allocator:

External fragmentation would increase as the available contiguous regions decreased in size.

Internal fragmentation would increase as the available contiguous regions decreased in size.

External fragmentation would increase as the available contiguous regions increased in size.

Internal fragmentation would increase as the available contiguous regions increased in size.

---

