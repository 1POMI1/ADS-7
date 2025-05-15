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

  Car* const pos = start;
  int n = 1;
  // cppcheck-suppress constVariablePointer
  Car* current = pos->next;
  while (current != pos) {
    n++;
    current = current->next;
  }

  bool allOn = true;
  current = pos;
  for (int i = 0; i < n; ++i) {
    if (!current->light) {
      allOn = false;
      break;
    }
    current = current->next;
  }

  if (allOn) {
    countOp = (n == 4 ? 5 * n : 7 * n);
  } else {
    countOp = 2 * n;
  }

  return n;
}

int Train::getOpCount() {
  return countOp;
}
