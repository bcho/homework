#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_SET -1

struct networks_t {
    int size;
    int *nodes;
};

struct networks_t *init_networks(int size);
void free_networks(struct networks_t *networks);
void connect(struct networks_t *networks, int a, int b);
int isreachable(struct networks_t *networks);

int main()
{
    int n, query, a, b;
    struct networks_t *networks;

    scanf("%d %d", &n, &query);

    networks = init_networks(n);

    while (query-- > 0) {
        scanf("%d %d", &a, &b);
        connect(networks, a - 1, b - 1);
        if (isreachable(networks))
            printf("it is possible.\n");
        else
            printf("it is impossible.\n");
    }
    free_networks(networks);

    return 0;
}

struct networks_t *init_networks(int size)
{
    struct networks_t *n;
    int i;

    n = malloc(sizeof *n);
    assert(n != NULL);
    n->size = size;
    n->nodes = malloc(sizeof(int) * n->size);
    assert(n->nodes != NULL);
    for (i = 0;i < n->size;i++)
        n->nodes[i] = INIT_SET;

    return n;
}

void free_networks(struct networks_t *networks)
{
    assert(networks->nodes != NULL && networks != NULL);
    free(networks->nodes);
    free(networks);
}

static int find_root(struct networks_t *n, int a)
{
    assert(a < n->size);
    if (n->nodes[a] == INIT_SET)
        return a;
    else
        return (n->nodes[a] = find_root(n, n->nodes[a]));
}

void connect(struct networks_t *networks, int a, int b)
{
    assert(a < networks->size && b < networks->size);
    networks->nodes[b] = find_root(networks, a);
}

/* must use path compression */
int isreachable(struct networks_t *networks)
{
    int root, i;

    for (root = find_root(networks, 0), i = 1;i < networks->size;i++)
        if (find_root(networks, i) != root)
            return 0;
    return 1;
}
