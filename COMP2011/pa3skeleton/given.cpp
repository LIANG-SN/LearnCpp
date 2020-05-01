//do NOT modify this file
//do NOT submit this file

#include "given.h"

char* substring(char* source, int startIndex, int endIndex)
{
    int size = endIndex - startIndex + 1;
    char* s = new char[size+1];
    strncpy(s, source + startIndex, size); //you can read the documentation of strncpy online
    s[size]  = '\0'; //make it null-terminated
    return s;
}


char** readCSV(const char* csvFileName, int& csvLineCount)
{
    ifstream fin(csvFileName);
    if (!fin)
    {
        return nullptr;
    }
    csvLineCount = 0;
    char line[1024];
    while(fin.getline(line, 1024))
    {
        csvLineCount++;
    };
    char **lines = new char*[csvLineCount];
    fin.clear();
    fin.seekg(0, ios::beg);
    for (int i=0; i<csvLineCount; i++)
    {
        fin.getline(line, 1024);

        //it is unfortunate that this online data is not very consistent 
        //there is a line with "Korea, South" as the "Country/Region" name in the file
        //it causes problems as it contains a comma
        //therefore, we are replacing it with "South Korea" instead, so that the students don't have to deal with it
        if(strstr(line, "Korea, South") != nullptr)
        {
            char* laterPart = substring(line, 15, strlen(line)-1); 
            lines[i] = new char[strlen(laterPart)+12+1];
            strcpy(lines[i], ",South Korea");
            strcat(lines[i], laterPart);
            delete [] laterPart;
        }
        else if(strstr(line, "Bonaire, Sint Eustatius and Saba") != nullptr) //similarly, there is another entry with this problem
        {
            char* laterPart = substring(line, 34, strlen(line)-1); 
            lines[i] = new char[strlen(laterPart)+35+1];
            strcpy(lines[i], "Bonaire and Sint Eustatius and Saba");
            strcat(lines[i], laterPart);
            delete [] laterPart;
        }
        else
        {
            lines[i] = new char[strlen(line)+1];
            strcpy(lines[i], line);
        }
    };
    fin.close();
    return lines;
}

void printPlaces(Place* regions, int regionCount)
{
    for(int i=0; i<regionCount; i++)
    {
        cout << "Region " << i << " (";
        if(regions[i].region && !regions[i].province)
            cout <<  regions[i].region << ")" << endl;
        else if(regions[i].region && regions[i].province)
        {
            cout <<  regions[i].region << "'s " << regions[i].province << ")" << endl;
        }
        else 
        {
            cout << "ERROR!" << endl; //country shouldn't be nullptr!
        }
        Node* cur = regions[i].headNode;
        while(cur)
        {
            cout <<"Day " <<  setw(3) << cur->day << ": " << cur->number << endl;
            cur = cur->next;
        }
        cout << endl;
    }
}