// Copyright 2021 NNTU-CS
#include "train.h"
  Train::Train() {
    countOp = 0;
    first = nullptr;
  }
  void Train::addCage(bool light) {
    if (first == nullptr) {
      first = new Cage;
      first->light = light;
      first->next = first;
      first->prev = first;
      return;
    }
    Cage* newCage = new Cage;
    newCage->light = light;
    newCage->next = first->next;
    newCage->prev = first;
    first->next->prev = newCage;
    first->next = newCage;
  }

int Train::getLength() {
  first->light = true;
  Cage* first_copy = first;
  int cages = 0;
  while (first->light) {
    cages = 1;
    first_copy = first->next;
    while (!first_copy->light) {
      first_copy = first_copy->next;
      cages += 1;
    }
    first_copy->light = false;
    countOp += 2 * cages;
  }
  return cages;
}

int Train::getOpCount() {
  return countOp;
}
