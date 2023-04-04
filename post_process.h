#ifndef EDGE_DETECT
#define EDGE_DETECT

#include<glew.h>

typedef unsigned int uint;

class FBO
{
public:

	FBO();

	void Bind(GLenum usage);

	void DeleteFBO();

	GLuint *GetScreenImage() { return &screen_image; };
	GLuint *GetFBO() { return &fbo; };
	GLuint* GetRBO() { return &rbo; };

private:

	GLuint fbo;
	GLuint screen_image;
	GLuint rbo;

};


   void BindFBONULL();
  
   void CreateCustomFrameBuffer(FBO *fbo, uint width, uint height);




#endif // !EDGE_DETECT


