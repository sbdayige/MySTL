#pragma once

#include <iostream>
#include <algorithm> // for std::copy
#include <utility>   // for std::swap
#include <cassert>
#include <mutex>

template <typename T>
class MyDeque
{
private:
    struct Node
    {
        T data_;
        Node *next_;
        Node *prev_;
        Node(const T val) : data_(val), next_(nullptr), prev_(nullptr) {}
    };

    Node *head_;
    Node *tail_;
    size_t size_;

public:
    MyDeque() : head_(nullptr), tail_(nullptr), size_(0) {}

    ~MyDeque()
    {
        // 释放所有节点
        Node *cur = head_;
        while (cur)
        {
            Node *next = cur->next_;
            delete cur;
            cur = next;
        }
        head_ = tail_ = nullptr;
        size_ = 0;
    }

    // 深拷贝构造
    MyDeque(const MyDeque &other) : head_(nullptr), tail_(nullptr), size_(0)
    {
        for (Node *cur = other.head_; cur != nullptr; cur = cur->next_)
        {
            push_back(cur->data_);
        }
    }

    // 拷贝赋值（copy-and-swap）
    MyDeque &operator=(MyDeque other)
    {
        swap(other);
        return *this;
    }

    // 移动构造
    MyDeque(MyDeque &&other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    // 移动赋值
    MyDeque &operator=(MyDeque &&other) noexcept
    {
        if (this != &other)
        {
            // 释放当前节点
            Node *cur = head_;
            while (cur)
            {
                Node *n = cur->next_;
                delete cur;
                cur = n;
            }
            // 接管资源
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 交换成员
    void swap(MyDeque &other) noexcept
    {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

    bool empty() const
    {
        return size_ == 0;
    }

    const T front() const
    {
        assert(!empty());
        return head_->data_;
    }

    const T back() const
    {
        assert(!empty());
        return tail_->data_;
    }

    void push_back(const T &val)
    {
        Node *node = new Node(val);
        if (empty())
        {
            head_ = tail_ = node;
        }
        else
        {
            node->prev_ = tail_;
            tail_->next_ = node;
            tail_ = node;
        }
        size_++;
    }

    void pop_back()
    {
        assert(!empty());
        Node *node = tail_;
        tail_ = tail_->prev_;
        if (tail_)
            tail_->next_ = nullptr;
        else
            head_ = nullptr;
        delete node;
        size_--;
    }

    void push_front(const T &val)
    {
        Node *node = new Node(val);
        if (empty())
        {
            head_ = tail_ = node;
        }
        else
        {
            head_->prev_ = node;
            node->next_ = head_;
            head_ = node;
        }
        size_++;
    }

    void pop_front()
    {
        assert(!empty());
        Node *node = head_;
        head_ = head_->next_;
        if (head_)
            head_->prev_ = nullptr;
        else
            tail_ = nullptr;
        delete node;
        size_--;
    }
};