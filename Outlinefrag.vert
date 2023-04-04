#version 330 core

  layout(location = 0) in vec3 vertexdata;

  layout(location = 1) in vec3 aNormal;
  
  uniform mat4 model;
  
  uniform mat4 cameramatrix;

  uniform float scale_avg;
  

  void main()
  {
    vec4 pos = vec4(vertexdata + normalize(aNormal) * scale_avg * 0.004f , 1.0);
    gl_Position = cameramatrix * model * pos;
  }


  