// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
  Cage* node = new Cage;
  node->light = light;

  if (first == nullptr) {
    first = node;
    node->prev = node;
    node->next = node;
    return;
  }

  node->next = first;
  node->prev = first->prev;
  first->prev->next = node;
  first->prev = node;
}

int Train::getLength() {
    int temp = 0;
    Cage* current = first;
    current->light = true;

    while (true) {
        current = current->next;
        countOp++;
        temp++;

        if (current->light) {
            current->light = false;
            int length = temp;

            for (int i = 0; i < length; i++) {
                current = current->prev;
                countOp++;
                temp--;
            }

            if (!current->light)
                return length;
        }
    }
}

int Train::getOpCount() {
  return countOp;
}
