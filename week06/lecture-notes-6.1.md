# Lecture Notes 6.1

## Talk about C pointers and messing around in a solid chunk of memory.

How we can have a pointer to a struct that points to somewhere in that
big chunk.

```
struct foo {
    int x, y;
};

char *data = malloc(1024);

struct foo *p;

p = data;
p = data + 1;  // Probably misaligned
p = data + 16; // Aligned
p = data + 2;  // Maybe aligned
p = data + 4;  // Likely aligned
```

Draw a memory map of how that's working

## Pointer Arithmetic with different types

```
char *p;
int *q;

// difference between

p + 1
q + 1
```

## Alignment

Describe

Can be forced with padding

## Padding

Describe what it is

```
#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (x - 1) & (ALIGNMENT - 1))
```
