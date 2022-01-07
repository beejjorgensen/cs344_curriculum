#include <stdio.h>   // perror
#include <unistd.h>  // close
#include <fcntl.h>   // open
#include <ctype.h>   // toupper

#define BUFSIZE 2048

void upper(int fd)
{
    char buf0[BUFSIZE];
    char buf1[BUFSIZE];
    int bytes;

    while ((bytes = read(fd, buf0, sizeof buf0)) > 0) {

        char *p0 = buf0;
        char *p1 = buf1;

        for(int i = 0; i < bytes; i++) {
            if (!isdigit(*p0)) {
                *p1++ = *p0;
            }

            p0++;
        }

        if (write(1, buf1, p1 - buf1) == -1) {  // stdout
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
        upper(0);  // stdin

    } else {
        for (char **p = argv + 1; *p != NULL; p++) {
            int fd = open(*p, O_RDONLY);

            if (fd == -1) {
                perror(*p);
                continue;
            }

            upper(fd);

            close(fd);
        }
    }
}
