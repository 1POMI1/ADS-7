// Copyright 2022 NNTU-CS
#include "train.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void fillTrain(Train& t, int n, const string& mode) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, 1);

  for (int i = 0; i < n; ++i) {
    if (mode == "off") t.addCar(false);
    else if (mode == "on") t.addCar(true);
    else t.addCar(dist(gen));
  }
}

int main() {
  vector<int> sizes = {10, 20, 40, 80, 160, 320, 640, 1000};

  for (const string& mode : {"off", "on", "random"}) {
    cout << "Mode: " << mode << endl;
    for (int n : sizes) {
      Train train;
      fillTrain(train, n, mode);

      auto start = high_resolution_clock::now();
      int length = train.getLength();
      auto end = high_resolution_clock::now();

      auto duration = duration_cast<microseconds>(end - start).count();

      cout << "n = " << n
           << ", length = " << length
           << ", ops = " << train.getOpCount()
           << ", time (us) = " << duration << endl;
    }
    cout << endl;
  }

  return 0;
}
