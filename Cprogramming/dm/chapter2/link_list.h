#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef struct LNode LNode;
typedef struct LNode * LinkList;

struct LNode {
    char data;
    struct LNode *next;
};

LinkList create_link_list_from_string(char *str);
LinkList create_link_list_from_string_with_dummy(char *str);
void destory_link_list(LinkList list);
LNode *get_nth_from_link_list(LinkList list, int n);
char *link_list_to_string(LinkList list);

#endif
