## Summary

* The OS is responsible for managing access to resources and running
  processes on a per user basis.
* Virtualization of pieces of hardware, including CPU and RAM, is the
  mechanism though which the OS can run many programs at once.
  * Each process thinks it has the machine to itself, when in fact it
    only has a complete set of virtual components to itself.
* The kernel is the core of the OS
* The UI and utilities and other programs are not in the kernel, but
  call into it.
* Programs use system calls (syscalls) to call into the kernel.
* Shell scripts are small programs executed by the shell.
* Pipes in Unix are used to pipe the output of one program into the
  input of another.
* Regular expressions match a pattern of characters.
  * Programs like `vim`, `sed`, and `grep` use these for search and
    potentially replace.