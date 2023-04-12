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

#define X_GIZMO 10000
#define Y_GIZMO 20000
#define Z_GIZMO 30000

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

			//models.at(CURRENT_OBJECT(selected_obj))->transformation.ObjectScales = scaled;

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

		for (size_t i = 1; i < models.size(); i++)
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

	void DrawGizmo(GLuint shader, Camera& camera , size_t iterator , int currentselectedobject , std::pair<uint , bool> enablegizmo_p)
	{

		glm::vec3 model_transformation(models.at(CURRENT_OBJECT(currentselectedobject))->transformation.transformmatrix[3]);

		glm::vec3 model_scales = glm::vec3(models.at(CURRENT_OBJECT(currentselectedobject))->transformation.transformmatrix[0][0], 
		                                   models.at(CURRENT_OBJECT(currentselectedobject))->transformation.transformmatrix[1][1], 
			                               models.at(CURRENT_OBJECT(currentselectedobject))->transformation.transformmatrix[2][2]);
			    

		glm::vec3 originpoint(GetModel(CURRENT_OBJECT(currentselectedobject))->originpoint.x,
			                  GetModel(CURRENT_OBJECT(currentselectedobject))->originpoint.y,
			                  GetModel(CURRENT_OBJECT(currentselectedobject))->originpoint.z);
		

		GetModel(0)->transformation.translate(originpoint);

		
		GetModel(0)->transformation.translate(model_transformation * 20.0f);
		


		GetModel(0)->transformation.scale(model_scales * 10.0f);

		GetModel(0)->transformation.scale(glm::vec3(GetModel(CURRENT_OBJECT(currentselectedobject))->transformation.scale_avg) / 12.0f);


		if (iterator == 0)
		{
			GetModel(0)->transformation.SendUniformToShader(shader, "model");
			UseShaderProgram(shader);

			if (enablegizmo_p.first == Y_GIZMO && enablegizmo_p.second)
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 0.0f, 1.0f, 0.0f, 1.0f);
			}
			else
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 0.0f, 0.7f, 0.0f, 1.0f);
			}

			UseShaderProgram(0);
			DrawModels(shader, camera, 0, NULL);

		}
		if (iterator == 1)
		{
			GetModel(0)->transformation.rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			GetModel(0)->transformation.SendUniformToShader(shader, "model");
			UseShaderProgram(shader);

			if (enablegizmo_p.first == Z_GIZMO && enablegizmo_p.second)
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 0.7f, 0.0f, 0.0f, 1.0f);
			}

			UseShaderProgram(0);
			DrawModels(shader, camera, 0, NULL);
			GetModel(0)->transformation.rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		}
		if (iterator == 2)
		{
			GetModel(0)->transformation.rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			GetModel(0)->transformation.rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			GetModel(0)->transformation.SendUniformToShader(shader, "model");
			UseShaderProgram(shader);

			if (enablegizmo_p.first == X_GIZMO && enablegizmo_p.second)
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				glUniform4f(glGetUniformLocation(shader, "lightColor"), 0.0f, 0.0f, 0.7f, 1.0f);
			}

			UseShaderProgram(0);
			DrawModels(shader, camera, 0, NULL);
			GetModel(0)->transformation.rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			GetModel(0)->transformation.rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));


		}


		GetModel(0)->transformation.scale(1.0f / (glm::vec3(GetModel(CURRENT_OBJECT(currentselectedobject))->transformation.scale_avg / 12.0f)));


		GetModel(0)->transformation.scale(1.0f / (model_scales * 10.0f));

	


		GetModel(0)->transformation.translate(-(model_transformation * 20.0f));

		

		GetModel(0)->transformation.translate(-originpoint);
		
		
		
		

	}

	vec2<double> UseGizmo(GLFWwindow* window , int &currentselectedgizmo , int currentselectedobj, std::pair<uint , bool> &enablegizmo_p , vec2<double> PrevMousePos , Camera camera)
	{

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			enablegizmo_p = { NULL,false };
			currentselectedgizmo = NULL;

		}

		if (currentselectedgizmo == (4 + GetModelCount() + lights.size()) && !enablegizmo_p.second)
		{
			enablegizmo_p = { Y_GIZMO, true };
		}
		else if (currentselectedgizmo == (5 + GetModelCount() + lights.size()) && !enablegizmo_p.second)
		{
			enablegizmo_p = { Z_GIZMO, true };
		}
		else if (currentselectedgizmo == (6 + GetModelCount() + lights.size()) && !enablegizmo_p.second)
		{
			enablegizmo_p = { X_GIZMO, true };
		}

		std::cout << "CAMERA DIRECTION: " << camera.Get_Orientation().x << " " << camera.Get_Orientation().y << " " << camera.Get_Orientation().z<<"\n";


		vec2<double> temp_mouse;

		glfwGetCursorPos(window, &temp_mouse.x, &temp_mouse.y);


		vec2<double> delta_mouse = { temp_mouse.x - PrevMousePos.x, temp_mouse.y - PrevMousePos.y };

		if (CURRENT_OBJECT(currentselectedobj) >= NULL)
		{
			if (enablegizmo_p.first == Y_GIZMO && enablegizmo_p.second == true)
			{

				GetModel(CURRENT_OBJECT(currentselectedobj))->transformation.translate(glm::vec3(NULL, -delta_mouse.y / 20.0f, NULL));

				GetModel(CURRENT_OBJECT(currentselectedobj))->dynamic_origin += glm::vec3(NULL, -delta_mouse.y / 20.0f, NULL);


			}
			else if (enablegizmo_p.first == Z_GIZMO && enablegizmo_p.second == true)
			{

				double active_delta_mouse = NULL;

				if (abs(delta_mouse.y) > abs(delta_mouse.x))
				{
					active_delta_mouse = delta_mouse.y;

					if (camera.Get_Orientation().z >= NULL)
					{
						active_delta_mouse = -active_delta_mouse;
					}
				}
				else if (abs(delta_mouse.y) <= abs(delta_mouse.x))
				{
					active_delta_mouse = -delta_mouse.x;

					if (camera.Get_Orientation().z <= NULL)
					{
						active_delta_mouse = -active_delta_mouse;
					}
				}

				
				

				GetModel(CURRENT_OBJECT(currentselectedobj))->transformation.translate(glm::vec3(NULL, NULL, active_delta_mouse / 20.0f));

				GetModel(CURRENT_OBJECT(currentselectedobj))->dynamic_origin += glm::vec3(NULL, NULL, active_delta_mouse / 20.0f);


			}

			else if (enablegizmo_p.first == X_GIZMO && enablegizmo_p.second == true)
			{

				double active_delta_mouse = NULL;

				if (abs(delta_mouse.y) > abs(delta_mouse.x))
				{
					active_delta_mouse = delta_mouse.y;

					if (camera.Get_Orientation().x >= NULL)
					{
						active_delta_mouse = -active_delta_mouse;
					}
				}
				else if (abs(delta_mouse.y) <= abs(delta_mouse.x))
				{
					active_delta_mouse = delta_mouse.x;

					if (camera.Get_Orientation().x <= NULL)
					{
						active_delta_mouse = -active_delta_mouse;
					}
				}

				


				GetModel(CURRENT_OBJECT(currentselectedobj))->transformation.translate(glm::vec3(active_delta_mouse / 20.0f, NULL, NULL));

				GetModel(CURRENT_OBJECT(currentselectedobj))->dynamic_origin += glm::vec3(active_delta_mouse / 20.0f, NULL, NULL);

			}
		}
		
		return temp_mouse;
	}

	

};


#endif // !LIGHTCLASS
