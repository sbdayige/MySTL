#pragma once
#include <utility>

template <typename T>
class unique_ptr
{
private:
    T *ptr_;

public:
    explicit unique_ptr(T *ptr = nullptr) : ptr_(ptr) {}

    ~unique_ptr()
    {
        delete ptr_;
    }

    unique_ptr(const unique_ptr &) = delete;

    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}

    unique_ptr &operator=(unique_ptr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr_;
            ptr_ = std::exchange(other.ptr_, nullptr);
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

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    T *get() const noexcept
    {
        return ptr_;
    }
};