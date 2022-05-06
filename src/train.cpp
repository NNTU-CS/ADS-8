// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
    if (first != nullptr) {
        Cage* step;
        step = new Cage;
        step->light = light;
        step->next = nullptr;
        step->prev = last;
        last->next = step;
        last = step;
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
        Cage* van = first->next;
        while (van != nullptr) {
            if (!van->light) {
                count++;
                countOp++;
                van = van->next;
            } else {
                if (van->light) {
                        van->light = 0;
                    countOp++;
                }
                for (int i = count; i > 0; i--) {
                    van = van->prev;
                    countOp++;
                }
                if (!van->light) {
                    break;
                }
                van = van->next;
                count = 1;
            }
        }
        return count;
    }

int Train::getOpCount() {
  return countOp;
}
