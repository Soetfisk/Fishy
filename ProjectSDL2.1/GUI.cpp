#include "GUI.h"
#include <iostream>

GUI::GUI()
{
	InitTextureAtlas(DEFAULT_FONT);
	//InitCharacters(DEFAULT_FONT);
	InitBuffers();

	//InitTestBuffers();
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
	FT_Set_Pixel_Sizes(face, 0, (int)fontSize);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Iterate through character 32 to 127 in the ASCII table
	// Skipp first 32 ASCII characters because they are just control codes
	for (GLubyte c = 32; c < 128; c++)
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
				(GLuint)face->glyph->advance.x
			};

			characters.insert(std::pair<GLchar, Character>(c, character));
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void GUI::InitTextureAtlas(std::string fontName)
{
	// Initialize lib
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not initialize FreeType Library\n";

	std::string path = "fonts/" + fontName;
	// Load font
	if (FT_New_Face(ft, path.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font\n";

	// Set font size in width and height, 0 dynamiclly calculates the width/height based on the other, e.g. w = 0, h = 48
	FT_Set_Pixel_Sizes(face, 0, (int)fontSize);

	int w = 0;	// Atlas width
	int h = 0;	// Atlas height

	// Iterate through character 32 to 127 in the ASCII table
	// Skipp first 32 ASCII characters because they are just control codes
	for (int c = 32; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
		else
		{
			w += face->glyph->bitmap.width;
			h = (h > face->glyph->bitmap.rows) ? h : face->glyph->bitmap.rows;
		}
	}
	atlasWidth = w;
	atlasHeight = h;

	glGenTextures(1, &atlasTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	// Disable byte-alignment restriction
	glTexImage2D(	GL_TEXTURE_2D, 
					0, 
					GL_RED, 
					atlasWidth, 
					atlasHeight, 
					0, 
					GL_RED, 
					GL_UNSIGNED_BYTE, 
					0);

	int x = 0;
	for (int c = 32; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYPE: Failed to load Glyph\n";
		else
		{	
			// Save info about glyph
			chInfo[c].ax = face->glyph->advance.x >> 6;
			chInfo[c].ay = face->glyph->advance.y >> 6;
			chInfo[c].bw = face->glyph->bitmap.width;
			chInfo[c].bh = face->glyph->bitmap.rows;
			chInfo[c].bl = face->glyph->bitmap_left;
			chInfo[c].bt = face->glyph->bitmap_top;
			chInfo[c].tx = (float) x / atlasWidth;

			glTexSubImage2D(GL_TEXTURE_2D, 
							0, 
							x,
							0,
							face->glyph->bitmap.width, 
							face->glyph->bitmap.rows, 
							GL_RED, 
							GL_UNSIGNED_BYTE, 
							face->glyph->bitmap.buffer);
			x += face->glyph->bitmap.width;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void GUI::InitBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GUI::InitTestBuffers()
{
	glGenBuffers(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		GLfloat vertices[4][4] =
		{
			//{xpos,		ypos + h,	0.0, 0.0},
			{xpos,		ypos,		0.0, 1.0},
			{xpos + w,	ypos,		1.0, 1.0},

			{xpos,		ypos + h,	0.0, 0.0},
			//{xpos + w,	ypos,		1.0, 1.0},
			{xpos + w, ypos + h,	1.0, 0.0}
		};
		
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// Update VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Move cursors for next glyph (move is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale;	// Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GUI::TestRenderText(GLShader & shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	shader.Bind();
	glUniform3f(shader.GetUnifromLocation("textColor"), color.x, color.y, color.z);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters[*c];
		
	}
}

void GUI::OptimizedRenderText(GLShader & shader, const std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	Point* coords = new Point[6 * text.length()];
	int n = 0;

	shader.Bind();
	glUniform3f(shader.GetUnifromLocation("textColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		GLfloat x2 = x + chInfo[*c].bl * scale;
		GLfloat y2 = -y - chInfo[*c].bt * scale;
		GLfloat w = chInfo[*c].bw * scale;
		GLfloat h = chInfo[*c].bh * scale;

		// Move cursor to the start of next character
		x += chInfo[*c].ax * scale;
		y += chInfo[*c].ay * scale;

		if (w || h)
		{
			coords[n++] = { x2,		-y2,	chInfo[*c].tx,								0 };
			coords[n++] = { x2 + w,	-y2,	chInfo[*c].tx + chInfo[*c].bw / atlasWidth, 0 };
			coords[n++] = { x2,		-y2 - h,chInfo[*c].tx,								chInfo[*c].bh / atlasHeight };

			coords[n++] = { x2 + w, -y2,	chInfo[*c].tx + chInfo[*c].bw / atlasWidth, 0 };
			coords[n++] = { x2,		-y2 - h,chInfo[*c].tx,								chInfo[*c].bh / atlasHeight };
			coords[n++] = { x2 + w, -y2 - h,chInfo[*c].tx + chInfo[*c].bw / atlasWidth, chInfo[*c].bh / atlasHeight };
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, n);

	glActiveTexture(0);
	glBindVertexArray(0);
}

void GUI::RenderAtlasTexture(GLShader & shader)
{
	shader.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);

	GLfloat test[4][4]
	{
		{0,				0,				0, 0},
		{0,				window::HEIGHT, 0, 1},
		{window::WIDTH, 0,				1, 0},
		{window::WIDTH, window::HEIGHT,	1, 1}
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(test), test);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(test), test, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glActiveTexture(0);
	glBindVertexArray(0);
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
		height = (ch.size.y * scale > height) ? ch.size.y * scale : height;
	}
	return height;
}
