#version 330 core
layout (location = 0) in vec3 vertexdata;

uniform mat4 lightProjection;
uniform mat4 model;


void main()
{
    vec3 currentpos = vec3(model* vec4(vertexdata , 1.0f));
    gl_Position = lightProjection * vec4(currentpos , 1.0f);
}