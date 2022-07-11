#ifndef list_h
#define list_h

struct __DOUBLY_LINKED_LIST_NODE {
    void *data;
    struct __DOUBLY_LINKED_LIST_NODE *prev, *next;
};

typedef struct __DOUBLY_LINKED_LIST {
    struct __DOUBLY_LINKED_LIST_NODE *start, *end;
} DoublyLinkedList;

#endif /* list_h */
