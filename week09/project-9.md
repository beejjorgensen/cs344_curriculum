<!-- Project 9: Page Tables Part 1 -->
## Introduction

**This is part 1 of a multipart project.**

We're going to simulate a page table on a simple computer.

Recall that the page table is effectively a big array that you use to
map virtual page numbers to physical page numbers.

This simulation will allow us to start new (fake) processes that need a
certain number of pages of physical memory, store and load data from
virtual addresses per process, and so on.

We're going to issue commands on the command line to do these things.

### Skeleton Code

Download these two files and add them to your project:

* [`Makefile`]( https://canvas.oregonstate.edu/courses/1849663/files/92219564?wrap=1)
* [`ptsim.c`](https://canvas.oregonstate.edu/courses/1849663/files/92219566?wrap=1)

The C file is a skeleton file to be filled out.

### Command Line

The program we're writing is called `ptsim`, and you'll run it with a
variety of commands and arguments:

```
ptsim command command ...
```

The possible commands are:

* `np n m`: launch new process `n` with initial allocation of `m` pages.
* `ppt n`: print page table for process `n`.
* `pfm`: print a representation of a free map.

The `ppt` and `pfm` functions are already written for you.

Next project, we'll add more commands.

### The Fake Computer

This is a machine with 14-bit addressing, supporting physical addresses
from 0-16385 (16 KB), and per process virtual addresses in the same
range.

We're going to simulate this physical memory with a big global array of
`unsigned char`s:

```
#define MEM_SIZE 16384

unsigned char mem[MEM_SIZE];
```

(In C, a `unsigned char` type is just a byte--on your system, it's
certainly 8-bits. It can hold charaters, or small numbers between 0 and 255.
In this case, we'll use them to hold small numbers.

The memory is logically split up into 64 pages of 256 bytes each.  (`64
x 256 = 16384`, the total memory size.)

Page 0 goes from addresses 0 to 255.

Page 1 goes from addresses 256 to 511, and so on.

### Addressing

Confusingly, there are two ways to refer to the same address:

1. The address number from 0-16383.
2. The page number and the offset within that page.

Remember that we've logically split the 16384-byte area up into 64
contiguous pages of 256 bytes each. So if I give you a page number and
an offset within that page, you should be able to compute the address:

```
address = page_num * 256 + offset;
```

So page 3, offset 12 is:

```
#define PAGE_SIZE 256

address = 3 * PAGE_SIZE + 12 = 780
```

In our fake computer, we can write physical memory with an address
directly like this:

```
mem[addr] = 12;
```

or with a page and offset like this:

```
mem[page * PAGE_SIZE + offset] = 12;
```

### Zero Page

This is the zeroth page of physical memory, from address 0-255. It has
special uses in this fake computer.

* **Free Page Map**: Bytes 0-63 (effectively addresses 0-63) form a free
  page map (which lets you know which pages are in use and which
  aren't).

* **Page Table Map**: Bytes 64-127 hold page table pointers for up to 64
  processes.

Process 0's page table page number is at address 64.

Process 1's page table page number is at address 65, and so on.

The page table page number is the number of the page in physical memory
that holds the page table for the given process.

You might need to reread that sentence a number of times to get it.

### Mapping a Process Number to it's Page Table

In the following diagram, we're trying to locate process #12's page
table.

![Mapping a process to a page table page](https://canvas.oregonstate.edu/courses/1849663/files/92199722/preview)

The first step is to compute the address that holds process 12's page
table number.

This address is going to be in zero page in the page table pointers
section which begins at address 64.

So we add 64 to 12 to get 76, which is the address that holds process
12's page table number.

Then we look in memory at that address and find, say, 18.

This tells us that process 12's page table is to be found in RAM on page
18.

### Per Process Page Table

Each process has its own page table. Each page table also resides in
memory, and each one takes a single page.

So we have zero page, which is reserved for the system stuff, above. And
then each process also has a page table allocated from the pool of free
physical pages.

The page table entry for the given process points to the page that holds
the its page table.

### Process Page Allocation Examples

If we started a `Process 1` that needed two pages of data, we'd have the
following physical memory layout:

```
Page 0: Zero Page, reserved
Page 1: Process 1's page table
Page 2: Process 1's data page 0
Page 3: Process 1's data page 1
Page 4: Unused
Page 5: Unused
Page 6: Unused
Page 7: ... and so on ...
```

If we then started another `Process 2` that needed just one page of
data, we'd then have:

```
Page 0: Zero Page, reserved
Page 1: Process 1's page table
Page 2: Process 1's data page 0
Page 3: Process 1's data page 1
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Unused
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

If we then killed `Process 1`, all its physical pages would be freed:

```
Page 0: Zero Page, reserved
Page 1: Unused
Page 2: Unused
Page 3: Unused
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Unused
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

and those pages become available for reuse.

> Note that we're not freeing pages this week--that's next week--but
> this example is here to show how the first pages available are always
> used even if they're not contiguous.

So let's start a new `Process 3` that needs three pages of memory. We'd
see this happen:

```
Page 0: Zero Page, reserved
Page 1: Process 3's page table
Page 2: Process 3's data page 0
Page 3: Process 3's data page 1
Page 4: Process 2's page table
Page 5: Process 2's data page 0
Page 6: Process 3's data page 2
Page 7: Unused
Page 8: Unused
Page 9: ... and so on ...
```

See how `Process 3`'s pages are disjoint and spread out over `Process
2`s?

This is not a problem, because the page tables tell you how to map from
a process's continuous virtual pages to the system's physical pages,
even if those physical pages are scattered about.

### Page Table Layout

Each process has its own page table. This is how the CPU maps a virtual
address from a process to a physical address.

This table is an array of bytes.

The index of the array represents the virtual page number. The byte in
the array at that index holds the corresponding physical page number.

So if you have a process's page table page number `page_table_page`, and
virtual page number `virt_page`, you can look up the corresponding
physical page number in the page table like this:


```
address = page_table_page * PAGE_SIZE + virt_page;

phys_page = mem[address];
```

Let's take the previous example where we figured out that process 12's
page table was in physical page 18.

And let's have process 12 retrieve the value in memory at virtual
address 553 (binary `00001000101001`).

![Looking up a Virtual Address](https://canvas.oregonstate.edu/courses/1849663/files/92199723/preview)

Since we know each page is 256 bytes and 8 bits can represent 256
different values, we know the low 8 bits of the address is the _offset_.
And we know the high 6 bits is the physical _page_ we want to get for
this virtual page.

We see the value of the high 6 bits is `2`, which means we look at
offset `2` in our page table. The value there is `37`.

This tells us that physical page `37` is the same as the process's
virtual page `2`.

We're part way there.

So we go look at physical page `37`, and we use the offset (low 8 bits)
from the address. In this case, the offset is `41`.

That is, virtual page 2, offset 41 is the same as physical page 37,
offset 41.

And finally we get the value the process was wanting from virtual
address 553: `99`.

### Free Page Map Layout

In zero page, the first 64 bytes indicate which physical pages are used.

There are 64 physical pages, so that's one byte per page. The value of
the byte indicates if the page is used:

* `0`: page is ununsed/free.
* `1`: page is used/not free.

### Initialization of Memory on Bootup

There's some initialization that needs to be done before we start.

1. Zero every byte of physical memory in the `mem` array.
2. Mark zero page as "used" in the Used Page Table. (That is, set
   `mem[0]` to `1`.)

We mark zero page as used so that later we don't use it for a process's
memory.  Zero page is reserved and will never move or be used for
anything else.

### Algorithm to Map Page/Offset to Address

We've already see this, but for completeness:

```
GetAddress(page, offset):
    return page * PAGE_SIZE + offset
```

### Algorithm to Allocate a Page

This is what we'll do to get a page of physical memory. We want to do
this for a few reasons:

* When we allocate a new process's page table
* When we allocate data pages for a new process
* When a process requests more pages

We're going to use the first available page we find in a linear search
for this simulation.

> A real OS isn't going to do anything that inefficient; it'll have some
> kind of free block structure that can deliver the next free block in
> `O(1)` time. But we're keeping it simple here. The important thing is
> there's some way to get an available block.

The algorithm is:

```
AllocatePage():
    For each page_number in the Used Page array in zero page:
        If it's unused (if it's 0):
            mem[page_number] = 1 // mark used
            return the page_number

    return 0xff  // indicating no free pages
```

Recall the Used Page array is the first 64 bytes of zero page.

For example, if the first 64 bytes has this:

```
1 1 1 0 1 0 1 1 0 [... truncated ... ]
      ^
```

The first unused page is at index 3, indicated by the caret, above.
This means that the first unused physical page is page #3. (Which starts
at address `3 x 256`, where `256` is the page size.)

So we'd mark it as used:

```
1 1 1 1 1 0 1 1 0 [... truncated ... ]
      ^
```

And return `3`.

### Algorithm to Allocate Memory for a New Process

We need to do a couple things.

1. Allocate a single page to be this process's page table.
2. Allocate the other data pages the process requested.
   1. Add entries for those pages to the process's page table.

```
NewProcess(proc_num, page_count):
    // Get the page table page
    page_table = AllocatePage()

    // Set this process's page table pointer in zero page
    mem[64 + proc_num] = page_table

    // Allocate data pages
    For i from 0 to page_count:
        new_page = AllocatePage()

        // Set the page table to map virt -> phys
        // Virtual page number is i
        // Physical page number is new_page
        pt_addr = GetAddress(page_table, i)
        mem[pt_addr] = new_page
```

If the initial page table allocation fails (due to out-of-memory), the
function should print:

```
    printf("OOM: proc %d: page table\n", proc_num);
```

and return.

If any of the subsequent page allocations fail, it should print:

```
    printf("OOM: proc %d: data page\n", proc_num);
```

and return.

### Example Output

#### Example

Here we don't add any processes, but we see zero page is already marked
as allocated:

```
%  ./ptsim pfm
--- PAGE FREE MAP ---
#...............
................
................
................
```

#### Example

Here we make a new `Process 1` with `2` data pages:

```
%  ./ptsim np 1 2 pfm
--- PAGE FREE MAP ---
####............
................
................
................
```

The first used page is zero page.

The second used page is `Process 1`s page table.

The third and fourth used page are `Process 1`s data pages.

#### Example

Here we see the mappings from the virtual pages on the left to the
corresponding physical pages on the right:

```
%  ./ptsim np 1 2 ppt 1
--- PROCESS 1 PAGE TABLE ---
00 -> 02
01 -> 03
```

Virtual page 0 maps to physical page 2.

Virtual page 1 maps to physical page 3.

#### Example

Allocate 2 blocks for `Process 1` and 3 blocks for `Process 2`.

```
%  ./ptsim np 1 2 np 2 3 ppt 1 ppt 2 pfm
--- PROCESS 1 PAGE TABLE ---
00 -> 02
01 -> 03
--- PROCESS 2 PAGE TABLE ---
00 -> 05
01 -> 06
02 -> 07
--- PAGE FREE MAP ---
########........
................
................
................
```

See there are 8 pages used on the free map. They are:

```
Page 0: zero page (reserved)
Page 1: Process 1's page table
Page 2: Process 1's data block 0
Page 3: Process 1's data block 1
Page 4: Process 2's page table
Page 5: Process 2's data block 0
Page 6: Process 2's data block 1
Page 7: Process 2's data block 2
```

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **75 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

## Extensions

* This coming week we're going to:
  * Add code to kill a process and free its memory
  * Add code to read and write from virtual memory addresses

<!-- Rubric

"ptsim pfm" working (5)

"ptsim np 1 2 pfm" working (10)

"ptsim np 1 2 ppt 1" working (10)

"ptsim np 1 2 np 2 3 ppt 1 ppt 2 pfm" working (10)

"ptsim np A B ppt A np C D ppt C pfm" working, for arbitrary values of A, B, C, D (20)

"ptsim np A B ppt A np C D np E F ppt E pfm" working, for arbitrary values of A, B, C, D, E, F (20)

-->
