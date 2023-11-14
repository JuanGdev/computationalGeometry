#include "image.hpp"


Image::Image(): m_width(0), m_height(0), m_size(0), m_yinv(false) { }

Image::Image( bool yinv ): m_width(0), m_height(0), m_size(0), m_yinv(yinv) { }

Image::Image( unsigned width, unsigned height, bool yinv ):
   m_width(width), m_height(height), m_size(width*height), m_yinv(yinv)
{
   m_pixmap.reserve(m_size);
   m_pixmap.resize(m_size);
}

Image::Image( const std::string filename, bool yinv ): Image(yinv) {
   read(filename);
}

Image::Image( const char* filename, bool yinv ): Image(yinv) {
   read(filename);
}

unsigned Image::width() const {
   return m_width;
}

unsigned Image::height() const {
   return m_height;
}

unsigned Image::size() const {
   return m_size;
}

bool Image::yinvert() const {
   return m_yinv;
}

void Image::yinvert( bool invert ) {
   m_yinv = invert;
}

const Color& Image::at( unsigned x, unsigned y ) const {
   return m_pixmap[m_width*y+x];
}

const Color& Image::operator()( unsigned x, unsigned y ) const {
   return m_pixmap[m_width*y+x];
}

const Color& Image::at( unsigned n ) const {
   return m_pixmap[n];
}

const Color& Image::operator()( unsigned n ) const {
   return m_pixmap[n];
}

Color& Image::at( unsigned x, unsigned y ) {
   return m_pixmap[m_width*y+x];
}

Color& Image::operator()( unsigned x, unsigned y ) {
   return m_pixmap[m_width*y+x];
}

Color& Image::at( unsigned n ) {
   return m_pixmap[n];
}

Color& Image::operator()( unsigned n ) {
   return m_pixmap[n];
}

void Image::px( int x, int y, const Color& color ) {
   if ( x < 0 || x >= (int)m_width ) return;
   if ( y < 0 || y >= (int)m_width ) return;
   if ( m_yinv ) m_pixmap[m_width*(m_height-y-1)+x] = color;
   else m_pixmap[m_width*y+x] = color;
}

Color Image::px( int x, int y ) {
   if ( x < 0 || x >= (int)m_width ) return Color::Name::CLEAR;
   if ( y < 0 || y >= (int)m_width ) return Color::Name::CLEAR;
   if ( m_yinv ) return m_pixmap[m_width*(m_height-y-1)+x];
   return m_pixmap[m_width*y+x];
}

bool Image::write( const std::string& filename ) const {
   return write(filename.c_str());
}

bool Image::write( const char* filename ) const {
   std::vector<unsigned char> raw;

   raw.reserve(m_size);
   for ( unsigned i=0; i<m_size; i+=1 ) {
      raw.push_back(m_pixmap[i].r);
      raw.push_back(m_pixmap[i].g);
      raw.push_back(m_pixmap[i].b);
      raw.push_back(m_pixmap[i].a);
   }

   unsigned error = lodepng::encode(filename, raw, m_width, m_height);
   if ( error ) return false;
   return true;
}

bool Image::read( const std::string& filename ) {
   return read(filename.c_str());
}

bool Image::read( const char* filename ) {
   std::vector<unsigned char> raw;
   unsigned width, height;

   unsigned error = lodepng::decode(raw, width, height, filename);
   if ( error ) return false;

   // pixel formating
   m_width = width;
   m_height = height;
   m_size = width*height;
   m_pixmap.reserve(m_size);

   for ( unsigned i=0; i<4*m_size; i+=4 ) {
      m_pixmap.push_back( Color(raw[i],raw[i+1],raw[i+2],raw[i+3]) );
   }

   return true;
}

