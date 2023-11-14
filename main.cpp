#include <iostream>
#include <string>
#include "geocomp.hpp"
#include "draw.hpp"
#include "color.hpp"
#define ME 10


Poly qhull(const PointSet& pset)
{
  Image im(400,300);
  Draw draw(im);
  draw.clear(Color::Name::WHITE);
  int cnt = 0;
  for(unsigned i = 0; i <pset.size(); i+=1)
  {
    draw.circle(pset[i].x, pset[i].y,2,Color::Name::WHITE);
  }

  Point a, b;
  PointSet top;
  PointSet bot;
  init_line(pset,a,b);
  draw.fcircle(a.x,a.y,2,Color::Name::GREEN);
  draw.fcircle(b.x,b.y,2,Color::Name::GREEN);
  init_sets(pset,a,b,top,bot);

  PolyCh pc;
  pc = pc + a;
  pc = pc + qhcall(bot,a,b);
  pc = pc + b;
  pc = pc + qhcall(top, b, a);
  
  im.write(std::string("qhull_" + std::to_string(cnt) + ".png"));
  cnt+=1;

  return Poly(pc);
}

PolyCh qhcall(const PointSet& pset, Point a, Point b)
{
  PolyCh ret;
  if(pset.size()==0) return ret;
  // Vector v = b - a
  Vector w = Vector(a.y - b.y, b.x - a.x);  
  //  Obtener el índice del punto más alejado en dirección w
  unsigned i = most_forward(pset,w);
  Point c = pset[i];


  //  Creando un subconjunto que esta fuera del triangulo a,b y c
  if(is_left(a,b,c))
  {
    PointSet sub = subset(pset,a,b,c);

    ret = ret + qhcall(sub,b,c);
    ret = ret + c;
    ret = ret + qhcall(sub,c,a);
    return ret;
  }
  return ret;
}


int main (){
  Image img(400,300);
  Draw draw(img);
  draw.clear(Color::Name::AQUA);

  PointSet pset = generator_genpos(10, 0+ME, 400-ME, 0+ME, 300-ME);
  Poly hull = qhull(pset);
  for(unsigned i = 0; i < hull.size(); i+= 1)
  {
    draw.line(hull[i].x, hull[i].y, hull[i+1].x, hull[i+1].y,
              Color::Name::FUCHSIA);
  }
  TArray tri = ear_clipping((hull));
  for(unsigned i = 0; i < tri.size(); i+=1)
  {
    draw.line(tri[i].a.x, tri[i].a.y, tri[i].b.x, tri[i].b.y, Color::Name::BLUE);
    draw.line(tri[i].b.x, tri[i].b.y, tri[i].c.x, tri[i].c.y, Color::Name::BLUE);
    draw.line(tri[i].c.x, tri[i].c.y, tri[i].a.x, tri[i].a.y, Color::Name::BLUE);
  }

  img.write("qhull.png");

  return 0;
}
