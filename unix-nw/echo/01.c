#include <errno.h>

#include "unp.h"

void str_echo(int clientfd);

int
main(int argc, char *argv[])
{
    int serverfd;
    struct sockaddr_in serveraddr;

    serverfd = Socket();

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);

    Bind(serverfd, &serveraddr);
    Listen(serverfd);

    for (;;) {
        int clientfd;
        struct sockaddr_in clientaddr;
        pid_t pid;

        clientfd = Accept(serverfd, &clientaddr);

        if ((pid = fork()) == 0) { // child process
            Close(serverfd);

            str_echo(clientfd);

            exit(EXIT_SUCCESS);
        }

        Close(clientfd);
    }

    return 0;
}

void str_echo(int clientfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while ((n = read(clientfd, buf, MAXLINE)) > 0)
        write(clientfd, buf, n);
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        perror("str_echo: read error");
}
