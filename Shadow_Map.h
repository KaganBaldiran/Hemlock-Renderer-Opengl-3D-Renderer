#ifndef SHADOWMAP
#define SHADOWMAP

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include "Helper_classes.h"
#include "Buffers.h"
#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <array>



  class shadowmap
  {
  public:

	  shadowmap(uint shadowMapWidth, uint shadowMapHeight)
	  {
		  
		  glGenFramebuffers(1, &shadowMapfbo);

		  this->shadowMapWidth = shadowMapWidth;
		  this->shadowMapHeight = shadowMapHeight;
		  
		  glGenTextures(1, &shadowMap);
		  glBindTexture(GL_TEXTURE_2D, shadowMap);
		  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->shadowMapWidth, this->shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		  float clampcolor[] = { 1.0f,1.0f,1.0f,1.0f };
		  glTextureParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampcolor);

		  glBindFramebuffer(GL_FRAMEBUFFER, shadowMapfbo);
		  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
		  glDrawBuffer(GL_NONE);
		  glReadBuffer(GL_NONE);

		  GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		  if (result == GL_FRAMEBUFFER_COMPLETE)
		  {
			  std::cerr << "Framebuffer is complete." << "\n";

		  }
		  else
		  {
			  std::cerr << "Framebuffer is not complete." << "\n";

		  }

		  // Revert to the default framebuffer for now
		  glBindFramebuffer(GL_FRAMEBUFFER, 0);
		  

	  };

      ~shadowmap()
	  {
		  glDeleteFramebuffers(1, &shadowMapfbo);
		  glDeleteTextures(1, &shadowMap);

	  };


	  void LightProjection(glm::vec3 lightposition,GLuint shader ,GLFWwindow* window,std::vector<Model*> &models ,float scene_scale , Camera camera , vec2<int> current_viewport_size)
	  {
		 

		  glm::mat4 lightprojection = glm::mat4(1.0f);
		  glm::mat4 orthgonalProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -20.0f , 20.0f );
		  int height = NULL, width = NULL;
		  glfwGetWindowSize(window, &width, &height);

		  float total_scale = NULL;

		  
		  glm::mat4 CameraPositionTranslation = glm::mat4(1.0f);

		  CameraPositionTranslation = glm::translate(CameraPositionTranslation, glm::vec3(camera.Get_Position().x, NULL,-camera.Get_Position().z) / 7.0f);
		  /*
		  float ar = (float)current_viewport_size.x / (float)current_viewport_size.y;
		  float fov = glm::radians(45.0f);
		  float nearDist = 0.01f;
		  float farDist = 100.0f;
		  float Hnear = 2 * tan(fov / 2) * nearDist;
		  float Wnear = Hnear * ar;
		  float Hfar = 2 * tan(fov / 2) * farDist;
		  float Wfar = Hfar * ar;
		  glm::vec3 centerFar = camera.Position + 1.0f * farDist;

		  

		  glm::vec3 topLeftFar = centerFar + (camera.Up * Hfar / 2.0f) - (glm::vec3(1.0f, 0.0f, 0.0f) * Wfar / 2.0f);
		  glm::vec3 topRightFar = centerFar + (camera.Up * Hfar / 2.0f) + (glm::vec3(1.0f, 0.0f, 0.0f) * Wfar / 2.0f);
		  glm::vec3 bottomLeftFar = centerFar - (camera.Up * Hfar / 2.0f) - (glm::vec3(1.0f, 0.0f, 0.0f) * Wfar / 2.0f);
		  glm::vec3 bottomRightFar = centerFar - (camera.Up * Hfar / 2.0f) + (glm::vec3(1.0f, 0.0f, 0.0f) * Wfar / 2.0f);

		  glm::vec3 centerNear = camera.Position + glm::vec3(0.0f, 0.0f, 1.0f) * nearDist;

		  glm::vec3 topLeftNear = centerNear + (camera.Up * Hnear / 2.0f) - (glm::vec3(1.0f, 0.0f, 0.0f) * Wnear / 2.0f);
		  glm::vec3 topRightNear = centerNear + (camera.Up * Hnear / 2.0f) + (glm::vec3(1.0f, 0.0f, 0.0f) * Wnear / 2.0f);
		  glm::vec3 bottomLeftNear = centerNear - (camera.Up * Hnear / 2.0f) - (glm::vec3(1.0f, 0.0f, 0.0f) * Wnear / 2.0f);
		  glm::vec3 bottomRightNear = centerNear - (camera.Up * Hnear / 2.0f) + (glm::vec3(1.0f, 0.0f, 0.0f) * Wnear / 2.0f);

		  glm::vec3 frustumCenter = (centerFar - centerNear) * 0.5f;

		  glm::mat4 lightView = glm::lookAt(normalize(lightposition), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		  std::array<glm::vec3, 8> frustumToLightView
		  {
			  lightView * glm::vec4(bottomRightNear, 1.0f),
			  lightView * glm::vec4(topRightNear, 1.0f),
			  lightView * glm::vec4(bottomLeftNear, 1.0f),
			  lightView * glm::vec4(topLeftNear, 1.0f),
			  lightView * glm::vec4(bottomRightFar, 1.0f),
			  lightView * glm::vec4(topRightFar, 1.0f),
			  lightView * glm::vec4(bottomLeftFar, 1.0f),
			  lightView * glm::vec4(topLeftFar, 1.0f)
		  };

		  // find max and min points to define a ortho matrix around
		  glm::vec3 min{ INFINITY, INFINITY, INFINITY };
		  glm::vec3 max{ -INFINITY, -INFINITY, -INFINITY };
		  for (unsigned int i = 0; i < frustumToLightView.size(); i++)
		  {
			  if (frustumToLightView[i].x < min.x)
				  min.x = frustumToLightView[i].x;
			  if (frustumToLightView[i].y < min.y)
				  min.y = frustumToLightView[i].y;
			  if (frustumToLightView[i].z < min.z)
				  min.z = frustumToLightView[i].z;

			  if (frustumToLightView[i].x > max.x)
				  max.x = frustumToLightView[i].x;
			  if (frustumToLightView[i].y > max.y)
				  max.y = frustumToLightView[i].y;
			  if (frustumToLightView[i].z > max.z)
				  max.z = frustumToLightView[i].z;
		  }

		  float l = min.x;
		  float r = max.x;
		  float b = min.y;
		  float t = max.y;
		  // because max.z is positive and in NDC the positive z axis is 
		  // towards us so need to set it as the near plane flipped same for min.z.
		  float n = -max.z;
		  float f = -min.z;

		  // finally, set our ortho projection
		  // and create the light space view-projection matrix
		  glm::mat4 lightProjection = glm::ortho(l, r, b, t, n, f);
		  glm::mat4 lightSpaceMatrix = lightProjection * lightView;
		  */

		  glm::mat4 scale = glm::mat4(1.0f);
		  scale = glm::scale(scale,glm::vec3(200.0f / scene_scale , 200.0f / scene_scale, 200.0f / scene_scale));

		  

		  //glm::mat4 orthgonalProjection = glm::perspective(glm::radians(45.0f), (float)(width/ height), 0.1f, 100.0f);
		  glm::mat4 lightView = glm::lookAt(lightposition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		  
		  //glm::mat4 lightView = glm::lookAt(lightposition, glm::vec3(camera.Get_Position().x,NULL, -camera.Get_Position().z), glm::vec3(0.0f, 1.0f, 0.0f));

		  

		  lightprojection = orthgonalProjection * lightView;

		  //lightprojection = lightSpaceMatrix;
		  //translation = glm::translate(translation, -(average_origin_point / 10.0f));


		  lp = lightprojection;

		  UseShaderProgram(shader);

		  glUniformMatrix4fv(glGetUniformLocation(shader, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightprojection));

		  UseShaderProgram(0);

		 

	  };

	  GLuint GetShadowMapFBO() { return this->shadowMapfbo; };

	  uint GetShadowMapImage() { return this->shadowMap; };

	  vec2<uint> GetShadowMapSize() { return { this->shadowMapWidth, this->shadowMapHeight }; };

	  glm::mat4 GetLightProjection() { return this->lp; };



  private:

	  GLuint shadowMapfbo;
	  GLuint shadowMap;
	  uint shadowMapWidth;
	  glm::mat4 lp;
	  uint shadowMapHeight;
	  
	  

  };





#endif // !1

