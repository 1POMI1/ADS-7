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
  Car* current = pos;

  int steps = 0;
  do {
    current->light = false;
    current = current->next;
    steps++;
    countOp++;
  } while (steps == 1 || current != pos);

  pos->light = true;

  current = pos->next;
  int len = 1;
  countOp++;

  while (!current->light) {
    current = current->next;
    len++;
    countOp++;
  }

  return len;
}


int Train::getOpCount() {
  return countOp;
}
