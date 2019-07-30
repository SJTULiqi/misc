/*
This file is used to test the inherit characteristic in C++ class.
pointer to a base class can be used to visit the function in inherited class.
*/
#include<stdio.h>

class Stu
{
public:
	Stu() :m_score(0){};
	Stu(int score) :m_score(score){};
	~Stu();
private:
	int m_score;

public:
	int GetScore(){ return m_score; };
};

class GradeStu : public Stu
{
public:
	GradeStu() :Stu(0), m_grade(0){};
	GradeStu(int score, int grade) :Stu(score), m_grade(grade){};

private:
	int m_grade;
public:
	int GetGrade(){ return m_grade; };
};

int main()
{
	GradeStu* pgstu = new GradeStu(100, 7);
	Stu* pstu = pgstu;// 基类指针指向子类实例
	int grade = ((GradeStu*)pstu)->GetGrade();
	printf("grade is %d.\n", grade);
	return 0;
}
