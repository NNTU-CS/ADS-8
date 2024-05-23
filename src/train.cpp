// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
}

void Train::addCage(bool cond) {
  if (!first) {
    Cage* nCage = new Cage;
    nCage->light = cond;
    nCage->next = nCage;
    nCage->prev = nCage;
    first = nCage;
  } else {
    Cage* copyFirst = first;
    Cage* nCage = new Cage;
    nCage->light = cond;
    nCage->next = first;
    nCage->prev = first->prev;
    first->prev->next = nCage;
    first->prev = nCage;
  }
}

int Train::getLength() {
  first->light = true;
  Cage* copyfirst = first;
  int cagess = 1;
  while (first->light) {
    cagess = 1;
    copyfirst = first->next;
    while (!copyfirst->light) {
      copyfirst = copyfirst->next;
      cagess += 1;
    }
    copyfirst->light = false;
    countOp += 2 * cagess;
  }
  return cagess;
}

int Train::getOpCount() {
  return countOp;
}
