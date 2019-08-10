#include <iostream>
using namespace std;

const char directions[] = {'N', 'W', 'S', 'E'};
const int  num_direction = sizeof(directions) / sizeof(directions[0]);

class State
{
public:
    State(int direction = 0)
	: directionIndex(direction)
    {}

    void onLeft()
    {
        ++directionIndex;
    }

    void onRight()
    {
        --directionIndex;
    }

    char getDirection()
    {
        while(directionIndex >= 4)
            directionIndex -= 4;
        while(directionIndex < 0)
            directionIndex += 4;
        return directions[directionIndex];
    }

private:

private:
    int directionIndex;
};

int main()
{
    int num;
    cin>>num;
    State state(0);
    for(int i = 0; i < num; ++i)
    {
        char direction;
        cin >> direction;
        if(direction == 'L')
            state.onLeft();
        else if(direction == 'R')
            state.onRight();
        else
            ; // abnormal case
    }
    char direction = state.getDirection();
    cout << direction;
    return 0;
}