// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
  if (first != nullptr) {
    Cage* oC = new Cage;
    oC->light = light;
    tail->next = oC;
    oC->prev = tail;
    oC->next = nullptr;
    tail = tail->next;
  } else {
    first = new Cage;
    first->light = light;
    first->next = nullptr;
    first->prev = nullptr;
    tail = first;
    }
}
int Train::getLength() {
  sTr = 1;
  first->prev = tail;
  tail->next = first;
  first->light = true;
  Cage* train = new Cage;
  train = first->next;
  while (true) {
    countOp++;
    if (train->light != true) {
      sTr++;
      train = train->next;
    } else {
      train->light = false;
      break;
      }
  }
  for (int i = 1; i <= sTr; i++) {
    countOp++;
    train = train->prev;
  }
  if (train->light == false) {
    return sTr;
  } else {
    return getLength();
  }
}
int Train::getOpCount() {
  return countOp;
}
