#include <iostream>
#include <vector>
using namespace std;

int getClampNum(const vector<int>& array)
{
    int num_array_ele = array.size();
    int num_clamp = 0;
    for(int i = 0; i < num_array_ele;)
    {
        if(array[i] == 1)
        {
            num_clamp++;
            i += 3;
        }
        else
        {
            ++i;
        }
    }
    return num_clamp;
}

int main()
{
    int num_array;
    cin >>num_array;
	vector<vector<int>> arrays;
	arrays.reserve(num_array);
	for (int i = 0; i < num_array; ++i)
    {
        int num_array_element;
		cin >> num_array_element;
		vector<int> array;
		array.reserve(num_array_element);
        char ch;
        for(int j = 0; j < num_array_element; ++j)
        {
            cin >> ch;
            if(ch == '.')
                array.push_back(1);
            else if(ch == 'X')
                array.push_back(0);
            else
            {
                ;// do nothing
            }
        }
		arrays.push_back(array);
    }

    for(int i = 0; i < num_array; ++i)
    {
        int num_clamp = getClampNum(arrays[i]);
        cout << num_clamp << endl;
    }

    return 0;
}