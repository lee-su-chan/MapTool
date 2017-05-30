#include "TextureClass.h"

TextureClass::TextureClass()
{
	m_texture = 0;
	m_textureView = 0;
}

TextureClass::TextureClass(const TextureClass &other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device *device,
	ID3D11DeviceContext *deviceContext,
	char *path,
	char *filename)
{
	bool result;
	std::string pathFileName;
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	HRESULT hResult;
	UINT rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ScratchImage image;

	pathFileName = path;
	pathFileName += filename;
	
	result = LoadTextureFromFile(image, (LPSTR)(LPCTSTR)pathFileName.c_str());
	if (!result)
		return false;

	hResult = CreateShaderResourceView(device, 
		image.GetImages(), 
		image.GetImageCount(),
		image.GetMetadata(), 
		&m_textureView);
	if (FAILED(hResult))
		return false;

	deviceContext->GenerateMips(m_textureView);

	return true;
}

void TextureClass::Shutdown()
{
	if (m_textureView)
	{
		m_textureView->Release();
		m_textureView = NULL;
	}

	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}

	return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_textureView;
}

bool TextureClass::LoadTextureFromFile(ScratchImage &image, LPCSTR filename)
{
	HRESULT hr;
	std::string str(filename);
	std::wstring ws(strconvert(str));
	WCHAR ext[_MAX_EXT];

	_wsplitpath_s(ws.c_str(),
		nullptr,
		0,
		nullptr,
		0,
		nullptr,
		0,
		ext,
		_MAX_EXT);

	if (_wcsicmp(ext, L".dds") == 0) 
		hr = LoadFromDDSFile(ws.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else if (_wcsicmp(ext, L".tga") == 0) 
		hr = LoadFromTGAFile(ws.c_str(), nullptr, image);
	else 
		hr = LoadFromWICFile(ws.c_str(), WIC_FLAGS_NONE, nullptr, image);

	if (FAILED(hr))
		return false;

	return true;
}
std::wstring TextureClass::strconvert(const std::string& _src)
{
	USES_CONVERSION;

	return std::wstring(A2W(_src.c_str()));
};