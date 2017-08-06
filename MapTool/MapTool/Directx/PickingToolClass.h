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

private:
	bool BuildCircleBuffers(ID3D11Device *);

public:
	void Picking(D3DClass *, TerrainClass *, RayClass *);
	void RenderPickingCircle(ID3D11DeviceContext *);

private:
	bool m_isFirstCall;

	ID3D11Buffer *m_circleVertexBuffer;
	ID3D11Buffer *m_circleIndexBuffer;
};