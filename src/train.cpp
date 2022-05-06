// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}

void Train::addCage(bool light) {
  Cage *rwc = new Cage;
  rwc->light = light;
  rwc->next = nullptr;
  rwc->prev = nullptr;
  if (first == nullptr) {
    first = rwc;
  } else if (first->next == nullptr) {
    first->next = rwc;
    rwc->prev = first;
    first->prev = rwc;
    rwc->next = first;
  } else {
      first->prev->next = rwc;
      rwc->prev = first->prev;
      first->prev = rwc;
      rwc->next = first;
  }
}

int Train::getLength() {
Cage* cr = first;
  first->light = true;
  countOp = 0;
  length = 0;
  while (true) {
    int trlen;
    countOp++;
    length++;
    cr = cr->next;
    if (cr->light) {
      cr->light = false;
      trlen = length;
      for (trlen; trlen > 0; trlen--) {
        cr = cr->prev;
        countOp++;
      }
      if (!cr->light) {
        return length;
      }
      length = trlen;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
