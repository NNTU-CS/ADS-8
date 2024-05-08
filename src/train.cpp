// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
    countOp = 0;
    first = nullptr;
}

void Train::addCage(bool light)
{
	Cage *newCage = new Cage;
	newCage->light = light;
	newCage->next = nullptr;
	if (first == nullptr) {
		first = newCage;
		newCage->prev = nullptr;
	} else {
		Cage* curr = first;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = newCage;
		newCage->prev = curr;
	}
}

int Train::getLength()
{
	int len = 0; 
	Cage *curr = first;
	curr->light = true;
	while (true) {
		curr = curr->next;
		len++;
		countOp++;
		if (curr->light == true) {
			curr->light = false;
			int maxLen = len;
			len = 0;
		    for (int i = 0; i < maxLen; i++) {
			    curr = curr->prev;
			    countOp++;
		    }
        }

		if (curr->light == false) {
			return maxLen;
		}
	}
	
	return 0;
}

int Train::getOpCount()
{
	return countOp;
}

Train::~Train()
{
	Cage* curr = new Cage;
	while (curr->next != nullptr) {
		Cage* temp = curr;
		curr = curr->next;
		delete[] temp;
	}
}
