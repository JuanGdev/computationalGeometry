#include "draw.hpp"


Draw::Draw( Image& image )
   : m_im(&image), m_fg(Color::Name::BLACK), m_bg(Color::Name::WHITE) { }

Draw::Draw( Image& image, const Color& fg, const Color& bg )
   : m_im(&image), m_fg(fg), m_bg(bg) { }

void Draw::fg( const Color& color ) {
   m_fg = color;
}

void Draw::bg( const Color& color ) {
   m_bg = color;
}

Color Draw::fg() const {
   return m_fg;
}

Color Draw::bg() const {
   return m_bg;
}

void Draw::clear( const Color& color ) {
   for ( size_t n=0; n<m_im->size(); n+=1 ) m_im->at(n) = color;
}

void Draw::clear() {
   for ( size_t n=0; n<m_im->size(); n+=1 ) m_im->at(n) = m_bg;
}

void Draw::pixel( int x, int y, const Color& color ) {
   m_im->px(x,y,color);
}

void Draw::pixel( int x, int y ) {
   m_im->px(x,y,m_fg);
}

void Draw::vruler( int x, const Color& color ) {
   for ( unsigned y=0; y<m_im->height(); y+=1 ) m_im->px(x,y,color);
}

void Draw::vruler( int x ) {
   for ( unsigned y=0; y<m_im->height(); y+=1 ) m_im->px(x,y,m_fg);
}

void Draw::hruler( int y, const Color& color ) {
   for ( unsigned x=0; x<m_im->width(); x+=1 ) m_im->px(x,y,color);
}

void Draw::hruler( int y ) {
   for ( unsigned x=0; x<m_im->width(); x+=1 ) m_im->px(x,y,m_fg);
}

void Draw::line( int x0, int y0, int x1, int y1, const Color& color ) {

   if ( abs(y1 - y0) < abs(x1 - x0) ) {
      if ( x0 < x1 ) line_low(x0,y0,x1,y1,color);
      else line_low(x1,y1,x0,y0,color);
   }
   else {
      if ( y0 < y1 ) line_high(x0,y0,x1,y1,color);
      else line_high(x1,y1,x0,y0,color);
   }
}

void Draw::line( int x0, int y0, int x1, int y1 ) {
   line(x0,y0,x1,y1,m_fg);
}

void Draw::vline( int x, int y0, int y1, const Color& color ) {
   int a = (y0 < y1) ? y0 : y1;
   int b = (y0 < y1) ? y1 : y0;
   for ( int y=a; y<=b; y+=1 ) m_im->px(x,y,color);
}

void Draw::vline( int x, int y0, int y1 ) {
   vline(x,y0,y1,m_fg);
}

void Draw::hline( int x0, int x1, int y, const Color& color ) {
   int a = (x0 < x1) ? x0 : x1;
   int b = (x0 < x1) ? x1 : x0;
   for ( int x=a; x<=b; x+=1 ) m_im->px(x,y,color);
}

void Draw::hline( int x0, int x1, int y ) {
   hline(x0,x1,y,m_fg);
}

// Draws low lines (m < 1)
void Draw::line_low( int x0, int y0, int x1, int y1, const Color& color ) {
   int dx = x1 - x0;
   int dy = y1 - y0;

   // switch drawing direction if y0 > y1
   int yi = 1;
   if ( dy < 0 ) {
      yi = -1;
      dy = -dy;
   }

   int dx2 = dx << 1;
   int dy2 = dy << 1;
   int D = dy2 - dx;
   int y = y0;

   for ( int x=x0; x<=x1; x+=1 ) {
      m_im->px(x,y,color);
      if ( D > 0 ) {
         y += yi;
         D -= dx2;
      }
      D += dy2;
   }
}

// Draws high lines (m > 1)
void Draw::line_high( int x0, int y0, int x1, int y1, const Color& color ) {
   int dx = x1 - x0;
   int dy = y1 - y0;

   // switch drawing direction if x0 > x1
   int xi = 1;
   if ( dx < 0 ) {
      xi = -1;
      dx = -dx;
   }

   int dx2 = dx << 1;
   int dy2 = dy << 1;
   int D = dx2 - dy;
   int x = x0;

   for ( int y=y0; y<=y1; y+=1 ) {
      m_im->px(x,y,color);
      if ( D > 0 ) {
         x += xi;
         D -= dy2;
      }
      D += dx2;
   }
}

void Draw::box( int x0, int y0, int x1, int y1, const Color& color ) {
   int x_0 = ( x0 < x1 ) ? x0 : x1;
   int x_1 = ( x0 < x1 ) ? x1 : x0;
   int y_0 = ( y0 < y1 ) ? y0 : y1;
   int y_1 = ( y0 < y1 ) ? y1 : y0;

   for ( int x=x_0; x<=x_1; x+=1 ) m_im->px(x,y_0,color);
   for ( int x=x_0; x<=x_1; x+=1 ) m_im->px(x,y_1,color);
   for ( int y=y_0; y<=y_1; y+=1 ) m_im->px(x_0,y,color);
   for ( int y=y_0; y<=y_1; y+=1 ) m_im->px(x_1,y,color);
}

void Draw::box( int x0, int y0, int x1, int y1 ) {
   box(x0,y0,x1,y1,m_fg);
}

void Draw::fbox( int x0, int y0, int x1, int y1, const Color& color ) {
   int x_0 = ( x0 < x1 ) ? x0 : x1;
   int x_1 = ( x0 < x1 ) ? x1 : x0;
   int y_0 = ( y0 < y1 ) ? y0 : y1;
   int y_1 = ( y0 < y1 ) ? y1 : y0;

   for ( int y=y_0; y<=y_1; y+=1 ) {
      for ( int x=x_0; x<=x_1; x+=1 ) {
         m_im->px(x,y,color);
      }
   }
}

void Draw::fbox( int x0, int y0, int x1, int y1 ) {
   box(x0,y0,x1,y1,m_fg);
}

void Draw::circle2( int x0, int y0, int r, const Color& color ) {

   //int rr = r*r;
   //int rr = (r+1)*(r+1);
   int x = r;
   int y = 0;

   while ( y <= x ) {
      m_im->px(x0+x,y0+y,color);
      m_im->px(x0+x,y0-y,color);
      m_im->px(x0-x,y0+y,color);
      m_im->px(x0-x,y0-y,color);
      m_im->px(x0+y,y0+x,color);
      m_im->px(x0+y,y0-x,color);
      m_im->px(x0-y,y0+x,color);
      m_im->px(x0-y,y0-x,color);
      y += 1;
      //if ( x*x + y*y >= rr ) x -= 1;
      if ( 4*(x*x + y*y) > 4*r*r + 2*r + 1 ) x -= 1;
      //if ( 16*(x*x + y*y) >= 16*r*r + 4*r + 1 ) x -= 1;
   }
}

void Draw::circle( int x0, int y0, int r, const Color& color ) {

   int x = r;
   int y = 0;
   int E = -(r << 2) - 1;

   while ( y <= x ) {
      m_im->px(x0+x,y0+y,color);
      m_im->px(x0+x,y0-y,color);
      m_im->px(x0-x,y0+y,color);
      m_im->px(x0-x,y0-y,color);
      m_im->px(x0+y,y0+x,color);
      m_im->px(x0+y,y0-x,color);
      m_im->px(x0-y,y0+x,color);
      m_im->px(x0-y,y0-x,color);
      y += 1;
      if ( E > 0 ) {
         x -= 1;
         E += (y - x + 1) << 3;
      }
      else E += ((y << 1) + 1) << 2;
   }
}

void Draw::circle( int x0, int y0, int r ) {
   circle(x0,y0,r,m_fg);
}

void Draw::circle_mid( int x0, int y0, int r, const Color& color ) {

   // Initial condition
   int x = r;
   int y = 0;
   int E = 3 - (r << 1);
   //int E = 3 - 2*r;

   while ( y <= x ) {
      m_im->px(x0+x,y0+y,color);
      m_im->px(x0+x,y0-y,color);
      m_im->px(x0-x,y0+y,color);
      m_im->px(x0-x,y0-y,color);

      m_im->px(x0+y,y0+x,color);
      m_im->px(x0+y,y0-x,color);
      m_im->px(x0-y,y0+x,color);
      m_im->px(x0-y,y0-x,color);

      // Update:
      // if E >  0: E = E + 2 ( 5 − 2 x + 2 y )
      // if E <= 0: E = E + 2 ( 3 + 2 y )

      y += 1;
      if ( E > 0 ) {
         x -= 1;
         E += (5 - (x << 1) + (y << 1) ) << 1;
      }
      else E += (3 + (y << 1) ) << 1;
   }
}

void Draw::fcircle2( int x0, int y0, int r, const Color& color ) {

   //int rr = r*r;
   //int rr = (r+1)*(r+1);
   for ( int y=-r; y<=r; y+=1 ) {
      for ( int x=-r; x<=r; x+=1 ) {
         //if ( x*x + y*y < rr ) m_im->px(x0+x,y0+y,color);
         if ( 4*(x*x + y*y) <= 4*r*r + 2*r + 1 ) m_im->px(x0+x,y0+y,color);
         //if ( 16*(x*x + y*y) < 16*r*r + 4*r + 1 ) m_im->px(x0+x,y0+y,color);
      }
   }
}

void Draw::fcircle( int x0, int y0, int r, const Color& color ) {

   int x = r;
   int y = 0;
   int E = -(r << 2) - 1;

   while ( y <= x ) {
      hline(x0-x,x0+x,y0+y,color);
      hline(x0-x,x0+x,y0-y,color);
      hline(x0-y,x0+y,y0+x,color);
      hline(x0-y,x0+y,y0-x,color);

      y += 1;
      if ( E > 0 ) {
         x -= 1;
         E += (y - x + 1) << 3;
      }
      else E += ((y << 1) + 1) << 2;
   }
}

void Draw::fcircle( int x0, int y0, int r ) {
   fcircle(x0,y0,r,m_fg);
}

void Draw::fellipse( int x0, int y0, int rx, int ry, const Color& color ) {

   for ( int y=-ry; y<=ry; y+=1 ) {
      for ( int x=-rx; x<=rx; x+=1 ) {
         if ( rx < ry ) {
            if ( (x*ry/rx)*(x*ry/rx) + y*y < ry ) m_im->px(x0+x,y0+y,color);
         }
         else {
            if ( x*x + (y*rx/ry)*(y*rx/ry) < rx ) m_im->px(x0+x,y0+y,color);
         }
      }
   }
}

