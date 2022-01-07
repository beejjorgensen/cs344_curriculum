#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: readfile filename\n");
        return 1;
    }

    int fd;

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        return 2;
    }

    char buf[4096];
    int bytes;

    if ((bytes = read(fd, buf, sizeof buf - 1)) == -1) {
        perror("read");
        return 3;
    }

    write(1, buf, bytes);

    close(fd);
}
