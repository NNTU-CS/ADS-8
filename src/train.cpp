// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
  Cage *cage = new Cage;
  cage->light = light;
  cage->next = nullptr;
  cage->prev = nullptr;
  if (first == nullptr) {
    first = cage;
  } else if (first->next == nullptr) {
    first->next = cage;
    cage->prev = first;
    first->prev = cage;
    cage->next = first;
  } else {
      first->prev->next = cage;
      cage->prev = first->prev;
      first->prev = cage;
      cage->next = first;
  }
}

int Train::getLength() {
  Cage* current = first;
  first->light = true;
  countOp = 0;
  int len = 0;
  while (true) {
    int tLen;
    countOp++;
    len++;
    current = current->next;
    if (current->light) {
      current->light = false;
      tLen = len;
      for (tLen; tLen > 0; tLen--) {
        current = current->prev;
        countOp++;
      }
      if (!current->light) {
        return len;
      }
      len = tLen;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
