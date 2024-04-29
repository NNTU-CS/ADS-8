// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():first(nullptr), countOp(0) {}
void Train::addCage(bool light) {
  Cage* newCage = new Cage;
  newCage->light = light;
  if (first == nullptr) {
    first = newCage;
    newCage->prev = newCage;
    newCage->next = newCage;
    return;
  }
  newCage->next = first;
  newCage->prev = first->prev;
  first->prev->next = newCage;
  first->prev = newCage;
}
int Train::getLength() {
  if (first == nullptr)
    return 0;
  Cage* current = first;
  current->light = 1;
  int longg = 1;
  while (true) {
    current = current->next;
    while (current->light == 0) {
      current = current->next;
      longg += 1;
      countOp++;
    }
    countOp++;
    current->light = 0;
    for (int i = longg; i > 0; i--) {
      countOp++;
      current = current->prev;
    }
    if (current->light == 0)
      return longg;
    longg = 1;
  }
}
int Train::getOpCount() {
  return countOp;
}
