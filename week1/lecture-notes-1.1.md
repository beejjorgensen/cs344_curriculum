# Notes 1.1

## Introduction

* Industry experience
* Teaching experience

## Knowledge check

* Scale of 1-5 how familiar with
  * C
  * Unix user
  * Unix system programming

## Expectations

* Push yourself to excel
* No exams--you are in charge
* You're not competing against anyone else--just yourself
* More CS knowledge is created every day than you can learn in a day
* I'm here to guide and help, but you're going to be doing the heavy
  lift.
* No cheating, you can work together on understanding a problem and
  coming up with a plan, but solutions must be independent

## OS course overview

* This isn't an in-depth look at OS internals.
* Modern OSes represent thousands of person-years of work.
* The details are devilishly complex.
* But the overall view is relatively simple. That's what we'll do. Keep
  this in mind.
* Get used to the medium--the more comfortable you with it, the better.
* We'll go over some material, but won't necessarily use the whole two
  hours.
* Leftover time can optionally be used to work on projects in class.

## OS

* [Exploration 1.1 on screen]
* Discussion:
  * Why do we need something to manage this?
  * Why not just code up for the hardware directly?
  * Virtualization: why do this?

## Scripting

* Think of things you do on the command line frequently
* Small programs to automate them
* Pipes for power
* Can do really complex stuff, flow control, variables, etc.

## Demo

* Put three commands together.

## Demo, pipes

* Simple pipe to more

## Demo, pipes 2

* Manual page for stat
* Use stat to extract the size in bytes of a file by piping all kinds of
  commands
  
  `stat ./foo.py | head -n 2 | tail -n 1 | tr -s " " | cut -d' ' -f 3`



