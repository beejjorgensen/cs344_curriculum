# Lecture 4.2

* File demo
* Write code that opens a file, then forks, then writes single bytes
  out. Look at output.
  * Why doesn't it just alternate C,P?

```
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("foo.out", O_CREAT|O_WRONLY, 0644);

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    char *s = pid == 0? "C": "P";

    for (int i = 0; i < 10000; i++)
        write(fd, s, 1);

    close(fd);  // Do both the parent and the child have to close? yes.
}
```

## Cache review

* Cache hit
* Cache miss

## Multicore

* multicore with caches
* cache coherency
  * synchronization
  * briefly mention acquire/release semantics, more in the future

## File permissions

* open for writing
* open for read/write

* the file offset
    * lseek

