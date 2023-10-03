#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "geocomp.hpp"

TEST_CASE( "wrong parameters is_monotone function" ) {
  SUBCASE( "reference line is a point" ) {
    Line ln( Point(0,0), Point(0,0) );
    PolyCh pc;

    pc.push_back( Point(1,1) );
    pc.push_back( Point(2,1) );
    pc.push_back( Point(3,1) );

    CHECK_FALSE( is_monotone(pc,ln) );
  }

  SUBCASE( "less than 3 vertices on PolyCh" ) {
    Line ln( Point(0,0), Point(1,0) );
    PolyCh pc;

    pc.push_back( Point(1,1) );
    pc.push_back( Point(2,1) );

    CHECK_FALSE( is_monotone(pc,ln) );
  }
}

TEST_CASE( "polygonal chain monotone test" ) {
  Line ln( Point(0,0), Point(1,0) );
  PolyCh pc;

  SUBCASE( "Polygonal Chain Case 1" ) {
    pc.push_back( Point(1,1) );
    pc.push_back( Point(2,1) );
    pc.push_back( Point(3,2) );
    pc.push_back( Point(4,1) );
    pc.push_back( Point(5,1) );

    CHECK( is_monotone(pc,ln) );
  }

  SUBCASE( "Polygonal Chain Case 2" ) {
    pc.push_back( Point(1,1) );
    pc.push_back( Point(2,1) );
    pc.push_back( Point(4,2) );
    pc.push_back( Point(4,1) );
    pc.push_back( Point(5,1) );

    CHECK( is_monotone(pc,ln) == true );
  }

  SUBCASE( "Polygonal Chain Case 3" ) {
    pc.push_back( Point(1,1) );
    pc.push_back( Point(2,1) );
    pc.push_back( Point(4,3) );
    pc.push_back( Point(4,2) );
    pc.push_back( Point(4,1) );

    CHECK( is_monotone(pc,ln) == false );
  }

  SUBCASE( "Polygonal Chain Case 4" ) {
    pc.push_back( Point(1,1) );
    pc.push_back( Point(3,1) );
    pc.push_back( Point(2,2) );
    pc.push_back( Point(4,1) );
    pc.push_back( Point(5,1) );

    CHECK( is_monotone(pc,ln) == false );
  }
}

TEST_CASE( "area2 function" ) {

  SUBCASE( "cw triangle" ) {
    Point a(1,1);
    Point b(2,3);
    Point c(3,2);

    CHECK( area2(a,b,c) == -3 );
  }

  SUBCASE( "ccw triangle" ) {
    Point a(1,1);
    Point b(3,2);
    Point c(2,3);

    CHECK( area2(a,b,c) == 3 );
  }

}

TEST_CASE( "general position " ) {
  PointSet set;

  SUBCASE( "empty set" ) {
    CHECK( is_genpos(set) );
  }

  SUBCASE( "single point" ) {
    set.push_back( Point(1,1) );
    CHECK( is_genpos(set) );
  }

  SUBCASE( "two different points" ) {
    set.push_back( Point(1,1) );
    set.push_back( Point(2,3) );
    CHECK( is_genpos(set) );
  }

  SUBCASE( "two equal points" ) {
    set.push_back( Point(1,1) );
    set.push_back( Point(1,1) );
    CHECK_FALSE( is_genpos(set) );
  }

  SUBCASE( "general case" ) {

    set.push_back( Point(1,1) );
    set.push_back( Point(2,3) );
    set.push_back( Point(4,2) );
    set.push_back( Point(5,4) );
    set.push_back( Point(3,6) );

    CHECK( is_genpos(set) );
  }

  SUBCASE( "general case fail" ) {
    set.push_back( Point(1, 1) );
    set.push_back( Point(2, 2) );
    set.push_back( Point(3, 3) );
    set.push_back( Point(4, 4) );
    set.push_back( Point(5, 5) );
    CHECK_FALSE( is_genpos(set) );
  }
}

TEST_CASE( "general position point set generator" ) {
  PointSet set = generator_genpos(10,0,100,0,100);
  CHECK( is_genpos(set) );
}

TEST_CASE("ángulos internos de triángulos")
{
  SUBCASE("Ángulo regular"){
    Vertex a(1,2);
    Vertex b(5,4);
    Vertex c(2,5);
    CHECK(angle(a,b,c)== doctest::Approx(0.7853981633974));
    CHECK(angle(b,c,a)== doctest::Approx(0.7853981633974));
    CHECK(angle(c,a,b)== doctest::Approx(1.5707963267949));
  }
  SUBCASE("Ángulo de 180")
  {
    Vertex a(1,2);
    Vertex b(5,4);
    Vertex c(3,3);
    CHECK(angle(a,b,c) == doctest::Approx(0.0));
    CHECK(angle(b,c,a) == doctest::Approx(0.0));
    CHECK(angle(c,a,b) == doctest::Approx(3.1415926535));

  }
}

TEST_CASE( "proper intersection" ) {
  SUBCASE( "segmento cd a la derecha de ab" ) {
    Point a(2,1);
    Point b(8,4);
    Point c(6,2);
    Point d(9,0);
    CHECK_FALSE( is_properint(a,b,c,d) );
  }
  SUBCASE( "segmento cd a la izquierda de ab" ) {
    Point a(2,1);
    Point b(8,4);
    Point c(4,4);
    Point d(1,8);
    CHECK_FALSE( is_properint(a,b,c,d) );
  }
  SUBCASE( "segmento ab a la derecha de cd" ) {
    Point a(6,2);
    Point b(9,0);
    Point c(2,1);
    Point d(8,4);
    CHECK_FALSE( is_properint(a,b,c,d) );
  }
  SUBCASE( "segmento ab a la izqueirda de cd" ) {
    Point a(4,4);
    Point b(1,8);
    Point c(2,1);
    Point d(8,4);
    CHECK_FALSE( is_properint(a,b,c,d) );
  }
  SUBCASE( "segmentos se intersectan" ) {
    Point a(1,2);
    Point b(7,5);
    Point c(7,2);
    Point d(2,7);
    CHECK( is_properint(a,b,c,d) );
  }
}

TEST_CASE( "intersection point" ) {
  Point a(1,2);
  Point b(7,5);
  Point c(7,2);
  Point d(2,7);

  Point e = inter_pt(a,b,c,d);
  CHECK( e.x == 5 );
  CHECK( e.y == 4 );
}

TEST_CASE( "circular array index" ) {

  // nominal
  CHECK( cindex(5,0) == 0 );
  CHECK( cindex(5,4) == 4 );

  // mayor o igual a n
  CHECK( cindex(5,5) == 0 );
  CHECK( cindex(5,9) == 4 );

  // mayor o igual a 2n
  CHECK( cindex(5,10) == 0 );
  CHECK( cindex(5,14) == 4 );

  // menor que 0 y mayor o igual a -n
  CHECK( cindex(5,-1) == 4 );
  CHECK( cindex(5,-5) == 0 );

  // menor que -n
  CHECK( cindex(5,-6)  == 4 );
  CHECK( cindex(5,-10) == 0 );
}

TEST_CASE( "circular index object function" ) {

  SUBCASE( "defaults" ) {
    CircIndex cind;

    // nominal
    CHECK( cind(0) == 0 );
    CHECK( cind(4) == 0 );

    // mayor o igual a n
    CHECK( cind(5) == 0 );
    CHECK( cind(9) == 0 );

    // mayor o igual a 2n
    CHECK( cind(10) == 0 );
    CHECK( cind(14) == 0 );

    // menor que 0 y mayor o igual a -n
    CHECK( cind(-1) == 0 );
    CHECK( cind(-5) == 0 );

    // menor que -n
    CHECK( cind(-6)  == 0 );
    CHECK( cind(-10) == 0 );
  }

  SUBCASE( "size set at definition" ) {
    CircIndex cind(5);

    // nominal
    CHECK( cind(0) == 0 );
    CHECK( cind(4) == 4 );

    // mayor o igual a n
    CHECK( cind(5) == 0 );
    CHECK( cind(9) == 4 );

    // mayor o igual a 2n
    CHECK( cind(10) == 0 );
    CHECK( cind(14) == 4 );

    // menor que 0 y mayor o igual a -n
    CHECK( cind(-1) == 4 );
    CHECK( cind(-5) == 0 );

    // menor que -n
    CHECK( cind(-6)  == 4 );
    CHECK( cind(-10) == 0 );
  }

  SUBCASE( "change size with set" ) {
    CircIndex cind;
    cind.set(5);

    // nominal
    CHECK( cind(0) == 0 );
    CHECK( cind(4) == 4 );

    // mayor o igual a n
    CHECK( cind(5) == 0 );
    CHECK( cind(9) == 4 );

    // mayor o igual a 2n
    CHECK( cind(10) == 0 );
    CHECK( cind(14) == 4 );

    // menor que 0 y mayor o igual a -n
    CHECK( cind(-1) == 4 );
    CHECK( cind(-5) == 0 );

    // menor que -n
    CHECK( cind(-6)  == 4 );
    CHECK( cind(-10) == 0 );
  }
}

TEST_CASE("Convex polygon")
{
  SUBCASE("Is convex")
  {
    Polygon polyy;
    polyy.push(Vertex(1,1));
    polyy.push(Vertex(4,0));
    polyy.push(Vertex(7,2));
    polyy.push(Vertex(6,5));
    polyy.push(Vertex(3,6));
    polyy.push(Vertex(1,4));
    CHECK(is_convex(polyy)==true);
  }
  SUBCASE("Not convex")
  {
    Polygon polyy;
    polyy.push(Vertex(1,1));
    polyy.push(Vertex(4,0));
    polyy.push(Vertex(7,2));
    polyy.push(Vertex(4,3));
    polyy.push(Vertex(3,6));
    polyy.push(Vertex(1,4));
    CHECK_FALSE(is_convex(polyy));
  }

  SUBCASE("Area")
  {
    Polygon polyy;
    polyy.push(Vertex(1,1));
    polyy.push(Vertex(4,0));
    polyy.push(Vertex(7,2));
    polyy.push(Vertex(6,5));
    polyy.push(Vertex(3,6));
    polyy.push(Vertex(1,4));
    CHECK(area(polyy) == doctest::Approx(25.5));
  }
}

TEST_CASE("is ahead function")
{
  Vector a(1,1);
  Vector b(3,-1);
  Vector d(2,1);
  CHECK(is_ahead(b,a,d));
  CHECK_FALSE(is_ahead(a,b,d));
}

TEST_CASE("extreme vertices lml")
{
  Polygon poly;
  poly.push(Vertex(3,1));
  poly.push(Vertex(8,2));
  poly.push(Vertex(9,5));
  poly.push(Vertex(4,7));
  poly.push(Vertex(1,4));



  SUBCASE("extreme indices")
  {
    Vector d(7,8);
    int  imin, imax;
    extremev(poly,d,imin,imax);
    CHECK(imin == 0);
    CHECK(imax == 2);
  }
  SUBCASE("extreme vertices")
  {
    Vector d(7,8);
    Vertex  vmin, vmax;
    extremev(poly,d,vmin,vmax);
    CHECK(vmin == Vertex(3,1));
    CHECK(vmax == Vertex(9,5));
  }
  SUBCASE("extreme indices (2)")
  {
    Vector d(-3,8);
    int imin, imax;
    extremev(poly, d, imin, imax);
    CHECK(imin == 1);
    CHECK(imax == 3);
  }
}
