# Day 1

* Project

* Review Page tables
  * Note one page table per process

* Translation Lookaside Buffers
  * Jump to first image and use it as an example
  * Run examples, hit, hit, hit, hit, miss

* Hardware TLB handler x86
* Software TLB handler RISCy
  * Have an interrupt occur
  * OS can use whatever structure it wants for the TLB

* What about context switches?
  * TLB is only good for a single address space mapping
  * What to do?
    * Flush it?
    * Tag with a "address space ID"

# Day 2

Multi-level Page Tables

Example

64-bit address space, 4 KB pages
52-bit VPN + 12-bit offset

`2**52` PTEs--4,503,599,627,370,496 (4 quadrillion) entries

If each entry is 128 bits (16 bytes), that's:

72,057,594,037,927,936 (72 petabytes) bytes per process

If we have 100 processes, it's

7,205,759,403,792,793,600 (7 exabytes) total for page tables.

And almost all these entries are empty!!

It's time to trade space for speed!

MLPTs split it up more like a tree... hides all the unused PTEs on
"branches that go nowhere".

Hard concept: page table is made of pages (of course). Each page of the
page table contains so-many entries.

We only need to actually store pages of page table entries if there are
any valid page table entries in that page.

[Figure 20.3]

So let's make a "directory" that has references to the pages of the
page table that are "in use". The directory has a valid bit to indicate
if the entry goes anywhere.

Advantage: pages of the page table that are unused don't consume any
memory.

Advantage: pages of the page table can be discontinuous now.

[Second VPN/offset diagram after Figure 20.4, Page 9]

Usage: part of the VPN is now the page directory index. And the other
part is the page table index within that page.

[VPN/offset diagrams on Page 11]

Multi level just adds more indirection. Directories point to other
directories.

Some kind of analogy with directories of people by physical region?

* If you were only interested in Romania, all the books you'd need would
  be the directories that got you down to Romania, and then the Romania
  books themselves.

  Versus having a book with everyone in the world.

  Sure, you have to dig down through all those layers to look someone
  up, but you save a lot of space.

  And if you cache the result, you don't even have to go through all the
  layers.
