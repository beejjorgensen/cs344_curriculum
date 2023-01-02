<!-- Exploration 5.1 Process Memory Allocation -->

## Rules About Memory Allocation in C

When I say `malloc()`, below, I mean `malloc()` or any variant like
`calloc()`.

Here are the rules:

* For each `malloc()`, there must be one `free()`.
* You may not access data after it has been `free()`d.

And here are some consequences of those rules:

* You shouldn't `free()` memory multiple times. Just once.
* If you don't `free()` memory, it is _leaked_ and cannot be used by any
  process until your process dies.
* If you lose the pointer to the memory region (returned by `malloc()`),
  you cannot `free()` it, so it is leaked.

## Memory Allocation from the OS

There are a couple common ways of getting more RAM straight from the OS:

* `brk()` system call: puts more room at the end of the data segment by
  setting the _break_--the lowest address in the process's data segment.
  On some systems, there is no way to free this memory, but a process
  can reuse the memory it already has allocated.
  
  > Note that on some systems (e.g. MacOS) the `brk()` call is
  > deprecated. And if you use it **and** the C standard library I/O
  > functions (e.g. `printf()`), you're liable to be stepping on C's
  > toes.

* `mmap()` system call: "memory map" a section of memory for general
  purpose use. This can be freed with `munmap()`.

  > `mmap()` is actually more capable than that--you can use it to map a
  > file into a section of memory. But for our purposes we will just ask
  > the OS to give us an _anonymous_ section of memory that's not
  > associated with any file. Then we can use this memory for whatever
  > we want.

Under the hood, `malloc()` use one or the other or both of those
syscalls.

Since a syscall has overhead, it's common for `malloc()` to `brk()` or
`mmap()` a significant chunk of memory when it needs it, then it manages
subchunks of that memory over various `malloc()` and `free()` calls.
This has the advantage that most of that memory management takes place
in user space and no context switch to kernel mode is necessary when
`malloc()` and `free()` are used.

But since that memory might not be able to be freed from the system
(there's no `unbrk()` call), if the user tries to `malloc()` a large
chunk of RAM, `malloc()` might opt to call `mmap()` for that, instead.
It's more overhead, but `free()` will be able to `munmap()` the data and
give it back to the system later.

Trade-offs.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Memory API](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-api.pdf)
  
## Reflect

* If I've made 5 memory allocations with `malloc()`, how many times
  should I call `free()`?
* What's the difference between getting memory from `malloc()` and
  getting it from `mmap()`?
* What is a memory leak? How is it caused?

