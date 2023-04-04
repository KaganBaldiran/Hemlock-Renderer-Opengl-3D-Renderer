#pragma once
#include <vector>
#include <iostream>
#include <string>

typedef float GLfloat;
typedef int GLint;
typedef unsigned int GLuint;

#ifndef SHADER
#define SHADER 1

#if SHADER

  std::string ReadTextFile(const char* filepath);

  GLuint CompileVertShader(const char* vertexsource);

  GLuint CompileFragShader(const char* fragmentsource);

  GLuint CompileShaderProgram(GLuint vertexshader, GLuint fragmentshader);

  void UseShaderProgram(GLuint program);

  void DeleteShaderProgram(GLuint program);


  class Shader
  {
  public:

	  Shader(const char* vertsource , const char* fragsource);

	  GLuint GetID();

  private:

	  GLuint shaderID;
  };


#endif // INITIALIZE

#endif // !1

