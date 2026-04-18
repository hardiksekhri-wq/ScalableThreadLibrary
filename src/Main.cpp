#include "ThreadPool.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {

    std::cout << "Creating Thread Pool..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    ThreadPool pool(8);

    for (int i = 1; i <= 1000; i++) {
        pool.addTask(Task(i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(20));

    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\nTotal Tasks Submitted: 1000" << std::endl;
    std::cout << "Worker Threads Used: 8" << std::endl;
    std::cout << "Execution Time: "
              << duration.count()
              << " ms" << std::endl;

    return 0;
}