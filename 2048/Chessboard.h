#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <cstddef>
#include <vector>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <map>
using namespace std;

const int BASEELEMENT = 2;

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class StartUnit
{
public:
    StartUnit(int start_ = -1, int singleBarStride_ = -1, int traverBarStride_ = -1)
    : start(start_)
    , singleBarStride(singleBarStride_)
    , traverBarStride(traverBarStride_)
    {}

    int getStart() const {return start;}
    int getSingleBarStride() const {return singleBarStride;}
    int getTraverBarStride() const {return traverBarStride;}

private:
    int start;
    int singleBarStride;
    int traverBarStride;
};

template<size_t side>
class BaseChessboard
{
public:
    BaseChessboard()
    : maxValue(0)
    , sumValue(0)
    {
        srand(time(0));
        data.resize(side * side);

        directionStartUnitMap[Direction::Up]     = StartUnit(                0,  side,     1);
        directionStartUnitMap[Direction::Down]   = StartUnit(side * (side - 1), -side,     1);
        directionStartUnitMap[Direction::Left]   = StartUnit(                0,     1,  side);
        directionStartUnitMap[Direction::Right]  = StartUnit(         side - 1,    -1,  side);
    }

    bool onUpPressed()
    {
        return onDirction(Direction::Up);
    }

    bool onDownPressed()
    {
        return onDirction(Direction::Down);
    }

    bool onLeftPressed()
    {
		return onDirction(Direction::Left);
    }

    bool onRightPressed()
    {
		return onDirction(Direction::Right);
    }

    void show()
    {
        cout << "------------------------\n";
        for(int i = 0; i < side; ++i)
        {
            for(int j = 0; j < side; ++j)
            {
                cout << setw(5) << data[i * side + j];
            }
            cout << endl;
        }
        cout << "------------------------\n";
    }

    bool full()
    {
        return availablePos.size() == 0;
    }

    void addNewElement()
    {
        updateAvailablePosition();
        if(full())
        {
            cout << "The board is full.\n";
            calculateScore();
            return;
        }

        int num = availablePos.size();
        int index = rand() % num;
        int pos = availablePos[index];
        data[pos] = BASEELEMENT;
        calculateScore();
    }

    int getMaxNum() const{return maxValue;}
    int getSumValue() const{return sumValue;}

private:

    void updateAvailablePosition()
    {
        availablePos.clear();
        availablePos.reserve(side * side);
        for(int i = 0; i < side; ++i)
        {
            for(int j = 0; j < side; ++j)
            {
                if(data[i * side + j] == 0)
                    availablePos.push_back(i * side + j);
            }
        }
    }

    void calculateScore()
    {
        sumValue = 0;
        for(int i = 0; i < side; ++i)
        {
            for(int j = 0; j < side; ++j)
            {
                if(maxValue < data[i * side + j])
                    maxValue = data[i * side + j];
                sumValue += data[i * side + j];
            }
        }
        cout << "Max element is " << maxValue << " and Total score is " << sumValue << endl;
    }

    // first element is the laziest element(least movement)
    bool updateSingleBar(vector<int>& src)
    {
        // find the non-zero item in single row/column
        vector<int> validValues;
		validValues.reserve(side);
        for(int i = 0; i < side; ++i)
        {
            if(src[i] != 0)
            {
                validValues.push_back(src[i]);
            }
        }

        // combine the two continuous equal numbers
        vector<int> result;
		result.reserve(side);
        for(int i = 0; i < validValues.size(); ++i)
        {
            // if it's last element or it's not equal to its next element
			if ((i == validValues.size() - 1) || (validValues[i] != validValues[i + 1]))
			{
				result.push_back(validValues[i]);
			}
			else // the element is equal to its next element
			{
				result.push_back(validValues[i] + validValues[i + 1]);
				i++;
			}
        }
        result.resize(side);
		
        // if changed after the possible movement, copy the result to src
		bool changed = (src != result);
		if (changed)
		{
			copy(result.begin(), result.end(), src.begin());
		}
		return changed;
    }

    bool onDirction(Direction direction)
    {
        bool changed        = false;
        StartUnit startUnit = directionStartUnitMap[direction];
        int start           = startUnit.getStart();
        int singleBarStride = startUnit.getSingleBarStride();
        int traverBarStride = startUnit.getTraverBarStride();

        for(int i = 0; i < side; ++i)
        {
            vector<int> singleBar;
            singleBar.reserve(side);
            int tmpStart = start + i * traverBarStride;
            // get original row/column
            for(int j = 0; j < side; ++j)
            {
                singleBar.push_back(data[tmpStart + j * singleBarStride]);
            }
            // update the row/column
            changed |= updateSingleBar(singleBar);
            // set the result back
            for(int j = 0; j < side; ++j)
            {
                data[tmpStart + j * singleBarStride] = singleBar[j];
            }
        }
        return changed;
    }

private:
    vector<int> data; // row first for store all chessboard data
    vector<int> availablePos;
 
    map<Direction, StartUnit> directionStartUnitMap;

    int maxValue;
    int sumValue;
};

template<size_t side>
class Game
{
public:
    Game()
    : playing(true)
    {}
    
    void run()
    {
        cout << "please enter w/s/a/d to control the movement direction.\n";
        while(playing)
        {
            chessBoard.addNewElement();
            chessBoard.show();
			char key;
			cin >> key;
			switch (key)
			{
			case 'w':
				playing = chessBoard.onUpPressed();
				break;

			case 's':
				playing = chessBoard.onDownPressed();
				break;

			case 'a':
				playing = chessBoard.onLeftPressed();
				break;

			case 'd':
				playing = chessBoard.onRightPressed();
				break;

			case 'q':
			case 'Q':
				cout << "Press q/Q and exit the game.\n";
				exit(1);
				break;

			default:
				break;
			}
            playing = !chessBoard.full();
		}
    }

private:
    BaseChessboard<side> chessBoard;
    bool playing;
};

typedef Game<4> Game2048;

#endif
