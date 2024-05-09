// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

struct Cage {
bool light;
Cage *prev;
Cage *next;
};

class Train {
  private:
Cage *first;
int countOp;
   public:

Train() : first(nullptr), countOp(0) {}

void addCage(bool light) {
  Cage *cage = new Cage{light, nullptr, nullptr};
  if (first == nullptr) {
    first = cage;
    first->next = first;
    first->prev = first;
  } else {
    Cage *last = first->prev;
    last->next = cage;
    cage->prev = last;
    cage->next = first;
    first->prev = cage;
  }
  countOp = 0;
}
int getLength() {
  Cage *currentCage = first;
  if (!currentCage->light) {
    currentCage->light = true;
  }
  int res = 0;
  int cageCount = 0;
  while (true) {
    currentCage = currentCage->next;
    countOp++;
    cageCount++;
    while (!currentCage->light) {
      currentCage = currentCage->next;
      countOp++;
      cageCount++;
    }
    currentCage->light = false;
    res = cageCount;
    while (cageCount > 0) {
      countOp++;
      cageCount--;
      currentCage = currentCage->next;
      if (currentCage == first) {
        break;
      }
    }
    if (currentCage == first) {
      break;
    }
  }
  return res;
}
int getOpCount() {
  return countOp;
}
};
