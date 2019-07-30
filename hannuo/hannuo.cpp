#include <iostream>
#include <string>
#include "assert.h"
using namespace std;

void hanno(int n, const string& from, const string& to, const string& middle)
{
    assert(n > 0);
    if(n == 1)
    {
        cout << from << " --> " << to << endl;
        return;        
    }

    hanno(n - 1,   from, middle,     to);
    hanno(    1,   from,     to, middle);
    hanno(n - 1, middle,     to,   from);
}

int main()
{
    std::string A = "A";
    std::string B = "B";
    std::string C = "C";

    hanno(3, A, B, C);
    return 0;
}
