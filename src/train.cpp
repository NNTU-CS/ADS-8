// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train():countOp(0), first(nullptr) {}
void Train::addCage(bool light) {
    Cage* newCage = new Cage;
    newCage->light = light; //создадим вагон и зажгём лампу
    if (first == nullptr) {
        first = newCage;
        newCage->prev = newCage;
        newCage->next = newCage;
        return;
    }
    newCage->next = first;
    newCage->prev = first->prev;
    first->prev->next = newCage;
    first->prev = newCage; //создадим любой другой вагон
}
int Train::getLength() {
    if (first == nullptr)
        return 0; //сразу вдруг поезд пустой
    Cage* cur = first;
    cur->light = 1; //зажгём лампу, даже если она горит
    int k = 1;
    while (true) { //запустим цикл
        cur = cur->next;
        while (cur->light == 0) {
            cur = cur->next;
            k += 1;
            countOp++;
        } //доёдём до светлой лампы
        countOp++;
        cur->light = 0; //погасим её
        for (int i = k; i > 0; i--) {
            countOp++;
            cur = cur->prev;
        } // придём назад
        if (cur->light == 0)
            return k;//если она погасла, то мы нашли длину, иначе всё заново
        k = 1;
    }
}
int Train::getOpCount() {
    return countOp;
}
