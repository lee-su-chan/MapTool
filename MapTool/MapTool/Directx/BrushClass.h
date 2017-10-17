#pragma once

#include "D3D_Core.h"

class BrushClass
{
public:
	BrushClass();
	BrushClass(const BrushClass &) = default;
	~BrushClass() = default;

public:
	bool Init(ID3D11Device *, MyEnum::BrushShape, XMFLOAT4, int, int);
	void Render(ID3D11DeviceContext *);
	void Shutdown();

public:
	void SetPosition();

public:
	inline void SetColor(XMFLOAT4 color) { m_Color = color; }

private:
	bool BuildCircleBuffers(ID3D11Device *);
	bool BuildSquareleBuffers(ID3D11Device *);

private:
	ID3D11Buffer *m_CircleVertexBuffer;
	ID3D11Buffer *m_CircleIndexBuffer;

	ID3D11Buffer *m_SquareVertexBuffer;
	ID3D11Buffer *m_SquareIndexBuffer;

private:
	XMFLOAT4 m_Color;
	MyEnum::BrushShape m_eShape;

	int m_Radius;
	int m_VertexCount;
};