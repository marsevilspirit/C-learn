#include <iostream>

const int x = 10; // 运行时常量
constexpr int y = 20; // 编译时常量

constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    const int z = add(x, y); // 运行时调用 add()，z 在运行时确定
    constexpr int result = add(x, y); // 编译时调用 add()，result 在编译时确定

    std::cout << z <<" "<< result << std::endl;

    return 0;
}
