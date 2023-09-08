#ifndef GEOCOMP_HPP
#define GEOCOMP_HPP

#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

struct Point {
   Point();
   Point( int x, int y );
   int x;
   int y;
};

Point operator+( Point a, Point b );
Point operator-( Point a, Point b );
Point operator/( Point a, int k );
Point operator*( Point a, Point b );
Point operator*( Point a, int k );
Point operator*( int k, Point a );

bool operator==( Point a, Point b );
bool operator!=( Point a, Point b );
std::ostream& operator<<( std::ostream& os, Point pt );

typedef Point Vertex;
typedef Point Vector;

struct Segment {
   Segment();
   Segment( Point a, Point b );
   Segment( int x0, int y0, int x1, int y1 );
   Point a;
   Point b;
};

typedef Segment Line;
typedef Segment Edge;

typedef std::vector<Vertex> PolyCh;
std::ostream& operator<<( std::ostream& os, const PolyCh& pc );

typedef std::vector<Point> PointSet;

// Producto escalar
int dot( Vector a, Vector b);
int distsqr( Point a, Point b );
int dist( Point a, Point b );
double fdist( Point a, Point b );

// Monotonía cadenas poligonales
bool is_monotone( PolyCh pc, Line ln );

// Área con signo
int area2( Point a, Point b, Point c );

// Posición relativa
bool is_right( Point a, Point b, Point c );
bool is_left( Point a, Point b, Point c );
bool is_righton( Point a, Point b, Point c );
bool is_lefton( Point a, Point b, Point c );
bool is_colinear( Point a, Point b, Point c );
bool is_onedge( Point a, Point b, Point c );

bool is_genpos( const PointSet& set );
PointSet generator_genpos(unsigned, int, int, int, int);
      //unsiged N, int x0, int x1, int y0, int y1
      //);

// Geometría de Triángulos
Point centroid( Point a, Point b, Point c );
Point middlept( Point a, Point b );
Point circcenter ( Point a, Point b, Point c );
Point circradius ( Point o, Point v );
double angle( Point a, Point b, Point c );

// Intersección
bool is_properint( Point a, Point b, Point c, Point d );
bool is_improperint( Point a, Point b, Point c, Point d );
bool is_inter( Point a, Point b, Point c, Point d );
Point inter_pt( Point a, Point b, Point c, Point d );
void inter_pt( Point a, Point b, Point c, Point d, double& x, double& y );
#endif

