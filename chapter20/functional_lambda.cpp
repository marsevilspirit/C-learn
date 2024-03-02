#include <functional>

int main(void)
{
    double (*addNumbers1)(double, double){
        [](double a, double b){
            return a+b;
        }
    };

    addNumbers1(1, 2);

    std::function addNumbers2{
        [](double a, double b){
            return a+b;
        }
    };

    addNumbers2(3, 4);

    auto addNumbers3{
        [](double a, double b){
            return a+b;
        }
    };

    addNumbers3(5, 6);

    return 0;
}
