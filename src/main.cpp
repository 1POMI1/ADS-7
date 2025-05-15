// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "train.h"

void fillTrain(Train& t, int n, const std::string& mode) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);

  for (int i = 0; i < n; ++i) {
    if (mode == "off") t.addCar(false);
    else if (mode == "on") t.addCar(true);
    else t.addCar(dist(gen));
  }
}

int main() {
  std::vector<int> sizes = {10, 20, 40, 80, 160, 320, 640, 1000};

  std::cout << "mode,n,ops,time_us\n";

  for (const std::string& mode : {"off", "on", "random"}) {
    for (int n : sizes) {
      Train train;
      fillTrain(train, n, mode);

      auto start = std::chrono::high_resolution_clock::now();
      int length = train.getLength();
      auto end = std::chrono::high_resolution_clock::now();

      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(end - start)
              .count();

      std::cout << mode << "," << n << "," << train.getOpCount() << "," << duration << "\n";
    }
  }

  return 0;
}
