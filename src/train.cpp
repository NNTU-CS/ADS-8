// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
  if (first == nullptr) {
    first = new Cage();
    first->light = light;
    first->next = nullptr;
    first->prev = first->next;
    last = first;
  } else {
    //prov-first совпадает с last
    Cage* prov = new Cage();
    prov->light = light;
    last->next = prov;
    prov->next = nullptr;
    prov->prev = last;
    last = last->next;
    }
}

int Train::getLength() {
  last->next = first;
  first->prev = last;
  first->light = true;
  size = 1;
  Cage* carriage = new Cage();
  carriage = first->next;
  while (true) {
    countOp++;
    if (carriage->light != true) {
      size++;
      carriage = carriage->next;
    } else {
      carriage->light = false;
      break;
      }
  }
  int temp = 1;
  while (temp <= size) {
    countOp++;
    carriage = carriage->prev;
    temp++;
  }
  if (carriage->light == true) {
    return getLength();
  } else {
    return size;
    }
}

int Train::getOpCount() {
  return countOp;
}
