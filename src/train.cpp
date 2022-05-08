// Copyright 2021 NNTU-CS
#include "train.h"

void Train::addCage(bool light) {
if (first != nullptr) {
first = create(light);
current = first;
} else {
current->next = create(light);
current->next->prev = current;
current = current->next;
if (!current->next) {
current->next = first;
} else {
first->prev = current;
}
}
}

int Train::getLength() {
int i = 0;
int ct = 0;
first->light = true;
Cage *temp = first;
while (true) {
temp = temp->next;
ct++;
countOp++;
if (temp->light == true) {
temp->light = false;
i = 0;
while (i < ct) {
temp = temp->prev;
countOp++;
i++;
}
if (!temp->light) {
return ct;
}
ct = 0;
}
}
return i;
}

int Train::getOpCount() {
return countOp;
}
