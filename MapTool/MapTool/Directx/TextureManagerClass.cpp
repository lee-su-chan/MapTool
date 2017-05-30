#include "TextureManagerClass.h"

TextureManagerClass::TextureManagerClass()
{
	m_TextureArray = 0;
}

TextureManagerClass::TextureManagerClass(const TextureManagerClass &other)
{
}

TextureManagerClass::~TextureManagerClass()
{
}

bool TextureManagerClass::Initialize(int count)
{
	m_textureCount = count;

	m_TextureArray = new TextureClass[m_textureCount];
	if (!m_TextureArray)
		return false;

	return true;
}

void TextureManagerClass::Shutdown()
{
	int i;

	if (m_TextureArray)
	{
		for (i = 0; i < m_textureCount; ++i)
			m_TextureArray[i].Shutdown();

		delete[] m_TextureArray;
		m_TextureArray = NULL;
	}

	return;
}

bool TextureManagerClass::LoadTexture(ID3D11Device *device,
	ID3D11DeviceContext *deviceContext,
	char *path,
	char *filename,
	int location)
{
	bool result;

	result = m_TextureArray[location].Initialize(device, deviceContext, path, filename);
	if (!result)
		return false;

	return true;
}

ID3D11ShaderResourceView * TextureManagerClass::GetTexture(int id)
{
	return m_TextureArray[id].GetTexture();
}
