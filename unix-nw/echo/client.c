#include "unp.h"

void str_cli(FILE *fp, int sockfd);

int
main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serveraddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress>", argv[0]);
        return 1;
    }

    sockfd = Socket();

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);

    Connect(sockfd, &serveraddr);

    str_cli(stdin, sockfd);

    return 0;
}

void
str_cli(FILE *fp, int sockfd)
{
    char send[MAXLINE], recv[MAXLINE];

    while (fgets(send, MAXLINE, fp) != NULL) {
        write(sockfd, send, strlen(send));

        if (read(sockfd, recv, MAXLINE) == 0)
            perror("str_cli: server terminated prematurely");

        fputs(recv, stdout);
    }
}
