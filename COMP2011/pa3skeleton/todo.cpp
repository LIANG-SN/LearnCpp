// submit this file ONLY
// if you need to write your own helper functions, write the functions in this file
// again, do NOT include additional libraries and make sure this todo.cpp can be compiled with
// the unmodified versions of the other given files in our official compilation environment

#include "given.h"
#include "todo.h"


using namespace std;
int max(int a, int b) { return a > b ? a : b; }
void del(char *&array)
{
    delete[] array;
    array = nullptr;
}
void deleteZero(Node *&head)
{
    Node *prev = nullptr;
    Node *current = head;
    // STEP 1: Find the item to be deleted
    while (current != nullptr)
    {
        if (current->number == 0)
        {
            if (current == head)  // Special case: delete the first item
            {
                head = head->next;
                current = current->next;
            }
            else
            {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        }
        else
        {
            prev = current;  // Advance both pointers
            current = current->next;
        }
    }
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
/**
 * @brief Helper function, get the index of Nth comma
 *
 * @param line
 * @param start
 * @param n
 * @return int return -99 if not found nth
 */
int getNthComma(char *line, int start, int n)
{
    if (getNextComma(line, start) == -99)
        return -99;
    else if (n == 1)
        return getNextComma(line, start);
    else
        return getNthComma(line, getNextComma(line, start) + 1, n - 1);
}
/**
 * @brief helper function, get next substring
 *
 * @param line
 * @param subExtern
 * @param start
 * @return true
 * @return false
 */
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

// linked list helper functions
Node *createNode(int day, int number)
{
    Node *p = new Node;
    p->day = day;
    p->number = number;
    p->next = nullptr;
    return p;
}
// special version
Node *createNodes(const int startDay, const int dayNum, const int numbers[])
{
    Node *head = createNode(startDay, numbers[startDay - 1]);
    Node *p = head;
    for (int day = startDay + 1; day <= dayNum; day++)
    {
        if (numbers[day - 1] == 0)
            continue;
        p->next = createNode(day, numbers[day - 1]);
        p = p->next;
    }
    return head;
}
void deleteAllNodes(Node *&head)
{
    if (head == nullptr)
        return;
    deleteAllNodes(head->next);
    delete head;
    head = nullptr;
}

// ======================== Helper functions end =========================== //

// ======================== Task functions start =========================== //

int getDateCount(char *headerLine)
{
    const int extraComma = 3;
    int commaCount = 0;
    for (int i = 0; headerLine[i] != '\0'; i++)
    {
        if (headerLine[i] == ',')
            commaCount++;
    }
    return commaCount - extraComma;
};

// given the csv header line (i.e., first row), return an array of dates which are stored in the
// order of their appearances, as a dynamic array of dynamic char arrays remember all char
// arrays should be null-terminated
char **getDates(char *headerLine)
{
    int dateCount = getDateCount(headerLine);
    char **dates = new char *[dateCount];
    int start = getNthComma(headerLine, 0, 4) + 1;
    int count = 0;
    while (getNextSubstring(headerLine, dates[count], start))
    {
        start = getNextComma(headerLine, start) + 1;
        count++;
    }
    return dates;
};

// given the dates array and the date count, return the day
// first date in the array is considered as day 1, and so on
// return 0 if the given date is not in the dates array
// note: this is actually not used in other tasks; it is by itself a separated test
// hint: you may use strcmp (see online documentation of it)
int getDay(char **dates, int dateCount, const char *date)
{
    int day = 0;
    for (int i = 0; i < dateCount; i++)
    {
        if (strcmp(dates[i], date) == 0)
            day = i + 1;
    }
    return day;
};

// given the csv lines (header row included) and the number of those
// return the dynamic array of places
// each of the place should have a linked list of dated numbers (i.e. you need to fill in day
// and number to each node) skip all days with 0 numbers (to reduce the use of memory, since
// there can be a lot of zeros) for the "day" integer in a linked list node, the first date in
// the header: "1/22/20" is considered as day 1, and the second date "1/23/20" is considered as
// day 2, etc. read the sample output and see what it means hint: the library function atoi may
// be useful for converting c-string to an integer, you may look for its online documentation
Place *getPlaces(char **csvLines, int csvLineCount)
{
    Place *places = new Place[csvLineCount - 1];
    for (int line = 1; line < csvLineCount; line++)
    {
        int start = 0;
        if (csvLines[line][0] == ',')
            start++;
        else
        {
            getNextSubstring(csvLines[line], places[line - 1].province, start);
            start = getNextComma(csvLines[line], start) + 1;
        }
        getNextSubstring(csvLines[line], places[line - 1].region, start);
        for (int move = 0; move < 3; move++)
            start = getNextComma(csvLines[line], start) + 1;
        int dayNum = getDateCount(csvLines[line]);
        int *numbers = new int[dayNum];
        for (int day = 0; day < dayNum; day++)
        {
            char *date;
            getNextSubstring(csvLines[line], date, start);
            numbers[day] = atoi(date);
            start = getNextComma(csvLines[line], start) + 1;
        }
        int startDay = 1;
        while (startDay <= dayNum && numbers[startDay - 1] == 0)
            startDay++;
        if (startDay <= dayNum)
            places[line - 1].headNode = createNodes(startDay, dayNum, numbers);
        delete[] numbers;
    }
    return places;
};

// given the places array and the number of places,
// remove all provinces (deallocate all province character arrays, and set all province pointers
// to nullptr) merge all places (of any province) in the same region, to one single place by
// merging, it means, all numbers are added up for the same day therefore, the resulting new
// places array (will be given back via the places reference variable) is essentially a list of
// whole regions see sample output for examples the function returns the number of places in the
// new array note that the old array (likely bigger than the new array) shall be deallocated the
// last parameter "home" denotes the province that you have special interest in please see the
// webpage description for this part
int mergeAllProvinces(Place *&places, int placeCount, const char *home)
{
    int newPlaceCount = 0;
    Place *newPlacesTemp = new Place[placeCount];
    for (int i = 0; i < placeCount; i++)
    {
        if (places[i].region == nullptr)
            continue;
        else if (places[i].province != nullptr && strcmp(places[i].province, home) == 0)
        {
            newPlaceCount++;

            int length = strlen(home);
            char *homeName = new char[length + 6];
            strcpy(homeName, home);
            strcat(homeName, "(Home)");
            newPlacesTemp[newPlaceCount - 1].region = homeName;
            newPlacesTemp[newPlaceCount - 1].headNode = places[i].headNode;
            delete[] places[i].region;
            places[i].region = nullptr;
            delete[] places[i].province;
            places[i].province = nullptr;
        }
        else
        {
            int thisPlaceCount = ++newPlaceCount;
            newPlacesTemp[newPlaceCount - 1].region = places[i].region;
            for (int j = i + 1; j < placeCount; j++)
            {
                if (places[j].region == nullptr)
                    continue;
                if (strcmp(places[i].region, places[j].region) == 0)
                {
                    if (places[j].province != nullptr && strcmp(places[j].province, home) == 0)
                    {
                        newPlaceCount++;

                        int length = strlen(home);
                        char *homeName = new char[length + 6];
                        strcpy(homeName, home);
                        strcat(homeName, "(Home)");
                        delete[] places[j].province;
                        places[j].province = nullptr;
                        delete[] places[j].region;
                        places[j].region = nullptr;
                        newPlacesTemp[newPlaceCount - 1].region = homeName;
                        newPlacesTemp[newPlaceCount - 1].headNode = places[j].headNode;
                    }
                    else
                    {
                        // make a new merged array
                        int maxday = 0;
                        for (Node *p = places[i].headNode; p != nullptr; p = p->next)
                            maxday = max(maxday, p->day);
                        for (Node *p = places[j].headNode; p != nullptr; p = p->next)
                            maxday = max(maxday, p->day);
                        int *numbers = new int[maxday - 1];
                        for (int i = 0; i < maxday; i++)
                            numbers[i] = 0;
                        for (Node *p = places[i].headNode; p != nullptr; p = p->next)
                            numbers[p->day - 1] += p->number;
                        for (Node *p = places[j].headNode; p != nullptr; p = p->next)
                            numbers[p->day - 1] += p->number;
                        // delete origin list
                        deleteAllNodes(places[i].headNode);
                        // make new list
                        int startDay = 1;
                        while (startDay <= maxday && numbers[startDay - 1] == 0)
                            startDay++;
                        if (startDay <= maxday)
                            places[i].headNode = createNodes(startDay, maxday, numbers);
                        delete[] places[j].province;
                        delete[] places[j].region;
                        places[j].province = nullptr;
                        places[j].region = nullptr;
                        deleteAllNodes(places[j].headNode);
                    }
                }
            }
            newPlacesTemp[thisPlaceCount - 1].headNode = places[i].headNode;
        }
        delete[] places[i].province;
        places[i].province = nullptr;
    }
    delete[] places;
    places = new Place[newPlaceCount];
    for (int i = 0; i < newPlaceCount; i++)
    {
        places[i] = newPlacesTemp[i];
    }
    delete[] newPlacesTemp;
    return newPlaceCount;
}

// given the places array and the number of places
// give back a new places array and count (via the places reference variable and placeCount
// reference variable) the new places array is normalized in this sense: we consider the day
// with confirmed-cases number that is equal to or larger than "threshold", as day 1 remove all
// nodes before day 1 as a result, the day 1 node shall be the new head node the node after the
// day 1 node are day 2 node, day 3 node, and so on study samples for details
void normalizeDays(Place *&places, int &placeCount, int threshold)
{
    for (int i = 0; i < placeCount; i++)
    {
        int dayT = 0;
        Node *p = places[i].headNode;
        while (p != nullptr)
        {
            if (dayT == 0 && p->number < threshold)
            {
                places[i].headNode = places[i].headNode->next;
                delete p;
                p = places[i].headNode;
            }
            else
            {
                p->day = ++dayT;
                p = p->next;
            }
        }
        if (places[i].headNode == nullptr)
        {
            del(places[i].province);
            del(places[i].region);
            for (int j = i; j < placeCount - 1; j++)
            {
                places[j] = places[j + 1];
            }
            placeCount--;
            i--;
        }
    }
};

// given the places, the count of places, and n
// change the numbers of each day of the places to n-day growth
// for example, if a place has these numbers in day 1 to day 6:
// 16,18,20,22,22,24
// and n is 3
// that means the numbers will be changed to [number of today] - [number of 3-days ago]
// so the numbers shall become
// 16,18,20,6,4,4
// note that for the first 3 days, the numbers remain unchanged because there is no "3-days ago"
// for them study samples for more examples
void changeToNDayGrowth(Place *places, int placeCount, int n)
{
    for (int i = 0; i < placeCount; i++)
    {
        int dayCount = 0;
        for (Node *p = places[i].headNode; p != nullptr; p = p->next)
            dayCount = p->day;
        int *temp = new int[dayCount];
        for (Node *p = places[i].headNode; p != nullptr; p = p->next)
            temp[p->day - 1] = p->number;
        for (Node *p = places[i].headNode; p != nullptr; p = p->next)
        {
            if (p->day <= n)
                continue;
            else
            {
                p->number -= temp[p->day - n - 1];
            }
        }
        delete[] temp;
        deleteZero(places[i].headNode);
    }
};

// write the given places to a csv file, just like the sample output
void writeCSV(const char *csvFileName, Place *places, int placeCount)
{
    ofstream output(csvFileName);
    for (int i = 0; i < placeCount; i++)
    {
        output << places[i].region;
        Node *p = places[i].headNode;
        while (p != nullptr)
        {
            output << "," << p->number;
            p = p->next;
        }
        output << endl;
    }
    output.close();
};

// deallocate all the csv lines given the array and count of lines
// hint: the given array is a dynamic array of dynamic arrays, deallocate them all
// hint: remember that you must use [] to deallocate a dynamic array
void deallocateCSVLines(char **csvLines, int csvLineCount)
{
    for (int i = 0; i < csvLineCount; i++)
        delete[] csvLines[i];
    delete [] csvLines;
};

// deallocate the dates array given the array and the count of dates
void deallocateDates(char **dates, int dateCount)
{
    for (int i = 0; i < dateCount; i++)
        delete[] dates[i];
    delete [] dates;
};

// deallocate all linked list nodes given the head node
void deallocateLinkedList(Node *headNode)
{
    deleteAllNodes(headNode);
};

// deallocate the whole places array given the pointer to it and the count of places
// note that you should also deallocate all dynamic char arrays (i.e. the country and province)
// and the linked list in each place
void deallocatePlaces(Place *places, int placeCount)
{
    for(int i =0; i< placeCount; i++)
    {
        delete [] places[i].province;
        delete [] places[i].region;
        deallocateLinkedList(places[i].headNode);
    }
        delete [] places;
};
