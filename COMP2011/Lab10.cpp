#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// Provided print array function
void print_array(const int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << ' ';
    }
    cout << endl;
}

// Find missing number function
// You should return the missing number
int missing_number(const int *nums, int size)
{
    int realSum = 0, expSum = 0;
    for (int i = 0; i < size; i++)
        realSum += nums[i];
    for (int i = 0; i <= size; i++)
        expSum += i;
    return expSum - realSum;
}

// Generate the shuffled array missing one number
int *generate_array(int size)
{
    int *array = new int[size];
    int miss = rand() % size;
    for (int i = 0; i < size; i++)
    {
        if (i == miss)
            array[i] = size;
        else
            array[i] = i;
    }
    // shuffle
    for (int i = 0; i < size - 1; i++)
    {
        int randN = i + 1 + rand() % (size - 1 - i);
        int temp = array[randN];
        array[randN] = array[i];
        array[i] = temp;
    }
    return array;
}

// You should first generate array and then find the missing number
// You should free all allocated memory and return the missing number (which is used to
// determine the length of the array in the next iteration)
void solve(int size, int iter)
{
    int *array = nullptr;
    int missNum = 0;
    for (int i = 0; i < iter; i++)
    {
        size += missNum;
        array = generate_array(size);
        missNum = missing_number(array, size);
        cout << "This is iteration: " << i << endl << "-----------------" << endl;
        cout << "The array:" << endl;
        print_array(array, size);
        cout << "The missing number: " << missNum << endl;

        delete array;
        array = nullptr;
    }
}

int main()
{
    srand(time(0));
    int size = 0;
    int iter = 0;
    cout << "Please input the length of the array (between 2 and 100): " << endl;
    cin >> size;

    cout << "Please input the total number of iterations (between 1 and 5): " << endl;
    cin >> iter;
    solve(size, iter);

    return 0;
}
