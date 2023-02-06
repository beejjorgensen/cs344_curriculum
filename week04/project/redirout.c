#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void usage_exit(void)
{
    fprintf(stderr, "redirout filename command [arg1 [arg2 ... ] ]\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        usage_exit();

    char *outfile_name = argv[1];

    int fd = open(outfile_name, O_CREAT|O_TRUNC|O_WRONLY, 0644);

    dup2(fd, 1);

    execvp(argv[2], argv + 2);
    perror(argv[2]);
    exit(1);
}
