#pragma once

#include <iostream>
#include <cstring>
#include <atomic>
template <typename T>
class shared_ptr
{
private:
    T *ptr_;
    std::atomic<std::size_t> *ref_count_;

    void release()
    {
        if (ref_count_ && ref_count_->fetch_sub(1, std::memory_order_acq_rel) == 1)
        {
            delete ptr_;
            delete ref_count_;
        }
    }

public:
    shared_ptr() : ptr_(nullptr), ref_count_(nullptr) {}

    ~shared_ptr()
    {
        release();
    }

    explicit shared_ptr(T *p) : ptr_(p), ref_count_(p ? new std::atomic<std::size_t>(1) : nullptr) {}

    shared_ptr(const shared_ptr<T> &others) : ptr_(others.ptr_), ref_count_(others.ref_count_)
    {
        if (ref_count_)
        {
            ref_count_->fetch_add(1, std::memory_order_acq_rel);
        }
    }

    shared_ptr &operator=(const shared_ptr<T> &others)
    {
        if (this != &others)
        {
            // 增加目标的引用计数，防止在释放自身后目标被删除（并发安全）
            if (others.ref_count_)
            {
                others.ref_count_->fetch_add(1, std::memory_order_acq_rel);
            }
            // 释放当前持有的资源
            release();
            // 接管引用
            ptr_ = others.ptr_;
            ref_count_ = others.ref_count_;
        }
        return *this;
    }

    shared_ptr(shared_ptr<T> &&others) noexcept : ptr_(others.ptr_), ref_count_(others.ref_count_)
    {
        others.ptr_ = nullptr;
        others.ref_count_ = nullptr;
    }

    shared_ptr &operator=(shared_ptr<T> &&others) noexcept
    {
        if (this != &others)
        {
            release();
            ptr_ = others.ptr_;
            ref_count_ = others.ref_count_;
            others.ptr_ = nullptr;
            others.ref_count_ = nullptr;
        }
        return *this;
    }

    T &operator*() const
    {
        return *ptr_;
    }

    T *operator->() const
    {
        return ptr_;
    }

    T *get() const
    {
        return ptr_;
    }

    // 返回当前引用计数（若为空返回 0）
    size_t count() const
    {
        return ref_count_ ? ref_count_->load(std::memory_order_acquire) : 0;
    }

    void reset(T *ptr = nullptr)
    {
        // 为了异常安全，先分配新的 ref_count，再释放旧的。
        std::atomic<std::size_t> *new_ref = ptr ? new std::atomic<std::size_t>(1) : nullptr;
        release();
        ptr_ = ptr;
        ref_count_ = new_ref;
    }
};
