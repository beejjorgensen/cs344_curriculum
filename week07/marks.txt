For the Makefile to work, you need to put a tab character in front of the command lines. Spaces won't do; they'll give you the "missing separator" error. You might have to change settings in your editor.

---------------

There's a very subtle bug in the free code that gets exposed if you rearrange the struct block so the next pointer is the middle field. myfree() stops marking blocks as freed.

Right now it works if the padded struct block is 16 bytes, but rearranging the fields so the padded block is 32 bytes shows the breakage.

It's in the code that searches to find the pointer the user passed in. The `+1` adds the offset of an unpadded `struct block` to the pointer--the unpadded part is what breaks it.

If n points to the struct block, the user data must be the padded struct block size number of bytes past that pointer.

And the PTR_OFFSET macro does that math.

So the comparison should be:

if (pointer == PTR_OFFSET(n, PADDED_SIZE(sizeof(struct block)))) {

-5 Free doesn't find the proper struct block location with padded structs.

Secondly, if you know the pointer the user passed in, you should be able to compute the location of the struct block, since you know it's directly before it.

struct block *b;
b = PTR_OFFSET(pointer, -PADDED_SIZE(sizeof(struct block)));
b->in_use = 0;

That way you don't need a loop.

-------------

This code corrupts the list:

p = myalloc(500);
print_data();
q = myalloc(16);
print_data();
myfree(p);
print_data();
p = myalloc(32);
print_data();

I get this output:

[512,used] -> [480,free]
[512,used] -> [16,used] -> [448,free]
[512,free] -> [16,used] -> [448,free]
[32,used] -> [464,free]

Notice how the remaining list is far less than 1024 total.

This line of code:

split_node->next = NULL;

only handles splits at the end of the list.

To wire the new node in correctly, it needs to be:

split_node->next = s->next;

-5 split node only half-wired-in.

-------------

There are a couple bugs in here that don't compute the padding properly on the struct block.

In myalloc(),

return p + 1

gives a pointer back with the unpadded struct block size added to p.

This is fine if there's no padding on the struct, but when there is, the offset is computed improperly.

[0x10811a000:16,used] -> [0x10811a028:944,free]

Note that the second address is not a multiple of 16 (the last hex digit would be 0 if it were).

So I get pointers back at offset 24, which isn't a multiple of 16, when I expected 32.

That's still past the struct block, but its in the struct block's padding space.

It should be:

return PTR_OFFSET(p, PADDED_SIZE(sizeof(struct block)));

but if I fix that and then run code that allocates 16 bytes and then fills them all with 0xff, I end up with a list that looks like this:

[0x10cc0c000:16,used] -> [0x10cc0c028:-1,free]

Which clearly isn't right. My writing to the space is trampling the next struct block.

There's another complementary issue in split_space() when computing the next pointer:

(*p)->next = (struct block *) (((char*)((*p) + 1)) + PADDED_SIZE(size));

That +1 is moving ahead the size of a struct block, not the size of a padded struct block.

Fixing with:

(*p)->next = PTR_OFFSET(*p, PADDED_SIZE(sizeof(struct block)) + PADDED_SIZE(size));

brings it to working order again, now both with padded and unpadded struct blocks.

[0x10b3da000:16,used] -> [0x10b3da030:944,free]

Note that all the addresses are now multiples of 16.

Looks like I missed this on grading project 6, so I'm going to drop 7 points here for misalignment on the blocks (but not the data).

-------------

-5 proper size for split not computed entirely correctly

-5 new linked node not fully wired in

-5 split's new node not marked not-in-use

-7 free doesn't compute proper block location
