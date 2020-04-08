/* COMP2011 Spring 2020
 * Lab 7: Lights Out
 */

#include <math.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

void step(int dest[][MAX_SIZE], int x, int y, int size);
void init_figure(int dest[][MAX_SIZE], int size);
bool check_win(const int dest[][MAX_SIZE], int size);
void find_solution(const int dest[][MAX_SIZE], int size);

// Helper functions for printing
void printw(int size, int ch)
{
    cout.width(size);
    cout << ch;
}
void printw(int size, char ch)
{
    cout.width(size);
    cout << ch;
}
void print_figure(const int figure[][MAX_SIZE], int size)
{
    const int gap = 3;
    cout.fill(' ');
    printw(gap, ' ');
    printw(gap, ' ');
    for (int i = 0; i < size; ++i)
    {
        printw(gap, i);
    }
    cout << endl;
    printw(gap, ' ');
    printw(gap, '+');
    for (int i = 0; i < size; ++i)
        printw(gap, '-');
    cout << endl;
    for (int i = 0; i < size; ++i)
    {
        printw(gap, i);
        printw(gap, '|');
        for (int j = 0; j < size; ++j)
        {
            if (figure[i][j] == 0)
                printw(gap, '.');
            else
                printw(gap, 'O');
        }
        cout << endl;
    }
}

// generate a puzzle.
void init_figure(int dest[][MAX_SIZE], int size)
{
    // set random seed
    srand(static_cast<unsigned int>(time(0)));

    // The puzzle is generated by a reverse solving process which makes sure the it has the
    // solution. initialization the whole table with 0 values.
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            dest[i][j] = 0;
    // randomly flip some lights as well as their neighbors.
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (rand() % 2 == 1)
                step(dest, i, j, size);
}

void step(int dest[][MAX_SIZE], int x, int y, int size)
{
    dest[x][y] = (dest[x][y] + 1) % 2;
    if (x + 1 < size)
        dest[x + 1][y] = (dest[x + 1][y] + 1) % 2;
    if (x - 1 >= 0)
        dest[x - 1][y] = (dest[x - 1][y] + 1) % 2;
    if (y + 1 < size)
        dest[x][y + 1] = (dest[x][y + 1] + 1) % 2;
    if (y - 1 >= 0)
        dest[x][y - 1] = (dest[x][y - 1] + 1) % 2;
}

bool check_win(int dest[][MAX_SIZE], int size)
{
    bool is_win = true;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (dest[row][col] == 1)
                is_win = false;
        }
    }
    return is_win;
}

/**
 * @brief find solution by enumeration
 *
 * @param dest
 * @param size
 */
void find_solution(int dest[][MAX_SIZE], int size)
{
    int solution_figure[MAX_SIZE][MAX_SIZE] = {0};
    for (int solution_num = 0; solution_num <= pow(2, (size * size)) - 1; solution_num++)
    {
        bool is_solution = true;
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                int move_digit = size * row + col;
                if (((solution_num >> move_digit) % 2) == 1)
                    step(solution_figure, row, col, size);
            }
        }
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (dest[row][col] != solution_figure[row][col])
                    is_solution = false;
            }
        }
        if (is_solution)
        {
            for (int row = 0; row < size; row++)
            {
                for (int col = 0; col < size; col++)
                {
                    int move_digit = row * size + col;
                    if (((solution_num >> move_digit) % 2) == 1)
                        cout << "(" << row << "," << col << ")"
                             << " ";
                }
            }
            cout << endl;
            break;
        }
        else
        {
            for (int row = 0; row < size; row++)
            {
                for (int col = 0; col < size; col++)
                {
                    solution_figure[row][col] = 0;
                }
            }
        }
    }
}
/**
 * @brief recursively find solution.
 * There are two paths in recursion, judge whether step the certain grid or not.
 *
 * @param dest
 * @param size
 * @param curr
 * @return true
 * @return false
 */
bool recursive_find(int dest[][MAX_SIZE], int size, int curr)
{
    if (check_win(dest, size))
        return true;
    if (curr == size * size)
        return false;
    if (recursive_find(dest, size, curr + 1))
        return true;
    step(dest, curr / size, curr % size, size);
    if (recursive_find(dest, size, curr + 1))
    {
        cout << "(" << curr / size << "," << curr % size << ")"
             << " ";
        return true;
    }
    step(dest, curr / size, curr % size, size);
    return false;
}
void find_solution_recursively(int dest[][MAX_SIZE], int size)
{
    int copy[MAX_SIZE][MAX_SIZE] = {0};
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            copy[row][col] = dest[row][col];
        }
    }
    recursive_find(copy, size, 0);
}
// main function
int main()
{
    int size;
    cout << "Welcome to Lights Out Puzzle!" << endl << "Please input the size." << endl;
    cin >> size;

    int is_show_solution;
    cout << endl << "Do you want the solution? (1-Yes / 0-No)" << endl;
    cin >> is_show_solution;

    // figure is a 2D array that stores the states of all lights. 1 for on and 0 for off.
    int figure[MAX_SIZE][MAX_SIZE] = {};

    init_figure(figure, size);

    int x = -1, y = -1;
    do
    {
        print_figure(figure, size);
        if (check_win(figure, size))
        {
            cout << endl << "******Congratulations!******" << endl;
            return 0;
        }

        if (is_show_solution)
            find_solution_recursively(figure, size);
        cout << "Please choose a location (x, y)" << endl;
        cin >> x >> y;
        step(figure, x, y, size);
    } while (x >= 0 && y >= 0);

    return 0;
}
