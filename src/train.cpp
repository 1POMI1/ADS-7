// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : start(nullptr), countOp(0) {}

Train::~Train() {
  if (!start) return;
  Car* current = start->next;
  while (current != start) {
    Car* temp = current;
    current = current->next;
    delete temp;
  }
  delete start;
}

void Train::addCar(bool light) {
  Car* newCar = new Car(light);
  if (!start) {
    start = newCar;
    start->next = start;
    start->prev = start;
  } else {
    Car* last = start->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = start;
    start->prev = newCar;
  }
}

int Train::getLength() {
  Car* pos = start;
  countOp = 0;

  if (!pos) return 0;

  while (!pos->light) {
    pos->light = true;
    pos = pos->next;
    countOp++;
  }

  pos = pos->next;
  countOp++;

  int len = 1;
  while (!pos->light) {
    pos = pos->next;
    countOp++;
    len++;
  }

  return len;
}

int Train::getOpCount() {
  return countOp;
}
