#ifndef LIMO_THREADPOOL_H_
#define LIMO_THREADPOOL_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <memory>
#include <thread>

class ThreadPool {
public:

    ThreadPool() = default;
    explicit ThreadPool(int threadCount = 8) : pool_(std::make_shared<Pool>()) { 
        pool_->isClosed_ = false;

        for (int i = 0; i < threadCount; i++) {
            std::thread([this]() {
                std::unique_lock<std::mutex> locker(pool_->mtx_);
                while (true) {
                    if (!pool_->tasks_.empty()) {
                        auto task = std::move(pool_->tasks_.front());
                        pool_->tasks_.pop();
                        locker.unlock();
                        task();
                        locker.lock();
                    } else if (pool_->isClosed_) {
                        break;
                    } else {
                        pool_->cond_.wait(locker);
                    }
                }
            }).detach();
        }
    }

    ~ThreadPool() {
        if (pool_) {
            std::unique_lock<std::mutex> locker(pool_->mtx_);
            pool_->isClosed_ = true;
            pool_->cond_.notify_all();
        }
    }

    template<typename T>
    void addTask(T&& task) {
        std::unique_lock<std::mutex> lock(pool_->mtx_);
        tasks_.emplace(std::forward<T>(task));
        pool_->cond_.notify_one();
    }


private:
    struct Pool {
        std::mutex mtx_;
        bool isClosed_;
        std::condition_variable cond_;
        std::queue<std::function<void()>> tasks_;
    };
    std::shared_ptr<Pool> pool_;
};


#endif