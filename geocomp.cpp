#include "geocomp.hpp"
#include <ostream>

// Initilization list
Point::Point(): x(0), y(0){}
// {
// x = 0;
// y = 0;
// }


Point::Point(int x, int y): x(x), y(y) {}
// {
// this->x = x; //x variable from point gets a value from parameters
// this->x uses the variable from the struct
// this->y = y;
// }


Point operator+(Point a, Point b)
{
  return Point(a.x+b.x, a.y+b.y);
}

Point operator-(Point a, Point b)
{
  return Point(a.x-b.x, a.y-b.y);
}

bool operator == (Point a, Point b)
{
  if(a.x != b.x) return false;
  if(a.y != b.y) return false;
  return true;
}

std::ostream& operator << (std::ostream& os, const Point& pt)
{
  os << "(" << pt.x << "," << pt.y << ")";
  return os;
}

std::ostream& operator << (std::ostream& os, const PolyCh& pc)
{
  os << pc[0];
  for(unsigned i = 1; i < pc.size(); i+=1)
  {
    os << "--" << pc[i];
  }
  return os;
}





bool operator != (Point a, Point b)
{
  if(a.x != b.x) return true;
  if(a.y != b.y) return true;
  return false;
}


Segment::Segment() {}

Segment::Segment(Point a, Point b): a(a.x, a.y), b(b.x, b.y){}
//{
//this -> a = Point(a.x, a.y);
//this -> b = Point(b.x, b.y);
//}

Segment::Segment(int x0, int y0, int x1, int y1): a(x0, y0), b(x1,y1){}
//{
//a = Point(x0, y0);
//b = Point(x1, y1);
//}

int dot( Vector a, Vector b)
{
  return a.x*b.x + a.y*b.y;
}
bool is_monotone(PolyCh pc, Line ln)
{
  if(pc.size() < 3) return false;
  if (ln.a == ln.b) return false; //-> check if the line is not a point

  Vector v, w;
  w = ln.b - ln.a;
  int a = 0;
  //  v.x = pc[0].x - ln.a.x;
  //v.y = pc[0].y - ln.a.y;

  v = pc[0] - ln.a;
  int b = dot(v,w);

  v = pc[1] - ln.a;
  int c = dot(v,w);

  for(int i = 2; i < pc.size(); i +=1)
  {
    v = pc[i] - ln.a;

    a = b;
    b = c;
    c = dot(v,w);

    // Case 1: (a < b < c) 
    // (a > b > c) 
    if (a < b && b < c) continue;
    if( a > b && b > c) continue;
    // continue stops the current for loop iteration
    // Case 2: (a = b < c) || (a < b = c) 
    //         (a = b > c) || (a > b = c)
    if((a == b && b < c) || (a < b && b == c)) continue;
    if((a == b && b > c) || (a > b && b == c)) continue;
    return false;
  }
  return true;
}
int area2( Point a, Point b, Point c)
{
  Vector v = b - a;
  Vector w = c - a;
  return (v.x*w.y - v.y*w.x);
}

