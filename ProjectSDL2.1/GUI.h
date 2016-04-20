#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

class GUI
{
public:
	GUI();
	virtual ~GUI();
private:
	FT_Library* ft;
	FT_Face* face;
};

