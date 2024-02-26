#include <array>
#include <deque>
#include <string>
#include <vector>
#include <list>
#include <forward_list>

std::list<std::string> authors = {"Milton", "Shakespeare", "Austen"};
std::vector<const char*> articles = {"a", "an", "the"};
std::vector<int> ivec(10, -1);
std::list<std::string> svec(10, "hi");
std::forward_list<int> ifvec(10);
std::deque<std::string> sdvec(10);

std::array<int, 42> arr1;
std::array<std::string, 10> arr2;
std::array<int, 10>::size_type i;
std::array<int>::size_type j; //worry

