#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D shadowMap;

void main()
{ 
    FragColor = vec4(texture(shadowMap, TexCoords).r);
}