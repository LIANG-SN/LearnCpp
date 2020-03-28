/*
 * COMP2011 (Spring 2020) Assignment 1: Kaprekar's Constant
 *
 * Student name: Shengnan Liang
 * Student ID: 20677615
 * Student email: sliangal@connect.ust.hk
 *
 * Note:
 * 1. Add your code ONLY in the corresponding "TODO" area.
 * 2. DO NOT change the function header of the given functions.
 * 3. DO NOT add additional libraries.
 * 4. DO NOT use array, otherwise ZERO marks for the assignment.
 * 5. You can add helper function(s) if needed.
 */
#include <math.h>

#include <iostream>
using namespace std;

const bool ASCENDING = 0;
const bool DESCENDING = 1;
const bool DEBUG = true;

/**
 *  Task 1: selectDigit() returns one digit from a given index location of an
 * arbitrary positive integer The index starts from 0 at the rightmost digit The
 * function return -1 if index is invalid Examples: selectDigit(123, 0) = 3,
 * selectDigit(1234, 3) = 1, selectDigit(123, 3) = -1, selectDigit(123, -1) = -1
 */
int selectDigit(int number, int index)
{
    int length = 0, digit = 0;
    while ((10 ^ length) <= number)
        length++;
    if (index < 0 || index >= length)
        digit = -1;
    else
    {
        digit = (number / (int)(pow(10, index))) % 10;
    }
    return digit;
}

/**
 *  Task 2: isRepdigit() checks whether all digits in a positive integer are the
 * same It returns true if Yes, false otherwise Examples: isRepdigit(222) =
 * true, isRepdigit(212) = false, isRepdigit(2) = true
 */
bool isRepdigit(int number)
{
    bool repeat = true;
    int lastDigit = number % 10;
    for (int i = 0; number / (int)pow(10, i) > 0; i++)
    {
        int currentDigit = (number / (int)pow(10, i)) % 10;
        if (lastDigit != currentDigit)
            repeat = false;
        lastDigit = currentDigit;
    }
    return repeat;
}

/**
 *  Task 3: sortDigit() takes an arbitrary positive integer number,
 *  and returns a new integer with all digits in number arranged in ascending or
 * descending order Examples: sortDigit(16845, ASCENDING) = 14568,
 * sortDigit(16845, DESCENDING) = 86541 The function should be able to handle
 * number consists 0s Examples: sortDigit(500, ASCENDING) = 5, sortDigit(100250,
 * DESCENDING) = 521000, sortDigit(100250, ASCENDING) = 125
 */
int sortDigit(int number, bool order)
{
    int sortedNum = 0;
    if (order == DESCENDING)
    {
        for (int i = 9; i >= 0; i--)
        {
            int tmpNumber = number;
            while (tmpNumber > 0)
            {
                int digit = tmpNumber % 10;
                if (digit == i)
                {
                    sortedNum *= 10;
                    sortedNum += digit;
                }
                tmpNumber /= 10;
            }
        }
    }
    else
    {
        for (int i = 0; i <= 9; i++)
        {
            int tmpNumber = number;
            while (tmpNumber > 0)
            {
                int digit = tmpNumber % 10;
                if (digit == i)
                {
                    sortedNum *= 10;
                    sortedNum += digit;
                }
                tmpNumber /= 10;
            }
        }
    }
    return sortedNum;
}

/**
 * Task 4: isKaprekar6174() takes an arbitrary positive integer,
 * and returns the number of steps needed to reach Kaprekar's constant 6174
 * The function returns -1 if the number can't reach 6174
 * when DEBUG is true, calculation details needs to be printed out
 * Output format for the calculation details: Each row represents a subtraction
 * calculation There is no space between the number and minus sign. There is no
 * space between the number and equal sign
 */
int isKaprekar6174(int number, bool debug)
{
    int step = 0;
    if ((isRepdigit(number)) || ((number / 1000) == 0 )|| ((number / 1000) >= 10))
    {
        step = -1;
        if (debug)
        {
            cout << "can't reach Kaprekar's constant 6174" << endl;
        }
    }
    else
    {
        do
        {
            number =
                sortDigit(number, DESCENDING) - sortDigit(number, ASCENDING);
            if (number < 10)
                number *= 1000;
            else if (number < 100)
                number *= 100;
            else if (number < 1000)
                number *= 10;
            else
                ;
            step++;
            if (debug)
            {
                cout << sortDigit(number, DESCENDING) << "-"
                     << sortDigit(number, ASCENDING) << "=" << number << endl;
            }
        } while (number != 6174);
    }
    return step;
}

/**
 * Task 5: printStat() bincounts #steps to reach Kaprekar's constant 6174 for
 * numbers in a given range from m to n (both inclusive) Then print the bar
 * chart (*) For simplicity, you can assume that m and n are positive integers
 * and there is always a valid range 8 bins are used, which count the numbers
 * with 1 to 7 steps to reach Kaprekar's constant 6174, or fail to do so A * is
 * printed for every 50 counted Print a * if there is remainder For example if
 * bincount = 350, print 7 stars; bincount = 351, print 8 stars Output format:
 * For each row, starts with the bin number (i.e. 1 to 7) and immediately
 * followed by the star. Do not leave any spaces between them Output format: The
 * last row (eighth row) of the output represents the failure case (started with
 * -1 and immediately followed by the star, do not leave any spaces between
 * them)
 */
void printStat(int m, int n)
{
    for (int k = 1; k <= 7; k++)
    {
        int count = 0;
        int star = 0;
        for (int i = m; i <= n; i++)
        {
            if (isKaprekar6174(i, false) == k)
                count++;
        }
        if (count % 50 == 0)
            star = count / 50;
        else
            star = count / 50 + 1;
        cout << k;
        for (int i = 0; i < star; i++)
            cout << "*";
        cout << endl;
    }
    int count = 0;
    int star = 0;
    for (int i = m; i <= n; i++)
    {
        if (isKaprekar6174(i, false) == -1)
            count++;
    }
    if (count % 50 == 0)
        star = count / 50;
    else
        star = count / 50 + 1;
    cout << -1;
    for (int i = 0; i < star; i++)
        cout << "*";
    cout << endl;
}

// This is the main function. It is already done. Please DO NOT make any
// modification.
int main()
{
    cout << "Task 1:" << endl;
    cout << "selectDigit(896543,0) = " << selectDigit(896543, 0) << endl;
    cout << "selectDigit(896543,5) = " << selectDigit(896543, 5) << endl;
    cout << "selectDigit(896543,-1) = " << selectDigit(896543, -1) << endl;
    cout << "selectDigit(896543,6) = " << selectDigit(896543, 6) << endl;

    cout << endl << "Task 2:" << endl;
    cout << "isRepdigit(2999) " << boolalpha << isRepdigit(2999) << endl;
    cout << "isRepdigit(888888) " << boolalpha << isRepdigit(888888) << endl;
    cout << "isRepdigit(1) " << boolalpha << isRepdigit(1) << endl;

    cout << endl << "Task 3:" << endl;
    cout << "sortDigit(54321, ASCENDING) = " << sortDigit(54321, ASCENDING)
         << endl;
    cout << "sortDigit(794621, ASCENDING) = " << sortDigit(794621, ASCENDING)
         << endl;
    cout << "sortDigit(794621, DESCENDING) = " << sortDigit(794621, DESCENDING)
         << endl;
    cout << "sortDigit(100250, ASCENDING) = " << sortDigit(100250, ASCENDING)
         << endl;
    cout << "sortDigit(100250, DESCENDING) = " << sortDigit(100250, DESCENDING)
         << endl;
    cout << "sortDigit(500, ASCENDING) = " << sortDigit(500, ASCENDING) << endl;

    cout << endl << "Task 4:" << endl;
    cout << "isKaprekar6174(546, DEBUG) = " << isKaprekar6174(546, !DEBUG)
         << endl;
    isKaprekar6174(546, DEBUG);
    cout << "isKaprekar6174(18604, DEBUG) = " << isKaprekar6174(18604, !DEBUG)
         << endl;
    isKaprekar6174(18604, DEBUG);
    cout << "isKaprekar6174(8888, DEBUG) = " << isKaprekar6174(8888, !DEBUG)
         << endl;
    isKaprekar6174(8888, DEBUG);
    cout << "isKaprekar6174(2894, DEBUG) = " << isKaprekar6174(2894, !DEBUG)
         << endl;
    isKaprekar6174(2894, DEBUG);
    cout << "isKaprekar6174(6174, DEBUG) = " << isKaprekar6174(6174, !DEBUG)
         << endl;
    isKaprekar6174(6174, DEBUG);

    cout << endl << "Task 5: " << endl;
    cout << "Statistic for range from 1000 to 9999" << endl;
    printStat(1000, 9999);
    cout << "Statistic for range from 500 to 10500" << endl;
    printStat(500, 10500);

    return 0;
}