// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage{
        false,
        nullptr,
        nullptr
    };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool Light) {
    if (first) {
        Cage* h = first;
        while (first != h->next) {
            h = h->next;
        }
        Cage* temp = new Cage;
        temp->light = Light;
        temp->prev = temp->next = nullptr;
        temp->prev = h;
        h->next = temp;
        temp->next = first;
        first->prev = temp;
    } else {
        first = new Cage;
        first->light = Light;
        first->prev = first;
        first->next = first;
    }
}
int Train::getLength() {
    int len = 0;
    Cage* current = first;
    current->light = true;
    while (true) {
        current = current->next;
        countOp++;
        len++;
        if (current->light == true) {
            current->light = false;
            int maximum = len;
            len = 0;
            for (int i = 0; i < maximum; i++) {
                current = current->prev;
                countOp++;
            }
            if (current->light == false)
                return maximum;
        }
    }
}
int Train::getOpCount() {
    return countOp;
}
