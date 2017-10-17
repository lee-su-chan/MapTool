#include "BrushClass.h"

BrushClass::BrushClass()
{

}

bool BrushClass::Init(ID3D11Device *device, 
	MyEnum::BrushShape eShape, 
	XMFLOAT4 color, 
	int radius, 
	int VertexCount)
{
	bool result;

	m_eShape = eShape;
	m_Color = color;
	m_Radius = radius;
	m_VertexCount = VertexCount;

	result = BuildCircleBuffers(device);
	if (!result)
		return false;

	result = BuildSquareleBuffers(device);
	if (!result)
		return false;

	return true;
}

void BrushClass::Render(ID3D11DeviceContext *deviceContext)
{
	//ID3D11Buffer *tempVertexBuffer;
	//ID3D11Buffer *tempIndexBuffer;
	//unsigned int stride;
	//unsigned int offset;

	//stride = sizeof(MyStruct::ColorVertexType);
	//offset = 0;

	//switch (m_eShape)
	//{
	//case MyEnum::BrushShape::CIRCLE:
	//	tempVertexBuffer = m_CircleVertexBuffer;
	//	tempIndexBuffer  = m_CircleIndexBuffer;
	//	break;

	//case MyEnum::BrushShape::RECTANGLE:
	//	tempVertexBuffer = m_SquareVertexBuffer;
	//	tempIndexBuffer = m_SquareIndexBuffer;
	//	break;

	//default:
	//	logic_error("BrushClass : Nothing case!");
	//	break;
	//}
	//
	//deviceContext->IASetVertexBuffers(0, 1, &tempVertexBuffer, &stride, &offset);
	//deviceContext->IASetIndexBuffer(tempIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
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
	if (m_SquareVertexBuffer)
	{
		m_SquareVertexBuffer->Release();
		m_SquareVertexBuffer = nullptr;
	}
	if (m_SquareIndexBuffer)
	{
		m_SquareIndexBuffer->Release();
		m_SquareIndexBuffer = nullptr;
	}
}

bool BrushClass::BuildCircleBuffers(ID3D11Device *device)
{
	HRESULT result;

	MyStruct::ColorVertexType *vertices;
	unsigned long *indices;

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	int index, indexCount;
	float radian;
	XMVECTOR currentPos, newPos;
	XMMATRIX matRot;

	index = 0;
	indexCount = m_VertexCount;
	radian = XM_PI * 2.0f / m_VertexCount;
	currentPos = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0);

	vertices = new MyStruct::ColorVertexType[m_VertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[indexCount];
	if (!indices)
		return false;

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(MyStruct::ColorVertexType) * m_VertexCount;
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
	XMStoreFloat3(&vertices[index].position, currentPos * m_Radius);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	for (int i = 1; i < m_VertexCount + 1; ++m_VertexCount)
	{

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

	return true;
}

bool BrushClass::BuildSquareleBuffers(ID3D11Device *device)
{
	MyStruct::ColorVertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	int index, vertexCount, indexCount;
	HRESULT result;

	index = 0;
	vertexCount = 24;
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

	// TODO : vertex of infomation
	vertices[index].position = XMFLOAT3(0, 0, 0);
	vertices[index].color = m_Color;
	indices[index] = index;
	++index;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_SquareVertexBuffer);
	if (FAILED(result))
		return false;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_SquareIndexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	return true;
}
