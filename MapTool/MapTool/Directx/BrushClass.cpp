#include "BrushClass.h"

BrushClass::BrushClass()
{
	m_CircleVertexBuffer = nullptr;
	m_CircleIndexBuffer = nullptr;
	m_RectangleVertexBuffer = nullptr;
	m_RectangleIndexBuffer = nullptr;
	m_CircleIndexCount = 0;
	m_RectangleIndexCount = 0;
	m_IndexCount = 0;
}

bool BrushClass::Initialize(ID3D11Device *device,
	XMFLOAT4 color)
{
	bool result;

	m_Color = color;

	result = BuildCircleBuffers(device);
	if (!result)
		return false;

	result = BuildRectangleBuffers(device);
	if (!result)
		return false;

	return true;
}

bool BrushClass::Render(ID3D11DeviceContext *deviceContext)
{
	switch (EditInputManager::GetInstance()->m_BrushType)
	{
	case BrushType::CIRCLE:
		m_IndexCount = m_CircleIndexCount;
		RenderCircle(deviceContext);
		return true;

	case BrushType::RECTANGLE:
		m_IndexCount = m_RectangleIndexCount;
		RenderRectangle(deviceContext);
		return true;

	default:
		return false;
	}
}

void BrushClass::Shutdown()
{
	if (m_CircleVertexBuffer)
	{
		m_CircleVertexBuffer->Release();
		m_CircleVertexBuffer = nullptr;
	}
	if (m_CircleIndexBuffer)
	{
		m_CircleIndexBuffer->Release();
		m_CircleIndexBuffer = nullptr;
	}
	if (m_RectangleVertexBuffer)
	{
		m_RectangleVertexBuffer->Release();
		m_RectangleVertexBuffer = nullptr;
	}
	if (m_RectangleIndexBuffer)
	{
		m_RectangleIndexBuffer->Release();
		m_RectangleIndexBuffer = nullptr;
	}
}

bool BrushClass::BuildCircleBuffers(ID3D11Device *device)
{
	HRESULT result;

	MyStruct::ColorVertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	int index, indexCount, vertexCount;
	float radian;
	XMVECTOR currentPos, newPos;
	XMMATRIX matRot;

	index = 0;
	indexCount = vertexCount = 24;
	radian = XM_PI * 2.0f / vertexCount;
	currentPos = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0);

	vertices = new MyStruct::ColorVertexType[vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[indexCount];
	if (!indices)
		return false;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(MyStruct::ColorVertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// TODO vertex of infomation
	XMStoreFloat3(&vertices[index].position, currentPos * EditInputManager::GetInstance()->m_BrushRadius);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	for (int i = 1; i < vertexCount + 1; ++vertexCount)
	{
		// TODO: set vertecies
	}

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_CircleVertexBuffer);
	if (FAILED(result))
		return false;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_CircleIndexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	m_CircleIndexCount = index - 1;

	return true;
}
bool BrushClass::BuildRectangleBuffers(ID3D11Device *device)
{
	MyStruct::ColorVertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	int index, vertexCount, indexCount;
	HRESULT result;

	index = 0;
	vertexCount = 4;
	indexCount = vertexCount;

	vertices = new MyStruct::ColorVertexType[vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[indexCount];
	if (!indices)
		return false;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(MyStruct::ColorVertexType) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// TODO : set vertices
	vertices[index].position = XMFLOAT3(0, 0, 0);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	vertices[index].position = XMFLOAT3(1, 0, 0);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	vertices[index].position = XMFLOAT3(0, 0, -1);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	vertices[index].position = XMFLOAT3(1, 0, 1);
	vertices[index].color = m_Color;
	indices[index] = index;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_RectangleVertexBuffer);
	if (FAILED(result))
		return false;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_RectangleIndexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	m_RectangleIndexCount = index;

	return true;
}

void BrushClass::RenderCircle(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(MyStruct::ColorVertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_CircleVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_CircleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
void BrushClass::RenderRectangle(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(MyStruct::ColorVertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_RectangleVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_RectangleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
