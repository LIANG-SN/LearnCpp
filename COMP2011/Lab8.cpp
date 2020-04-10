/**
 * @file Lab8.cpp
 * @author Liang Shengnan sliangal@connect.ust.hk
 * @brief File input/output
 * @version 0.1
 * @date 2020-04-09
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <fstream>
#include <iostream>
using namespace std;

const int MAX_COURSES = 10;

bool isEmpty(char name[], string n)
{
    if (name[0] == '\0')
    {
        cout << n << " cannot be empty!" << endl;
        return true;
    }
    else
        return false;
}
void addCourse(char name[], char course[])
{
    cout << "Adding course: " << course << endl;
    string buffer[MAX_COURSES];
    ifstream ifs(name);
    if (!ifs)
    {
        cout << "first course of " << name << endl;
        ofstream ofs(name);
        ofs << course;
        ofs.close();
    }
    else
    {
        bool newCourse = true;
        int count = 0;
        while (!ifs.eof())
        {
            char tempCourse[20];
            ifs.getline(tempCourse, sizeof(tempCourse));
            if (tempCourse[0] == '\0')
                continue;
            buffer[count] = tempCourse;
            if (buffer[count] == course)
                newCourse = false;
            count++;
        }
        if (newCourse)
        {
            buffer[count] = course;
        }
        else
            cout << "this course has already been enrolled" << endl;
        ofstream ofs(name);
        for (int i = 0; i <= count; i++)
            ofs << buffer[i] << "\n";
        ofs.close();
    }
    ifs.close();
}

void dropCourse(char name[], char course[])
{
    ifstream ifs(name);
    if (!ifs)
    {
        cout << "drop failed, cannot find student named " << name << endl;
    }
    else
    {
        cout << "Dropping course: " << course << endl;
        string buffer[MAX_COURSES];
        bool hasEnrolled = false;
        int count = 0;
        while (!ifs.eof())
        {
            char tempCourse[20];
            ifs.getline(tempCourse, sizeof(tempCourse));
            if (tempCourse[0] == '\0')
                continue;
            buffer[count] = tempCourse;
            if (buffer[count] == course)
            {
                hasEnrolled = true;
                continue;
            }
            count++;
        }
        if (!hasEnrolled)
        {
            cout << name << " haven't enrll this course." << endl;
        }
        else
        {
        }
        ofstream ofs(name);
        for (int i = 0; i <= count - 1; i++)
            ofs << buffer[i] << endl;
        ofs.close();
    }
    ifs.close();
}

void listCourse(char name[])
{
    ifstream ifs(name);
    if (!ifs)
    {
        cout << "list failed, cannot find student named " << name << endl;
    }
    else
    {
        cout << "listing the course of " << name << endl;
        while (!ifs.eof())
        {
            char temp[20];
            ifs.getline(temp, sizeof(temp));
            if (temp[0] == '\0')
                continue;
            cout << temp << endl;
        }
    }
    ifs.close();
}

int main()
{
    char action;
    char name[20];
    char course[20];

    while (true)
    {
        cout << "----------------------" << endl;
        cout << "Add-Drop course start!" << endl;
        cout << "A for add; D for drop; L for list; Q for quit:" << endl;

        cin >> action;
        cin.get();

        if (action == 'A')
        {
            cout << "Please enter student name: " << endl;
            cin.getline(name, sizeof(name));
            if (isEmpty(name, "name"))
                continue;
            cout << "Please enter the course you want to add: " << endl;
            cin.getline(course, sizeof(course));
            if (isEmpty(course, "course"))
                continue;

            addCourse(name, course);
        }
        else if (action == 'D')
        {
            cout << "Please enter student name: " << endl;
            cin.getline(name, sizeof(name));
            if (isEmpty(name, "name"))
                continue;
            cout << "Please enter the course you want to add: " << endl;
            cin.getline(course, sizeof(course));
            if (isEmpty(course, "course"))
                continue;

            dropCourse(name, course);
        }
        else if (action == 'L')
        {
            cout << "Please enter student name: " << endl;
            cin.getline(name, sizeof(name));
            if (isEmpty(name, "name"))
                continue;

            listCourse(name);
        }
        else if (action == 'Q')
        {
            cout << "Quit..." << endl;
            break;
        }
        else
        {
            cout << "Input Invalid, please input again" << endl;
        }
    }

    return 0;
}