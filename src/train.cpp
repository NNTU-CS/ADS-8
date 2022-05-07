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
    if (last && first) {
        last->next = create(light);
        last->next->prev = last;
        last = last->next;
        first->prev = last;
        last->next = first;
    } else {
        first = create(light);
        last = first;
    }
}

int Train::getLength() {
    int len = 0;
    first->light = true;
    Cage* temp = first;
    while (true) {
        len += 1;
        for (int i = 0; i < len; ++i) {
            temp = temp->next;
            countop += 1;
        }
        if (temp->light) {
            temp->light = false;
            for (int i = 0; i < len; ++i) {
                temp = temp->prev;
                countop += 1;
            }
        } else {
            while (!temp->light) {
                len += 1;
                temp = temp->next;
                countop += 1;
            }
            temp->light = false;
            for (int i = 0; i < len; ++i) {
                temp = temp->prev;
                countop += 1;
            }
        }
        if (!temp->light) {
            break;
        }
    }
    return len;
}

int Train::getOpCount() {
    return countop;
}
