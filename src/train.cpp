// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    if (first == nullptr) {
        first = cage;
        first->next = first;
        first->prev = first;
    } else {
        Cage* current = first;
        while (current->next != first) {
            current = current->next;
        }
        current->next = cage;
        cage->prev = current;
        cage->next = first;
        first->prev = cage;
    }
}
int Train::getLength() {
    int curLen = 0;
    Cage* current = first;
    current->light = true;
    while (true) {
        current = current->next;
        countOp++;
        curLen++;
        if (current->light) {
            current->light = false;
            int finLen = curLen;
            for (int i = 0; i < finLen; ++i) {
                current = current->prev;
                countOp++;
                curLen--;
            }
            if (!current->light)
                return finLen;
        }
    }
}
int Train::getOpCount() {
    return countOp;
}
