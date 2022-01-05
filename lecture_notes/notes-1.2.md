# Notes 1.2

## OS

* Review: The OS is responsible for controlling access to hardware and resources, and virtualizing components of the system.

* Review virtualizing
  * CPU
  * RAM
  * Disks
  * Processes don't have to worry (much!) about stepping on toes
    * Counterexample: writing files, more on that later 
  * Makes it easier to write programs when you don't have to worry about any of this; the OS takes a load off.

## Shebangs

* Demo a script with a `#!`
* Demo `chmod +x` and `chmod 700`
* Talk about how the OS knows what kind of program to run
  * Hexdump a binary, Mach-O 64 begins with 0xfeedfacf
  * Hexdump a shell script, begins with `#!`
  
## Regular Expressions

* Pattern matching
* A language that describes a pattern
* Uses
  * Search
  * Search and Replace
  * Extract
* Programs
  * Commonly `vim`, `sed`, `grep`
  * But many others
* Programming languages
  * Modern ones support it out of the box
  * Great for text processing, finding, replacing
  * Beej uses these to process special commands in the sources for his guides.
  * C's too old--need a 3rd-party library to do it
    * Kernighan and Pike discuss how to write a simple regex matcher in _The Practice of Programming_.

### Examples

Use `grep` to find things in directory listings, or in the dictionary (`/usr/share/dict/words`)

* `a...c` - a followed by any three letters followed by c
* `a...[cde]` - same, followed by c, d, or e.
* `^[aeioy]` - words that start with vowels
* `[^aeioy]$` - words that don't end with vowels
* `^[a-c]e[b-d]` - words that begin with a-c, followed by e, followed by b-d
* `^[qwerasdfzxcv]*$` - words that you can type entirely with your left hand

Bring up a file or the dictionary in vim and show some searches.

Make up a file in vim with a bunch of jpeg names:

```
keyboardcat.jpeg
foojpeg.jpeg
bar.jpg
```

Do a `:%s/jpeg/jpg/` and see what happens. Fix with `:%s/jpeg$/jpg/`.

## Post-class

* Make sure gcc is running everywhere.
* Do a hello world program with everyone.