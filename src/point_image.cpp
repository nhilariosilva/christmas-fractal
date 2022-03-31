#include <point_image.hpp>

#include <iostream>
#include <time.h>

PointImage::PointImage(float x, float y){
  this->x = x;
  this->y = y;
  this->z = 0.0f;
  this->color_r = ((double) rand() / (RAND_MAX));
  this->color_g = ((double) rand() / (RAND_MAX));
  this->color_b = ((double) rand() / (RAND_MAX));
}

PointImage::~PointImage(){

}

void PointImage::print_point(){
  std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ") - (" << this->color_r << ", " << this->color_g << ", " << this->color_b << ")" << std::endl;
}
