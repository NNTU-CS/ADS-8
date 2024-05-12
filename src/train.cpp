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
  int length = 0;
  first->light = true;
  Cage* current = first;
  while (first->light) {
    length = 1;
    current = first->next;
    while (!current->light) {
      current = current->next;
      length += 1;
    }
    current->light = false;
    countOp += length * 2;
  }
  return length;
}

int Train::getOpCount() { return countOp; }
