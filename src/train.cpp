// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
  first = nullptr;
  countOp = 0;
}

Train::~Train() {
  // Очистка списка вагонов
  while (first != nullptr) {
    Cage *temp = first;
    first = first->next;
    delete temp;
  }
}

void Train::addCage(bool light) {
  Cage *newCage = new Cage;
  newCage->light = light;

  if (first == nullptr) {
    first = newCage;
    first->next = first;
    first->prev = first;
  } else {
    Cage *last = first->prev;
    last->next = newCage;
    newCage->prev = last;
    newCage->next = first;
    first->prev = newCage;
  }
}

int Train::getLength() {
  int length = 0;
  Cage *current = first;
  do {
    length++;
    current = current->next;
  } while (current != first);
  return length;
}

int Train::getOpCount() { return countOp; }
