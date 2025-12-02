#include <iostream>
#include <thread>
#include <vector>
#include "MyString.hpp"
#include "MyQueue.hpp"
#include "MyVector.hpp"

void test_string() {
    std::cout << "--- Testing MyString ---" << std::endl;
    MyString s1("Hello");
    MyString s2(" World");
    MyString s3 = s1 + s2;
    s3.print("s3");
}

void test_queue() {
    std::cout << "\n--- Testing MyQueue ---" << std::endl;
    MyQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    std::cout << "Queue size: " << q.size() << std::endl;
    std::cout << "Queue front: " << q.front() << std::endl;
    
    while(!q.empty()) {
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

void test_vector() {
    std::cout << "\n--- Testing MyVector ---" << std::endl;
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    std::cout << "Vector size: " << v.size() << std::endl;
    std::cout << "Vector capacity: " << v.capacity() << std::endl;
    
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    test_string();
    test_queue();
    test_vector();
    return 0;
}
