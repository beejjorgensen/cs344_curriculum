# All

-2 stdin reading broken, but file reading working

-5 Makefile there, but not the right one and doesn't build everything

# Yell/MyCat

-0 You don't need to `open()` file descriptor `0`. The OS opens it for you automatically.

-2 Only worked from stdin, not from the file

-2 Only worked from file, not from the stdin

-3 read and write don't happen in a loop until EOF

-2 read and write don't happen in a loop until EOF in the case of the files.

-2 Doesn't loop through multiple files on the command line correctly

-1 argv[0] is the command name, not the first argument. Counting needs to start at 1.

-2 When you read(), there's no guarantee there will be a NUL terminator on the data. This was causing some of my tests to fail. When I replaced with a counting loop up to `readBytes`, it started working.

# Yell

-0 sizeof evaluates to type `size_t` which is unsigned while `int` is signed. Make your comparison variable either `size_t` or `unsigned int` to fix.

-1 inner loop used the same variable as the outer loop, causing badness

-1 Yell is the same as cat for output with files.

# Misc

-0 Please try to follow the exact output as shown in the project spec. Otherwise it breaks my tests!
