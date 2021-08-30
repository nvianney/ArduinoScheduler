#include "scheduler.h"

Scheduler::Scheduler() : prevTime(millis()) {
}

void Scheduler::schedule(int key, uint64_t repeatDelay, std::function<void()> task, bool runImmediately) {
    if (tasks.find(key) == tasks.end()) {
        Serial.printf("Key %d already exists\n", key);
        return;
    }

    Task t{repeatDelay, runImmediately ? millis() - repeatDelay : millis(), task};
    tasks[key] = t;
}

void Scheduler::remove(int key) {
    tasks.erase(key);
}

void Scheduler::loop() {
    
}
