#ifndef UNP_H
#define UNP_H

/* basic stuffs */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* basic config */
#define MAXLINE 1024
#define SERVER_PORT 5816
#define BACKLOG 15

int Socket();
void Bind(int sockfd, struct sockaddr_in *address);
void Listen(int sockfd);
int Accept(int sockfd, struct sockaddr_in *address);
void Connect(int sockfd, struct sockaddr_in *address);
void Close(int sockfd);

#endif
