// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (!firstAdded) {
        first->light = light;
        firstAdded = true;
    } else {
        Cage* n = new Cage;
        n->light = light;
        if (first->next == nullptr) {
            n->next = first;
            n->prev = first;
            first->next = n;
            first->prev = n;
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
    Cage* p = first;
    int len = 0;
    int realLen = 0;
    first->light = true;
    while (true) {
        countOp++;
        len++;
        p = p->next;
        if (p->light) {
            p->light = false;
            realLen = len;
            for (realLen; realLen > 0; realLen--) {
                countOp++;
                p = p->prev;
            }
            if (!p->light) {
                return len;
            }
            len = realLen;
        }
    }
    return realLen;
}
