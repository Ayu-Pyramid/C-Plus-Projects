#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

std::mutex mtx;

// Define a Task structure
struct Task {
    int priority;          // Lower number = higher priority
    std::string name;
    
    // Comparator for priority_queue
    bool operator<(const Task& other) const {
        return priority > other.priority; // min-heap (highest priority first)
    }
};

// Function to simulate task execution
void executeTask(Task task) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Executing Task: " << task.name 
              << " | Priority: " << task.priority << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate work
}

int main() {
    // Priority queue of tasks
    std::priority_queue<Task> taskQueue;

    // Add tasks
    taskQueue.push({2, "Process Data"});
    taskQueue.push({1, "Handle Customer Request"});
    taskQueue.push({3, "Backup Files"});
    taskQueue.push({1, "Critical Security Patch"});

    std::vector<std::thread> threads;

    // Execute tasks concurrently
    while (!taskQueue.empty()) {
        Task t = taskQueue.top();
        taskQueue.pop();

        // Launch a thread to execute each task
        threads.push_back(std::thread(executeTask, t));
    }

    // Join all threads
    for (auto &th : threads) {
        th.join();
    }

    std::cout << "All tasks completed!" << std::endl;
    return 0;
}
