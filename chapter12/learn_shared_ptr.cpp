#include <iostream>
#include <memory>

class Resource 
{
public:
    Resource() {std::cout << "Resource acquired\n";}
    ~Resource() {std::cout << "Resource destroyed\n";}
};

int main(void)
{
    Resource* res {new Resource};
    std::shared_ptr<Resource> ptr1{res};
    {
        std::shared_ptr<Resource> ptr2{ptr1};
        
        std::cout << "Killing one shared pointer\n";
    }

    std::cout << "Killing another shared pointer\n";

    return 0;
}
