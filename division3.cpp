#include <iostream>
using namespace std;
// 1,12,123,1234,... 这样一个序列被3整除的个数
int main()
{
    int left, right;
    cin >> left >> right;
    int rValue = right * 2 / 3;
    int lValue = (left - 1) * 2 / 3;
    cout << rValue - lValue;
    return 0;
}
