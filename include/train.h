// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
    struct Cage {
        bool light;
        Cage* next;
        Cage* prev;
    };
    int countOp = 0;
    int count = 1;
    bool flag = false;
    Cage* first = nullptr;
    Cage* last = nullptr;
    void getCount();

 public:
    void addCage(bool light);
    int getLength();
    int getOpCount();

    void createCage(bool light) {
        first = new Cage;
        first->light = light;
        first->next = nullptr;
        first->prev = nullptr;
        last = first;
        return;
    }
};
#endif  // INCLUDE_TRAIN_H_
