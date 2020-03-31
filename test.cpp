#include <math.h>

#include <iostream>
using namespace std;

double G(int t);
double S(int t);
int A(int t)
{
    int A[] = {200,
               214,
               211,
               228,
               235,
               232,
               248,
               250,
               253,
               267,
               281,
               275,
               280,
               288,
               310};
    return A[t - 1];
}
double S(int t)
{
    double temp;
    if (t == 4)
        temp = 228;
    else
        temp = 0.3 * A(t) + 0.7 * (S(t - 1) + G(t - 1));
    //cout << "S(" << t << ") = " << "0.3 * " << A(t) << " + " << endl;
    return temp;
}
double G(int t)
{
    if (t == 4)
        return 9.33;
    else
        return 0.2 * (S(t) - S(t - 1)) + 0.8 * G(t - 1);
}

int main()
{
    
    for(int i = 5 ; i < 16 ; i++)
    {
        cout << "S(" << i << ") = " << S(i) << endl;
        cout << "G(" << i << ") = " << G(i) << endl;
    }
    cout << "F(16) = S(15) + S (15) = " << S(15) + G(15) << endl;
    return 0;
}