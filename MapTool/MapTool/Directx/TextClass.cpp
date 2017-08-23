#include "TextClass.h"

TextClass::TextClass()
{
	m_vertexBuffer = 0;
	m_vertexBuffer2 = 0;
	m_indexBuffer = 0;
	m_indexBuffer2 = 0;
}

TextClass::TextClass(const TextClass &other)
{
}

TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D11Device *device, 
	ID3D11DeviceContext *deviceContext,
	int screenWidth, 
	int screenHeight, 
	int maxLength, 
	bool shadow, 
	FontClass *font, 
	const char *text,
	int posX, 
	int posY,
	float red, 
	float green, 
	float blue)
{
	bool result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_maxLength = maxLength;
	m_shadow = shadow;

	result = InitializeSentence(device,
		deviceContext,
		font,
		text,
		posX,
		posY,
		red,
		green,
		blue);

	if (!result)
		return false;

	return true;
}

void TextClass::Shutdown()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}

	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer2)
	{
		m_vertexBuffer2->Release();
		m_vertexBuffer2 = NULL;
	}

	if (m_indexBuffer2)
	{
		m_indexBuffer2->Release();
		m_indexBuffer2 = NULL;
	}

	return;
}

void TextClass::Render(ID3D11DeviceContext *deviceContext,
	ShaderManagerClass *shaderManager, 
	XMMATRIX worldMatrix, 
	XMMATRIX viewMatrix, 
	XMMATRIX orthoMartrix, 
	ID3D11ShaderResourceView *fontTexture)
{
	RenderSentence(deviceContext,
		shaderManager,
		worldMatrix,
		viewMatrix,
		orthoMartrix,
		fontTexture);

	return;
}

bool TextClass::UpdateSentence(ID3D11DeviceContext *deviceContext, 
	FontClass *font, 
	const char *text, 
	int posX, 
	int posY, 
	float red, 
	float green, 
	float blue)
{
	int numLetters;
	MyStruct::TextureVertexType *vertices;
	float drawX, drawY;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	void *verticesPtr;
	HRESULT result;

	m_pixelColor = XMFLOAT4(red, green, blue, 1.0f);
	numLetters = (int)strlen(text);

	if (numLetters > m_maxLength)
		return false;

	vertices = new MyStruct::TextureVertexType[m_vertexCount];
	if (!vertices)
		return false;

	memset(vertices, 0, (sizeof(MyStruct::TextureVertexType) * m_vertexCount));

	drawX = (float)(m_screenWidth / 2 * -1 + posX);
	drawY = (float)(m_screenHeight / 2 + posY);

	font->BuildVertexArray((void *)vertices, text, drawX, drawY);

	result = deviceContext->Map(m_vertexBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource);

	if (FAILED(result))
		return false;

	verticesPtr = (void *)mappedResource.pData;
	memcpy(verticesPtr, (void *)vertices, (sizeof(MyStruct::TextureVertexType) * m_vertexCount));
	
	deviceContext->Unmap(m_vertexBuffer, 0);

	if (m_shadow)
	{
		memset(vertices, 0, (sizeof(MyStruct::TextureVertexType) * m_vertexCount));

		drawX = (float)(m_screenWidth / 2 * -1 + posX + 2);
		drawY = (float)(m_screenHeight / 2 - posX - 2);

		font->BuildVertexArray((void *)vertices, text, drawX, drawY);

		result = deviceContext->Map(m_vertexBuffer2,
			0,
			D3D11_MAP_WRITE_DISCARD,
			0,
			&mappedResource);

		if (FAILED(result))
			return false;

		verticesPtr = (void *)mappedResource.pData;
		memcpy(verticesPtr, (void *)vertices, (sizeof(MyStruct::TextureVertexType) * m_vertexCount));
		
		deviceContext->Unmap(m_vertexBuffer2, 0);
	}

	delete[] vertices;
	vertices = NULL;

	return true;
}

bool TextClass::InitializeSentence(ID3D11Device *device, 
	ID3D11DeviceContext *deviceContext, 
	FontClass *font, 
	const char *text,
	int posX, 
	int posY, 
	float red, 
	float green, 
	float blue)
{
	MyStruct::TextureVertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	m_vertexCount = 6 * m_maxLength;
	m_indexCount = 6 * m_maxLength;

	vertices = new MyStruct::TextureVertexType[m_vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	memset(vertices, 0, (sizeof(MyStruct::TextureVertexType) * m_vertexCount));

	for (i = 0; i < m_indexCount; ++i)
		indices[i] = i;

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(MyStruct::TextureVertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;

	if (m_shadow)
	{
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer2);
		if (FAILED(result))
			return false;

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer2);
		if (FAILED(result))
			return false;
	}

	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	result = UpdateSentence(deviceContext,
		font,
		text,
		posX,
		posY,
		red,
		green,
		blue);

	if (!result)
		return false;

	return true;
}

void TextClass::RenderSentence(ID3D11DeviceContext *deviceContext, 
	ShaderManagerClass *shaderManager, 
	XMMATRIX worldMatrix, 
	XMMATRIX viewMatrix, 
	XMMATRIX orthoMatrix, 
	ID3D11ShaderResourceView *fontTexture)
{
	unsigned int stride, offset;
	XMFLOAT4 shadowColor;

	stride = sizeof(MyStruct::TextureVertexType);
	offset = 0;

	if (m_shadow)
	{
		shadowColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer2, &stride, &offset);
		deviceContext->IASetIndexBuffer(m_indexBuffer2, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		shaderManager->RenderFontShader(deviceContext,
			m_indexCount,
			worldMatrix,
			viewMatrix,
			orthoMatrix,
			fontTexture,
			shadowColor);
	}

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shaderManager->RenderFontShader(deviceContext,
		m_indexCount,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		fontTexture,
		m_pixelColor);

	return;
}
