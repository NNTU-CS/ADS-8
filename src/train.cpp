// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
  if (!first) {
    first = create(true);
  } else if (first->prev == nullptr) {
    first->next = create(light);
    first->next->prev = first;
    first->next->next = first;
    first->prev = first->next;
  } else {
    first->prev->next = create(light);
    first->prev->next->prev = first->prev;
    first->prev->next->next = first;
    first->prev = first->prev->next;
  }
}

int Train::getLength() {
  current = first;
  while (first->light) {
    stepsForward = 0;
    do {
      stepsForward++;
      countOp++;
      current = current->next;
    } while (!current->light);
    current->light = false;
    countOp += stepsForward;
    current = first;
  }
  return stepsForward;
}

int Train::getOpCount() {
  return countOp;
}
