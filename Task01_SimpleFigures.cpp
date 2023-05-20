#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Abstract base class Shape.
class Shape {
public:
    // Pure virtual functions to be implemented by derived classes.
    virtual void Move(double tx, double ty) = 0; // translation.
    virtual void Rotate(double rt, double rx, double ry) = 0; // rotation about point (x,y).
    virtual void Print() = 0; // print information.
};

// Derived class Point, a point in a 2D plane.
class Point : public Shape {
private:
    double mx, my; // coordinates of the Point.

public:
    // Constructor to initialize the point with coordinates (x, y).
    Point(double x, double y) : mx(x), my(y) {}

    // Getter functions.
    double GetX() const {
        return mx;
    }

    double GetY() const {
        return my;
    }

    // Move the point by translation values (tx, ty).
    void Move(double tx, double ty) override {
        mx += tx;
        my += ty;
    }

    // Rotate the point by an angle (rt) about a point (rx, ry).
    void Rotate(double rt, double rx, double ry) override {
        double dx = mx - rx;
        double dy = my - ry;
        double cn = cos(rt);
        double sn = sin(rt);

        // Apply rotation transformation and round off to integers
        mx = round((dx * cn) - (dy * sn) + rx);
        my = round((dx * sn) + (dy * cn) + ry);
    }

    // Print the coordinates of the point
    void Print() override {
        cout << "Point at (" << mx << ", " << my << ")" << endl;
    }
};

// Derived class Line, a line segment between two points.
class Line : public Shape {
private:
    Point ms, me; // starting and ending points of the line.

public:
    // Constructor to initialize with starting point (sx, sy) and ending point (ex, ey).
    Line(double sx, double sy, double ex, double ey) : ms(sx, sy), me(ex, ey) {}

    // Midpoint.
    Point GetMidpoint() {
        double midX = (ms.GetX() + me.GetX()) / 2;
        double midY = (ms.GetY() + me.GetY()) / 2;
        return Point(midX, midY);
    }

    // Move by translation values (tx, ty).
    void Move(double tx, double ty) override {
        // Move both points together to shift the line
        ms.Move(tx, ty);
        me.Move(tx, ty);
    }

    // Rotate an angle (rt) about a point (rx, ry).
    void Rotate(double rt, double rx, double ry) override {
        // Rotate both points.
        ms.Rotate(rt, rx, ry);
        me.Rotate(rt, rx, ry);
    }

    // Print the line's starting and ending points
    void Print() override {
        cout << "Line with points:" << endl;
        cout << "Starting ";
        ms.Print();
        cout << "Ending ";
        me.Print();
    }
};

// Derived class Circle, a circle with a center and radius
class Circle : public Shape {
private:
    Point mc; // center point.
    double mr; // radius.

public:
    // Constructor to initialize the circle with center point (cx, cy) and radius (cr).
    Circle(double cx, double cy, double cr) : mc(cx, cy), mr(cr) {}

    // Move translation values (tx, ty).
    void Move(double tx, double ty) override {
        mc.Move(tx, ty);
    }

    // Rotate an angle (rt) about a point (rx, ry).
    void Rotate(double rt, double rx, double ry) override {
        mc.Rotate(rt, rx, ry);
    }

    // Print the circle's radius and center point.
    void Print() override {
        cout << "Circle of radius " << mr << " with center ";
        mc.Print();
    }
};

// Derived class Aggregate, an aggregate of multiple shapes.
class Aggregate : public Shape {
private:
    vector<Shape*> ma; // vector to store shapes.

public:
    // Add a shape to the aggregate
    void AddShape(Shape* ns) {
        ma.push_back(ns);
    }

    // Move the entire aggregate by translation values (tx, ty)
    void Move(double tx, double ty) override {
        // Move each shape in the aggregate
        for (Shape* s : ma) {
            s->Move(tx, ty);
        }
    }

    // Rotate the entire aggregate by an angle (rt) about a point (rx, ry).
    void Rotate(double rt, double rx, double ry) override {
        // Rotate each shape in the aggregate
        for (Shape* s : ma) {
            s->Rotate(rt, rx, ry);
        }
    }

    // Print all shapes in the aggregate
    void Print() override {
        cout << "Aggregate of shapes:" << endl;
        for (Shape* s : ma) {
            s->Print();
        }
    }
};

int main() {
    // An instance of Point class
    Point p1(4, 10); // point at (4, 10)
    p1.Print();
    p1.Move(0, 1);
    p1.Print();
    p1.Rotate(-M_PI / 2, 0, 0);
    p1.Print();
    p1.Rotate(M_PI / 4, 0, 0);
    p1.Print();

    p1.Rotate(M_PI, p1.GetX(), p1.GetY());
    p1.Print();

    // Create an instance of Line class
    Line l1(0, 0, 1, 1);
    l1.Move(1, 0);
    l1.Print();

    l1.Move(-1, 0);
    l1.Print();

    Point l1mp = l1.GetMidpoint();
    l1.Rotate(M_PI, l1mp.GetX(), l1mp.GetY());
    l1.Print();

    // Create an instance of Circle class
    Circle c1(1, 1, 1);
    c1.Print();
    c1.Move(-2, -2);
    c1.Print();

    c1.Rotate(M_PI, 0, 0);
    c1.Print();

    // Create an instance of Aggregate class
    Aggregate a1;
    a1.AddShape(new Point(1, 2));
    a1.AddShape(new Circle(1, 1, 1));
    a1.AddShape(new Line(1, 1, 2, 2));
    a1.Print();

    a1.Move(1, 1);
    a1.Print();
    a1.Move(-1, -1);
    a1.Print();

    a1.Rotate(M_PI, 0, 0);
    a1.Print();

    return 0;
}
