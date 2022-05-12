// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): first(nullptr), countOp(0) {}
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
  int length = 0;
  int lengthTrain;
  countOp = 0;
  first->light = true;
  Cage* temp = first;
  while (true) {
    countOp++;
    length++;
    temp = temp->next;
    if (temp->light) {
      temp->light = false;
      lengthTrain = length;
      for (lengthTrain; lengthTrain > 0; lengthTrain--) {
        temp = temp->prev;
        countOp++;
      }
      if (!temp->light) {
        return length;
      }
      length = lengthTrain;
    }
  }
  return lengthTrain;
}
int Train::getOpCount() {
  return countOp;
}
