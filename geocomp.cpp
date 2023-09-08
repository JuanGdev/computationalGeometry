#include "geocomp.hpp"

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

std::ostream& operator<<( std::ostream& os, const PolyCh& pc ) {
   os << pc[0];
   for ( unsigned i=1; i<pc.size(); i+=1 ) {
      os << "--" << pc[i];
   }
   return os;
}

Segment::Segment() { }

Segment::Segment( Point a, Point b ): a(a.x,a.y), b(b.x,b.y) { }

Segment::Segment( int x0, int y0, int x1, int y1 ): a(x0,y0), b(x1,y1) { }

int dot( Vector a, Vector b) {
   return a.x*b.x + a.y*b.y;
}
int distsqr(Point a, Point b)
{
  return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}
int dist(Point a, Point b)
{
  return (int)std::sqrt(distsqr(a,b));
}

double fdist(Point a, Point b){
  return std::sqrt(distsqr(a,b));
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
PointSet generator_genpos(
      unsigned N, int x0, int x1, int y0, int y1
) {
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

// Bloque 'while' de generator_genpos() usando banderas para salir de los ciclos
// anidados. El código extra que es necesario hace el bloque más confuso y
// difícil de leer. Este es uno de los pocos casos en que usar 'goto' está
// justificado.
//
// while ( set.size() < N ) {
//
//    pt.x = distx(generator);
//    pt.y = disty(generator);
//
//    bool flag = true;
//    for ( unsigned i=0; i<set.size()-1; i+=1 ) {
//       if ( flag == false ) break
//       for ( unsigned j=i+1; j<set.size(); j+=1 ) {
//          if ( is_colinear(set[i],set[j],pt)  {
//                flag = false;
//                break;
//          }
//       }
//    }
//
//    if ( flag == false ) continue;
//
//    // verificar si el punto pasa la prueba
//
//    set.push_back(pt);
//
// }

Point centroid( Point a, Point b, Point c ) {
   return ((a + b + c)/3);
}

Point middlept( Point a, Point b ) {
   return ((a + b)/2);
}

Point circ_center ( Point a, Point b, Point c ) {
   Point B = b - a;
   Point C = c - a;
   Point O;

   Point B2 = B * B;
   Point C2 = C * C;

   O.x = C.y*(B2.x + B2.y) - B.y*(C2.x + C2.y);
   O.y = B.x*(C2.x + C2.y) - C.x*(B2.x + B2.y) ;
   int D = 2*(B.x*C.y - B.y*C.x);

   //return Point( O.x/D + a.x, O.y/D + a.y );
   return O/D + a;
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

   //return Point( O.x/D + a.x, O.y/D + a.y );
   o = O/D + a;
   r = (int)std::sqrt(O.x*O.x + O.y*O.y);
}

double circ_radius ( Point o, Point v ) {
   return dist(o,v);
}

// double angle( Point a, Point b, Point c );


bool is_properint( Point a, Point b, Point c, Point d ) {
   if ( is_right(a,b,c) && is_right(a,b,d) ) return false;
   if ( is_left(a,b,c)  && is_left(a,b,d)  ) return false;
   if ( is_right(c,d,a) && is_right(c,d,b) ) return false;
   if ( is_left(c,d,a)  && is_left(c,d,b)  ) return false;
   return true;
}

//bool is_properint( Point a, Point b, Point c, Point d ) {
//
//   if ( ( (is_right(a,b,c) && is_left(a,b,d)) || \
//          (is_left(a,b,c) && is_right(a,b,d)) ) && \
//      (   (is_right(c,d,a) && is_left(c,d,b)) || \
//          (is_left(c,d,a) && is_right(c,d,b)) ) ) {
//      return true;
//   }
//   return false;
//}


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

// WARNING: Primero usar las funciones de intersección
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
void inter_pt( Point a, Point b, Point c, Point d, double& x, double& y ){
   double m1, m2, k1, k2;

   // Caso: (a,b) vertical 
   if (a.x == b.x ){
      x = a.x;
      m2 = (double)(d.y - c.y) / (d.x - c.x);
      k2 = c.y - m2*c.x;

      y = m2*x + k2; 
      return; 
   }
   // Caso: (c,d) vertical
   if ( c.x == d.x ){
      x = c.x;
      m1 = (double)(b.y - a.y) / (b.x - a.x);
      k1 = a.y - m1*a.x;

      y = m1*x + k1;
      return; 
   }

   // Caso: General
   m1 = (double)(b.y - a.y) / (b.x - a.x);
   m2 = (double)(d.y - c.y) / (d.x - c.x);
   k1 = a.y - m1*a.x;
   k2 = c.y - m2*c.x;

   x = (k2 - k1)/(m1 - m2);
   y = m1*x + k1;
}
