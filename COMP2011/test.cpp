#include <math.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

// main function
int main()
{
    ofstream ofs("output");
    ofs << "hello" << endl;
    ofs << "lol";
    ofs.close();
    return 0;
}
