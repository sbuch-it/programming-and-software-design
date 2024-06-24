#include <stdio.h> // standard input-output header

// representation of a point with a structure
struct Point {
    float x; // x coordinate of a point
    float y; // y coordinate of a point
};

Point InitByCopy(float x, float y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

void InitByAddress(float x, float y, Point* p) {
    p->x = x;
    p->y = y;
}

int main() {
    Point p1 = InitByCopy(3.0f, 3.0f);
    printf("Initialize by copy: %f %f \n", p1.x, p1.y);

    Point p2;
    InitByAddress(3.0f, 3.0f, &p2);
    printf("Initialize by address: %f %f \n", p2.x, p2.y);
    
    return 0;
}