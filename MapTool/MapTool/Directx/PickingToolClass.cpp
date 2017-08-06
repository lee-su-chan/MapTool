#include "PickingToolClass.h"

PickingToolClass::PickingToolClass()
{
	m_isFirstCall = false;
}

bool PickingToolClass::BuildCircleBuffers(ID3D11Device *device)
{
	MyStruct::ColorVertexType *vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	XMFLOAT4 lineColor;
	int index, vertexCount, indexCount;

	lineColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
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

	// TODO: 정점 정보 채우기
	vertices[index].position = XMFLOAT3(0, 0, 0);
	vertices[index].color = lineColor;
	indices[index] = index;
	++index;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_circleVertexBuffer);
	if (FAILED(result))
		return false;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_circleIndexBuffer);
	if (FAILED(result))
		return false;

	delete[] vertices;
	vertices = NULL;

	delete[] indices;
	indices = NULL;

	return true;
}

void PickingToolClass::Picking(D3DClass *direct3D, TerrainClass *terrain, RayClass *ray)
{
	int pickVertex = -1;
	XMVECTOR v0, v1, v2;

	if (!m_isFirstCall)
	{
		BuildCircleBuffers(direct3D->GetDevice());
		m_isFirstCall = true;
	}

	for (int cellIndex = 0; cellIndex < terrain->GetCellCount(); ++cellIndex)
	{
		const int nVertex = terrain->GetTerrainCellObj()[cellIndex].GetVertexCount();
		XMFLOAT3 *tempVertexList = new XMFLOAT3[nVertex];
		float minDist = INT_MAX;

		pickVertex = -1;

		for (int i = 0; i < nVertex; ++i)
		{
			tempVertexList[i].x = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.x;
			tempVertexList[i].y = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.y;
			tempVertexList[i].z = terrain->GetTerrainCellObj()[cellIndex].m_vertexList[i].position.z;
		}
		for (int i = 0; i < nVertex / 3; ++i)
		{
			v0 = XMLoadFloat3(&tempVertexList[i * 3 + 0]);
			v1 = XMLoadFloat3(&tempVertexList[i * 3 + 1]);
			v2 = XMLoadFloat3(&tempVertexList[i * 3 + 2]);

			float currentDist = 0.0f;
			if (DirectX::TriangleTests::Intersects(ray->GetOriginal(),
				ray->GetDirection(),
				v0, v1, v2,
				currentDist))
			{
				if (currentDist < minDist)
				{
					minDist = currentDist;
					pickVertex = i * 3;
				}

				// TODO: 마우스 포인터에 따른 원 그리기

			}
		}

		if (pickVertex != -1)
		{
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 0].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 1].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].m_vertexList[pickVertex + 2].position.y += 0.016f;
			terrain->GetTerrainCellObj()[cellIndex].TranslateVertex(direct3D->GetDeviceContext());
		}
	}
}

void PickingToolClass::RenderPickingCircle(ID3D11DeviceContext *deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(MyStruct::ColorVertexType);
	offset = 0;
	
	deviceContext->IASetVertexBuffers(0, 1, &m_circleVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_circleIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}