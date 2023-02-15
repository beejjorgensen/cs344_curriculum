# Lecture Notes 6.2

## Watching the Stack and Heap

* Experiment with mmap
* Experiment with stack
  * Recursion to see

## Loading the Heap for the Project

Pencil and Paper Demo

* Get padded sizes of requested data and header
* Manually calculate offsets from start of heap


--------------------

# Or this

Limited Direct execution

Memory relocation with base and bounds

Kernel mode user mode

Kernel mode allows setting BB registers

In Kernel mode BB restrictions do not apply

In user mode, memory accesses are automatically adjusted by the CPU and
the Base Register.

Out of bounds raises interrupt and the kernel takes control again

Process Control Block holds info about the process
Kernel has a table of these

Segmentation
One set of BB registers per segment

Origin of the term "segmentation fault"--when you access OOB memory out
of the segment

Protection bits/sharing segments

