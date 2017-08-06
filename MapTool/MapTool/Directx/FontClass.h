#pragma once

#include "TextureClass.h"

class FontClass
{
public:
	FontClass();
	FontClass(const FontClass &);
	~FontClass();

	bool Initialize(ID3D11Device *, ID3D11DeviceContext *, char *, char *, char *, float, int);
	void Shutdown();

	ID3D11ShaderResourceView *GetTexture();
	void BuildVertexArray(void *, char *, float, float);
	int GetSentencePixelLength(char *);
	int GetFontHeight();

private:
	bool LoadFontData(char *);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device *, ID3D11DeviceContext *, char *, char *);
	void ReleaseTexture();

private:
	MyStruct::FontType *m_Font;
	TextureClass *m_Texture;
	float m_fontHeight;
	int m_spaceSize;
};