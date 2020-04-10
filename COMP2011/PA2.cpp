/*
 * COMP2011 (Spring 2020) Assignment 2: "Recursion"
 *
 * Student name: Liang Shengnan
 * Student ID: 20677615
 * Student email: sliangal@connect.ust.hk
 *
 * Note:
 * - DO NOT change any of the function headers given.
 * - DO NOT use any loops.
 * - DO NOT use any global variables or add additional libraries.
 * - DO NOT use any static variables.
 * - You can add helper function(s) if needed.
 */

#include <iostream>

using namespace std;

// Constants

// NULL character. This is the last char of all C Strings
const char END = '\0';

// Single quotation character '
const char SQUOTE = '\'';

// Double quotation character "
const char DQUOTE = '\"';

// Error. Used in Task 2 and 3
const int ERROR = -1;

// For fun
const bool INTERESTING_VERSION = true;

// Practice Task: Task 0 (Not Graded)
unsigned int recursive_strlen(const char line[], int start)
{
    if (line[start] == END)
        return start;
    else
        return recursive_strlen(line, start + 1);
}

// Normal Task: Task 1
unsigned int count_dquotes(const char line[], int start)
{
    if (line[start] == END)
        return 0;
    if (line[start] == DQUOTE)
        return count_dquotes(line, start + 1) + 1;
    else
        return count_dquotes(line, start + 1);
}

// Normal Task: Task 2
int find_first_dquote(const char line[], int start)
{
    if (line[start] == END)
        return ERROR;
    if (line[start] == DQUOTE)
        return start;
    else
        return find_first_dquote(line, start + 1);
}

// Normal Task: Task 3
int count_chars_in_matched_dquote(const char line[], int start)
{
    if ((count_dquotes(line, 0) % 2) == 0)
    {
        if (find_first_dquote(line, start) != ERROR)
        {
            return count_chars_in_matched_dquote(
                       line, find_first_dquote(line, find_first_dquote(line, start) + 1) + 1) +
                   find_first_dquote(line, find_first_dquote(line, start) + 1) -
                   find_first_dquote(line, start) - 1;
        }
        else
            return 0;
    }
    else
        return ERROR;
}

// Challenging Task: Task 4
int find_first_squote(const char line[], int start)
{
    if (line[start] == END)
        return ERROR;
    if (line[start] == SQUOTE)
        return start;
    else
        return find_first_squote(line, start + 1);
}
bool check_quotes_matched(const char line[], int start)
{
    if (line[start] == END)
        return true;
    else if (line[start] == SQUOTE)
    {
        if (find_first_squote(line, start + 1) == ERROR)
            return false;
        else
            return check_quotes_matched(line, find_first_squote(line, start + 1) + 1);
    }
    else if (line[start] == DQUOTE)
    {
        if (find_first_dquote(line, start + 1) == ERROR)
            return false;
        else
            return check_quotes_matched(line, find_first_dquote(line, start + 1) + 1);
    }
    else
        return check_quotes_matched(line, start + 1);
}

// Challenging Task: Task 5

/**
 * @brief help function
 * @return the number of first consecutive double quotes
 *
 */
unsigned int count_first_consecutive_dquotes(const char line[], int first_dequote)
{
    if (first_dequote == ERROR)
        return 0;
    if (line[first_dequote + 1] == DQUOTE)
        return count_first_consecutive_dquotes(line, first_dequote + 1) + 1;
    else
        return 1;
}
/**
 * @brief original function
 * The variable `INTERSTING_VERSION` is just a switch for two styles.
 * Actually I wonder in which way will the program run faster, it help me to test.
 * But finally both of them run quite fast so I cannot compare.
 *
 */
unsigned int length_of_longest_consecutive_dquotes(const char line[], int start)
{
    if (line[start] == '\0' || find_first_dquote(line, start) == ERROR)
        return 0;
    else if (!INTERESTING_VERSION)
    {
        int curr = count_first_consecutive_dquotes(line, find_first_dquote(line, start));
        int next = length_of_longest_consecutive_dquotes(line, start + curr);
        return curr > next ? curr : next;
    }
    else
    {
        return (count_first_consecutive_dquotes(line, find_first_dquote(line, start)) >
                length_of_longest_consecutive_dquotes(
                    line, start + count_first_consecutive_dquotes(
                                      line, find_first_dquote(line, start))))
                   ? count_first_consecutive_dquotes(line, find_first_dquote(line, start))
                   : length_of_longest_consecutive_dquotes(
                         line, start + count_first_consecutive_dquotes(
                                           line, find_first_dquote(line, start)));
    }
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

const int MAX_LENGTH = 1000;

int main()
{
    int option = 0;
    char line[MAX_LENGTH];

    do
    {
        cout << "Options:" << endl;
        cout << "0:  Test recursive_strlen()" << endl;
        cout << "1:  Test count_dquotes()" << endl;
        cout << "2:  Test find_first_dquote()" << endl;
        cout << "3:  Test count_chars_in_matched_dquote()" << endl;
        cout << "4:  Test check_quotes_matched()" << endl;
        cout << "5:  Test length_of_longest_consecutive_dquotes()" << endl;
        cout << "-1: Quit" << endl;

        cin >> option;
        cin.ignore();

        switch (option)
        {
        case 0:
            cout << "Testing recursive_strlen()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << recursive_strlen(line, 0) << endl;
            break;

        case 1:
            cout << "Testing count_dquotes()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << count_dquotes(line, 0) << endl;
            break;

        case 2:
            cout << "Testing find_first_dquote()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << find_first_dquote(line, 0) << endl;
            break;

        case 3:
            cout << "Testing count_chars_in_matched_dquote()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << count_chars_in_matched_dquote(line, 0) << endl;
            break;

        case 4:
            cout << "Testing check_quotes_matched()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << check_quotes_matched(line, 0) << endl;
            break;

        case 5:
            cout << "Testing length_of_longest_consecutive_dquotes()" << endl;
            cout << "Enter line: ";
            cin.getline(line, MAX_LENGTH);
            cout << length_of_longest_consecutive_dquotes(line, 0) << endl;
            break;

        default:
            break;
        }

        cout << endl;

    } while (option != -1);

    return 0;
}