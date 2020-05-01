// submit this file ONLY
// if you need to write your own helper functions, write the functions in this file
// again, do NOT include additional libraries and make sure this todo.cpp can be compiled with
// the unmodified versions of the other given files in our official compilation environment

#include "given.h"

#include "todo.h"


int max(int a, int b) { return a > b ? a : b; }
void del(char *&array_ptr)
{
    delete[] array_ptr;
    array_ptr = nullptr;
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

// declare
void deallocatePlaces(Place *places, int placeCount);

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
            delete[] date;
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
            char *homeName = new char[length + 6 + 1];
            strcpy(homeName, home);
            strcat(homeName, "(Home)");
            newPlacesTemp[newPlaceCount - 1].region = homeName;
            newPlacesTemp[newPlaceCount - 1].headNode = places[i].headNode;
            del(places[i].province);
            del(places[i].region);
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
                        char *homeName = new char[length + 6 + 1];
                        strcpy(homeName, home);
                        strcat(homeName, "(Home)");
                        del(places[j].province);
                        del(places[j].region);
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
                        int *numbers = new int[maxday];
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
                        delete[] numbers;
                        del(places[j].province);
                        del(places[j].region);
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

void deallocateCSVLines(char **csvLines, int csvLineCount)
{
    for (int i = 0; i < csvLineCount; i++)
        delete[] csvLines[i];
    delete[] csvLines;
};

void deallocateDates(char **dates, int dateCount)
{
    for (int i = 0; i < dateCount; i++)
        delete[] dates[i];
    delete[] dates;
};

void deallocateLinkedList(Node *headNode) { deleteAllNodes(headNode); };

void deallocatePlaces(Place *places, int placeCount)
{
    for (int i = 0; i < placeCount; i++)
    {
        delete[] places[i].province;
        delete[] places[i].region;
        deallocateLinkedList(places[i].headNode);
    }
    delete[] places;
};
