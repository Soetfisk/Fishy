#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "GLUtil.h"
class FrameBuffer
{
private:
	GLuint texUniformID; // getuniformlocation 
	GLuint framebufferName;
	GLuint renderedTexture;
public:
	FrameBuffer();
	~FrameBuffer();
	void CreateFrameBuffer();
	void BindFrameBuffer();
	void UnbindFrameBuffer();
	void BindTexturesToProgram(GLuint uniform);
};
#endif

