#include <algorithm>
#include <string>
#include <vector>

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());

    auto end_unique = unique(words.begin(), words.end());

    words.erase(end_unique, words.end());

}
