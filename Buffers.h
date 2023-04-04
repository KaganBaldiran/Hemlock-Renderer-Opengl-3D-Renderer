#pragma once
#include <vector>
#include <iostream>

typedef float GLfloat;
typedef int GLint;
typedef unsigned int GLuint;
typedef unsigned int uint;

typedef short int int16;
typedef short unsigned int uint16;

#define SUCCESS 1
#define FAIL -1

#ifndef BUFFERS
#define BUFFERS 1

#if BUFFERS

 class VBO
 {
 public:

	 VBO();
	 GLuint Bind();
	 GLuint GetBufferID();
	 ~VBO();
		 
 private:

	 GLuint vbo;

  };



 class VAO
 {
 public:

	 VAO();
	 GLuint Bind();
	 GLuint GetVertexArrID();
	 ~VAO();

 private:

	 GLuint vao;

 };



 class EBO
 {
 public:

	 EBO();
	 GLuint Bind();
	 GLuint GetEBOID();
	 ~EBO();

 private:

	 GLuint ebo;

 };

 void BindVBONull();
 void BindVAONull();
 void BindEBONull();


#endif // INITIALIZE

#endif // !1
