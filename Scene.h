#ifndef LIGHTCLASS
#define LIGHTCLASS 

#include "Mesh.h"
#include <memory>
#include <FreeImage.h>
#include "Shadow_Map.h"

#define CUBE_LIGHT 1080
#define SPHERE_LIGHT 1090
#define POINT_LIGHT 100
#define DIRECTIONAL_LIGHT 200
#define SPOT_LIGHT 300

#define CURRENT_OBJECT(Current_obj) (Current_obj - 2)

class Light
{
public:


	Light(glm::vec3 meshposition,glm::vec3 meshscale,glm::vec4 light_color, GLuint shader, uint16 light_shape , uint16 lighttype)
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


			


			std::vector <Vertexs> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertexs));
			std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
			std::vector<Textures> tex;
			// Crate light mesh
			Meshs *light = new Meshs(lightVerts, lightInd, tex , shader);

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
	
		lightmesh->Draw(shader, camera,GL_TRIANGLES);
	
	};

private:

	Meshs *lightmesh;
	glm::vec3 lightpos;
	glm::vec4 light_color;
	glm::vec3 lightscale;
	glm::mat4 lightmodel = glm::mat4(1.0f);
	//uint16 light_shape;

};

class scene
{
public:

	glm::vec4 LightColors[10];
	glm::vec3 LightPositions[10];
	int numberoflights = NULL;
	int typeoflights[10];
	std::vector<Light*> lights;
	std::vector<Model*> models;
	float globalscale;


	unsigned int quadVAO, quadVBO;


	void FindGlobalMeshScales()
	{

		float maxX = -std::numeric_limits<float>::infinity();
		float maxY = -std::numeric_limits<float>::infinity();
		float maxZ = -std::numeric_limits<float>::infinity();
		float minX = std::numeric_limits<float>::infinity();
		float minY = std::numeric_limits<float>::infinity();
		float minZ = std::numeric_limits<float>::infinity();

		for (unsigned int i = 0; i < models.size(); i++)
		{

			for (size_t j = 0; j < models[i]->meshes.size(); j++)
			{

				Vertex origin = models[i]->meshes[j].vertices[0]; // use first vertex as origin point

				for (unsigned int k = 0; k < models[i]->meshes[j].vertices.size(); k++) {

					Vertex vertex;
					vertex.Position.x = models[i]->meshes[j].vertices[k].Position.x - origin.Position.x;
					vertex.Position.y = models[i]->meshes[j].vertices[k].Position.y - origin.Position.y;
					vertex.Position.z = models[i]->meshes[j].vertices[k].Position.z - origin.Position.z;// subtract origin point from vertex

					maxX = std::max(maxX, vertex.Position.x);
					maxY = std::max(maxY, vertex.Position.y);
					maxZ = std::max(maxZ, vertex.Position.z);
					minX = std::min(minX, vertex.Position.x);
					minY = std::min(minY, vertex.Position.y);
					minZ = std::min(minZ, vertex.Position.z);

				}
			}


			float meshWidth = maxX - minX;
			float meshHeight = maxY - minY;
			float meshDepth = maxZ - minZ;

			models.at(i)->transformation.ObjectScales.x = meshWidth;
			models.at(i)->transformation.ObjectScales.y = meshHeight;
			models.at(i)->transformation.ObjectScales.z = meshDepth;

			maxX = -std::numeric_limits<float>::infinity();
			maxY = -std::numeric_limits<float>::infinity();
			maxZ = -std::numeric_limits<float>::infinity();
			minX = std::numeric_limits<float>::infinity();
			minY = std::numeric_limits<float>::infinity();
			minZ = std::numeric_limits<float>::infinity();

		}


		float sceneWidth = -std::numeric_limits<float>::infinity();
		float sceneHeight = -std::numeric_limits<float>::infinity();
		float sceneDepth = -std::numeric_limits<float>::infinity();

		for (unsigned int i = 0; i < models.size(); i++)
		{

			sceneWidth = std::max(sceneWidth, models.at(i)->transformation.ObjectScales.x);
			sceneHeight = std::max(sceneHeight, models.at(i)->transformation.ObjectScales.y);;
			sceneDepth = std::max(sceneDepth, models.at(i)->transformation.ObjectScales.z);

		}

		// Decide on a unit scale for the scene
		float unitScale = 1.0f; // 1 unit = 1 meter

		// Calculate the global scale factor
		//float maxDimension = std::max(sceneWidth, std::max(sceneHeight, sceneDepth));
		//float globalScale = maxDimension / unitScale;

		float maxDimension = (sceneWidth + sceneHeight + sceneDepth) / 3;
		float globalScale = maxDimension / unitScale;



		this->globalscale = globalScale;

		for (size_t i = 0; i < models.size(); i++)
		{
			models.at(i)->transformation.scale_avg = (models.at(i)->transformation.ObjectScales.x + models.at(i)->transformation.ObjectScales.y + models.at(i)->transformation.ObjectScales.z) / 3;
			models.at(i)->transformation.dynamic_scale_avg = models.at(i)->transformation.scale_avg;

			models.at(i)->transformation.ObjectScales.x = models.at(i)->transformation.ObjectScales.x ;
			models.at(i)->transformation.ObjectScales.y = models.at(i)->transformation.ObjectScales.y ;
			models.at(i)->transformation.ObjectScales.z = models.at(i)->transformation.ObjectScales.z ;


			std::cout << "Model width: " << models.at(i)->transformation.ObjectScales.x << " Model height: " << models.at(i)->transformation.ObjectScales.y << " Model Depth: " << models.at(i)->transformation.ObjectScales.z << "\n";
			std::cout << "Scale avg: " << models.at(i)->transformation.scale_avg << "\n";

		}

		std::cout << "GLOBAL SCALE: " << globalScale << "\n";


	}

	void RecalculateObjectScales(size_t selected_obj , glm::vec3 scale)
	{

		static glm::vec3 prev_scale = glm::vec3(NULL, NULL, NULL);


		if (prev_scale != scale)
		{
			
			std::cout << "Old global scale: " << globalscale << "\n";

			glm::vec3 scaled;
			scaled = models.at(CURRENT_OBJECT(selected_obj))->transformation.ObjectScales * scale;

			models.at(CURRENT_OBJECT(selected_obj))->transformation.dynamic_scale_avg = (scaled.x  + scaled.y  + scaled.z ) / 3;

			globalscale = -std::numeric_limits<float>::infinity();


			for (size_t i = 0; i < models.size(); i++)
			{
				globalscale = std::max(models.at(i)->transformation.dynamic_scale_avg, globalscale);
			}

			std::cout << "New global scale: " << globalscale << "\n";


			prev_scale = scale;
		}

	}

	void Takescreenshot(shadowmap* ShadowMap, int width, int height, const char* path)
	{
		
		// Make the BYTE array, factor of 3 because it's RBG.
		BYTE* pixels = new BYTE[3 * width * height];


		glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		// Convert to FreeImage format & save to file
		FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
		FreeImage_Save(FIF_PNG, image, path, 0);

		// Free resources
		FreeImage_Unload(image);
		delete[] pixels;

	}

	void Addlight(glm::vec3 meshposition, glm::vec3 meshscale, glm::vec4 light_color, GLuint shader, uint16 light_shape, int lighttype)
	{
		if (!(numberoflights >= 10))
		{
			Light* templight = new Light(meshposition, meshscale, light_color, shader, light_shape, lighttype);
			lights.push_back(templight);
			LightColors[numberoflights] = light_color;
			LightPositions[numberoflights] = meshposition;
			typeoflights[numberoflights] = lighttype;

			numberoflights++;
		}
		else
		{

			std::cout << "Already reached the sufficent count of lights!" << "\n";

		}


	}

	void ImportModel(std::string filepath, GLuint shader)
	{
		Model* newmodel = new Model(filepath, shader);

		models.push_back(newmodel);

		FindGlobalMeshScales();

	}

	void CopyModel(size_t index)
	{

		Model* newmodel = new Model;

		//newmodel->meshes.assign(->meshes.begin(), models.at(index)->meshes.end());
		for (size_t i = 0; i < models.at(index)->meshes.size(); i++)
		{
			newmodel->meshes.push_back(Mesh(models.at(index)->meshes[i].vertices, models.at(index)->meshes[i].indices, models.at(index)->meshes[i].textures));
			//newmodel->meshes[i].setupMesh();
		}
		//newmodel->textures_loaded.assign(models.at(index)->textures_loaded.begin(), models.at(index)->textures_loaded.end());
		newmodel->directory = models.at(index)->directory;
		newmodel->modelpath = models.at(index)->modelpath;

		std::cout << "copied models Mesh count: " << newmodel->meshes.size() << "\n";
		std::cout << "newmodel->meshes[1].textures.size(): " << newmodel->meshes[0].vertices.size() << "\n";
		std::cout << "models.at(index)->meshes[i].textures: " << models.at(index)->meshes[0].textures.size() << "\n";

		newmodel->transformation = models.at(index)->transformation;
		*newmodel->GetModelIDcounterptr() += 1;
		*GetModel(GetModelCount() - 1)->GetModelIDcounterptr() += 1;
		*newmodel->GetModelIDptr() = GetModelCount() + 2;



		std::cout << "Coppied models ID: " << *newmodel->GetModelIDptr() << "\n";
		//memcpy(newmodel,models.at(index), sizeof(*models.at(index)));

		std::cout << "COPPIED MODEL ID: " << *GetModel(0)->GetModelIDcounterptr() << "\n";
		std::cout << "COPPIED MODEL ID: " << *newmodel->GetModelIDcounterptr() << "\n";

		models.push_back(newmodel);

	}
	void DrawShadowMap(shadowmap* ShadowMap, GLuint shadow_map_shader, Camera& camera, GLFWwindow* window, glm::vec4 background_color)
	{


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		UseShaderProgram(shadow_map_shader);

		glEnable(GL_DEPTH_TEST);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glBindFramebuffer(GL_FRAMEBUFFER, ShadowMap->GetShadowMapFBO());

		glViewport(0, 0, ShadowMap->GetShadowMapSize().x, ShadowMap->GetShadowMapSize().y);


		glClear(GL_DEPTH_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, ShadowMap->GetShadowMapImage());

		
		//glCullFace(GL_BACK);

		for (size_t i = 0; i < models.size(); i++)
		{
			models.at(i)->transformation.SendUniformToShader(shadow_map_shader, "model");
			models[i]->Draw(shadow_map_shader, camera, ShadowMap->GetShadowMapImage());
		}


		UseShaderProgram(0);
		//glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);



	}

	void SetScreenQuads()
	{

		float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};


		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));



	}

	void DrawScreenQuad(GLuint shader, GLuint buffertexture)
	{

		// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);

		UseShaderProgram(shader);


		glBindVertexArray(quadVAO);
		glActiveTexture(GL_TEXTURE0 + 7);
		glBindTexture(GL_TEXTURE_2D, buffertexture);
		glUniform1i(glGetUniformLocation(shader, "shadowMap"), 7);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		UseShaderProgram(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void DrawModelsWithOutline(GLuint shader1, GLuint shader2, Camera& camera, size_t model_index_to_draw, size_t current_selected, GLuint shadowMap)
	{

		glClear(GL_STENCIL_BUFFER_BIT);

		UseShaderProgram(shader1);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glDisable(GL_DEPTH_TEST);

		models[model_index_to_draw]->transformation.SendUniformToShader(shader1, "model");
		models[model_index_to_draw]->Draw(shader1, camera, shadowMap);

		//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glEnable(GL_DEPTH_TEST);

		//glDepthFunc(GL_NEVER);
		UseShaderProgram(shader2);

		//glm::mat4 temp = *models[model_index_to_draw]->transformation.GetTransformationMat4();
		//SetGrid(shader2).vertices[0] /
		//models[model_index_to_draw]->transformation.translate(glm::vec3(0.0f, -0.5f, 0.0f));

		//models[model_index_to_draw]->transformation.scale(glm::vec3(1.01f, 1.01f, 1.01f));
		models[model_index_to_draw]->transformation.SendUniformToShader(shader2, "model");

		std::cout << "SCALE AVG@; " << models[model_index_to_draw]->transformation.scale_avg << "\n";

		UseShaderProgram(shader2);

		glUniform1f(glGetUniformLocation(shader2, "scale_avg"), models[model_index_to_draw]->transformation.scale_avg);

		//models[model_index_to_draw]->transformation.translate(-glm::vec3(0.0f, -0.5f, 0.0f));

		models[model_index_to_draw]->Draw(shader2, camera, shadowMap);

		UseShaderProgram(NULL);

		//*models[model_index_to_draw]->transformation.GetTransformationMat4() = temp;
		//models[model_index_to_draw]->transformation.SendUniformToShader(shader2, "model");

		glDepthFunc(GL_LESS);
		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);

	}
	void DrawModels(GLuint shader, Camera& camera, size_t model_index_to_draw, GLuint shadowMap)
	{

		models[model_index_to_draw]->Draw(shader, camera, shadowMap);

	}

	Model* GetModel(size_t model_index)
	{
		return models[model_index];
	}

	size_t GetModelCount()
	{
		return models.size();
	}

	void DeleteModel(size_t index)
	{
		delete models.at(index);
		models.erase(models.begin() + index);
	}

	~scene()
	{
		for (auto temp : lights)
		{
			delete temp;
		}

		for (auto temp : models)
		{
			delete temp;
		}
	}

	void handlelights(GLuint shader)
	{
		UseShaderProgram(shader);

		GLuint Lcolors = glGetUniformLocation(shader, "lightColors");
		glUniform4fv(Lcolors, 10, &LightColors[0][0]);

		GLuint Lpos = glGetUniformLocation(shader, "lightpositions");
		glUniform3fv(Lpos, 10, &LightPositions[0][0]);

		GLuint numberofl = glGetUniformLocation(shader, "numberoflights");
		glUniform1i(numberofl, numberoflights);

		GLuint typeoflight = glGetUniformLocation(shader, "typeoflight");
		glUniform1iv(typeoflight, 10, typeoflights);

		UseShaderProgram(0);

	}

	void DrawLights(GLuint shader, Camera& camera)
	{

		for (size_t i = 0; i < numberoflights; i++)
		{

			lights[i]->Draw(shader, camera);

		}

	}

	std::pair<std::vector<Vertexs>, std::vector<uint>> Grid(size_t grid_incr)
	{

		std::vector<Vertexs> vertices;
		std::vector<uint> indices;

		for (int j = 0; j <= grid_incr; ++j) {
			for (int i = 0; i <= grid_incr; ++i) {
				float x = (float)i / (float)grid_incr;
				float y = 0;
				float z = (float)j / (float)grid_incr;
				Vertexs temp = { glm::vec3(x, y, z) };
				vertices.push_back(temp);
			}
		}

		for (int j = 0; j < grid_incr; ++j) {
			for (int i = 0; i < grid_incr; ++i) {

				int row1 = j * (grid_incr + 1);
				int row2 = (j + 1) * (grid_incr + 1);

				indices.push_back(row1 + i);
				indices.push_back(row1 + i + 1);
				indices.push_back(row1 + i + 1);
				indices.push_back(row2 + i + 1);
				indices.push_back(row2 + i + 1);
				indices.push_back(row2 + i);
				indices.push_back(row2 + i);
				indices.push_back(row1 + i);

			}
		}


		return { vertices,indices };

	}

	Meshs SetGrid(GLuint shader)
	{

		std::vector<Vertexs> gridvert = Grid(10).first;
		std::vector<uint> gridindices = Grid(10).second;
		std::vector<Textures> tex;

		Meshs grid(gridvert, gridindices, tex, shader);

		return grid;

	}

	void RenderGrid(GLuint shader, Meshs& grid, Camera& camera)
	{
		UseShaderProgram(shader);

		glm::mat4 modelmat = glm::mat4(1.0f);

		modelmat = glm::translate(modelmat, glm::vec3(-0.5f, 0.0f, -0.5f));
		modelmat = glm::scale(modelmat, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelmat));
		camera.Matrix(shader, "cameramatrix");
		grid.Draw(shader, camera, GL_LINES);

		UseShaderProgram(0);

	}

	void DrawGizmo(GLuint shader, Model& gizmo, Camera& camera  ,GLuint shadow_map)
	{
		UseShaderProgram(shader);

		glm::mat4 modelmat = glm::mat4(1.0f);

		gizmo.transformation.translate(glm::vec3(-0.5f, 0.0f, -0.5f));
		gizmo.transformation.scale(glm::vec3(1.0f, 1.0f, 1.0f));

		//glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelmat));
		//camera.Matrix(shader, "cameramatrix");
		gizmo.transformation.SendUniformToShader(shader, "model");

		gizmo.Draw(shader, camera, shadow_map);

		UseShaderProgram(0);

	}

	Meshs SetCursorObject(GLuint shader)
	{

		Vertexs vertices[] = 
		{ 
			Vertexs{ glm::vec3(0.000000 ,- 0.113012 ,- 1.000000)},
			Vertexs{ glm::vec3(0.195090 ,-0.113012 ,-0.980785)},
			Vertexs{ glm::vec3(0.382683 ,-0.113012 ,-0.923880)},
			Vertexs{ glm::vec3(0.555570 ,-0.113012 ,-0.831470)},
			Vertexs{ glm::vec3(0.707107 ,-0.113012 ,-0.707107)},
			Vertexs{ glm::vec3(0.831470 ,-0.113012 ,-0.555570)},
			Vertexs{ glm::vec3(0.923880 ,-0.113012 ,-0.382683)},
			Vertexs{ glm::vec3(0.980785 ,-0.113012 ,-0.195090)},
			Vertexs{ glm::vec3(1.000000 ,-0.113012 ,0.000000)},
			Vertexs{ glm::vec3(0.980785 ,-0.113012 ,0.195090)},
			Vertexs{ glm::vec3(0.923880 ,-0.113012 ,0.382683)},
			Vertexs{ glm::vec3(0.831470 ,-0.113012 ,0.555570)},
			Vertexs{ glm::vec3(0.707107 ,-0.113012 ,0.707107)},
			Vertexs{ glm::vec3(0.555570 ,-0.113012 ,0.831470)},
			Vertexs{ glm::vec3(0.382683 ,-0.113012 ,0.923880)},
			Vertexs{ glm::vec3(0.195090 ,-0.113012 ,0.980785)},
			Vertexs{ glm::vec3(0.000000 ,-0.113012 ,1.000000)},
			Vertexs{ glm::vec3(-0.195090 ,-0.113012 ,0.980785)},
			Vertexs{ glm::vec3(-0.382683 ,-0.113012 ,0.923880)},
			Vertexs{ glm::vec3(-0.555570 ,-0.113012 ,0.831470)},
			Vertexs{ glm::vec3(-0.707107 ,-0.113012 ,0.707107)},
			Vertexs{ glm::vec3(-0.831470 ,-0.113012 ,0.555570)},
			Vertexs{ glm::vec3(-0.923880 ,-0.113012 ,0.382683)},
			Vertexs{ glm::vec3(-0.980785 ,-0.113012 ,0.195090)},
			Vertexs{ glm::vec3(-1.000000 ,-0.113012 ,0.000000)},
			Vertexs{ glm::vec3(-0.980785 ,-0.113012 ,-0.195090)},
			Vertexs{ glm::vec3(-0.923880 ,-0.113012 ,-0.382683)},
			Vertexs{ glm::vec3(-0.831470 ,-0.113012 ,-0.555570)},
			Vertexs{ glm::vec3(-0.707107 ,-0.113012 ,-0.707107)},
			Vertexs{ glm::vec3(-0.555570 ,-0.113012 ,-0.831470)},
			Vertexs{ glm::vec3(-0.382683 ,-0.113012 ,-0.923880)},
			Vertexs{ glm::vec3(-0.195090 ,-0.113012 ,-0.980785)},
			Vertexs{ glm::vec3(0.000000 ,1.886988 ,0.000000)} 
		};

		GLuint indices[] =
		{
			 1, 2, 1,
			33, 65, 1,
			2, 3, 1,
			2, 3, 2,
			33, 65, 2,
			3, 5, 2,
			3, 5, 3,
			33, 65, 3,
			4, 7, 3,
			4, 7, 4,
			33, 65, 4,
			5, 9, 4,
			5, 9, 5,
			33, 65, 5,
			6, 11, 5,
			6, 11, 6,
			33, 65, 6,
			7, 13, 6,
			7, 13, 7,
			33, 65, 7,
			8, 15, 7,
			8, 15, 8,
			33, 65, 8,
			9, 17, 8,
			9, 17, 9,
			33, 65, 9,
			10, 19, 9,
			10, 19, 10,
			33, 65, 10,
			11, 21, 10,
			11, 21, 11,
			33, 65, 11,
			12, 23, 11,
			12, 23, 12,
			 33 , 65 , 12,
			 13 , 25 , 12,
			 13 , 25 , 13,
			 33 , 65 ,  13,
			 14 , 27 , 13,
			 14 , 27 , 14,
			 33 , 65 , 14,
			 15 , 29 , 14,
			 15 , 29 , 15,
			 33 , 65 , 15,
			 16 , 31 , 15,
			 16 , 31 , 16,
			 33 , 65 , 16,
			 17 , 33 , 16,
			 17 , 33 , 17,
			 33 , 65 , 17,
			 18 , 35 , 17,
			 18 , 35 , 18,
			 33 , 65 , 18,
			 19 , 37 , 18,
			 19 , 37 , 19,
			 33 , 65 , 19,
			 20 , 39 , 19,
			 20 , 39 , 20,
			 33 , 65 , 20,
			 21 , 41 , 20,
			 21 , 41 , 21,
			 33 , 65 , 21,
			 22 , 43 , 21,
			 22 , 43 , 22,
			 33 , 65 , 22,
			 23 , 45 , 22,
			 23 , 45 , 23,
			 33 , 65 , 23,
			 24 , 47 , 23,
			 24 , 47 , 24,
			 33 , 65 , 24,
			 25 , 49 , 24,
			 25 , 49 , 25,
			 33 , 65 , 25,
			 26 , 51 , 25,
			 26 , 51 , 26,
			 33 , 65 , 26,
			 27 , 53 , 26,
			 27 , 53 , 27,
			 33 , 65 , 27,
			 28 , 55 , 27,
			 28 , 55 , 28,
			 33 , 65 , 28,
			 29 , 57 , 28,
			 29 , 57 , 29,
			 33 , 65 , 29,
			 30 , 59 , 29,
			 30 , 59 , 30,
			 33 , 65 , 30,
			 31 , 62 , 30,
			 1 , 1 , 31,
			 2 , 4 , 31,
			 3 , 6 , 31,
			 4 , 8 , 31,
			 5 , 10 , 31,
			 6 , 12 , 31,
			 7 , 14 , 31,
			 8 , 16 , 31,
			 9 , 18 , 31,
			 10 , 20 , 31,
			 11 , 22 , 31,
			 12 , 24 , 31,
			 13 , 26 , 31,
			 14 , 28 , 31,
			 15 , 30 , 31,
			 16 , 32 , 31,
			 17 , 34 , 31,
			 18 , 36 , 31,
			 19 , 38 , 31,
			 20 , 40 , 31,
			 21 , 42 , 31,
			 22 , 44 , 31,
			 23 , 46 , 31,
			 24 , 48 , 31,
			 25 , 50 , 31,
			 26 , 52 , 31,
			 27 , 54 , 31,
			 28 , 56 , 31,
			 29 , 58 , 31,
			 30 , 60 , 31,
			 31 , 61 , 31,
			 32 , 63 , 31,
			 31 , 62 , 32,
			 33 , 65 , 32,
			 32 , 64 , 32,
			 32 , 64 , 33,
			 33 , 65 , 33,
			 1 , 2 , 33

		};


		std::vector <Vertexs> Verts(vertices, vertices + sizeof(vertices) / sizeof(Vertexs));
		std::vector <GLuint> Ind(indices, indices + sizeof(indices) / sizeof(GLuint));
		std::vector<Textures> tex;
		// Crate light mesh
		Meshs cursor(Verts, Ind, tex, shader);

		return cursor;
	}

	void DrawCursor(Meshs &cursor , GLuint shader , Camera &camera)
	{

		UseShaderProgram(shader);

		glm::mat4 modelmat = glm::mat4(1.0f);

		modelmat = glm::translate(modelmat, glm::vec3(-0.5f, 0.0f, -0.5f));
		modelmat = glm::scale(modelmat, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelmat));
		camera.Matrix(shader, "cameramatrix");

		cursor.Draw(shader, camera, GL_LINE_LOOP);

		UseShaderProgram(0);

	}

};


#endif // !LIGHTCLASS
