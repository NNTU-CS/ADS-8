// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage{ false, nullptr, nullptr };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool f) {
    if (!first) {
        first = new Cage;
        first->light = f;
        first->prev = first;
        first->next = first;
    } else {
        Cage* w = first;
        while (w->next != first)
            w = w->next;
        Cage* tmp = new Cage;
        tmp->light = f;
        tmp->prev = tmp->next = nullptr;
        tmp->prev = w;
        w->next = tmp;
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
    Cage* m = first;
    if (m->light == false) {
        m->light = true;
        m = m->next;
        count_steps++;
        while (true) {
            while (m->light != true) {
                count_steps++;
                m = m->next;
            }
            m = m->prev;
            count_steps_2++;
            while (m->light != true) {
                count_steps_2++;
                m = m->prev;
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
