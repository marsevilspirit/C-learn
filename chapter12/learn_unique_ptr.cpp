#include <iostream>
#include <memory>

class Resource 
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main(void)
{
    std::unique_ptr<Resource> res{ new Resource{} };

    return 0;
}
