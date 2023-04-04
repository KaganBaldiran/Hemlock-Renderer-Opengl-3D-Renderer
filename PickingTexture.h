#ifndef PICKINGTEXTURE
#define PICKINGTEXTURE

#include<glew.h>
#include<iostream>
#include"Helper_classes.h"
typedef unsigned int uint;

struct mouseleftbuttom
{
	bool ispressed = false;
	int x, y;
};

class pickingtexture
{
public:

	void Init(uint w_width, uint w_height);

	void EnableWriting();
	void DisableWriting();
	

	struct pixelinfo
	{
		uint ObjectID = 0;
		uint DrawID = 0;
		uint PrimID = 0;

		void Print()
		{
			std::cout << "Object " << ObjectID << " draw " << DrawID << " prim " << PrimID << "\n";
		}
	};


	pixelinfo ReadPixel(uint x, uint y);

	GLuint onMouse(int x, int y , vec2<uint> windowscale) {
		
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		glReadPixels(x, windowscale.y - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
		glReadPixels(x, windowscale.y - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, windowscale.y - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	    //std::cout << "Clicked on pixel " << x << " " << y << " " << color[0] << " " << color[1] << " " << color[2] << "" << color[3] << " " << depth << " " << index << "\n";

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
			x, y, color[0], color[1], color[2], color[3], depth, index);

		return index;
	}


private:

	GLuint m_fbo = 0;
	GLuint m_picking_texture = 0;
	GLuint m_depth_texture = 0;

};


class picking_technique
{
public:

	bool init();

	void DrawStartCB(GLuint shader , uint Drawindex);

	void SetObjectIndex(GLuint shader,uint Objectindex);

};


#endif // !PICKINGTEXTURE
