#include "Texture.h"
#include "Shader.h"
#include <glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glfw3.h>
#include <iostream>

Textures::Textures(const char* filepath , GLenum slot , GLenum texturetype , GLenum pixeltype, unsigned int texture_type_for_pbr, std::string texture_type_for_pbr_str)
{
	std::string temp(filepath);
	path = temp;
	std::cout << "TEST OF PATH STRING: " << path << "\n";

	this->texture_type_of_pbr = texture_type_for_pbr;
	this->texture_type_of_pbr_str = texture_type_for_pbr_str;
	type = texturetype;
	//stbi_set_flip_vertically_on_load(true);
	int channels;
	unsigned char* pixels = stbi_load(filepath, &width, &height, &channels,0);
	if (!pixels)
	{

		std::cerr << "Failed to load texture :: " << filepath << "\n";
		return;

	}

	this->channels = channels;

	GLenum formattex = NULL;
	if (channels == 1)
	{
		formattex = GL_RED;
	}	
	else if (channels == 3)
	{
		formattex = GL_RGB;

	}
	else if (channels == 4)
	{
		formattex = GL_RGBA;

	}

	std::cout << "Texture channel count : " << channels << "\n";

	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(texturetype, texture);

	glTexParameteri(texturetype, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(texturetype, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(texturetype, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texturetype, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(texturetype, 0, formattex, width, height, 0, formattex, pixeltype, pixels);
	glGenerateMipmap(texturetype);

	stbi_image_free(pixels);

	glBindTexture(texturetype, 0);

}

Textures::~Textures()
{
}

void Textures::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, texture);
}

void Textures::Unbind()
{
	glBindTexture(type, 0);
}

void Textures::DeleteTexture()
{
	glDeleteTextures(1, &texture);
}

std::string Textures::GetPathData()
{
	return this->path;
}

void Textures::texunit(GLuint shader_program, const char* uniform, GLuint unit)
{
	GLuint texuni = glGetUniformLocation(shader_program, uniform);

	UseShaderProgram(shader_program);

	glUniform1i(texuni, unit);
}

unsigned int Textures::GetTexturePbrType()
{
	return this->texture_type_of_pbr;
}

std::string Textures::GetTexturePbrType_str()
{
	return this->texture_type_of_pbr_str;
}

vec2<float> GetScreenRatio(GLFWwindow* m_window , vec2<int> menu_size)
{
	vec2<int> winsize;
	glfwGetWindowSize(m_window, &winsize.x, &winsize.y);

	//std::cout << "WINSIZE.X: " << winsize.x << "WINSIZE.Y: " << winsize.y << "\n";

	winsize.x = menu_size.x;
	winsize.y = menu_size.y;

	//std::cout << "WINSIZE.X: " << winsize.x << "WINSIZE.Y: " << winsize.y << "\n";


	float ratio_minmax = NULL;

	float aspectRatios_wh = static_cast<float>(winsize.x) / static_cast<float>(winsize.y);

	float aspectRatios_hw = static_cast<float>(winsize.y) / static_cast<float>(winsize.x);


	float ratio_minmax_x = NULL, ratio_minmax_y = NULL;

	if (winsize.y > winsize.x)
	{
		ratio_minmax_x = aspectRatios_hw;
		ratio_minmax_y = 1.0f;

	}
	if (winsize.y < winsize.x)
	{
		ratio_minmax_x = aspectRatios_hw;
		ratio_minmax_y = 1.0f;

	}
	if (winsize.y == winsize.x)
	{
		ratio_minmax_x = 1.0f;
		ratio_minmax_y = 1.0f;
	}

	//std::cout << "x: " << ratio_minmax_x << "\n";
	//std::cout << "y: " << ratio_minmax_y << "\n";

	return vec2<float>{ratio_minmax_x, ratio_minmax_y};
}
