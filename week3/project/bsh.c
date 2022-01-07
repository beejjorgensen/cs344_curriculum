#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CL_LEN 2048
#define MAX_ARGS 128

#define WHITESPACE " \t\n\r"

void run_external(char *args[])
{
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror(args[0]);
        exit(1);
    } else {
        // Parent process
        wait(NULL);
    }
}

void run_cd(int count, char *args[])
{
    if (count != 2) {
        fprintf(stderr, "usage: cd directory\n");
        return;
    }

    if (chdir(args[1]))
        perror(args[1]);
}

void run_exit(int count, char *args[])
{
    if (count > 2) {
        fprintf(stderr, "usage: exit [status]\n");
        return;
    }

    int status;

    if (count == 1)
        status = 0;
    else
        status = atoi(args[1]);

    exit(status);
}

void run_command(int count, char *args[])
{
    if (strcmp(args[0], "cd") == 0)
        run_cd(count, args);

    else if (strcmp(args[0], "exit") == 0)
        run_exit(count, args);

    else
        run_external(args);
}

int main(void)
{
    char cl[MAX_CL_LEN];
    char *token;
    char *args[MAX_ARGS];

    for(;;) {
        printf("bsh$ ");
        fflush(stdout);

        fgets(cl, sizeof cl, stdin);

        if (feof(stdin))
            break;

        if ((token = strtok(cl, WHITESPACE)) != NULL) {
            int i = 0;

            do {
                args[i++] = token;
            } while ((token = strtok(NULL, WHITESPACE)) != NULL);

            args[i] = NULL;

            run_command(i, args);
        }
    }
}

