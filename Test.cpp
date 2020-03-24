#include <iostream>

using namespace std;
int main()
{
    double y[9] = {0};
    int x[9] = {0, 1, 1, 1, 0, 0, 0, 0, 0};
    for (int i = 1; i <= 8; i++)
    {
        y[i] = 0.8 * y[i - 1] + 0.17 * x[i];
        cout << "y" << i+1 << "=  " << y[i] << endl;
    }

}