#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>

#define SHOWHOST

void showtime(long);
void show_info(struct utmp *);

int main()
{
    struct utmp utbuf;
    int utmpfd;

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }

    // just read from the binary file?
    // read sizeof(utbuf) bytes into the utbuf
    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
        show_info(&utbuf);

    close(utmpfd);

    return 0;
}

void showtime(long timeval)
{
    char *cp;
    // the content of the cp is from
    // static memory and hence it's not
    // thread-safe
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}

void show_info(struct utmp *utbuf)
{
    if (utbuf->ut_type != USER_PROCESS)
        return;

    printf("%-8.8s", utbuf->ut_name);
    printf(" ");
    printf("%-8.8s", utbuf->ut_line);
    printf(" ");
    showtime(utbuf->ut_time);

#ifdef SHOWHOST
    if (utbuf->ut_host[0] != '\0')
        printf(" (%s)", utbuf->ut_host);
#endif

    printf("\n");
}
