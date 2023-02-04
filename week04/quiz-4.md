[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

How does the Completely Fair Scheduler (CFS) decide how much time to give a process?

A fixed length of time is divided up evenly between all processes that are ready to run.

A fixed length of time is divided up evenly between all processes that are ready to run or are blocked.

Every process gets the same amount of time to run every time it gets scheduled.

Every process gets an equal slice of time in round-robin fashion.

---

How does "nice" work with the Completely Fair Scheduler (CFS)?

A negative nice gives a process a longer timeslice and makes it vruntime accumulate less quickly.

A positive nice gives a process a longer timeslice and makes it vruntime accumulate less quickly.

A negative nice gives a process a longer timeslice and makes it vruntime accumulate more quickly.

A positive nice gives a process a longer timeslice and makes it vruntime accumulate more quickly.

---

One of the biggest challenges with having a cache on each core is:

Keeping the caches synchronized.

Keeping the caches fast.

Keeping the caches full.

Keeping the caches small.

Keeping the caches large.

---

When fork() creates a child process, it:

Gets a copy of the parent's data and shares its open files.

Gets a copy of the parent's data and all files are closed.

Shares the parent's data and its open files.

Shares the parent's data and all its files are closed.

---

Why is sharing data between Unix processes challenging?

Because they don't share any data by default and you have to use other mechanisms to pass data between them.

Because they share all their data and you have to watch for concurrent access issues.

Because data loss can occur if you don't call fork() carefully; you need to give the right arguments to the fork() call that causes it to preserve data.

Because looking at data from multiple processes is CPU-intensive.

---

What is a pipe?

A unidirectional data conduit that maintains the order of the data passed though it.

A bidirectional data conduit that maintains the order of the data passed though it.

A unidirectional data conduit that does not necessarily maintain the order of the data passed though it.

A bidirectional data conduit that does not necessarily maintain the order of the data passed though it.

---

If you create a new pipe into an array pfd, then pfd[0] and pfd[1] are the:

Read end of the pipe and the write end of the pipe, respectively.

Write end of the pipe and the read end of the pipe, respectively.

They're both the write end of the pipe, counterintuitively.

They're both the read end of the pipe, amusingly.

---

What does dup2(f1,f2) do?

It makes it so that file descriptor f2 refers to the same file that file descriptor f1 does, closing f2 first if necessary.

It makes it so that file descriptor f1 refers to the same file that file descriptor f2 does, closing f1 first if necessary.

It makes it so that file descriptor f2 refers to the same file that file descriptor f1 does, closing f1 first if necessary.

It makes it so that file descriptor f1 refers to the same file that file descriptor f2 does, closing f1 first if necessary.

---

Why would we use dup2() with pipe()?

To set up standard input and standard output to go through the pipe.

To make a backup of the pipe's file descriptors before a fork().

To make sure we don't lose our copies of file descriptors 0 and 1 when we open the pipe.

To get additional bandwidth through the pipe for performance reasons.

---

