//do NOT modify this file
//do NOT submit this file
#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <iomanip>

enum Stat {CASESRAW, DEATHSRAW, CASESPOP, DEATHSPOP, CASESAREA, DEATHSAREA, MORTALITY};

class DayStat
{
private:
    double cases, deaths;
public:
    DayStat();
    DayStat(int _cases, int _deaths);
    DayStat(const DayStat &d, double denominator);
    double mortalityRate() const;
    double getcases() const;
    double getdeaths() const;
};

class Region
{
private:
    DayStat *raw;
    char *name;
    int population;
    int area;
    int nday;

    DayStat *normPop;
    DayStat *normArea;
    double *mortality;

public:
    Region();
    ~Region();
    void readline(char *line);
    void normalizeByPopulation();
    void normalizeByArea();
    void computeMortalityRate();
    void write(Stat stat) const;
};

int readcsv(Region*& region, const char* csvFileName);
void writecsvs(const Region* region, int nRegions);
