// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
    Cage *cage = new Cage{light, nullptr, nullptr};
    if (first == nullptr) {
        first = cage;
        first->next = first;
        first->prev = first;
    } else {
        Cage *last = first->prev;
        last->next = cage;
        cage->prev = last;
        cage->next = first;
        first->prev = cage;
    }
    countOp = 0;
}

int Train::getLength() {
    Cage *currentVan = first;
    if (!currentVan->light) {
        currentVan->light = true;
    }
    int res = 0;
    int vanCount = 0;
    while (true) {
        currentVan = currentVan->next;
        countOp++;
        vanCount++;
        while (!currentVan->light) {
            currentVan = currentVan->next;
            countOp++;
            vanCount++;
        }
        currentVan->light = false;
        res = vanCount;
        while (vanCount > 0) {
            countOp++;
            vanCount--;
            currentVan = currentVan->prev;
        }
        if (!currentVan->light) {
            return res;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
