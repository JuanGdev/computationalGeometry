#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "geocomp.hpp"

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

// TEST_CASE("test description")
// REQUIRE(); //half
// CHECK(); //continue
// WARN(); // message only
// SUBCASE("subtest description"){
// CHECK(a==b);
// }
// }
