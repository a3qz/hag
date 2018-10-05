#include "list.h"
#include <stdlib.h>

struct list *list_create() {
    struct list *l = (struct list*)malloc(sizeof(*l));
    l->head = 0;
    l->tail = 0;
    return l;
}

struct node *list_add_tail(struct list *list, void *data) {
    if (!list) {
        return 0;
    }
    struct node *n = (struct node*)malloc(sizeof(*n));
    n->data = data;
    n->list = list;
    n->next = 0;
    n->prev = list->tail;
    if (list->tail) {
        list->tail->next = n;
    }
    if (!list->head) {
        list->head = n;
    }
    list->tail = n;
    return n;
}

struct node *list_add_head(struct list *list, void *data) {
    if (!list) {
        return 0;
    }
    struct node *n = (struct node*)malloc(sizeof(*n));
    n->data = data;
    n->list = list;
    n->prev = 0;
    n->next = list->head;
    if (list->head) {
        list->head->prev = n;
    }
    if (!list->tail) {
        list->tail = n;
    }
    list->head = n;
    return n;
}

struct node *list_add_after(struct node *node, void *data) {
    if (!node) {
        return 0;
    }
    struct node *n = (struct node*)malloc(sizeof(*n));
    n->list = node->list;
    n->data = data;
    n->next = node->next;
    n->prev = node;
    if (n->next) {
        n->next->prev = n;
    }
    node->next = n;
    if (node->list->tail == node) {
        node->list->tail = n;
    }
    return n;
}

void list_remove(struct node *node) {
    if (!node || !node->list) {
        return;
    }
    if (node->list->head == node) {
        node->list->head = node->next;
    }
    if (node->list->tail == node) {
        node->list->tail = node->prev;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    free(node);
}

void list_clear(struct list *list) {
    while (list->head) {
        list_remove(list->head);
    }
}

void *list_traverse(struct node *node) {
    static struct node *prev = 0;
    if (node) {
        prev = node;
        return 0;
    }
    void *ret = 0;
    if (prev) {
        ret = prev->data;
        prev = prev->next;   
    }
    return ret;
}
