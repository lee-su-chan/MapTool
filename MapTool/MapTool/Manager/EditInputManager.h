#pragma once

#include "BaseSingleton.h"
#include "EditEnums.h"

class EditInputManager : public BaseSingleton<EditInputManager>
{
public:
	EditInputManager() = default;
	~EditInputManager() = default;

public:
#pragma region TerrainEdit
	TerrainEditType m_TerrainEditType;
#pragma endregion

#pragma region Brush
	BrushType m_BrushType;
	int m_BrushRadius;
#pragma endregion
};