#include<iostream>
#include<cstring>


class MyString {
private:
    char* m_data;

public:
    explicit MyString(const char* data = nullptr){
        if(data){
            size_t len = std::strlen(data);
            m_data =  new char[len + 1];
            std::strcpy(m_data,data);
        }else{
            m_data = new char[1];
            m_data[0] = '\0';
        }

    }

    ~MyString(){
        delete[] m_data;
        m_data = nullptr;
    }

    MyString(const MyString& other){
        size_t len = std::strlen(other.m_data);
        m_data = new char[len + 1];
        std::strcpy(m_data,other.m_data);
    }

    MyString(MyString&& other) : m_data(other.m_data){
        other.m_data = nullptr;
    } 

    size_t len() const{
        return std::strlen(m_data);
    }

    MyString& operator=(const MyString& other){
        if(this == &other) return *this;
        delete[] m_data;
        size_t len = std::strlen(other.m_data);
        m_data = new char[len + 1];
        std::strcpy(m_data,other.m_data);
        return *this;
    }

    friend MyString operator+ (const MyString& l,const MyString& r){
        size_t l_len = std::strlen(l.m_data);
        size_t r_len = std::strlen(r.m_data);
        char* data = new char[l_len + r_len + 1];
        std::strcpy(data,l.m_data);
        std::strcat(data,r.m_data);
        MyString ms(data);
        delete[] data;
        return ms;
    }

    const char* c_str() const {
        return m_data ? m_data : "";
    }

    void print(const char* name) const {
        std::cout << "-> " << name << ": '" << c_str() << "', Length: " << len() << std::endl;
    }
};

signed main(){
    MyString s1("Hello"); // 调用构造函数
    s1.print("s1");
    MyString s2;         // 调用构造函数 (nullptr 版本)
    s2.print("s2");

    return 0;
}