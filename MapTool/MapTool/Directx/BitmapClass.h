#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_

#include <DirectXMath.h>

using namespace DirectX;

#include "TextureClass.h"

class BitmapClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass &);
	~BitmapClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, int, int, int, int, char *, char *);
	void Shutdown();
	bool Render(ID3D11DeviceContext *, int, int);

	int GetIndexCount();
	ID3D11ShaderResourceView *GetTexture();

private:
	bool InitializeBuffers(ID3D11Device *);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext *, int, int);
	void RenderBuffers(ID3D11DeviceContext *);
	bool LoadTexture(ID3D11Device *, ID3D11DeviceContext *, char *, char *);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
	TextureClass *m_Texture;
};

#endif