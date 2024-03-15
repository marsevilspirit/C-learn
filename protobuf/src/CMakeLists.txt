add_subdirectory(proto)

add_executable(test test.cpp)

target_link_libraries(test proto)
