#include <iostream>
#include <vector>
#include "lodepng.h"
#include "geocomp.hpp"

using namespace std;

int main() {
  PointSet pset = generator_genpos(30, 0,800, 0, 600);
  Poly hull = incremental_hull(pset);

  return 0;
}

