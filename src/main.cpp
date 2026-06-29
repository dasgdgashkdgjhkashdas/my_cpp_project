#include <iostream>
#include <chrono> 
#include <vector> 
#include <future> 
#include "thread_pool.h"

int main() {
    std::cout << "=== Многопоточное приложение с ThreadPool ===" << std::endl;
    std::cout << "Создаем пул из 4 потоков..." << std::endl;

    ThreadPool pool(4);

    std::cout << "Добавляем 10 задач в пул..." << std::endl;

    std::vector<std::future<int>> results;

    for (int i = 0; i < 10; ++i) {
        auto result = pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
            });
        results.push_back(std::move(result));
    }

    std::cout << "Все задачи добавлены. Ждем результаты..." << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << "Результат задачи " << i << ": " << results[i].get() << std::endl;
    }

    std::cout << "Все задачи выполнены!" << std::endl;
    std::cout << "Завершение работы..." << std::endl;

    return 0;
}