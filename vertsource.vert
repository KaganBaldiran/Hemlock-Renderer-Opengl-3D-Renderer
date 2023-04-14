#version 330 core

  layout(location = 0) in vec3 vertexdata;
  layout(location = 3) in vec3 tangentnormal;
  layout(location = 4) in vec3 bitangentnormal;
  layout(location = 7) in vec3 inputcolors;
  layout(location = 2) in vec2 textcoord;
  layout(location = 1) in vec3 aNormal;
  
 
  out vec3 finalcolor;
  out vec2 finaltextcoord;
  out vec3 Normal;
  out vec3 currentpos;
  out vec3 bitangent;
  out vec3 tangent;
  
  out vec3 inverse_normal;

  out mat3 TBN;

  out vec4 FragPosLight;

  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 proj;
  uniform mat4 lightProjection;
  

  uniform mat4 cameramatrix;

  void main()
  {

    currentpos = vec3(model* vec4(vertexdata , 1.0f));
    gl_Position = cameramatrix * vec4(currentpos , 1.0f);
    
    bitangent = bitangentnormal;
    tangent = tangentnormal; 

    vec3 T = normalize(vec3(model * vec4(tangentnormal,0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangentnormal,0.0)));
    vec3 N = normalize(vec3(model * vec4(aNormal,0.0)));
    TBN = mat3(T,B,N);


    finaltextcoord = textcoord;
    finalcolor = inputcolors;

    //Normal = aNormal;
    Normal = vec3(model * vec4(aNormal,0.0));

    inverse_normal = mat3(transpose(inverse(model))) * aNormal;


    FragPosLight = lightProjection * vec4(currentpos , 1.0f);
    

  }


  