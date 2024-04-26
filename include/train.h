// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
    struct Cage {
        bool light;
        Cage* next;
        Cage* prev;
    };
    int countOp;
    Cage* first;
 public:
    Train();
    void addCage(bool light);
    int getLength();
    int getOpCount();
    bool IsEmpty();
    Cage* create(bool l);
    ~Train();
};
#endif  // INCLUDE_TRAIN_H_
