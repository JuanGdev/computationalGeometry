#include "geocomp.hpp"


//------------------------------------------------------------------------
// Point
//------------------------------------------------------------------------

Point::Point(): x(0), y(0) { }

Point::Point( int x, int y ): x(x), y(y) { }

Point operator+( Point a, Point b ) {
  return Point(a.x+b.x,a.y+b.y);
}

Point operator-( Point a, Point b ) {
  return Point(a.x-b.x,a.y-b.y);
}

Point operator/( Point a, int k ) {
  return Point(a.x/k,a.y/k);
}

Point operator*( Point a, Point b ) {
  return Point(a.x*b.x,a.y*b.y);
}

Point operator*( Point a, int k ) {
  return Point(a.x*k,a.y*k);
}

Point operator*( int k, Point a ) {
  return Point(a.x*k,a.y*k);
}

bool operator==( Point a, Point b ) {
  if ( a.x != b.x ) return false;
  if ( a.y != b.y ) return false;
  return true;
}

bool operator!=( Point a, Point b ) {
  if ( a.x != b.x ) return true;
  if ( a.y != b.y ) return true;
  return false;
}

std::ostream& operator<<( std::ostream& os, Point pt ) {
  os << "(" << pt.x << "," << pt.y << ")";
  return os;
}

//-----------------------------------------------------------------------
// Segment
//-----------------------------------------------------------------------

Segment::Segment() { }

Segment::Segment( Point a, Point b ): a(a.x,a.y), b(b.x,b.y) { }

Segment::Segment( int x0, int y0, int x1, int y1 ): a(x0,y0), b(x1,y1) { }

//-----------------------------------------------------------------------
// Polygonal chain
//-----------------------------------------------------------------------

std::ostream& operator<<( std::ostream& os, const PolyCh& pc ) {
  os << pc[0];
  for ( unsigned i=1; i<pc.size(); i+=1 ) {
    os << "--" << pc[i];
  }
  return os;
}

PolyCh operator+(const PolyCh& pc1, const PolyCh& pc2)
{
  PolyCh ret;
  for(unsigned i = 0; i < pc1.size(); i+=1)
  {
    ret.push_back(pc1[i]);
  }
  for(unsigned i = 0; i < pc2.size(); i+=1)
  {
    ret.push_back(pc2[i]);
  }
  return ret;
}

PolyCh operator+(const PolyCh& pc, const Point& pt)
{
  PolyCh ret;
  for(unsigned i = 0; i < pc.size(); i+=1)
  {
    ret.push_back(pc[i]);
  }
  ret.push_back(pt);
  return ret;
}

PolyCh operator+( const Point& pt,const PolyCh& pc)
{
  PolyCh ret;
  ret.push_back(pt);

  for(unsigned i = 0; i < pc.size(); i+=1)
  {
    ret.push_back(pc[i]);
  }
  return ret;
}

//-----------------------------------------------------------------------
// Circular array
//-----------------------------------------------------------------------

CircIndex::CircIndex(): n(1), dn(1), sn(-1) { }

CircIndex::CircIndex( unsigned size ): n(size), dn(size<<1), sn(-size) { }

void CircIndex::set( unsigned size ) {
  n = (int)size;
  dn = n << 1;
  sn = -n;
}

int CircIndex::operator()( int i ) const {
  if ( i >= 0 ) {
    if ( i < n ) return i;
    if ( i < dn ) return i - n;
    return i % n;
  }
  if ( i >= sn ) return n + i;
  return (i + 1) % n + (n - 1);
}

unsigned cindex( unsigned n, int i ) {
  int m = (int)n;

  if ( i >= 0 ) {
    if ( i < m ) return i;
    if ( i < (m<<1) ) return i - m;
    return i % m;
  }
  if ( i >= -m ) return m + i;
  return (i + 1) % m + (m - 1);
}

//-----------------------------------------------------------------------
// Poly
//-----------------------------------------------------------------------

Poly::Poly() { }

Poly::Poly( const PolyCh& pc ) {
  m_vertices = pc;
  cind.set( size() );
}

unsigned Poly::size() const {
  return m_vertices.size();
}

void Poly::push( Vertex vertex ) {
  m_vertices.push_back(vertex);
  cind.set( size() );
  //cind = CircIndex(m_vertices.size());
}

int Poly::realind( int index ) const {
  return cind(index);
}

const Vertex& Poly::operator[]( int index ) const {
  return m_vertices[cind(index)];
}

Vertex& Poly::operator[]( int index ) {
  return m_vertices[cind(index)];
}

std::ostream& operator<<( std::ostream& os, const Poly& poly ) {
  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    os << poly[i] << "--";
  }
  os << "{" << poly[0] << "}";
  return os;
}

//-----------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------

int dot( Vector a, Vector b) {
  return a.x*b.x + a.y*b.y;
}

int distsqr( Point a, Point b ) {
  return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

int dist( Point a, Point b ) {
  return (int)std::sqrt(distsqr(a,b));
}

double fdist( Point a, Point b ) {
  return std::sqrt(distsqr(a,b));
}

double mag( Vector v ) {
  return std::sqrt(v.x*v.x + v.y*v.y);
}

// Caso 1: ( a < b < c )
//         ( a > b > c )
// Caso 2: ( a = b < c ) || ( a < b = c )
//         ( a = b > c ) || ( a > b = c )
bool is_monotone( PolyCh pc, Line ln ) {
  if ( pc.size() < 3 ) return false;
  if ( ln.a == ln.b ) return false;

  Vector v, w;
  w = ln.b - ln.a;
  int a = 0;

  v = pc[0] - ln.a;
  int b = dot(v,w);

  v = pc[1] - ln.a;
  int c = dot(v,w);

  for ( int i=2; i<(int)pc.size(); i+=1 ) {
    v = pc[i] - ln.a;

    a = b;
    b = c;
    c = dot(v,w);

    if ( a < b && b < c ) continue;
    if ( a > b && b > c ) continue;
    if ( ( a == b && b < c ) || ( a < b && b == c ) ) continue;
    if ( ( a == b && b > c ) || ( a > b && b == c ) ) continue;

    return false;
  }
  return true;
}

int area2( Point a, Point b, Point c ) {
  Vector v = b - a;
  Vector w = c - a;
  return (v.x*w.y - v.y*w.x);
}

double area( Point a, Point b, Point c ) {
  return 0.5*area2(a,b,c);
}

bool is_right( Point a, Point b, Point c ) {
  return (area2(a,b,c) < 0);
}

bool is_left( Point a, Point b, Point c ) {
  return (area2(a,b,c) > 0);
}

bool is_righton( Point a, Point b, Point c ) {
  return (area2(a,b,c) <= 0);
}

bool is_lefton( Point a, Point b, Point c ) {
  return (area2(a,b,c) >= 0);
}

bool is_colinear( Point a, Point b, Point c ) {
  return (area2(a,b,c) == 0);
}

bool is_onedge( Point a, Point b, Point c ) {
  // Comprobamos colinealidad
  if (area2(a,b,c) != 0) return false;

  // Verificamos si c está entre a y b
  if ( (a.x < c.x) && (c.x < b.x) ) return true;
  if ( (a.y < c.y) && (c.y < b.y) ) return true;
  if ( (a.x > c.x) && (c.x > b.x) ) return true;
  if ( (a.x > c.y) && (c.y > b.y) ) return true;
  return false;
}

bool is_genpos( const PointSet& set ) {

  // Casos especiales
  if ( set.size() == 0 ) return true;
  if ( set.size() == 1 ) return true;
  if ( set.size() == 2 ) {
    if ( set[0] != set[1] ) return true;
    return false;
  }

  // Caso general
  for ( unsigned i=0; i<set.size()-2; i+=1 ) {
    for ( unsigned j=i+1; j<set.size()-1; j+=1 ) {
      for ( unsigned k=j+1; k<set.size(); k+=1 ) {
        if ( is_colinear(set[i],set[j],set[k]) ) {
          return false;
        }
      }
    }
  }

  return true;
}

// N = número de puntos a generar
// x0 = menor valor componente en x
// x1 = mayor valor componente en x
// y0 = menor valor componente en y
// y1 = mayor valor componente en y
PointSet generator_genpos( unsigned N, int x0, int x1, int y0, int y1 ) {
  PointSet set;
  Point pt;

  if ( N == 0 ) return set;
  if ( x0 > x1 ) std::swap(x0,x1);
  if ( y0 > y1 ) std::swap(y0,y1);

  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_int_distribution<int> distx(x0,x1);
  std::uniform_int_distribution<int> disty(y0,y1);

  pt.x = distx(generator);
  pt.y = disty(generator);
  set.push_back(pt);
  if ( N == 1 ) return set;

  do {
    pt.x = distx(generator);
    pt.y = disty(generator);
  } while ( pt == set[0] );
  set.push_back(pt);
  if ( N == 2 ) return set;

  while ( set.size() < N ) {
    pt.x = distx(generator);
    pt.y = disty(generator);

    // ADVERTENCIA: Este bloque de código usa la instrucción 'goto' para
    // romper los ciclos anidados. La etiqueta se coloca justo después del
    // bloque de ciclos por claridad. Este es el único caso en que el uso de
    // 'goto' está justificado, porque este bloque no podemos separarlo
    // facilmente como una función independiente.
    for ( unsigned i=0; i<set.size()-1; i+=1 ) {
      for ( unsigned j=i+1; j<set.size(); j+=1 ) {
        if ( is_colinear(set[i],set[j],pt) ) {
          goto gen_pt_again;
        }
      }
    }
    set.push_back(pt);
  gen_pt_again:;
  }

  return set;
}

Point centroid( Point a, Point b, Point c ) {
  return ((a + b + c)/3);
}

Point middlept( Point a, Point b ) {
  return ((a + b)/2);
}

void ccirc ( Point a, Point b, Point c, Point& o, int& r ) {
  Point B = b - a;
  Point C = c - a;
  Point O;

  Point B2 = B * B;
  Point C2 = C * C;

  O.x = C.y*(B2.x + B2.y) - B.y*(C2.x + C2.y);
  O.y = B.x*(C2.x + C2.y) - C.x*(B2.x + B2.y) ;
  int D = 2*(B.x*C.y - B.y*C.x);

  o = O/D + a;
  r = (int)std::sqrt(O.x*O.x + O.y*O.y);
}

void centroid( Point a, Point b, Point c, double& x, double& y ) {
  x = (a.x + b.x + c.x)*(1.0/3.0);
  y = (a.y + b.y + c.y)*(1.0/3.0);
}

void middlept( Point a, Point b, double& x, double& y ) {
  x = 0.5*(a.x + b.x);
  y = 0.5*(a.y + b.y);
}

void ccirc ( Point a, Point b, Point c, double& x, double& y, double& r ) {
  Point B = b - a;
  Point C = c - a;

  Point B2 = B * B;
  Point C2 = C * C;

  double Ox = C.y*(B2.x + B2.y) - B.y*(C2.x + C2.y);
  double Oy = B.x*(C2.x + C2.y) - C.x*(B2.x + B2.y) ;
  double D = 2*(B.x*C.y - B.y*C.x);

  x = Ox/D + a.x;
  y = Oy/D + a.y;
  r = std::sqrt(Ox*Ox + Oy*Oy);
}

//Point circcenter ( Point a, Point b, Point c ) {
//   Point B = b - a;
//   Point C = c - a;
//   Point O;
//
//   Point B2 = B * B;
//   Point C2 = C * C;
//
//   O.x = C.y*(B2.x + B2.y) - B.y*(C2.x + C2.y);
//   O.y = B.x*(C2.x + C2.y) - C.x*(B2.x + B2.y) ;
//   int D = 2*(B.x*C.y - B.y*C.x);
//
//   return O/D + a;
//}

double angle( Point a, Point b, Point c ) {
  Vector v = b - a;
  Vector w = c - a;
  return std::acos( dot(v,w)/(mag(v)*mag(w)) );
}

bool is_properint( Point a, Point b, Point c, Point d ) {
  if ( is_right(a,b,c) && is_right(a,b,d) ) return false;
  if ( is_left(a,b,c)  && is_left(a,b,d)  ) return false;
  if ( is_right(c,d,a) && is_right(c,d,b) ) return false;
  if ( is_left(c,d,a)  && is_left(c,d,b)  ) return false;
  return true;
}

bool is_improperint( Point a, Point b, Point c, Point d ) {
  if ( is_onedge(a,b,c) ) return true;
  if ( is_onedge(a,b,d) ) return true;
  if ( is_onedge(c,d,a) ) return true;
  if ( is_onedge(c,d,b) ) return true;

  if ( a == c ) return true;
  if ( a == d ) return true;
  if ( b == c ) return true;
  if ( b == d ) return true;

  return false;
}

bool improper_pt( Point a, Point b, Point c, Point d, Point& r ) {
  if ( is_onedge(a,b,c) ) {
    r = c;
    return true;
  }

  if ( is_onedge(a,b,d) ) {
    r = d;
    return true;
  }

  if ( is_onedge(c,d,a) ) {
    r = a;
    return true;
  }

  if ( is_onedge(c,d,b) ) {
    r = b;
    return true;
  }

  if ( a == c ) {
    r = a;
    return true;
  }

  if ( a == d ) {
    r = a;
    return true;
  }

  if ( b == c ) {
    r = b;
    return true;
  }

  if ( b == d ) {
    r = b;
    return true;
  }

  r = a;
  return false;
}

bool is_inter( Point a, Point b, Point c, Point d ) {
  if ( is_properint(a,b,c,d) ) return true;
  if ( is_improperint(a,b,c,d) ) return true;
  return false;
}

Point inter_pt( Point a, Point b, Point c, Point d ) {
  double x, y, m1, m2, k1, k2;

  // Caso: (a,b) vertical
  if ( a.x == b.x ) {
    x = a.x;
    m2 = (double)(d.y - c.y)/(d.x - c.x);
    k2 = c.y - m2*c.x;
    y = m2*x + k2;
    return Point((int)x,(int)y);
  }

  // Caso: (c,d) vertical
  if ( c.x == d.x ) {
    x = c.x;
    m1 = (double)(b.y - a.y)/(b.x - a.x);
    k1 = a.y - m1*a.x;
    y = m1*x + k1;
    return Point((int)x,(int)y);
  }

  // Caso General
  m1 = (double)(b.y - a.y)/(b.x - a.x);
  m2 = (double)(d.y - c.y)/(d.x - c.x);
  k1 = a.y - m1*a.x;
  k2 = c.y - m2*c.x;

  x = (k2 - k1)/(m1 - m2);
  y = m1*x + k1;
  return Point((int)x,(int)y);
}

// WARNING: Primero usar las funciones de intersección
void inter_pt( Point a, Point b, Point c, Point d, double& x, double& y ) {
  double m1, m2, k1, k2;

  // Caso: (a,b) vertical
  if ( a.x == b.x ) {
    x = a.x;
    m2 = (double)(d.y - c.y)/(d.x - c.x);
    k2 = c.y - m2*c.x;
    y = m2*x + k2;
    return;
  }

  // Caso: (c,d) vertical
  if ( c.x == d.x ) {
    x = c.x;
    m1 = (double)(b.y - a.y)/(b.x - a.x);
    k1 = a.y - m1*a.x;
    y = m1*x + k1;
    return;
  }

  // Caso General
  m1 = (double)(b.y - a.y)/(b.x - a.x);
  m2 = (double)(d.y - c.y)/(d.x - c.x);
  k1 = a.y - m1*a.x;
  k2 = c.y - m2*c.x;

  x = (k2 - k1)/(m1 - m2);
  y = m1*x + k1;
  return;
}

// Poly

bool is_inside_convex( const Poly& poly, Point pt ) {

  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( !is_left(poly[i],poly[i+1],pt) ) return false;
  }
  return true;
}

bool is_insideon_convex( const Poly& poly, Point pt ) {

  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( !is_lefton(poly[i],poly[i+1],pt) ) return false;
  }
  return true;
}

bool is_properint( const Poly& poly, const Segment& seg ) {
  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( is_properint(poly[i],poly[i+1],seg.a,seg.b) ) {
      return true;
    }
  }
  return false;
}

int is_propercnt( const Poly& poly, const Segment& seg ) {
  int cnt = 0;

  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( is_properint(poly[i],poly[i+1],seg.a,seg.b) ) {
      cnt += 1;
    }
  }
  return cnt;
}

bool is_simple( const Poly& poly ) {

  for ( unsigned i=0; i<poly.size()-1; i+=1 ) {
    for ( unsigned j=i+1; j<poly.size(); j+=1 ) {
      if ( is_properint(poly[i],poly[i+1],poly[j],poly[j+1]) ) {
        return false;
      }
    }
  }
  return true;
}

bool is_autoint( const Poly& poly ) {
  return !is_simple(poly);
}

// Determina si el rayo horizontal (-inf,c) se intersecta con
// el segmento a-b
bool is_rayinter( Point a, Point b, Point c ) {

  // Caso 1
  if ( a.y < c.y && c.y < b.y ) {
    if ( area2(a,b,c) <= 0 ) return true;
    return false;
  }

  //Caso 2
  if ( b.y < c.y && c.y < a.y ) {
    if ( area2(a,b,c) >= 0 ) return true;
    return false;
  }

  return false;
}

bool is_inside_noconvex( const Poly& poly, Point pt ) {
  int cnt = 0; // cuenta de intersecciones

  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( is_rayinter(poly[i],poly[i+1],pt) ) cnt += 1;
    if ( poly[i].y == pt.y && poly[i].x <= pt.x ) cnt += 1;
  }

  //if ( cnt % 2 ) return true;
  if ( cnt & 1 ) return true;
  return false;
}

bool is_convex( const Poly& poly ) {
  for ( unsigned i=0; i<poly.size(); i+=1 ) {
    if ( !is_lefton(poly[i],poly[i+1],poly[i+2]) ) {
      return false;
    }
  }
  return true;
}

double area( const Poly& poly) {
  double sum = 0.0;
  for ( unsigned i=1; i<poly.size()-1; i+=1 ) {
    sum += area(poly[0],poly[i],poly[i+1]);
  }
  return sum;
}

bool is_ahead( Vector a, Vector b, Vector d ) {
  if ( dot((a-b),d) > 0 ) return true;
  return false;
}

void extremev( const Poly& poly, Vector d, Vertex& vmin, Vertex& vmax ) {
  Vertex tmin = poly[0];
  Vertex tmax = poly[0];

  for ( unsigned i=1; i<poly.size(); i+=1 ) {
    if ( is_ahead(poly[i],tmax,d) ) tmax = poly[i];
    if ( is_ahead(tmin,poly[i],d) ) tmin = poly[i];
  }

  vmin = tmin;
  vmax = tmax;
}

void extremev( const Poly& poly, Vector d, int& imin, int& imax ) {
  int tmin = 0;
  int tmax = 0;

  for ( unsigned i=1; i<poly.size(); i+=1 ) {
    if ( is_ahead(poly[i],poly[tmax],d) ) tmax = i;
    if ( is_ahead(poly[tmin],poly[i],d) ) tmin = i;
  }

  imin = tmin;
  imax = tmax;
}

void extremev( const PointSet& pset, Vector d, int& imin, int& imax ) {
  int tmin = 0;
  int tmax = 0;

  for ( unsigned i=1; i<pset.size(); i+=1 ) {
    if ( is_ahead(pset[i],pset[tmax],d) ) tmax = i;
    if ( is_ahead(pset[tmin],pset[i],d) ) tmin = i;
  }

  imin = tmin;
  imax = tmax;
}

bool psplit( const Poly& poly, int v1, int v2, PolyCh& c1, PolyCh& c2 ) {
  PolyCh C1, C2;
  int ind1 = poly.realind(v1);
  int ind2 = poly.realind(v2);

  if ( ind1 == ind2 ) return false;

  int i = ind1;
  while ( i != ind2 ) {
    C1.push_back(poly[i]);
    i = poly.realind(i+1);
  }
  C1.push_back(poly[ind2]);

  i = ind2;
  while ( i != ind1 ) {
    C2.push_back(poly[i]);
    i = poly.realind(i+1);
  }
  C2.push_back(poly[ind1]);

  c1 = C1;
  c2 = C2;
  return true;
}

bool is_monotone( const Poly& poly, Line ln ) {
  int i1, i2;
  PolyCh C1, C2;

  extremev(poly, ln.b-ln.a, i1, i2);
  psplit(poly,i1,i2,C1,C2);
  //return is_monotone(C1,ln) && is_monotone(C2,ln);

  if ( !is_monotone(C1,ln) ) return false;
  if ( !is_monotone(C2,ln) ) return false;
  return true;
}

void tangents( const Poly& poly, Point pt, int& i1, int& i2 ) {

  bool s = false;
  for ( int i=0; i<(int)poly.size(); i+=1 ) {
    bool a = is_lefton(poly[i-1],poly[i],pt);
    bool b = is_lefton(poly[i],poly[i+1],pt);
    if ( (a && !b) || (!a && b) ) {
      if ( s == false ) {
        i1 = i;
        s = true;
      }
      else {
        i2 = i;
        return;
      }
    }
  }
}


Poly incremental_hull( PointSet pset ) {

  // Obtener la semilla
  Poly hull;
  if ( area2(pset[0],pset[1],pset[2]) > 0 ) {
    hull.push(pset[0]);
    hull.push(pset[1]);
    hull.push(pset[2]);
  }
  else {
    hull.push(pset[0]);
    hull.push(pset[2]);
    hull.push(pset[1]);
  }

  for ( unsigned i=3; i<pset.size(); i+=1 ) {

    // Elegir p
    if ( is_inside_convex(hull,pset[i]) ) continue;

    // Tangentes
    int k1, k2;
    tangents(hull,pset[i],k1,k2);

    // Dividir en cadenas C1 y C2
    PolyCh C1, C2;
    psplit(hull,k1,k2,C1,C2);

    // Determinar Cc y Cr
    C1.push_back(pset[i]);
    C2.push_back(pset[i]);

    Poly hull1(C1);
    Poly hull2(C2);

    bool conv1 = is_convex( hull1 );
    bool conv2 = is_convex( hull2 );

    // Caso 1
    if ( conv1 && !conv2 ) {
      hull = hull1;
      continue;
    }

    // Caso 2
    if ( !conv1 && conv2 ) {
      hull = hull2;
      continue;
    }

    // Caso 3
    if ( conv1 && conv2 ) {
      if ( hull1.size() == 3 ) {
        hull = hull2;
        continue;
      }
      hull = hull1;
    }
  }

  return hull;
}

// === Graham ===

int get_p0( PointSet pset ) {
  int k = 0;
  for ( unsigned i=1; i<pset.size(); i+=1 ) {

    if ( pset[i].y < pset[k].y ) {
      k = i;
      continue;
    }

    if ( pset[i].y != pset[k].y ) continue;

    if ( pset[i].x < pset[k].x ) k = i;
  }

  return k;
}

AngleCmp::AngleCmp( const Point& p0 ) : p0(p0) { }

bool AngleCmp::operator()( const Point& si, const Point& sk ) {
  if ( si == p0 ) return true;
  if ( sk == p0 ) return false;
  if ( area2(p0,si,sk) < 0 ) return false;
  return true;
}

void angle_sort( PointSet& pset ) {
  int k = get_p0(pset);
  AngleCmp acmp(pset[k]);

  sort(pset.begin(),pset.end(),acmp);
}

Poly graham_hull( PointSet pset ) {
  PolyCh stack;
  angle_sort(pset);

  stack.push_back(pset[0]); // p0
  stack.push_back(pset[1]);

  unsigned i1, i2;
  for ( unsigned i=2; i<pset.size(); i+=1 ) {
    i1 = stack.size()-1;
    i2 = stack.size()-2;
    while ( is_right( stack[i2],stack[i1],pset[i]) ) {
      stack.pop_back();
      i1 -= 1;
      i2 -= 1;
    }
    stack.push_back(pset[i]);
  }

  return Poly(stack);
}

unsigned most_forward(const PointSet& pset, Vector w)
{
  int mf = 0;

  for(unsigned i = 1; i < pset.size(); i+=1)
  {
    if(is_ahead(pset[i], pset[mf],w)) mf = i;
  }
  return (unsigned)mf;
}
void init_line(const PointSet& pset, Point& a, Point& b)
{
  unsigned ta = 0;//bigger
  unsigned tb = 0;//lower
  for(unsigned i=1; i < pset.size(); i+=1)
  {
    if(pset[i].x < pset[ta].x) ta = i;
    else if (pset[i].x == pset[ta].x)
    {
    if(pset[i].y < pset[ta].y) ta = i;
  }
    if(pset[i].x > pset[tb].x) tb = i;
    else if(pset[i].x == pset[tb].x)
    {
    if(pset[i].y > pset[tb].y) tb = i;
  }
  }
  a = pset[ta];
  b = pset[tb];
}


void init_sets(const PointSet& pset, Point a, Point b, PointSet& lset, PointSet& rset)
{
  PointSet right;
  PointSet left;

  for(unsigned i = 0; i<pset.size(); i+=1)
  {
    if(is_left(a, b, pset[i])) {
      left.push_back(pset[i]);
      continue;
    }
    if(is_right(a, b, pset[i]))
    {
      right.push_back(pset[i]);
      continue;
    }
  }
  lset = left;
  rset = right;
}

PointSet subset(const PointSet& pset, Point a, Point b, Point c)
{
  PointSet sub;
  for(unsigned i=0; i<pset.size(); i+=1)
  {
    if(is_right(a,b,pset[i]))
    {
      sub.push_back(pset[i]);
      continue;
    }
    if(is_right(b,c, pset[i]))
    {
      sub.push_back(pset[i]);
      continue;
    }
    if(is_right(c,a,pset[i]))
    {
      sub.push_back(pset[i]);
      continue;
    }
  }
  return sub; 
}


Poly qhull(const PointSet& pset)
{
  Point a, b;
  PointSet top;
  PointSet bot;
  init_line(pset,a,b);
  init_sets(pset,a,b,top,bot);

  PolyCh pc;
  pc = pc + a;
  pc = pc + qhcall(top,a,b);
  pc = pc + b;
  pc = pc + qhcall(bot, b, a);

  return Poly(pc);
}

PolyCh qhcall(const PointSet& pset, Point a, Point b)
{
  PolyCh ret;
  if(pset.size()==0) return ret;
  // Vector v = b - a
  Vector w = Vector(b.y - a.y, a.x - b.x);  
  //  Obtener el índice del punto más alejado en dirección w
  unsigned i = most_forward(pset,w);
  Point c = pset[i];


  //  Creando un subconjunto que esta fuera del triangulo a,b y c
  if(is_right(a,b,c))
  {
    PointSet sub = subset(pset,a,b,c);

    ret = ret + qhcall(sub,b,c);
    ret = ret + c;
    ret = ret + qhcall(sub,c,a);
    return ret;
  }
  return ret;
}

