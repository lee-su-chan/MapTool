#pragma once

#include <atlstr.h>
#include <vector>

#define MAIN_WND_WIDTH		1680
#define MAIN_WND_HEIGHT		1024

#define DIRECT_WND_WIDTH	1280
#define DIRECT_WND_HEIGHT	1024

namespace MyStruct
{
	struct TERRAIN_DESC
	{
		int nCell;
		int nTile;

		std::vector<std::string> *textureNames;
		int textureCurSel;	// Cursor Select
		int nTexture;
		char *baseTextureName;
	};
}