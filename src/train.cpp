// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    Cage* newCage = new Cage;
    newCage->light = light;
    if (first == nullptr) {
        first = newCage;
        newCage->prev = newCage;
        newCage->next = newCage;
        return;
    }
    newCage->next = first;
    newCage->prev = first->prev;
    first->prev->next = newCage;
    first->prev = newCage;
}
int Train::getLength() {
    if (first == nullptr)
        return 0;
    Cage* cur = first;
    cur->light = 1;
    int k = 1;
    while (true) {
        cur = cur->next;
        while (cur->light == 0) {
            cur = cur->next;
            k += 1;
            countOp++;
        }
        countOp++;
        cur->light = 0;
        for (int i = k; i > 0; i--) {
            countOp++;
            cur = cur->prev;
        } // придём назад
        if (cur->light == 0)
            return k;
        k = 1;
    }
}
int Train::getOpCount() {
    return countOp;
}
