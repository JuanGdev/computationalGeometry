#ifndef DRAW_HPP
#define DRAW_HPP

#include <iostream>
#include "image.hpp"
#include "color.hpp"

typedef unsigned int uint;

class Draw {
   public:
      Draw( Image& image );
      Draw( Image& image, const Color& fg, const Color& bg );
      void fg( const Color& color );
      void bg( const Color& color );
      Color fg() const;
      Color bg() const;
      void clear( const Color& color );
      void clear();
      void pixel( int x, int y, const Color& color );
      void pixel( int x, int y );
      void vruler( int x, const Color& color );
      void vruler( int x );
      void hruler( int y, const Color& color );
      void hruler( int y );
      void line( int x0, int y0, int x1, int y1, const Color& color );
      void line( int x0, int y0, int x1, int y1 );

      // Vertical and horizontal line segments
      void vline( int x, int y0, int y1, const Color& color );
      void vline( int x, int y0, int y1 );
      void hline( int x0, int x1, int y, const Color& color );
      void hline( int x0, int x1, int y );

      void box( int x0, int y0, int x1, int y1, const Color& color );
      void box( int x0, int y0, int x1, int y1 );

      void fbox( int x0, int y0, int x1, int y1, const Color& color );
      void fbox( int x0, int y0, int x1, int y1 );

      void circle( int x0, int y0, int r, const Color& color );
      void circle2( int x0, int y0, int r, const Color& color );
      void circle( int x0, int y0, int r );
      void circle_mid( int x0, int y0, int r, const Color& color );

      void fcircle( int x0, int y0, int r, const Color& color );
      void fcircle2( int x0, int y0, int r, const Color& color );
      void fcircle( int x0, int y0, int r );

      void fellipse( int x0, int y0, int rx, int ry, const Color& color );

   private:
      Image *m_im;
      Color m_fg;
      Color m_bg;

      void line_low( int x0, int y0, int x1, int y1, const Color& color );
      void line_high( int x0, int y0, int x1, int y1, const Color& color );
};

#endif

