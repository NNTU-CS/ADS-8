// Copyright 2021 NNTU-CS
#include "train.h"

bool Train::isEmpty() {
    if (first == nullptr) {
        return true;
    } else {
        return false;
    }
}

void Train::addCage(bool value) {
    Cage* n = new Cage;
    n->light = value;
    if (isEmpty()) {
        first = n;
        n->next = n;
        n->prev = n;
        return;
    }
    n->next = first->next;
    n->prev = first;
    first->next->prev = n;
    first->next = n;
}

bool Train::get() {
    if (!(isEmpty())) {
        bool num = first->light;
        return num;
    } else {
        return 0;
    }
}

void Train::goNext() {
    if (isEmpty()) return;
    first = first->next;
}

void Train::goPrev() {
    if (isEmpty()) return;
    first = first->prev;
}

void Train::counting() {
    if (check) {
        return;
    }
    check = true;
    countOp = 0;
    length = 1;
    if (get()) {
    } else {
        first->light = true;
    }
    while (true) {
        goNext();
        countOp++;
        if (get()) {
            first->light = false;
            for (int i = length; i > 0; i--) {
                goPrev();
                countOp++;
            }
            if (get()) {
                for (int i = 0; i < length; i++) {
                    goNext();
                    countOp++;
                }
                length++;
            } else {
                return;
            }
        } else {
            length++;
        }
    }
}

int Train::getLength() {
    counting();
    return length;
}

int Train::getOpCount() {
    counting();
    return countOp;
}
