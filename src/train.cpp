// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = new Cage;
  first->prev = nullptr;
  iLen = 0;
  iRes = 0;
  countOp = 0;
}

void Train::addCage(bool light) {
  if (first->prev == nullptr) {
    first->light = light;
    first->prev = first;
    first->next = first;
  } else {
    Cage *cTemp = first->next;
    first->next = new Cage;
    first->next->prev = first;
    first = first->next;
    cTemp->prev = first;
    first->next = cTemp;
    first->light = light;
  }
}

int Train::getLength() {
  if (!first->light)
    first->light = true;
  while (true) {
    while (!first->next->light) {
      first = first->next;
      countOp = countOp + 1;
      iLen = iLen + 1;
    }
    countOp = countOp + 2;
    first->next->light = false;
    iRes = iLen + 1;
    for (; iLen > 0; iLen--) {
      first = first->prev;
      countOp = countOp + 1;
    }
    if (first->light == false)
      break;
  }
  return iRes;
}

int Train::getOpCount() {
  return countOp;
}
