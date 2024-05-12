// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    Cage* CageNew = new Cage;
    CageNew->light = light;
    if (first == nullptr) {
        first = CageNew;
        first->next = first;
        first->prev = first;
    } else {
        CageNew->next = first;
        CageNew->prev = first->prev;
        first->prev->next = CageNew;
        first->prev = CageNew;
    }
}

int Train::getLength() {
    if (first == nullptr) return 0;
    int dlina = 0;
    first->light = true;
    Cage* CageNow = first;
    while (first->light) {
        dlina = 1;
        CageNow = first->next;
        while (!CageNow->light) {
            CageNow = CageNow->next;
            dlina = dlina + 1;
        }
        CageNow->light = false;
        countOp = countOp + dlina * 2;
    }
    return dlina;
}

int Train::getOpCount() {
    return countOp;
}
