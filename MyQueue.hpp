#include <cstddef>
#include <cassert>

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