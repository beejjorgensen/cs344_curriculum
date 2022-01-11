[Note: first answer is the correct one.]
[Note: 10 points each unless otherwise noted.]

---

What's the difference between a process and a program?

A process is a running program.

A program is a running process.

A process is several programs running simultaneously.

A process is several programs running one at a time.

Program is just another word for process.

---

What is timesharing?

A technique for virtualizing the CPU that involves giving processes control of the CPU for a limited time.

A way for multiple programs to be stored in the same region of memory.

A mechanism for hardware peripherals to be used simultaneously.

A way to keep multiple copies of a file with the same name.

A can't-miss investment opportunity in Cancun.

---

From a process API standpoint, describe what happens when you type a command like ls at the shell, and that program runs.

The shell creates a new process with the program you specified, then waits for that process to complete before showing another prompt.

The shell exits as it hands control to the new program to run. Once that program is complete, the shell is restarted.

The shell creates a new process and then repeatedly checks to see if the process is still running. Once the process dies, a new prompt is shown.

The shell goes to sleep waiting for I/O when launching the process. When I/O is complete, it wakes up.

---

In C programs, what is the difference between the stack and the heap? What kind of data is stored on each?

The stack is where local variables and return addresses are stored. The heap is where dynamically-allocated data (like from malloc()) is stored.

The heap is where local variables and return addresses are stored. The stack is where dynamically-allocated data (like from malloc()) is stored.

The heap is where data is temporarily stored during disk I/O. The stack is where variables are stored.

The heap holds variables, both dynamic and local, while the stack holds information about network hardware.

---

What are things that could cause a process to enter the blocked state? How does a process get out of the blocked state?

Attempting to perform I/O when the data isn't readily available causes a process to become blocked. It will unblock as the data becomes available.

Deliberately yielding the CPU to other processes will cause this process to block. It becomes unblocked when it is scheduled to run again.

Keeping a window minimized causes the process to block. It will unblock when the window is expanded.

When there are too many processes running on the system, some of them become blocked. They become unblocked when they get scheduled.

Reading #random when you should be coding means your process is blocked.

---

[5 points]

What is the name of the part of the kernel that's responsible for deciding which process runs next?

Scheduler

Timesharer

Process Control Block

Master Control Program

Context Switcher

---

In Unix, how does a process enter the zombie state? How does it stop being a zombie?

It becomes a zombie when it exits. It stops being a zombie and vanishes when another process waits for it.

It becomes a zombie when it's blocked on I/O. When it becomes unblocked, it stops being a zombie.

It becomes a zombie when the program explicitly goes to sleep. It stops being a zombie when the OS wakes it up.

It becomes a zombie when the system shuts down. It stops being a zombie when the system boots again.

It becomes a zombie when it receives at least one byte from another zombie process.

---

What are the differences between a syscall (e.g. write()) versus a C library function call (e.g. sqrt())? What happens during a syscall that doesn't happen during a regular function call?

A system call runs in privileged kernel mode, whereas a library function runs in unprivileged user mode.

A library function runs in privileged kernel mode, whereas a system call runs in unprivileged user mode.

A system call handles I/O, whereas a library function handles privileged hardware.

A library function is a low-level part of the OS that interfaces with hardware, whereas a system call is part of the C library.

---

What is a Process ID (PID) in Unix? What type is it, and what does it represent?

It's an integer type that uniquely refers to an existing process.

It's a floating point type that uniquely refers to an existing process.

It's an integer type that refers to an existing process; processes may share an ID.

It's a floating point type that refers to an existing process; processes may share an ID.

---

After a fork() call returns to both the child and the parent, how does a process know if it's the child or the parent?

It returns the child PID to the parent, and zero to the child.

It returns the parent PID to the child, and zero to the parent.

If a processes parent PID is 1, it was the child process; otherwise it was the parent.

If a process receives the SIGCHLD signal, it is the child process.
