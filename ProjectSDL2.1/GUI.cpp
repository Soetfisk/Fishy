#include "GUI.h"
#include <iostream>

GUI::GUI()
{
	ft = new FT_Library();
	face = new FT_Face();

	if (FT_Init_FreeType(ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";

	if (FT_New_Face(*ft, "fonts/arial.ttf", 0, face))
		std::cout << "ERROR::FREETYPE: Failed to load font\n";
}

GUI::~GUI()
{
	delete ft;
	delete face;
}
