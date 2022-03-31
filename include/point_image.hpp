#ifndef POINTIMAGE_HPP
#define POINTIMAGE_HPP

class PointImage{
public:
  float x;
  float y;
  float z;
  float color_r;
  float color_g;
  float color_b;

  PointImage(float x, float y);
  ~PointImage();

  void print_point();
};

#endif
