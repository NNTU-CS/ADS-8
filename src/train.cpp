// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>
#include <cmath>

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    if (first == nullptr) {
        first = new struct Cage;
        first->prev = first;
        first->next = first;
    } else {
        Cage* temp = first->prev;
        first->prev = new struct Cage;
        temp->next = first->prev;

        first->prev->next = first;
        first->prev->prev = temp;
        first->prev->light = light;
    }
}

int Train::getLength() {
    int length = 0;
    countOp = 1;
    first->light = true;
    Cage* temp = first->next;
    while (1) {
        while (temp->light != true) {
            temp = temp->next;
            countOp++;
        }
        temp->light = false;
        length = (length == 0) ? \
            countOp + 1 : sqrt(countOp) + 1;
        for (int i = length - 1; i > 0; i--) {
            temp = temp->prev;
            countOp++;
        }
        if (temp->light == false) { return length - 1; }
        temp = temp->next;
        countOp++;
    }
}
int Train::getOpCount() {
    return countOp;
}
