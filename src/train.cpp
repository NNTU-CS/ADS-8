// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
  first = nullptr;
  countOp = 0;
}
void Train::addCage(bool v) {
    if (!first) {
      first = new Cage{v, nullptr, nullptr};
      first->prev = first;
      first->next = first;
    } else {
      Cage* last = first->prev;
      Cage* newCage = new Cage{v, last, first};
      last->next = newCage;
      first->prev = newCage;
    }
}
int Train::getOpCount() {
  return countOp;
}
int Train::getLength() {
  if (!first) {
    return 0;
    }
  int count = 1;
  Cage* current = first->next;
  while (current != first) {
    count++;
    current = current->next;
  }
  return count;
}
