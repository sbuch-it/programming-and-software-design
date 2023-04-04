#include <stdio.h> // standard input-output header

struct Point {
    float x; // x coordinate of a point
    float y; // y coordinate of a point
};

void Center(Point& p1, Point& p2, Point* center) {
    center->x = (p1.x + p2.x) / 2.0f;
    center->y = (p1.y + p2.y) / 2.0f;
}

int main() {
    Point p1;
    p1.x = 0.3f;
    p1.y = 0.5f;

    Point p2;
    p2.x = 0.6f;
    p1.y = 0.4f;

    Point center;
    Center(p1, p2, &center);
    // p1 and p2 are passed by reference
    // &center is passed by address
    
    printf("%f %f\n", center.x, center.y);
    return 0;
}