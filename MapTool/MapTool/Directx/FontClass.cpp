#include "FontClass.h"

FontClass::FontClass()
{
	m_Font = 0;
	m_Texture = 0;
}

FontClass::FontClass(const FontClass &)
{
}

FontClass::~FontClass()
{
}

bool FontClass::Initialize(ID3D11Device *device, 
	ID3D11DeviceContext *deviceContext,
	char *path,
	char *fontFilename,
	char *textureFilename, 
	float fontHeight, 
	int spaceSize)
{
	bool result;
	std::string pathFileName;

	m_fontHeight = fontHeight;
	m_spaceSize = spaceSize;
	pathFileName = path;
	pathFileName += fontFilename;

	result = LoadFontData((char *)pathFileName.c_str());
	if (!result)
		return false;

	result = LoadTexture(device, deviceContext, path, textureFilename);
	if (!result)
		return false;

	return true;
}

void FontClass::Shutdown()
{
	ReleaseTexture();
	ReleaseFontData();
}

ID3D11ShaderResourceView * FontClass::GetTexture()
{
	return m_Texture->GetTexture();
}

void FontClass::BuildVertexArray(void *vertices, 
	char *sentence, 
	float drawX, 
	float drawY)
{
	MyStruct::TextureVertexType *vertexPtr;
	int numLetters, index, i, letter;

	vertexPtr = (MyStruct::TextureVertexType *)vertices;
	numLetters = (int)strlen(sentence);
	index = 0;

	for (i = 0; i < numLetters; ++i)
	{
		letter = (int)sentence[i] - 32;
		
		if (letter == 0)
			drawX += (float)m_spaceSize;
		else
		{
			// First triangle in quad.
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f); // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			++index;

			vertexPtr[index].position = XMFLOAT3(drawX + m_Font[letter].size,
				drawY - m_fontHeight, 
				0.0f); // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			++index;

			vertexPtr[index].position = XMFLOAT3(drawX, drawY - m_fontHeight, 0.0f); // Bottom left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			++index;

			// Second triangle in quad.
			vertexPtr[index].position = XMFLOAT3(drawX, drawY, 0.0f); // Top left.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].left, 0.0f);
			++index;

			vertexPtr[index].position = XMFLOAT3(drawX + m_Font[letter].size, drawY, 0.0f); // Top right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 0.0f);
			++index;

			vertexPtr[index].position = XMFLOAT3(drawX + m_Font[letter].size, 
				drawY - m_fontHeight, 
				0.0f); // Bottom right.
			vertexPtr[index].texture = XMFLOAT2(m_Font[letter].right, 1.0f);
			++index;

			drawX += m_Font[letter].size + 1.0f;
		}
	}

	return;
}

int FontClass::GetSentencePixelLength(char *sentence)
{
	int pixelLength, numLetters, i, letter;

	pixelLength = 0;
	numLetters = (int)strlen(sentence);

	for (i = 0; i < numLetters; ++i)
	{
		letter = (int)sentence[i] - 32;

		if (letter == 0)
			pixelLength += m_spaceSize;
		else
			pixelLength += m_Font[letter].size + 1;
	}

	return pixelLength;
}

int FontClass::GetFontHeight()
{
	return (int)m_fontHeight;
}

bool FontClass::LoadFontData(char *filename)
{
	ifstream fin;
	int i;
	char temp;

	m_Font = new MyStruct::FontType[95];

	if (!m_Font)
		return false;

	fin.open(filename);

	if (fin.fail())
		return false;

	for (i = 0; i < 95; ++i)
	{
		fin.get(temp);

		while (temp != ' ')
			fin.get(temp);

		fin.get(temp);

		while (temp != ' ')
			fin.get(temp);

		fin >> m_Font[i].left;
		fin >> m_Font[i].right;
		fin >> m_Font[i].size;
	}

	fin.close();

	return true;
}

void FontClass::ReleaseFontData()
{
	if (m_Font)
	{
		delete[] m_Font;
		m_Font = NULL;
	}
}

bool FontClass::LoadTexture(ID3D11Device *device, 
	ID3D11DeviceContext *deviceContext, 
	char *path,
	char *filename)
{
	bool result;

	m_Texture = new TextureClass;

	if (!m_Texture)
		return false;

	result = m_Texture->Initialize(device, deviceContext, path, filename);

	if (!result)
		return false;

	return true;
}

void FontClass::ReleaseTexture()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = NULL;
	}
}
