# Nodes Padded

-10 block size wasn't padded out with `PADDED_SIZE(BLOCK_SIZE)` when returning pointer

# Data Padded to Proper Alignment 

There's no way to make this wrong in this assignment.

# Return NULL in myalloc

-10 `myalloc` was missing return NULL--the compiler warned about it

# Traverse List

-5 Forgot to move the linked list pointer to next

-2 Should be <= to see if it fits

-4 couldn't find any free space because the inequality on the `if` was backward

# Other

Don't check build products into source control!

!cur->in_use would also work.
