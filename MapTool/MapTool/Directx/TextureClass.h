#pragma once

#include "D3D_Core.h"

class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass &);
	~TextureClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, const char *, const char *);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool LoadTextureFromFile(ScratchImage &, const LPCSTR);
	std::wstring strconvert(const std::string &);

private:
	ID3D11Texture2D *m_texture;
	ID3D11ShaderResourceView *m_textureView;
};