#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Point
{
    double x, y;
} Point;

typedef struct Polygon
{
    Point *vertices;
    int vCount;
} Polygon;

static Point centroid;

double get2x2Det(double d11, double d12, double d21, double d22)
{
    return (d11 * d22 - d12 * d21);
}

int equalSlope(Point p1, Point p2, Point q1, Point q2)
{
    double s1_dx = p2.x - p1.x;
    double s1_dy = p2.y - p1.y;
    double s2_dx = q2.x - q1.x;
    double s2_dy = q2.y - q1.y;

    return fabs(s1_dy * s2_dx - s2_dy * s1_dx) < 1e-9;
}

Point getCentroid(Polygon *poly)
{
    Point c;
    double x_sum = 0.0, y_sum = 0.0;

    for (int i = 0; i < poly->vCount; i++)
    {
        x_sum += poly->vertices[i].x;
        y_sum += poly->vertices[i].y;
    }
    c.x = x_sum / poly->vCount;
    c.y = y_sum / poly->vCount;

    return c;
}

int compareAngles(const void *a, const void *b)
{
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;

    // Compute the angles
    double angle1 = atan2(p1->y - centroid.y, p1->x - centroid.x);
    double angle2 = atan2(p2->y - centroid.y, p2->x - centroid.x);

    // Sort by increasing angle
    if (angle1 < angle2)
        return -1;
    if (angle1 > angle2)
        return 1;
    return 0;
}

Point getIntersectionPoint(Point p1, Point p2, Point q1, Point q2)
{
    Point intPt;
    double a1 = p2.y - p1.y, a2 = q2.y - q1.y;
    double b1 = p1.x - p2.x, b2 = q1.x - q2.x;
    double c1 = p1.x * a1 + p1.y * b1, c2 = q1.x * a2 + q1.y * b2;

    intPt.x = get2x2Det(c1, b1, c2, b2) / get2x2Det(a1, b1, a2, b2);
    intPt.y = get2x2Det(a1, c1, a2, c2) / get2x2Det(a1, b1, a2, b2);

    return intPt;
}

int isSamePoint(Point p1, Point p2)
{
    return (p1.x == p2.x && p1.y == p2.y);
}

/* strict is ON, during intersection checks */
int pointOnSegment(Point p, Point v1, Point v2, int strict)
{
    if (isSamePoint(p, v1) || isSamePoint(p, v2))
    {
        return (strict) ? 0 : 1;
    }

    double crossProduct = get2x2Det(p.x - v1.x, p.y - v1.y, v2.x - v1.x, v2.y - v1.y);
    // printf("Cross Product: %lf\n", crossProduct);
    if (fabs(crossProduct) > 1e-9)
        return 0;

    if (p.x >= fmin(v1.x, v2.x) && p.x <= fmax(v1.x, v2.x) && p.y >= fmin(v1.y, v2.y) && p.y <= fmax(v1.y, v2.y))
        return 1;

    return 0;
}

/* perform counter-clockwise orientation on set of points of polygon, to get the ordered set */
void performCCWOrientation(Polygon **poly)
{
    centroid = getCentroid(*poly);
    qsort((*poly)->vertices, (*poly)->vCount, sizeof(Point), compareAngles);
}

int checkTouching(Polygon *poly1, Polygon *poly2)
{
    // finding set intersection p1->vertices and p2->vertices
    for (int i = 0; i < poly1->vCount; i++)
    {
        for (int j = 0; j < poly2->vCount; j++)
        {
            if (isSamePoint(poly1->vertices[i], poly2->vertices[j]))
            {
                return 1;
            }
        }
    }

    // checking polygon 1 with polygon 2
    for (int i = 0; i < poly1->vCount; i++)
    {
        for (int j = 0; j < poly2->vCount; j++)
        {
            if (pointOnSegment(poly1->vertices[i], poly2->vertices[j], poly2->vertices[(j + 1) % poly2->vCount], 0))
            {
                return 1;
            }
        }
    }

    // checking polygon 2 with polygon 1
    for (int i = 0; i < poly2->vCount; i++)
    {
        for (int j = 0; j < poly1->vCount; j++)
        {
            if (pointOnSegment(poly2->vertices[i], poly1->vertices[j], poly1->vertices[(j + 1) % poly1->vCount], 0))
            {
                return 1;
            }
        }
    }
    return 0;
}

int checkIntersecting(Polygon *poly1, Polygon *poly2)
{
    int flag = 0;
    for (int i = 0; i < poly1->vCount; i++)
    {
        for (int j = 0; j < poly2->vCount; j++)
        {
            // printf("Equal Slope? %d\n", equalSlope(poly1->vertices[i], poly1->vertices[(i + 1) % poly1->vCount], poly2->vertices[j], poly2->vertices[(j + 1) % poly2->vCount]));
            if (!equalSlope(poly1->vertices[i], poly1->vertices[(i + 1) % poly1->vCount], poly2->vertices[j], poly2->vertices[(j + 1) % poly2->vCount]))
            {
                Point intPt = getIntersectionPoint(poly1->vertices[i], poly1->vertices[(i + 1) % poly1->vCount], poly2->vertices[j], poly2->vertices[(j + 1) % poly2->vCount]);
                // printf("%lf %lf\n", intPt.x, intPt.y);
                if (pointOnSegment(intPt, poly1->vertices[i], poly1->vertices[(i + 1) % poly1->vCount], 1) && pointOnSegment(intPt, poly2->vertices[j], poly2->vertices[(j + 1) % poly2->vCount], 1))
                {
                    flag |= 1;
                }
                // printf("Flag: %d\n", flag);
            }
        }
    }

    for (int i = 0; i < poly2->vCount; i++)
    {
        for (int j = 0; j < poly1->vCount; j++)
        {
            if (!equalSlope(poly2->vertices[i], poly2->vertices[(i + 1) % poly2->vCount], poly1->vertices[j], poly1->vertices[(j + 1) % poly1->vCount]))
            {
                Point intPt = getIntersectionPoint(poly2->vertices[i], poly2->vertices[(i + 1) % poly2->vCount], poly1->vertices[j], poly1->vertices[(j + 1) % poly1->vCount]);
                if (pointOnSegment(intPt, poly2->vertices[i], poly2->vertices[(i + 1) % poly2->vCount], 1) && pointOnSegment(intPt, poly1->vertices[j], poly1->vertices[(j + 1) % poly1->vCount], 1))
                {
                    flag |= 1;
                }
            }
        }
    }

    return (flag) ? 1 : 0;
}

int main()
{

    printf("\nTHIS PROGRAM CHECKS WHETHER TWO POLYGONS ARE INTERSECTING OR TOUCHING OR NON-INTERSECTING\n\n");

    int v1, v2;
    printf("Enter number of vertices of convex polygon 1: ");
    scanf("%d", &v1);
    printf("Enter number of vertices of convex polygon 2: ");
    scanf("%d", &v2);

    /* Polygon 1 */
    Polygon *poly1 = (Polygon *)malloc(sizeof(Polygon));
    poly1->vertices = (Point *)malloc(v1 * sizeof(Point));
    poly1->vCount = v1;

    printf("Enter vertices of convex polygon 1:\n");
    for (int i = 0; i < poly1->vCount; i++)
    {
        printf("Vertex %d: ", i + 1);
        scanf("%lf %lf", &(poly1->vertices[i].x), &(poly1->vertices[i].y));
    }

    /* Polygon 2 */
    Polygon *poly2 = (Polygon *)malloc(sizeof(Polygon));
    poly2->vertices = (Point *)malloc(v2 * sizeof(Point));
    poly2->vCount = v2;

    printf("Enter vertices of convex polygon 2:\n");
    for (int i = 0; i < poly2->vCount; i++)
    {
        printf("Vertex %d: ", i + 1);
        scanf("%lf %lf", &(poly2->vertices[i].x), &(poly2->vertices[i].y));
    }

    performCCWOrientation(&poly1);
    performCCWOrientation(&poly2);

    /*printf("Polygon 1:\n");
    for (int i = 0; i < poly1->vCount; i++)
    {
        printf("(%lf,%lf)", poly1->vertices[i].x, poly1->vertices[i].y);
    }
    printf("\nPolygon2 2:\n");
    for (int i = 0; i < poly2->vCount; i++)
    {
        printf("(%lf,%lf)", poly2->vertices[i].x, poly2->vertices[i].y);
    }
    printf("\n");*/

    int intersect = 0, touch = 0;

    touch = checkTouching(poly1, poly2);
    intersect = checkIntersecting(poly1, poly2);

    if (intersect)
    {
        printf("Intersecting Polygons\n");
    }
    else
    {
        if (touch)
        {
            printf("Touching Polygons\n");
        }
        else
        {
            printf("Non-intersecting Polygons\n");
        }
    }

    free(poly1->vertices);
    free(poly2->vertices);
    free(poly1);
    free(poly2);
}
