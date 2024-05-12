// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

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
    int lenght = 0;
    first->light = true;
    Cage* CageNow = first;
    while (first->light) {
        lenght = 1;
        CageNow = first->next;
        while (!CageNow->light) {
            CageNow = CageNow->next;
            lenght = lenght + 1;
        }
        CageNow->light = false;
        countOp = countOp + lenght * 2;
    }
    return lenght;
}

int Train::getOpCount() {
    return countOp;
}
