#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSON_COUNT 10000  /* Person capacity limit */
#define MAX_PERSON_NAME_LENGTH 50  /* Person name maximum length */
#define EMPTY_NAME_PREFIX 0
#define HAS_RELATIONSHIP "TRUE"
#define HAS_NO_RELATIONSHIP "FALSE"

char PERSON[MAX_PERSON_COUNT][MAX_PERSON_NAME_LENGTH];  /* Person names set */
int PERSON_ANCESTOR[MAX_PERSON_COUNT];  /* Person ancestor set */

/*
 * Read persons list from stdin.
 *
 * :param n: list size, should <= MAX_PERSON_COUNT.
 * :param array: persons list.
 * :param array: person ancestors list. 
 */
void read_persons(int, char (*)[MAX_PERSON_NAME_LENGTH], int *);

/*
 * Union two persons.
 *
 * :param n: union times.
 * :param array: persons list.
 * :param array: person ancestors list. 
 */
void union_persons(int, char (*)[MAX_PERSON_NAME_LENGTH], int *);

/*
 * Query from relationship
 *
 * :param n: query times.
 * :param array: persons list.
 * :param array: person ancestors list. 
 */
void query_relationship(int, char (*)[MAX_PERSON_NAME_LENGTH], int *);


int main()
{
    int name_count, relationship_count, query_count;
    int i;

    for (i = 0; i < MAX_PERSON_COUNT; i++)
        PERSON[i][0] = EMPTY_NAME_PREFIX;

    scanf("%d", &name_count);
    read_persons(name_count, PERSON, PERSON_ANCESTOR);

    scanf("%d", &relationship_count);
    union_persons(relationship_count, PERSON, PERSON_ANCESTOR);

    scanf("%d", &query_count);
    query_relationship(query_count, PERSON, PERSON_ANCESTOR);

    return 0;
}

void *Malloc(size_t size)
{
    void *buffer;

    if ((buffer = malloc(size)) == NULL)
        exit(-1);
    return buffer;
}

void read_persons(int n,
                  char (*persons)[MAX_PERSON_NAME_LENGTH],
                  int *ancestors)
{
    int i;

    for (i = 0; i < n; i++) {
        scanf("%s", persons[i]);
        ancestors[i] = i;
    }
}

/*
 * Find person index with name.
 *
 * ..info:
 *  
 *     The running time is O(n).
 *
 * :param name: person's name.
 * :param persons: person names set.
 * :rtype: int, returns `-1` if the name not in the test.
 */
int find_person(char *name, char (*persons)[MAX_PERSON_NAME_LENGTH])
{
    int i;

    for (i = 0; i < MAX_PERSON_NAME_LENGTH; i++) {
        if (persons[i][0] == EMPTY_NAME_PREFIX)
            break;
        if (strcmp(name, persons[i]) == 0)
            return i;
    }

    return -1;
}

/*
 * Find person's ancestor (\w path compression).
 *
 * :param a: person's index.
 * :param ancestors: ancestors list.
 */
int find_(int a, int *ancestors)
{
    /* Perform path compression for new query. */
    for (; a != ancestors[a] ; a = ancestors[a])
        ;
    return a;
}

/*
 * Union two person.
 *
 * TODO union by rank.
 *
 * :param a, b: persons' index.
 * :param ancestors: ancestors list.
 */
void union_(int a, int b, int *ancestors)
{
    int ap, bp;

    ap = find_(a, ancestors);
    bp = find_(b, ancestors);

    /* TODO union by rank */
    ancestors[ap] = bp;
}

void union_persons(int n,
                   char (*persons)[MAX_PERSON_NAME_LENGTH],
                   int *ancestors)
{
    int i, a_idx, b_idx;
    char a_name[MAX_PERSON_NAME_LENGTH], b_name[MAX_PERSON_NAME_LENGTH];

    for (i = 0; i < n; i++) {
        scanf("%s %s", a_name, b_name);
        /* TODO Error handling here. */
        a_idx = find_person(a_name, persons);
        b_idx = find_person(b_name, persons);

        union_(a_idx, b_idx, ancestors);
    }
}

void query_relationship(int n,
                        char (*persons)[MAX_PERSON_NAME_LENGTH],
                        int *ancestors)
{
    int i, a_idx, b_idx;
    char a_name[MAX_PERSON_NAME_LENGTH], b_name[MAX_PERSON_NAME_LENGTH];

    for (i = 0; i < n; i++) {
        scanf("%s %s", a_name, b_name);
        /* TODO Error handling here. */
        a_idx = find_person(a_name, persons);
        b_idx = find_person(b_name, persons);

        if (find_(a_idx, ancestors) == find_(b_idx, ancestors))
            printf("%s\n", HAS_RELATIONSHIP);
        else
            printf("%s\n", HAS_NO_RELATIONSHIP);
    }
}
