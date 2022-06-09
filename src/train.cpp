// Copyright 2021 NNTU-CS
#include "train.h"
int Train::getLength() {
  sz = 1;
  first->prev = lst;
  lst->next = first;
  first->light = true;
  Cage* pozd = new Cage;
  pozd = first->next;
  while (true) {
    countOp++;
    if (pozd->light != true) {
      sz++;
      pozd = pozd->next;
      } else {
        pozd->light = false;
        break;
      }
    }
  for (int i = 1; i <= sz; i++) {
    countOp++;
    pozd = pozd->prev;
  }
  if (pozd->light == false) {
    return sz;
  } else {
    return getLength();
  }
}
void Train::addCage(bool light) {
  if (first != nullptr) {
    Cage* p1 = new Cage;
    p1->light = light;
    lst->next = p1;
    p1->prev = lst;
    p1->next = nullptr;
    lst = lst->next;
    } else {
  first = new Cage;
  first->light = light;
  first->next = nullptr;
  first->prev = nullptr;
  lst = first;
  }
}
int Train::getOpCount() {
  return countOp;
}
