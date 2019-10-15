// 用于合适地去遍历一个区间
// 思路是按照不同的步长去遍历，为了避免存在重复或者遗漏的情况，将其对齐到2的指数幂
// 这样在遍历数组的时候是按照先大步长再小步长去遍历的

#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <cmath>

// 得到不超过输入值的最大的2的指数幂对应的指数
int get2power(unsigned int value)
{
    int count = 0;
    while(value){
        ++count;
        value = value>>1;
    }
    return count;
}

// num = 3
// [1,2,3,4,5,6,7,8]
// 8, 4, 2, 6, 1, 3, 5, 7
// [1,2,3,...,2^n-1,2^n]
// 2^(n-1) 2^(n-2) 3*2^(n-1) ... 
// 按照每次二分的顺序选择数字
vector<int> getOrder(int num)
{
    map<int, int> values;
    vector<int> result;
    int num_values = pow(2, num);
    for(int i = num; i >= 0; --i){
        int step = pow(2,i);
        for(int j = step; j <= num_values; j += step){
            if(values[j] != 1){
                values[j] = 1;
                result.push_back(j);
            }
        }
    }
    return result;
}

void swap(int& left, int& right)
{
    int temp = left;
    left = right;
    right = temp;
}

// 获取指定区域按照规则排列的数字
vector<int> getArray(int left, int right)
{
    vector<int> res;
    if(left > right){
        swap(left, right);
    }
    cout << left << ' ' << right << endl;
    unsigned int num = right - left + 1;

    int count = get2power(num);
    vector<int> values = getOrder(count);
    for(auto& it : values){
        it += left - 1; 
    }
    for(auto it = values.begin(); it != values.end();){
        if(*it > right){
            values.erase(it);
        }else{
            ++it;
        }
    }
    
    return values;
}

template<class T>
void printVector(const vector<T>& vec){
    for(int i = 0; i < vec.size();++i){
        cout << vec[i] << ' ';
    }
    cout << endl;
}

int main(int argc, char** argv)
{
    int left = 1; int right = 8;
    cout << "enter two numbers: ";
    cin >> left >> right;
    vector<int> values = getArray(left, right);
    printVector(values);
    return 0;
}
