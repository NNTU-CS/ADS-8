// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train(): countOp(0), first(nullptr) {}

void Train::addCage(bool glim) {
      Cage *cage = new Cage;
      cage->glim = glim;
      cage->next = nullptr;
      cage->prev = nullptr;
        if (first == nullptr) {
            first = cage;
        } else if (first->prev == nullptr) {
          first->prev = cage;
          cage->next = first;
          first->next = cage;
          cage->prev = first;
        } else {
          first->next->prev = cage;
          cage->next = first->next;
          first->next = cage;
          cage->prev = first;
      }
  }

int Train::getLength() {
      int lengthTR = 0;
      int i = 0;
      first->glim = true;
      Cage *temp = first;
        while (true) {
            countOp++;
            lengthTR++;
            temp = temp->prev;
            if (temp->glim) {
                temp->glim = false;
                i = 0;
                while (i < lengthTR) {
                    temp = temp->next;
                    countOp++;
                    i++;
              }
                if (!temp->glim) {
                    return lengthTR;
              }
              lengthTR = 0;
          }
      }
      return i;
  }

int Train::getOpCount() {
      return countOp;
  }
