// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : first(nullptr), current(nullptr), countOp(0) {}

Train::Cage* Train::create(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  newCage->next = nullptr;
  newCage->prev = nullptr;
  return newCage;
}

void Train::addCage(bool light) {
  if (first && last) {
    last->next = create(light);
    last->next->prev = last;
    last = last->next;
    last->next = first;
    first->prev = last;
  } else {
    first = last = create(light);
  }
}

int Train::getLength() {
  int length = 0;
  first->light = true;
  current = first;
  bool flag = true;
  while (flag) {
    int c = 1;
    current = current->next;
    countOp++;
    while (!current->light) {
      current = current->next;
      c++;
      countOp++;
    }
    current->light = false;
    length = c;
    while (c--) {
      current = current->prev;
      countOp++;
    }
    if (!current->light) flag = false;
  }
  return length;
}

int Train::getOpCount() {
  return countOp;
}
