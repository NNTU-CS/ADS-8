// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
  first = nullptr;
  countOp = 0;
}

Train::~Train() {
  Cage* curnt = first;
  while (curnt->next != first) {
    Cage* temp = curnt;
    curnt = curnt->next;
    delete temp;
  }
}

void Train::addCage(bool light) {
  Cage* cage = new Cage;
  cage->light = light;
  cage->next = nullptr;
  if (first == nullptr) {
    cage->prev = nullptr;
    first = cage;
    first->next = first;
  } else {
    Cage* curnt = first;
    while (curnt->next != first) {
      curnt = curnt->next;
    }
    curnt->next = cage;
    cage->prev = curnt;
    cage->next = first;
    first->prev = cage;
  }
}

int Train::getLength() {
  int len = 0;
  Cage* curnt = first;
  curnt->light = true;
  while (true) {
    curnt = curnt->next;
    countOp++;
    len++;
    if (curnt->light == true) {
      curnt->light = false;
      int maxlen = len;
      len = 0;
      for (int i = 0; i < maxlen; i++) {
        curnt = curnt->prev;
        countOp++;
      }
      if (curnt->light == false)
        return maxlen;
    }
  }
}
int Train::getOpCount() {
  return countOp;
}
