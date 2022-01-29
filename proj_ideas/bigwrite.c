#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/file.h>

#define INDEX_FILE "bigwrite.index"
#define OUTPUT_FILE "bigwrite.out"

#define PROCESS_COUNT 10

#define WRITE_COUNT 128 

int create_file(char *filename, char *str)
{
    int fd;

    if ((fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
        return -1;

    if (str != NULL) {
        write(fd, str, strlen(str));
    }

    if (close(fd) == -1)
        return -1;

    return 0;  // Success
}

char increment_index(void)
{
    char buf;
    int fd;

    if ((fd = open(INDEX_FILE, O_RDWR)) == -1)
        return -1;

    read(fd, &buf, 1);

    char value = buf;
    buf++;

    lseek(fd, 0, SEEK_SET);

    write(fd, &buf, 1);

    close(fd);

    return value;
}

int main(void)
{
    create_file(INDEX_FILE, "0");
    create_file(OUTPUT_FILE, NULL);

    int process_count = 0;

    for (int _ = 0; _ < PROCESS_COUNT; _++) {
        pid_t pid;

        if ((pid = fork()) == -1) {
            perror("fork");
            continue;
        }

        process_count++;

        if (pid == 0) {
            // child
            int fd;

            if ((fd = open(OUTPUT_FILE, O_WRONLY|O_APPEND)) == -1) {
                perror("open outputfile");
                exit(1);
            }

            flock(fd, LOCK_EX);

            char index = increment_index();


            for (int i = 0; i < WRITE_COUNT; i++) {
                write(fd, &index, 1);
            }

            flock(fd, LOCK_UN);

            exit(0);
        }
    }

    for (int _ = 0; _ < process_count; _++)
        wait(NULL);
}

