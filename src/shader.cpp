#include <shader.hpp>
#include <fstream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path){
  std::ifstream vertex_file, fragment_file;
  std::string line;
  std::stringstream vertex_stream, fragment_stream;

  vertex_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  fragment_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

  try{
    vertex_file.open(vertex_path);
    fragment_file.open(fragment_path);

    vertex_stream << vertex_file.rdbuf();
    fragment_stream << fragment_file.rdbuf();

    vertex_file.close();
    fragment_file.close();
  }catch(std::ifstream::failure e){
    std::cout << "ERROR: It was not possible to read shaders files" << std::endl;
  }

  std::string vertex_code_str = vertex_stream.str();
  std::string fragment_code_str = fragment_stream.str();

  const char* vertex_code = vertex_code_str.c_str();
  const char* fragment_code = fragment_code_str.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  fragment = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex, 1, &vertex_code, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(success != 1){
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

  glShaderSource(fragment, 1, &fragment_code, NULL);
  glCompileShader(fragment);
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertex);
  glAttachShader(this->ID, fragment);
  glLinkProgram(this->ID);
  glGetShaderiv(this->ID, GL_LINK_STATUS, &success);
	if(success != 1){
		glGetShaderInfoLog(this->ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

  glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader(){

}

unsigned int Shader::getID(){
  return this->ID;
}

void Shader::use(){
  glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value){
  glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value){
  glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value){
  glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value){
  glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));}
