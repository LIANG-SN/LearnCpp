/*
 * COMP2011 Spring 2020
 * Lab 9: Clustering
 */

#include <iostream>
using namespace std;

struct Point
{
    double x;
    double y;
    double z;
};
const int LARGE_NUM = 66666666;
/*******************************************************************************
 * The functions we provided
 *******************************************************************************/

/*generate test case*/
void generate_point(Point pts[], int size);

/*get the distance of p1 and p2*/
double get_distance(Point p1, Point p2);

/*output the points in pts*/
void output_point(Point p);

/*output point array*/
void output_points(Point pts[], int size);

/*******************************************************************************
 * The functions you need to implement
 *******************************************************************************/

/*query the closest point*/
Point get_closest_point(Point pts[], Point p, int size);

/*
 * merge closest pair of points n times, update the pts array and size
 * In the task, n = size - 3 in each invocation of this function
 */
void merge_multiple(Point pts[], int &size, int n);

/* Compute mean of point array and return the mean point */
Point mean_all_points(Point pts[], int size);
/*******************************************************************************
 * Helper Function
 * Remark: You might need to define the helper function for convenience
 ********************************************************************************/
/*Compute mean of two points, update point a with the result*/
Point mean_point(const Point &a, const Point &b);

/*merge closest pair of points, update the pts array and size*/
void merge_single(Point pts[], int &size);

/*merge a pair of points*/
void merge_point(Point pts[], int &size, int pid1, int pid2);
/*******************************************************************************
 * Implementation: These function might help you
 ********************************************************************************/

void generate_point(Point pts[], int size)
{
    double x = 3, y = 8, z = 2;
    for (int i = 0; i < size; i++, x *= 1.9, y *= 0.9, z *= 1.1)
    {
        pts[i].x = x;
        pts[i].y = y;
        pts[i].z = z;
    }
}

double get_distance(Point p1, Point p2)
{
    double distance = 0;
    distance += (p1.x - p2.x) * (p1.x - p2.x);
    distance += (p1.y - p2.y) * (p1.y - p2.y);
    distance += (p1.z - p2.z) * (p1.z - p2.z);
    return distance;
}

void output_point(Point p) { cout << p.x << " " << p.y << " " << p.z << endl; }

void output_points(Point pts[], int size)
{
    for (int i = 0; i < size; i++)
    {
        output_point(pts[i]);
    }
}

/*******************************************************************************
 *  Implementation: Define your function here
 *******************************************************************************/

Point get_closest_point(Point pts[], Point p, int size)
{
    int temp = LARGE_NUM;
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (temp > get_distance(pts[i], p) && get_distance(pts[i], p) != 0)
        {
            temp = get_distance(pts[i], p);
            index = i;
        }
    }
    return pts[index];
}
int get_closest_point_index(Point pts[], Point p, int size)
{
    int temp = LARGE_NUM;
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        if (temp > get_distance(pts[i], p) && get_distance(pts[i], p) != 0)
        {
            temp = get_distance(pts[i], p);
            index = i;
        }
    }
    return index;
}
Point mean_point(const Point &a, const Point &b)
{
    Point temp = {(a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2};
    return temp;
}

Point mean_all_points(Point pts[], int size)
{
    double x = 0, y = 0, z = 0;
    for (int i = 0; i < size; i++)
    {
        x += pts[i].x;
        y += pts[i].y;
        z += pts[i].z;
    }
    Point temp = {x / size, y / size, z / size};
    return temp;
}

void merge_point(Point pts[], int &size, int pid1, int pid2)
{
    pts[pid1] = mean_point(pts[pid1], pts[pid2]);
    for (int i = pid2; i < size - 1; i++)
        pts[i] = pts[i + 1];
    size--;
}

void merge_single(Point pts[], int &size)
{
    int distance = LARGE_NUM;
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        Point temp = get_closest_point(pts, pts[i], size);
        if (get_distance(pts[i], temp) < distance && get_distance(pts[i], temp) != 0)
        {
            distance = get_distance(pts[i], temp);
            index = i;
        }
    }
    merge_point(pts, size, index, get_closest_point_index(pts, pts[index], size));
}

void merge_multiple(Point pts[], int &size, int n)
{
    for (int i = 0; i < n; i++)
        merge_single(pts, size);
}

/*******************************************************************************
 *  Implementation: Define the entry of the program
 ********************************************************************************/
int main()
{
    int size;
    Point p;

    cout << "Please input the number of the points to generate" << endl;
    cin >> size;

    Point *pts = new Point[size];
    generate_point(pts, size);

    cout << size << " points have been generated successfully" << endl;
    output_points(pts, size);
    cout << endl;

    /*Task 1: Find the closest point*/
    cout << "Task 1: Find the closest point" << endl;
    cout << "Input your 3D point" << endl;
    cin >> p.x >> p.y >> p.z;
    Point q = get_closest_point(pts, p, size);
    cout << "The closest point is " << endl;
    output_point(q);
    cout << endl;

    /*Task 2: merge closest points*/
    cout << "Task 2: merge closest points" << endl;
    int merge_num = size - 3;
    merge_multiple(pts, size, merge_num);
    cout << "The remaining points are " << endl;
    output_points(pts, size);
    cout << endl;

    Point mean = mean_all_points(pts, 3);
    cout << "The mean point of remaining points is " << endl;
    output_point(mean);
    cout << endl;

    delete (pts);

    return 0;
}