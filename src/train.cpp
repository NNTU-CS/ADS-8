// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (!firstAdded) {
        firstAdded = true;
        first->light = light;
    } else {
        Cage* n = new Cage;
        n->light = light;
        if (first->next == nullptr) {
            n->next = first;
            n->prev = first;
            first->prev = n;
            first->next = n;
        } else {
            Cage* p = first;
            while (p->next != first) p = p->next;
            p->next = n;
            n->next = first;
            n->prev = p;
            first->prev = n;
        }
    }
}

int Train::getLength() {
    int len = 0;
    int rLen = 0;
    Cage* p = first;
    first->light = true;
    while (true) {
        p = p->next;
        len++;
        countOp++;
        if (p->light) {
            p->light = false;
            rLen = len;
            for (rLen; rLen > 0; rLen--) {
                countOp++;
                p = p->prev;
            }
            if (!p->light) {
                return len;
            }
            len = rLen;
        }
    }
    return rLen;
}
