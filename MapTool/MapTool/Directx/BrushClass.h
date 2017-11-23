#pragma once

#include "D3D_Core.h"
#include "../Manager/EditInputManager.h"

class BrushClass
{
public:
	BrushClass();
	BrushClass(const BrushClass &) = default;
	~BrushClass() = default;

public:
	bool Initialize(ID3D11Device *, XMFLOAT4);
	bool Render(ID3D11DeviceContext *);
	void Shutdown();

public:
	//void SetPosition();
	inline void SetColor(XMFLOAT4 color) { m_Color = color; }
	inline int GetIndexCount() { return m_IndexCount; }

private:
	bool BuildCircleBuffers(ID3D11Device *);
	bool BuildRectangleBuffers(ID3D11Device *);

	void RenderCircle(ID3D11DeviceContext *);
	void RenderRectangle(ID3D11DeviceContext *);

private:
	ID3D11Buffer *m_CircleVertexBuffer;
	ID3D11Buffer *m_CircleIndexBuffer;
	int m_CircleIndexCount;

	ID3D11Buffer *m_RectangleVertexBuffer;
	ID3D11Buffer *m_RectangleIndexBuffer;
	int m_RectangleIndexCount;

private:
	XMFLOAT4 m_Color;
	int m_IndexCount;
};