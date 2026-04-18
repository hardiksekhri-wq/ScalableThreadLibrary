#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int numThreads) {
    stop = false;

    for (int i = 0; i < numThreads; i++) {

        workers.emplace_back([this, i]() {

            while (true) {

                Task task(0);

                {
                    std::unique_lock<std::mutex> lock(queueMutex);

                    condition.wait(lock, [this]() {
                        return !taskQueue.empty() || stop;
                    });

                    if (stop && taskQueue.empty()) {
                        return;
                    }

                    task = taskQueue.front();
                    taskQueue.pop();
                }

                std::cout << "Thread " << i + 1
                          << " picked Task "
                          << task.id << std::endl;

                task.execute();
            }
        });
    }
}

void ThreadPool::addTask(Task task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(task);
    }

    condition.notify_one();
}

void ThreadPool::shutdown() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stop = true;
    }

    condition.notify_all();

    for (std::thread &worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}