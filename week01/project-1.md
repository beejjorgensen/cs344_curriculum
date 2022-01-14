<!-- Project 1: Shell Scripting -->

## Introduction

For this project, we want to use the power of shell scripts to get work
done in a more automated sense.

We'll be using either bash or zsh shells, which you should have already
installed if you have a Mac, Linux, WSL, or some other Unix-like OS.

The simplest shell script is a file that contains commands to run in
sequence. For example, if a file called, arbitrarily, `datedir` contains
this:

```
date
ls
```

And you run it from the command line like this (assuming `%` is your shell prompt):

```
% sh datedir
```

you should get the output of those two commands in sequence.

You can bundle as many commands as you want together this way.

But wait! There's more!

## Pipes

You can take the output of one command and pipe it into another with the `|` symbol.

Lots of commands can be strung together this was. For instance, we know
ls -la will give us a long directory listing of all files as output, but
what if there are so many that they scroll off the screen?

There's another program called `more` that will read input, and pause
each page waiting for you to hit the space bar.

If only there were a way to pipe the output of `ls` into the input of
`more`...

Of course there is. Let's try it on a directory that's likely to have a
lot of files first without the pipe and watch it hopefully scroll off
the screen:

```
% ls -la /usr/lib
```

And then with more:

```
% ls -la /usr/lib | more
```
(You read that as "ls minus L A user lib piped to more".) Try it!

## Helpful utilities

<!-- caption: Common Utilities -->
|Command|Description|
|-|-|
|`echo "Hello, world!"`|Print a message as output|
|`curl https://example.com/`|Get data at a URL and print it as output|
|`curl https://example.com/ --output example.html`|Get data at a URL and save it to a file|
|`tr -s " "`|Collapse spaces|
|`grep regex`|Print out lines that match a regular expression|
|`cut -d' ' -f 2,4`|Cut fields 2 and 4 from a space-delimited line|
|`head`|Print out the first 10 lines of input|
|`tail`|Print out the last 10 lines of output|
|`head -n 3`|Print out the first 3 lines|
|`tail -n 4`|Print out the last 4 lines|
|`sort`|Sort lexicographically|
|`sort -n`|Sort numerically|

For example, to cut out file sizes and names from a `ls -la` directory
listing, we could first run `ls -la`, then pipe it into `tr` to collapse
the spaces, then pipe that into `cut` to pull out those specific fields:

```
% ls -la /usr/bin | tr -s " " | cut -d' ' -f 5,9
```

to get output like this:

```
3 captoinfo
77 caspol
43232 cat
3273 catchsegv
43392 catman
```

Each step of the pipeline take the output from the previous step as
input. And it and gives its output to the next step as input. You can
use this to powerfully transform data. 

You can look up more information on how to use these utilities with the
built-in manual:

```
% man sort
```

to get details of the `sort` command.

## Regular Expressions 

AKA regexes for short, these are sequences of characters that describe a
pattern to match. You can use this to find lines in a file or input that
is piped to the `grep` command. ("grep" is pronounced as a single
syllable, short for Global Regular Expression Print.)

Let's find all the files in a directory listing that have the string
`ab` in them:

```
% ls /usr/local/bin | grep ab
```

Example output:

```
crontab
iptab
snmptable
tab2space
tabs
```

Notice how all those have the string `ab` in the name somewhere.

But regular expressions are far more powerful than that. You can add
special characters to the regular expression that match specific parts
of the line.

For example, the caret `^` matches the beginning of a line. Let's use
that--note that often regexes on the command line are wrapped in single
quotes to keep the shell from interpreting them.

Find all the directories in an `ls` listing; these are the lines that
start with `d` in a long listing.

```
% ls -l | grep '^d'
```

In that regex, `^` matches the beginning of the line, immediately
followed by a letter `d`. Lines that meet that description will be
printed.

Other special regex characters, an incomplete list:

<!-- Caption: Regular Expressions -->
|Regex|Description|
|-|-|
|`xyz`|Match literal string `xyz`|
|`^`|Match beginning of the line|
|`$`|Match end of the line|
|`[abcdef]`|Match any character in set|
|`[^abcdef]`|Match any character not in the set|
|`[A-F]`|Match any character capital `A` through `F`, inclusive|
|`[A-Fx]`|Match any character capital `A` through `F`, inclusive, and the letter `x`|
|`.`|Match any character|
|`x+`|Match 1 or more `x` characters|
|`y*`|Match 0 or more `y` characters|
|`.+`|Match 1 or more of any character|
|`^[Xx]yzz+y$`|Match lines that begin with capital or lowercase `x`, followed by `yz`, followed by 1 or more `z`s, ending with a `y`|
|`\. \+ \* \\`|Match literal `.`, `+`, `*`, or `\`, or any special character by adding a `\` escape|

## Variables, flow control, and more

The shell holds a powerful and complete programming language. It can,
among other things:

* Process command line arguments in a script
* Handle while and for loops, and conditionals
* Define and modify variables
* Define functions
* Read user input
* Read input a line at a time, processing each line

Though beyond the scope of what we'll do in this class, it would be
worth looking up more information on these topics. It can be a powerful
addition to your programming toolkit.

## What to do

Make a new github repo for this project.

Don't forget: if anything is unclear or vague in the specification, it's
your job as a software developer to ask questions until you understand
the problem fully! This is true here and on the job.

### 1. Big Files

Write a shell script called `bigfiles` that prints out a directory
listing with each file size followed by its name of the 7 largest files
in the `/usr/bin` directory. The sizes and files should be sorted in
descending (reverse) order with the largest file first.

Think of how you can pipe commands together to make this happen in a
single line.

Example output:

```
15181424 fileproviderctl
12455552 parl5.30
6045856 kmutil
4693872 vim
3898064 sqlite3
3780304 dig
3762464 delv
```

### 2. Command Line Arguments

A special variable `$1` holds the first command line argument for a
script. Write a script called `arg1` with one line:

```
echo $1
```

Then run it like this:

```
% sh arg1 Hello
```

You should see `Hello` on the output, or whatever you typed as an
argument. Any place `$1` is placed in the script, whatever you typed for
the first argument will be substituted there.

### 3. Saving Web Data

Like with `$1`, `$2` is the second command line argument. Write a script
called `geturl` that gets a file from a URL and saves it with the given
filename, like so:

```
% sh geturl https://example.com/ example.html
```

Hint: if you're using `curl`, using the `-s` flag will put it in
"silent" mode and cause it to not output the progress information.

### 4. Generalizing `bigfiles`

Copy the `bigfiles` script from part 1 to `bigfiles2` and modify it to work
on the directory specified as a command line argument.

For testing, in Unix, a single period `.` means "the current directory",
and `..` means the parent directory.

### 5. Grepping with Regexes

Write a shell script called `vowelending` that will show all filenames
(including the extension--`foo.txt` should not match) of a directory
specified on the command line that end with a vowel, upper or lowercase.
Use `ls -a` to get the directory listing.

### 6: Grepping Part 2

Write a shell script called `findlink` that takes a URL as an argument
and prints the lines that match an anchor tag, that is, tags beginning
with `<a`. Don't forget the single quotes around that regex!

## What to turn in

Submit the link to your GitHub repo.

## Grading criteria

This assignment is worth 50 points.

Due Sunday at midnight.

Be sure to consult the rubric for expectations regarding your submission.

## Extensions

If you want more challenge--and you do--try these out. (They don't
contribute to your class score--only to your personal XP as a
developer!) [The Bend Hackers Guild Bash
Cheatsheet](https://docs.google.com/document/d/12lT81cndJz25MFEYUY6O5xEnY5tBqJpCU4rMERbMq9Q/edit)
might be useful.

### 1. Atomic Clock Time

If you have the `telnet` program installed (install it if you don't),
you can get the current time of day (in Universal Coordinated Time) like
this:

```
% telnet time.nist.gov 13
```

Example output from the above command:

```
Trying 132.163.97.3...
Connected to ntp1.glb.nist.gov.
Escape character is '^]'.

59576 21-12-28 03:14:42 00 0 0 616.6 UTC(NIST) *
Connection closed by foreign host.
```

The "Connection closed by foreign host" message isn't actually going to
standard output--it's going to another output stream called standard
error. You can suppress it by redirecting standard error into a special
file /dev/null before piping telnet's output into anything:

```
% telnet time.nist.gov 13 2> /dev/null
```

Write a shell script that prints out only the date and time from the
above command. Then follows it with the current system date and time in
[UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time), which
can be obtained with `date -u`.

Example output:

```
21-12-28 03:10:04
Tue Dec 28 03:10:03 UTC 2021
```

Look at the manual page for the `date` command (`man date`) to see how
to make the output match exactly with format specifiers, if you want
even more power. (Depending on your system, the man page might tell you
to also `man 3 strftime` for more information.)

### 2. Line by Line Processing

Write a shell script that reads lines of a file and prints them out with
their line number prepended. For example, for a file `input.txt` that
contains this:

```
If you spend too much time thinking
about a thing, you’ll never get it
done. Make at least one definite move
daily toward your goal.

    --Bruce Lee
```

The program should output this:

```
%  sh showlines input.txt
Line 1: If you spend too much time thinking
Line 2: about a thing, you’ll never get it
Line 3: done. Make at least one definite move
Line 4: daily toward your goal.
Line 5:
Line 6: --Bruce Lee 
```

Hints:

You can read lines with something like this, where the lines get
repeatedly read into the line variable:

```
cat infile.txt | while read line
```

There's more to it, but search for the net for `bash while loop` for
examples. 

Variables can be defined like this (no spaces around the `=`!)

```
foo=123
```

You can do math substitutions with the `$(())` construct. For example, to assign `y = x + 7`:

```
y=$(($x + 7))
```

#### 3. Random Lines

There used to be a program on Unix machines called
[`fortune`](https://en.wikipedia.org/wiki/Fortune_(Unix)) that would
print out a random saying each time it was run.

As an homage to `fortune`, write a shell script `randline` that prints
out a random line from the specified file each time you run it.

Hint: bash and zsh both have a built-in variable called `RANDOM` that
you can use to get random numbers.

```
%  echo $RANDOM 
9271
%  echo $RANDOM
23314
%  echo $RANDOM
21342
```

<!--
Rubric

bigfiles works properly (10)
arg1 works properly (5)
geturl works properly (5)
bigfiles2 works properly (10)
vowelending works properly (10)
findlink works properly (10)
-->
