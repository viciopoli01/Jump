#ifndef TYPE_H
#define TYPE_H
#include <SDL.h>

struct Color {
  Uint8 r = 0xFF;
  Uint8 g = 0xFF;
  Uint8 b = 0xFF;
  Uint8 a = 0xFF;
  Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : a(a), r(r), g(g), b(b){};
  Color(){};
};

typedef struct Colors {
  Color Blue = Color(0x00, 0x00, 0xFF, 0xFF);
  Color Red = Color(0xFF, 0x00, 0x00, 0xFF);
  Color Green = Color(0x00, 0xFF, 0x00, 0xFF);
} Colors ;

#endif