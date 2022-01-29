#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define DATA_FILE "fincrement.dat"

#define NUM_PROCESSES 80

void init_datafile(void)
{
    int fd;

    if ((fd = open(DATA_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
        perror("open");
        return;
    }

    int initial_value = 0;

    write(fd, &initial_value, sizeof(int));

    close(fd);
}

void increment(void)
{
    int fd;

    if ((fd = open(DATA_FILE, O_RDWR)) == -1) {
        perror("open");
        return;
    }

    //flock(fd, LOCK_EX);

    int value;

    read(fd, &value, sizeof(int));

    value++;

    lseek(fd, 0, SEEK_SET);

    write(fd, &value, sizeof(int));

    //flock(fd, LOCK_UN);

    close(fd);
}

int read_value(void)
{
    int fd;

    if ((fd = open(DATA_FILE, O_RDONLY)) == -1) {
        perror("open");
        return -1;
    }

    int value;

    read(fd, &value, sizeof(int));

    close(fd);

    return value;
}

int main(void)
{
    init_datafile();

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (fork() == 0) {
            increment();
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++)
        wait(NULL);

    int value = read_value();

    printf("%s news: value is %d (expected %d)\n",
        value == NUM_PROCESSES? "Good": "Bad", value, NUM_PROCESSES);
}
