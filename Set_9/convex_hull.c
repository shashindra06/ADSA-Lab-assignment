#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Point
{
    int x;
    int y;
};

struct Point points[MAX];
struct Point hull[MAX];

int n;

struct Point pivot;


/* ------------------------------------------------ */
/* Cross product / orientation                      */
/* ------------------------------------------------ */

int orientation(struct Point a,
                struct Point b,
                struct Point c)
{
    int value;

    value = (b.x - a.x) * (c.y - a.y)
          - (b.y - a.y) * (c.x - a.x);

    return value;
}


/* ------------------------------------------------ */
/* Squared distance                                 */
/* ------------------------------------------------ */

int distanceSquared(struct Point a,
                    struct Point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;

    return dx * dx + dy * dy;
}


/* ------------------------------------------------ */
/* Compare points by polar angle                    */
/* ------------------------------------------------ */

int comparePoints(const void *p1,
                  const void *p2)
{
    struct Point a = *(struct Point *)p1;
    struct Point b = *(struct Point *)p2;

    int turn;

    turn = orientation(pivot, a, b);

    if(turn == 0)
    {
        /*
         * If points have same angle,
         * closer point comes first.
         */
        return distanceSquared(pivot, a)
             - distanceSquared(pivot, b);
    }

    /*
     * Counter-clockwise point comes first.
     */
    if(turn > 0)
        return -1;

    return 1;
}


/* ------------------------------------------------ */
/* Find Convex Hull using Graham Scan               */
/* ------------------------------------------------ */

int grahamScan()
{
    int i;
    int pivotIndex = 0;

    /*
     * Find the lowest point.
     * If tied, choose the leftmost.
     */
    for(i = 1; i < n; i++)
    {
        if(points[i].y < points[pivotIndex].y ||
          (points[i].y == points[pivotIndex].y &&
           points[i].x < points[pivotIndex].x))
        {
            pivotIndex = i;
        }
    }

    /* Swap pivot to first position */
    struct Point temp = points[0];
    points[0] = points[pivotIndex];
    points[pivotIndex] = temp;

    pivot = points[0];

    /*
     * Sort remaining points by polar angle.
     */
    qsort(points + 1,
          n - 1,
          sizeof(struct Point),
          comparePoints);

    /*
     * Remove points having the same polar angle,
     * keeping only the farthest point.
     */
    int uniqueCount = 1;

    for(i = 1; i < n; i++)
    {
        while(i < n - 1 &&
              orientation(pivot,
                           points[i],
                           points[i + 1]) == 0)
        {
            i++;
        }

        points[uniqueCount++] = points[i];
    }

    if(uniqueCount < 3)
        return 0;

    /*
     * Initialize stack.
     */
    int top = 0;

    hull[top++] = points[0];
    hull[top++] = points[1];
    hull[top++] = points[2];

    /*
     * Process remaining points.
     */
    for(i = 3; i < uniqueCount; i++)
    {
        while(top >= 2 &&
              orientation(hull[top - 2],
                           hull[top - 1],
                           points[i]) <= 0)
        {
            top--;
        }

        hull[top++] = points[i];
    }

    return top;
}


/* ------------------------------------------------ */
/* Main                                             */
/* ------------------------------------------------ */

int main()
{
    int i;
    int hullSize;

    printf("========================================\n");
    printf("          CONVEX HULL - GRAHAM SCAN\n");
    printf("========================================\n");

    printf("\nEnter number of points: ");
    scanf("%d", &n);

    if(n < 3 || n > MAX)
    {
        printf("At least 3 and at most %d points are required.\n",
               MAX);
        return 0;
    }

    printf("\nEnter coordinates (x y):\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d %d",
              &points[i].x,
              &points[i].y);
    }

    hullSize = grahamScan();

    if(hullSize == 0)
    {
        printf("\nConvex hull cannot be formed.\n");
        return 0;
    }

    printf("\nConvex Hull Points:\n");

    for(i = 0; i < hullSize; i++)
    {
        printf("(%d, %d)\n",
               hull[i].x,
               hull[i].y);
    }

    printf("\nTotal points on convex hull: %d\n",
           hullSize);

    printf("\n========================================\n");

    return 0;
}