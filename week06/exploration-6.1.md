<!-- Exploration 6.1: Memory Virtualization and Alignment -->

## The Gritty Details of Memory Virtualization

When a process accesses some memory with a machine code instruction,
the process has no idea it's running in a virtual memory space.

So it just names an address to read or write from and trusts that the
data will be there.

Of course, behind the scenes, the OS has set things up so that the
virtual memory _maps_ to pages of physical memory in a way that's
transparent to the process.

But for this to work efficiently, it has to be implemented in
hardware--the CPU has to support it.

### Base and Bounds Approach

This is a simple approach to virtualization wherein the process runs in
a contiguous section of memory that is remapped to a particular base
address.

That is, if a process thinks it's accessing memory address 3490, but the
OS has set the base to 20000, then the process will actually be looking
at physical address 23490 (20000+3490) when it looks at virtual address
3490.

The bounds register is used to limit the process's reach through memory.
If it tries to access memory beyond the bound, the CPU raises an
exception that gives control back to the OS. At that point, the OS will
probably punish the process with a signal that kills it and dumps core.

This is a simple approach that demonstrates:

* how the CPU can do hardware address translation (by adding the virtual
  address onto the base register) 
* how the OS can limit process memory access to the physical address to
  which it has been restricted.

But modern CPUs are more complicated than that.

## Alignment

_Alignment_ is the concept that certain types of memory accesses by the
CPU must start on addresses that are a multiple of a certain number.

For example, a particular CPU might require that a 2-byte integer begin
on an even-numbered address.

And that starting one on an odd-numbered address might be either slower
or cause the process to crash.

Or a system might require that multibyte values start on addresses that
are multiples of 8 or 16.

For example, here are two 2-byte hex numbers stored in RAM.

The address of the number (the address of the first byte) 0x1234 is 3490.

The address of the number 0x5678 is 3493. This is an odd address, and
probably counts as misaligned:

```
Address   Value (hex)
-------  ------------
 3490         12
 3491         34
 3492
 3493         56
 3494         78
 3495
```

Different types might have different alignment requirements on different
systems, except for `char`, a single byte, which can be in any address.

An example might be:

```
 Type   Alignment
------- ---------
char        1
short       2
int         2
long        4
```

Here's an example of how we might get something misaligned in C using
pointers of different types:

```
char *p = malloc(10);
int *q = p + 1;  // move up 1 address

*q = 1234;
```

`malloc()` always returns a data space that's aligned at the largest
possible alignment for all of a particular CPU's data types. On your
system, this is likely to be aligned at a multiple of 16 bytes.

> We're hand-waving a bit when we say "all" data types, above. But it's
> true for the common ones, like `short`, `int`, `float`, `double`, etc.

But in the above example, we forced things to be misaligned by pushing
them one byte up.

If you want to get the maximum alignment for data types on your system, you can run this:

```
#include <stdio.h>
#include <stddef.h>
#include <stdalign.h>

int main(void)
{
    printf("%zu\n", alignof(max_align_t));
}
```

which prints `16` in my case, meaning that the largest alignment
requirement of all the data types is that it begins on an address that's
a multiple of 16.

Some data types might require less alignment. But to be sure, memory
allocators like `malloc()` guarantee that the returned pointer has a
suitable alignment for any data type, that is has the max alignment.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Address Translation](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-mechanism.pdf)
  
## Reflect

* What do you think some problems might be with implementing memory
  virtualization in software?

* What is the max alignment on your system?

* When it comes to memory virtualization, what parts are the CPU's job?
  What parts are the OS's job?

* What happens when a process tries to read outside of its virtual
  address space?

* What are some of the drawbacks of memory virtualization with
  base/bounds?