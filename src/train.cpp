// Copyright 2021 Matvey Ryabchikov
#include "train.h"

Train::Train() : first(nullptr), countOp(0) {}

void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  if (!first) {
    newCage->next = newCage;
    newCage->prev = newCage;
    first = newCage;
    return;
  }
  newCage->next = first->next;
  newCage->prev = first;
  first->next->prev = newCage;
  first->next = newCage;
}

int Train::getOpCount() { return countOp; }

int Train::getLength() {
  first->light = true;
  while (true) {
    int len = 0, count = 0;
    first = first->next;
    count++;
    countOp++;
    while (!first->light) {
      first = first->next;
      count++;
      countOp++;
    }
    first->light = false;
    len = count;
    while (count--) {
      countOp++;
      first = first->prev;
    }
    if (!first->light) return len;
  }
}
