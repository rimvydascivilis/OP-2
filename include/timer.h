#pragma once

#include <chrono>

using namespace std::chrono;

class Timer {
private:
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
public:
    Timer() {
        start = high_resolution_clock::now();
    }

    void stop() {
        end = high_resolution_clock::now();
    }

    void reset() {
        start = high_resolution_clock::now();
    }

    double getDuration() {
        return duration_cast<milliseconds>(end - start).count() / 1000.0;
    }
};