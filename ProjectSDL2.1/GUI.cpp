#include "GUI.h"
#include <iostream>

GUI::GUI()
{
	InitCharacters(DEFAULT_FONT);
	InitBuffers();
	
}

GUI::GUI(std::string& fontName)
{
	InitCharacters(fontName);
	InitBuffers();
}

GUI::~GUI()
{
	
}

void GUI::InitCharacters(std::string fontName)
{
	// Initialize lib
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";

	std::string path = "fonts/" + fontName;
	// Load font
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font\n";

	// Set font size in width and height, 0 dynamiclly calculates the width/height based on the other, e.g. w = 0, h = 48
	FT_Set_Pixel_Sizes(face, 0, fontSize);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
		else
		{
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
				);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			Character character =
			{
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			characters.insert(std::pair<GLchar, Character>(c, character));
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void GUI::InitBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GUI::RenderText(GLShader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	shader.Bind();
	glUniform3f(shader.GetUnifromLocation("textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];
		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		
		// Update VBO for each character
		GLfloat vertices[6][4] =
		{
			{xpos,		ypos + h,	0.0, 0.0},
			{xpos,		ypos,		0.0, 1.0},
			{xpos + w,	ypos,		1.0, 1.0},

			{xpos,		ypos + h,	0.0, 0.0},
			{xpos + w,	ypos,		1.0, 1.0},
			{xpos + w, ypos + h,	1.0, 0.0}
		};
		
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// Update VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Move cursors for next glyph (move is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale;	// Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLfloat GUI::GetTextLenght(std::string& text, GLfloat& scale)
{
	GLfloat lenght = 0;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];
		lenght += (ch.advance >> 6) * scale;
	}
	return lenght;
}

GLfloat GUI::GetTextHeight(std::string & text, GLfloat & scale)
{
	GLfloat height = 0;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];
		if (ch.size.y * scale > height)
			height = ch.size.y * scale;
	}
	return height;
}
