#ifndef _LIST_H_
#define _LIST_H_

#include "struct.h"

struct list {
    struct abonent *Head;
    struct abonent *Tail;
    int size;
};

int push_front(struct list*);
int pop_front(struct list*);
int clear(struct list*);
int GetAll(struct list*);
int Find(struct list*);
#endif
