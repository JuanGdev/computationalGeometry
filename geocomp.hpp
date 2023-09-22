#ifndef GEOCOMP_HPP
#define GEOCOMP_HPP

#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

//-----------------------------------------------------------------------------
// Point
//-----------------------------------------------------------------------------

struct Point {
   Point();
   Point( int x, int y );
   int x;
   int y;
};

typedef Point Vertex;
typedef Point Vector;

Point operator+( Point a, Point b );
Point operator-( Point a, Point b );
Point operator/( Point a, int k );
Point operator*( Point a, Point b );
Point operator*( Point a, int k );
Point operator*( int k, Point a );

bool operator==( Point a, Point b );
bool operator!=( Point a, Point b );
std::ostream& operator<<( std::ostream& os, Point pt );

//-----------------------------------------------------------------------------
// Segment
//-----------------------------------------------------------------------------

struct Segment {
   Segment();
   Segment( Point a, Point b );
   Segment( int x0, int y0, int x1, int y1 );
   Point a;
   Point b;
};

typedef Segment Line;
typedef Segment Edge;

//-----------------------------------------------------------------------------
// Polygonal chain
//-----------------------------------------------------------------------------

typedef std::vector<Vertex> PolyCh;
std::ostream& operator<<( std::ostream& os, const PolyCh& pc );

typedef std::vector<Point> PointSet;


//-----------------------------------------------------------------------------
// Circular array
//-----------------------------------------------------------------------------

unsigned cindex( unsigned n, int i );

// objeto función
class CircIndex {
   public:
      CircIndex();
      CircIndex( unsigned size );
      void set( unsigned size );
      int operator()( int i ) const; //La función debe ser const
   private:
      int n;
      int dn;
      int sn;
};

//-----------------------------------------------------------------------------
// Polygon
//-----------------------------------------------------------------------------

class Polygon {
   public:
      Polygon();
      unsigned size() const;
      void push( Vertex vertex );

      const Vertex& operator[]( int index ) const;
      Vertex& operator[]( int index );

   private:
      CircIndex cind;
      std::vector<Vertex> m_vertices;
};

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Operaciones con puntos
int dot( Vector a, Vector b);
int distsqr( Point a, Point b );
int dist( Point a, Point b );
double fdist( Point a, Point b );

// Monotonía, cadenas poligonales
bool is_monotone( PolyCh pc, Line ln );

// Posición general de puntos
bool is_genpos( const PointSet& set );
PointSet generator_genpos(unsigned N, int x0, int x1, int y0, int y1);

// Área con signo
int area2( Point a, Point b, Point c );

// Posición relativa
bool is_right( Point a, Point b, Point c );
bool is_left( Point a, Point b, Point c );
bool is_righton( Point a, Point b, Point c );
bool is_lefton( Point a, Point b, Point c );
bool is_colinear( Point a, Point b, Point c );
bool is_onedge( Point a, Point b, Point c );

// Geometría de Triángulos
Point centroid( Point a, Point b, Point c );
Point middlept( Point a, Point b );
void ccirc ( Point a, Point b, Point c, Point& o, int& r );

void centroid( Point a, Point b, Point c, double& x, double& y );
void middlept( Point a, Point b, double& x, double& y );
void ccirc ( Point a, Point b, Point c, double& x, double& y, double& r );
double angle( Point a, Point b, Point c );

//Point circcenter ( Point a, Point b, Point c );

// Intersección
bool is_properint( Point a, Point b, Point c, Point d );
bool is_improperint( Point a, Point b, Point c, Point d );
bool is_inter( Point a, Point b, Point c, Point d );
Point inter_pt( Point a, Point b, Point c, Point d );
void inter_pt( Point a, Point b, Point c, Point d, double& x, double& y);

// Polygon
bool is_inside_convex( const Polygon& poly, Point pt );
bool is_insideon_convex( const Polygon& poly, Point pt );
bool is_properint( const Polygon& poly, const Segment& seg );
bool is_simple( const Polygon& poly );
bool is_autoint( const Polygon& poly );

//Tarea
bool is_convex(const Polygon& poly);
bool is_inside_noconvex(const Polygon& poly, Point pt);
=======

#endif

