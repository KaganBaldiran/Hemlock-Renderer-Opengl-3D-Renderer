#version 330 core

  in vec3 vertexdata;
  
  uniform mat4 model;
  
  uniform mat4 cameramatrix;
  

  void main()
  {
    vec4 pos = vec4(vertexdata.x  , vertexdata.y  , vertexdata.z, 1.0);
    gl_Position = cameramatrix * model * pos;

  }


  