#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage: redirout outfile command [option [...]]\n");
        exit(1);
    }

    char *filename = argv[1];

    // Make a pipe to connect the command's output
    int pfd[2];

    if (pipe(pfd) == -1) {
        perror("pipe");
        exit(2);
    }

    // Open the output file

    int fout = open(filename, O_CREAT | O_WRONLY, 0644);

    if (fout == -1) {
        perror("open");
        exit(2);
    }

    // Launch the command
    pid_t pid;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(2);
    }

    if (pid == 0) {
        // Connect the pipe on the write side
        dup2(pfd[1], 1);
        close(pfd[0]);

        execvp(argv[2], argv + 2);
        perror("exec");
        exit(2);
    }

    // Read everything from the read end of the pipe
    // and save it to a file

    int count;
    char buf[4096];

    close(pfd[1]); // Don't need the write end

    while ((count = read(pfd[0], buf, sizeof buf)) > 0) {
        write(fout, buf, count);
    }

    close(fout);
}