#include "todo.h"
using namespace std;
//******** Helper functions ******* //

char *substring(char *source, int startIndex, int endIndex)
{
    int size = endIndex - startIndex + 1;
    char *s = new char[size + 1];
    strncpy(s, source + startIndex, size);  // you can read the documentation of strncpy online
    s[size] = '\0';                         // make it null-terminated
    return s;
}
/**
 * @brief Helper function, get the index of next comma
 *
 * @param line
 * @param start
 * @return int not found if return -99
 */
int getNextComma(char *line, int start)
{
    int index = -99;
    for (int i = start; line[i] != '\0'; i++)
    {
        if (line[i] == ',')
        {
            index = i;
            break;
        }
    }
    return index;
}
bool getNextSubstring(char *line, char *&subExtern, int start)
{
    int end = 0;
    bool notEnd = true;
    if (getNextComma(line, start) != -99)
    {
        end = getNextComma(line, start) - 1;
    }
    else
    {
        end = strlen(line);
        notEnd = false;
    }
    subExtern = substring(line, start, end);
    return notEnd;
}
int getDateCount(char *line)
{
    const int extraComma = 1;
    int commaCount = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ',')
            commaCount++;
    }
    return (commaCount - extraComma) / 2;
}

//******** IMPLEMENTATION OF DayStat ******* //

DayStat::DayStat()
{
    this->cases = 0;
    this->deaths = 0;
}

DayStat::DayStat(int _cases, int _deaths)
{
    this->cases = _cases;
    this->deaths = _deaths;
}

DayStat::DayStat(const DayStat &d, double denominator)
{
    this->cases = d.getcases() / denominator;
    this->deaths = d.getdeaths() / denominator;
}

double DayStat::mortalityRate() const
{
    if (this->cases == 0)
        return 0;
    else
        return this->deaths / this->cases * 100;
}

double DayStat::getcases() const { return this->cases; }

double DayStat::getdeaths() const { return this->deaths; }

//******** IMPLEMENTATION OF Region *******
Region::Region()
{
    this->raw = nullptr;
    this->mortality = nullptr;
    this->name = nullptr;
    this->population = 0;
    this->area = 0;
    this->nday = 0;
    this->normPop = nullptr;
    this->normArea = nullptr;
    this->mortality = nullptr;
}

void Region::readline(char *line)
{
    int start = 0;
    char *char2IntBuffer;

    this->nday = getDateCount(line);
    getNextSubstring(line, this->name, 0);
    start = getNextComma(line, start) + 1;

    getNextSubstring(line, char2IntBuffer, start);
    this->population = atoi(char2IntBuffer);
    delete[] char2IntBuffer;
    start = getNextComma(line, start) + 1;

    getNextSubstring(line, char2IntBuffer, start);
    this->area = atoi(char2IntBuffer);
    delete[] char2IntBuffer;
    start = getNextComma(line, start) + 1;

    this->raw = new DayStat[nday];
    for (int i = 0; i < nday; i++)
    {
        getNextSubstring(line, char2IntBuffer, start);
        double cases = atoi(char2IntBuffer);
        delete[] char2IntBuffer;
        start = getNextComma(line, start) + 1;
        getNextSubstring(line, char2IntBuffer, start);
        double deaths = atoi(char2IntBuffer);
        delete[] char2IntBuffer;
        start = getNextComma(line, start) + 1;
        this->raw[i] = DayStat(cases, deaths);
    }
}

Region::~Region()
{
    delete[] this->raw;
    delete[] this->mortality;
    delete[] this->name;
    delete[] this->normPop;
    delete[] this->normArea;
    this->raw = nullptr;
    this->mortality = nullptr;
    this->name = nullptr;
    this->normPop = nullptr;
    this->normArea = nullptr;
}

void Region::normalizeByPopulation()
{
    this->normPop = new DayStat[nday];
    for (int i = 0; i < this->nday; i++)
    {
        this->normPop[i] = DayStat(raw[i], (double)this->population / 1000000);
    }
}

void Region::normalizeByArea()
{
    this->normArea = new DayStat[nday];
    for (int i = 0; i < this->nday; i++)
    {
        this->normArea[i] = DayStat(raw[i], (double)this->area / 1000);
    }
}

void Region::computeMortalityRate()
{
    this->mortality = new double[nday];
    for (int i = 0; i < this->nday; i++)
    {
        this->mortality[i] = this->raw[i].mortalityRate();
    }
}

void Region::write(Stat stat) const
{
    string fileName;
    double *output = new double[this->nday];
    switch (stat)
    {
    case CASESRAW:
        fileName = "CASESRAW.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = raw[i].getcases();
        break;
    case DEATHSRAW:
        fileName = "DEATHSRAW.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = raw[i].getdeaths();
        break;
    case CASESPOP:
        fileName = "CASESPOP.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = normPop[i].getcases();
        break;
    case DEATHSPOP:
        fileName = "DEATHSPOP.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = normPop[i].getdeaths();
        break;
    case CASESAREA:
        fileName = "CASESAREA.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = normArea[i].getcases();
        break;
    case DEATHSAREA:
        fileName = "DEATHSAREA.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = normArea[i].getdeaths();
        break;
    case MORTALITY:
        fileName = "MORTALITY.csv";
        for (int i = 0; i < this->nday; i++)
            output[i] = mortality[i];
    }
    ofstream out(fileName, ios::app);
    out.precision(6);
    out.setf(ios_base::fixed);
    out << this->name;
    for (int i = 0; i < this->nday; i++)
        out << ',' << output[i];
    out << endl;
    out.close();
    delete[] output;
    output = nullptr;
}

//******** IMPLEMENTATION OF FILE I/O FUNCTIONS *******

int readcsv(Region *&region, const char *csvFileName)
{
    ifstream fin(csvFileName);
    if (!fin)
    {
        return 0;
    }
    int csvLineCount = 0;
    char line[2048];
    while (fin.getline(line, 2048))
    {
        csvLineCount++;
    };
    char **lines = new char *[csvLineCount];
    fin.clear();
    fin.seekg(0, ios::beg);
    for (int i = 0; i < csvLineCount; i++)
    {
        fin.getline(line, 2048);
        lines[i] = new char[strlen(line) + 1];
        strcpy(lines[i], line);
    };
    fin.close();

    region = new Region[csvLineCount - 1];
    for (int i = 0; i < csvLineCount - 1; i++)
    {
        region[i].readline(lines[i + 1]);
    }
    for (int i = 0; i < csvLineCount; i++)
        delete[] lines[i];
    delete[] lines;
    return csvLineCount - 1;
}

void writecsvs(const Region *region, int nRegions)
{
    for (int n = 0; n < nRegions; n++)
    {
        for (int i = 0; i < 7; i++)
            region[n].write((Stat)i);
    }
}
