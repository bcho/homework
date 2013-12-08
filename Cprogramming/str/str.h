/**
 * str
 *
 * Some useful string process utilities.
 */

#ifndef STR_H
#define STR_H

char *trim(const char *);
char *join(const char **, int, const char *);
char **split(const char *, const char *, int *);

#endif
