<!-- Project 9: Page Tables Part 2 -->
## Introduction

**This is part 2 of a multipart project.**

We're going to continue our simulation of a page table on a simple
computer.

### Command Line

We're adding more commands to our simulator:

The possible commands from last week were:

* `np n m`: launch new process `n` with initial allocation of `m` pages.
* `ppt n`: print page table for process `n`.
* `pfm`: print a representation of a free map.

The `ppt` and `pfm` functions are already written for you.

The commands to add this week are:

* `kp n`: kill process `n` and free all its pages.
* `sb n a b`: For process `n` at virtual address `a`, store the value
  `b`.
* `lb n a`: For process `n`, get the value at virtual address `a`.

### Algorithm to Deallocate a Page

Remember that pages are marked either used or unused in the free page
map in zero page (in memory from address 0 to 63).

And that each byte of memory lets you know if the page is used or not.

For example, if `mem[12]` is `1`, that means that physical page 12 is
allocated. And if the value were `0`, it would mean it wasn't allocated.

So to free a page, we just need to set that value to 0 for the given
page:

```
DeallocatePage(p):
    Set the value at address p in zeropage to 0
```

### Algorithm to Kill a Process

When killing a process, we have to do a bunch of things.

1. Go through the page table and free every page that's listed there.
2. Free the page table itself.

This is the opposite of what we did to create the process.

Here's a diagram that shows us getting the page table page for a
particular process:

![Mapping a process to a page table page]()

**Remember**: `0` is not a valid page number to find in a page table.
Zero page is reserved in this system. So when we're going through the
page table looking for pages to free, we shouldn't a page if the
physical page value is zero.

```
KillProcess(p):
    Get the page table page for this process

    Get the page table for this process

    For each entry in the page table
        If it's not 0:
            Deallocate that page

    Deallocate the page table page
```

Recall that you can find the page table index for a given process from
the page table map in zero page. Bytes 64-127 hold pointers to page
tables for process numbers 0-64 (i.e. add 64 to the process number to
find the index of the page table number).

```
page_table_page = mem[proc_num + 64];
```
    
### Converting a Virtual Address to a Physical Address

**This is it.** This is the core of virtual addressing.

We need the process's page table to do this, because it describes the
mapping between virtual and physical pages for this process.

So we'll get that first.

![Looking up a Virtual Address]()

Then we need to figure out what page we're talking about. We're given an
address, which is just an index into memory, but we need to pull the
page number out of there.

But see in the diagram, above, how the high bits of the address hold the
page number? We just need to shift them down. There are 8 offset bits,
so we'll just shift down over those.

```
virtual_page = virtual_address >> 8
```

But that's not all we need--we need the offset (which is the same on the
physical page as it is on the virtual page). We can do that by masking
out the low 8 bits with bitwise-AND:

```
offset = virtual_address & 255;
```

```
GetPhysicalAddress(proc_num, virtual_addr):
    Get the virtual page (see code above)
    Get the offset
    Get the physical page from the page table

    Build the physical address from the phys page and offset

    Return it
```

That last step--building the physical address can also be done with
bitwise math:

```
phys_addr = (phys_page << 8) | offset;
```

That shifts the physical page number up to the high bits, and then
stamps the offset on the low bits.

### Algorithm to Store a Value at a Virtual Address

This one's not too bad if your mapping to physical addresses code is
working.

```
StoreValue(proc_num, virt_addr, value):
    phys_addr = GetPhysicalAddr(proc_num, virt_addr)
    mem[phys_addr] = value
```

This function should have some output:

```
printf("Store proc %d: %d => %d, value=%d\n",
    proc_num, vaddr, addr, val);
```

where `vaddr` is the virtual address, and `addr` is the physical
address, and `val` is the stored value.

You can change the variable names in that `printf()`, but please don't
change the output--it'll be used for testing.

### Algorithm to Load a Value from a Virtual Address

This is very similar to storing a value--we have to get it instead of
setting it.

```
LoadValue(proc_num, virt_addr):
    phys_addr = GetPhysicalAddr(proc_num, virt_addr)
    value = mem[phys_addr]
```

This function should also have some output:

```
printf("Load proc %d: %d => %d, value=%d\n",
    proc_num, vaddr, addr, val);
```

where `vaddr` is the virtual address, and `addr` is the physical
address, and `val` is the loaded value.

You can change the variable names in that `printf()`, but please don't
change the output--it'll be used for testing.

### Example Output

#### Example

We'll create and kill processes to see how pages get used. Since we're
using the first available free page when a process comes to life, these
will turn out in a specific order.

1. Make a new Process 1 with 2 pages
2. Make a new Process 2 with 3 pages
3. Kill Process 1, freeing its pages
4. Make a new Process 3 with 5 pages
5. Kill Process 3, freeing its pages

**Note**: the output below is annotated with comments in square
brackets.  These should **not** appear in your output!

```
%  ./ptsim np 1 2 pfm np 2 3 pfm kp 1 pfm np 3 5 pfm ppt 3 kp 3 pfm
--- PAGE FREE MAP ---
####............          [Zero page and process 1 allocated]
................
................
................
--- PAGE FREE MAP ---
########........          [And process 2 added on]
................
................
................
--- PAGE FREE MAP ---
#...####........          [Process 1 killed]
................
................
................
--- PAGE FREE MAP ---
###########.....          [Process 3 created]
................
................
................
--- PROCESS 3 PAGE TABLE ---
00 -> 02
01 -> 03
02 -> 08                  [See the jump in physical page numbers]
03 -> 09
04 -> 0a
--- PAGE FREE MAP ---
#...####........          [Process 3 killed]
................
................
................
```

Notice that when Process 3 was created, there were 3 free pages from
where Process 1 was killed. (Pages at index 1, 2, and 3.)

When we created process 3, it wanted 5 data pages. But of course in
addition to those, we needed to allocate its page table.

So its page table went on page 1, then pages 2 and 3 were used for its
first two virtual pages, as you see in the page table output, above.

But page 4 is in use by Process 2, still, so Process 3 can't use that.
Or any of Process 2's pages, for that matter.

The next free page is at index 8, then another at 9, and another at 10
(hex 0x0a). So those get used.

Again, it's no problem to have discontinuous blocks of pages. The page
table gets you there no matter where the physical pages are.

In real life, they might not even be in order, but that won't happen
with this simulation with our "use the lowest free page first" strategy.

#### Example

Make a new process with 2 pages, store value 99 at virtual address 10,
then load the value from virtual address 10.

```
./ptsim np 1 2 ppt 1 sb 1 10 99 lb 1 10

--- PROCESS 1 PAGE TABLE ---
00 -> 02
01 -> 03
Store proc 1: 10 => 522, value=99
Load proc 1: 10 => 522, value=99
```

We see virtual address 10 maps to physical address 522. Let's compute
it.

Virtual address 10 is on virtual page #0 (each page is 256 bytes,
remember?), and we could get that by right shifting 10 by 8 bits. Or
dividing by 256--same thing. 10/256 is 0 (integer math), so that's how
we get virtual page 0.

We then look in the process 1 page table and see that virtual page 0
maps to physical page 2.

And since each page is 256 bytes, we know that physical page 2 starts at
address 512. Which is 2 * 256. Or 2 left-shifted 8 bits, same thing.

But just knowing where the page starts isn't enough. We need to add the
offset into the page.

The offset is the low 8 bits of the virtual address. So we get that by
bitwise-ANDing the virtual address with 255. Or we could mod it with
256, same thing.

So we do that math: `10 & 255` and we get `10`. That's the offset.

And we take the physical page start address of `512`, and we add the
offset of `10`, and we get `522`, the final physical address.

## What to Turn In

Submit the link to your GitHub repo.

## Grading Criteria

This assignment is worth **100 points**.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your
submission.

### Extensions

* Detect if the `GetPhysicalAddress` algorithm is passed an invalid
  virtual address. That is, the virtual page isn't mapped to a physical
  page in the page table.
  * You could check if the relevant physical page has a value of `0`;
    this would indicate it was invalid.
  * If this happens, you can print that there was a page fault:
    ```
    printf("PAGE FAULT: proc %d, vaddr %d\n", proc_num, vaddr);
    ```
* Add `ap n p` command to add `p` pages to process `n`'s memory. (This
  is like calling `sbrk()`.)
  * This should be done by finding the first `0` entry in `n`'s page
    table and then allocate `p` pages on starting there.
  * Detect when you're out of physical memory--when a process asks for
    too many pages, and output something when it happens.

<!-- Rubric

5
Command works: ./ptsim np 1 2 pfm kp 1 pfm

10
Command works: ./ptsim np 1 2 np 3 4 pfm kp 1 pfm

10
Command works: ./ptsim np 1 2 np 3 4 pfm kp 3 pfm

10
Command works: ./ptsim np 1 2 np 3 4 kp 3 pfm np 4 5 ppt 4 pfm

10
Command works: ./ptsim np 1 2 np 3 4 kp 1 pfm np 4 5 ppt 4 pfm

10
Command works: ./ptsim np 1 2 np 3 4 kp 1 kp 3 pfm np 4 5 ppt 4 pfm

10
Command works: ./ptsim np 1 2 pfm np 2 3 pfm kp 1 pfm np 3 5 pfm ppt 3 kp 3 pfm

5
Command works: ./ptsim np 1 2 ppt 1 sb 1 10 99 lb 1 10

10
Command works: ./ptsim np 1 2 ppt 1 sb 1 0 99 lb 1 0

10
Command works: ./ptsim np 1 2 np 2 3 sb 1 10 99 sb 2 20 100 lb 1 10 lb 2 20

10
Command works: ./ptsim np 1 2 np 2 3 sb 1 10 99 sb 2 10 100 lb 1 10 lb 2 10

-->
