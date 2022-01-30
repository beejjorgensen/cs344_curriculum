[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

What is one of the challenges of having multiple programs in memory at the same time?

The memory needs to be protected so that other processes can't trample on each other.

The OS won't be able to run more programs than there is available physical RAM.

Scheduling multiple processes becomes more difficult.

I/O works better when there is a single program in memory.

---

What is the address space of a process?

It's the range of memory addresses visible to a process.

It's how much memory the process needs to run.

It's a range of addresses in physical memory.

It's the memory returned by malloc().

---

With virtual memory:

Each process thinks it has the entire address space of the computer to itself.

Each process knows its starting and ending address in physical memory.

Each process lives in the same address space, organized safely by the OS.

Each process has its own memory, but shares a heap.

---

What is the relationship between virtual addresses and physical addresses?

Virtual addresses map to physical addresses as controlled by the OS.

Virtual addresses map to physical addresses as controlled by the process.

Virtual addresses match exactly to the same physical addresses.

The more physical addresses you have, the more virtual addresses you can have.

---

Where are automatic variables allocated?  (5)

Stack

Heap


---

Where is data stored when allocated with malloc?  (5)

Heap

Stack

---

What's an automatic variable in C?

A local variable that's allocated on the stack, freed when the enclosing block exits.

A local variable that's allocated on the heap, freed when the enclosing block exits.

A local variable that's allocated on the heap, freed when you call free().

A local variable that's allocated on the heap, freed when the function exits.

---

How does memory leak?

You malloc some memory and don't free it.

You malloc some memory and free it more than once.

You free memory without malloc'ing it.

You forget to malloc memory before using it.

---

When it OK to access memory just beyond the end of an allocated array?

Never.

As long as you're only one or two past the end.

As long as you're only reading data, not writing it.

As long as there's enough free memory past the end.

---

It's OK to access freed memory as long as you do it immediately after the free() call. (5)

False

True

---

The earliest time leaked memory is returned to the system is

When the leaking process exits

When the leaking process is adopted by init

When the system is rebooted

When you buy more RAM

---

When you malloc() in Unix, under the hood the library uses these syscalls:

brk() or mmap()

calloc() or realloc()

brk() or calloc()

mmap() or realloc()
