#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//#define TRIALS 500
//#define ATM_COUNT 10
#define TRIALS 1
#define ATM_COUNT 5

#define INITIAL_BALANCE 150
#define WITHDRAWAL_AMOUNT 100

#define DATA_FILE "banker.dat"

void init_balance(int balance)
{
    int fd;

    if ((fd = open(DATA_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1) {
        perror("open");
        return;
    }

    write(fd, &balance, sizeof(int));

    close(fd);
}

void withdraw(int amount)
{
    int fd;

    if ((fd = open(DATA_FILE, O_RDWR)) == -1) {
        perror("open");
        return;
    }

    int balance;

    read(fd, &balance, sizeof(int));
    printf("[%d]: balance=%d\n", getpid(), balance);
    sleep(1);

    if (balance >= amount)
        balance -= amount;

    lseek(fd, 0, SEEK_SET);

    write(fd, &balance, sizeof(int));

    close(fd);
}

int get_balance(void) {
    int fd;

    if ((fd = open(DATA_FILE, O_RDONLY)) == -1) {
        perror("open");
        return -1;
    }

    int balance;

    read(fd, &balance, sizeof(int));

    close(fd);

    return balance;
}

int main(void)
{

    for (int _ = 0; _ < TRIALS; _++)
    {
        init_balance(INITIAL_BALANCE);

        int fcount = 0;

        for (int _ = 0; _ < ATM_COUNT; _++) {
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                continue;
            }

            fcount++;

            if (pid == 0) {
                withdraw(WITHDRAWAL_AMOUNT);
                exit(0);
            }
        }

        for (int _ = 0; _ < fcount; _++)
            wait(NULL);

        int balance = get_balance();

        int expected_balance = INITIAL_BALANCE - WITHDRAWAL_AMOUNT;

        if (balance != expected_balance) {
            printf("Balance was %d (expected %d)\n", balance, expected_balance);
        }
    }
}

