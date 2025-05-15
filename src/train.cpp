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
  Car* const pos = start;

  int n = 1;
  Car* current = pos->next;
  while (current != pos) {
    n++;
    current = current->next;
  }

  bool allOn = true;
  current = pos;
  for (int i = 0; i < n; ++i) {
    countOp++;
    if (!current->light) {
      allOn = false;
      break;
    }
    current = current->next;
  }

  current = pos;

  if (allOn) {

    for (int i = 0; i < n; ++i) {
      countOp++;
      if (current->light) {
        current->light = false;
        countOp++;
      }
      current = current->next;
      countOp++;
    }

    pos->light = true;
    countOp++;

    current = pos->next;
    int len = 1;
    countOp++;
    countOp++;

    while (!current->light) {
      current = current->next;
      len++;
      countOp += 2;
    }

    return len;

  } else {

    pos->light = true;
    countOp++;

    current = pos->next;
    int len = 1;
    countOp++;
    countOp++;

    while (!current->light) {
      current = current->next;
      len++;
      countOp += 2;
    }

    pos->light = false;
    countOp++;

    return len;
  }
}

int Train::getOpCount() {
  return countOp;
}
