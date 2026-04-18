#pragma once

#include <iostream>
#include <thread>
#include <chrono>

class Task {
public:
    int id;

    Task(int taskId) {
        id = taskId;
    }

    void execute() {
        std::cout << "Task " << id << " is running..." << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << "Task " << id << " completed." << std::endl;
    }
};