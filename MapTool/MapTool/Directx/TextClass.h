#pragma once

#include "FontClass.h"
#include "ShaderManagerClass.h"

class TextClass
{
private:

public:
	TextClass();
	TextClass(const TextClass &);
	~TextClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, int, int, int, bool, FontClass *, const char *, int, int, float, float, float);
	void Shutdown();
	void Render(ID3D11DeviceContext *, ShaderManagerClass *, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *);

	bool UpdateSentence(ID3D11DeviceContext *, FontClass *, const char *, int, int, float, float, float);
	
private:
	bool InitializeSentence(ID3D11Device *, ID3D11DeviceContext *, FontClass *, const char *, int, int, float, float, float);
	void RenderSentence(ID3D11DeviceContext *, ShaderManagerClass *, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView *);

private:
	ID3D11Buffer *m_vertexBuffer, *m_vertexBuffer2, *m_indexBuffer, *m_indexBuffer2;
	int m_screenWidth, m_screenHeight, m_maxLength, m_vertexCount, m_indexCount;
	bool m_shadow;
	XMFLOAT4 m_pixelColor;
};