## Summary

* Unix uses file descriptors (non-negative integers) to uniquely
  identify open files per process.
* The Big Four functions for file I/O in Unix are `open()`, `close()`,
  `read()`, and `write()`.
* Among other things, the kernel's process API allows creation of,
  destruction of, and waiting for processes.
* Unix uses syscalls `fork()`/`exec()`, `kill()`, and `wait()` to
  create, destroy, and wait for processes.
* A "parent" process can create a "child" process.
* Standard Input (`stdin`), Standard Output (`stdout`), and Standard
  Error (`stderr`) are three file descriptors opened automatically for
  each new process.
* In Unix, a process becomes a zombie when it dies.
* A zombie process is removed when another process wait()s for it.