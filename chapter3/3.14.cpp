#include <iostream>
#include <vector>
using namespace std;
int main(void)
{
    vector<string> ivec; 
    string a;
    while(cin >> a)
    {
        ivec.push_back(a);
    }
    for(auto b : ivec)
    {
        cout << b << " ";
    }

    return 0;
}
