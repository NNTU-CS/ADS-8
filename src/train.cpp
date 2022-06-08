// Copyright 2021 NNTU-CS
#include "train.h"

Train::Cage* Train::create(bool light) {
    Cage* cage = new Cage;
    cage->light = light;
    cage->right = nullptr;
    cage->left = nullptr;
    return cage;
}

void Train::addCage(bool light) {
    if (last && first) {
        last->right = create(light);
        last->right->left = last;
        last = last->right;
        first->left = last;
        last->right = first;
    } else {
        first = create(light);
        last = first;
    }
}

int Train::getLength() {
    int count = 0;
    first->light = true;
    Cage* temp = first;
    while (true) {
        count++;
        for (int a = 0; a < count; ++a) {
            temp = temp->right;
            countOp++;
        }
        if (temp->light) {
            temp->light = false;
            for (int a = 0; a < count; ++a) {
                temp = temp->left;
                countOp++;
            }
        } else {
            while (!temp->light) {
                count++;
                temp = temp->right;
                countOp++;
            }
            temp->light = false;
            for (int a = 0; a < count; ++a) {
                temp = temp->left;
                countOp++;
            }
        }
        if (!temp->light) {
            break;
        }
    }
    return count;
}

int Train::getOpCount() {
    return countOp;
}
