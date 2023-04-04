#include "PickingTexture.h"

void pickingtexture::Init(uint w_width, uint w_height)
{

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_picking_texture);
	glBindTexture(GL_TEXTURE_2D, m_picking_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, w_width, w_height, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_picking_texture, 0);


	glGenTextures(1, &m_depth_texture);
	glBindTexture(GL_TEXTURE_2D, m_depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, w_width, w_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_texture, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Frame buffer error :: " << status << "\n";
		exit(1);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void pickingtexture::EnableWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void pickingtexture::DisableWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

pickingtexture::pixelinfo pickingtexture::ReadPixel(uint x, uint y)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);

	glReadBuffer(GL_COLOR_ATTACHMENT0);

	pixelinfo pixel;

	glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &pixel);
	
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	return pixel;
}

bool picking_technique::init()
{


	return false;
}

void picking_technique::DrawStartCB(GLuint shader, uint Drawindex)
{
	glUniform1ui(glGetUniformLocation(shader, "drawindex"), Drawindex);
}

void picking_technique::SetObjectIndex(GLuint shader,uint Objectindex)
{
	glUniform1ui(glGetUniformLocation(shader, "objectindex"), Objectindex);
}



