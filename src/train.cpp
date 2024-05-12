// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  if (first == nullptr) {
    first = newCage;
    first->next = first;
    first->prev = first;
  } else {
    newCage->next = first;
    newCage->prev = first->prev;
    first->prev->next = newCage;
    first->prev = newCage;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;
  int len = 0;
  first->light = true;
  Cage* thisCage = first;
  while (first->light) {
    len = 1;
    thisCage = first->next;
    while (!thisCage->light) {
      thisCage = thisCage->next;
      len += 1;
    }
    thisCage->light = false;
    countOp += len * 2;
  }
  return len;
}

int Train::getOpCount() {
  return countOp;
}
