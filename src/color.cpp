#include "color.h"

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(double red, double green, double blue)
  : red(red), green(green), blue(blue) {}

Color& Color::normalize_components(double max_value) {
  red /= max_value;
  red = red > max_value ? max_value : red;

  green /= max_value;
  green = green > max_value ? max_value : green;

  blue /= max_value;
  blue = blue > max_value ? max_value : blue;
  
  return *this;
}

Color operator*(const Color& color, double k) {
  return Color(color.red * k, color.green * k, color.blue * k);
}

Color operator*(double k, const Color& color) {
  return color * k;
}

Color operator*(const Color& color1, const Color& color2) {
  return Color(color1.red * color2.red, color1.green * color2.green, color1.blue * color2.blue);
}

Color operator/(const Color& color, double k) {
  return (1 / k) * color;
}

Color operator+(const Color& color1, const Color& color2) {
  return Color(color1.red + color2.red, color1.green + color2.green, color1.blue + color2.blue);
}

Color& Color::operator+=(const Color& other_color) {
  *this = *this + other_color;
  return *this;
}