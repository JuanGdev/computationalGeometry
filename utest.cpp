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

//  Intersección
TEST_CASE("proper intersection")
{
  SUBCASE("Segmento cd a la derecha de ab")
  {
    Point a(2,1);
    Point b(8,4);
    Point c(6,2);
    Point d(9,0);
    CHECK_FALSE(is_properint(a,b,c,d));
  }
  SUBCASE("segmento cd a la izquierda de ab")
  {
    Point a (2,1);
    Point b (8,4);
    Point c (4,4);
    Point d (1,8);
    CHECK_FALSE(is_properint(a,b,c,d));
  }
  SUBCASE("segmentos se intersectan")
  {
    Point a(1,2);
    Point b(7,5);
    Point c(7,2);
    Point d(2,7);
    CHECK(is_properint(a,b,c,d));
  }
}
TEST_CASE("Punto de intersección")
{
  Point a(1,2);
  Point b(7,5);
  Point c(7,2);
  Point d(2,7);
  Point e = inter_pt(a,b,c,d);
  CHECK(e.x == 5);
  CHECK(e.y == 4);
}

TEST_CASE("índice arreglo circular")
{
  SUBCASE("nominal")
  {
    CHECK( cind(5,0) == 0);
    CHECK( cind(5,1) == 1);
    CHECK( cind(5,2) == 2);
    CHECK( cind(5,3) == 3);
    CHECK( cind(5,4) == 4);
  }

  SUBCASE("Mayor o igual a n")
  {
    CHECK( cind(5,5) == 0);
    CHECK( cind(5,6) == 1);
    CHECK( cind(5,7) == 2);
    CHECK( cind(5,8) == 3);
    CHECK( cind(5,9) == 4);
  }

  SUBCASE("Mayor o igual a 2n")
  {
    CHECK( cind(5,10) == 0);
    CHECK( cind(5,11) == 1);
    CHECK( cind(5,12) == 2);
    CHECK( cind(5,13) == 3);
    CHECK( cind(5,14) == 4);
  }
  SUBCASE("Menor que 0 y mayor o igual a -n")
  {
    CHECK( cind(5,-1) == 4);
    CHECK( cind(5,-2) == 3);
    CHECK( cind(5,-3) == 2);
    CHECK( cind(5,-4) == 1);
    CHECK( cind(5,-5) == 0);
  }
  SUBCASE("Menor que -n")
  {
    CHECK( cind(5,-6) == 4);
    CHECK( cind(5,-7) == 3);
    CHECK( cind(5,-8) == 2);
    CHECK( cind(5,-9) == 1);
    CHECK( cind(5,-10) == 0);
  }
}
