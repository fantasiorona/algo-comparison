#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Timer final {
  public:
    explicit Timer(std::string name = "") : name(name) {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void Stop() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto count =
            std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        std::cout << name << " took " << format_microseconds(count) << std::endl;
    }

  private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::string name;
    std::string format_microseconds(long long count) {
        std::string string = std::to_string(count / (1000.0f * 1000.0f)) + " seconds";
        /*int minutes = count / (1000 * 1000 * 60);
        count -= minutes * 1000 * 1000 * 60;
        int seconds = count / (1000 * 1000);
        count -= seconds * 1000 * 1000;
        int milliseconds = count / 1000;
        count -= milliseconds * 1000;
        int microseconds = count;

        std::stringstream ssMinutes;
        ssMinutes << std::setw(1) << std::setfill('0') << minutes;
        std::string stringMinutes = ssMinutes.str();

        std::stringstream ssSeconds;
        ssSeconds << std::setw(2) << std::setfill('0') << seconds;
        std::string stringSeconds = ssSeconds.str();

        std::stringstream ssMilliseconds;
        ssMilliseconds << std::setw(3) << std::setfill('0') << milliseconds;
        std::string stringMilliseconds = ssMilliseconds.str();

        std::stringstream ssMicroseconds;
        ssMicroseconds << std::setw(3) << std::setfill('0') << microseconds;
        std::string stringMicroseconds = ssMicroseconds.str();

        std::string string = stringMinutes + "m " + stringSeconds + "s " + stringMilliseconds +
                             "ms " + stringMicroseconds + "us";*/
        return string;
    }
};
