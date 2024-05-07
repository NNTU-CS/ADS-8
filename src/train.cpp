// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstddef>

Train::Train() {
    countOp = 0;
    first = NULL;
}
void Train::addCage(bool light) {
    Cage* newCage = new Cage;
    newCage->light = light;
    if (first == NULL) {
        first = newCage;
        first->prev = newCage;
        first->next = newCage;
    } else {
        newCage->prev = first->prev;
        newCage->next = first;
        first->prev->next = newCage;
        first->prev = newCage;
    }
}
int Train::getLength() {
    Cage* current = first;
    int numbers = 1;
    int k = 0;
    if (first->light == false) {
        first->light = true;
    }
    while (true) {
        countOp++;
        current = current->next;
        k++;
        numbers++;
        int index;
        if (current->light == true) {
            current->light = false;
            index = numbers;
            while (index > 1) {
                current = current->prev;
                countOp++;
                index--;
            }
            if (current->light == false) {
                break;
            } else {
              index = 1;
              while (index < numbers) {
                current = current->next;
                countOp++;
                index++;
              }
              current->light = true;
            }
        } else {
          current->light = true;
        }
    }
  return k;
}
int Train::getOpCount() {
    return countOp;
}
