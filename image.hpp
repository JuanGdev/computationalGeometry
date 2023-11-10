#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include "lodepng.h"
#include "color.hpp"

class Image {
   public:
      Image();
      Image( bool yinv=false );
      Image( unsigned width, unsigned height, bool yinv=false );
      Image( const std::string filename, bool yinv=false );
      Image( const char* filename, bool yinv=false );

      unsigned width() const;
      unsigned height() const;
      unsigned size() const;

      bool yinvert() const;
      void yinvert( bool invert );

      const Color& at( unsigned x, unsigned y ) const;
      const Color& operator()( unsigned x, unsigned y ) const;
      const Color& at( unsigned n ) const;
      const Color& operator()( unsigned n ) const;

      Color& at( unsigned x, unsigned y );
      Color& operator()( unsigned x, unsigned y );
      Color& at( unsigned n );
      Color& operator()( unsigned n );

      void px( int x, int y, const Color& color );
      Color px( int x, int y );

      bool write( const std::string& filename ) const;
      bool write( const char* filename ) const;

      bool read( const std::string& filename );
      bool read( const char* filename );

   private:
      unsigned m_width;
      unsigned m_height;
      unsigned m_size;
      bool     m_yinv;
      std::vector<Color> m_pixmap;
};

#endif

