// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
  Cage *newcage = new Cage();
  newcage->light = light;

  if (first == nullptr) {
    first = newcage;
    newcage->next = newcage;
    newcage->prev = newcage;
  } else {
    newcage->next = first;
    newcage->prev = first->prev;
    first->prev->next = newcage;
    first->prev = newcage;
  }
}

int Train::getLength() {
  if (first == nullptr)
    return 0;
  first->light = true;
  int count = 1;
  Cage* temp;

  while (first->light) {
    count = 1;
    temp = first->next;
    while (!temp->light) {
      temp = temp->next;
      count++;
    }
    countOp += 2 * count;
    temp->light = false;
  }
  return count;
}

int Train::getOpCount() {
  return countOp;
}
