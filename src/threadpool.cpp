#include "threadpool.hpp"

threadpool::threadpool(size_t numThreads) : stop(false)
{
    for(size_t i = 0; i < numThreads; ++i)
    {
        workers.emplace_back(&threadpool::workerLoop, this);
    }
}


threadpool::~threadpool()
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();

    for(std::thread &worker : workers)
    {
        if(worker.joinable())
        {
            worker.join();
        }
    }
}

void threadpool::enqueue(std::function<void()> task)
{
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);
    }
    condition.notify_one();
}

void threadpool::workerLoop()
{
    while(true)
    {
        std::function<void()> task;
        {
            std::unique_lock <std::mutex> lock(queueMutex);
            while (!(stop || !tasks.empty())) 
            {
                condition.wait(lock);
            }
            
            if (stop && tasks.empty()) return;
        
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}