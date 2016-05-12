#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H
#include "GLUtil.h"
#include "GLShader.h"
#include <map>

class GUI
{
public:
	GUI();
	GUI(std::string& fontName);
	virtual ~GUI();
	
	void RenderText(GLShader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void TestRenderText(GLShader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void OptimizedRenderText(GLShader& shader, const std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	
	GLfloat GetTextLenght(std::string& text, GLfloat& scale);
	GLfloat GetTextHeight(std::string& text, GLfloat& scale);

private:
	const std::string DEFAULT_FONT = "Starjedi.ttf";

	struct Point
	{
		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};

	struct CharacterInfo
	{
		float ax; // advance.x
		float ay; // advance.y

		float bw; // bitmap.width
		float bh; // bitmap.rows

		float bl; // bitmap_left
		float bt; // bitmap_top

		float tx; // x offset of glyph in texture coordinates
	}chInfo[128];
	int atlasWidth, atlasHeight;
	GLuint atlasTexture;

	struct Character
	{
		GLuint textureID;	// ID handle of the glyph texture
		glm::ivec2 size;	// Size of the glyph
		glm::ivec2 bearing;	// Offset from baseline to left/top of glyph
		GLuint advance;		// Offset to advance to next glyph
	};
	std::map<GLchar, Character> characters;

	FT_Library ft;
	FT_Face face;
	float fontSize = 48;

	GLuint VAO, VBO;

	void InitCharacters(std::string fontName);
	void InitTextureAtlas(std::string fontName);
	void InitBuffers();
};

