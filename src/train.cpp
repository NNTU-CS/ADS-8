// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
  if (first == nullptr) {
    first = new Cage{light, nullptr, nullptr};
    first->next = first;
    first->prev = first;
  } else {
    Cage *newCage = new Cage{light, first, first->prev};
    first->prev->next = newCage;
    first->prev = newCage;
  }
}

int Train::getLength() {
  first->light = true;
  int length = 1;
  Cage *current = first;
  while (first->light) {
    length = 1;
    current = first->next;
    while (!current->light) {
      current = current->next;
      length++;
    }
    current->light = false;
    countOp += 2 * length;
  }
  return length;
}

int Train::getOpCount() {
  return countOp;
}
