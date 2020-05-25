//do NOT modify this file
//do NOT submit this file

#include "todo.h"
using namespace std;

int main()
{
    cout << "Hi COVID-19 Outbreak Data Analyst 2.0!" << endl << endl;
    cout << "=======================================================" << endl;
    
    Region *regions;
    int nRegions = 0;
    cout << "Reading the CSV file..." << endl;
    //const char* csvFileName = "pa4_data_short.csv";
    const char* csvFileName = "pa4_data.csv";

    nRegions = readcsv(regions, csvFileName);
    
    cout << "=======================================================" << endl;
    cout << "Processing data.." << endl;

    for(int i = 0; i < nRegions; ++i){
        //normalize by population:
        regions[i].normalizeByPopulation();
        //normalize by area:
        regions[i].normalizeByArea();
        //compute mortality rate:
        regions[i].computeMortalityRate();
    }
    
    cout << "=======================================================" << endl;
    cout << "Writing to csvs..." << endl;
    writecsvs(regions, nRegions);

    cout << "=======================================================" << endl;
    cout << "Performing deallocations..." << endl;
    delete [] regions;

    cout << "=======================================================" << endl;
    cout << "Done! Please take care and stay healthy! :)" << endl;
    return 0;
}
