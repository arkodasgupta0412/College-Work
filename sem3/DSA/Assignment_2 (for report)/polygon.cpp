#include <iostream>
#include <cmath>
#include <optional>

using namespace std;
const double EPSILON = 1e-6;

bool areEqual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return areEqual(x, other.x) && areEqual(y, other.y);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

class Line {
public:
    double a, b, c;

    Line(const Point& p1, const Point& p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p1.x * p2.y;
    }

    bool contains(const Point& p) const {
        return areEqual(a * p.x + b * p.y + c, 0);
    }

    std::optional<Point> intersection(const Line& other) const {
        double determinant = a * other.b - other.a * b;
        if (areEqual(determinant, 0)) {
            return std::nullopt;
        }
        double x = (b * other.c - other.b * c) / determinant;
        double y = (other.a * c - a * other.c) / determinant;
        return Point(x, y);
    }

    void print() const {
        std::cout << a << "x + " << b << "y + " << c << " = 0";
    }
};

class LineSegment {
public:
    Point p1, p2;

    LineSegment(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}

    bool contains(const Point& p) const {
        Line line(p1, p2);

        if (!line.contains(p)) {
            return false;
        }

        return (min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x)) &&
               (min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y));
    }

    std::optional<Point> intersection(const LineSegment& other) const {
        Line line1(p1, p2);
        Line line2(other.p1, other.p2);

        auto inter = line1.intersection(line2);

        if (!inter) {
            return std::nullopt;
        }

        Point p = *inter;
        if (contains(p) && other.contains(p)) {
            return p;
        }
        return std::nullopt;
    }

    void print() const {
        std::cout << "Segment[";
        p1.print();
        std::cout << " - ";
        p2.print();
        std::cout << "]";
    }
};

int main() {
    // Example usage:
    Point p1(0, 0), p2(4, 4), p3(0, 4), p4(4, 0);
    Line line(p1, p2);
    LineSegment segment(p1, p2);

    std::cout << "Line: ";
    line.print();
    std::cout << "\n";

    std::cout << "Segment: ";
    segment.print();
    std::cout << "\n";

    // Check if a point is on the line
    Point testPoint(2, 2);
    std::cout << "Point ";
    testPoint.print();
    std::cout << (line.contains(testPoint) ? " lies on the line.\n" : " does not lie on the line.\n");

    // Check if a point is on the segment
    std::cout << "Point ";
    testPoint.print();
    std::cout << (segment.contains(testPoint) ? " lies on the segment.\n" : " does not lie on the segment.\n");

    // Find intersection of two lines
    Line otherLine(p3, p4);
    auto intersectionPoint = line.intersection(otherLine);
    if (intersectionPoint) {
        std::cout << "Intersection of lines: ";
        intersectionPoint->print();
        std::cout << "\n";
    } else {
        std::cout << "Lines do not intersect.\n";
    }

    // Find intersection of two line segments
    LineSegment otherSegment(p3, p4);
    auto segmentIntersection = segment.intersection(otherSegment);
    if (segmentIntersection) {
        std::cout << "Intersection of segments: ";
        segmentIntersection->print();
        std::cout << "\n";
    } else {
        std::cout << "Segments do not intersect.\n";
    }

    return 0;
}
