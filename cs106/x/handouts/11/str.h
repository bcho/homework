#ifndef STR_H
#define STR_H

/**
 * str.h
 *
 * Declare some string operations from handouts 08.
 */

int str_length(char *string);

/**
 * Retrieves the character at a position.
 * It will fail in assertion if pos is bigger
 * than string's length. If the pos is negative,
 * it will count reversly.
 */
char str_at(char *string, int pos);

char *str_copy(char *src);

int str_cmp(char *a, char *b);

char *str_concat(char *a, char *b);

void str_append(char **string, char *part);

int str_find_char(char *haystack, char needle);

int str_find_str(char *haystack, char *needle);

char *str_substr(char *string, int start, int length);

/* inserts b at position start within a */
void str_insert(char **a, int start, char *b);

/** 
 * remove from a a total of length characters starting
 * at the position start, replacing them with a copy
 * of b
 */
void str_replace(char **a, int start, int length, char *b);

/*
char *integer_to_string(int integer);
char *real_to_string(double real);
int string_to_integer(char *string);
double string_to_real(char *string);
*/

void str_trim(char **string);

/* any copy from str should be freed after using */
void str_free(char *string);

#endif
