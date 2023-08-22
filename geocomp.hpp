#ifndef GEOCOMP_HPP
#define GEOCOMP_HPP
#include <vector>
#include <ostream>
struct Point{
  Point();
  Point(int x, int y);
  int x;
  int y;
};

Point operator-(Point a, Point b);
Point operator+(Point a, Point b);

bool operator == (Point a, Point b);
bool operator != (Point a, Point b);

std::ostream& operator << (std::ostream& os, const Point& pt); //Printing in cout objects type Point


// Vertext and Vector in code are the same as Point, but not conceptually
typedef Point Vertex;
typedef Point Vector;

struct Segment{
  Segment();
  Segment(Point a, Point b);
  Segment( int x0, int y0, int x1, int y1);
  Point a;
  Point b;
};

typedef Segment Line;
typedef Segment Edge;

//PolyCh now is std::vector<Vertex>
typedef std::vector<Vertex> PolyCh;
std::ostream& operator <<(std::ostream& os, const PolyCh& pc);

int dot( Vector a, Vector b);

bool is_monotone(PolyCh pc, Line ln);

int area2( Point a, Point b, Point c);
#endif
