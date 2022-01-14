#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *filename;

    // Parse the command line

    switch (argc) {
        case 1:
            // If the user didn't specify, just use the current dir
            filename = ".";
            break;

        case 2:
            // Otherwise, use the directory specified
            filename = argv[1];
            break;

        default:
            fprintf(stderr, "usage: lswc [directory]\n");
            exit(1);
    }

    // Set up the pipe and run processes

    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        exit(2);
    }

    pid_t pid;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (pid == 0) {
        // Child can run wc
        dup2(fds[0], 0); // hook stdin (read) into pipe
        close(fds[1]);   // close unused write end
        execlp("wc", "wc", "-l", NULL);
        perror("child: exec");
        exit(3);
    }

    dup2(fds[1], 1); // hook stdout (write) into pipe
    close(fds[0]);   // close the unused (read) end

    execlp("ls", "ls", "-1a", filename, NULL);  // minus one A
    perror("parent: exec");
    exit(3);
}