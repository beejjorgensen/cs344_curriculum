## Summary

* The OS virtualizes RAM--it appears to each process that they own the
  entire address space.
* Physical RAM is mapped to virtual addresses in a way that is
  transparent to the processes.
* From a process perspective, local (automatic) variables are stored on
  the _stack_ and freed automatically when they fall out of scope.
* From a process perspective, data allocated with `malloc()` is stored on
  the _heap_ and is only freed when done explicitly by the process, or
  when the process ends.
* When manually manipulating memory with `malloc()` and `free()`, it's
  important to follow certain rules:
  * Don't use data after you've freed it.
  * Don't free it more than once.
  * Don't access memory beyond the bounds of what you've allocated.
  * Don't forget to allocate memory--a pointer points to garbage unless
    it is initialized.
  * Only call `free()` with values you got from `malloc()` (or `NULL`).