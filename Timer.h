#pragma once

#include <chrono>
#include <string>
#include <iostream>

class Timer final {
public:
  explicit Timer(std::string name = ""): name(name) {
    startTime = std::chrono::high_resolution_clock::now();
  }

  ~Timer() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto count = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << name << " took " << count << " microseconds" << std::endl; 
  }

private:
  std::chrono::high_resolution_clock::time_point startTime;
  std::string name;
};
