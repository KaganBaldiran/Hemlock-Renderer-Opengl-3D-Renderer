#include "Mesh.h"

Meshs::Meshs(std::vector<Vertexs> &vertices, std::vector<GLuint> &indices, std::vector<Textures> &textures , GLuint Shaderprogram)
{
    Meshs::vertices = vertices;
    Meshs::indices = indices;
    Meshs::textures = textures;

   
	this->vao.Bind();
	this->vbo.Bind();
	this->ebo.Bind();

    std::cout << "textures: " << textures.size() << "\n";

    GLint posattr = glGetAttribLocation(Shaderprogram, "vertexdata");
    glEnableVertexAttribArray(posattr);
    glVertexAttribPointer(posattr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexs), (GLvoid*)0);

    GLint colorattr = glGetAttribLocation(Shaderprogram, "inputcolors");
    glEnableVertexAttribArray(colorattr);
    glVertexAttribPointer(colorattr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexs), (GLvoid*)(3 * sizeof(GLfloat)));

    GLint texattr = glGetAttribLocation(Shaderprogram, "textcoord");
    glEnableVertexAttribArray(texattr);
    glVertexAttribPointer(texattr, 2, GL_FLOAT, GL_FALSE, sizeof(Vertexs), (GLvoid*)(6 * sizeof(GLfloat)));

    GLint normalattr = glGetAttribLocation(Shaderprogram, "aNormal");
    glEnableVertexAttribArray(normalattr);
    glVertexAttribPointer(normalattr, 3, GL_FLOAT, GL_FALSE, sizeof(Vertexs), (GLvoid*)(8 * sizeof(GLfloat)));

    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertexs), this->vertices.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_DYNAMIC_DRAW);

    BindVAONull();
    BindVBONull();
    BindEBONull();

   

}

void Meshs::Draw(GLuint shaderprogram, Camera& camera , GLenum drawmode)
{
    UseShaderProgram(shaderprogram);

    

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    std::string uniform;


    for (size_t i = 0; i < this->textures.size(); i++)
    {
        
        unsigned int pbr_type = textures[i].GetTexturePbrType();

        if (pbr_type == SPECULAR_TEXTURE)
        {
            std::string specular_string = "texture_specular";
            uniform = specular_string + std::to_string(numSpecular++);

        }
        else if (pbr_type == DIFFUSE_TEXTURE)
        {
            std::string diffuse_string = "texture_diffuse";
            uniform = diffuse_string + std::to_string(numDiffuse++);

        }

        textures[i].texunit(shaderprogram, uniform.c_str(), i);
        textures[i].Bind();

    }

   

    glUniform3f(glGetUniformLocation(shaderprogram, "campos"), camera.Position.x, camera.Position.y, camera.Position.z);

    camera.Matrix(shaderprogram, "cameramatrix");


    this->vao.Bind();

    

    glDrawElements(drawmode, indices.size(), GL_UNSIGNED_INT, 0);

    UseShaderProgram(0);

    BindVAONull();

}
