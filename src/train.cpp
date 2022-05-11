// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool StateOfLight) {
    if (first != nullptr && tail != nullptr) {
        tail->next = create(StateOfLight);
        tail->next->prev = tail;
        tail = tail->next;
        tail->next = first;
        first->prev = tail;
    } else {
        first = tail = create(StateOfLight);
    }
}
int Train::getLength() {
    int n = 1;
    first->prev = tail;
    tail->next = first;
    first->StateOfLight = true;
    Cage* train = new Cage;
    train = first->next;
    while (true) {
        countOp++;
        if (train->StateOfLight != true) {
            n++;
            train = train->next;
        } else {
            train->StateOfLight = false;
            break;
        }
    }
    for (int i = 1; i <= n; i++) {
        countOp++;
        train = train->prev;
    }
    if (train->StateOfLight == false) {
        return n;
    } else {
        return getLength();
    }
}

int Train::getOpCount() {
    return countOp;
}
