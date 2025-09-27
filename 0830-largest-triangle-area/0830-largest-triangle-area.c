#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
} Point;

int cmpPoints(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1 -> x == p2 -> x) return p1 -> y - p2 -> y;
    return p1 -> x - p2 -> x;
}

int cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double area2(Point a, Point b, Point c) {
    return fabs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

int convexHull(Point* pts, int n, Point* hull) {
    qsort(pts, n, sizeof(Point), cmpPoints);
    int m = 0;
    
    for (int i = 0; i < n; i++) {
        while (m >= 2 && cross(hull[m-2], hull[m-1], pts[i]) <= 0) {
            m--;
        }
        hull[m++] = pts[i];
    }

    int t = m + 1;
    for (int i = n - 2; i >= 0; i--) {
        while (m >= t && cross(hull[m - 2], hull[m - 1], pts[i]) <= 0) {
            m--;
        }
        hull[m++] = pts[i];
    }
    return m - 1;
}

double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {
    Point pts[55];
    for (int i = 0; i < pointsSize; i++) {
        pts[i].x = points[i][0];
        pts[i].y = points[i][1];
    }

    Point hull[110];
    int h = convexHull(pts, pointsSize, hull);

    double maxArea = 0.0;
    for (int i = 0; i < h; i++) {
        int k = (i + 2) % h;
        for (int j = i + 1; j < h; j++) {
            while ((k + 1) % h != i && area2(hull[i], hull[j], hull[k]) < area2(hull[i], hull[j], hull[(k + 1) % h])) {
                k = (k + 1) % h;
            }
            double a = area2(hull[i], hull[j], hull[k]);
            if (a > maxArea) maxArea = a;
        }
    }
    return maxArea / 2.0;
}