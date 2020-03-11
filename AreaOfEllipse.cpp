#include <iomanip>
#include <iostream>

using namespace std;
bool isInside(long double x, long double y, double a, double b)
{
    return (x * x) / (a * a) + (y * y) / (b * b) < 1;
}
long long calculateGrid(double a, double b, double precision)
{
    long long numOfGrid = 0;
    int x = 0;
    for (x = (a / precision); x > 0; x--)
    {
        int start = 0, end = (b / precision);
        while (start < end)
        {
            int mid = start + (end - start) / 2;
            if (isInside(x * precision, mid * precision, a, b) &&
                !isInside((x)*precision, (mid + 1) * precision, a, b))
            {
                numOfGrid += mid;
                // cout << numOfGrid << endl;
                break;
            }
            else if (isInside(x * precision, (mid + 1) * precision, a, b))
            {
                start = mid + 1;
            }
            else if (!isInside(x * precision, mid * precision, a, b))
            {
                end = mid;
            }
        }
    }
    return 4 * numOfGrid;
}
long double calculateArea(long long numOfGrid, double precision)
{
    long double area = numOfGrid * precision * precision;
    return area;
}
int main()
{
    double precision = 0.0;
    double a, b;
    long double area;

    cout << "Enter the precision:" << endl;
    cin >> precision;
    cout << "Enter the 'a' and 'b' of ellipse" << endl;
    cin >> a >> b;
    area = calculateArea(calculateGrid(a, b, precision), precision);
    cout.precision(10);
    cout << (long double)area << endl;
    return 0;
}