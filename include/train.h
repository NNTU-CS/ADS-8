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
    Cage* first = nullptr;

 public:
    bool check = false;
    int countOp;
    int length;
    bool isEmpty();
    void addCage(bool light);
    bool get();
    void goNext();
    void goPrev();
    void counting();
    int getLength();
    int getOpCount();
};
#endif  // INCLUDE_TRAIN_H_
