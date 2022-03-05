## Summary

* Both VMS and Linux split virtual memory into two large sections: user
  and kernel memory.
* Unlike Linux, VMS used a hybrid paged/segmented scheme in order to
  avoid having large page tables.
* VMS used second-chance queues to avoid the poor performance of a
  single FIFO.
* For speed, OSes don't tend to zero memory until it is used.
* For speed after a fork, OSes don't tend to copy memory until it is
  written to by the child process.
* Linux has support for 4 KB pages, and a couple other larger sizes.
  * Larger pages mean smaller page tables.
  * But they also mean more opportunity for internal fragmentation.
* OSes use spare memory as a page cache to keep pages of data copied
  from persistent storage (e.g. disks) in RAM for speed.
* There are a wide variety of clever attacks that can be made against
  virtual memory systems.
