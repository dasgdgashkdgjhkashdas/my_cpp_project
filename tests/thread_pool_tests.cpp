#include <gtest/gtest.h>
#include "thread_pool.h"
#include <chrono>

TEST(ThreadPoolTest, BasicTaskExecution) {
    ThreadPool pool(2);

    auto future = pool.enqueue([]() {
        return 42;
        });

    EXPECT_EQ(future.get(), 42);
}

TEST(ThreadPoolTest, MultipleTasks) {
    ThreadPool pool(4);
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 100; ++i) {
        futures.push_back(pool.enqueue([i]() {
            return i * 2;
            }));
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(futures[i].get(), i * 2);
    }
}

TEST(ThreadPoolTest, ParallelExecution) {
    ThreadPool pool(4);
    std::atomic<int> counter{ 0 };
    const int num_tasks = 100;

    std::vector<std::future<void>> futures;
    for (int i = 0; i < num_tasks; ++i) {
        futures.push_back(pool.enqueue([&counter]() {
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }));
    }

    for (auto& f : futures) {
        f.get();
    }

    EXPECT_EQ(counter, num_tasks);
}