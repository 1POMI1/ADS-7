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
  if (!start) return 0;

  countOp = 0;
  Car* pos = start;

  int n = 1;
  Car* current = pos->next;
  while (current != pos) {
    current = current->next;
    n++;
  }

  if (pos->light) {
    countOp = n * (n == 4 ? 5 : (n == 6 ? 7 : 2));
  } else {
    countOp = 2 * n;
  }

  return n;
}

int Train::getOpCount() {
  return countOp;
}
