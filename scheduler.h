#ifndef scheduler_h
#define scheduler_h

#include <Arduino.h>
#include <unordered_map>
#include <functional>

struct Task {
    uint64_t delay = 0;
    uint64_t prev = 0;
    std::function<void(uint64_t)> func;

    Task(uint64_t repeatDelay, uint64_t lastRun, std::function<void(uint64_t)> function);
};

class Scheduler {
    std::unordered_map<int, Task> tasks;

public:
    /**
     * Schedules a task to be run every [repeatDelay] milliseconds.
     * 
     * @param key the identifier of this task
     * @param repeatDelay the delay to run, in milliseconds
     * @param task the function to run
     * @param runImmediately true to run immediately, false to run after [repeatDelay] milliseconds
     */
    void schedule(int key, uint64_t repeatDelay, std::function<void(uint64_t)> task, bool runImmediately = true);
    void remove(int key);

    void loop();
};

#endif
