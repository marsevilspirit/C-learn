#include <iostream>
#include <google/protobuf/version.h>

int main() {
    std::cout << "Protocol Buffers version: " << GOOGLE_PROTOBUF_VERSION << std::endl;
    return 0;
}
