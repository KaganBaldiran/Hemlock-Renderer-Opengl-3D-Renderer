#ifndef CUBEMAP
#define CUBEMAP

#include <glew.h>
#include <glfw3.h>
#include "Buffers.h"
#include <vector>
#include <string>
#include "Shader.h"
#include "Camera.h"


class CubeMap
{
public:

	CubeMap(std::vector<std::string> texture_faces, const char* vertex_source, const char* frag_source);
	~CubeMap();
	void Draw(Camera& camera);
	GLuint GetCubeMapTexture() { return this->cubemaptextureID; };


private:

	GLuint cubemaptextureID;
	VBO vbo;
	VAO vao;
	std::vector<std::string> texture_faces;
	Shader* cubemapshader;

};


#endif 

