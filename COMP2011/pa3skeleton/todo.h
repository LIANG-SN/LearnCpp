//do NOT modify this file
//do NOT submit this file

//given the csv header line (i.e., first row), return the number of dates
int getDateCount(char* headerLine);

//given the csv header line (i.e., first row), return an array of dates which are stored in the order of their appearances, as a dynamic array of dynamic char arrays 
//remember all char arrays should be null-terminated
char** getDates(char *headerLine);

//given the dates array and the date count, return the day
//first date in the array is considered as day 1, and so on
//return 0 if the given date is not in the dates array
//note: this is actually not used in other tasks; it is by itself a separated test
//hint: you may use strcmp (see online documentation of it)
int getDay(char** dates, int dateCount, const char *date);

//given the csv lines (header row included) and the number of those
//return the dynamic array of places
//each of the place should have a linked list of dated numbers (i.e. you need to fill in day and number to each node)
//skip all days with 0 numbers (to reduce the use of memory, since there can be a lot of zeros)
//for the "day" integer in a linked list node, the first date in the header: "1/22/20" is considered as day 1, and the second date "1/23/20" is considered as day 2, etc. 
//read the sample output and see what it means
//hint: the library function atoi may be useful for converting c-string to an integer, you may look for its online documentation
Place* getPlaces(char** csvLines, int csvLineCount);

//given the places array and the number of places,
//remove all provinces (deallocate all province character arrays, and set all province pointers to nullptr)
//merge all places (of any province) in the same region, to one single place
//by merging, it means, all numbers are added up for the same day
//therefore, the resulting new places array (will be given back via the places reference variable) is essentially a list of whole regions
//see sample output for examples
//the function returns the number of places in the new array
//note that the old array (likely bigger than the new array) shall be deallocated
//the last parameter "home" denotes the province that you have special interest in
//please see the webpage description for this part 
int mergeAllProvinces(Place*& places, int placeCount, const char *home = "Hong Kong");

//given the places array and the number of places
//give back a new places array and count (via the places reference variable and placeCount reference variable)
//the new places array is normalized in this sense:
//we consider the day with confirmed-cases number that is equal to or larger than "threshold", as day 1
//remove all nodes before day 1
//as a result, the day 1 node shall be the new head node
//the node after the day 1 node are day 2 node, day 3 node, and so on
//study samples for details
void normalizeDays(Place*& places, int& placeCount, int threshold);

//given the places, the count of places, and n
//change the numbers of each day of the places to n-day growth
//for example, if a place has these numbers in day 1 to day 6:
//16,18,20,22,22,24
//and n is 3
//that means the numbers will be changed to [number of today] - [number of 3-days ago]
//so the numbers shall become
//16,18,20,6,4,4
//note that for the first 3 days, the numbers remain unchanged because there is no "3-days ago" for them
//study samples for more examples
void changeToNDayGrowth(Place* places, int placeCount, int n);

//write the given places to a csv file, just like the sample output
void writeCSV(const char* csvFileName, Place* places, int placeCount);

//deallocate all the csv lines given the array and count of lines
//hint: the given array is a dynamic array of dynamic arrays, deallocate them all
//hint: remember that you must use [] to deallocate a dynamic array
void deallocateCSVLines(char** csvLines, int csvLineCount);

//deallocate the dates array given the array and the count of dates
void deallocateDates(char** dates, int dateCount);

//deallocate all linked list nodes given the head node
void deallocateLinkedList(Node* headNode);

//deallocate the whole places array given the pointer to it and the count of places
//note that you should also deallocate all dynamic char arrays (i.e. the country and province) and the linked list in each place
void deallocatePlaces(Place* places, int placeCount);
