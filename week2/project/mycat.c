#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 2048

void mycat(int fd)
{
    char buf[BUFSIZE];
    int bytes;

    while ((bytes = read(fd, buf, sizeof buf)) > 0) {
        if (write(1, buf, bytes) == -1) {  // stdout
            perror("write");
            return;
        }
    }

    if (bytes < 0) {
        perror("read");
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        mycat(0);  // stdin

    } else {
        for (char **p = argv + 1; *p != NULL; p++) {
            int fd = open(*p, O_RDONLY);

            if (fd == -1) {
                perror(*p);
                continue;
            }

            mycat(fd);

            close(fd);
        }
    }
}
