#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::cout << "Hello from multithreaded app!" << std::endl;

    
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back([i]() {
            std::cout << "Thread " << i << " is running" << std::endl;
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}