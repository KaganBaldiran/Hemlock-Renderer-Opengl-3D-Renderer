/* #ifndef MODEL 
#define MODEL

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "stb_image.h"

#define AI_IMPORT_FLAGS (aiProcess_Triangulate | aiProcess_FlipUVs)

class Model
{
public:

	Model(const char* filepath, GLuint shader)
	{
		loadModel(filepath, shader);
	}

	void Draw(GLuint shaderprogram, Camera& camera)
	{
		int somevalue = NULL;
		for (size_t i = 0; i < meshes.size(); i++)
		{
			std::cout << "HERE: " << somevalue << "\n";
			meshes[i].Draw(shaderprogram, camera);
			somevalue++;
		}
	}

private:

	std::vector<Mesh> meshes;
	std::string directory;
	GLuint shaderprogram;

	void loadModel(std::string filepath, GLuint shader)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filepath, (aiProcess_Triangulate | aiProcess_FlipUVs));


		std::cout << "TEST OF PATH STRING: " << filepath << "\n";

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cerr << "Error regarding loading the model ::" << importer.GetErrorString() << "\n";

		}

		directory = filepath.substr(0, filepath.find_last_of('/'));

		if (scene)
		{
			processNode(scene->mRootNode, scene, shader);
		}

	}

	void processNode(aiNode* node, const aiScene* scene, GLuint shader)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene, shader));
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, shader);
		}

	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene, GLuint shader)
	{
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;

			}

			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;

				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.texUV = vec;

				if (mesh->HasTangentsAndBitangents())
				{
					vector.x = mesh->mTangents[i].x;
					vector.y = mesh->mTangents[i].y;
					vector.z = mesh->mTangents[i].z;
					vertex.tangent = vector;

					vector.x = mesh->mBitangents[i].x;
					vector.y = mesh->mBitangents[i].y;
					vector.z = mesh->mBitangents[i].z;
					vertex.bitangent = vector;
				}


			}
			else
			{
				vertex.texUV = glm::vec2(0.0f, 0.0f);
			}


			vertices.push_back(vertex);

		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);

			}

		}


		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());



		return Mesh(vertices, indices, textures, shader);
	}

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;
		unsigned int slotnumtemp = NULL;
		//std::cout << "directory: " << directory << "\n";

		for (size_t i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);

			bool skip = false;
			for (size_t j = 0; j < texture_loaded.size(); j++)
			{
				if (std::strcmp(texture_loaded[j].GetPathData().c_str(), str.C_Str()) == 0)
				{
					textures.push_back(texture_loaded[j]);
					skip = true;
					break;

				}

			}
			if (!skip)
			{

				int textypetemp;

				if (type == aiTextureType_DIFFUSE)
				{
					textypetemp = DIFFUSE_TEXTURE;
				}
				else if (type == aiTextureType_SPECULAR)
				{
					textypetemp = SPECULAR_TEXTURE;
				}
				else if (type == aiTextureType_HEIGHT)
				{
					textypetemp = NORMAL_TEXTURE;
				}
				else if (type == aiTextureType_AMBIENT)
				{
					textypetemp = HEIGHT_TEXTURE;
				}

				Texture texture(str.C_Str(), slotnumtemp, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, textypetemp);
				std::cout << "directory: " << str.C_Str() << "\n";
				*texture.GetTexture() = TextureFromFile(str.C_Str(), this->directory);
				textures.push_back(texture);
				texture_loaded.push_back(texture);

			}

			slotnumtemp++;

		}

		return textures;

	}



	GLuint TextureFromFile(const char* path, const std::string& directory)
	{
		std::string filename = std::string(path);

		filename = directory + '/' + filename;

		std::cout << "directory: " << directory << "\n";

		GLuint textureID;
		glGenTextures(1, &textureID);

		int width, height, nrcomponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrcomponents, 0);

		if (data)
		{
			GLenum format;
			if (nrcomponents == 1)
			{
				format = GL_RED;
			}
			else if (nrcomponents == 3)
			{
				format = GL_RGB;
			}
			else if (nrcomponents == 4)
			{
				format = GL_RGBA;
			}

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);

		}
		else
		{
			std::cerr << "Texture failed to load at path :: " << path << "\n";
			stbi_image_free(data);
		}

		return textureID;
	}

	std::vector<Texture> texture_loaded;

};


#endif 


*/


