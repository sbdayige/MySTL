#pragma once

#include <iostream>
#include <cstddef>
#include <cassert>
#include <utility> // for std::swap

template <typename T>
class MyStack
{
private:
    struct Node
    {
        T _data;
        Node *_next;

        Node(const T &val) : _data(val), _next(nullptr) {};
    };
    Node *_head;
    size_t _size;

public:
    MyStack() : _head(nullptr), _size(0) {}

    // Destructor
    ~MyStack()
    {
        while (!empty())
        {
            pop();
        }
    }

    // Copy Constructor
    MyStack(const MyStack &other) : _head(nullptr), _size(0)
    {
        if (other._head == nullptr)
            return;

        Node *current = other._head;
        Node *newTail = nullptr;

        while (current != nullptr)
        {
            Node *newNode = new Node(current->_data);
            if (_head == nullptr)
            {
                _head = newNode;
                newTail = newNode;
            }
            else
            {
                newTail->_next = newNode;
                newTail = newNode;
            }
            current = current->_next;
        }
        _size = other._size;
    }

    // Assignment Operator
    MyStack &operator=(MyStack other)
    {
        swap(*this, other);
        return *this;
    }

    void push(const T &val)
    {
        Node *newNode = new Node(val);
        newNode->_next = _head;
        _head = newNode;
        _size++;
    }

    void pop()
    {
        assert(!empty());
        Node *temp = _head;
        _head = _head->_next;
        delete temp;
        _size--;
    }

    bool empty() const
    {
        return _size == 0;
    }

    const T &top() const
    {
        assert(!empty());
        return _head->_data;
    }

    size_t size() const
    {
        return _size;
    }

    friend void swap(MyStack &first, MyStack &second) noexcept
    {
        using std::swap;
        swap(first._head, second._head);
        swap(first._size, second._size);
    }
};