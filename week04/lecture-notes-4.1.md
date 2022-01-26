# Lecture Notes 4.1

## Overview

* Goal: communication between processes
* `fork()` and copied runtime data
* `fork()` and the system-wide open file table
* `pipe()` details
* `dup()` details

## Fork copied data

Variables are copies.

Demo

## Fork system-wide open file table

Demo with graphic from Exploration 4.1

Demo with writing to a file from two processes post fork

## Pipe

Demo single process read/write from pipe

Demo multiple process read/write from pipe

* One process should be read-only, the other write-only. Don't mix and
  match.

## Dup

Demo with graphic from Exploration 4.1

You can make it so reading from stdin (fd 0) comes from another fd
You can make it so writing to stdout (fd 1) goes to another fd

Demo Make it so stdout goes to a file instead.