// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  cntOp = 0;
}

Train::~Train() {
  Cage* current = first;
  while (current->next != first) {
    Cage* temp = current;
    current = current->next;
    delete temp;
  }
}

void Train::addCage(bool light) {
  Cage *newCage = new Cage;
  newCage->light = light;
  newCage->next = nullptr;
  if (first == nullptr) {
    newCage->prev = nullptr;
    first = newCage;
    first->next = first;
  } else {
    Cage* current = first;
    while (current->next != first) {
      current = current->next;
    }
    current->next = newCage;
    newCage->prev = current;
    newCage->next = first;
    first->prev = newCage;
  }
}

int Train::getLength() {
  int len = 0;
  Cage *current = first;
  current->light = true;
  while (true) {
    current = current->next;
    cntOp++;
    len++;
    if (current->light == true) {
      current->light = false;
      int mlen = len;
      len = 0;
      for (int i = 0; i < mlen; i++) {
        current = current->prev;
        cntOp++;
      }
      if (current->light == false)
        return mlen;
    }
  }
}

int Train::getOpCount() {
  return cntOp;
}
