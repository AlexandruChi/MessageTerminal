#ifndef list_h
#define list_h

struct __DOUBLY_LINKED_LIST_NODE {
    void *data;
    struct __DOUBLY_LINKED_LIST__NODE *prev, *next;
};

typedef struct __DOUBLY_LINKED_LIST {
    struct {
        struct __DOUBLY_LINKED_LIST_NODE *start, *end;
    } node;
    void (*create)(struct __DOUBLY_LINKED_LIST);
} DoublyLinkedList;

#endif /* list_h */
