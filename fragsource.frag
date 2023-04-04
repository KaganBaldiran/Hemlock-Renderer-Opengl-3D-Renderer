#version 330 core

  in vec2 finaltextcoord;
  in vec3 finalcolor;
  out vec4 outColor;
  in vec3 Normal;
  in vec3 currentpos;

  in vec3 bitangent;
  in vec3 tangent;

  in mat3 TBN;

  in vec4 FragPosLight;

  uniform sampler2D color;

  uniform vec4 colorpr;

  uniform sampler2D texture_diffuse0;
  uniform sampler2D texture_specular0;
  uniform sampler2D texture_normal0;
  uniform sampler2D texture_diffuse1;
  uniform sampler2D texture_specular1;
  uniform sampler2D texture_normal1;
  uniform sampler2D texture_diffuse2;
  uniform sampler2D stexture_specular2;
  uniform sampler2D texture_normal2;
  uniform sampler2D texture_diffuse3;
  uniform sampler2D texture_specular3;
  uniform sampler2D texture_normal3;
  uniform sampler2D texture_diffuse4;
  uniform sampler2D texture_specular4;
  uniform sampler2D texture_normal4;
  uniform sampler2D shadowMap;


  uniform vec4 lightColor1;
  uniform vec3 lightpos1;


  uniform vec4 lightColors[10];
  uniform vec3 lightpositions[10];
  uniform int numberoflights;

  uniform int typeoflight[10];


  uniform int stencilindex;
  uniform int modelID;

  uniform bool enablehighlight;


  uniform int disableclaymaterial[3];


  uniform vec3 campos;


  float near = 0.1;
  float far = 100.0;

  
  float ShadowCalculation(vec4 fragPosLightSpace , vec3 lightDir ,vec3 normal)
  {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = max(0.02 * (1.0 - dot(normal, lightDir)), 0.003);  
    //float bias = 0.05;  
    
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
      for(int y = -1; y <= 1; ++y)
      {
         float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
         shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
      }    
    }
    shadow /= 9.0;


    return shadow;
  }

  vec4 pointLight(vec4 texturespecular , vec4 texturediffuse , vec3 lightpos , vec4 lightColor , vec3 inputnormal , bool blinn_phong)
  {
     
     vec3 lightvec = (lightpos - currentpos);


     float dist = length(lightvec);
     float a = 1.0f;
     float b = 0.1f;
     float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);


     float ambient = 0.20f;

     vec3 normal = normalize(inputnormal);
     vec3 lightDirection = normalize(lightvec);
     float diffuse = max(dot(normal , lightDirection),0.0f);

     float specularlight = 0.50f;
     vec3 viewdirection = normalize(campos - currentpos);
     vec3 reflectdirection = reflect(-lightDirection , normal);
     vec3 halfwaydir = normalize(lightDirection + viewdirection);

     float specular;

     if(blinn_phong)
     {
        float specamount = pow(max(dot(normal,halfwaydir),0.0),32.0);
        specular = specamount * specularlight;
     }
     else
     {
       float specamount = pow(max(dot(viewdirection , reflectdirection ), 0.0f),16);
       specular = specamount * specularlight;
     }

     float shadow = 0.0f;
     vec3 lightcoords = FragPosLight.xyz / FragPosLight.w;
     if(lightcoords.z <= 1.0f);
     {
        lightcoords = (lightcoords + 1.0f) / 2.0f;

        float closestdepth = texture(shadowMap,lightcoords.xy).r * 10.0f;
        float currentdepth = lightcoords.z;

        if(currentdepth > closestdepth)
        {
           shadow = 1.0f;
        }
     }
     
     shadow = ShadowCalculation(FragPosLight,lightDirection,normal);
     

     return (texturediffuse * lightColor * ((diffuse  * inten + ambient) + texturespecular.r * specular  * inten));
     
 
  }


  vec4 directionalLight(vec4 texturespecular , vec4 texturediffuse, vec3 lightpos , vec4 lightColor , vec3 inputnormal , bool blinn_phong)
  {
  
     float ambient = 0.20f;

     vec3 normal = normalize(inputnormal);
     vec3 lightDirection = normalize(lightpos);
     float diffuse = max(dot(normal , lightDirection),0.0f);

     float specularlight = 1.0f;
     vec3 viewdirection = normalize(campos - currentpos);
     vec3 reflectdirection = reflect(-lightDirection , normal);
     vec3 halfwaydir = normalize(lightDirection + viewdirection);

     float specular;

     if(blinn_phong)
     {
        float specamount = pow(max(dot(normal,halfwaydir),0.0),32.0);
        specular = specamount * specularlight;
     }
     else
     {
       float specamount = pow(max(dot(viewdirection , reflectdirection ), 0.0f),16);
       specular = specamount * specularlight;
     }

     
     float shadow = ShadowCalculation(FragPosLight,lightDirection,normal);
     

     return (texturediffuse * lightColor * ((diffuse * (1.0f - shadow)  + ambient) + texturespecular * specular * (1.0f - shadow) ));
     
  }


  vec4 spotLight(vec4 texturespecular , vec4 texturediffuse, vec3 lightpos , vec4 lightColor, vec3 inputnormal , bool blinn_phong)
  {
  
     vec3 lightvec = (lightpos - currentpos);

     float outercone = 0.90f;
     float innercone = 0.95f;

     float ambient = 0.20f;

     vec3 normal = normalize(inputnormal);
     vec3 lightDirection = normalize(lightvec);
     float diffuse = max(dot(normal , lightDirection),0.0f);

     float specularlight = 0.50f;
     vec3 viewdirection = normalize(campos - currentpos);
     vec3 reflectdirection = reflect(-lightDirection , normal);
     vec3 halfwaydir = normalize(lightDirection + viewdirection);

     float specular;

     if(blinn_phong)
     {
        float specamount = pow(max(dot(normal,halfwaydir),0.0),32.0);
        specular = specamount * specularlight;
     }
     else
     {
       float specamount = pow(max(dot(viewdirection , reflectdirection ), 0.0f),16);
       specular = specamount * specularlight;
     }


     float angle = dot(vec3(0.0f,-1.0f,0.0f),-lightDirection);
     float inten = clamp((angle - outercone) / (innercone - outercone), 0.0f , 1.0f);


     return (texturediffuse * lightColor * ((diffuse * inten + ambient) + texturespecular * specular * inten));
     
 
  }




  float linearizeDepth(float depth)
  {
  
     float z = depth * 2.0 - 1.0;
     return (2.0 * near * far) / (far + near - z * (far - near));

  }

  vec4 DepthDemonstration()
  {
     float depth = linearizeDepth(gl_FragCoord.z) / far;
     return vec4(vec3(depth),1.0);
  }



  void main() 
  {

     vec3 resultnormal;

     
     if(disableclaymaterial[2] == 0)
     {
         resultnormal = Normal;
         
     }
     else
     {
          resultnormal = texture(texture_normal1,finaltextcoord).rgb;

          resultnormal = resultnormal * 2.0f - 1.0f;
          resultnormal = normalize(TBN * resultnormal);
        //resultnormal = vec3(resultnormal.x , 1.0 - resultnormal.y , resultnormal.z);

     }
     
     
     vec4 specularmap;

     if(disableclaymaterial[1] == 0)
     {
        specularmap = vec4(2.0f,2.0f,2.0f,2.0f);
     }
     else
     {
        specularmap = texture(texture_specular1, finaltextcoord) * vec4(2.0f,2.0f,2.0f,2.0f);

     }

     //vec4 inverted_rougness = vec4(1.0 - specularmap.r , 1.0 - specularmap.g , 1.0 - specularmap.b , 1.0f);

     vec4 inverted_rougness = specularmap;

     specularmap = vec4(0.7f,0.7f,0.7f,1.0f);
     

     vec4 texturecolor ;

     if(disableclaymaterial[0] == 0)
     {
        texturecolor = vec4(1.0f,1.0f,1.0f,1.0f);
     }
     else
     {
         texturecolor = texture(texture_diffuse1, finaltextcoord);

     }
     
      
     

     vec4 claymodel = vec4(1.0f,1.0f,1.0f,1.0f);

     vec4 endresult = vec4(0.0f,0.0f,0.0f,0.0f);

     for(int i = 0; i < numberoflights; i++)
     {
       if(typeoflight[i] == 100)
       {
          endresult += pointLight(inverted_rougness,texturecolor,lightpositions[i],lightColors[i] , resultnormal , true);
          
       }     
       else if(typeoflight[i] == 200)
       {
          endresult += directionalLight(inverted_rougness,texturecolor,lightpositions[i],lightColors[i] , resultnormal , true);
       }
       else if(typeoflight[i] == 300)
       {
          endresult += spotLight(inverted_rougness,texturecolor,lightpositions[i],lightColors[i] , resultnormal , true);
       }
     }

     //endresult += directionalLight(inverted_rougness,texturecolor,lightpositions[0],lightColors[0] , resultnormal , true);

     //outColor = endresult * vec4(1.5f,1.5f,1.5f,1.5f);
       outColor = endresult ;
     
     
     if(enablehighlight)
     {
        outColor = endresult * vec4(5.5f,5.5f,2.5f,2.5f);
     }

     

     //outColor = endresult * vec4(1.5f,1.5f,1.5f,1.5f);
    
     //outColor = DepthDemonstration();
     
        

  }