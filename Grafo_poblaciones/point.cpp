#include "point.h"

Point::Point(int _x, int _y)
{
    x = _x;
    y = _y;
}

double Point::dist(Point p)
{
    return hypot(p.x - x, p.y - y );
}
