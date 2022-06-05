// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool l) {
    Cage* cage = new Cage;
    cage->l = l;
    cage->next = nullptr;
    cage->prev = nullptr;
    if (first == nullptr) {
        first = cage;
    } else if (first->prev == nullptr) {
        first->prev = cage;
        cage->next = first;
        first->next = cage;
        cage->prev = first;
    } else {
        first->next->prev = cage;
        cage->next = first->next;
        first->next = cage;
        cage->prev = first;
    }
}

int Train::getLength() {
    int trainlen = 0;
    int i = 0;
    first->l = true;
    Cage* temp = first;
    while (true) {
        countOp++;
        trainlen++;
        temp = temp->prev;
        if (temp->l) {
            temp->l = false;
            i = 0;
            while (i < trainlen) {
                temp = temp->next;
                countOp++;
                i++;
            }
            if (!temp->l) {
                return trainlen;
            }
            trainlen = 0;
        }
    }
    return i;
}

int Train::getOpCount() {
    return countOp;
}
