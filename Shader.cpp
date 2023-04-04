#include "Shader.h"
#include <glew.h>
#include <glfw3.h>
#include <string>
#include <fstream>

std::string ReadTextFile(const char* filepath)
{
    std::ifstream inp(filepath, std::ios::binary);

    if (inp)
    {
        std::string texts;
        inp.seekg(0, std::ios::end);
        texts.resize(inp.tellg());
        inp.seekg(0, std::ios::beg);
        inp.read(&texts[0], texts.size());
        inp.close();
        return texts;
    }
    else
    {
        std::cerr << "Error reading the text file :: " << filepath << "\n";

    }
}

GLuint CompileVertShader(const char* vertexsource)
{
    GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexshader, 1, &vertexsource, nullptr);
    glCompileShader(vertexshader);

    GLint status;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(vertexshader, 512, nullptr, buffer);
        std::cerr << "Failed to compile vertex shader :: " << buffer << "\n";

    }

    return vertexshader;

}

GLuint CompileFragShader(const char* fragmentsource)
{
    GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, &fragmentsource, nullptr);
    glCompileShader(fragmentshader);

    GLint status;
    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE);
    {

        char buffer[512];
        glGetShaderInfoLog(fragmentshader, 512, nullptr, buffer);
        std::cerr<< "Failed to compile fragment shader :: " << buffer << "\n";

    }

    return fragmentshader;
}

GLuint CompileShaderProgram(GLuint vertexshader , GLuint fragmentshader)
{
    GLuint m_program;
    m_program = glCreateProgram();
    glAttachShader(m_program, vertexshader);
    glAttachShader(m_program, fragmentshader);
    glLinkProgram(m_program);


    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(m_program, 512, nullptr, buffer);
        std::cerr << "Failed to link program :: " << buffer << "\n";
    }



    return m_program;
}

void UseShaderProgram(GLuint program)
{
    glUseProgram(program);
}

void DeleteShaderProgram(GLuint program)
{
    glDeleteProgram(program);
}

Shader::Shader(const char* vertsourcepath, const char* fragsourcepath)
{

    std::string vertsource = ReadTextFile(vertsourcepath);
    std::string fragsource = ReadTextFile(fragsourcepath);

    GLuint vertexshader = CompileVertShader(vertsource.c_str());
    GLuint fragmentshader = CompileFragShader(fragsource.c_str());
    shaderID = CompileShaderProgram(vertexshader, fragmentshader);

}

GLuint Shader::GetID()
{
    return shaderID;
}
