#pragma once

#include "D3D_Defines.h"

class TerrainShaderClass
{
public:
	TerrainShaderClass();
	TerrainShaderClass(const TerrainShaderClass &);
	~TerrainShaderClass();

	bool Initialize(ID3D11Device *, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, XMFLOAT3, XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device *, HWND, const WCHAR *, const WCHAR *);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *, HWND, const WCHAR *);

	bool SetShaderParameters(ID3D11DeviceContext *, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, ID3D11ShaderResourceView *, XMFLOAT3, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext *, int);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11SamplerState *m_sampleState;
	ID3D11Buffer *m_lightBuffer;
};