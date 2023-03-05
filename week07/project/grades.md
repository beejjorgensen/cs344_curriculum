Signed/unsigned warning on a comparison. `sizeof` returns type `size_t`, and you can cast your `int` to that to avoid the warning.

# Split only splits if there's the proper amount of room

-4 

This should only happen if a split occurred:

b->size = padded_requested_space;

If a split did not occur, the block size should remain unchanged.

If I had:

[16,used] -> [32,free] -> [32,used]

and then I allocated 16 bytes, it would change it to:

[16,used] -> [16,used] -> [32,used]

when in fact that block size was still 32 bytes.


-7 Doesn't handle case when allocating all the space, or almost all of it. There shouldn't be a split in that case.


-4 Can't allocate 1008 bytes even when 1008 bytes are available.

I think there might be a regression here around the split code.
