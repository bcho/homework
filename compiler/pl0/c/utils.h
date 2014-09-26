#ifndef UTILS_H
#define UTILS_H

#define NELEMS(x) (sizeof((x)) / sizeof((x)[0]))

void panic(char *);

char *str_copy(char *);

#endif /* UTILS_H */
