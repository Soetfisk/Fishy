#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "GLUtil.h"
class FrameBuffer
{
private:
	enum
	{
		TEXTURE1,
		TEXTURE2,
		TEXTURE3,
		TEXTURE4,
		TEXTURE5,
		TEXTURE6,

		NUM_TEXTURES
	};
	GLuint texUniformID; // getuniformlocation 
	GLuint framebufferName;
	GLuint renderedTexture, renderedTexture2;
	GLuint textures[NUM_TEXTURES];
	GLenum* drawBuffers;
	int textureAmount;

public:
	FrameBuffer();
	~FrameBuffer();
	void CreateFrameBuffer(int textureAmount, int screenWidth, int screenHeight, GLint RGBformat);
	void BindFrameBuffer();
	void UnbindFrameBuffer();
	void BindTexturesToProgram(GLuint uniform, GLuint texture);
	void BindImageTexturesToProgram(GLuint uniform, GLuint texture);
};
#endif

