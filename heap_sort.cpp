#include <iostream>
using namespace std;

// 交换堆中的两个元素
void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 对包含n个节点的堆的第i个节点进行heapify的操作
void heapify(int* arr, int n, int i){
    int ch1 = 2 * i + 1;
    int ch2 = 2 * i + 2；
    int maxIdx = i;
    if(ch1 < n && arr[ch1] > arr[maxIdx]){
        maxIdx = ch1;
    }
    if(ch2 < n && arr[ch2] > arr[maxIdx]){
        maxIdx = ch2;
    }
    if(maxIdx == i)
        return;
    swap(arr, maxIdx, i);
    heapify(arr, n, maxIdx);
}

// 建堆 找到最后一个父节点，然后不断往回找父节点，对每个父节点执行一次heapify的操作
void buildHeap(int* arr, int n){
    int last_node = n - 1;
    int parent = (last_node - 1) / 2;
    for(int i = parent; i >= 0; --i){
        heapify(arr, n, i);
    }
}

// 对给定的数组进行堆排序
void heapsort(int * arr, int n){
    buildHeap(arr, n);
    for(int i = n - 1; i >= 1; --i){
        swap(arr, 0, i);
        heapify(arr, i, 0);
    }
}

int main(){
    int array[] = {10,6,3,7,4,2,1,9,8,5};
    int size = sizeof(array)/sizeof(array[0]);
    heapsort(array, size);
    for(int i = 0; i < size; ++i){
        cout << array[i] << ' ';
    }
    cout << endl;
}
