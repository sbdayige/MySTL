#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include "MyString.hpp"
#include "MyQueue.hpp"
#include "MyVector.hpp"
#include "MyStack.hpp"
#include "MyDeque.hpp"
#include "Myshared_ptr.hpp"

void test_string()
{
    std::cout << "--- Testing MyString ---" << std::endl;
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;
    s3.print("s3");
}

void test_stack()
{
    std::cout << "\n--- Testing MyStack ---" << std::endl;
    MyStack<int> s;
    s.push(100);
    s.push(200);
    s.push(300);

    std::cout << "Stack size: " << s.size() << std::endl;
    std::cout << "Stack top: " << s.top() << std::endl;

    while (!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;

    // Test copy constructor
    MyStack<int> s2;
    s2.push(1);
    s2.push(2);
    MyStack<int> s3 = s2;
    std::cout << "s3 (copy of s2) top: " << s3.top() << std::endl;
}

void test_queue()
{
    std::cout << "\n--- Testing MyQueue ---" << std::endl;
    MyQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    std::cout << "Queue size: " << q.size() << std::endl;
    std::cout << "Queue front: " << q.front() << std::endl;

    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;

    // Test copy constructor and assignment
    MyQueue<int> q2;
    q2.push(10);
    q2.push(20);
    MyQueue<int> q3 = q2; // Copy constructor
    std::cout << "q3 (copy of q2) front: " << q3.front() << std::endl;

    MyQueue<int> q4;
    q4 = q2; // Assignment operator
    std::cout << "q4 (assigned from q2) front: " << q4.front() << std::endl;
}

void test_vector()
{
    std::cout << "\n--- Testing MyVector ---" << std::endl;
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::cout << "Vector size: " << v.size() << std::endl;
    std::cout << "Vector capacity: " << v.capacity() << std::endl;

    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void test_deque()
{
    std::cout << "\n--- Testing MyDeque ---" << std::endl;
    MyDeque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_front(0);

    std::cout << "Deque front: " << d.front() << " back: " << d.back() << std::endl;

    std::cout << "Pop front sequence: ";
    while (!d.empty())
    {
        std::cout << d.front() << " ";
        d.pop_front();
    }
    std::cout << std::endl;

    // Test copy and move
    MyDeque<int> d2;
    d2.push_back(10);
    d2.push_back(20);
    MyDeque<int> d3 = d2; // copy
    std::cout << "d3 (copy) front: " << d3.front() << std::endl;

    MyDeque<int> d4;
    d4 = d2; // copy assign
    std::cout << "d4 (assigned) back: " << d4.back() << std::endl;

    MyDeque d5 = std::move(d2); // move
    std::cout << "d5 (moved) front: " << d5.front() << std::endl;
}

void test_shared_ptr()
{
    std::cout << "\n--- Testing shared_ptr ---" << std::endl;
    shared_ptr<int> p1(new int(42));
    std::cout << "p1 count=" << p1.count() << ", value=" << *p1 << std::endl;

    // copy
    shared_ptr<int> p2 = p1;
    std::cout << "after copy p1.count=" << p1.count() << ", p2.count=" << p2.count() << std::endl;

    // move
    shared_ptr<int> p3 = std::move(p2);
    std::cout << "after move p3.count=" << p3.count() << ", p2.count=" << p2.count() << std::endl;

    // reset
    p3.reset(new int(100));
    std::cout << "after reset p3.count=" << p3.count() << ", *p3=" << *p3 << std::endl;
}

int main()
{
    // test_string();
    // test_stack();
    // test_queue();
    test_deque();
    test_shared_ptr();
    // test_vector();
    return 0;
}
