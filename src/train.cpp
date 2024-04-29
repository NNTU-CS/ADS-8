// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    Train::Cage *wagon = create(light);
    if (first == nullptr) {
        first = wagon;
    } else {
        if (first->next == nullptr) {
            first->prev = wagon;
            first->next = wagon;
            wagon->next = first;
            wagon->prev = first;

        } else {
            Train::Cage *temp = first;
            while (temp->next != first) {
                temp = temp->next;
            }
            temp->next = wagon;
            wagon->prev = temp;
            wagon->next = first;
            first->prev = wagon;
        }
    }
    countOp = 0;
}

Train::Train() : first(nullptr), countOp(0) {}

int Train::getLength() {
    Train::Cage *CurrentWagon = first;
    if (CurrentWagon->light == false) {
        CurrentWagon->light = true;
    }
    int rez = 0;
    int countWagon = 0;
    while (true) {
        CurrentWagon = CurrentWagon->next;
        countOp += 1;
        countWagon += 1;
        while (CurrentWagon->light == false) {
            CurrentWagon = CurrentWagon->next;
            countOp += 1;
            countWagon += 1;
        }
        CurrentWagon->light = false;
        rez = countWagon;
        while (countWagon != 0) {
            countOp += 1;
            countWagon -= 1;
            CurrentWagon = CurrentWagon->prev;
        }
        if (CurrentWagon->light == false) {
            return rez;
        }
    }
}

int Train::getOpCount() {
    return countOp;
}
