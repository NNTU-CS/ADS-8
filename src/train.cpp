// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
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
  Cage* cage = new Cage;
  cage->light = light;
  cage->next = nullptr;
  if (first == nullptr) {
    cage->prev = nullptr;
    first = cage;
    first->next = first;
  } else {
    Cage* current = first;
    while (current->next != first) {
      current = current->next;
    }
    current->next = cage;
    cage->prev = current;
    cage->next = first;
    first->prev = cage;
  }
}

int Train::getLength() {
  int length = 0;
  Cage* current = first;
  current->light = true;
  while (true) {
    current = current->next;
    countOp++;
    length++;
    if (current->light == true) {
      current->light = false;
      int maxlength = length;
      length = 0;
      for (int i = 0; i < maxlength; i++) {
        current = current->prev;
        countOp++;
      }
      if (current->light == false)
        return maxlength;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
