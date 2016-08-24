#include "Point.h"
#include <cmath>

int Point::distance(const Point &pt)
{
    int dx, dy, r;
    dx = pt.x - x;
    dy = pt.y - y;
    r = sqrt(dx * dx + dy * dy);
    return r;
}
