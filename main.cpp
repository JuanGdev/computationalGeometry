#include <iostream>
#include "lodepng.h"
#include "geocomp.hpp"

using namespace std;

int main()
{
  Polygon poly;
  poly.push(Vertex(500,300));
  poly.push(Vertex(700,100));
  poly.push(Vertex(300,100));
  poly.push(Vertex(100,300));
  poly.push(Vertex(300,500));
  poly.push(Vertex(700,500));

  unsigned width  = 800;
  unsigned height = 600;

  vector<unsigned char> image;

  for(unsigned y=0; y < height; y +=1)
  {
    for(unsigned x = 0; x < width; x +=1)
    {
      if(is_inside_noconvex(poly, Point(x,y)))
      {
        image.push_back(199);
        image.push_back(163);
        image.push_back(199);
        image.push_back(255);
        continue;
      }
      image.push_back(120);
      image.push_back(89);
      image.push_back(219);
      image.push_back(255);
    }
  }

  unsigned error = lodepng::encode("prueba.png", image, width,height);
  if(error) return 1;
  return 0;
}
