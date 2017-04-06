#include "ShaderManagerClass.h"

ShaderManagerClass::ShaderManagerClass()
{
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_FontShader = 0;
	m_SkyDomeShader = 0;
	m_TerrainShader = 0;
}

ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass &other)
{
}

ShaderManagerClass::~ShaderManagerClass()
{
}

bool ShaderManagerClass::Initialize(ID3D11Device *device, HWND hwnd)
{
	bool result;

	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
		return false;

	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
		return false;

	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
		return false;

	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
		return false;

	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
		return false;

	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
		return false;

	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
		return false;

	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
		return false;

	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
		return false;

	result = m_SkyDomeShader->Initialize(device, hwnd);
	if (!result)
		return false;

	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
		return false;

	result = m_TerrainShader->Initialize(device, hwnd);
	if (!result)
		return false;

	return true;
}

void ShaderManagerClass::Shutdown()
{
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = NULL;
	}

	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = NULL;
	}

	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = NULL;
	}

	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = NULL;
	}

	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = NULL;
	}

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = NULL;
	}

	return;
}

bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix, 
	XMMATRIX viewMatix,
	XMMATRIX projectionMatrix)
{
	return m_ColorShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatix,
		projectionMatrix);
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture)
{
	return m_TextureShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		texture);
}

bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix, 
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture,
	XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_LightShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		texture,
		lightDirection,
		diffuseColor);
}

bool ShaderManagerClass::RenderFontShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture, 
	XMFLOAT4 color)
{
	return m_FontShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		texture,
		color);
}

bool ShaderManagerClass::RenderSkyDomeShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	XMFLOAT4 apexColor,
	XMFLOAT4 centerColor)
{
	return m_SkyDomeShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		apexColor,
		centerColor);
}

bool ShaderManagerClass::RenderTerrainShader(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture,
	ID3D11ShaderResourceView *normalMap,
	ID3D11ShaderResourceView *normalMap2,
	ID3D11ShaderResourceView *normalMap3,
	XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_TerrainShader->Render(deviceContext,
		indexCount,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		texture,
		normalMap,
		normalMap2,
		normalMap3,
		lightDirection,
		diffuseColor);
}
