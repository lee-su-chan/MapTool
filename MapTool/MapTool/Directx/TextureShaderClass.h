#pragma once

#include "D3D_Defines.h"

class TextureShaderClass
{
public:
	TextureShaderClass();
	TextureShaderClass(const TextureShaderClass &);
	~TextureShaderClass();

	bool Initialize(ID3D11Device *, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext *, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *);

private:
	bool InitializeShader(ID3D11Device *, HWND, const WCHAR *, const WCHAR *);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob *, HWND, const WCHAR *);

	bool SetShaderParameters(ID3D11DeviceContext *, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *);
	void RenderShader(ID3D11DeviceContext *, int);

private:
	ID3D11VertexShader *m_vertexShader;
	ID3D11PixelShader *m_pixelShader;
	ID3D11InputLayout *m_layout;
	ID3D11Buffer *m_matrixBuffer;
	ID3D11SamplerState *m_sampleState;
};