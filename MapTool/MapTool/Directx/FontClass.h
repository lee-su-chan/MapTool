#pragma once

#include "TextureClass.h"

class FontClass
{
public:
	FontClass();
	FontClass(const FontClass &);
	~FontClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, const char *, const char *, const char *, float, int);
	void Shutdown();

	ID3D11ShaderResourceView *GetTexture();
	void BuildVertexArray(void *, const char *, float, float);
	int GetSentencePixelLength(const char *);
	int GetFontHeight();

private:
	bool LoadFontData(char *);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device *, ID3D11DeviceContext *, const char *, const char *);
	void ReleaseTexture();

private:
	MyStruct::FontType *m_Font;
	TextureClass *m_Texture;
	float m_fontHeight;
	int m_spaceSize;
};