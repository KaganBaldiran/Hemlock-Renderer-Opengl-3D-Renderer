#include "Buffers.h"
#include <glew.h>
#include <glfw3.h>

VBO::VBO()
{
    glGenBuffers(1, &vbo);
}

GLuint VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    return vbo;
}

GLuint VBO::GetBufferID()
{
    return vbo;
}

VBO::~VBO()
{
    glDeleteBuffers(1, &vbo);
}

VAO::VAO()
{
    glGenVertexArrays(1, &vao);

}

GLuint VAO::Bind()
{
    glBindVertexArray(vao);
    return vao;
}

GLuint VAO::GetVertexArrID()
{
    return vao;
}

VAO::~VAO()
{
    glDeleteVertexArrays(1, &vao);

}

void BindVBONull()
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
}

void BindVAONull()
{
    glBindVertexArray(NULL);
}

void BindEBONull()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

EBO::EBO()
{
    glGenBuffers(1, &ebo);
}

 GLuint EBO::Bind()
{
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
     return ebo;
}

GLuint EBO::GetEBOID()
{
    return ebo;
}

EBO::~EBO()
{
    glDeleteBuffers(1, &ebo);
}
