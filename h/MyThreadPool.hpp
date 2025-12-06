#pragma once

#include <cstddef>
#include <thread>
#include <vector>
#include <deque>
#include <math.h>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <utility>

class MyThreadPool
{
private:
    std::vector<std::thread> workers_;
    std::deque<std::function<void()>> tasks_;
    size_t thread_num_;
    size_t max_tasks_;
    std::atomic<bool> stop_;
    std::condition_variable cv;
    mutable std::mutex mtx_;

public:
    explicit MyThreadPool(size_t threads = std::thread::hardware_concurrency(), size_t max_tasks = 0);
    ~MyThreadPool();
    MyThreadPool(const MyThreadPool &) = delete;
    MyThreadPool &operator=(const MyThreadPool &) = delete;
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args)
        -> std::future<typename std::invoke_result_t<F, Args...>>;
    size_t worker_count() const noexcept
    {
        return thread_num_;
    }
    size_t task_count() const noexcept
    {
        std::unique_lock<std::mutex> lock(mtx_);
        return tasks_.size();
    }
    void shutdown() noexcept;
};

inline MyThreadPool::MyThreadPool(size_t thread_num, size_t max_task_num)
    : thread_num_(std::max(thread_num, (size_t)1)), max_tasks_(std::min(max_task_num, (size_t)1024)), stop_(false)
{
    for (size_t i = 0; i < thread_num_; i++)
    {
        workers_.emplace_back([this]
                              {
            for(;;){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->mtx_);
                    this->cv.wait(lock,[this]{return this->stop_.load() || !this->tasks_.empty();});
                    if (this->stop_.load() && this->tasks_.empty())
                        return;
                    // 取出一个任务
                    task = std::move(this->tasks_.front());
                    this->tasks_.pop_front();
                }
                try{
                    task();
                }catch(...){
                    
                }
            } });
    }
}

template <typename F, typename... Args>
inline auto MyThreadPool::submit(F &&f, Args &&...args)
    -> std::future<typename std::invoke_result_t<F, Args...>>
{
    using R = typename std::invoke_result_t<F, Args...>;
    auto task_ptr = std::make_shared<std::packaged_task<R()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<R> fut = task_ptr->get_future();

    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (stop_.load())
            throw std::runtime_error("submit on stopped ThreadPool");

        if (max_tasks_ > 0 && tasks_.size() >= max_tasks_)
        {
            lock.unlock();
            (*task_ptr)();
            return fut;
        }

        tasks_.emplace_back([task_ptr]()
                            { (*task_ptr)(); });
    }
    cv.notify_one();
    return fut;
}

inline MyThreadPool::~MyThreadPool()
{
    shutdown();
}

inline void MyThreadPool::shutdown() noexcept
{
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (stop_.load())
            return;
        stop_.store(true);
    }
    cv.notify_all();
    for (auto &t : workers_)
    {
        if (t.joinable())
            t.join();
    }
    workers_.clear();
}