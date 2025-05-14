// Copyright 2021 NNTU-CS
#include "train.h"

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
