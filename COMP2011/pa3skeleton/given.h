//do NOT modify this file
//do NOT submit this file
#include <iostream> 
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip> 
using namespace std;

//the following are the 2 structs we use in this assignment
//a node in a linked list
struct Node { 
    int day = 0; //day
    int number = 0; //number to be stored for the day
    Node* next = nullptr; //next node in the linked list; remember the last node should point to nullptr
};
//a place
struct Place {
    char* region = nullptr; //region/country, in dynamic char array (C-string)
    char* province = nullptr; //province/state, in dynamic char array (C-string)
    Node* headNode = nullptr; //head of the linked list of dated numbers; set to nullptr if there is no node (yet)
};


//given a source C-string, return the substring between the given indices (inclusively)
//for example, if source is "abcdef", and startIndex is 1, and endIndex is 3, then 
//it will return a new dynamic char array (C-string) of size 4 with content bcd\0
//note that the dynamic array shall be deallocated by yourself before the end of the program
//you may use it in various tasks if you want
char* substring(char* source, int startIndex, int endIndex);

//read the CSV given the file name and it will return the csv lines read
//it also gives back the csv line count with the reference variable csvLineCount
char** readCSV(const char* csvFileName, int& csvLineCount);

//print the places given the region array and the number of places
void printPlaces(Place* places, int placeCount);