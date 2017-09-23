#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

struct Point
{
public:
    int x, y;
    Point(int, int);
    double dist(Point);
};

#endif // POINT_H
