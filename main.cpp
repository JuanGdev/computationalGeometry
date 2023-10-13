#include <iostream>

#include <vector>

#include "lodepng.h"
#include "geocomp.hpp"

using namespace std;


int main() {

   Poly poly;
   poly.push(Vertex(1,2));
   poly.push(Vertex(2,1));
   poly.push(Vertex(3,1));
   poly.push(Vertex(4,3));
   poly.push(Vertex(3,3));
   poly.push(Vertex(2,3));

   Line ln(Point(2,1),Point(3,3));

   cout << "poly = " << poly << endl;

   PolyCh C1, C2;
   psplit(poly,1,4,C1,C2);
   cout << "C1 = " << C1 << endl;
   cout << "C2 = " << C2 << endl;
   if ( is_monotone(C1,ln) ) cout << "C1 = monótono" << endl;
   else cout << "C1 = NO monótono" << endl;
   if ( is_monotone(C2,ln) ) cout << "C2 = monótono" << endl;
   else cout << "C2 = NO monótono" << endl;

   if ( is_monotone(poly,ln) ) {
      cout << "El polígono es monótono" << endl;
   }
   else {
      cout << "El polígono NO es monótono" << endl;
   }

   return 0;
}
