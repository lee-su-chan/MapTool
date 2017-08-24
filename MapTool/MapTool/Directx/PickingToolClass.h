#pragma once

#include "D3DClass.h"
#include "TerrainClass.h"
#include "RayClass.h"

class PickingToolClass
{
public:
	PickingToolClass();
	PickingToolClass(const PickingToolClass &) = default;
	~PickingToolClass() = default;

public:
	bool InitPick(D3DClass *direct3D, CameraClass *camera, HWND hwnd, int screenWidth, int screenHeight, int cursorX, int cursorY);
	void Picking(D3DClass *, TerrainClass *);
	void RenderPickingCircle(ID3D11DeviceContext *);

private:
	bool BuildCircleBuffers(ID3D11Device *);

private:
	bool IsCursorInWindow(HWND hwnd);

private:
	RayClass m_Ray;

private:
	ID3D11Buffer *m_circleVertexBuffer;
	ID3D11Buffer *m_circleIndexBuffer;

private:
	bool m_isFirstCall;

};