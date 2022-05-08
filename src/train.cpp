// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
  if (first != nullptr) {
    Cage* oC = new Cage;
    oC->light = light;
    last->next = oC;
    oC->prev = last;
    oC->next = nullptr;
    last = last->next;
  } else {
    first = new Cage;
    first->light = light;
    first->next = nullptr;
    first->prev = nullptr;
    last = first;
    }
}
int Train::getLength() {
  size = 1;
  first->prev = last;
  last->next = first;
  first->light = true;
  Cage* train = new Cage;
  train = first->next;
  while (true) {
    countOp++;
    if (train->light != true) {
      size++;
      train = train->next;
    } else {
      train->light = false;
      break;
      }
  }
  for (int i = 1; i <= size; i++) {
    countOp++;
    train = train->prev;
  }
  if (train->light == false) {
    return size;
  } else {
    return getLength();
  }
}
int Train::getOpCount() {
  return countOp;
}
