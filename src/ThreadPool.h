#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "Task.h"

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<Task> taskQueue;

    std::mutex queueMutex;
    std::condition_variable condition;

    bool stop;

public:
    ThreadPool(int numThreads);

    void addTask(Task task);

    void shutdown();

    ~ThreadPool();
};