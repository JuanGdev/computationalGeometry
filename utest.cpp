#include <functional>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "geocomp.hpp"
Point start(0,0);
Point end(0,5);
Segment reference(start, end);
Point rightPoint(2,2);
Point leftPoint(-2,-2);
Point edgePoint(0,3);

TEST_CASE ("Wrong parameters is_monotone function")
{
  SUBCASE("reference line is a point")
  {
    Line ln(Point(0,0), Point(0,0));
    PolyCh pc;
    pc.resize(3);
    pc[0] = Point(1,1);
    pc[1] = Point(2,1);
    pc[2] = Point(3,1);
    CHECK(is_monotone(pc,ln) == false);
  }
  SUBCASE("less than 3 vertices on PolyCh")
  {
    Line ln(Point(0,0), Point(1,0));
    PolyCh pc;
    pc.resize(2);
    pc[0] = Point(1,1);
    pc[1] = Point(2,1);
    CHECK(is_monotone(pc,ln) == false);
  }
}

TEST_CASE("polygonal chain monotone test"){ 
  Line ln(Point (0,0), Point (1,0));
  PolyCh pc; 
  pc.resize(5);

  SUBCASE("Polygonal Chain Case 1")
  {
    pc[0] = Point(1,1);
    pc[1] = Point(2,1);
    pc[2] = Point(3,2);
    pc[3] = Point(4,1);
    pc[4] = Point(5,1);

    CHECK(is_monotone(pc,ln) == true);
  }
  SUBCASE("Polygonal Chain Case 2")
  {
    pc[0] = Point(1,1);
    pc[1] = Point(2,1);
    pc[2] = Point(4,2);
    pc[3] = Point(4,1);
    pc[4] = Point(5,1);

    CHECK(is_monotone(pc,ln) == true);
  } 
  SUBCASE("Polygonal Chain Case 3")
  {
    pc[0] = Point(1,1);
    pc[1] = Point(2,1);
    pc[2] = Point(4,3);
    pc[3] = Point(4,2);
    pc[4] = Point(4,1);

    CHECK(is_monotone(pc,ln) == false);
  }
  SUBCASE("Polygonal Chain Case 4")
  {
    pc[0] = Point(1,1);
    pc[1] = Point(3,1);
    pc[2] = Point(2,2);
    pc[3] = Point(4,1);
    pc[4] = Point(5,1);

    CHECK(is_monotone(pc,ln) == false);
  }
}

TEST_CASE("area2 function")
{
  SUBCASE("Clock wise triangle"){
    Point a(1,1);
    Point b(2,3);
    Point c(3,2);
    CHECK(area2(a,b,c) == -3);
  }
  SUBCASE("Counterclock wise")
  {
    Point a(1,1);
    Point b(3,2);
    Point c(2,3);
    CHECK(area2(a,b,c) == 3);
  }
}

TEST_CASE("Point in Right?")
{
  SUBCASE("Right case")
  {
    CHECK(is_right(reference, rightPoint) == true);
  }
  SUBCASE("No Right")
  {
    CHECK(is_right(reference, leftPoint) == false);
  }
  SUBCASE("Is on edge")
  {
    CHECK(is_right(reference, edgePoint)==false);
  }
}
TEST_CASE("Point in Left?")
{
  SUBCASE("Left case")
  {
    CHECK(is_left(reference, leftPoint)==true);
  }
  SUBCASE("No left")
  {
    CHECK(is_left(reference, rightPoint)==false);
  }
  SUBCASE("Is on edge")
  {
    CHECK(is_left(reference, edgePoint)==false);
  }
}
TEST_CASE("Is left or on")
{
  SUBCASE("Left case")
  {
    CHECK(is_lefton(reference, leftPoint)==true);
  }
  SUBCASE("No left")
  {
    CHECK(is_lefton(reference, rightPoint)==false);
  }
  SUBCASE("Left or on edge")
  {
    CHECK(is_lefton(reference, edgePoint) == true);
  }
}
TEST_CASE("Is right or on")
{
  SUBCASE("Right case")
  {
    CHECK(is_righton(reference, rightPoint)==true);
  }
  SUBCASE("No right")
  {
    CHECK(is_righton(reference, rightPoint)==true);
  }
  SUBCASE("Right or on edge")
  CHECK(is_righton(reference, edgePoint)==true);
}
TEST_CASE("Is colinear")
{
  SUBCASE("Right point")
  {
    CHECK(is_colinear(reference, rightPoint)==false);
  }
  SUBCASE("Left point")
  {
    CHECK(is_colinear(reference, leftPoint)==false);
  }
  SUBCASE("On edge point")
  {
    CHECK(is_colinear(reference, edgePoint)==true);
  }
}
//is on edge test cases
TEST_CASE("Vertical Line")
{
  SUBCASE("Above the border line")
  {
    Point abovePt(0,7);
    CHECK(is_on_edge(reference, abovePt)==false); 
  }
  SUBCASE("Bellow the border line")
  {
    Point bellowPt(0,-7);
    CHECK(is_on_edge(reference, bellowPt)==false);
  }
  SUBCASE("On Border")
  {
    CHECK(is_on_edge(reference, edgePoint)==true);
  }
}

TEST_CASE("Horizontal Line")
{
  Point startHor(0,0);
  Point endHor(5,0);
  Segment horizontalLn(startHor, endHor);
  SUBCASE("To the left of border line")
  {
    Point leftHor(-4,0);
    CHECK(is_on_edge(horizontalLn, leftHor) == false);
  }
  SUBCASE("To the right of border line")
  {
    Point rightHor(8,0);
    CHECK(is_on_edge(horizontalLn, rightHor)==false);
  }
  SUBCASE("On border")
  {
    Point onBorderHor(2,0);
    CHECK(is_on_edge(horizontalLn, onBorderHor) == true);
  }
}

TEST_CASE("Canonical Line")
{
  Point startCan(-3,4);
  Point endCan(6,10);
  Segment canonicalLine(startCan, endCan);
  SUBCASE("Left to the border line canLn")
  {
    Point canPtLeft(-5, 8);
    CHECK(is_on_edge(canonicalLine, canPtLeft)==false);
  }
  SUBCASE("Right to the border line canLn")
  {
    Point canPtRight(4,8);
    CHECK(is_on_edge(canonicalLine, canPtRight)==false);
  }
  SUBCASE("On border line")
  {
    Point canPtEdge(0,6);
    CHECK(is_on_edge(canonicalLine, canPtEdge)==true);
  }
}
