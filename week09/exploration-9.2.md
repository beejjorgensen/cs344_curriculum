<!-- Exploration 9.2: Swapping Policies -->

## Swapping Policies

A _swapping policy_ is the logic that governs when a page is swapped out
to disk. There are a lot of possible strategies. Some are:

* Optimal: swap out the page that will be used most distantly in the
  future. This has the advantage of being as good as it gets. It also
  has the disadvantage of requiring a time machine to look into the
  future.

* FIFO: the page that was swapped into RAM first gets booted back to
  disk first. Not terribly optimal, but really easy to implement.

* Random: just swap random pages out. This might seem insane, but it
  actually performs slightly better than FIFO.

* Least Recently Used (LRU): the page that has been used (accessed)
  least-recently is swapped out. This is a pretty good policy, but
  difficult to implement.

* Approximate LRU: Almost as good as LRU but easier to implement.

### Locality

There are two types mentioned in the text:

* **Spatial locality**: if a piece of memory is accessed, the
  neighboring pieces of memory are likely to be accessed.
* **Temporal locality**: a page accessed now is likely to be accessed
  again soon.

Either or both (or neither) of these can be kept in mind when coming up
with a swapping policy.

If the processes exhibit no locality of any kind, then the swapping
policy doesn't matter. They all lose, because they're trying to take
advantage of locality and there is none. (Or in the case of the Random
policy, they simply don't pay attention to locality at all.)

But if the processes do exhibit some locality, we can see some of the
policies beginning to take advantage of that.

### Demand Paging

When do you swap a page back into memory? We could be proactive, but
most OSes use _demand paging_. They swap the page back in when a process
page faults and needs that page.

### Thrashing

Let's say a system has 300 processes. Let's say most of those process
are sleeping (blocked on I/O or deliberately sleeping).

The blocked processes don't need their memory pages while they're not
running. If they've been asleep for a while, most of their pages might
be swapped out.

The processes that _aren't_ sleeping, though, need their pages to run.
So the running processes' pages all need some RAM.

Now there are two options:

* We have enough physical RAM for all the running processes
* We don't have enough physical RAM for all the running processes

In the first case, everyone's happy.

In the second, though, we end up _thrashing_.

This means that all of the running processes likely have some of their
pages swapped out to disk. So before a process can run, those pages have
to be swapped back in, swapping out some other process's pages.

For every context switch, tons of pages might have to be written to and
read from disk. This makes a context switch (which normally happens many
times per second) several orders of magnitude slower than normal.

You'll see this manifest as your computer becoming more and more
sluggish, maybe to the point of unusability.

Reducing the amount of RAM used by running processes (or killing them)
or buying more RAM can make your computer seem faster by reducing
thrashing.

Using faster secondary storage (like SSD instead of hard disks) can
decrease the amount of time spent swapping, also improving things a bit.

## Reading

* In the Virtualization section of [the book](https://pages.cs.wisc.edu/~remzi/OSTEP/), read:
  * [Swapping Policies](https://pages.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys-policy.pdf)
  
## Reflect

* When does a system start to thrash?

* What are the main issues that can get in the way of performance with
  Random and FIFO swapping policies?

* What is a drawback to demand paging? How could performance potentially
  be further improved?

* What is dirty vs clean page?
