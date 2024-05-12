// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

Train::Train() {
    countOp = 0;
    Cage{ false, nullptr, nullptr };
    first = nullptr;
}

Train::~Train() {
    if (first) {
        Cage *current = first;
        do {
            Cage *next = current->next;
            delete current;
            current = next;
        } while (current != first);
    }
}

void Train::addCage(bool l) {
    if (!first) {
        first = new Cage;
        first->light = l;
        first->prev = first;
        first->next = first;
    } else {
        Cage* c = first;
        while (c->next != first)
            c = c->next;
        Cage* newCage = new Cage;
        newCage->light = l;
        newCage->prev = newCage->next = nullptr;
        newCage->prev = c;
        c->next = newCage;
        newCage->next = first;
        first->prev = newCage;
    }
}

int Train::getLength() {
    int count_steps = 0;
    int count_steps_2 = 0;
    int total_ops = 0;
    Cage* current = first;

    if (!current) {
        return 0;
    }
    if (!current->light) {
        current->light = true;
        count_steps++;
        current = current->next;

        while (!current->light) {
            count_steps++;
            current = current->next;
        }

        count_steps_2 = 0;
        Cage* reverse = current->prev;
        count_steps_2++;

        while (!reverse->light) {
            count_steps_2++;
            reverse = reverse->prev;
        }

        if (count_steps_2 == count_steps) {
            total_ops = count_steps * 2;
            countOp = total_ops;
            return count_steps;
        }
    } else {
        int count = 0;
        total_ops = 0;

        while (true) {
            current = current->next;
            count++;
            total_ops++;

            if (current->light) {
                current->light = false;
                for (int i = 0; i < count; i++) {
                    current = current->prev;
                    total_ops++;
                }
                if (!current->light) {
                    countOp = total_ops;
                    return count;
                } else {
                    count = 0;
                }
            }
        }
    }
    return 0;
}
int Train::getOpCount() {
    return countOp;
}
