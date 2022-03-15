#ifndef _UTILS_HPP
#define _UTILS_HPP
#include <algorithm>

struct Vertex {
    float x, y, z;
    float r, g, b;
    Vertex(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z) {}
};

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface -> format -> BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


struct EdgeEquation {
  float a;
  float b;
  float c;
  bool tie;

  EdgeEquation(const Vertex &v0, const Vertex &v1)
  {
    a = v0.y - v1.y;
    b = v1.x - v0.x;
    c = - (a * (v0.x + v1.x) + b * (v0.y + v1.y)) / 2;
    tie = a != 0 ? a > 0 : b > 0;
  }

  /// Evaluate the edge equation for the given point.
  float evaluate(float x, float y)
  {
    return a * x + b * y + c;
  }

  /// Test if the given point is inside the edge.
  bool test(float x, float y)
  {
    return test(evaluate(x, y));
  }

  /// Test for a given evaluated value.
  bool test(float v)
  {
    return (v > 0 || v == 0 && tie);
  }
};


struct ParameterEquation {
  float a;
  float b;
  float c;

  ParameterEquation(
    float p0,
    float p1,
    float p2,
    const EdgeEquation &e0,
    const EdgeEquation &e1,
    const EdgeEquation &e2,
    float area)
  {
    float factor = 1.0f / (2.0f * area);

    a = factor * (p0 * e0.a + p1 * e1.a + p2 * e2.a);
    b = factor * (p0 * e0.b + p1 * e1.b + p2 * e2.b);
    c = factor * (p0 * e0.c + p1 * e1.c + p2 * e2.c);
  }

  /// Evaluate the parameter equation for the given point.
  float evaluate(float x, float y)
  {
    return a * x + b * y + c;
  }
};

void drawTriangle(SDL_Surface *m_surface, const Vertex& v0, const Vertex &v1, const Vertex &v2)
{
  // Compute triangle bounding box.
  int minX = std::min(std::min(v0.x, v1.x), v2.x);
  int maxX = std::max(std::max(v0.x, v1.x), v2.x);
  int minY = std::min(std::min(v0.y, v1.y), v2.y);
  int maxY = std::max(std::max(v0.y, v1.y), v2.y);

  // Compute edge equations.
  EdgeEquation e0(v0, v1);
  EdgeEquation e1(v1, v2);
  EdgeEquation e2(v2, v0);

  float area = 0.5 * (e0.c + e1.c + e2.c);
  
  // Check if triangle is backfacing.
  if (area < 0)
    return;

  ParameterEquation r(v0.r, v1.r, v2.r, e0, e1, e2, area);
  ParameterEquation g(v0.g, v1.g, v2.g, e0, e1, e2, area);
  ParameterEquation b(v0.b, v1.b, v2.b, e0, e1, e2, area);

  // Add 0.5 to sample at pixel centers.
  for (float x = minX + 0.5f, xm = maxX + 0.5f; x <= xm; x += 1.0f)
  for (float y = minY + 0.5f, ym = maxY + 0.5f; y <= ym; y += 1.0f)
  {
    if (e0.test(x, y) && e1.test(x, y) && e2.test(x, y))
    {
      int rint = r.evaluate(x, y) * 255;
      int gint = g.evaluate(x, y) * 255;
      int bint = b.evaluate(x, y) * 255;
      Uint32 color = SDL_MapRGB(m_surface->format, rint, gint, bint);
      putpixel(m_surface, x, y, color);
    }
  }
};

#define RGB(r, g, b)  (r<<24 |  g << 16 | b << 8 | 255)

#endif