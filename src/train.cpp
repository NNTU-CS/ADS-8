// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
    if (first == nullptr) {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        return;
    }
          Cage* start;
          start = new Cage;
          start->light = light;
          start->next = nullptr;
          start->prev = last;
          last->next = start;
          last = start;
}

    int Train::getLength() {
        getCount();
        return count;
    }

    void Train::getCount() {
        if (flag) return;
        flag = true;
        first->light = true;
        first->prev = last;
        last->next = first;
        Cage* temp = first;
        Cage* current = first->next;
        while (current != nullptr) {
            if (current->light == false) {
                countOp++;
                count++;
                current = current->next;
            } else {
                if (current->light == true) {
                    current->light = false;
                    countOp++;
                }
                int i = count;
                while (i != 0) {
                    current = current->prev;
                    countOp++;
                    i--;
                }
                if (current->light == false) {
                    break;
                }
                current = current->next;
                count = 1;
            }
        }
    }

    int Train::getOpCount() {
        getLength();
        return countOp;
    }
