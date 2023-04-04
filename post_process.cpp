#include "post_process.h"

#include<iostream>



FBO::FBO()
{
	glGenFramebuffers(1, &fbo);
}

void FBO::Bind(GLenum usage)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FBO::DeleteFBO()
{
	glDeleteFramebuffers(1, &fbo);
}

void BindFBONULL()
{
	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
}

void CreateCustomFrameBuffer(FBO *fbo , uint width , uint height)
{

	fbo->Bind(GL_FRAMEBUFFER);

	glGenTextures(1, fbo->GetScreenImage());
	glBindTexture(GL_TEXTURE_2D, *fbo->GetScreenImage());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *fbo->GetScreenImage(), 0);


	glGenRenderbuffers(1, fbo->GetRBO());
	glBindRenderbuffer(GL_RENDERBUFFER, *fbo->GetRBO());
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *fbo->GetRBO());


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
}
