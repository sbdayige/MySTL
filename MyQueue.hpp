#include <cstddef>
#include <cassert>
#include <utility> // for std::swap

template<typename T>
class MyQueue {
private:
    struct Node{
        T _data;
        Node* _next;
        
        Node(const T& _val) : _data(_val),_next(nullptr) {}
    };
    Node* _head;
    Node* _tail;
    size_t _size;

public:
    MyQueue() : _head(nullptr), _tail(nullptr), _size(0) {}

    // 拷贝构造函数
    MyQueue(const MyQueue& other) : _head(nullptr), _tail(nullptr), _size(0) {
        Node* cur = other._head;
        while (cur) {
            push(cur->_data);
            cur = cur->_next;
        }
    }

    // 移动构造函数
    MyQueue(MyQueue&& other) noexcept : _head(other._head), _tail(other._tail), _size(other._size) {
        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
    }

    // 赋值运算符重载
    MyQueue& operator=(const MyQueue& other) {
        if (this == &other) {
            return *this;
        }

        // 1. 清理当前资源
        Node* cur = _head;
        while (cur) {
            Node* next = cur->_next;
            delete cur;
            cur = next;
        }
        _head = _tail = nullptr;
        _size = 0;

        // 2. 拷贝新数据
        Node* other_cur = other._head;
        while (other_cur) {
            push(other_cur->_data);
            other_cur = other_cur->_next;
        }

        return *this;
    }

    ~MyQueue(){
        Node* cur = _head;
        while(cur){
            Node* next = cur->_next;
            delete cur;
            cur = next;
        }
        _head = _tail = nullptr;
        _size = 0;
    }

    void push(const T& val){
        Node* node = new Node(val);
        if(_tail == nullptr){
            _head = _tail = node;
        }else{
            _tail->_next = node;
            _tail = node;
        }
        _size = _size + 1;
    }

    void pop() {
        if (_head == nullptr) return;
        Node* next = _head->_next;
        delete _head;
        _head = next;
        if (_head == nullptr) {
            _tail = nullptr;
        }
        _size--;
    }

    bool empty() const {
        return _head == nullptr;
    }

    const T& front() const{
        assert(!empty());
        return _head->_data;
    }

    const size_t size() const{
        return _size;
    }

};