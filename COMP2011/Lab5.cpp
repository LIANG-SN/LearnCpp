/**
 * @file Lab5.cpp
 * @author Shengnan Liang (liangsn2001@outlook.com)
 * @brief Shuttle Puzzle
 * @version 0.1
 * @date 2020-03-24
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <iostream>
using namespace std;

const int MAX_SIZE = 1000;

/**
 * @brief Print the current game board
 *
 * @param board
 * @param valid_length
 */
void print(const char board[], int valid_length)
{
    cout << " [";
    for (int i = 0; i < valid_length; ++i)
        cout << i;
    cout << "]" << endl;
    cout << "  ";
    for (int i = 0; i < valid_length; ++i)
        cout << board[i];
    cout << endl;
}

/**
 * @brief Initialize the game board with white (W) marbles on the left and
 * black (B) marbles on the right, and a gap in between
 * @param board
 * @param num_W
 * @param num_B
 * @return the length of the puzzle
 */
int initialize(char board[], int num_W, int num_B)
{
    int length = num_W + num_B + 1;
    for (int i = 0; i < num_W; i++)
    {
        board[i] = 'W';
    }
    board[num_W] = '.';
    for (int i = num_W + 1; i < length; i++)
    {
        board[i] = 'B';
    }
    return length;
}

/**
 * @brief Jump a marble over 1 and only 1 marble of the opposite color into the
 * empty position. CANNOT backtrack moves.
 * @param board
 * @param length
 * @param index
 * @return true: the jump is valid
 * @return false: invalid jump
 */
bool jump(char board[], int length, int index)
{
    bool valid;
    if (board[index] == 'W' && board[index + 2] == '.' &&
        board[index + 1] == 'B' && index + 2 <= length - 1)
    {
        board[index + 2] = 'W';
        board[index] = '.';
        valid = true;
    }
    else if (board[index] == 'B' && board[index - 2] == '.' &&
             board[index - 1] == 'W' && index - 2 >= 0)
    {
        board[index - 2] = 'B';
        board[index] = '.';
        valid = true;
    }
    else
        valid = false;
    return valid;
}

/**
 * @brief Slide a marble. CANNOT backtrack moves.
 * @param board
 * @param length
 * @param index
 * @return true: the slide is valid
 * @return false: invalid slide
 */
bool slide(char board[], int length, int index)
{
    bool valid;
    if (board[index] == 'W' && board[index + 1] == '.' &&
        index + 1 <= length - 1)
    {
        board[index] = '.';
        board[index + 1] = 'W';
        valid = true;
    }
    else if (board[index] == 'B' && board[index - 1] == '.' && index - 1 >= 0)
    {
        board[index] = '.';
        board[index - 1] = 'B';
        valid = true;
    }
    else
        valid = false;
    return valid;
}

/*
 * Returns true if all black marbles are on the left and white marbles are on
 * the right otherwise, returns false
 */
bool game_finished(const char board[], int num_W, int num_B)
{
    int count = 0;
    bool finished = false;
    for (int i = 0; i < num_B; i++)
    {
        if (board[i] == 'B')
            count++;
    }

    for (int i = num_B + 1; i <= num_B + num_W; i++)
    {
        if (board[i] == 'W')
            count++;
    }
    if (count == num_B + num_W)
        finished = true;
    return finished;
}

int main()
{
    char board[MAX_SIZE] = {};
    int num_W, num_B;

    // Get the number of white (W) & black (B) marbles
    cout << "Num of white and black marbles: ";
    cin >> num_W >> num_B;

    // Initialize the board
    int length = initialize(board, num_W, num_B);
    print(board, length);

    // Continue while not all marbles are switched
    while (!game_finished(board, num_W, num_B))
    {
        // Get the index (position) for the move (operation), -1 means give up
        // the game
        int index;
        cout << "Index (-1 to exit): ";
        cin >> index;
        if (index == -1)
        {
            cout << "Exit." << endl;
            break;
        }

        // Get the operation, 'J' for jump or 'S' for slide
        char op;
        cout << "'J' or 'S': ";
        cin >> op;
        bool res = false;
        switch (op)
        {
        case 'J':
            res = jump(board, length, index);
            break;
        case 'S':
            res = slide(board, length, index);
            break;
        }
        if (!res)
            cout << "Error!" << endl;
        else
            print(board, length);
    }

    if (game_finished(board, num_W, num_B))
    {
        cout << "Congratulations!" << endl;
    }

    return 0;
}