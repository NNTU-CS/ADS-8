// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Cage* node = new Cage;
    if (!first) {
        node->light = light;
        node->prev = node;
        node->next = node;
        first = node;
    } else {
        Cage* SecFirst = first;
        node->light = light;
        node->next = first;
        node->prev = first->prev;
        first->prev->next = node;
        first->prev = node;
    }
}

int Train::getLength() {
    first->light = true;
    Cage *SecFirst = first;
    int q = 1;
    int carriages = 1;
    while (first->light) {
        carriages = 1;
        SecFirst = first->next;
        while (!SecFirst->light) {
            SecFirst = SecFirst->next;
            carriages += 1;
        }
        SecFirst->light = false;
        countOp += carriages * 2;
    }
    return carriages;
}

int Train::getOpCount() {
    return countOp;
}
