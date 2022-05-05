// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage* Train::create(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->next = nullptr;
    cage->prev = nullptr;
    return cage;
}

void Train::addCage(bool light) {
    if (first && final) {
        final->next = create(light);
        final->next->prev = final;
        final = final->next;
        final->next = first;
        first->prev = final;
    } else {
        first = final = create(light);
    }
}

int Train::getLength() {
    Cage* temp = first;
    int stepN = 0;
    if (!(temp->light)) {
        temp->light = !(temp->light);
    }
    temp->light = true;
    while (temp) {
        temp = temp->next;
        stepN++;
        countOp++;
        if (temp->light == true) {
            temp->light = !true;
            break;
        }
    }
    for (int k = 0; k < stepN; k++) {
        temp = temp->prev;
        countOp++;
    }
    if (temp->light != true) {
        return stepN;
    }
    return getLength();
}

int Train::getOpCount() {
    return countOp;
}
