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
	virtual ~GUI();
private:
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

	void InitCharacters();
	void RenderText(GLShader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void Update(float& dt, int player1, int player2);
};

