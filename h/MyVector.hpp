#pragma once

#include <iostream>
#include <algorithm> // for std::copy
#include <cassert>
#include <mutex>

template <typename T>
class MyVector
{
public:
    typedef const T *const_iterator;

    MyVector() : _start(nullptr), _finish(nullptr), _out_range(nullptr) {}

    MyVector(size_t n, const T &value = T())
    {
        _start = new T[n];
        _finish = _start + n;
        _out_range = _start + n;
        for (size_t i = 0; i < n; ++i)
        {
            _start[i] = value;
        }
    }

    ~MyVector()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        if (_start)
        {
            delete[] _start;
            _start = _finish = _out_range = nullptr;
        }
    }

    const_iterator begin() const { return _start; }
    const_iterator end() const { return _finish; }

    size_t capacity() { return _out_range - _start; }
    size_t size() { return _finish - _start; }
    bool empty() { return _start == _finish; }

    void reserve(size_t n)
    {
        std::lock_guard<std::mutex> lock(_mtx);
        if (n <= capacity())
            return;
        size_t old_size = size();
        T *tmp = new T[n];
        if (_start)
        {
            for (size_t i = 0; i < old_size; ++i)
            {
                tmp[i] = _start[i];
            }
            delete[] _start;
        }
        _start = tmp;
        _finish = _start + old_size;
        _out_range = _start + n;
    }

    void push_back(T val)
    {
        std::lock_guard<std::mutex> lock(_mtx);
        if (_finish == _out_range)
        {
            size_t new_capacity = (_out_range == _start) ? 4 : (capacity() * 2);
            // inline expansion to avoid double-locking
            size_t old_size = _finish - _start;
            T *tmp = new T[new_capacity];
            for (size_t i = 0; i < old_size; ++i)
                tmp[i] = _start[i];
            delete[] _start;
            _start = tmp;
            _finish = _start + old_size;
            _out_range = _start + new_capacity;
        }
        *_finish = val;
        ++_finish;
    }

    void pop_back()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        assert(!(_start == _finish));
        --_finish;
    }

    const T &operator[](size_t pos) const
    {
        std::lock_guard<std::mutex> lock(_mtx);
        assert(pos < static_cast<size_t>(_finish - _start));
        return _start[pos];
    }
    void swap(MyVector<T> &v)
    {
        if (this == &v)
            return;
        // lock both mutexes without deadlock
        std::lock(_mtx, v._mtx);
        std::lock_guard<std::mutex> lk1(_mtx, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(v._mtx, std::adopt_lock);
        std::swap(_start, v._start);
        std::swap(_finish, v._finish);
        std::swap(_out_range, v._out_range);
    }

private:
    T *_start;
    T *_finish;
    T *_out_range;
    mutable std::mutex _mtx;
};
