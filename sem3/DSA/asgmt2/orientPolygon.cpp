#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
    double x, y;

public:
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double getX() const { return x; }
    double getY() const { return y; }
};

class Polygon
{
    vector<Point> lst;

public:
    vector<Point> &getPoly() { return lst; }

    void printPoly()
    {
        for (Point &p : lst)
        {
            cout << "(" << p.getX() << ", " << p.getY() << ")\n";
        }
    }
};

static Point centroid;

int compareAngles(Point p1, Point p2)
{
    double angle1 = atan2(p1.getY() - centroid.getY(), p1.getX() - centroid.getX());
    double angle2 = atan2(p2.getY() - centroid.getY(), p2.getX() - centroid.getX());

    return angle1 < angle2;
}

Point getCentroid(Polygon *poly)
{
    double cx = 0.0, cy = 0.0;
    int vcount = poly->getPoly().size();

    for (int i = 0; i < vcount; i++)
    {
        cx += poly->getPoly()[i].getX();
        cy += poly->getPoly()[i].getY();
    }

    cx /= vcount, cy /= vcount;

    return Point(cx, cy);
}

void performCCWOrientation(Polygon **poly)
{
    centroid = getCentroid(*poly);
    sort((*poly)->getPoly().begin(), (*poly)->getPoly().end(), compareAngles);
}

int main()
{
    int v1, v2;
    double x, y;
    cout << "Enter number of vertices in convex polygon 1: ";
    cin >> v1;
    cout << "Enter number of vertices in convex polygon 2: ";
    cin >> v2;

    Polygon *poly1 = new Polygon;
    cout << "Enter vertices of polygon 1:\n";
    for (int i = 0; i < v1; i++)
    {
        cout << "Vertex " << i + 1 << ": ";
        cin >> x >> y;
        poly1->getPoly().push_back(Point(x, y));
    }

    Polygon *poly2 = new Polygon;
    cout << "Enter vertices of polygon 2:\n";
    for (int i = 0; i < v2; i++)
    {
        cout << "Vertex " << i + 1 << ": ";
        cin >> x >> y;
        poly2->getPoly().push_back(Point(x, y));
    }

    cout << "\nUnoriented set of points\n";
    cout << "Polygon 1:\n";
    poly1->printPoly();
    cout << endl;
    cout << "Polygon 2:\n";
    poly2->printPoly();

    performCCWOrientation(&poly1);
    performCCWOrientation(&poly2);

    cout << "\nOriented set of points (CCW) \n";
    cout << "Polygon 1:\n";
    poly1->printPoly();
    cout << endl;
    cout << "Polygon 2:\n";
    poly2->printPoly();

    delete poly1;
    delete poly2;
}
