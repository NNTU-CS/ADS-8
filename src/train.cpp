// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = last = nullptr;
  countOp = len = a = 0;
}
void Train::addCage(bool light) {
  if (!(first)) {
  Cage* NewC = new Cage;
  NewC->light = light;
  NewC->next = NewC->prev = nullptr;
  first = NewC;
  last = first;
  } else {
  Cage* NewC = new Cage;
  NewC->light = light;
  NewC->next = NewC->prev = nullptr;
  last->next = NewC;
  last->next->prev = last;
  last = last->next;
  if (!last->next) {
  last->next = first;
  } else {
  first->prev = last;
  }
  }
}
int Train::getLength() {
  first->light = true;
  last = first;
  int temp;
  while (true) {
  ++countOp, ++a;
  last = last->next;
  if (last->light) {
  temp = a;
  last->light = false;
  if ((last->prev) != nullptr) {
  while (last->light == false) {
  last = last->prev;
  --a, ++countOp;
  }
  }
  if (!last->light) {
  len = temp;
  break;
  }
  }
  }
  countOp += len;
  return len;
}
int Train::getOpCount() {
  return countOp;
}
