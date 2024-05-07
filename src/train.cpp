// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (!first) {
        Cage* newCage = new Cage;
        newCage->light = light;
        newCage->next = newCage;
        newCage->prev = newCage;
        first = newCage;
    } else {
        Cage* newCage = new Cage;
        newCage->light = light;
        newCage->next = first;
        newCage->prev = first->prev;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}

int Train::getLength() {
    first->light = true;
    Cage* tmp = first;
    int cnt = 0;
    int step = 0;
    while (true) {
        cnt = 1;
        countOp += 1;
        step += 1;
        tmp = tmp->next;
        while (tmp->light == false) {
            step += 1;
            countOp += 1;
            cnt += 1;
            tmp = tmp->next;
        }
        tmp->light = 0;
        tmp = tmp->prev;
        countOp += 1;
        step--;
        while (step > 0) {
            countOp += 1;
            step -= 1;
            tmp = tmp->prev;
        }
        if (tmp->light == false) return cnt;
    }
}


