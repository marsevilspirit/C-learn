#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Car{
private:
    std::string m_car1;
    std::string m_car2;

public:
    Car(std::string car1, std::string car2):m_car1(car1), m_car2(car2) {}

    friend std::ostream& operator<<(std::ostream& out, const Car& car);
    friend bool operator<(Car& cars1, Car& cars2);
};

std::ostream& operator<<(std::ostream& out, const Car& car) {
    out << "(" << car.m_car1 << ", " << car.m_car2 << ")";
    return out;
}

bool operator<(Car& cars1, Car& cars2) {
    // 在此处编写比较逻辑，例如按照 m_car1 的字典顺序比较
    return cars1.m_car1 < cars2.m_car1;
}

int main(void)
{
    std::vector<Car> cars{
        {"Toyota", "Corolla"},
        {"Honda", "Accord"},
        {"Toyota", "Camry"},
        {"HOnda", "Civic"}
    };

    std::sort(cars.begin(), cars.end());

    for (const auto& car : cars) 
        std::cout << car << '\n';    

    return 0;
}
