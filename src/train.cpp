// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() {
    Cage{ false, nullptr, nullptr };
    countOp = 0;
    first = nullptr;
}
void Train::addCage(bool a) {
    if (!first) {
        first = new Cage;
        first->light = a;
        first->prev = first;
        first->next = first;
    } else {
        Cage* p = first;
        while (p->next != first)
            p = p->next;
        Cage* tmp = new Cage;
        tmp->light = a;
        tmp->prev = tmp->next = nullptr;
        tmp->prev = p;
        p->next = tmp;
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
    Cage* h = first;
    if (h->light == false) {
        h->light = true;
        h = h->next;
        count_steps++;
        while (true) {
            while (h->light != true) {
                count_steps++;
                h = h->next;
            }
            h = h->prev;
            count_steps_2++;
            while (h->light != true) {
                count_steps_2++;
                h = h->prev;
            }
            if (count_steps_2 == count_steps) {
                countOp = count_steps * 2;
                return count_steps;
            }
        }
    } else {
        int count = 0;
        int res = 0;
        bool end = true;
        Cage* cur = first;
        do {
            cur = cur->next;
            count++;
            res++;
            if (cur->light) {
                cur->light = false;
                for (int i = count; i > 0; i--) {
                    cur = cur->prev;
                    res++;
                }
                if (!cur->light) {
                    countOp = res;
                    return count;
                } else {
                    count = 0;
                }
            } else {
                continue;
            }
        } while (end);
    }
return 0;
}
