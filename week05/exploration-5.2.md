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

* `brk()` system call: puts more room at the end of the data segment. On
  some systems, there is no way to free this memory, but a process can
  reuse the memory it already has.
* `mmap()` system call: "memory map" an anonymous section of memory for
  general purpose use. This can be freed with `munmap()`.

Under the hood, `malloc()` use one or the other or both of those
syscalls.

Since a syscall has overhead, it's common for `malloc()` to `brk()` a
significant chunk of memory when it needs it, then it manages subchunks
of that memory over various `malloc()` and `free()` calls. This has the
advantage that most of that memory management takes place in user space
and no context switch to kernel mode is necessary when `malloc()` anda
`free()` are used.

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

* TODO questions