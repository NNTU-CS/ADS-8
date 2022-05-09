// Copyright 2021 NNTU-CS
#include "train.h"
void Train::addCage(bool light) {
  if (first != nullptr) {
    Cage* oCage = new Cage;
    oCage -> light = light;
    tail -> next = oCage;
    oCage -> prev = tail;
    oCage -> next = nullptr;
    tail = tail -> next;
  } else {
    first = new Cage;
    first -> light = light;
    first -> next = nullptr;
    first -> prev = nullptr;
    tail = first;
    }
}
int Train::getLength() {
  sTrain = 1;
  first -> prev = tail;
  tail -> next = first;
  first -> light = true;
  Cage* train = new Cage;
  train = first -> next;
  while (true) {
    countOp++;
    if (train -> light != true) {
      sTrain++;
      train = train -> next;
    } else {
      train -> light = false;
      break;
      }
  }
  for (int i = 1; i <= sTrain; i++) {
    countOp++;
    train = train -> prev;
  }
  if (train -> light == false) {
    return sTrain;
  } else {
    return getLength();
  }
}
int Train::getOpCount() {
  return countOp;
}
