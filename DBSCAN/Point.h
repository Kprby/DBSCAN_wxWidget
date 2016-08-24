#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct Point
{
    bool visited = false;
    int type = 0;   //1代表核心点
    int cluster = -1;   //-1代表未处理，0代表噪声，其他代表簇的序号
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
