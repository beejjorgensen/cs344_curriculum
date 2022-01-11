<!-- How Hard Links and Symbolic Links Work -->
Before we get into this, we have to step back just a bit and study a
little of how files are actually stored on disk.

We'll discuss:

* inodes
* Directories
* Hard Links
* Symbolic Links

## The Mighty inode

In Unixland, the metadata for a file on disk is stored in a data
structure (also on disk) called an _inode_ (pronounced "EYE-node", short
for "index node"). 

The inode contains things like:

* Who the owner is
* What group the file is in
* What the permissions on the file are
* What the size of the file is
* The time the file was created
* The time the file was last accessed
* A list of data blocks that hold the file's actual data
* The number of hard links to the file (more on this later)
* The type of the file, e.g.
  * Regular
  * Directory
  * Character device
  * Block device
  * FIFO
  * Symbolic link (more on this later)

So each file has one inode associated with it.

## The Directory

A directory is a list of inode/filename pairs. The directory is stored
on disk, with its corresponding inode of type "directory".

So in a way, a directory is a type of "file". It contains data, just
like any file. It's just not a "regular" file like we might store our
source code in.

Notice something interesting: _the inode does not contain the filename_.
Only the directory contains the filename!

The filenames are uncoupled from the file data and metadata. This frees
us up to have multiple filenames for the same file data. That is, we
could have two different directory entries (maybe even in different
directories) of filenames that both refer to the same inode.

## Hard Links

As opposed to symbolic links, sometimes these are just called "links".

A hard link is just another directory entry to the same file by a
different name.

By analogy, this is like writing a program where you have two variables
that both refer to the same object. There's only one object, but it has
two "names", in effect.

Likewise, when you link one filename to another, you end up with two
filenames that both refer to the same data. You could edit and modify
the file by either name.

Let's say I have a file, `hello.txt`, which is 6 bytes long. We can see
the size and the number of links to this file, below:

```
        link count        size
            |              |
            v              v
-rw-r--r--  1 beej  staff  6 Jan 11 10:12 hello.txt
```

So that file has 1 name in a directory somewhere (because the link count
is 1). And notice how `ls -l` spits out tons of data found in the inode!

Let's make another hard link. This gives that same file data another
additional name. Let's make that name `world.txt`:

```
%  ln hello.txt world.txt
```

And now if we `ls -l`:

```
        link count
            |
            v
-rw-r--r--  2 beej  staff  6 Jan 11 10:12 hello.txt
-rw-r--r--  2 beej  staff  6 Jan 11 10:12 world.txt
```

We see we have a link count of 2. This means there are 2 directories
that refer to this particular data.

You can remove the link with a regular `rm` command--all the does (for
any file!) is remove the directory entry and decrement the link count.

Once the link count falls to 0 (i.e. all the filenames in all the
directories that once referred to this data have been removed), the file
data and the inode are all freed, analogous to a garbage collector in a
high-level language.

But hard links have a few limitations:

* Since inodes are per-device (that is, all partitions on all disks have
  their own inodes), you can't hard link to a file on a different disk.
  These days, we tend to just have one disk per computer so it's not so
  much of an issue, but in the old days, there were racks of disks per
  computer.

* Hard links cannot refer to directories, only to regular files.

Symbolic Links help solve that.

## Symbolic Links

Remember how the inode stores the _type_ of file, like "regular",
"directory", etc.? One of those types is "symbolic link", or _symlink_.

While a hard link is a directory reference to an inode, the symbolic
link is a reference to another _path_.

This frees us from the hard link restriction of not being able to cross
devices or refer to directories. If it's something you can refer to in
the filesystem by path, you can get there with a symbolic link.

Because the path in the symbolic link must be parsed each time it is
used, the symlink is less efficient than a hard link, but not so much so
that we typically notice.

We can make a symlink with `ln -s`. Let's make a symlink to the file
`hello.txt` from the previous section. We'll call the symlink
`helloworld.txt`.

```
% ln -s hello.txt helloworld.txt
```

And now we see:

```
-rw-r--r--  2 beej  staff  6 Jan 11 10:12 hello.txt
lrwxr-xr-x  1 beej  staff  9 Jan 11 10:27 helloworld.txt -> hello.txt
-rw-r--r--  2 beej  staff  6 Jan 11 10:12 world.txt
```

There's the symlink, indicated by an `l` on the left of the listing, and
the `->` notation on the right.

Notice the hard link count to `hello.txt` (aka `world.txt`) remains 2,
from before. And notice the filesize of the symlink: 9 bytes. That's the
length of the link target: `hello.txt`, 9 characters.

Now if I try to view the file `helloworld.txt`, the OS does some things
first.

1. The OS looks in the current directory for that filename and its
   corresponding inode.
2. It looks in the inode and checks the filetype.
3. If it's a symlink:
   1. It gets the symlink destination ('hello.txt')
   2. And goes back to step 1.
4. Else if it's a file:
   1. It shows me the file.

In this way, it can follow symlinks from one to the next until it
reaches a real file.

But where is the symlink data stored? That is, we know `helloworld.txt`
is symlinked to `world.txt`. Where is all that?

The symlink name itself `helloworld.txt` is just stored in this
directory listing, like every other filename in this directory. And
there's a corresponding inode for it, just like for every filename in
every directory.

The symlink target is stored either:

* In that inode itself, if it fits. The inode is a fixed size, but some
  filesystems have enough room there. For example, the ext4 filesystem
  stores the symlink target in the inode if the target is less than 60
  bytes.
* In a data block that the inode points to, like a regular file. This is
  used if the filesystem doesn't support keeping the target in the
  inode, or the target doesn't fit in the inode. It's a little slower
  because another disk read must occur to get the data block.

  