[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

With virtualized memory: (5)

When a process accesses a particular virtual address, the CPU maps that to a physical address.

When a process accesses a particular physical address, the CPU maps that to a virtual address.

---

One of the main benefits of base/bound virtual memory schemes is:

Simplicity of implementation in the CPU

Processes can span multiple, disjoint pages of memory

Pages don't necessarily have to be mapped in sequential order

Processes don't necessarily have to be contiguous in physical memory

---

What are the base and bound registers?

The base holds the lowest physical address of the process, and the bound holds the highest physical address of the process

The base holds the highest physical address of the process, and the bound holds the lowest physical address of the process

The base holds the lowest virtual address of the process, and the bound holds the highest virtual address of the process

The base holds the highest virtual address of the process, and the bound holds the lowest virtual address of the process

---

Alignment refers to

Data beginning on an address that is a multiple of a certain number

Related data starting at regular intervals

Memory being allocated in same-sized chunks

Virtual memory and physical memory addresses that are identical

---

Accessing misaligned data might, depending on the architecture (choose all that apply):

Cause a bus error and termination of the process.

Causes data to be accessed more slowly than aligned data.

Have no effect.

Cause incorrect data to be read.

---

With a coarse-grained segmented memory scheme:

Each segment of the process must be in a contiguous section of physical memory

The entire process's memory must be in a contiguous section of physical memory

Each segment of the process may be in a nonc-ontiguous sections of physical memory

None of the segments can grow or shrink after they are created.

---

One of the benefits of a fine-grained segmented memory scheme is:

Don't need to have a single continuous stretch of physicaly memory for the program or its major segments

Simplicity of implementation

Works faster than base/bound

Guarantees contiguous stretches of physical memory per process

---

The basic operation of malloc() is

Ask for bigger chunk of memory from the OS and manage it in smaller pieces to be used by the process

For each call to malloc(), ask the OS to allocate more space as requested, passing those on to the process

Manage the preexisting stack data on an as-needed basis for the process.

Magically manifest additional memory for the user through a series of complex spells.

---

Fragmentation is when

Despite there being lots of free chunks of data, none of them are of a large contiguous size.

Memory fails due to too many read/write cycles.

There's not enough disk swap space to service memory requests.

You call `malloc()` many times in succession

