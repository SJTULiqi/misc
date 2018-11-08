/* This file is used to test the performance of STL map */
#include <map>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<windows.h>
#include<time.h>
using namespace std;

#define random(x) (rand()%x)

const int ImageIDs = 19;
string IDs[ImageIDs] = { "1002/", "1004/", "1005/", "1007/", "1008/", "1011/", "1012/", "1013/", 
"1014/", "1015/", "1016/", "1018/", "1019/", "1022/", "1023/", "1024/", "1025/", "1026/", "1027/" };

double t1, t2;
int main()
{
	int size = 5000000;
	vector<string> vstr;
	srand(time(0));
	for (int i = 0; i < size; ++i)
	{
		// actually, in order to create the random is the most time-consuming
		int index = random(ImageIDs); 
		vstr.push_back(IDs[index]);
		if ((i % 10000 == 0) && i >0)
		{
			printf("%d random numbers are created.\n",i);
		}
	}

	// for tradition method be comparing the strings
	t1 = GetTickCount();
	for (int i = 0; i < size; ++i)
	{
		char*src = (char*)vstr[i].c_str();
		for (int j = 0; j < ImageIDs; ++j)
		{
			char* dst = (char*)IDs[j].c_str();
			if (strcmp(src, dst) == 0)
				break;
		}
	}
	t2 = GetTickCount();
	printf("Tradition Elapse time is %fms.\n",t2-t1); // find 100000 strings will cost about only 31ms

	// by using STL map method
	map<string, int> mapIndex;
	for (int i = 0; i < ImageIDs; ++i)
	{
		mapIndex.insert(map<string, int>::value_type(IDs[i],i));
	}
	t1 = GetTickCount();
	for (int i = 0; i < size; ++i)
	{
		int index = mapIndex.at(vstr[i]);
		//printf("index:%d, vstr:%s",index,vstr[i].c_str());
	}
	t2 = GetTickCount();
	printf("STL Map Elapse time is %fms.\n",t2-t1); // find 100000 strings will cost about only 312ms

	return 0;
}

/* result:
1. By using the map in STL, time is more consuming than by using the comparing written by myself. The reason 
behind this is maybe that keeping a red-black tree in memory is time-consuming.(just my guess).
2. I ever think of that map will perfom better in larger scale data, however, by creating 5000000 random number
and compare, it finds that 2297ms/16125ms. In this process, I find that generating the random number is really 
time-consuming. It takes me about 5min to finish the random-generating process. And the printf may has lots of
latancy.
*/
