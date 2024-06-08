// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
    Cage* cage = new Cage{light, nullptr, nullptr};

    if (!first) {
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
    currentVan->light = true;

    for ( int res = 0, vanCount = 0 ; ; ) {
        currentVan = currentVan->next;
        countOp++;
        vanCount++;

        for ( ; !currentVan->light; currentVan = currentVan->next, vanCount++ )
            countOp++;

        currentVan->light = false;
        res = vanCount;

        for ( ; vanCount > 0; vanCount--, currentVan = currentVan->prev )
            countOp++;

        if (!currentVan->light)
            return res;
    }
}

int Train::getOpCount() {
    return countOp;
}
