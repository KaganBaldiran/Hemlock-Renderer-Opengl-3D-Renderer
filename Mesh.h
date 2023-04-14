#ifndef  MESH
#define MESH

#include<string>
#include<vector>
#include"Camera.h"
#include"Shader.h"
#include"Buffers.h"
#include"Texture.h"
#include"Helper_classes.h"

#define DIFFUSE_TEXTURE 10
#define SPECULAR_TEXTURE 20
#define NORMAL_TEXTURE 30
#define HEIGHT_TEXTURE 40
#define METALIC_TEXTURE 50


struct Vertexs
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
	glm::vec3 color;
	glm::vec3 tangent;
	glm::vec3 bitangent;

};



class Meshs
{
public:

	std::vector<Vertexs> vertices;
	std::vector<GLuint> indices;
	std::vector<Textures> textures;


	
	VAO vao;
	VBO vbo;
	EBO ebo;
	
	//Mesh(GLfloat *vertices, GLuint *indices, Texture *textures, GLuint Shaderprogram);
	Meshs(std::vector<Vertexs>& vertices, std::vector<GLuint>& indices, std::vector<Textures>& textures, GLuint Shaderprogram);

	void Draw(GLuint shaderprogram, Camera& camera, GLenum drawmode);
};


#endif