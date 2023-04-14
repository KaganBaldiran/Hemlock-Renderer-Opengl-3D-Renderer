#ifndef MODEL_H
#define MODEL_H

#include <glew.h>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Meshhhh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "Helper_classes.h"

using namespace std;
using namespace newwww;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class worldtransform
{
public:

    glm::mat4 transformmatrix = glm::mat4(1.0f);
    glm::vec3 ObjectScales;
    float scale_avg;
    float dynamic_scale_avg;

    void translate(glm::vec3 position)
    {
        transformmatrix = glm::translate(transformmatrix, position);
    }

    void scale(glm::vec3 scale)
    {
        transformmatrix = glm::scale(transformmatrix, scale);
    }

    void rotate(float degree , glm::vec3 axis)
    {
        transformmatrix = glm::rotate(transformmatrix, glm::radians(degree), axis);

    }

    void SendUniformToShader(GLuint shader , const char *uniform)
    {
        UseShaderProgram(shader);
        glUniformMatrix4fv(glGetUniformLocation(shader, uniform), 1, GL_FALSE, glm::value_ptr(transformmatrix));
        UseShaderProgram(0);
    }

    glm::mat4 *GetTransformationMat4() { return &transformmatrix; };

};


class UIproperties
{
public:

    bool autorotate = false;
    float rotationamount = NULL;
    float keepoldrotation = NULL;
    vec3<float> moveamount = { NULL,NULL,NULL };
    vec3<float> maxmove = { 20.0f,20.0f,20.0f };
    vec3<float> newtreshold = { 20.0f,20.0f,20.0f };
    float degree;
    float scaleamount = 1.0f;
    float maxscale = 2.0f;

};


class Model
{
public:
    // model data 
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh>  meshes;
    string directory;
    bool gammaCorrection;
    string modelpath;
    worldtransform transformation;
    UIproperties UIprop;
    bool imported = false;
    uint* modelcounterptr;
    vec3<double> originpoint;

    glm::vec3 dynamic_origin;

    bool gizmo_first_time = true;

    
    
    
    Model(string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        
        static uint counter = 2;
        modelcounterptr = &counter;
        modelid = counter;
        modelpath = path;
        loadModel(path);
        counter++;
        
    }

    Model(bool gamma = false) : gammaCorrection(gamma)
    {
        static uint counter = 2;
        modelcounterptr = &counter;
        modelid = counter;
        counter++;

    }

    ~Model()
    {

        for (size_t i = 0; i < meshes.size(); i++)
        {
            meshes[i].CleanBuffer();
        }

        static long int model_count = NULL;

        std::cout << "Model " <<model_count<< " buffers are cleaned :: "<< modelpath << "\n";

        model_count++;

    }

    
    void Draw(GLuint shader , Camera& camera, GLuint shadowMap , GLuint cube_map_texture)
    {
        glUniform1i(glGetUniformLocation(shader, "modelID"), modelid);
        
        //std::cout << "Model ID " << modelid << "\n";

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader , camera,shadowMap,cube_map_texture);
    }


    int GetModelID() { return modelid; };

    int *GetModelIDptr() { return &modelid; };

    uint *GetModelIDcounterptr() { return modelcounterptr; };

private:

    int modelid;

    
    void loadModel(string const& path)
    {
        
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices);
        
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }



        std::vector<glm::vec3> originPoints;
        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[i];

            float minX = mesh->mVertices[0].x, minY = mesh->mVertices[0].y, minZ = mesh->mVertices[0].z;
            float maxX = mesh->mVertices[0].x, maxY = mesh->mVertices[0].y, maxZ = mesh->mVertices[0].z;
            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                if (mesh->mVertices[j].x < minX) minX = mesh->mVertices[j].x;
                if (mesh->mVertices[j].y < minY) minY = mesh->mVertices[j].y;
                if (mesh->mVertices[j].z < minZ) minZ = mesh->mVertices[j].z;
                if (mesh->mVertices[j].x > maxX) maxX = mesh->mVertices[j].x;
                if (mesh->mVertices[j].y > maxY) maxY = mesh->mVertices[j].y;
                if (mesh->mVertices[j].z > maxZ) maxZ = mesh->mVertices[j].z;
            }
            float centerX = (minX + maxX) / 2.0f;
            float centerY = (minY + maxY) / 2.0f;
            float centerZ = (minZ + maxZ) / 2.0f;

            originPoints.push_back(glm::vec3(centerX, centerY, centerZ));
        }

        // Compute overall origin point
        float overallCenterX = 0.0f, overallCenterY = 0.0f, overallCenterZ = 0.0f;
        for (unsigned int i = 0; i < originPoints.size(); i++) {
            overallCenterX += originPoints[i].x;
            overallCenterY += originPoints[i].y;
            overallCenterZ += originPoints[i].z;
        }
        overallCenterX /= originPoints.size();
        overallCenterY /= originPoints.size();
        overallCenterZ /= originPoints.size();

        originpoint = { overallCenterX,overallCenterY,overallCenterZ };

        dynamic_origin = glm::vec3(overallCenterX, overallCenterY, overallCenterZ);

        std::cout << "Overall origin point: (" << overallCenterX << ", " << overallCenterY << ", " << overallCenterZ << ")" << std::endl;

        
        // retrieve the directory path of the filepath

        directory = path.substr(0, path.find_last_of('/'));

        
        processNode(scene->mRootNode, scene);
    }

    
    void processNode(aiNode* node, const aiScene* scene)
    {
        
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }

    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene)
    {
        
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; 
            
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
           
            if (mesh->mTextureCoords[0]) 
            {
                glm::vec2 vec;
                
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.Tangent = vector;
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.Bitangent = vector;

                
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
      
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
     

        // 1. diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        Mesh newmesh(vertices, indices, textures);

        newmesh.meshname = mesh->mName.C_Str();

        newmesh.diffuse_textures.assign(diffuseMaps.begin(), diffuseMaps.end());
        newmesh.specular_textures.assign(specularMaps.begin(), specularMaps.end());
        newmesh.normal_textures.assign(normalMaps.begin(), normalMaps.end());
        
        return newmesh;
    }

    
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; 
                    break;
                }
            }
            if (!skip)
            {   
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
            }
        }
        return textures;
    }
};


unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(false);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    std::cout <<"Texture filepath: " << filename.c_str() << " widht: " << width << " height: " << height << " Count of components: " << nrComponents << "\n";

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

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
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
#endif