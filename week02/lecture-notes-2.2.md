# Lecture Notes 2.2

Basically following Exploration 2.2.

* Go over basic scheduling again
  * Instructions and data are stored in memory
  * Show processes in various states
  * Show how they move between states
* Talk about Limited Direct Execution
  * What it is
  * Why is it important?
    * Why give the process full control of the CPU?
    * Why limit its access?
* Break
* Talk about the Unix API for making new processes
  * What is a PID?
  * Shared variables after `fork()`
  * Talk about zombie processes and the relation to init
