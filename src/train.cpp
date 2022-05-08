// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
  first = nullptr;
  countOp = 0;
}
int Train::getOpCount() {
  return countOp;
}

void Train::addCage(bool light) {
  Cage *cage = new Cage;
  cage->light = light;
  cage->prev = nullptr;
  cage->next = nullptr;
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
  int len = 0;
  countOp = 0;
  if (first) {
    first->light = true;
    Cage* temp = first;
    while (true) {
      temp = temp->next;
      countOp++;
      len++;
      if (temp->light == true) {
        temp->light = false;
        for (int tr = len; tr > 0; tr--) {
          temp = temp->prev;
          countOp++;
        }
        if (temp->light == false) {
          return len;
        }
        len = 0;
      }
    }
  }
  return 0;
}
