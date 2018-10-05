#ifndef LIST_H
#define LIST_H
    #include <stdlib.h>

    typedef struct node {
        struct list *list;
        struct node *next;
        struct node *prev;
        void *data;
    } node_t;

    typedef struct list {
        struct node *head;
        struct node *tail;
    } list_t;

    struct list *list_create();
    struct node *list_add_tail(struct list *list, void *data);
    struct node *list_add_head(struct list *list, void *data);
    struct node *list_add_after(struct node *node, void *data);
    void list_remove(struct node *node);
    void list_clear(struct list *list);
    void *list_traverse(struct node *node);

#endif
