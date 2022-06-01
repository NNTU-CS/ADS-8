// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    first = nullptr;
    countOp = 0;
}

void Train::addCage(bool light) {
    Train::Cage* item = new Train::Cage;
    item->light = light;
    item->next = first;
    item->prev = nullptr;
    if (this->first != nullptr) {
        Train::Cage* find = this->first;
        while (find->next != first) {
            find = find->next;
        }
        find->next = item;
        item->prev = find;
    } else {
        first = item;
        first->next = first;
        first->prev = first;
    }
    return;
}

int Train::getOpCount() {
    return this->countOp;
}

int Train::getLength() {
    int count = 0;
    int length = 0;
    if (!this->first->light) {
        this->first->light = true;
    }
    Train::Cage* find = this->first;
    while (find->light) {
        find = find->next;
        count = 1;
        this->countOp++;
        while (!find->light) {
            find = find->next;
            this->countOp++;
            count++;
        }
        length = count;
        find->light = false;
        while (count--) {
            find = find->prev;
            this->countOp++;
        }
    }
    return length;
}
