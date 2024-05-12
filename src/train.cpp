// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  countOp = 0;
  first = nullptr;
}

void Train::addCage(bool light) {
  Cage *newCage = new Cage();
  newCage->light = light;

  if (first == nullptr) {
    newCage->next = newCage;
    newCage->prev = newCage;
    first = newCage;
  } else {
    newCage->next = first;
    newCage->prev = first->prev;

    first->prev->next = newCage;
    first->prev = newCage;
  }
}
int Train::getLength() {
  first->light = true;

  int counter = 1;
  Cage *cur;

  while (first->light) {
    counter = 1;
    cur = first->next;

    while (!cur->light) {
      cur = cur->next;
      counter++;
    }

    countOp += 2 * counter;
    cur->light = false;
  }
  return counter;
}
int Train::getOpCount() {
  return countOp;
}
