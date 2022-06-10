// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {
}

void Train::addCage(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    if (first == nullptr) {
        first = cage;
        cage->next = cage;
        cage->prev = cage;
    } else {
        cage->next = first;
        cage->prev = first->prev;
        first->prev = cage;
        cage->prev->next = cage;
    }
}

int Train::getLength() {
    first->light = true;
    int len = 0;
    while (first->light == true) {
        Cage* item = first->next;
        countOp += 2;
        len = 1;
        while (item->light == false) {
            countOp += 2;
            len++;
            item = item->next;
        }
        item->light = false;
    }
    return len;
}

int Train::getOpCount() {
    return countOp;
}
