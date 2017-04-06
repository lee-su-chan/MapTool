#include "MinimapClass.h"

MiniMapClass::MiniMapClass()
{
	m_MiniMapBitmap = 0;
	m_PointBitmap = 0;
}

MiniMapClass::MiniMapClass(const MiniMapClass &other)
{
}

MiniMapClass::~MiniMapClass()
{
}

bool MiniMapClass::Initialize(ID3D11Device *device,
	ID3D11DeviceContext *deviceContext,
	int screenWidth,
	int screenHeight, 
	float terrainWidth,
	float terrainHeight)
{
	bool result;

	m_mapSizeX = 150.0f;
	m_mapSizeY = 150.0f;

	m_mapLocationX = screenWidth - (int)m_mapSizeX - 10;
	m_mapLocationY = 10;

	m_terrainWidth = terrainWidth;
	m_terrainHeight = terrainHeight;

	m_MiniMapBitmap = new BitmapClass;
	if (!m_MiniMapBitmap)
		return false;

	result = m_MiniMapBitmap->Initialize(device,
		deviceContext,
		screenWidth,
		screenHeight,
		154,
		154,
		"data/minimap/minimap.tga");
	
	if (!result)
		return false;

	m_PointBitmap = new BitmapClass;
	if (!m_PointBitmap)
		return false;

	result = m_PointBitmap->Initialize(device,
		deviceContext,
		screenWidth,
		screenHeight,
		3,
		3,
		"data/minimap/point.tga");

	if (!result)
		return false;

	return true;
}

void MiniMapClass::Shutdown()
{
	if (m_PointBitmap)
	{
		m_PointBitmap->Shutdown();
		delete m_PointBitmap;
		m_PointBitmap = NULL;
	}

	if (m_MiniMapBitmap)
	{
		m_MiniMapBitmap->Shutdown();
		delete m_MiniMapBitmap;
		m_MiniMapBitmap = NULL;
	}

	return;
}

bool MiniMapClass::Render(ID3D11DeviceContext *deviceContext,
	ShaderManagerClass *shaderManager,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX orthoMatrix)
{
	bool result;

	result = m_MiniMapBitmap->Render(deviceContext,
		m_mapLocationX,
		m_mapLocationY);

	if (!result)
		return false;

	result = shaderManager->RenderTextureShader(deviceContext,
		m_MiniMapBitmap->GetIndexCount(),
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_MiniMapBitmap->GetTexture());

	if (!result)
		return false;

	result = m_PointBitmap->Render(deviceContext,
		m_pointLocationX,
		m_pointLocationY);

	if (!result)
		return false;

	result = shaderManager->RenderTextureShader(deviceContext,
		m_PointBitmap->GetIndexCount(),
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_PointBitmap->GetTexture());

	if (!result)
		return false;

	return true;
}

void MiniMapClass::PositionUpdate(float positionX, float positionZ)
{
	float percentX, percentY;

	if (positionX < 0) positionX = 0.0f;
	if (positionZ < 0) positionZ = 0.0f;
	if (positionX > m_terrainWidth)  positionX = m_terrainWidth;
	if (positionZ > m_terrainHeight) positionZ = m_terrainHeight;

	percentX = positionX / m_terrainWidth;
	percentY = 1.0f - positionZ / m_terrainHeight;

	m_pointLocationX = (m_mapLocationX + 2) + (int)(percentX * m_mapSizeX);
	m_pointLocationY = (m_mapLocationY + 2) + (int)(percentY * m_mapSizeY);

	m_pointLocationX -= 1.0f;
	m_pointLocationY -= 1.0f;

	return;
}
