// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    first = nullptr;
    countOp = 0;
}
Train::~Train() {
    if (IsEmpty()) {
        return;
    } else {
        if (first->next->next != first) {
            Cage* temp = first->next->next;
            while (temp->next != first) {
                delete temp->prev;
                temp = temp->next;
            }
            delete first;
        } else {
            delete first->next;
            delete first;
        }
    }
}
Train::Cage* Train::create(bool l) {
    Cage* cage = new Cage;
    cage->next = nullptr;
    cage->prev = nullptr;
    cage->light = l;
    return cage;
}
bool Train::IsEmpty() {
    return first == nullptr;
}
void Train::addCage(bool light) {
    Cage* temp;
    if (IsEmpty()) {
        first = create(light);
    } else {
        temp = first;
        if (temp->next) {
            while (temp->next != first) {
                temp = temp->next;
            }
        }
        temp->next = create(light);
        temp->next->prev = temp;
        temp->next->next = first;
        first->prev = temp->next;
    }
}
int Train::getOpCount() {
    return countOp;
}
int Train::getLength() {
    int lcount = 0;
    int fake = 0;
    int countCage = 1;
    first->light = 1;
    while (true) {
        lcount++;
        first = first->next;
        countOp++;
        countCage++;
        if (first->light) {
            first->light = 0;
            fake = lcount;
            while (lcount--) {
                first = first->prev;
                countOp++;
            }
            if (!first->light) {
                return countCage - 1;
            } else {
                lcount = fake;
                while (fake--) {
                    first = first->next;
                    countOp++;
                }
            }
        }
    }
}
