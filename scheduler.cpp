#include "scheduler.h"


Task::Task(uint64_t repeatDelay, uint64_t lastRun, std::function<void(uint64_t)> function)
: delay(repeatDelay), prev(lastRun), func(function) {}

void Scheduler::schedule(int key, uint64_t repeatDelay, std::function<void(uint64_t)> task, bool runImmediately) {
    if (tasks.find(key) == tasks.end()) {
        Serial.printf("Key %d already exists\n", key);
        return;
    }

    Task t(repeatDelay, runImmediately ? millis() - repeatDelay : millis(), task);
    tasks.insert(std::make_pair(key, t));
}

void Scheduler::remove(int key) {
    tasks.erase(key);
}

void Scheduler::loop() {
    uint64_t time = millis();

    for (auto &it : tasks) {
        Task &t = it.second;

        // this works even with binary overflow
        if (time - t.prev >= t.delay) {
            t.func(time - t.prev);
            t.prev = time;
        }
    }

}
