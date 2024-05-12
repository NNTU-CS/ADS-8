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
    Cage light;
    int length = 0;

    if (first != nullptr) {
        length = 1;
        Cage* current = first->next;

        while (current != first) {
            length++;
			countOp++;
            current = current->next;
        }
    }

    return length;
}

int Train::getOpCount() {
  return countOp;
}
