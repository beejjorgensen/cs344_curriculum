# Lecture Notes 5.2

## Today

* Correction: Diagram of the stack and heap

* Exercise: Expression Types

* `malloc()` again
  * Side trip with `void*`
  * Remember to `free()`!

* `malloc()`, `brk()`, and `mmap()` again


## Correction

```
+-------------------+
|       Stack       |
+-------------------+
|        vvv        |
|                   |
|                   |
|        ^^^        |
+-------------------+
|       Heap        |
+-------------------+
|      Program      |
+-------------------+
```

## Expression Types

* Goal: to understand what address-of and indirection operators do when
  applied to expressions.

  * Start with numeric expressions

  * Then add dereferences and pointers
  
## Malloc

* Gets us memory from the heap

* What's a `void*`?

* Always `free()`!

## How the OS Allocates Memory

* `malloc()` is in user space. It's not a syscall.

* `brk()` is a syscall. Raises the "break" between the heap and
  unallocated memory.

  * Permanent raise for the life of the program

  * Deprecated on the Mac.

  * Don't call it if you use any of the standard library functions
    (including things like `printf()`) because it conflicts.

* `mmap()` is a syscall.

  * Describe in general--makes a file look like an array.

  * Can be used to allocated "anonymous" memory regions that aren't
    associated with any file.

* `malloc()` calls either `mmap()` or `brk()` (or both!) to get more
  memory.

  * In our project, we'll call `mmap()` so we don't conflict with the
    standard library.
