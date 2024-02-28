#include <iostream>

template <typename T>
class Auto_ptr1
{
    T* m_ptr;
public:
    Auto_ptr1(T* ptr=nullptr)
        :m_ptr(ptr)
    {
    }

    ~Auto_ptr1()
    {
        delete m_ptr;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }   
};

class Resource 
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi\n"; }
};

void someFunction()
{
    Auto_ptr1<Resource>ptr(new Resource());

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
    if(x == 0)
        return;

    ptr->sayHi();
}

int main(void)
{
    someFunction();

    return 0;
}
