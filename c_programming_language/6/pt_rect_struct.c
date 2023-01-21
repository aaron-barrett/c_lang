#include <stdio.h>
#define XMAX 100
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

struct point {
    int x; 
    int y;
};

void print_point(struct point pt)
{
    printf("(%d, %d)",pt.x, pt.y);
}

struct rect {
    struct point pt1;
    struct point pt2;
};

void print_rect(struct rect r)
{
    printf("pt1 = ");
    print_point(r.pt1);
    printf("\n");
    printf("pt2 = ");
    print_point(r.pt2);
    printf("\n");
}

/* makepoint: make a piont from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2)
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
    return p.x>= r.pt1.x && p.x < r.pt2.x & p.y >= r.pt1.y && p.y < r.pt2.y;
}

/* canonrect: canonicalize coordinates of rectangle, i.e, put in first quadrant */
struct rect canonrect(struct rect r)
{
    struct rect temp;
    temp.pt1.x = min(r.pt1.x , r.pt2.x);
    temp.pt1.y = min(r.pt1.y , r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}

int main()
{
    struct rect screen;
    struct point middle;
    struct point makepoint(int,int);
    screen.pt1 = makepoint(0,0);
    screen.pt2 = makepoint(-XMAX,-XMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x)/2, (screen.pt1.y + screen.pt2.y)/2);
    print_rect(screen);
    struct rect screen_canon = canonrect(screen);
    print_rect(screen_canon);
    return 0 ;
}