#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

#include "D3DClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "LightShaderClass.h"
#include "FontShaderClass.h"
#include "SkyDomeShaderClass.h"
#include "TerrainShaderClass.h"

class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass &);
	~ShaderManagerClass();

	bool Initialize(ID3D11Device *, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *);
	bool RenderLightShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *, XMFLOAT3, XMFLOAT4);
	bool RenderFontShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *, XMFLOAT4);
	bool RenderSkyDomeShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, XMFLOAT4, XMFLOAT4);
	bool RenderTerrainShader(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, XMFLOAT3, XMFLOAT4);

private:
	ColorShaderClass *m_ColorShader;
	TextureShaderClass *m_TextureShader;
	LightShaderClass *m_LightShader;
	FontShaderClass *m_FontShader;
	SkyDomeShaderClass *m_SkyDomeShader;
	TerrainShaderClass *m_TerrainShader;
};

#endif