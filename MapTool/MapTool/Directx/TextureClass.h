#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

#include <d3d11.h>
#include <stdio.h>
#include <string>
#include <atlconv.h>
#include <DirectXTex.h>

using namespace DirectX;

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass &);
	~TextureClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, char *, char *);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadTextureFromFile(ScratchImage &, LPCSTR filename);
	std::wstring strconvert(const std::string& _src);

private:
	ID3D11Texture2D *m_texture;
	ID3D11ShaderResourceView *m_textureView;
};

#endif