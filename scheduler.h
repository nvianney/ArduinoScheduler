#ifndef scheduler_h
#define scheduler_h

#include <Arduino.h>
#include <unordered_map>
#include <functional>

struct Task {
    uint64_t repeatDelay = 0;
    uint64_t lastRun = 0;
    std::function<void()> func;
};

class Scheduler {
    std::unordered_map<int, Task> tasks;
    uint64_t prevTime;

public:
    Scheduler();

    void schedule(int key, uint64_t repeatDelay, std::function<void()> task, bool runImmediately = true);
    void remove(int key);

    void loop();
};

#endif
