#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Job
{
    Job(int diff, int mon)
    : difficulty(diff)
    , money(mon)
    {}

    int difficulty;
    int money;
};

bool operator < (const Job& lhs, const Job& rhs)
{
	return lhs.difficulty < rhs.difficulty;
}

template<class T>
vector<size_t> sort_index(const vector<T> & v)
{
	vector<size_t> idx(v.size());
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(),
		[&v](size_t& i1, size_t& i2){return v[i1] < v[i2]; });
	return idx;
}

// jobs and persons are ordered
vector<int> getJobIndexes(const vector<int>& persons, const vector<Job>& jobs)
{
    int nPerson = persons.size();
    int nJob = jobs.size();
    
    vector<int> indexes(nPerson);
    int res = 0;
    for(int i = 0; i < nPerson; ++i)
    {
        while(res < nJob && persons[i] >= jobs[res].difficulty)
        {
            res++;
        }
        indexes[i] = res - 1;
    }
    return indexes;
}

int main()
{
    // handle input data
    int nPerson, nJobs;
    cin >> nJobs >> nPerson;
    vector<Job> jobs;
    jobs.reserve(nJobs);
    for(int i = 0; i < nJobs; ++i)
    {
        int difficulty, money;
        cin >> difficulty >> money;
        jobs.push_back(Job(difficulty, money));
    }
    vector<int> persons;
    persons.reserve(nPerson);
    for(int i = 0; i < nPerson; ++i)
    {
        int capi;
        cin >> capi;
        persons.push_back(capi);
    }

    // 先按照难度级别排序
    sort(jobs.begin(), jobs.end());

    // DP 建表 每个难度级别下的薪资最高的工作
    vector<Job> bestJobs;
    bestJobs.reserve(nJobs);
    int maxMoney = jobs[0].money;
    for(int i = 0; i < nJobs; ++i)
    {
        int money = jobs[i].money;
        if(money > maxMoney)
        {
            maxMoney = money;
        }
        bestJobs.push_back(Job(jobs[i].difficulty, maxMoney));
    }

	// 按照人的能力排序
	// indexes是排好序的数组中每个元素在原数组中的索引
	// 需要的是原数组中的元素在排好序的数组中的索引，所以需要reverse一下
	vector<size_t> indexes = sort_index(persons);
	vector<size_t> reverse_indexes(nPerson);
	for (int i = 0; i < nPerson; ++i)
	{
		reverse_indexes[indexes[i]] = i;
	}
	sort(persons.begin(), persons.end());

    // 根据人的能力查表去得到薪资最高的工作
    vector<int> job_indexes = getJobIndexes(persons, bestJobs);

    for(int i = 0; i < nPerson; ++i)
    {
		int index = job_indexes[reverse_indexes[i]];
		int money = (index == -1) ? 0 : bestJobs[index].money;
		cout << money << endl;
    }

    return 0;
}
