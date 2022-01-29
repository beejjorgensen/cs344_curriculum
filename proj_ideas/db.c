#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define ENTRY_COUNT 1000
#define RECORD_SIZE 16

void child_main(void)
{
    int fd = open("db.txt", O_RDWR);
    char rec[RECORD_SIZE+1];

    for (int i = 0; i < ENTRY_COUNT; i++) {
        lseek(fd, -RECORD_SIZE, SEEK_END);

        read(fd, rec, RECORD_SIZE);

        rec[RECORD_SIZE] = '\0';

        int rec_num;
        sscanf(rec, " %d", &rec_num);

        rec_num++;

        sprintf(rec, "%*d", RECORD_SIZE, rec_num);
        lseek(fd, 0, SEEK_END);
        //write(fd, )
    }

    close(fd);
}

void initdb(void)
{
    char rec0[RECORD_SIZE+1];

    sprintf(rec0, "%*d", RECORD_SIZE, 0);

    int fd = open("record.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, rec0, RECORD_SIZE);
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: commentdb count\n");
        return 1;
    }

    int process_count = atoi(argv[1]);

    if (process_count < 1 || process_count > 20) {
        fprintf(stderr, "commentdb: count must be in range 1-20\n");
        return 1;
    }

    initdb();

    int actual_count = 0;

    for (int i = 0; i < process_count; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            continue;
        }

        actual_count++;

        if (pid == 0) {
            // Child
            child_main();
            exit(0);
        }
    }

    for (int i = 0; i < actual_count; i++) {
        wait(NULL);
    }
}