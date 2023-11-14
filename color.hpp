#ifndef COLOR_HPP
#define COLOR_HPP

#include <ostream>

typedef unsigned char uchar;

struct Color {

   enum class Name { CLEAR, BLACK, GRAY, SILVER, WHITE, MAROON, RED, OLIVE,
                     YELLOW, GREEN, LIME, TEAL, AQUA, CYAN, NAVY, BLUE,
                     PURPLE, FUCHSIA, MAGENTA };

   Color();

   Color( uchar g, uchar a=255 );

   Color( uchar r, uchar g, uchar b, uchar a=255 );

   Color( const Name& colorname );

   bool operator==( const Color& other ) const;
   bool operator!=( const Color& other ) const;

   uchar r;
   uchar g;
   uchar b;
   uchar a;
};

std::ostream& operator<<( std::ostream& os, const Color& color );

#endif

