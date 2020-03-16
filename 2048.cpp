#include <iostream>

#include "stdlib.h"
#include "time.h"

using namespace std;
class Gameboard
{
   public:
    void update()
    {
        char input;
        cout << "Input directon:" << endl;
        cin >> input;
        switch (input)
        {
        case 'w':;
        case 'W':
            moveUp();
            break;
        case 's':;
        case 'S':
            moveDown();
            break;
        case 'a':;
        case 'A':
            moveLeft();
            break;
        case 'd':;
        case 'D':
            moveRight();
            break;
        }
        randomGenerate();
    }
    void print()
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                cout << "    " << array[row][col];
            }
            cout << endl;
        }
    }
    bool checkWin()
    {
        bool win = false;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (array[i][j] == 32)
                    win = true;
            }
        }
        return win;
    }
    bool checkLose()
    {
        bool lose = false;
        int remainSpace = 0;
        bool stack = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (array[i][j] == 0)
                    remainSpace++;
            }
        }
        for (int row = 0; row < 3; row++)
        {
            if (array[row][0] == array[row][1] ||
                array[row][2] == array[row][1])
                stack = false;
        }
        for (int col = 0; col < 3; col++)
        {
            if (array[0][col] == array[1][col] ||
                array[2][col] == array[1][col])
                stack = false;
        }
        if (remainSpace == 0 && stack)
            lose = true;
        return lose;
    }
    void randomGenerate()
    {
        if(remainSpace > 0)
        {
            // ramdom generate 2 or 4 at random place
        srand((unsigned)time(0));
        int newNum = 0, place = 0;
        newNum = ((rand() % 2) + 1) * 2;
        place = rand() % 8;
        if (array[place / 3][place % 3] == 0)
            array[place / 3][place % 3] = newNum;
        else
            randomGenerate();
        }
    }

   private:
    int array[3][3] = {0};
    int remainspace = 8 ;
    void moveUp()
    {
        for (int col = 0; col < 3; col++)
        {
            // loop twice in case there are two '0's
            for (int i = 0; i < 2; i++)
            {
                for (int row = 0; row < 2; row++)
                {
                    if (array[row][col] == 0)
                    {
                        array[row][col] = array[row + 1][col];
                        array[row + 1][col] = 0;
                    }
                }
            }
            if (array[0][col] == array[1][col])
            {
                array[0][col] *= 2;
                array[1][col] = array[2][col];
                array[2][col] = 0;
            }
            if (array[1][col] == array[2][col])
            {
                array[1][col] *= 2;
                array[2][col] = 0;
            }
        }
    }
    void moveDown()
    {
        for (int col = 0; col < 3; col++)
        {
            // loop twice in case there are two '0's
            for (int i = 0; i < 2; i++)
            {
                for (int row = 2; row >0; row--)
                {
                    if (array[row][col] == 0)
                    {
                        array[row][col] = array[row - 1][col];
                        array[row - 1][col] = 0;
                    }
                }
            }
            if (array[2][col] == array[1][col])
            {
                array[2][col] *= 2;
                array[1][col] = array[0][col];
                array[0][col] = 0;
            }
            if (array[1][col] == array[0][col])
            {
                array[1][col] *= 2;
                array[0][col] = 0;
            }
        }
    }
    void moveLeft()
    {
        for (int row = 0; row < 3; row++)
        {
            // loop twice in case there are two '0's
            for (int i = 0; i < 2; i++)
            {
                for (int col = 0; col < 2; col++)
                {
                    if (array[row][col] == 0)
                    {
                        array[row][col] = array[row][col+1];
                        array[row][col+1] = 0;
                    }
                }
            }
            if (array[row][0] == array[row][1])
            {
                array[row][0] *= 2;
                array[row][1] = array[row][2];
                array[row][2] = 0;
            }
            if (array[row][1] == array[row][2])
            {
                array[row][1] *= 2;
                array[row][2] = 0;
            }
        }
    }
    void moveRight()
    {
        for (int row = 0; row < 3; row++)
        {
            // loop twice in case there are two '0's
            for (int i = 0; i < 2; i++)
            {
                for (int col = 2; col > 0; col--)
                {
                    if (array[row][col] == 0)
                    {
                        array[row][col] = array[row][col -1];
                        array[row][col -1] = 0;
                    }
                }
            }
            if (array[row][2] == array[row][1])
            {
                array[row][2] *= 2;
                array[row][1] = array[row][0];
                array[row][0] = 0;
            }
            if (array[row][1] == array[row][0])
            {
                array[row][1] *= 2;
                array[row][0] = 0;
            }
        }
    }
};

int main()
{
    Gameboard gameboard;
    cout << "Game start!!!" << endl;
    gameboard.randomGenerate();
    gameboard.print();
    while (true)
    {
        gameboard.update();
        gameboard.print();
        if (gameboard.checkLose())
        {
            cout << "You lose! Try again." << endl;
            break;
        }
        if(gameboard.checkWin())
        {
            cout << "Win!!!" << endl;
            break;
        }
    }
    return 0;
}
