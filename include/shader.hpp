#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <fstream>

class Shader{
public:
  Shader(const GLchar* vertex_path, const GLchar* fragment_path);
  ~Shader();

  unsigned int getID();

  void use();
  void setBool(const std::string &name, bool value);
  void setInt(const std::string &name, int value);
  void setFloat(const std::string &name, float value);
  void setMat4(const std::string &name, glm::mat4 value);

private:
  unsigned int ID;

};

#endif
