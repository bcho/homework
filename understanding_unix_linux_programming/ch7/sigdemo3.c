#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define INPUTLEN 100

void inthandler(int);
void quithandler(int);

int main(int argc, char *argv[])
{
    char input[INPUTLEN];
    int nchars;

    signal(SIGINT, inthandler);
    signal(SIGQUIT, quithandler);

    do {
        printf("\nType a message\n");
        nchars = read(0, input, (INPUTLEN - 1));
        if (nchars == -1) {
            perror("read returned an error");
        } else {
            input[nchars] = 0;
            printf("You typed: %s", input);
        }
    } while (strncmp(input, "quit", 4) != 0);

    return 0;
}

void inthandler(int s)
{
    printf("Recevied signal %d .. waiting\n", s);
    sleep(2);
    printf("Leaving inthandler\n");
}

void quithandler(int s)
{
    printf("Recevied signal %d .. waiting\n", s);
    sleep(3);
    printf("Leaving quithandler\n");
}
