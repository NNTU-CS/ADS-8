// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  countOp = 0;
  first = nullptr;
}

Train::~Train() {
  Cage* actual = first;
  while (actual->next != first) {
    Cage* t = actual;
    actual = actual->next;
    delete t;
  }
}

void Train::addCage(bool light) {
  Cage* newcage = new Cage;
  newcage->light = light;
  newcage->next = nullptr;
  if (first == nullptr) {
    newcage->prev = nullptr;
    first = newcage;
    first->next = first;
  } else {
    Cage* actual = first;
    while (actual->next != first) {
      actual = actual->next;
    }
    actual->next = newcage;
    newcage->prev = actual;
    newcage->next = first;
    first->prev = newcage;
  }
}

int Train::getLength() {
  Cage* actual = first;
  int len = 0;
  actual->light = true;
  while (true) {
    actual = actual->next;
    len++;
    countOp++;
    if (actual->light == true) {
      actual->light = false;
      int maximumlen = len;
      len = 0;
      for (int i = 0; i < maximumlen; i++) {
        actual = actual->prev;
        countOp++;
      }
      if (actual->light == false)
        return maximumlen;
    }
  }
}
int Train::getOpCount() {
  return countOp;
}
