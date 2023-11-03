#ifndef GEOCOMP_HPP
#define GEOCOMP_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <ostream>
#include <random>
#include <chrono>
#include <cmath>
#include <algorithm>

#define DEG (180.0/M_PI);
//angle*DEG;

// Nota:
// Problema con MinGW 64 y wingdi.h, windows.h
// Colisión de nombre con Polygon

//-----------------------------------------------------------------------
// Point
//-----------------------------------------------------------------------

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

//-----------------------------------------------------------------------
// Segment
//-----------------------------------------------------------------------

struct Segment {
   Segment();
   Segment( Point a, Point b );
   Segment( int x0, int y0, int x1, int y1 );
   Point a;
   Point b;
};

typedef Segment Line;
typedef Segment Edge;

//-----------------------------------------------------------------------
// Polygonal chain
//-----------------------------------------------------------------------

typedef std::vector<Vertex> PolyCh;
std::ostream& operator<<( std::ostream& os, const PolyCh& pc );
PolyCh operator+(const PolyCh& pc1, const PolyCh& pc2);

PolyCh operator+(const PolyCh& pc, const Point& pt);
PolyCh operator+( const Point& pt,const PolyCh& pc);

typedef std::vector<Point> PointSet;


//-----------------------------------------------------------------------
// Circular array
//-----------------------------------------------------------------------

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

//-----------------------------------------------------------------------
// Poly
//-----------------------------------------------------------------------

class Poly {
   public:
      Poly();
      Poly( const PolyCh& pc );
      unsigned size() const;
      void push( Vertex vertex );

      int realind( int index ) const;
      const Vertex& operator[]( int index ) const;
      Vertex& operator[]( int index );

   private:
      CircIndex cind;
      std::vector<Vertex> m_vertices;
};

std::ostream& operator<<( std::ostream& os, const Poly& poly );

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------

// Operaciones con puntos
int dot( Vector a, Vector b);
int distsqr( Point a, Point b );
int dist( Point a, Point b );
double fdist( Point a, Point b );
double mag( Vector v );

// Monotonía, cadenas poligonales
bool is_monotone( PolyCh pc, Line ln );

// Posición general de puntos
bool is_genpos( const PointSet& set );
PointSet generator_genpos(unsigned N, int x0, int x1, int y0, int y1);

// Área con signo
int area2( Point a, Point b, Point c );
double area( Point a, Point b, Point c );

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

// Poly
bool is_inside_convex( const Poly& poly, Point pt );
bool is_insideon_convex( const Poly& poly, Point pt );
bool is_properint( const Poly& poly, const Segment& seg );
bool is_simple( const Poly& poly );
bool is_autoint( const Poly& poly );
bool is_inside_noconvex( const Poly& poly, Point pt );

bool is_convex( const Poly& poly );

double area( const Poly& poly);

// true:  si a > b en dirección d
// false: si a < b en dirección d
bool is_ahead( Vector a, Vector b, Vector d );

void extremev( const Poly& poly, Vector d, Vertex& vmin, Vertex& vmax );
void extremev( const Poly& poly, Vector d, int& imin, int& imax );
void extremev( const PointSet& pset, Vector d, int& imin, int& imax );
bool psplit( const Poly& poly, int v1, int v2, PolyCh& c1, PolyCh& c2 );
bool is_monotone( const Poly& poly, Line ln );
void tangents( const Poly& poly, Point pt, int& i1, int& i2 );

// Incremental Hull
Poly incremental_hull( PointSet pset );

// Graham Hull
int get_p0( PointSet pset );

class AngleCmp {
   public:
      AngleCmp( const Point& p0 );
      bool operator()( const Point& si, const Point& sk );
   private:
      Point p0;
};

void angle_sort( PointSet& pset );

Poly graham_hull( PointSet pset );

//  Quick Hull
//  Función que recibe una nube de puntos, una dirección y regresa el punto más alejado
void init_line(const PointSet& pset, Point& a, Point& b);
void init_sets(const PointSet& pset, Point a, Point b, PointSet& lset, PointSet& rset);
unsigned most_forward(const PointSet& pset, Vector w);
PointSet subset(const PointSet& pset, Point a, Point b, Point c);
Poly qhull(const PointSet& pset);
PolyCh qhcall(const PointSet& pset, Point a, Point b);


#endif

