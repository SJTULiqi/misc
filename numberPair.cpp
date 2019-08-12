#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LLong;

int main()
{
    int n, k;
    cin >> n >> k;
    // 使用long long的原因是可能会超出int的表示范围,而long字节数不确定,long long确定是64位的
	LLong count = 0;
    if(k == 0)
    {
        // 牛客网不支持在这里写成 long long(n) ,所以 typedef 一下
		count = LLong(n) * LLong(n);
        cout << count;
        return 0;
    }

    for(int y = k + 1; y <= n; ++y)
    {
        int division = n / y;
        count += (y - k) * division + max(0, n - division * y - k + 1);
    }
    cout << count << endl;
    return 0;
}
