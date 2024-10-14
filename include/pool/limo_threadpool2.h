#ifndef THREAD_POOL_2_H_
#define THREAD_POOL_2_H_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <memory>
#include <thread>

class ThreadPool {
public:
    ThreadPool() = default;
    ~ThreadPool();

    explicit ThreadPool(int threadCount) { }

    template<typename T>
    void addTask(T&& task);

private:


    struct Pool {
        std::mutex mtx_;
        std::condition_variable cond_;
        std::queue<std::function<void()>> tasks_;
        bool isClosed;
    };


    std::shared_ptr<Pool> pool_;
};

ThreadPool::~ThreadPool() {
    if (pool_) {
        std::unique_lock<std::mutex> locker(pool_->mtx_);
        pool_->isClosed = true;
        pool_->cond_.notify_all();
    }
}


explicit ThreadPool::ThreadPool(int threadCount = 8): pool_(std::make_shared<Pool>()) {
    pool_->isClosed = false;
    
    for (int i = 0; i < threadCount; i++) {
        std::thread([this]() {
            std::unique_lock<std::mutex> locker(pool_->mtx_);
            while(true) {
                if (!pool_->tasks_.empty()) {
                    auto task = std::move(pool_->tasks_.front());
                    pool_->tasks_.pop();
                    locker.unlock();
                    task();
                    locker.lock();
                } else if (pool_->isClosed) {
                    break;
                } else {
                    pool_->cond_.wait(locker);
                }
            }
        }).detach();
    }
}


template<typename T>
void ThreadPool::addTask(T&& task) {
    std::unique_lock<std::mutex> locker(pool_->mtx_);
    pool_->tasks_.emplace(std::forward<T>(task));
    pool_->cond_.notify_one();
}


#endif