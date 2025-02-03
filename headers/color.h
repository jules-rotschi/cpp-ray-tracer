#ifndef COLOR_H
#define COLOR_H

class Color {
public:
  double red, green, blue;
  Color();
  Color(double red, double green, double blue);
  Color& normalize_components(double max_value);
  Color& operator+=(const Color& other_color);
  Color& operator/=(double k);
};

Color operator*(const Color& color, double k);
Color operator*(double k, const Color& color);
Color operator*(const Color& color1, const Color& color2);
Color operator/(const Color& color, double k);
Color operator+(const Color& color1, const Color& color2);

#endif