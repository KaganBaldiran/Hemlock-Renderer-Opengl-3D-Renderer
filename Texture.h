#pragma once
#include "Helper_classes.h"
#include <string>


typedef unsigned int GLenum;
typedef unsigned int GLuint;
struct GLFWwindow;

#ifndef TEXTURES
#define TEXTURES 1

#if TEXTURES


   class Textures
   {
   public:

	   Textures(const char* filepath, GLenum slot, GLenum texturetype, GLenum pixeltype , unsigned int texture_type_for_pbr , std::string texture_type_for_pbr_str);
	   ~Textures();

	   void Bind();

	   void Unbind();

	   void DeleteTexture();

	   GLuint* GetTexture() { return &this->texture; };

	   std::string GetPathData();

	   void texunit(GLuint shader_program, const char* uniform, GLuint unit);

	   unsigned int GetTexturePbrType();
	   std::string GetTexturePbrType_str();

   private:

	   int width;
	   int height;
	   GLuint texture;
	   GLenum type;
	   GLuint unit;
	   unsigned int texture_type_of_pbr;
	   std::string texture_type_of_pbr_str;
	   std::string path;
	   int channels;

   };



   vec2<float> GetScreenRatio(GLFWwindow* m_window, vec2<int> menu_size);


#endif // INITIALIZE

#endif // !1
