#include "unp.h"

int
Socket()
{
    int sockfd, opt;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror("socket");


    opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    return sockfd;
}

void
Bind(int sockfd, struct sockaddr_in *address)
{
    if (bind(sockfd, (struct sockaddr *) (&*address), sizeof(*address)))
        perror("bind");
}

void
Listen(int sockfd)
{
    if (listen(sockfd, BACKLOG) < 0)
        perror("listen");
}

int Accept(int sockfd, struct sockaddr_in *address)
{
    int acceptfd;
    socklen_t size = sizeof(*address);

    acceptfd = accept(sockfd, (struct sockaddr *) &*address, &size);
    if (acceptfd < 0)
        perror("accept");

    return acceptfd;
}

void
Connect(int sockfd, struct sockaddr_in *address)
{
    if (!connect(sockfd, (struct sockaddr *) &*address, sizeof(*address))) {
        perror("connect");
    }
}

void
Close(int sockfd)
{
    close(sockfd);
}
