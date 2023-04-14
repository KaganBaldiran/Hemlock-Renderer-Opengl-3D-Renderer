#ifndef MESH_H
#define MESH_H

#include <glew.h>// holds all OpenGL type declarations

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Camera.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4
namespace newwww {
    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture {
        unsigned int id = NULL;
        string type;
        string path;
    };

    class Mesh {
    public:
        // mesh Data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture>      textures;

        vector<Texture>  diffuse_textures;
        vector<Texture>  specular_textures;
        vector<Texture>  normal_textures;

        std::string meshname = "";

        int disableclaymaterial[4] = { 0,0,0,0};

        unsigned int VAO;

        // constructor
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            // now that we have all the required data, set the vertex buffers and its attribute pointers.
            setupMesh();
        }

        void CleanBuffer()
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            
            for (auto temp : textures)
            {
                glDeleteTextures(1, &temp.id);
            }

        }

        // render the mesh
        void Draw(GLuint shader, Camera& camera , GLuint shadowMap,GLuint cube_map_texture)
        {

            UseShaderProgram(shader);
            // bind appropriate textures
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            unsigned int metalicNr = 1;

            //std::cout << "Texture size: " << textures.size() << "\n";
            for (unsigned int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                string number;
                string name = textures[i].type;
                if (name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (name == "texture_specular")
                    number = std::to_string(specularNr++); // transfer unsigned int to string
                else if (name == "texture_normal")
                    number = std::to_string(normalNr++); // transfer unsigned int to string
                else if (name == "texture_height")
                    number = std::to_string(heightNr++); // transfer unsigned int to string
                else if (name == "texture_metalic")
                    number = std::to_string(metalicNr++); // transfer unsigned int to string



                std::cout << "TEXTURE UNIFORM: " << (name + number).c_str() << "\n";

                // now set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(shader, (name + number).c_str()), i);



                if (std::strcmp((name + number).data(), "texture_diffuse1") == 0)
                {

                    disableclaymaterial[0] = 1;
                }
                else if(std::strcmp((name + number).data(), "texture_specular1") == 0)
                {

                    disableclaymaterial[1] = 1;
                }
                else if (std::strcmp((name + number).data(), "texture_normal1") == 0)
                {

                    disableclaymaterial[2] = 1;
                }
                else if (std::strcmp((name + number).data(), "texture_metalic1") == 0)
                {

                    disableclaymaterial[3] = 1;
                }


                GLuint boolArrayLocation = glGetUniformLocation(shader, "disableclaymaterial");

                glUniform1iv(boolArrayLocation, 4, disableclaymaterial);

                //std::cout << "Texture Name: " << (name + number).c_str() << "\n";

                // and finally bind the texture
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }

            


            glUniform3f(glGetUniformLocation(shader, "campos"), camera.Position.x, camera.Position.y, camera.Position.z);

            camera.Matrix(shader, "cameramatrix");

            
            glActiveTexture(GL_TEXTURE0 + 7);

            glBindTexture(GL_TEXTURE_2D, shadowMap);


            glUniform1i(glGetUniformLocation(shader, "shadowMap"), 7);

            glActiveTexture(GL_TEXTURE0 + 10);

            glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
            glUniform1i(glGetUniformLocation(shader, "skybox"), 10);

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindTexture(GL_TEXTURE_2D, 0);
            // always good practice to set everything back to defaults once configured.
            glActiveTexture(GL_TEXTURE0);

            
            for (size_t h = 0; h < 4; h++)
            {
               disableclaymaterial[h] = 0;

            }

            GLuint boolArrayLocation = glGetUniformLocation(shader, "disableclaymaterial");

            glUniform1iv(boolArrayLocation, 4, disableclaymaterial);
            
        }

        // initializes all the buffer objects/arrays
        void setupMesh()
        {
            // create buffers/arrays
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            // load data into vertex buffers
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // A great thing about structs is that their memory layout is sequential for all its items.
            // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
            // again translates to 3/2 floats which translates to a byte array.
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // set the vertex attribute pointers
            // vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            // vertex tangent
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
            // vertex bitangent
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
            // ids
            glEnableVertexAttribArray(5);
            glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

            // weights
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

    private:
        // render data 
        unsigned int VBO, EBO;

        
    };
}
#endif