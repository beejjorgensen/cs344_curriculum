[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

What problems can arise when repeatedly allocating and freeing small amounts of memory with malloc()?

External fragmentation can occur.

Page tables can fill up.

Virtual memory can become exhausted.

No problems will arise.

---

When splitting a new free block with our `myalloc()` system, some of the space becomes unusable in the future. Why?

Some of the remaining space must be used for the new block's metadata.

External fragmentation occurs.

Because we have to consolidate blocks before we split them.

More space in the OS's page table gets used.

---

Our myfree() implementation allows users to pass any pointer in even if it wasn't returned by myalloc() earlier. A magic number could be used to help detect this. How?

We test to see if the magic number is in a known positiion adjacent to the given pointer.

We test to see if the magic number is in the corresponding page table entry.

We test to see if the address is a multiple of the magic number.

We test to see if the magic number has vanished.

---

If we tried to use compaction with our myalloc() implementation, what would happen?

The blocks of data would be moved around and users of the values from myalloc() would not be able to find their data.

The blocks of data would be moved around and users of the values from myalloc() would have their pointers updated to the new values.

Only unused blocks of data are rearranged with compaction so the user wouldn't notice anything.

Only allocated blocks of data are rearranged, and their pointers are kept updated.

---

The page table maps:

A virtual page number to a physical frame number.

A virtual address to a physical frame number.

A physical frame number to a physical page number.

A physical address to a virtual frame number.

---

To compute the physical frame offset from the virtual memory offset:

Use the virtual memory offset as-is.

Right shift the virtual memory offset by 5.

Bitwise-AND the offset with the PFN.

Bitwise-OR the offset with the PFN.

---

Compared to base/bound, paging:

Suffers less from fragmentation, uses more memory, and is slower.

Suffers less from fragmentation, uses more memory, and is faster.

Suffers more from fragmentation, uses more memory, and is slower.

Suffers more from fragmentation, uses more memory, and is faster.

---

The "valid" bit in a page table entry:

Keeps track of whether or not a particular virtual page is mapped to a physical page.

Keeps track of which physical pages are not in use.

Keeps track of which virtual pages need updating from RAM.

Keeps track of which virtual are fragmented.

---

[5]

Unlike base/bounds, in a paging system all virtual memory segments must be contiguous.

False

True

---

What advantage might the next-fit strategy have over first-fit?

Spreads the allocations out more evenly over the list instead of favoring the front.

Keeps the allocations near the end of the list so the front remains unfragmented.

Keeps the allocations near the head of the list so the end remains unfragmented.

Next-fit runs faster than first-fit.
