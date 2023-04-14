#include "Cubemap.h"
#include "stb_image.h"


CubeMap::CubeMap(std::vector<std::string> texture_faces ,const char* vertex_source, const char* frag_source)
{
    this->texture_faces.assign(texture_faces.begin(),texture_faces.end());
	
	glGenTextures(1, &this->cubemaptextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemaptextureID);

    int width, height, nrchannels;
    unsigned char* data;

    for (size_t i = 0; i < texture_faces.size(); i++)
    {
        data = stbi_load(this->texture_faces[i].c_str(), &width, &height, &nrchannels, 0);

        if (data)
        {

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

        }
        else
        {

            std::cout << "Cubemap error :: failed to load at path  " << this->texture_faces.at(i) << "\n";
            stbi_image_free(data);

        }
    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    cubemapshader = new Shader(vertex_source, frag_source);


    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };



    vao.Bind();
    vbo.Bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);

    BindVAONull();
    BindVBONull();


}

CubeMap::~CubeMap()
{
    delete this->cubemapshader;
    glDeleteTextures(1, &this->cubemaptextureID);
}

void CubeMap::Draw(Camera &camera)
{
    
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);


    //glClear(GL_STENCIL_BUFFER_BIT);

    UseShaderProgram(cubemapshader->GetID());

    glm::mat4 view = glm::mat4(glm::mat3(camera.cam_view));

    glUniform1i(glGetUniformLocation(cubemapshader->GetID(), "skybox"), 0);
    glUniformMatrix4fv(glGetUniformLocation(cubemapshader->GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
    glUniformMatrix4fv(glGetUniformLocation(cubemapshader->GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));

    

    vao.Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemaptextureID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    BindVAONull();

    UseShaderProgram(0);

}
