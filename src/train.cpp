// Copyright 2021 NNTU-CS
#include "train.h"


Train::Train() :first(nullptr) {}

void Train::addCage(bool light) {
    if (!first) {
        first = new Cage(light, nullptr);
        first->next = nullptr;
    } else if (!first->next) {
        Cage* temp = new Cage(light, first);
        temp->next = first;
        first->next = temp;
        first->prev = temp;
    } else {
        Cage* temp = new Cage(light, first->prev);
        first->prev->next = temp;
        temp->next = first;
        first->prev = temp;
    }
}

int Train::getLength() {
    int Length = 0;
    int kol = 0;
    Cage* temp = first;
    temp->light = true;
    while (true) {
        while (1) {
            temp = temp->next;
            ++countOp;
            ++kol;
            if (temp->light) {
                temp->light = false;
                break;
            }
        }
        Length = kol;
        while (kol) {
            temp = temp->prev;
            ++countOp;
            --kol;
        }
        if (!temp->light)
            return Length;
    }
}

int Train::getOpCount() {
    return countOp;
}
