<!-- Exploration 1.2: Shell Scripts and Regular Expressions -->

## Shell Scripts

Shell scripts are programs that are run by the shell (e.g. bash, zsh,
etc.)

These scripts are surprisingly capable and can be used to automate
common tasks.

Every language has its relative strengths. Shell scripts are good at
dealing with running commands and processing their output. They can run
any specified command line program.

Example uses might be:

* Getting web pages and data periodically with curl
* Generating code
* Mass converting image files
* Automatically sending email messages
* Acting as a memorable alias for a series of easily-forgotten commands.

## Creation and Execution

All you need to do to create a shell script is bring up your favorite
editor and put the commands in the script you want to run, one per line.

For example, put these lines in a file called `dateping` to print the
date and time, and then ping a host three times:

```
date
ping -c 3 example.com
```

Then to run it, just type this on the command line (here `%` is the
prompt--maybe you have `$` instead):

```
% sh dateping
```

You could also specify `bash` or `zsh` instead of `sh`. These are all
different shells, but all are POSIX shell compliant, which means they
share common basic functionality.

## Shebangs

It's common at the top of a shell script to find this as the first line:

```
#!/bin/sh
```

(Again, other shells are possibly specified.)

This form is called a
[_shebang_](https://en.wikipedia.org/wiki/Shebang_(Unix)). This lets the
OS know what program to use to run this script.

If you also make the script executable like so:

```
% chmod u+x myscript
```

you can just run it directly on the command line, no need to put `sh`
before it:

```
% ./myscript
```

For more information, see [How the OS Runs Programs]().

## More Power

Though we won't be using it for this module, shell scripts are
full-fledged programming languages, complete with loops, variables, and
conditionals. If you want to see examples, check out the resources,
below.

## Resources

* [Bend Hackers Guild bash
  Cheatsheet](https://docs.google.com/document/d/12lT81cndJz25MFEYUY6O5xEnY5tBqJpCU4rMERbMq9Q/edit?usp=sharing)

## Regular Expressions

Regular expressions, or _regexes_ for short, describe a pattern to be
matched. A program such as `grep`, `vim`, or `sed` will use regular
expressions in a number of ways. All modern languages include regular
expression support in code.

> **Note about `grep`**: When you run it, run `egrep` or, equivalently,
> `grep -E`. This gives access to a more modern set of regular
> expressions. If you find `+` isn't working in your regex, this is
> probably why.

Think of them like search terms... only more powerful.

Here's an example of a regular expression: `xyz`. It matches literally
`x`, followed by `y`, followed by `z`.

Not very exciting. How about `x`, followed by any letter, followed by
`z`? Here it is: `x.z`. The period matches any letter.

How about a regular expression that matches
[`xyzzy`](https://en.wikipedia.org/wiki/Xyzzy_(computing)) or `xyzzzy`
or `xyzzzzy`--that is, two or more `z`s in the middle. Answer: `xyzz+y`.
The characters `z+` match one or more `z`s.

I hope you're getting the idea that regular expressions are fairly
powerful for pattern matching.

For shell scripts, `grep` (`egrep`!) is a tool commonly used. It prints
lines that contain the regular expression match. Let's use it to search
a file `foo.txt` for any of those `xyzzy` variants:

```
% egrep 'xyzz+y' foo.txt
```

And the `sed` program uses regexes for search and replace. For example,
you can replace all instances of `foo` with at least two `o`s with
`bar`:

```
% sed 's/foo+/bar/g' foo.txt
```

(The `/g` at the end instructs sed to make the replacement
"globally"--throughout the line, not just the first occurrence.)

Here are more examples of what you can match with regular expressions:

<!-- caption: Regular Expressions -->
|Regex|Description|
|-|-|
|`xyz`|Match literal string `xyz`|
|`^`|Match beginning of the line|
|`$`|Match end of the line|
|`[abcdef]`|Match any character in set|
|`[^abcdef]`|Match any character not in the set|
|`[A-F]`|Match any character capital `A` through `F`, inclusive|
|`[A-Fx]`|Match any character capital `A` through `F`, inclusive, or the letter `x`|
|`.`|Match any character|
|`x+`|Match 1 or more `x` characters|
|`y*`|Match 0 or more `y` characters|
|`.+`|Match 1 or more of any character|
|`^[Xx]yzz+y$`|Match lines that begin with capital or lowercase `x`, followed by `yz`, followed by 1 or more `z`s, ending with a `y`|
|`\. \+ \* \\`|Match literal `.`, `+`, `*`, or `\`, or any special character by adding a `\` escape|

Check the resources for a playground to test regular expressions.

## Resources

* [Regexr.com](https://regexr.com/) -- test regular expressions

## Reflect

* What is a shell script?
* How does a shebang work?
* What does a regex do?
* Can you write a regex that matches any two-digit number except 10 through 19?
