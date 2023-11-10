#include "color.hpp"

Color::Color(): r(0), g(0), b(0), a(0) {}

Color::Color( uchar g, uchar a ): r(g), g(g), b(g), a(a) { }

Color::Color( uchar r, uchar g, uchar b, uchar a ):
   r(r), g(g), b(b), a(a) { }

Color::Color( const Name& colorname ) {
   a = 255;
   switch( colorname ) {
      case Name::BLACK:
         r = 0;
         g = 0;
         b = 0;
         break;
     case Name::GRAY:
         r = 128;
         g = 128;
         b = 128;
         break;
     case Name::SILVER:
         r = 192;
         g = 192;
         b = 192;
         break;
     case Name::WHITE:
         r = 255;
         g = 255;
         b = 255;
         break;
     case Name::MAROON:
         r = 128;
         g = 0;
         b = 0;
         break;
     case Name::RED:
         r = 255;
         g = 0;
         b = 0;
         break;
     case Name::OLIVE:
         r = 128;
         g = 128;
         b = 0;
         break;
     case Name::YELLOW:
         r = 255;
         g = 255;
         b = 0;
         break;
     case Name::GREEN:
         r = 0;
         g = 128;
         b = 0;
         break;
     case Name::LIME:
         r = 0;
         g = 255;
         b = 0;
         break;
     case Name::TEAL:
         r = 0;
         g = 128;
         b = 128;
         break;
     case Name::AQUA:
     case Name::CYAN:
         r = 0;
         g = 255;
         b = 255;
         break;
     case Name::NAVY:
         r = 0;
         g = 0;
         b = 128;
         break;
     case Name::BLUE:
         r = 0;
         g = 0;
         b = 255;
         break;
     case Name::PURPLE:
         r = 128;
         g = 0;
         b = 128;
         break;
     case Name::FUCHSIA:
     case Name::MAGENTA:
         r = 255;
         g = 0;
         b = 255;
         break;
     case Name::CLEAR:
     default:
         r = 0;
         g = 0;
         b = 0;
         a = 0;
    }
}

bool Color::operator==( const Color& other ) const {
   if ( r != other.r ) return false;
   if ( g != other.g ) return false;
   if ( b != other.b ) return false;
   if ( a != other.a ) return false;
   return true;
}

bool Color::operator!=( const Color& other ) const {
   if ( r != other.r ) return true;
   if ( g != other.g ) return true;
   if ( b != other.b ) return true;
   if ( a != other.a ) return true;
   return false;
}

std::ostream& operator<<( std::ostream& os, const Color& color ) {
   os << "<";
   os << (int)color.r << ",";
   os << (int)color.g << ",";
   os << (int)color.b << ",";
   os << (int)color.a;
   os << ">";
   return os;
}

