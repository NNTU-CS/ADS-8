// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    if (first == nullptr) {
           cage->next = cage;
           cage->prev = cage;
           first = cage;
       } else {
           cage->next = first;
           cage->prev = first->prev;
           first->prev->next = cage;
           first->prev = cage;
       }
}
int Train::getLength() {
    first->light = true;
    int count = 1;
    Cage* current = first;
    while (first -> light) {
        count = 1;
        current = first->next;
        while (!current->light) {
            current = current->next;
            count++;
        }
        current->light = false;
        countOp += 2 * count;
        }
    return count;
}
int Train::getOpCount() {
    return countOp;
}
