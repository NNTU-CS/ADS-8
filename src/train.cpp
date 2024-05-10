// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage{ false, nullptr, nullptr };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool l) {
    if (!first) {
        first = new Cage;
        first->light = l;
        first->prev = first;
        first->next = first;
    } else {
        Cage* s = first;
        while (s->next != first)
            s = s->next;
        Cage* tmp = new Cage;
        tmp->light = l;
        tmp->prev = tmp->next = nullptr;
        tmp->prev = s;
        s->next = tmp;
        tmp->next = first;
        first->prev = tmp;
    }
}
int Train::getOpCount() {
return countOp;
}
int Train::getLength() {
    int length = 0;
    int count_steps = 0;
    int count_steps_2 = 0;
    Cage* t = first;
    if (t->light == false) {
        t->light = true;
        t = t->next;
        count_steps++;
        while (true) {
            while (t->light != true) {
                count_steps++;
                t = t->next;
            }
            t = t->prev;
            count_steps_2++;
            while (t->light != true) {
                count_steps_2++;
                t = t->prev;
            }
            if (count_steps_2 == count_steps) {
                countOp = count_steps * 2;
                return count_steps;
            }
        }
    } else {
        int counter = 0;
        int result = 0;
        bool endl = true;
        Cage* cureer = first;
        do {
            cureer = cureer->next;
            counter++;
            result++;
            if (cureer->light) {
                cureer->light = false;
                for (int i = counter; i > 0; i--) {
                    cureer = cureer->prev;
                    result++;
                }
                if (!cureer->light) {
                    countOp = result;
                    return counter;
                } else {
                    counter = 0;
                }
            } else {
                continue;
            }
        } while (endl);
    }
return 0;
}
