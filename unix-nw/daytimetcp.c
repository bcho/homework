#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 1024
#define SERVER_PORT 5816
#define BACKLOG 15

int
main()
{
    int serverfd, clientfd;
    int opt;
    struct sockaddr_in serveraddr, clientaddr;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0)
        perror("socket");
    opt = 1;
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(SERVER_PORT);

    if (bind(serverfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)))
        perror("bind");

    if (listen(serverfd, BACKLOG) < 0)
        perror("listen");

    for (;;) {
        socklen_t size = sizeof(clientaddr);
        char buff[MAXLINE];
        time_t ticks;
        int pid;

        clientfd = accept(serverfd, (struct sockaddr *) &clientaddr, &size);
        if (clientfd < 0)
            perror("accept");

        if ((pid = fork()) == 0) { // child process
            close(serverfd);

            printf("connect from %s, port %d\n",
                    inet_ntop(AF_INET, &clientaddr.sin_addr, buff, sizeof(buff)),
                    ntohs(clientaddr.sin_port));

            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
            write(clientfd, buff, strlen(buff));
            close(clientfd);

            return 0;
        } else {
            printf("fork to %d\n", pid);
        }

        close(clientfd);
    }

    return 0;
}
