#include <iostream>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int count = 0;
    int y_start = max(k,1);
    for(int x = 1; x <= n; ++x)
    {
        for(int y = 1; y <= n; ++y)
        {
			if ((x % y) >= k)
			{
				//cout << x << ' ' << y << endl;
				count++;
			}
        }
    }
    cout << count << endl;
    return 0;
}
