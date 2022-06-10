// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train(): countOp(0), one(nullptr) {}

void Train::addCage(bool gl) {
      Cage *cage = new Cage;
      cage->gl = gl;
      cage->next = nullptr;
      cage->prev = nullptr;
        if (one == nullptr) {
            one = cage;
        } else if (one->prev == nullptr) {
          one->prev = cage;
          cage->next = one;
          one->next = cage;
          cage->prev = one;
        } else {
          one->next->prev = cage;
          cage->next = one->next;
          one->next = cage;
          cage->prev = one;
      }
  }

int Train::getLength() {
      int lengthTR = 0;
      int j = 0;
      one->gl = true;
      Cage *temp = one;
        while (true) {
            countOp++;
            lengthTR++;
            temp = temp->prev;
            if (temp->gl) {
                temp->gl = false;
                j = 0;
                while (j < lengthTR) {
                    temp = temp->next;
                    countOp++;
                    j++;
              }
                if (!temp->gl) {
                    return lengthTR;
              }
              lengthTR = 0;
          }
      }
      return j;
  }

int Train::getOpCount() {
      return countOp;
  }
