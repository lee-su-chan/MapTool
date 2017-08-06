#pragma once

#include "BitmapClass.h"
#include "ShaderManagerClass.h"

class MiniMapClass
{
public:
	MiniMapClass();
	MiniMapClass(const MiniMapClass &);
	~MiniMapClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, int, int, float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext *, ShaderManagerClass *, XMMATRIX, XMMATRIX, XMMATRIX);

	void PositionUpdate(float, float);

private:
	int m_mapLocationX, m_mapLocationY, m_pointLocationX, m_pointLocationY;
	float m_mapSizeX, m_mapSizeY, m_terrainWidth, m_terrainHeight;
	BitmapClass *m_MiniMapBitmap, *m_PointBitmap;
};