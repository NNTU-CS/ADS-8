// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCage(bool cond) {
  if (!first) {
    Cage* newCage = new Cage;
    newCage->light = cond;
    newCage->next = newCage;
    newCage->prev = newCage;
    first = newCage;
  } else {
    Cage* copyFirst = first;
    Cage* newCage = new Cage;
    newCage->light = cond;
    newCage->next = first;
    newCage->prev = first->prev;
    first->prev->next = newCage;
    first->prev = newCage;
  }
}

int Train::getLength() {
  first->light = true;
  Cage* copyfst = first;
  int cages = 1;
  while (first->light) {
    cages = 1;
    copyfst = first->next;
    while (!copyfst->light) {
      copyfst = copyfst->next;
      cages += 1;
    }
    copyfst->light = false;
    countOp += 2 * cages;
  }
  return cages;
}

int Train::getOpCount() { return countOp; }
