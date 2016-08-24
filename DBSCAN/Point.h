#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct Point
{
    bool visited = false;
    int type = 0;   //1������ĵ�
    int cluster = -1;   //-1����δ����0������������������ص����
    int x;
    int y;

    Point() = default;
    Point(const Point &) = default;
    Point(int px, int py) : x(px), y(py) {}
    Point& operator=(const Point &) = default;
    ~Point() = default;

    int distance(const Point &pt);
};

#endif // POINT_H_INCLUDED
