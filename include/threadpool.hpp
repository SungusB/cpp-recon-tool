#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class threadpool 
{
    public:
        threadpool(size_t numThreads);
        ~threadpool();
    
        void enqueue(std::function<void()> task);

    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        

        std::mutex queueMutex;
        std::condition_variable condition;
        std::atomic<bool> stop;

        void workerLoop();
};

#endif