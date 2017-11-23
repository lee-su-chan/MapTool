#pragma once

#include "D3DClass.h"
#include "TerrainClass.h"
#include "RayClass.h"

class PickingToolClass
{
public:
	PickingToolClass() = default;
	PickingToolClass(const PickingToolClass &) = default;
	~PickingToolClass() = default;

public:
	void InitPick(D3DClass *direct3D, CameraClass *camera, int screenWidth, int screenHeight, int mousePosX, int mousePosY);
	void Picking(D3DClass *, TerrainClass *, XMVECTOR &);

	inline XMVECTOR GetRayOrignal() { return m_Ray.GetOriginal(); }
	inline XMVECTOR GetRayDirection() { return m_Ray.GetDirection(); }

//private:
//	bool IsCursorInWindow(HWND hwnd);

private:
	RayClass m_Ray;
};