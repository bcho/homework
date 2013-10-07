#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096

void oops(char *, char *);

int main(int argc, char *argv[])
{
    int src_fd, dest_fd, nbytes;
    char buf[BUFSIZE];

    if (argc != 3) {
        fprintf(stderr, "usage: %s source destination\n", argv[0]);
        exit(1);
    }

    if ((src_fd = open(argv[1], O_RDONLY)) == -1)
        oops("Cannot open", argv[1]);

    if ((dest_fd = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        oops("Cannot creat", argv[2]);

    while ((nbytes = read(src_fd, buf, BUFSIZE)) > 0)
        if (write(dest_fd, buf, nbytes) != nbytes)
            oops("Wrinte error to", argv[2]);

    if (nbytes == -1)
        oops("Read error from", argv[1]);

    if (close(src_fd) == -1 || close(dest_fd) == -1)
        oops("Error closing files", "");

    return 0;
}

void oops(char * a, char * b)
{
    fprintf(stderr, "Error: %s\n", a);
    perror(b);
    exit(1);
}
