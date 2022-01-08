[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

What's the typical relationship between `fork()` and `exec()`?

A process calls fork() and then the child process calls exec().

A process calls fork() and then the parent process calls exec().

A process calls exec() and then the child process calls fork().

A process calls exec() and then the parent process calls fork().

---

What does the scheduler do?

Chooses which process is next to run.

Decides which I/O is most important.

Compares the relative priority of different pieces of hardware and
schedules their handlers.

Makes sure the output on the screen is synchronized with the input from
the keyboard.

---

What describes the relationship between a typical scheduler and I/O?

I/O is relatively slow, so the scheduler runs other programs that are
blocked on I/O.

I/O is relatively fast, so the scheduler gives I/O-bound processes more
CPU time and keeps CPU-bound processes waiting.

I/O isn't particularly fast or slow, so schedulers don't typically treat
I/O-bound and CPU-bound processes differently.

---

[5 points]

After many years of research, we've finally settled on a single
scheduling policy that works well in all cases.

False.

---

What's the difference between the _response time_ and _turnaround time_
scheduling metrics?

Response time is the time difference between arrival of the job and the
time it gets scheduled. Turnaround time is the difference between
arrival of the job and completion of the job.

Response time is the time difference between arrival of the job and
completion of the job. Turnaround time is the difference between
arrival of the job and the time it gets scheduled.

Response time is the time between submission of an I/O request to a
device and acknowledgment from the device. Turnaround time is the time
between submission of an I/O request and return of the data from that
request.

Turnaround time is the time between submission of an I/O request to a
device and acknowledgment from the device. Response time is the time
between submission of an I/O request and return of the data from that
request.

---

What's the difference between Round Robin (RR) and First-In-First-Out
(FIFO) scheduling?

RR will stop running a process after a certain amount of time and switch
to the next one. FIFO runs each process non-stop to completion.

FIFO will stop running a process after a certain amount of time and
switch to the next one. RR runs each process non-stop to completion.

RR was better in the old days before timesharing environments existed.

FIFO is better now that we all use timesharing environments.

---

What are the relative strengths and weaknesses of Round-Robin (RR) and
Shortest-Job-First (SJF) scheduling?

RR has good response time and bad turnaround time. SJF has good
turnaround-time, but bad response time.

SJF has good response time and bad turnaround time. RR has good
turnaround-time, but bad response time.

RR and SJF both have good response time, but only SJF has good
turnaround time.

RR and SJF both have good turnaround time, but only SJF has good
response time.

---

Is `cd` a utility program or a command built into the shell? Why?

It's built-in. If `cd` were an external command, it would only set the
directory for the `cd` process, not the shell.

It's built-in, but it doesn't have to be. It would simply be too slow to
ask another process to change the shell's directory, so shells build it
in.

It's external. Processes aren't allowed to change directory on their
own; they have to ask another program to do it.

It's external. You need to have another program make the syscall to
change directory on your behalf.

---

In a Multi-Level Feedback Queue (MLFQ), how does an existent process
move to a higher priority from a lower one?

Periodically, the MLFQ boosts all processes to the highest priority.

It gives control back to the OS before its timeslice is used up.

If it uses its entire timeslice, it is moved up a level.

If no other processes exists at higher priority levels, it is moved up a
level.

---

In a Multi-Level Feedback Queue (MLFQ), how does an existent process
move to a lower priority from a higher one?

If it uses its entire timeslice, it is moved to a lower priority.

If it gives control back to the OS before its timeslice is used up it is
moved to a lower priority.

If no other processes exists at lower priority levels, it is moved down a
level.

Periodically, the MLFQ drops all processes to a lower priority.