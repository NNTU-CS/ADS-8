// Copyright 2021 NNTU-CS
#include "train.h"
  Train::Train() {
    countOp = 0;
    first = nullptr;
  }
  void Train::addCage(bool light) {
    if (first == nullptr) {
      first = new Cage;
      first->light = light;
      first->next = first;
      first->prev = first;
      return;
    }
    Cage* newCage = new Cage;
    newCage->light = light;
    newCage->next = first->next;
    newCage->prev = first;
    first->next->prev = newCage;
    first->next = newCage;
  }
  int Train::getLength() {
    if (!first->light) {
      first->light = true;
    }
    while (true) {
      int len = 1;
      int perehod = 1;
      countOp++;
      Cage* current = first->next;
      while (!current->light) {
        current = current->next;
        perehod++;
        countOp++;
      }
      current->light = false;
      for (; perehod > 1; perehod--) {
        current = current->prev;
        len++;
        countOp++;
      }
      countOp++;
      if (!current->prev->light) {
        return len;
      }
    }
  }
  int Train::getOpCount() {
    return countOp;
  }
