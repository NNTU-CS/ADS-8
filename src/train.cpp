// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* nextC = first->next;
        first->next = new Cage;
        first->next->prev = first;
        first = first->next;
        nextC->prev = first;
        first->next = nextC;
        first->light = light;
    } else {
        first = new Cage;
        first->light = light;
        first->prev = first;
        first->next = first;
    }
}

int Train::getLength() {
    int trr = 0;
    int dlina = 0;
    Cage* current = first;
    if (!current->light) {
        current->light = true;
    }
    for (;;) {
        if (!current->next->light) {
            current = current->next;
            countOp++;
            dlina++;
            continue;
        }
        current->next->light = false;
        countOp += 2;
        trr = dlina + 1;
        while ((dlina > 0)) {
            current = current->prev;
            countOp++;
            dlina--;
        }
        if (current->light == false) {
            break;
        }
    }
    return trr;
}

int Train::getOpCount() {
    return countOp;
}
