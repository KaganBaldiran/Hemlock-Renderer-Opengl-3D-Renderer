#ifndef LIGHTHEADER
#define LIGHTHEADER

#define CUBE_LIGHT 1080
#define SPHERE_LIGHT 1090
#define POINT_LIGHT 100
#define DIRECTIONAL_LIGHT 200
#define SPOT_LIGHT 300

#include "Mesh.h"
#include <memory>
#include "Shadow_Map.h"
#include "Entity.h"

class Light
{
public:


	Light(glm::vec3 meshposition, glm::vec3 meshscale, glm::vec4 light_color, GLuint shader, uint16 light_shape, uint16 lighttype)
	{
		if (light_shape == CUBE_LIGHT)
		{

			Vertexs lightVertices[] =
			{ //     COORDINATES     //
				Vertexs{glm::vec3(-0.1f, -0.1f,  0.1f)},
				Vertexs{glm::vec3(-0.1f, -0.1f, -0.1f)},
				Vertexs{glm::vec3(0.1f, -0.1f, -0.1f)},
				Vertexs{glm::vec3(0.1f, -0.1f,  0.1f)},
				Vertexs{glm::vec3(-0.1f,  0.1f,  0.1f)},
				Vertexs{glm::vec3(-0.1f,  0.1f, -0.1f)},
				Vertexs{glm::vec3(0.1f,  0.1f, -0.1f)},
				Vertexs{glm::vec3(0.1f,  0.1f,  0.1f)}
			};

			GLuint lightIndices[] =
			{
				0, 1, 2,
				0, 2, 3,
				0, 4, 7,
				0, 7, 3,
				3, 7, 6,
				3, 6, 2,
				2, 6, 5,
				2, 5, 1,
				1, 5, 4,
				1, 4, 0,
				4, 5, 6,
				4, 6, 7
			};


			float minX = lightVertices[0].position.x, minY = lightVertices[0].position.y, minZ = lightVertices[0].position.z;
			float maxX = lightVertices[0].position.x, maxY = lightVertices[0].position.y, maxZ = lightVertices[0].position.z;

			for (unsigned int j = 0; j < (sizeof(lightVertices) / sizeof(Vertexs)); j++) 
			{
				if (lightVertices[j].position.x < minX) minX = lightVertices[j].position.x;
				if (lightVertices[j].position.y < minY) minY = lightVertices[j].position.y;
				if (lightVertices[j].position.z < minZ) minZ = lightVertices[j].position.z;
				if (lightVertices[j].position.x > maxX) maxX = lightVertices[j].position.x;
				if (lightVertices[j].position.y > maxY) maxY = lightVertices[j].position.y;
				if (lightVertices[j].position.z > maxZ) maxZ = lightVertices[j].position.z;
			}

			float centerX = (minX + maxX) / 2.0f;
			float centerY = (minY + maxY) / 2.0f;
			float centerZ = (minZ + maxZ) / 2.0f;

			originpoint = glm::vec3(centerX, centerY, centerZ);

			std::vector <Vertexs> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertexs));
			std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
			std::vector<Textures> tex;
			// Crate light mesh
			Meshs* light = new Meshs(lightVerts, lightInd, tex, shader);

			lightmesh = light;

		}
		else if (light_shape == SPHERE_LIGHT)
		{



		}

		this->lightpos = meshposition;
		this->lightscale = meshscale;
		this->light_color = light_color;

		lightmodel = glm::translate(lightmodel, this->lightpos);
		lightmodel = glm::scale(lightmodel, this->lightscale);

		UseShaderProgram(shader);

		transformation.transformmatrix = lightmodel;

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(lightmodel));
		glUniform4f(glGetUniformLocation(shader, "lightColor"), light_color.x, light_color.y, light_color.z, light_color.w);

		UseShaderProgram(0);

		

	};

	~Light()
	{

		delete lightmesh;

	}


	void Draw(GLuint shader, Camera& camera)
	{
		//lightmodel = glm::translate(lightmodel, this->lightpos);
		//lightmodel = glm::scale(lightmodel, this->lightscale);

		UseShaderProgram(shader);

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(lightmodel));
		glUniform4f(glGetUniformLocation(shader, "lightColor"), light_color.x, light_color.y, light_color.z, light_color.w);

		UseShaderProgram(0);

		lightmesh->Draw(shader, camera, GL_TRIANGLES);

	};

	
	Meshs* lightmesh;
	glm::vec3 lightpos;
	glm::vec4 light_color;
	glm::vec3 lightscale;
	glm::mat4 lightmodel = glm::mat4(1.0f);
	glm::vec3 originpoint;
	worldtransform transformation;

};


#endif // !LIGHT
