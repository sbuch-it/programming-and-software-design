#include <cstdio>

class Point {
 private:
    float x;
    float y;

 public:
    Point() {
        x = 0.0f;
        y = 0.0f;
    }
    Point(float x_, float y_) {
        x = x_;
        y = y_;
    }

    float GetX() {
        return x;
    }
    float GetY() {
        return y;
    }

    void Set(float x_, float y_) {
        x = x_;
        y = y_;
    }
};


class Rectangle {
 private:
    Point anchor;
    float width;
    float height;

 public:
    Rectangle() {
        width = 0.0f;
        height = 0.0f;
    }
    Rectangle(Point anchor_, float width_, float height_) {
        anchor = anchor_;
        width = width_;
        height = height_;
    }

    float GetWidth() {
        return width;
    }
    float GetHeight() {
        return height;
    }

    float Area() {
        return width * height;
    }
    float Perimeter() {
        return 2.0f * width + 2.0f * height;
    }

    Point CenterWithCopy() {
        Point center(anchor.GetX() + width * 0.5f, 
            anchor.GetY() + height * 0.5f);
        return center;
    }
    void CenterWithoutCopy(Point* center) {
        center->Set(anchor.GetX() + width * 0.5f, 
            anchor.GetY() + height * 0.5f);
    }
};


int main() {
    
    Point anchor_start(2.3f, 3.3f);
    Rectangle rect(anchor_start, 10.0f, 4.1f);

    const float area = rect.Area();
    printf("Area %f\n", area);

    const float perimeter = rect.Perimeter();
    printf("Perimeter %f\n", perimeter);

    Point center1 = rect.CenterWithCopy();
    printf("Center with copy (%f, %f) \n", 
        center1.GetX(), center1.GetY());

    Point center2;
    rect.CenterWithoutCopy(&center2);
    printf("Center without copy (%f, %f) \n", 
        center2.GetX(), center2.GetY());

    return 0;
}