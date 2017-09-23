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

struct Point{
    double x, y;
    Point(){}
    Point(double _x, double _y): x(_x), y(_y) {}
    double dist(Point p){
        return hypot(p.x - x, p.y - y );
    }
};

#endif // POINT_H
