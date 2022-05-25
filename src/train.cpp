// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* vag;
        vag = new Cage;
        vag->light = light;
        vag->next = nullptr;
        vag->prev = last;
        last->next = vag;
        last = vag;
    } else {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        return;
    }
}
int Train::getLength() {
        first->light = true;
        first->prev = last;
        last->next = first;
        Cage* temp = first;
        Cage* cell = first->next;
        while (cell != nullptr) {
            if (!cell->light) {
                count++;
                countOp++;
                cell = cell->next;
            } else {
                if (cell->light) {
                        cell->light = 0;
                    countOp++;
                }
                for (int i = count; i > 0; i--) {
                    cell = cell->prev;
                    countOp++;
                }
                if (!cell->light) {
                    break;
                }
                cell = cell->next;
                count = 1;
            }
        }
        return count;
    }

int Train::getOpCount() {
  return countOp;
}
